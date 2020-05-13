/*
  Copyright (c) 2017 Daniel Fekete

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  Copyright (c) 2019 STMicroelectronics
  Modified to support Arduino_Core_STM32
*/

#include "Arduino.h"
#include "HardwareTimer.h"

#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)

/* Private Defines */
#define PIN_NOT_USED 0xFF
#define MAX_RELOAD ((1 << 16) - 1) // Currently even 32b timers are used as 16b to have generic behavior

/* Private Variables */
timerObj_t *HardwareTimer_Handle[TIMER_NUM] = {NULL};

/**
  * @brief  HardwareTimer constructor: set default configuration values
  * @param  Timer instance ex: TIM1, ...
  * @retval None
  */
HardwareTimer::HardwareTimer(TIM_TypeDef *instance)
{
  uint32_t index = get_timer_index(instance);
  if (index == UNKNOWN_TIMER) {
    Error_Handler();
  }

  HardwareTimer_Handle[index] = &_timerObj;

  _timerObj.handle.Instance = instance;
  _timerObj.handle.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
  _timerObj.handle.hdma[0] = NULL;
  _timerObj.handle.hdma[1] = NULL;
  _timerObj.handle.hdma[2] = NULL;
  _timerObj.handle.hdma[3] = NULL;
  _timerObj.handle.hdma[4] = NULL;
  _timerObj.handle.hdma[5] = NULL;
  _timerObj.handle.hdma[6] = NULL;
  _timerObj.handle.Lock = HAL_UNLOCKED;
  _timerObj.handle.State = HAL_TIM_STATE_RESET;

  _timerObj.__this = (void *)this;
  _timerObj.preemptPriority = TIM_IRQ_PRIO;
  _timerObj.subPriority = TIM_IRQ_SUBPRIO;

  /* Enable timer clock. Even if it is also done in HAL_TIM_Base_MspInit(),
     it is done there so that it is possible to write registers right now */
  enableTimerClock(&(_timerObj.handle));

  // Initialize NULL callbacks
  for (int i = 0; i < TIMER_CHANNELS + 1 ; i++) {
    callbacks[i] = NULL;
  }

  // Initialize channel mode and complementary
  for (int i = 0; i < TIMER_CHANNELS; i++) {
#if defined(TIM_CCER_CC1NE)
    isComplementaryChannel[i] = false;
#endif
    _ChannelMode[i] = TIMER_DISABLED;
  }

  /* Configure timer with some default values */
  _timerObj.handle.Init.Prescaler = 0;
  _timerObj.handle.Init.Period = MAX_RELOAD;
  _timerObj.handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  _timerObj.handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
#if defined(TIM_RCR_REP)
  _timerObj.handle.Init.RepetitionCounter = 0;
#endif
  _timerObj.handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&(_timerObj.handle));
}

/**
  * @brief  Pause HardwareTimer: stop timer
  * @param  None
  * @retval None
  */
void HardwareTimer::pause()
{
  // Disable all IT
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_UPDATE);
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_CC1);
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_CC2);
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_CC3);
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_CC4);

  // Disable timer unconditionally
  LL_TIM_DisableCounter(_timerObj.handle.Instance);

#if defined(TIM_CHANNEL_STATE_SET_ALL)
  /* Starting from G4, new Channel state implementation prevents to restart a channel,
     if the channel has not been explicitly be stopped with HAL interface */
  TIM_CHANNEL_STATE_SET_ALL(&(_timerObj.handle), HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET_ALL(&(_timerObj.handle), HAL_TIM_CHANNEL_STATE_READY);
#endif
}

/**
  * @brief  Pause only one channel.
  *         Timer is still running but channel is disabled (output and interrupt)
  * @param  Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::pauseChannel(uint32_t channel)
{
  int timAssociatedInputChannel;
  int LLChannel = getLLChannel(channel);
  if (LLChannel == -1) {
    Error_Handler();
  }

  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  // Disable channel and corresponding interrupt
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), interrupt);
  LL_TIM_CC_DisableChannel(_timerObj.handle.Instance, LLChannel);
#if defined(TIM_CHANNEL_STATE_SET)
  /* Starting from G4, new Channel state implementation prevents to restart a channel,
     if the channel has not been explicitly be stopped with HAL interface */
  if (isComplementaryChannel[channel - 1]) {
    TIM_CHANNEL_N_STATE_SET(&(_timerObj.handle), getChannel(channel), HAL_TIM_CHANNEL_STATE_READY);
  } else {
    TIM_CHANNEL_STATE_SET(&(_timerObj.handle), getChannel(channel), HAL_TIM_CHANNEL_STATE_READY);
  }
#endif

  // In case 2 channels are used, disbale also the 2nd one
  if (_ChannelMode[channel - 1] == TIMER_INPUT_FREQ_DUTY_MEASUREMENT) {
    // Identify and configure 2nd associated channel
    timAssociatedInputChannel = getAssociatedChannel(channel);
    __HAL_TIM_DISABLE_IT(&(_timerObj.handle), getIT(timAssociatedInputChannel));
    LL_TIM_CC_DisableChannel(_timerObj.handle.Instance, getLLChannel(timAssociatedInputChannel));
  }
}

/**
  * @brief  Start or resume HardwareTimer: all channels are resumed, interrupts are enabled if necessary
  * @param  None
  * @retval None
  */
void HardwareTimer::resume(void)
{
  // Clear flag and ennable IT
  if (callbacks[0]) {
    __HAL_TIM_CLEAR_FLAG(&(_timerObj.handle), TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE_IT(&(_timerObj.handle), TIM_IT_UPDATE);

    // Start timer in Time base mode. Required when there is no channel used but only update interrupt.
    HAL_TIM_Base_Start(&(_timerObj.handle));
  }

  // Resume all channels
  resumeChannel(1);
  resumeChannel(2);
  resumeChannel(3);
  resumeChannel(4);
}

/**
  * @brief  Convert arduino channel into HAL channel
  * @param  Arduino channel [1..4]
  * @retval HAL channel. return -1 if arduino channel is invalid
  */
int HardwareTimer::getChannel(uint32_t channel)
{
  uint32_t return_value;

  switch (channel) {
    case 1:
      return_value = TIM_CHANNEL_1;
      break;
    case 2:
      return_value = TIM_CHANNEL_2;
      break;
    case 3:
      return_value = TIM_CHANNEL_3;
      break;
    case 4:
      return_value = TIM_CHANNEL_4;
      break;
    default:
      return_value = -1;
  }
  return return_value;
}

/**
  * @brief  Convert arduino channel into LL channel
  * @param  Arduino channel [1..4]
  * @retval LL channel. return -1 if arduino channel is invalid
  */
int HardwareTimer::getLLChannel(uint32_t channel)
{
  uint32_t return_value;
#if defined(TIM_CCER_CC1NE)
  if (isComplementaryChannel[channel - 1]) {
    // Complementary channel
    switch (channel) {
      case 1:
        return_value = LL_TIM_CHANNEL_CH1N;
        break;
      case 2:
        return_value = LL_TIM_CHANNEL_CH2N;
        break;
      case 3:
        return_value = LL_TIM_CHANNEL_CH3N;
        break;
#if defined(LL_TIM_CHANNEL_CH4N)
      case 4:
        return_value = LL_TIM_CHANNEL_CH4N;
        break;
#endif
      default:
        return_value = -1;
    }
  } else
#endif
  {
    // Regular channel not complementary
    switch (channel) {
      case 1:
        return_value = LL_TIM_CHANNEL_CH1;
        break;
      case 2:
        return_value = LL_TIM_CHANNEL_CH2;
        break;
      case 3:
        return_value = LL_TIM_CHANNEL_CH3;
        break;
      case 4:
        return_value = LL_TIM_CHANNEL_CH4;
        break;
      default:
        return_value = -1;
    }
  }
  return return_value;
}

/**
  * @brief  Convert arduino channel into HAL Interrupt ID
  * @param  Arduino channel [1..4]
  * @retval HAL channel. return -1 if arduino channel is invalid
  */
int HardwareTimer::getIT(uint32_t channel)
{
  uint32_t return_value;

  switch (channel) {
    case 1:
      return_value = TIM_IT_CC1;
      break;
    case 2:
      return_value = TIM_IT_CC2;
      break;
    case 3:
      return_value = TIM_IT_CC3;
      break;
    case 4:
      return_value = TIM_IT_CC4;
      break;
    default:
      return_value = -1;
  }
  return return_value;
}

/**
  * @brief  Get input associated channel
  *         Channel 1 and 2 are associated; channel 3 and 4 are associated
  * @param  Arduino channel [1..4]
  * @retval HAL channel. return -1 if arduino channel is invalid
  */
int HardwareTimer::getAssociatedChannel(uint32_t channel)
{
  int timAssociatedInputChannel = -1;
  switch (channel) {
    case 1:
      timAssociatedInputChannel = 2;
      break;
    case 2:
      timAssociatedInputChannel = 1;
      break;
    case 3:
      timAssociatedInputChannel = 4;
      break;
    case 4:
      timAssociatedInputChannel = 3;
      break;
    default:
      break;
  }
  return timAssociatedInputChannel;
}

/**
  * @brief  Configure specified channel and resume/start timer
  * @param  Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::resumeChannel(uint32_t channel)
{
  int timChannel = getChannel(channel);
  int timAssociatedInputChannel;
  if (timChannel == -1) {
    Error_Handler();
  }

  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  int LLChannel = getLLChannel(channel);
  if (LLChannel == -1) {
    Error_Handler();
  }

  // Clear flag and enable IT
  if (callbacks[channel]) {
    __HAL_TIM_CLEAR_FLAG(&(_timerObj.handle), interrupt);
    __HAL_TIM_ENABLE_IT(&(_timerObj.handle), interrupt);
  }

  switch (_ChannelMode[channel - 1]) {
    case TIMER_OUTPUT_COMPARE_PWM1:
    case TIMER_OUTPUT_COMPARE_PWM2: {
#if defined(TIM_CCER_CC1NE)
        if (isComplementaryChannel[channel - 1]) {
          HAL_TIMEx_PWMN_Start(&(_timerObj.handle), timChannel);
        } else
#endif
        {
          HAL_TIM_PWM_Start(&(_timerObj.handle), timChannel);
        }
      }
      break;
    case TIMER_OUTPUT_COMPARE:
    case TIMER_OUTPUT_COMPARE_ACTIVE:
    case TIMER_OUTPUT_COMPARE_INACTIVE:
    case TIMER_OUTPUT_COMPARE_TOGGLE:
    case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
    case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE: {
#if defined(TIM_CCER_CC1NE)
        if (isComplementaryChannel[channel - 1]) {
          HAL_TIMEx_OCN_Start(&(_timerObj.handle), timChannel);
        } else
#endif
        {
          HAL_TIM_OC_Start(&(_timerObj.handle), timChannel);
        }
      }
      break;
    case TIMER_INPUT_FREQ_DUTY_MEASUREMENT: {
        HAL_TIM_IC_Start(&(_timerObj.handle), timChannel);

        // Enable 2nd associated channel
        timAssociatedInputChannel = getAssociatedChannel(channel);
        LL_TIM_CC_EnableChannel(_timerObj.handle.Instance, getLLChannel(timAssociatedInputChannel));
        if (callbacks[channel]) {
          __HAL_TIM_CLEAR_FLAG(&(_timerObj.handle), getIT(timAssociatedInputChannel));
          __HAL_TIM_ENABLE_IT(&(_timerObj.handle), getIT(timAssociatedInputChannel));
        }
      }
      break;
    case TIMER_INPUT_CAPTURE_RISING:
    case TIMER_INPUT_CAPTURE_FALLING:
    case TIMER_INPUT_CAPTURE_BOTHEDGE: {
        HAL_TIM_IC_Start(&(_timerObj.handle), timChannel);
      }
      break;
    case TIMER_NOT_USED:
    default :
      break;
  }
}

/**
  * @brief  Retrieve prescaler from hardware register
  * @param  None
  * @retval prescaler factor
  */
uint32_t HardwareTimer::getPrescaleFactor()
{
  // Hardware register correspond to prescaler-1. Example PSC register value 0 means divided by 1
  return (LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1);
}

/**
  * @brief  Configure hardwareTimer prescaler
  * @param  prescaler factor
  * @retval None
  */
void HardwareTimer::setPrescaleFactor(uint32_t prescaler)
{
  // Hardware register correspond to prescaler-1. Example PSC register value 0 means divided by 1
  LL_TIM_SetPrescaler(_timerObj.handle.Instance, prescaler - 1);
}

/**
  * @brief  Retrieve overflow (rollover) value from hardware register
  * @param  format of returned value. If ommited default format is Tick
  * @retval overflow depending on format value:
  *           TICK_FORMAT:     return number of tick for overflow
  *           MICROSEC_FORMAT: return number of microsecondes for overflow
  *           HERTZ_FORMAT:    return frequency in hertz for overflow
  */
uint32_t HardwareTimer::getOverflow(TimerFormat_t format)
{
  // Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  uint32_t ARR_RegisterValue = LL_TIM_GetAutoReload(_timerObj.handle.Instance);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1;
  uint32_t return_value;
  switch (format) {
    case MICROSEC_FORMAT:
      return_value = (uint32_t)(((ARR_RegisterValue + 1) * Prescalerfactor * 1000000.0) / getTimerClkFreq());
      break;
    case HERTZ_FORMAT:
      return_value = (uint32_t)(getTimerClkFreq() / ((ARR_RegisterValue + 1) * Prescalerfactor));
      break;
    case TICK_FORMAT:
    default :
      return_value = ARR_RegisterValue + 1;
      break;
  }
  return return_value;
}

/**
  * @brief  Set overflow (rollover)
  *
  *         Note that by default, the new value will not be applied
  *         immediately, but become effective at the next update event
  *         (usually the next timer overflow). See setPreloadEnable()
  *         for controlling this behaviour.
  * @param  overflow: depend on format parameter
  * @param  format of overflow parameter. If ommited default format is Tick
  *           TICK_FORMAT:     overflow is the number of tick for overflow
  *           MICROSEC_FORMAT: overflow is the number of microsecondes for overflow
  *           HERTZ_FORMAT:    overflow is the frequency in hertz for overflow
  * @retval None
  */
void HardwareTimer::setOverflow(uint32_t overflow, TimerFormat_t format)
{
  uint32_t ARR_RegisterValue;
  uint32_t PeriodTicks;
  uint32_t Prescalerfactor;
  uint32_t period_cyc;
  // Remark: Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  switch (format) {
    case MICROSEC_FORMAT:
      period_cyc = overflow * (getTimerClkFreq() / 1000000);
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      LL_TIM_SetPrescaler(_timerObj.handle.Instance, Prescalerfactor - 1);
      PeriodTicks = period_cyc / Prescalerfactor;
      break;
    case HERTZ_FORMAT:
      period_cyc = getTimerClkFreq() / overflow;
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      LL_TIM_SetPrescaler(_timerObj.handle.Instance, Prescalerfactor - 1);
      PeriodTicks = period_cyc / Prescalerfactor;
      break;
    case TICK_FORMAT:
    default :
      PeriodTicks = overflow;
      break;
  }

  if (PeriodTicks > 0) {
    // The register specifies the maximum value, so the period is really one tick longer
    ARR_RegisterValue = PeriodTicks - 1;
  } else {
    // But do not underflow in case a zero period was given somehow.
    ARR_RegisterValue = 0;
  }
  __HAL_TIM_SET_AUTORELOAD(&_timerObj.handle, ARR_RegisterValue);
}

/**
  * @brief  Retreive timer counter value
  * @param  format of returned value. If ommited default format is Tick
  * @retval overflow depending on format value:
  *           TICK_FORMAT:     return number of tick for counter
  *           MICROSEC_FORMAT: return number of microsecondes for counter
  *           HERTZ_FORMAT:    return frequency in hertz for counter
  */
uint32_t HardwareTimer::getCount(TimerFormat_t format)
{
  uint32_t CNT_RegisterValue = LL_TIM_GetCounter(_timerObj.handle.Instance);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1;
  uint32_t return_value;
  switch (format) {
    case MICROSEC_FORMAT:
      return_value = (uint32_t)((CNT_RegisterValue * Prescalerfactor * 1000000.0) / getTimerClkFreq());
      break;
    case HERTZ_FORMAT:
      return_value = (uint32_t)(getTimerClkFreq() / (CNT_RegisterValue  * Prescalerfactor));
      break;
    case TICK_FORMAT:
    default :
      return_value = CNT_RegisterValue;
      break;
  }
  return return_value;
}

/**
  * @brief  Set timer counter value
  * @param  counter: depend on format parameter
  * @param  format of overflow parameter. If ommited default format is Tick
  *           TICK_FORMAT:     counter is the number of tick
  *           MICROSEC_FORMAT: counter is the number of microsecondes
  *           HERTZ_FORMAT:    counter is the frequency in hertz
  * @retval None
  */
void HardwareTimer::setCount(uint32_t counter, TimerFormat_t format)
{
  uint32_t CNT_RegisterValue;
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1;
  switch (format) {
    case MICROSEC_FORMAT:
      CNT_RegisterValue = ((counter * (getTimerClkFreq() / 1000000)) / Prescalerfactor);
      break;
    case HERTZ_FORMAT:
      CNT_RegisterValue = (uint32_t)(getTimerClkFreq() / (counter * Prescalerfactor));
      break;
    case TICK_FORMAT:
    default :
      CNT_RegisterValue = counter;
      break;
  }
  __HAL_TIM_SET_COUNTER(&(_timerObj.handle), CNT_RegisterValue);
}

/**
  * @brief  Set channel mode
  * @param  channel: Arduino channel [1..4]
  * @param  mode: mode configuration for the channel (see TimerModes_t)
  * @param  pin: Arduino pin number, ex: D1, 1 or PA1
  * @retval None
  */
void HardwareTimer::setMode(uint32_t channel, TimerModes_t mode, uint32_t pin)
{
  setMode(channel, mode, digitalPinToPinName(pin));
}

/**
  * @brief  Set channel mode
  * @param  channel: Arduino channel [1..4]
  * @param  mode: mode configuration for the channel (see TimerModes_t)
  * @param  pin: pin name, ex: PB_0
  * @retval None
  */
void HardwareTimer::setMode(uint32_t channel, TimerModes_t mode, PinName pin)
{
  int timChannel = getChannel(channel);
  int timAssociatedInputChannel;
  TIM_OC_InitTypeDef channelOC;
  TIM_IC_InitTypeDef channelIC;

  if (timChannel == -1) {
    Error_Handler();
  }

  // Save channel selected mode to object attribute
  _ChannelMode[channel - 1] = mode;

  /* Configure some default values. Maybe overwritten later */
  channelOC.OCMode = TIMER_NOT_USED;
  channelOC.Pulse = __HAL_TIM_GET_COMPARE(&(_timerObj.handle), timChannel);  // keep same value already written in hardware <register
  channelOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  channelOC.OCFastMode = TIM_OCFAST_DISABLE;
#if defined(TIM_CR2_OIS1)
  channelOC.OCIdleState = TIM_OCIDLESTATE_RESET;
#endif
#if defined(TIM_CCER_CC1NE)
  channelOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
#if defined(TIM_CR2_OIS1)
  channelOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
#endif
#endif
  channelIC.ICPolarity = TIMER_NOT_USED;
  channelIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  channelIC.ICPrescaler = TIM_ICPSC_DIV1;
  channelIC.ICFilter = 0;

  switch (mode) {
    case TIMER_DISABLED:
      channelOC.OCMode = TIM_OCMODE_TIMING;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE:
      channelOC.OCMode = TIM_OCMODE_TIMING;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_ACTIVE:
      channelOC.OCMode = TIM_OCMODE_ACTIVE;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_INACTIVE:
      channelOC.OCMode = TIM_OCMODE_INACTIVE;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_TOGGLE:
      channelOC.OCMode = TIM_OCMODE_TOGGLE;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_PWM1:
      channelOC.OCMode = TIM_OCMODE_PWM1;
      HAL_TIM_PWM_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_PWM2:
      channelOC.OCMode = TIM_OCMODE_PWM2;
      HAL_TIM_PWM_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
      channelOC.OCMode = TIM_OCMODE_FORCED_ACTIVE;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE:
      channelOC.OCMode = TIM_OCMODE_FORCED_INACTIVE;
      HAL_TIM_OC_ConfigChannel(&(_timerObj.handle), &channelOC, timChannel);
      break;
    case TIMER_INPUT_CAPTURE_RISING:
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
      // channelIC[0].ICSelection = TIM_ICSELECTION_DIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, timChannel);
      break;
    case TIMER_INPUT_CAPTURE_FALLING:
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
      // _channelIC[0].ICSelection = TIM_ICSELECTION_DIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, timChannel);
      break;
    case TIMER_INPUT_CAPTURE_BOTHEDGE:
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, timChannel);
      break;
    case TIMER_INPUT_FREQ_DUTY_MEASUREMENT:
      // Configure 1st channel
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
      channelIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, timChannel);

      // Identify and configure 2nd associated channel
      timAssociatedInputChannel = getAssociatedChannel(channel);
      _ChannelMode[timAssociatedInputChannel - 1] = mode;
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
      channelIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, getChannel(timAssociatedInputChannel));
      break;
    default:
      break;
  }

  if (pin != NC) {
    if ((int)get_pwm_channel(pin) == timChannel) {
      /* Configure PWM GPIO pins */
      pinmap_pinout(pin, PinMap_PWM);
#if defined(STM32F1xx)
      if ((mode == TIMER_INPUT_CAPTURE_RISING) || (mode == TIMER_INPUT_CAPTURE_FALLING) \
          || (mode == TIMER_INPUT_CAPTURE_BOTHEDGE) || (mode == TIMER_INPUT_FREQ_DUTY_MEASUREMENT)) {
        // on F1 family, input alternate function must configure GPIO in input mode
        pinMode(pinNametoDigitalPin(pin), INPUT);
      }
#endif
    } else {
      // Pin doesn't match with timer output channels
      Error_Handler();
    }

#if defined(TIM_CCER_CC1NE)
    isComplementaryChannel[channel - 1] = STM_PIN_INVERTED(pinmap_function(pin, PinMap_PWM));
#endif
  }
}

/**
  * @brief  Retrieves channel mode configured
  * @param  channel: Arduino channel [1..4]
  * @retval returns configured mode
  */
TimerModes_t HardwareTimer::getMode(uint32_t channel)
{
  if ((1 <= channel) && (channel <= TIMER_CHANNELS)) {
    return _ChannelMode[channel - 1];
  } else {
    return TIMER_DISABLED;
  }
}

/**
  * @brief  Enable or disable preloading for overflow value
  *         When disabled, changes to the overflow value take effect
  *         immediately. When enabled (the default), the value takes
  *         effect only at the next update event (typically the next
  *         overflow).
  *
  *         Note that the capture/compare register has its own preload
  *         enable bit, which is independent and enabled in PWM modes
  *         and disabled otherwise. If you need more control of that
  *         bit, you can use the HAL functions directly.
  * @param  value: true to enable preloading, false to disable
  * @retval None
  */
void HardwareTimer::setPreloadEnable(bool value)
{
  if (value) {
    LL_TIM_EnableARRPreload(_timerObj.handle.Instance);
  } else {
    LL_TIM_DisableARRPreload(_timerObj.handle.Instance);
  }
}

/**
  * @brief  Set channel Capture/Compare register
  * @param  channel: Arduino channel [1..4]
  * @param  compare: compare value depending on format
  * @param  format of compare parameter. If ommited default format is Tick
  *           TICK_FORMAT:     compare is the number of tick
  *           MICROSEC_FORMAT: compare is the number of microsecondes
  *           HERTZ_FORMAT:    compare is the frequency in hertz
  * @retval None
  */
void HardwareTimer::setCaptureCompare(uint32_t channel, uint32_t compare, TimerCompareFormat_t format)
{
  int timChannel = getChannel(channel);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1;
  uint32_t CCR_RegisterValue;

  if (timChannel == -1) {
    Error_Handler();
  }

  switch (format) {
    case MICROSEC_COMPARE_FORMAT:
      CCR_RegisterValue = ((compare * (getTimerClkFreq() / 1000000)) / Prescalerfactor);
      break;
    case HERTZ_COMPARE_FORMAT:
      CCR_RegisterValue = getTimerClkFreq() / (compare * Prescalerfactor);
      break;
    // As per Reference Manual PWM reach 100% with CCRx value strictly greater than ARR (So ARR+1 in our case)
    case PERCENT_COMPARE_FORMAT:
      CCR_RegisterValue = ((__HAL_TIM_GET_AUTORELOAD(&(_timerObj.handle)) + 1) * compare) / 100;
      break;
    case RESOLUTION_1B_COMPARE_FORMAT:
    case RESOLUTION_2B_COMPARE_FORMAT:
    case RESOLUTION_3B_COMPARE_FORMAT:
    case RESOLUTION_4B_COMPARE_FORMAT:
    case RESOLUTION_5B_COMPARE_FORMAT:
    case RESOLUTION_6B_COMPARE_FORMAT:
    case RESOLUTION_7B_COMPARE_FORMAT:
    case RESOLUTION_8B_COMPARE_FORMAT:
    case RESOLUTION_9B_COMPARE_FORMAT:
    case RESOLUTION_10B_COMPARE_FORMAT:
    case RESOLUTION_11B_COMPARE_FORMAT:
    case RESOLUTION_12B_COMPARE_FORMAT:
    case RESOLUTION_13B_COMPARE_FORMAT:
    case RESOLUTION_14B_COMPARE_FORMAT:
    case RESOLUTION_15B_COMPARE_FORMAT:
    case RESOLUTION_16B_COMPARE_FORMAT:
      CCR_RegisterValue = ((__HAL_TIM_GET_AUTORELOAD(&(_timerObj.handle)) + 1) * compare) / ((1 << format) - 1) ;
      break;
    case TICK_COMPARE_FORMAT:
    default :
      CCR_RegisterValue = compare;
      break;
  }

  // Special case when ARR is set to the max value, it is not possible to set CCRx to ARR+1 to reach 100%
  // Then set CCRx to max value. PWM is then 1/0xFFFF = 99.998..%
  if ((__HAL_TIM_GET_AUTORELOAD(&(_timerObj.handle)) == MAX_RELOAD)
      && (CCR_RegisterValue == MAX_RELOAD + 1)) {
    CCR_RegisterValue = MAX_RELOAD;
  }

  __HAL_TIM_SET_COMPARE(&(_timerObj.handle), timChannel, CCR_RegisterValue);
}

/**
  * @brief  Retrieve Capture/Compare value
  * @param  channel: Arduino channel [1..4]
  * @param  format of return value. If ommited default format is Tick
  *           TICK_FORMAT:     return value is the number of tick for Capture/Compare value
  *           MICROSEC_FORMAT: return value is the number of microsecondes for Capture/Compare value
  *           HERTZ_FORMAT:    return value is the frequency in hertz for Capture/Compare value
  * @retval None
  */
uint32_t HardwareTimer::getCaptureCompare(uint32_t channel,  TimerCompareFormat_t format)
{
  int timChannel = getChannel(channel);
  uint32_t CCR_RegisterValue = __HAL_TIM_GET_COMPARE(&(_timerObj.handle), timChannel);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.handle.Instance) + 1;
  uint32_t return_value;

  if (timChannel == -1) {
    Error_Handler();
  }

  switch (format) {
    case MICROSEC_COMPARE_FORMAT:
      return_value = (uint32_t)((CCR_RegisterValue * Prescalerfactor * 1000000.0) / getTimerClkFreq());
      break;
    case HERTZ_COMPARE_FORMAT:
      return_value = (uint32_t)(getTimerClkFreq() / (CCR_RegisterValue  * Prescalerfactor));
      break;
    case PERCENT_COMPARE_FORMAT:
      return_value = (CCR_RegisterValue * 100) / __HAL_TIM_GET_AUTORELOAD(&(_timerObj.handle));
      break;
    case RESOLUTION_1B_COMPARE_FORMAT:
    case RESOLUTION_2B_COMPARE_FORMAT:
    case RESOLUTION_3B_COMPARE_FORMAT:
    case RESOLUTION_4B_COMPARE_FORMAT:
    case RESOLUTION_5B_COMPARE_FORMAT:
    case RESOLUTION_6B_COMPARE_FORMAT:
    case RESOLUTION_7B_COMPARE_FORMAT:
    case RESOLUTION_8B_COMPARE_FORMAT:
    case RESOLUTION_9B_COMPARE_FORMAT:
    case RESOLUTION_10B_COMPARE_FORMAT:
    case RESOLUTION_11B_COMPARE_FORMAT:
    case RESOLUTION_12B_COMPARE_FORMAT:
    case RESOLUTION_13B_COMPARE_FORMAT:
    case RESOLUTION_14B_COMPARE_FORMAT:
    case RESOLUTION_15B_COMPARE_FORMAT:
    case RESOLUTION_16B_COMPARE_FORMAT:
      return_value = (CCR_RegisterValue * ((1 << format) - 1)) / __HAL_TIM_GET_AUTORELOAD(&(_timerObj.handle));
      break;
    case TICK_COMPARE_FORMAT:
    default :
      return_value = CCR_RegisterValue;
      break;
  }
  return return_value;
}

/**
  * @param  channel: Arduino channel [1..4]
  * @param  pin: Arduino pin number, ex D1, 1 or PA1
  * @param  frequency: PWM frequency expessed in hertz
  * @param  dutycycle: PWM dutycycle expressed in percentage
  * @param  format of return value. If ommited default format is Tick
  *           TICK_FORMAT:     return value is the number of tick for Capture/Compare value
  *           MICROSEC_FORMAT: return value is the number of microsecondes for Capture/Compare value
  *           HERTZ_FORMAT:    return value is the frequency in hertz for Capture/Compare value
  * @retval None
  */
void HardwareTimer::setPWM(uint32_t channel, uint32_t pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback, callback_function_t CompareCallback)
{
  setPWM(channel, digitalPinToPinName(pin), frequency, dutycycle, PeriodCallback, CompareCallback);
}

/**
  * @brief  All in one function to configure PWM
  * @param  channel: Arduino channel [1..4]
  * @param  pin: pin name, ex PB_0
  * @param  frequency: PWM frequency expessed in hertz
  * @param  dutycycle: PWM dutycycle expressed in percentage
  * @param  format of return value. If ommited default format is Tick
  *           TICK_FORMAT:     return value is the number of tick for Capture/Compare value
  *           MICROSEC_FORMAT: return value is the number of microsecondes for Capture/Compare value
  *           HERTZ_FORMAT:    return value is the frequency in hertz for Capture/Compare value
  * @retval None
  */
void HardwareTimer::setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback, callback_function_t CompareCallback)
{
  setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
  setOverflow(frequency, HERTZ_FORMAT);
  setCaptureCompare(channel, dutycycle, PERCENT_COMPARE_FORMAT);
  if (PeriodCallback) {
    attachInterrupt(PeriodCallback);
  }
  if (CompareCallback) {
    attachInterrupt(channel, CompareCallback);
  }
  resume();
}

/**
  * @brief  Set the priority of the interrupt
  * @note   Must be call before resume()
  * @param  preemptPriority: the pre-emption priority for the IRQn channel
  * @param  subPriority: the subpriority level for the IRQ channel.
  * @retval None
  */
void HardwareTimer::setInterruptPriority(uint32_t preemptPriority, uint32_t subPriority)
{
  // Set Update interrupt priority for immediate use
  HAL_NVIC_SetPriority(getTimerUpIrq(_timerObj.handle.Instance), preemptPriority, subPriority);

  // Set Capture/Compare interrupt priority if timer provides a unique IRQ
  if (getTimerCCIrq(_timerObj.handle.Instance) != getTimerUpIrq(_timerObj.handle.Instance)) {
    HAL_NVIC_SetPriority(getTimerCCIrq(_timerObj.handle.Instance), preemptPriority, subPriority);
  }

  // Store priority for use if timer is re-initialized
  _timerObj.preemptPriority = preemptPriority;
  _timerObj.subPriority = subPriority;
}

/**
  * @brief  Attach interrupt callback on update (rollover) event
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(callback_function_t callback)
{
  if (callbacks[0]) {
    // Callback previously configured : do not clear neither enable IT, it is just a change of callback
    callbacks[0] = callback;
  } else {
    callbacks[0] = callback;
    if (callback) {
      // Clear flag before enabling IT
      __HAL_TIM_CLEAR_FLAG(&(_timerObj.handle), TIM_FLAG_UPDATE);
      // Enable update interrupt only if callback is valid
      __HAL_TIM_ENABLE_IT(&(_timerObj.handle), TIM_IT_UPDATE);
    }
  }
}

/**
  * @brief  Dettach interrupt callback on update (rollover) event
  * @retval None
  */
void HardwareTimer::detachInterrupt()
{
  // Disable update interrupt and clear callback
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), TIM_IT_UPDATE); // disables the interrupt call to save cpu cycles for useless context switching
  callbacks[0] = NULL;
}

/**
  * @brief  Attach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(uint32_t channel, callback_function_t callback)
{
  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }
  if (callbacks[channel]) {
    // Callback previously configured : do not clear neither enable IT, it is just a change of callback
    callbacks[channel] = callback;
  } else {
    callbacks[channel] = callback;
    if (callback) {
      // Clear flag before enabling IT
      __HAL_TIM_CLEAR_FLAG(&(_timerObj.handle), interrupt);
      // Enable interrupt corresponding to channel, only if callback is valid
      __HAL_TIM_ENABLE_IT(&(_timerObj.handle), interrupt);
    }
  }
}

/**
  * @brief  Dettach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::detachInterrupt(uint32_t channel)
{
  int interrupt = getIT(channel);
  if (interrupt == -1) {
    Error_Handler();
  }

  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }

  // Disable interrupt corresponding to channel and clear callback
  __HAL_TIM_DISABLE_IT(&(_timerObj.handle), interrupt);
  callbacks[channel] = NULL;
}

/**
  * @brief  Checks if there's an interrupt callback attached on Rollover event
  * @retval returns true if a timer rollover interrupt has already been set
  */
bool HardwareTimer::hasInterrupt()
{
  return callbacks[0] != NULL;
}

/**
  * @brief  Checks if there's an interrupt callback attached on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval returns true if a channel compare match interrupt has already been set
  */
bool HardwareTimer::hasInterrupt(uint32_t channel)
{
  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }
  return callbacks[channel] != NULL;
}

/**
  * @brief  Generate an update event to force all registers (Autoreload, prescaler, compare) to be taken into account
  * @note   Refresh() can only be called after a 1st call to resume() to be sure timer is initialised.
  *         It is usefull while timer is running after some registers update
  * @retval None
  */
void HardwareTimer::refresh()
{
  HAL_TIM_GenerateEvent(&(_timerObj.handle), TIM_EVENTSOURCE_UPDATE);
}

/**
  * @brief  Return the timer object handle object for more advanced setup
  * @note   Using this function and editing the Timer handle is at own risk! No support will
  *         be provided whatsoever if the HardwareTimer does not work as expected when editing
  *         the handle using the HAL functionality or other custom coding.
  * @retval TIM_HandleTypeDef address
  */
TIM_HandleTypeDef *HardwareTimer::getHandle()
{
  return &_timerObj.handle;
}

/**
  * @brief  Generic Update (rollover) callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::updateCallback(TIM_HandleTypeDef *htim)
{
  if (!htim) {
    Error_Handler();
  }

  timerObj_t *obj = get_timer_obj(htim);
  HardwareTimer *HT = (HardwareTimer *)(obj->__this);

  if (HT->callbacks[0]) {
    HT->callbacks[0]();
  }
}

/**
  * @brief  Generic Caputre and Compare callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::captureCompareCallback(TIM_HandleTypeDef *htim)
{
  if (!htim) {
    Error_Handler();
  }
  uint32_t channel = htim->Channel;

  switch (htim->Channel) {
    case HAL_TIM_ACTIVE_CHANNEL_1: {
        channel = 1;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_2: {
        channel = 2;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_3: {
        channel = 3;
        break;
      }
    case HAL_TIM_ACTIVE_CHANNEL_4: {
        channel = 4;
        break;
      }
    default:
      return;
  }

  timerObj_t *obj = get_timer_obj(htim);
  HardwareTimer *HT = (HardwareTimer *)(obj->__this);

  if (HT->callbacks[channel]) {
    HT->callbacks[channel]();
  }
}

/**
  * @brief  HardwareTimer destructor
  * @retval None
  */
HardwareTimer::~HardwareTimer()
{
  uint32_t index = get_timer_index(_timerObj.handle.Instance);
  disableTimerClock(&(_timerObj.handle));
  HardwareTimer_Handle[index] = NULL;
  _timerObj.__this = NULL;
}

/**
  * @brief  return timer index from timer handle
  * @param  htim : one of the defined timer
  * @retval None
  */
timer_index_t get_timer_index(TIM_TypeDef *instance)
{
  timer_index_t index = UNKNOWN_TIMER;

#if defined(TIM1_BASE)
  if (instance == TIM1) {
    index = TIMER1_INDEX;
  }
#endif
#if defined(TIM2_BASE)
  if (instance == TIM2) {
    index = TIMER2_INDEX;
  }
#endif
#if defined(TIM3_BASE)
  if (instance == TIM3) {
    index = TIMER3_INDEX;
  }
#endif
#if defined(TIM4_BASE)
  if (instance == TIM4) {
    index = TIMER4_INDEX;
  }
#endif
#if defined(TIM5_BASE)
  if (instance == TIM5) {
    index = TIMER5_INDEX;
  }
#endif
#if defined(TIM6_BASE)
  if (instance == TIM6) {
    index = TIMER6_INDEX;
  }
#endif
#if defined(TIM7_BASE)
  if (instance == TIM7) {
    index = TIMER7_INDEX;
  }
#endif
#if defined(TIM8_BASE)
  if (instance == TIM8) {
    index = TIMER8_INDEX;
  }
#endif
#if defined(TIM9_BASE)
  if (instance == TIM9) {
    index = TIMER9_INDEX;
  }
#endif
#if defined(TIM10_BASE)
  if (instance == TIM10) {
    index = TIMER10_INDEX;
  }
#endif
#if defined(TIM11_BASE)
  if (instance == TIM11) {
    index = TIMER11_INDEX;
  }
#endif
#if defined(TIM12_BASE)
  if (instance == TIM12) {
    index = TIMER12_INDEX;
  }
#endif
#if defined(TIM13_BASE)
  if (instance == TIM13) {
    index = TIMER13_INDEX;
  }
#endif
#if defined(TIM14_BASE)
  if (instance == TIM14) {
    index = TIMER14_INDEX;
  }
#endif
#if defined(TIM15_BASE)
  if (instance == TIM15) {
    index = TIMER15_INDEX;
  }
#endif
#if defined(TIM16_BASE)
  if (instance == TIM16) {
    index = TIMER16_INDEX;
  }
#endif
#if defined(TIM17_BASE)
  if (instance == TIM17) {
    index = TIMER17_INDEX;
  }
#endif
#if defined(TIM18_BASE)
  if (instance == TIM18) {
    index = TIMER18_INDEX;
  }
#endif
#if defined(TIM19_BASE)
  if (instance == TIM19) {
    index = TIMER19_INDEX;
  }
#endif
#if defined(TIM20_BASE)
  if (instance == TIM20) {
    index = TIMER20_INDEX;
  }
#endif
#if defined(TIM21_BASE)
  if (instance == TIM21) {
    index = TIMER21_INDEX;
  }
#endif
#if defined(TIM22_BASE)
  if (instance == TIM22) {
    index = TIMER2_INDEX;
  }
#endif
  return index;
}

/**
  * @brief  This function return the timer clock frequency.
  * @param  tim: timer instance
  * @retval frequency in Hz
  */
uint32_t HardwareTimer::getTimerClkFreq()
{
#if defined(STM32MP1xx)
  uint8_t timerClkSrc = getTimerClkSrc(_timerObj.handle.Instance);
  uint64_t clkSelection = timerClkSrc == 1 ? RCC_PERIPHCLK_TIMG1 : RCC_PERIPHCLK_TIMG2;
  return HAL_RCCEx_GetPeriphCLKFreq(clkSelection);
#else
  RCC_ClkInitTypeDef    clkconfig = {};
  uint32_t              pFLatency = 0U;
  uint32_t              uwTimclock = 0U, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  switch (getTimerClkSrc(_timerObj.handle.Instance)) {
    case 1:
      uwAPBxPrescaler = clkconfig.APB1CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK1Freq();
      break;
#if !defined(STM32F0xx) && !defined(STM32G0xx)
    case 2:
      uwAPBxPrescaler = clkconfig.APB2CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK2Freq();
      break;
#endif
    default:
    case 0: // Unknown timer clock source
      Error_Handler();
      break;
  }

#if defined(STM32H7xx)
  /* When TIMPRE bit of the RCC_CFGR register is reset,
   *   if APBx prescaler is 1 or 2 then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 2x PCLKx.
   * When TIMPRE bit in the RCC_CFGR register is set,
   *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 4x PCLKx
   */
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED) {
    switch (uwAPBxPrescaler) {
      default:
      case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
      case RCC_APB1_DIV4:
      /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
      case RCC_APB2_DIV4:
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock *= 4;
        break;
    }
  } else {
    switch (uwAPBxPrescaler) {
      default:
      case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
      /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
        // uwTimclock*=1;
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV4:
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV4:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock *= 2;
        break;
    }
  }
#else
  /* When TIMPRE bit of the RCC_DCKCFGR register is reset,
   *   if APBx prescaler is 1, then TIMxCLK = PCLKx,
   *   otherwise TIMxCLK = 2x PCLKx.
   * When TIMPRE bit in the RCC_DCKCFGR register is set,
   *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 4x PCLKx
   */
#if defined(STM32F4xx) || defined(STM32F7xx)
#if !defined(STM32F405xx) && !defined(STM32F415xx) &&\
    !defined(STM32F407xx) && !defined(STM32F417xx)
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED)
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock *= 4;
        break;
    } else
#endif
#endif
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
        // uwTimclock*=1;
        break;
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock *= 2;
        break;
    }
#endif /* STM32H7xx */
  return uwTimclock;
#endif /* STM32MP1xx */
}

/**
  * @brief  This function will reset the timer
  * @param  obj : Hardware timer instance ex: Timer6, ...
  * @retval None
  */
void HardwareTimer::timerHandleDeinit()
{
  HAL_TIM_Base_Stop_IT(&(_timerObj.handle));
  HAL_TIM_Base_DeInit(&(_timerObj.handle));
}

/******************************************************************************/
/*                            TIMx IRQ HANDLER                                */
/******************************************************************************/
extern "C" {

  void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
  {
    HardwareTimer::captureCompareCallback(htim);
  }

  void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
  {
    HardwareTimer::captureCompareCallback(htim);
  }

  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  {
    HardwareTimer::updateCallback(htim);
  }

#if defined(TIM1_BASE)
  /**
    * @brief  TIM1 IRQHandler common with TIM10 and TIM16 on some STM32F1xx
    * @param  None
    * @retval None
    */
  void TIM1_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER1_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER1_INDEX]->handle);
    }

#if defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#if defined (TIM10_BASE)
    if (HardwareTimer_Handle[TIMER10_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER10_INDEX]->handle);
    }
#endif
#endif

#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx) || defined(STM32L4xx) || \
    defined(STM32WBxx)
#if defined (TIM16_BASE)
    if (HardwareTimer_Handle[TIMER16_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER16_INDEX]->handle);
    }
#endif
#endif
  }

#if !defined(STM32F3xx)
  void TIM1_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER1_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER1_INDEX]->handle);
    }
  }
#endif // !STM32F3xx
#endif //TIM1_BASE

#if defined(TIM2_BASE)
  /**
    * @brief  TIM2 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM2_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER2_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER2_INDEX]->handle);
    }
  }
#endif //TIM2_BASE

#if defined(TIM3_BASE)
  /**
    * @brief  TIM3 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM3_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER3_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER3_INDEX]->handle);
    }
  }
#endif //TIM3_BASE

#if defined(TIM4_BASE)
  /**
    * @brief  TIM4 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM4_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER4_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER4_INDEX]->handle);
    }
  }
#endif //TIM4_BASE

#if defined(TIM5_BASE)
  /**
    * @brief  TIM5 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM5_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER5_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER5_INDEX]->handle);
    }
  }
#endif //TIM5_BASE

#if defined(TIM6_BASE)
  /**
    * @brief  TIM6 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM6_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER6_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER6_INDEX]->handle);
    }
  }
#endif //TIM6_BASE

#if defined(TIM7_BASE)
  /**
    * @brief  TIM7 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM7_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER7_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER7_INDEX]->handle);
    }
  }
#endif //TIM7_BASE

#if defined(TIM8_BASE)
  /**
    * @brief  TIM8 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM8_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER8_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER8_INDEX]->handle);
    }

#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx) || defined(STM32H7xx)
#if defined(TIMER13_BASE)
    if (HardwareTimer_Handle[TIMER13_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER13_INDEX]->handle);
    }
#endif // TIMER13_BASE
#endif
  }

  void TIM8_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER8_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER8_INDEX]->handle);
    }
  }
#endif //TIM8_BASE

#if defined(TIM9_BASE)
  /**
    * @brief  TIM9 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM9_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER9_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER9_INDEX]->handle);
    }
  }
#endif //TIM9_BASE

#if defined(TIM10_BASE)
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && !defined(STM32F7xx)
  /**
    * @brief  TIM10 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM10_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER10_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER10_INDEX]->handle);
    }
  }
#endif
#endif //TIM10_BASE

#if defined(TIM11_BASE)
  /**
    * @brief  TIM11 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM11_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER11_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER11_INDEX]->handle);
    }
  }
#endif //TIM11_BASE

#if defined(TIM12_BASE)
  /**
    * @brief  TIM12 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM12_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER12_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER12_INDEX]->handle);
    }
  }
#endif //TIM12_BASE

#if defined(TIM13_BASE)
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && !defined(STM32F7xx) && !defined(STM32H7xx)
  /**
    * @brief  TIM13 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM13_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER13_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER13_INDEX]->handle);
    }
  }
#endif
#endif //TIM13_BASE

#if defined(TIM14_BASE)
  /**
    * @brief  TIM14 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM14_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER14_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER14_INDEX]->handle);
    }
  }
#endif //TIM14_BASE

#if defined(TIM15_BASE)
  /**
    * @brief  TIM15 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM15_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER15_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER15_INDEX]->handle);
    }
  }
#endif //TIM15_BASE

#if defined(TIM16_BASE)
#if !defined(STM32F1xx) && !defined(STM32F3xx) && !defined(STM32G4xx) && !defined(STM32L4xx)
  /**
    * @brief  TIM16 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM16_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER16_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER16_INDEX]->handle);
    }
  }
#endif
#endif //TIM16_BASE

#if defined(TIM17_BASE)
  /**
    * @brief  TIM17 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM17_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER17_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER17_INDEX]->handle);
    }
  }
#endif //TIM17_BASE

#if defined(TIM18_BASE)
  /**
    * @brief  TIM18 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM18_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER18_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER18_INDEX]->handle);
    }

#if defined(STM32F3xx)
#if defined (TIM1_BASE)
    if (HardwareTimer_Handle[TIMER1_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER1_INDEX]->handle);
    }
#endif
#endif
  }
#endif //TIM18_BASE

#if defined(TIM19_BASE)
  /**
    * @brief  TIM19 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM19_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER19_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER19_INDEX]->handle);
    }
  }
#endif //TIM19_BASE

#if defined(TIM20_BASE)
  /**
    * @brief  TIM20 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM20_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER20_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER20_INDEX]->handle);
    }
  }

  void TIM20_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER20_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER20_INDEX]->handle);
    }
  }
#endif //TIM20_BASE

#if defined(TIM21_BASE)
  /**
    * @brief  TIM21 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM21_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER21_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER21_INDEX]->handle);
    }
  }
#endif //TIM21_BASE

#if defined(TIM22_BASE)
  /**
    * @brief  TIM22 IRQHandler
    * @param  None
    * @retval None
    */
  void TIM22_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER22_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER22_INDEX]->handle);
    }
  }
#endif //TIM22_BASE
}

#endif // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
