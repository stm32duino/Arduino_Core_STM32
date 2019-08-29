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

#ifdef HAL_TIM_MODULE_ENABLED

/* Private Defines */
#define PIN_NOT_USED 0xFF
#define MAX_RELOAD ((1 << 16) - 1) // Currently even 32b timers are used as 16b to have generic behavior

/* Private Variables */
HardwareTimerObj_t *HardwareTimer_Handle[TIMER_NUM] = {NULL};

IRQn_Type getTimerUpIrq(TIM_TypeDef *tim);
IRQn_Type getTimerCCIrq(TIM_TypeDef *tim);

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

  HardwareTimer_Handle[index] = &_HardwareTimerObj;

  _HardwareTimerObj.handle.Instance = instance;
  _HardwareTimerObj.handle.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
  _HardwareTimerObj.handle.hdma[0] = NULL;
  _HardwareTimerObj.handle.hdma[1] = NULL;
  _HardwareTimerObj.handle.hdma[2] = NULL;
  _HardwareTimerObj.handle.hdma[3] = NULL;
  _HardwareTimerObj.handle.hdma[4] = NULL;
  _HardwareTimerObj.handle.hdma[5] = NULL;
  _HardwareTimerObj.handle.hdma[6] = NULL;
  _HardwareTimerObj.handle.Lock = HAL_UNLOCKED;
  _HardwareTimerObj.handle.State = HAL_TIM_STATE_RESET;

  _HardwareTimerObj.handle.Instance = instance;
  _HardwareTimerObj.__this = (void *)this;

  // Enable Timer clock
  enableTimerClock(&(_HardwareTimerObj.handle));

  // Configure HAL structure for all channels
  for (int i = 0; i < TIMER_CHANNELS; i++) {
    _channelOC[i].OCMode = TIMER_NOT_USED;
    _channelOC[i].OCPolarity = TIM_OCPOLARITY_HIGH;
    _channelOC[i].OCFastMode = TIM_OCFAST_DISABLE;

#if defined(TIM_CR2_OIS1)
    _channelOC[i].OCIdleState = TIM_OCIDLESTATE_RESET;
#endif
#if defined(TIM_CCER_CC1NE)
    _channelOC[i].OCNPolarity = TIM_OCNPOLARITY_HIGH;
#if defined(TIM_CR2_OIS1)
    _channelOC[i].OCNIdleState = TIM_OCNIDLESTATE_RESET;
#endif
#endif
    _channelIC[i].ICPolarity = TIMER_NOT_USED;
    _channelIC[i].ICSelection = TIM_ICSELECTION_DIRECTTI;
    _channelIC[i].ICPrescaler = TIM_ICPSC_DIV1;
    _channelIC[i].ICFilter = 0;

    for (int i = 0; i < TIMER_CHANNELS ; i++) {
      callbacks[i] = NULL;
    }
  }
}

/**
  * @brief  Pause HardwareTimer: stop timer
  * @param  None
  * @retval None
  */
void HardwareTimer::pause()
{
  HAL_TIM_Base_Stop_IT(&(_HardwareTimerObj.handle));
}

/**
  * @brief  Start or resume HardwareTimer: all channels are resumed, interrupts are enabled if necessary
  * @param  None
  * @retval None
  */
void HardwareTimer::resume(void)
{
  _HardwareTimerObj.handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  _HardwareTimerObj.handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
#if defined(TIM_RCR_REP)
  _HardwareTimerObj.handle.Init.RepetitionCounter = 0;
#endif
  _HardwareTimerObj.handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&(_HardwareTimerObj.handle));

  // Start timer with IT if required
  if (callbacks[0] != NULL) {
    HAL_TIM_Base_Start_IT(&(_HardwareTimerObj.handle));
  } else {
    HAL_TIM_Base_Start(&(_HardwareTimerObj.handle));
  }

  resumeChannel(1);
  resumeChannel(2);
  resumeChannel(3);
  resumeChannel(4);
}

/**
  * @brief  Convert arduino  into HAL channel
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
  * @brief  Configure specified channel and resume/start timer
  * @param  Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::resumeChannel(uint32_t channel)
{
  int timChannel = getChannel(channel);
  if (timChannel == -1) {
    Error_Handler();
  }

  if (IS_TIM_PWM_MODE(_channelOC[channel - 1].OCMode)) {
    HAL_TIM_PWM_ConfigChannel(&(_HardwareTimerObj.handle), &_channelOC[channel - 1], timChannel);

    if ((channel < (TIMER_CHANNELS + 1)) && (callbacks[channel] != NULL)) {
      // Only channel 1..4 can have interruption
#if defined(TIM_CCER_CC1NE)
      if (isComplementaryChannel[channel]) {
        HAL_TIMEx_PWMN_Start_IT(&(_HardwareTimerObj.handle), timChannel);
      } else
#endif
      {
        HAL_TIM_PWM_Start_IT(&(_HardwareTimerObj.handle), timChannel);
      }
    } else {
#if defined(TIM_CCER_CC1NE)
      if (isComplementaryChannel[channel]) {
        HAL_TIMEx_PWMN_Start(&(_HardwareTimerObj.handle), timChannel);
      } else
#endif
      {
        HAL_TIM_PWM_Start(&(_HardwareTimerObj.handle), timChannel);
      }
    }
  } else if (IS_TIM_OC_MODE(_channelOC[channel - 1].OCMode)) {
    HAL_TIM_OC_ConfigChannel(&(_HardwareTimerObj.handle), &_channelOC[channel - 1], timChannel);

    if ((channel < (TIMER_CHANNELS + 1)) && (callbacks[channel] != NULL)) {
      // Only channel 1..4 can have interruption
#if defined(TIM_CCER_CC1NE)
      if (isComplementaryChannel[channel]) {
        HAL_TIMEx_OCN_Start_IT(&(_HardwareTimerObj.handle), timChannel);
      } else
#endif
      {
        HAL_TIM_OC_Start_IT(&(_HardwareTimerObj.handle), timChannel);
      }
    } else {
#if defined(TIM_CCER_CC1NE)
      if (isComplementaryChannel[channel]) {
        HAL_TIMEx_OCN_Start(&(_HardwareTimerObj.handle), timChannel);
      } else
#endif
      {
        HAL_TIM_OC_Start(&(_HardwareTimerObj.handle), timChannel);
      }
    }
  } else if (_channelIC[channel - 1].ICPolarity != TIMER_NOT_USED) {
    HAL_TIM_IC_ConfigChannel(&(_HardwareTimerObj.handle), &_channelIC[channel - 1], timChannel);

    if (callbacks[channel] != NULL) {
      HAL_TIM_IC_Start_IT(&(_HardwareTimerObj.handle), timChannel);
    } else {
      HAL_TIM_IC_Start(&(_HardwareTimerObj.handle), timChannel);
    }
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
  return (_HardwareTimerObj.handle.Init.Prescaler + 1);
}

/**
  * @brief  Configure hardwareTimer prescaler
  * @param  prescaler factor
  * @retval None
  */
void HardwareTimer::setPrescaleFactor(uint32_t prescaler)
{
  // Hardware register correspond to prescaler-1. Example PSC register value 0 means divided by 1
  __HAL_TIM_SET_PRESCALER(&_HardwareTimerObj.handle, prescaler - 1);
  _HardwareTimerObj.handle.Init.Prescaler = prescaler - 1;
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
  uint32_t ARR_RegisterValue = __HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle));
  uint32_t Prescalerfactor = _HardwareTimerObj.handle.Instance->PSC + 1;
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
  uint32_t Prescalerfactor;
  uint32_t period_cyc;
  // Remark: Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  switch (format) {
    case MICROSEC_FORMAT:
      period_cyc = overflow * (getTimerClkFreq() / 1000000);
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      __HAL_TIM_SET_PRESCALER(&_HardwareTimerObj.handle, Prescalerfactor - 1);
      _HardwareTimerObj.handle.Init.Prescaler = Prescalerfactor - 1;
      ARR_RegisterValue = (period_cyc / Prescalerfactor) - 1;
      break;
    case HERTZ_FORMAT:
      period_cyc = getTimerClkFreq() / overflow;
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      __HAL_TIM_SET_PRESCALER(&_HardwareTimerObj.handle, Prescalerfactor - 1);
      _HardwareTimerObj.handle.Init.Prescaler = Prescalerfactor - 1;
      ARR_RegisterValue = (period_cyc / Prescalerfactor) - 1;
      break;
    case TICK_FORMAT:
    default :
      ARR_RegisterValue = overflow - 1;
      break;
  }

  __HAL_TIM_SET_AUTORELOAD(&_HardwareTimerObj.handle, ARR_RegisterValue);
  _HardwareTimerObj.handle.Init.Period = ARR_RegisterValue;
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
  uint32_t CNT_RegisterValue = __HAL_TIM_GET_COUNTER(&(_HardwareTimerObj.handle));
  uint32_t Prescalerfactor = _HardwareTimerObj.handle.Instance->PSC + 1;
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
  uint32_t Prescalerfactor = _HardwareTimerObj.handle.Instance->PSC + 1;
  switch (format) {
    case MICROSEC_FORMAT:
      CNT_RegisterValue = ((counter * (getTimerClkFreq() / 1000000)) / Prescalerfactor) - 1 ;
      break;
    case HERTZ_FORMAT:
      CNT_RegisterValue = (uint32_t)((getTimerClkFreq() / (counter * Prescalerfactor)) - 1);
      break;
    case TICK_FORMAT:
    default :
      CNT_RegisterValue = counter - 1;
      break;
  }
  __HAL_TIM_SET_COUNTER(&(_HardwareTimerObj.handle), CNT_RegisterValue);
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
  if (getChannel(channel) == -1) {
    Error_Handler();
  }

  switch (mode) {
    case TIMER_OUTPUT_COMPARE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_TIMING;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_ACTIVE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_ACTIVE;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_INACTIVE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_ACTIVE;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_TOGGLE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_TOGGLE;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_PWM1:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_PWM1;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_PWM2:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_PWM2;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_FORCED_ACTIVE;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE:
      _channelOC[channel - 1].OCMode = TIM_OCMODE_FORCED_INACTIVE;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    case TIMER_INPUT_CAPTURE_RISING:
      _channelIC[channel - 1].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
      _channelIC[0].ICSelection = TIM_ICSELECTION_DIRECTTI;
      _channelOC[channel - 1].OCMode = TIMER_NOT_USED;
      break;
    case TIMER_INPUT_CAPTURE_FALLING:
      _channelIC[channel - 1].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
      _channelIC[0].ICSelection = TIM_ICSELECTION_DIRECTTI;
      _channelOC[channel - 1].OCMode = TIMER_NOT_USED;
      break;
    case TIMER_INPUT_CAPTURE_BOTHEDGE:
      _channelIC[channel - 1].ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
      _channelOC[channel - 1].OCMode = TIMER_NOT_USED;
      break;
    case TIMER_INPUT_FREQ_DUTY_MEASUREMENT:
      switch (channel) {
        case 1:
          _channelIC[0].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
          _channelIC[0].ICSelection = TIM_ICSELECTION_DIRECTTI;
          _channelIC[1].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
          _channelIC[1].ICSelection = TIM_ICSELECTION_INDIRECTTI;
          break;
        case 2:
          _channelIC[1].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
          _channelIC[1].ICSelection = TIM_ICSELECTION_DIRECTTI;
          _channelIC[0].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
          _channelIC[0].ICSelection = TIM_ICSELECTION_INDIRECTTI;
          break;
        case 3:
          _channelIC[2].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
          _channelIC[2].ICSelection = TIM_ICSELECTION_DIRECTTI;
          _channelIC[3].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
          _channelIC[3].ICSelection = TIM_ICSELECTION_INDIRECTTI;
          break;
        case 4:
          _channelIC[3].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
          _channelIC[3].ICSelection = TIM_ICSELECTION_DIRECTTI;
          _channelIC[2].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
          _channelIC[2].ICSelection = TIM_ICSELECTION_INDIRECTTI;
          break;
        default:
          break;
      }
      _channelOC[channel - 1].OCMode = TIMER_NOT_USED;
      break;
    case TIMER_DISABLED:
      _channelOC[channel - 1].OCMode = TIMER_NOT_USED;
      _channelIC[channel - 1].ICSelection = TIM_ICSELECTION_DIRECTTI;
      _channelIC[channel - 1].ICPolarity = TIMER_NOT_USED;
      break;
    default:
      break;
  }

  if (pin != NC) {
    if ((int)get_pwm_channel(pin) == getChannel(channel)) {
      /* Configure PWM GPIO pins */
      pinmap_pinout(pin, PinMap_PWM);
    } else {
      // Pin doesn't match with timer output channels
      Error_Handler();
    }

#if defined(TIM_CCER_CC1NE)
    isComplementaryChannel[channel] = STM_PIN_INVERTED(pinmap_function(pin, PinMap_PWM));
#endif
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
  uint32_t Prescalerfactor = _HardwareTimerObj.handle.Instance->PSC + 1;
  uint32_t CCR_RegisterValue;

  if (timChannel == -1) {
    Error_Handler();
  }

  switch (format) {
    case MICROSEC_COMPARE_FORMAT:
      CCR_RegisterValue = ((compare * (getTimerClkFreq() / 1000000)) / Prescalerfactor) - 1 ;
      break;
    case HERTZ_COMPARE_FORMAT:
      CCR_RegisterValue = (getTimerClkFreq() / (compare * Prescalerfactor)) - 1;
      break;
    case PERCENT_COMPARE_FORMAT:
      CCR_RegisterValue = ((__HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle)) + 1) * compare) / 100;
      break;
    case RESOLUTION_8B_COMPARE_FORMAT:
      CCR_RegisterValue = ((__HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle)) + 1) * compare) / 255 ;
      break;
    case RESOLUTION_12B_COMPARE_FORMAT:
      CCR_RegisterValue = ((__HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle)) + 1) * compare) / 4095 ;
      break;
    case TICK_COMPARE_FORMAT:
    default :
      CCR_RegisterValue = compare - 1;
      break;
  }

  __HAL_TIM_SET_COMPARE(&(_HardwareTimerObj.handle), timChannel, CCR_RegisterValue);
  _channelOC[channel - 1].Pulse = CCR_RegisterValue;
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
  uint32_t CCR_RegisterValue = __HAL_TIM_GET_COMPARE(&(_HardwareTimerObj.handle), timChannel);
  uint32_t Prescalerfactor = _HardwareTimerObj.handle.Instance->PSC + 1;
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
      return_value = (CCR_RegisterValue * 100) / __HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle));
      break;
    case RESOLUTION_8B_COMPARE_FORMAT:
      return_value = (CCR_RegisterValue * 255) / __HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle));
      break;
    case RESOLUTION_12B_COMPARE_FORMAT:
      return_value = (CCR_RegisterValue * 4095) / __HAL_TIM_GET_AUTORELOAD(&(_HardwareTimerObj.handle));
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
void HardwareTimer::setPWM(uint32_t channel, uint32_t pin, uint32_t frequency, uint32_t dutycycle, void (*PeriodCallback)(HardwareTimer *), void (*CompareCallback)(HardwareTimer *))
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
void HardwareTimer::setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, void (*PeriodCallback)(HardwareTimer *), void (*CompareCallback)(HardwareTimer *))
{
  setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
  setOverflow(frequency, HERTZ_FORMAT);
  setCaptureCompare(channel, dutycycle, PERCENT_COMPARE_FORMAT);
  if (PeriodCallback != NULL) {
    attachInterrupt(PeriodCallback);
  }
  if (CompareCallback != NULL) {
    attachInterrupt(channel, CompareCallback);
  }
  resume();
}

/**
  * @brief  Attach interrupt callback on update (rollover) event
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(void (*callback)(HardwareTimer *))
{
  callbacks[0] = callback;
}

/**
  * @brief  Dettach interrupt callback on update (rollover) event
  * @retval None
  */
void HardwareTimer::detachInterrupt()
{
  callbacks[0] = NULL;
}

/**
  * @brief  Attach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @param  callback: interrupt callback
  * @retval None
  */
void HardwareTimer::attachInterrupt(uint32_t channel, void (*callback)(HardwareTimer *))
{
  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }

  callbacks[channel] = callback;
}

/**
  * @brief  Dettach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::detachInterrupt(uint32_t channel)
{
  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }

  callbacks[channel] = NULL;
}

/**
  * @brief  Generate an update event to force all registers (Autoreload, prescaler, compare) to be taken into account
  * @note   Refresh() can only be called after a 1st call to resume() to be sure timer is initialised.
  *         It is usefull while timer is running after some registers update
  * @retval None
  */
void HardwareTimer::refresh()
{
  HAL_TIM_GenerateEvent(&(_HardwareTimerObj.handle), TIM_EVENTSOURCE_UPDATE);
}

/**
  * @brief  Generic Update (rollover) callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::updateCallback(TIM_HandleTypeDef *htim)
{
  if (htim == NULL) {
    Error_Handler();
  }

  HardwareTimerObj_t *obj = get_timer_obj(htim);
  HardwareTimer *HT = (HardwareTimer *)(obj->__this);

  if (HT->callbacks[0] != NULL) {
    HT->callbacks[0](HT);
  }
}

/**
  * @brief  Generic Caputre and Compare callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
void HardwareTimer::captureCompareCallback(TIM_HandleTypeDef *htim)
{
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

  if (htim == NULL) {
    Error_Handler();
  }

  HardwareTimerObj_t *obj = get_timer_obj(htim);
  HardwareTimer *HT = (HardwareTimer *)(obj->__this);

  if (HT->callbacks[channel] != NULL) {
    HT->callbacks[channel](HT);
  }
}

/**
  * @brief  HardwareTimer destructor
  * @retval None
  */
HardwareTimer::~HardwareTimer()
{
  uint32_t index = get_timer_index(_HardwareTimerObj.handle.Instance);
  HardwareTimer_Handle[index] = NULL;
  _HardwareTimerObj.__this = NULL;
  enableTimerClock(&(_HardwareTimerObj.handle));
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
  RCC_ClkInitTypeDef    clkconfig = {};
  uint32_t              pFLatency = 0U;
  uint32_t              uwTimclock = 0U, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  switch (getTimerClkSrc(_HardwareTimerObj.handle.Instance)) {
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
}

/* Aim of the function is to get _HardwareTimerObj_s pointer using htim pointer */
/* Highly inspired from magical linux kernel's "container_of" */
/* (which was not directly used since not compatible with IAR toolchain) */
HardwareTimerObj_t *get_timer_obj(TIM_HandleTypeDef *htim)
{
  HardwareTimerObj_t *obj;
  obj = (HardwareTimerObj_t *)((char *)htim - offsetof(HardwareTimerObj_t, handle));
  return (obj);
}

/**
  * @brief  This function will reset the timer
  * @param  obj : Hardware timer instance ex: Timer6, ...
  * @retval None
  */
void HardwareTimer::timerHandleDeinit()
{
  HAL_TIM_Base_Stop_IT(&(_HardwareTimerObj.handle));
  HAL_TIM_Base_DeInit(&(_HardwareTimerObj.handle));
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
    if (HardwareTimer_Handle[TIMER1_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER1_INDEX]->handle);
    }

#if defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#if defined (TIM10_BASE)
    if (HardwareTimer_Handle[TIMER10_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER10_INDEX]->handle);
    }
#endif
#endif

#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx) || defined(STM32L4xx) || \
    defined(STM32WBxx)
#if defined (TIM16_BASE)
    if (HardwareTimer_Handle[TIMER16_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER16_INDEX]->handle);
    }
#endif
#endif
  }

#if !defined(STM32F3xx)
  void TIM1_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER1_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER2_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER3_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER4_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER5_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER6_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER7_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER8_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER8_INDEX]->handle);
    }

#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx) || defined(STM32H7xx)
#if defined(TIMER13_BASE)
    if (HardwareTimer_Handle[TIMER13_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER13_INDEX]->handle);
    }
#endif // TIMER13_BASE
#endif
  }

  void TIM8_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER8_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER9_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER10_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER11_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER12_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER13_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER14_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER15_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER16_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER17_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER18_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER18_INDEX]->handle);
    }

#if defined(STM32F3xx)
#if defined (TIM1_BASE)
    if (HardwareTimer_Handle[TIMER1_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER19_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER20_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER20_INDEX]->handle);
    }
  }

  void TIM20_CC_IRQHandler(void)
  {
    if (HardwareTimer_Handle[TIMER20_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER21_INDEX] != NULL) {
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
    if (HardwareTimer_Handle[TIMER22_INDEX] != NULL) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER22_INDEX]->handle);
    }
  }
#endif //TIM22_BASE
}

#endif // HAL_TIM_MODULE_ENABLED