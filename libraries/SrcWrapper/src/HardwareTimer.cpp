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

#if !defined(HAL_TIM_MODULE_ONLY) &&\
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)))

/* Private Defines */
#define PIN_NOT_USED 0xFF
#define MAX_RELOAD ((1 << 16) - 1) // Currently even 32b timers are used as 16b to have generic behavior
#define REGULAR_CHAN_MASK 0x01
#define COMPLEMENTARY_CHAN_MASK 0x10

/* Private Variables */
timerObj_t *HardwareTimer_Handle[TIMER_NUM] = {NULL};

#if defined(HAL_FDCAN_MODULE_ENABLED) && defined(STM32G0xx) && defined(FDCAN1_BASE)
  /* Pointer to a FDCAN_HandleTypeDef structure that contains
  * the configuration information for the specified FDCAN.
  * Application have to declare them properly to be able to call
  * the HAL_FDCAN_IRQHandler().
  */
  extern FDCAN_HandleTypeDef *phfdcan1;
  #if defined(FDCAN2_BASE)
    extern FDCAN_HandleTypeDef *phfdcan2;
  #endif
#endif

/**
  * @brief  HardwareTimer constructor: make uninitialized timer
  *         Before calling any methods, call setup to select and setup
  *         the timer to be used.
  * @retval None
  */
HardwareTimer::HardwareTimer()
{
  _timerObj.instance = nullptr;
}

/**
  * @brief  HardwareTimer constructor: set default configuration values
  *         The timer will be usable directly, there is no need to call
  *         setup(). Using this constructor is not recommended for
  *         global variables that are automatically initialized at
  *         startup, since this will happen to early to report any
  *         errors. Better use the argumentless constructor and call the
  *         setup() method during initialization later.
  * @param  Timer instance ex: TIM1, ...
  * @retval None
  */
HardwareTimer::HardwareTimer(TIM_TypeDef *instance)
{
  _timerObj.instance = nullptr;
  setup(instance);
}

/**
  * @brief  HardwareTimer setup: configuration values. Must be called
  * exactly once before any other methods, except when an instance is
  * passed to the constructor.
  * @param  Timer instance ex: TIM1, ...
  * @retval None
  */
void HardwareTimer::setup(TIM_TypeDef *instance)
{
  uint32_t index = get_timer_index(instance);

  // Already initialized?
  if (_timerObj.instance) {
    Error_Handler();
  }
  HardwareTimer_Handle[index] = &_timerObj;

  _timerObj.instance = instance;
  _timerObj.__this = (void *)this;
  _timerObj.preemptPriority = TIM_IRQ_PRIO;
  _timerObj.subPriority = TIM_IRQ_SUBPRIO;

  /* Enable timer clock. Even if it is also done in HAL_TIM_Base_MspInit(),
     it is done there so that it is possible to write registers right now */
  enableTimerClock(instance);

  // Initialize NULL callbacks
  for (int i = 0; i < TIMER_CHANNELS + 1 ; i++) {
    callbacks[i] = NULL;
  }

  // Initialize channel mode and complementary
  for (int i = 0; i < TIMER_CHANNELS; i++) {
    __ChannelsUsed[i] = 0x00;
    _ChannelMode[i] = TIMER_OUTPUT_DISABLED;
  }

#if defined(USE_HALV2_DRIVER)
  hal_tim_config_t config;
  HAL_TIM_Init(&_timerObj.handle, (hal_tim_t)(uint32_t)instance);

  /* Configure timer with some default values */
  config.prescaler = 0;
  config.counter_mode = HAL_TIM_COUNTER_UP;
  config.period = MAX_RELOAD;
  config.repetition_counter = 0;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  HAL_TIM_SetConfig(&_timerObj.handle, &config);
  // /* Update Event Management */
  // HAL_TIM_SetUpdateSource(&_timerObj.handle, HAL_TIM_UPDATE_REGULAR);
  // HAL_TIM_EnableUpdateGeneration(&_timerObj.handle);

  // configure Update interrupt done in HAL_TIM_Base_MspInit for V1
  HAL_CORTEX_NVIC_SetPriority(getTimerUpIrq(_timerObj.instance),
                              (hal_cortex_nvic_preemp_priority_t)_timerObj.preemptPriority,
                              (hal_cortex_nvic_sub_priority_t)_timerObj.subPriority);
  HAL_CORTEX_NVIC_EnableIRQ(getTimerUpIrq(_timerObj.instance));

  if (getTimerCCIrq(_timerObj.instance) != getTimerUpIrq(_timerObj.instance)) {
    // configure Capture Compare interrupt
    HAL_CORTEX_NVIC_SetPriority(getTimerCCIrq(_timerObj.instance),
                                (hal_cortex_nvic_preemp_priority_t)_timerObj.preemptPriority,
                                (hal_cortex_nvic_sub_priority_t)_timerObj.subPriority);
    HAL_CORTEX_NVIC_EnableIRQ(getTimerCCIrq(_timerObj.instance));
  }
#else
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
#endif
}

/**
  * @brief  Pause HardwareTimer: stop timer
  * @param  None
  * @retval None
  */
void HardwareTimer::pause()
{
  // Disable all IT
  LL_TIM_DisableIT_UPDATE(_timerObj.instance);
  LL_TIM_DisableIT_CC1(_timerObj.instance);
  LL_TIM_DisableIT_CC2(_timerObj.instance);
  LL_TIM_DisableIT_CC3(_timerObj.instance);
  LL_TIM_DisableIT_CC4(_timerObj.instance);

#if defined(USE_HALV2_DRIVER)
  HAL_TIM_Stop(&(_timerObj.handle));
#else
  // Stop timer. Required to restore HAL State: HAL_TIM_STATE_READY
  HAL_TIM_Base_Stop(&(_timerObj.handle));
#endif
  /* Disable timer unconditionally. Required to guarantee timer is stopped,
   * even if some channels are still running */
  LL_TIM_DisableCounter(_timerObj.instance);

#if defined(TIM_CHANNEL_STATE_SET_ALL)
  /* Starting from G4, new Channel state implementation prevents to restart a channel,
     if the channel has not been explicitly be stopped with HAL interface */
  TIM_CHANNEL_STATE_SET_ALL(&(_timerObj.handle), HAL_TIM_CHANNEL_STATE_READY);
#endif
#if defined(TIM_CHANNEL_N_STATE_SET_ALL)
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
  if ((channel < 1) || (channel > TIMER_CHANNELS)) {
    return;
  }

  uint32_t timAssociatedInputChannel;
  uint32_t LLChannel = getLLChannel(channel);

  (void)manageIT(channel, DISABLE_IT); // Disable IT corresponding to channel
  LL_TIM_CC_DisableChannel(_timerObj.instance, LLChannel);
#if defined(TIM_CHANNEL_STATE_SET)
  /* Starting from G4, new Channel state implementation prevents to restart a channel,
     if the channel has not been explicitly be stopped with HAL interface */
#if defined(TIM_CHANNEL_N_STATE_SET)
  if (__ChannelsUsed[channel - 1] & COMPLEMENTARY_CHAN_MASK) {
    TIM_CHANNEL_N_STATE_SET(&(_timerObj.handle), getChannel(channel), HAL_TIM_CHANNEL_STATE_READY);
  }
#endif
  if (__ChannelsUsed[channel - 1] & REGULAR_CHAN_MASK) {
    TIM_CHANNEL_STATE_SET(&(_timerObj.handle), getChannel(channel), HAL_TIM_CHANNEL_STATE_READY);
  }
#endif

  // In case 2 channels are used, disable also the 2nd one
  if (_ChannelMode[channel - 1] == TIMER_INPUT_FREQ_DUTY_MEASUREMENT) {
    // Identify and configure 2nd associated channel
    timAssociatedInputChannel = getAssociatedChannel(channel);
    switch (timAssociatedInputChannel) {
      case 1:
        LL_TIM_EnableIT_CC1(_timerObj.instance);
        break;
      case 2:
        LL_TIM_EnableIT_CC2(_timerObj.instance);
        break;
      case 3:
        LL_TIM_EnableIT_CC3(_timerObj.instance);
        break;
      case 4:
        LL_TIM_EnableIT_CC4(_timerObj.instance);
        break;
      default:
        Error_Handler();
    }
    LL_TIM_CC_DisableChannel(_timerObj.instance, getLLChannel(timAssociatedInputChannel));
  }
}

/**
  * @brief  Start or resume HardwareTimer: all channels are resumed, interrupts are enabled if necessary
  * @param  None
  * @retval None
  */
void HardwareTimer::resume(void)
{
  bool baseStart = true;
  for (uint8_t i = 1; i <= TIMER_CHANNELS; i++) {
    if (_ChannelMode[i - 1] != TIMER_OUTPUT_DISABLED) {
      resumeChannel(i);
      baseStart = false;
    }
  }
  // Clear flag and enable IT
  if (callbacks[0]) {
    LL_TIM_EnableIT_UPDATE(_timerObj.instance);
  }

  // Start timer in Time base mode. Required when there is no channel used but only update interrupt.
  if (baseStart && (!LL_TIM_IsEnabledCounter(_timerObj.instance))) {
#if defined(USE_HALV2_DRIVER)
    HAL_TIM_Start(&(_timerObj.handle));
#else
    HAL_TIM_Base_Start(&(_timerObj.handle));
#endif
  }
}

/**
  * @brief  Convert arduino channel into HAL channel
  * @param  Arduino channel [1..4]
  * @retval HAL channel. Error handler called if arduino channel is invalid
  */
#if defined(USE_HALV2_DRIVER)
hal_tim_channel_t HardwareTimer::getChannel(uint32_t channel, bool complementary)
{
  hal_tim_channel_t timChannel = HAL_TIM_CHANNEL_1;

  switch (channel) {
    case 1:
      if (complementary) {
        timChannel = HAL_TIM_CHANNEL_1N;
      } else {
        timChannel = HAL_TIM_CHANNEL_1;
      }
      break;
    case 2:
      if (complementary) {
        timChannel = HAL_TIM_CHANNEL_2N;
      } else {
        timChannel = HAL_TIM_CHANNEL_2;
      }
      break;
    case 3:
      if (complementary) {
        timChannel = HAL_TIM_CHANNEL_3N;
      } else {
        timChannel = HAL_TIM_CHANNEL_3;
      }
      break;
    case 4:
      if (complementary) {
        timChannel = HAL_TIM_CHANNEL_4N;
      } else {
        timChannel = HAL_TIM_CHANNEL_4;
      }
      break;
    default:
      Error_Handler();
  }
  return timChannel;
}
#else
uint32_t HardwareTimer::getChannel(uint32_t channel)
{
  uint32_t timChannel = -1;

  switch (channel) {
    case 1:
      timChannel = TIM_CHANNEL_1;
      break;
    case 2:
      timChannel = TIM_CHANNEL_2;
      break;
    case 3:
      timChannel = TIM_CHANNEL_3;
      break;
    case 4:
      timChannel = TIM_CHANNEL_4;
      break;
    default:
      Error_Handler();
  }
  return timChannel;
}
#endif

/**
  * @brief  Convert arduino channel into LL channels used (regular and/or complementary)
  * @param  Arduino channel [1..4]
  * @retval LL channel. Error handler called if arduino channel is invalid
  */
uint32_t HardwareTimer::getLLChannel(uint32_t channel)
{
  bool error = false;
  uint32_t ll_channel = 0;

#if defined(TIM_CCER_CC1NE)
  if (__ChannelsUsed[channel - 1] & COMPLEMENTARY_CHAN_MASK) {
    // Complementary channel
    switch (channel) {
      case 1:
        ll_channel = LL_TIM_CHANNEL_CH1N;
        break;
#if defined(TIM_CCER_CC2NE)
#if defined(LL_TIM_CHANNEL_CH2N)
      case 2:
        ll_channel = LL_TIM_CHANNEL_CH2N;
        break;
#endif
#endif
#if defined(TIM_CCER_CC3NE)
#if defined(LL_TIM_CHANNEL_CH3N)
      case 3:
        ll_channel = LL_TIM_CHANNEL_CH3N;
        break;
#endif
#endif
#if defined(LL_TIM_CHANNEL_CH4N)
      case 4:
        ll_channel = LL_TIM_CHANNEL_CH4N;
        break;
#endif
      default:
        error = true;
    }
  }
#endif
  if ((!error) && (__ChannelsUsed[channel - 1] & REGULAR_CHAN_MASK)) {
    // Regular channel not complementary
    switch (channel) {
      case 1:
        ll_channel |= LL_TIM_CHANNEL_CH1;
        break;
      case 2:
        ll_channel |= LL_TIM_CHANNEL_CH2;
        break;
      case 3:
        ll_channel |= LL_TIM_CHANNEL_CH3;
        break;
      case 4:
        ll_channel |= LL_TIM_CHANNEL_CH4;
        break;
      default:
        error = true;
    }
  }
  if (error) {
    Error_Handler();
  }
  return ll_channel;
}

/**
  * @brief  Handle itterupt based on arduino channel
  * @param  Arduino channel [1..4]
  * @param  config: configuration for the interrupt (enable, disable, clear, clear and disable)
  * @retval true if interrupt is enabled, false otherwise
  */
bool HardwareTimer::manageIT(uint32_t channel, ChannelITConfig_t config)
{
  bool isEnabled = false;
  // Clear flag before enabling IT
  switch (channel) {
    case 1:
      if (config == CLEAR_IT) {
        LL_TIM_ClearFlag_CC1(_timerObj.instance);
      }
      if (config == DISABLE_IT) {
        LL_TIM_DisableIT_CC1(_timerObj.instance);
      }
      if (config == ENABLE_IT || config == CLEAR_AND_ENABLE_IT) {
        LL_TIM_EnableIT_CC1(_timerObj.instance);
      }
      isEnabled = LL_TIM_IsEnabledIT_CC1(_timerObj.instance);
      break;
    case 2:
      if (config == CLEAR_IT) {
        LL_TIM_ClearFlag_CC2(_timerObj.instance);
      }
      if (config == DISABLE_IT) {
        LL_TIM_DisableIT_CC2(_timerObj.instance);
      }
      if (config == ENABLE_IT || config == CLEAR_AND_ENABLE_IT) {
        LL_TIM_EnableIT_CC2(_timerObj.instance);
      }
      isEnabled = LL_TIM_IsEnabledIT_CC2(_timerObj.instance);
      break;
    case 3:
      if (config == CLEAR_IT) {
        LL_TIM_ClearFlag_CC3(_timerObj.instance);
      }
      if (config == DISABLE_IT) {
        LL_TIM_DisableIT_CC3(_timerObj.instance);
      }
      if (config == ENABLE_IT || config == CLEAR_AND_ENABLE_IT) {
        LL_TIM_EnableIT_CC3(_timerObj.instance);
      }
      isEnabled = LL_TIM_IsEnabledIT_CC3(_timerObj.instance);
      break;
    case 4:
      if (config == CLEAR_IT) {
        LL_TIM_ClearFlag_CC4(_timerObj.instance);
      }
      if (config == DISABLE_IT) {
        LL_TIM_DisableIT_CC4(_timerObj.instance);
      }
      if (config == ENABLE_IT || config == CLEAR_AND_ENABLE_IT) {
        LL_TIM_EnableIT_CC4(_timerObj.instance);
      }
      isEnabled = LL_TIM_IsEnabledIT_CC4(_timerObj.instance);
      break;
    default:
      Error_Handler();
  }
  return isEnabled;
}

/**
  * @brief  Get input associated channel
  *         Channel 1 and 2 are associated; channel 3 and 4 are associated
  * @param  Arduino channel [1..4]
  * @retval HAL channel. Error handler called if arduino channel is invalid
  */
uint32_t HardwareTimer::getAssociatedChannel(uint32_t channel)
{
  uint32_t timAssociatedInputChannel = 0;
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
      Error_Handler();
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
#if defined(USE_HALV2_DRIVER)
  hal_tim_channel_t timChannel = getChannel(channel);
  hal_tim_channel_t timChannelN = getChannel(channel, true);
#else
  uint32_t timChannel = getChannel(channel);
#endif
  uint32_t timAssociatedInputChannel;

  // Clear flag and enable IT
  if (callbacks[channel]) {
    manageIT(channel, CLEAR_AND_ENABLE_IT);
  }

  switch (_ChannelMode[channel - 1]) {
    case TIMER_OUTPUT_COMPARE_PWM1:
    case TIMER_OUTPUT_COMPARE_PWM2: {
#if defined(TIM_CCER_CC1NE)
        if (__ChannelsUsed[channel - 1] & COMPLEMENTARY_CHAN_MASK) {
#if defined(USE_HALV2_DRIVER)
          HAL_TIM_OC_StartChannel(&_timerObj.handle, timChannelN);
          HAL_TIM_Start(&_timerObj.handle);
#else
          HAL_TIMEx_PWMN_Start(&(_timerObj.handle), timChannel);
#endif
        }
#endif
        if (__ChannelsUsed[channel - 1] & REGULAR_CHAN_MASK) {
#if defined(USE_HALV2_DRIVER)
          HAL_TIM_OC_StartChannel(&_timerObj.handle, timChannel);
          HAL_TIM_Start(&_timerObj.handle);
#else
          HAL_TIM_PWM_Start(&(_timerObj.handle), timChannel);
#endif
        }
      }
      break;
    case TIMER_OUTPUT_COMPARE_ACTIVE:
    case TIMER_OUTPUT_COMPARE_INACTIVE:
    case TIMER_OUTPUT_COMPARE_TOGGLE:
    case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
    case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE: {
#if defined(TIM_CCER_CC1NE)
        if (__ChannelsUsed[channel - 1] & COMPLEMENTARY_CHAN_MASK) {
#if defined(USE_HALV2_DRIVER)
          HAL_TIM_OC_StartChannel(&_timerObj.handle, timChannelN);
          HAL_TIM_Start(&_timerObj.handle);
#else
          HAL_TIMEx_OCN_Start(&(_timerObj.handle), timChannel);
#endif
        }
#endif
        if (__ChannelsUsed[channel - 1] & REGULAR_CHAN_MASK) {
#if defined(USE_HALV2_DRIVER)
          HAL_TIM_OC_StartChannel(&_timerObj.handle, timChannel);
          HAL_TIM_Start(&_timerObj.handle);
#else
          HAL_TIM_OC_Start(&(_timerObj.handle), timChannel);
#endif
        }
      }
      break;
    case TIMER_INPUT_FREQ_DUTY_MEASUREMENT: {
#if defined(USE_HALV2_DRIVER)
        HAL_TIM_IC_StartChannel(&_timerObj.handle, timChannel);
        HAL_TIM_Start(&_timerObj.handle);
#else
        HAL_TIM_IC_Start(&(_timerObj.handle), timChannel);
#endif
        // Enable 2nd associated channel
        timAssociatedInputChannel = getAssociatedChannel(channel);
        LL_TIM_CC_EnableChannel(_timerObj.instance, getLLChannel(timAssociatedInputChannel));
        if (callbacks[channel]) {
          manageIT(timAssociatedInputChannel, CLEAR_AND_ENABLE_IT);
        }
      }
      break;
    case TIMER_INPUT_CAPTURE_RISING:
    case TIMER_INPUT_CAPTURE_FALLING:
    case TIMER_INPUT_CAPTURE_BOTHEDGE: {
#if defined(USE_HALV2_DRIVER)
        HAL_TIM_IC_StartChannel(&_timerObj.handle, timChannel);
        HAL_TIM_Start(&_timerObj.handle);
#else
        HAL_TIM_IC_Start(&(_timerObj.handle), timChannel);
#endif
      }
      break;
    case TIMER_OUTPUT_DISABLED:
      if (!LL_TIM_IsEnabledCounter(_timerObj.instance)) {
#if defined(USE_HALV2_DRIVER)
        HAL_TIM_Start(&(_timerObj.handle));
#else
        HAL_TIM_Base_Start(&(_timerObj.handle));
#endif
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
  return (LL_TIM_GetPrescaler(_timerObj.instance) + 1);
}

/**
  * @brief  Configure hardwareTimer prescaler
  * @param  prescaler factor
  * @retval None
  */
void HardwareTimer::setPrescaleFactor(uint32_t prescaler)
{
  // Hardware register correspond to prescaler-1. Example PSC register value 0 means divided by 1
  LL_TIM_SetPrescaler(_timerObj.instance, prescaler - 1);

  updateRegistersIfNotRunning(_timerObj.instance);
}

/**
  * @brief  Retrieve overflow (rollover) value from hardware register
  * @param  format of returned value. If omitted default format is Tick
  * @retval overflow depending on format value:
  *           TICK_FORMAT:     return number of tick for overflow
  *           MICROSEC_FORMAT: return number of microsecondes for overflow
  *           HERTZ_FORMAT:    return frequency in hertz for overflow
  */
uint32_t HardwareTimer::getOverflow(TimerFormat_t format)
{
  // Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  uint32_t ARR_RegisterValue = LL_TIM_GetAutoReload(_timerObj.instance);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.instance) + 1;
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
  * @param  format of overflow parameter. If omitted default format is Tick
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
      LL_TIM_SetPrescaler(_timerObj.instance, Prescalerfactor - 1);
      PeriodTicks = period_cyc / Prescalerfactor;
      break;
    case HERTZ_FORMAT:
      period_cyc = getTimerClkFreq() / overflow;
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      LL_TIM_SetPrescaler(_timerObj.instance, Prescalerfactor - 1);
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
  LL_TIM_SetAutoReload(_timerObj.instance, ARR_RegisterValue);

  updateRegistersIfNotRunning(_timerObj.instance);
}

/**
  * @brief  Retrieve timer counter value
  * @param  format of returned value. If omitted default format is Tick
  * @retval overflow depending on format value:
  *           TICK_FORMAT:     return number of tick for counter
  *           MICROSEC_FORMAT: return number of microsecondes for counter
  *           HERTZ_FORMAT:    return frequency in hertz for counter
  */
uint32_t HardwareTimer::getCount(TimerFormat_t format)
{
  uint32_t CNT_RegisterValue = LL_TIM_GetCounter(_timerObj.instance);
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.instance) + 1;
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
  * @param  format of overflow parameter. If omitted default format is Tick
  *           TICK_FORMAT:     counter is the number of tick
  *           MICROSEC_FORMAT: counter is the number of microsecondes
  *           HERTZ_FORMAT:    counter is the frequency in hertz
  * @retval None
  */
void HardwareTimer::setCount(uint32_t counter, TimerFormat_t format)
{
  uint32_t CNT_RegisterValue;
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.instance) + 1;
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
  LL_TIM_SetCounter(_timerObj.instance, CNT_RegisterValue);
}

/**
  * @brief  Set channel mode
  * @param  channel: Arduino channel [1..4]
  * @param  mode: mode configuration for the channel (see TimerModes_t)
  * @param  pin: Arduino pin number, ex: D1, 1 or PA1
  * @retval None
  */
void HardwareTimer::setMode(uint32_t channel, TimerModes_t mode, pin_size_t pin, ChannelInputFilter_t filter)
{
  setMode(channel, mode, digitalPinToPinName(pin), filter);
}

/**
  * @brief  Set channel mode
  * @param  channel: Arduino channel [1..4]
  * @param  mode: mode configuration for the channel (see TimerModes_t)
  * @param  pin: pin name, ex: PB_0
  * @retval None
  */
void HardwareTimer::setMode(uint32_t channel, TimerModes_t mode, PinName pin, ChannelInputFilter_t filter)
{
  uint32_t timAssociatedInputChannel;
  bool inverted = (pin != NC) ? STM_PIN_INVERTED(pinmap_function(pin, PinMap_TIM)) : false;
#if defined(USE_HALV2_DRIVER)
  hal_tim_channel_t timChannel = (inverted) ? getChannel(channel, true) : getChannel(channel, false);
  hal_tim_oc_compare_unit_t oc_compare_unit = hal_tim_oc_channel_to_compare_unit(timChannel);
  hal_tim_oc_compare_unit_config_t oc_cu_config;
  hal_tim_oc_channel_config_t oc_channel_config;
  hal_tim_ic_capture_unit_t ic_capture_unit = hal_tim_ic_channel_to_direct_capture_unit(timChannel);
  hal_tim_ic_capture_unit_config_t ic_cu_config;
  hal_tim_ic_channel_config_t ic_channel_config;
  /* Configure some default values. Maybe overwritten later */
  oc_channel_config.polarity = HAL_TIM_OC_HIGH;
  oc_channel_config.idle_state = HAL_TIM_OC_IDLE_STATE_RESET;
  oc_channel_config.override_state = HAL_TIM_OC_OVERRIDE_RESET;
  oc_channel_config.break_mode = HAL_TIM_OC_BREAKMODE_IMMEDIATE;
  // OCFastMode = TIM_OCFAST_DISABLE; --> replaced by HAL_TIM_OC_EnableChannelFastMode if supported
  ic_channel_config.polarity = HAL_TIM_IC_RISING;
  ic_channel_config.source = HAL_TIM_INPUT_TIM1_TI1_GPIO;
  ic_channel_config.filter = (hal_tim_filter_t)filter;

  ic_cu_config.prescaler = HAL_TIM_IC_DIV1;
  ic_cu_config.source = HAL_TIM_IC_DIRECT;

  switch (channel) {
    case 1:
      oc_cu_config.pulse = LL_TIM_OC_GetCompareCH1(_timerObj.instance);
      break;
    case 2:
      oc_cu_config.pulse = LL_TIM_OC_GetCompareCH2(_timerObj.instance);
      break;
    case 3:
      oc_cu_config.pulse = LL_TIM_OC_GetCompareCH3(_timerObj.instance);
      break;
    case 4:
      oc_cu_config.pulse = LL_TIM_OC_GetCompareCH4(_timerObj.instance);
      break;
    default:
      Error_Handler();
  }

  switch (mode) {
    case TIMER_OUTPUT_DISABLED:
      oc_cu_config.mode = HAL_TIM_OC_FROZEN;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_ACTIVE:
      oc_cu_config.mode = HAL_TIM_OC_ACTIVE_ON_MATCH;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_INACTIVE:
      oc_cu_config.mode = HAL_TIM_OC_INACTIVE_ON_MATCH;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_TOGGLE:
      oc_cu_config.mode = HAL_TIM_OC_TOGGLE;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_PWM1:
      oc_cu_config.mode = HAL_TIM_OC_PWM1;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_PWM2:
      oc_cu_config.mode = HAL_TIM_OC_PWM2;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
      oc_cu_config.mode = HAL_TIM_OC_FORCED_ACTIVE;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE:
      oc_cu_config.mode = HAL_TIM_OC_FORCED_INACTIVE;
      HAL_TIM_OC_SetConfigCompareUnit(&_timerObj.handle, oc_compare_unit, &oc_cu_config);
      HAL_TIM_OC_SetConfigChannel(&_timerObj.handle, timChannel, &oc_channel_config);
      break;
    case TIMER_INPUT_CAPTURE_RISING:
      ic_channel_config.polarity = HAL_TIM_IC_RISING;
      HAL_TIM_IC_SetConfigChannel(&_timerObj.handle, timChannel, &ic_channel_config);
      HAL_TIM_IC_SetConfigCaptureUnit(&_timerObj.handle, ic_capture_unit, &ic_cu_config);
      break;
    case TIMER_INPUT_CAPTURE_FALLING:
      ic_channel_config.polarity = HAL_TIM_IC_FALLING;
      HAL_TIM_IC_SetConfigChannel(&_timerObj.handle, timChannel, &ic_channel_config);
      HAL_TIM_IC_SetConfigCaptureUnit(&_timerObj.handle, ic_capture_unit, &ic_cu_config);
      break;
    case TIMER_INPUT_CAPTURE_BOTHEDGE:
      ic_channel_config.polarity = HAL_TIM_IC_RISING_FALLING;
      HAL_TIM_IC_SetConfigChannel(&_timerObj.handle, timChannel, &ic_channel_config);
      HAL_TIM_IC_SetConfigCaptureUnit(&_timerObj.handle, ic_capture_unit, &ic_cu_config);
      break;
    case TIMER_INPUT_FREQ_DUTY_MEASUREMENT:
      // Check if regular channel
      if (inverted) {
        Error_Handler();
      }
      // Configure 1st channel
      ic_channel_config.polarity = HAL_TIM_IC_RISING;
      HAL_TIM_IC_SetConfigChannel(&_timerObj.handle, timChannel, &ic_channel_config);
      HAL_TIM_IC_SetConfigCaptureUnit(&_timerObj.handle, ic_capture_unit, &ic_cu_config);

      // Identify and configure 2nd associated channel
      timAssociatedInputChannel = getAssociatedChannel(channel);
      __ChannelsUsed[timAssociatedInputChannel - 1] |= REGULAR_CHAN_MASK;
      _ChannelMode[timAssociatedInputChannel - 1] = mode;
      ic_channel_config.polarity = HAL_TIM_IC_FALLING;
      ic_capture_unit = hal_tim_ic_channel_to_direct_capture_unit(getChannel(timAssociatedInputChannel));
      ic_cu_config.source = HAL_TIM_IC_INDIRECT_FALLING;
      HAL_TIM_IC_SetConfigChannel(&_timerObj.handle, getChannel(timAssociatedInputChannel), &ic_channel_config);
      HAL_TIM_IC_SetConfigCaptureUnit(&_timerObj.handle, ic_capture_unit, &ic_cu_config);
      break;
    default:
      break;
  }
#else
  uint32_t timChannel = getChannel(channel);
  TIM_OC_InitTypeDef channelOC;
  TIM_IC_InitTypeDef channelIC;

  /* Configure some default values. Maybe overwritten later */
  channelOC.OCMode = TIMER_NOT_USED;
  switch (channel) {
    case 1:
      channelOC.Pulse = LL_TIM_OC_GetCompareCH1(_timerObj.instance);
      break;
    case 2:
      channelOC.Pulse = LL_TIM_OC_GetCompareCH2(_timerObj.instance);
      break;
    case 3:
      channelOC.Pulse = LL_TIM_OC_GetCompareCH3(_timerObj.instance);
      break;
    case 4:
      channelOC.Pulse = LL_TIM_OC_GetCompareCH4(_timerObj.instance);
      break;
    default:
      Error_Handler();
  }
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
  channelIC.ICPolarity = TIM_ICPOLARITY_RISING;
  channelIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  channelIC.ICPrescaler = TIM_ICPSC_DIV1;
  channelIC.ICFilter = filter;

  switch (mode) {
    case TIMER_OUTPUT_DISABLED:
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
      // Check if regular channel
      if (inverted) {
        Error_Handler();
      }
      // Configure 1st channel
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
      channelIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, timChannel);

      // Identify and configure 2nd associated channel
      timAssociatedInputChannel = getAssociatedChannel(channel);
      __ChannelsUsed[timAssociatedInputChannel - 1] |= REGULAR_CHAN_MASK;
      _ChannelMode[timAssociatedInputChannel - 1] = mode;
      channelIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
      channelIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
      HAL_TIM_IC_ConfigChannel(&(_timerObj.handle), &channelIC, getChannel(timAssociatedInputChannel));
      break;
    default:
      break;
  }
#endif
  // Save channel selected mode to object attribute
  _ChannelMode[channel - 1] = mode;
  if (mode != TIMER_OUTPUT_DISABLED) {
    if (pin != NC) {
      if (getTimerChannel(pin) == timChannel) {
        /* Configure PWM GPIO pins */
        pinmap_pinout(pin, PinMap_TIM);
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

      __ChannelsUsed[channel - 1] |= (inverted) ? COMPLEMENTARY_CHAN_MASK : REGULAR_CHAN_MASK;
    }
  }
}

/**
  * @brief  Retrieves channel mode configured
  * @param  channel: Arduino channel [1..4]
  * @retval returns configured mode
  */
TimerModes_t HardwareTimer::getMode(uint32_t channel)
{
  return ((1 <= channel) && (channel <= TIMER_CHANNELS)) ? _ChannelMode[channel - 1] : TIMER_OUTPUT_DISABLED;
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
    LL_TIM_EnableARRPreload(_timerObj.instance);
  } else {
    LL_TIM_DisableARRPreload(_timerObj.instance);
  }
}

/**
  * @brief  Set channel Capture/Compare register
  * @param  channel: Arduino channel [1..4]
  * @param  compare: compare value depending on format
  * @param  format of compare parameter. If omitted default format is Tick
  *           TICK_FORMAT:     compare is the number of tick
  *           MICROSEC_FORMAT: compare is the number of microsecondes
  *           HERTZ_FORMAT:    compare is the frequency in hertz
  * @retval None
  */
void HardwareTimer::setCaptureCompare(uint32_t channel, uint32_t compare, TimerCompareFormat_t format)
{
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.instance) + 1;
  uint32_t CCR_RegisterValue;

  switch (format) {
    case MICROSEC_COMPARE_FORMAT:
      CCR_RegisterValue = ((compare * (getTimerClkFreq() / 1000000)) / Prescalerfactor);
      break;
    case HERTZ_COMPARE_FORMAT:
      CCR_RegisterValue = getTimerClkFreq() / (compare * Prescalerfactor);
      break;
    // As per Reference Manual PWM reach 100% with CCRx value strictly greater than ARR (So ARR+1 in our case)
    case PERCENT_COMPARE_FORMAT:
      CCR_RegisterValue = ((LL_TIM_GetAutoReload(_timerObj.instance) + 1) * compare) / 100;
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
      CCR_RegisterValue = ((LL_TIM_GetAutoReload(_timerObj.instance) + 1) * compare) / ((1 << format) - 1) ;
      break;
    case TICK_COMPARE_FORMAT:
    default :
      CCR_RegisterValue = compare;
      break;
  }

  // Special case when ARR is set to the max value, it is not possible to set CCRx to ARR+1 to reach 100%
  // Then set CCRx to max value. PWM is then 1/0xFFFF = 99.998..%
  if ((LL_TIM_GetAutoReload(_timerObj.instance) == MAX_RELOAD)
      && (CCR_RegisterValue == MAX_RELOAD + 1)) {
    CCR_RegisterValue = MAX_RELOAD;
  }

  switch (channel) {
    case 1:
      LL_TIM_OC_SetCompareCH1(_timerObj.instance, CCR_RegisterValue);
      break;
    case 2:
      LL_TIM_OC_SetCompareCH2(_timerObj.instance, CCR_RegisterValue);
      break;
    case 3:
      LL_TIM_OC_SetCompareCH3(_timerObj.instance, CCR_RegisterValue);
      break;
    case 4:
      LL_TIM_OC_SetCompareCH4(_timerObj.instance, CCR_RegisterValue);
      break;
    default:
      Error_Handler();
  }

  updateRegistersIfNotRunning(_timerObj.instance);
}

/**
  * @brief  Retrieve Capture/Compare value
  * @param  channel: Arduino channel [1..4]
  * @param  format of return value. If omitted default format is Tick
  *           TICK_FORMAT:     return value is the number of tick for Capture/Compare value
  *           MICROSEC_FORMAT: return value is the number of microsecondes for Capture/Compare value
  *           HERTZ_FORMAT:    return value is the frequency in hertz for Capture/Compare value
  * @retval Capture/Compare value
  */
uint32_t HardwareTimer::getCaptureCompare(uint32_t channel,  TimerCompareFormat_t format)
{
  uint32_t CCR_RegisterValue = 0;
  uint32_t Prescalerfactor = LL_TIM_GetPrescaler(_timerObj.instance) + 1;
  uint32_t return_value;

  switch (channel) {
    case 1:
      CCR_RegisterValue = LL_TIM_OC_GetCompareCH1(_timerObj.instance);
      break;
    case 2:
      CCR_RegisterValue = LL_TIM_OC_GetCompareCH2(_timerObj.instance);
      break;
    case 3:
      CCR_RegisterValue = LL_TIM_OC_GetCompareCH3(_timerObj.instance);
      break;
    case 4:
      CCR_RegisterValue = LL_TIM_OC_GetCompareCH4(_timerObj.instance);
      break;
    default:
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
      return_value = (CCR_RegisterValue * 100) / LL_TIM_GetAutoReload(_timerObj.instance);
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
      return_value = (CCR_RegisterValue * ((1 << format) - 1)) / LL_TIM_GetAutoReload(_timerObj.instance);
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
  * @param  frequency: PWM frequency expressed in hertz
  * @param  dutycycle: PWM dutycycle expressed in percentage
  * @param  PeriodCallback: timer period callback (timer rollover upon update event)
  * @param  CompareCallback: timer compare callback
  * @retval None
  */
void HardwareTimer::setPWM(uint32_t channel, pin_size_t pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback, callback_function_t CompareCallback)
{
  setPWM(channel, digitalPinToPinName(pin), frequency, dutycycle, PeriodCallback, CompareCallback);
}

/**
  * @brief  All in one function to configure PWM
  * @param  channel: Arduino channel [1..4]
  * @param  pin: pin name, ex PB_0
  * @param  frequency: PWM frequency expressed in hertz
  * @param  dutycycle: PWM dutycycle expressed in percentage
  * @param  PeriodCallback: timer period callback (timer rollover upon update event)
  * @param  CompareCallback: timer compare callback
  * @retval None
  */
void HardwareTimer::setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback, callback_function_t CompareCallback)
{
  TimerModes_t previousMode = getMode(channel);
  if (previousMode != TIMER_OUTPUT_COMPARE_PWM1) {
    setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
  }
  setOverflow(frequency, HERTZ_FORMAT);
  setCaptureCompare(channel, dutycycle, PERCENT_COMPARE_FORMAT);
  if (PeriodCallback) {
    attachInterrupt(PeriodCallback);
  }
  if (CompareCallback) {
    attachInterrupt(channel, CompareCallback);
  }
  if (!isRunning() || !isRunningChannel(channel) || (previousMode != TIMER_OUTPUT_COMPARE_PWM1)) {
    resume();
  }
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
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_SetPriority(getTimerUpIrq(_timerObj.instance),
                              (hal_cortex_nvic_preemp_priority_t)preemptPriority,
                              (hal_cortex_nvic_sub_priority_t)subPriority);
#else
  HAL_NVIC_SetPriority(getTimerUpIrq(_timerObj.instance), preemptPriority, subPriority);
#endif
  // Set Capture/Compare interrupt priority if timer provides a unique IRQ
  if (getTimerCCIrq(_timerObj.instance) != getTimerUpIrq(_timerObj.instance)) {
#if defined(USE_HALV2_DRIVER)
    HAL_CORTEX_NVIC_SetPriority(getTimerCCIrq(_timerObj.instance),
                                (hal_cortex_nvic_preemp_priority_t)preemptPriority,
                                (hal_cortex_nvic_sub_priority_t)subPriority);
#else
    HAL_NVIC_SetPriority(getTimerCCIrq(_timerObj.instance), preemptPriority, subPriority);
#endif
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
      LL_TIM_ClearFlag_UPDATE(_timerObj.instance);
      // Enable update interrupt only if callback is valid
      LL_TIM_EnableIT_UPDATE(_timerObj.instance);
    }
  }
}

/**
  * @brief  Detach interrupt callback on update (rollover) event
  * @retval None
  */
void HardwareTimer::detachInterrupt()
{
  // Disable update interrupt and clear callback
  LL_TIM_DisableIT_UPDATE(_timerObj.instance); // disables the interrupt call to save cpu cycles for useless context switching
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
      manageIT(channel, CLEAR_AND_ENABLE_IT);
    }
  }
}

/**
  * @brief  Detach interrupt callback on Capture/Compare event
  * @param  channel: Arduino channel [1..4]
  * @retval None
  */
void HardwareTimer::detachInterrupt(uint32_t channel)
{
  if ((channel == 0) || (channel > (TIMER_CHANNELS + 1))) {
    Error_Handler();  // only channel 1..4 have an interrupt
  }
  // Disable interrupt corresponding to channel
  (void)manageIT(channel, DISABLE_IT);
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
  * @note   @note Refresh() can only be called after timer has been initialized,
            either by calling setup() function or thanks to constructor with TIM instance parameter.
  *         It is useful while timer is running after some registers update
  * @retval None
  */
void HardwareTimer::refresh()
{
#if defined(USE_HALV2_DRIVER)
  HAL_TIM_GenerateEvent(&(_timerObj.handle), HAL_TIM_SW_EVENT_UPD);
#else
  HAL_TIM_GenerateEvent(&(_timerObj.handle), TIM_EVENTSOURCE_UPDATE);
#endif
}

/**
  * @brief  Return the timer object handle object for more advanced setup
  * @note   Using this function and editing the Timer handle is at own risk! No support will
  *         be provided whatsoever if the HardwareTimer does not work as expected when editing
  *         the handle using the HAL functionality or other custom coding.
  * @retval TIM_HandleTypeDef or hal_tim_handle_t address
  */
#if defined(USE_HALV2_DRIVER)
  hal_tim_handle_t *HardwareTimer::getHandle()
#else
  TIM_HandleTypeDef *HardwareTimer::getHandle()
#endif
{
  return &_timerObj.handle;
}

/**
  * @brief  Generic Update (rollover) callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
#if defined(USE_HALV2_DRIVER)
  void HardwareTimer::updateCallback(hal_tim_handle_t *htim)
#else
  void HardwareTimer::updateCallback(TIM_HandleTypeDef *htim)
#endif
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
  * @brief  Generic Capture and Compare callback which will call user callback
  * @param  htim: HAL timer handle
  * @retval None
  */
#if defined(USE_HALV2_DRIVER)
  void HardwareTimer::captureCompareCallback(hal_tim_handle_t *htim, hal_tim_channel_t hal_channel)
#else
  void HardwareTimer::captureCompareCallback(TIM_HandleTypeDef *htim)
#endif
{
  if (!htim) {
    Error_Handler();
  }
#if defined(USE_HALV2_DRIVER)
  uint32_t channel = 0;
  switch (hal_channel) {
    case HAL_TIM_CHANNEL_1: {
        channel = 1;
        break;
      }
    case HAL_TIM_CHANNEL_2: {
        channel = 2;
        break;
      }
    case HAL_TIM_CHANNEL_3: {
        channel = 3;
        break;
      }
    case HAL_TIM_CHANNEL_4: {
        channel = 4;
        break;
      }
    default:
      return;
  }
#else
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
#endif
  timerObj_t *obj = get_timer_obj(htim);
  HardwareTimer *HT = (HardwareTimer *)(obj->__this);

  if (HT->callbacks[channel]) {
    HT->callbacks[channel]();
  }
}

/**
  * @brief  Check whether HardwareTimer is running (paused or resumed).
  * @retval return true if the HardwareTimer is running
  */
bool HardwareTimer::isRunning()
{
  return LL_TIM_IsEnabledCounter(_timerObj.instance);
}

/**
  * @brief  Check whether channel is running (paused or resumed).
  * @param  channel: Arduino channel [1..4]
  * @retval return true if HardwareTimer is running and the channel is enabled
  */
bool HardwareTimer::isRunningChannel(uint32_t channel)
{
  uint32_t LLChannel = getLLChannel(channel);
  bool ret;

  // channel is running if: timer is running, and either output channel is
  // enabled or interrupt is set
  ret = LL_TIM_CC_IsEnabledChannel(_timerObj.instance, LLChannel)
        || manageIT(channel, IS_ENABLE_IT);
  return (isRunning() && ret);
}

/**
  * @brief  Take into account registers update immediately if timer is not running,
  *         (independently from Preload setting)
  * @param  TIMx Timer instance
  * @retval None
  */
void HardwareTimer::updateRegistersIfNotRunning(TIM_TypeDef *TIMx)
{
  if (!isRunning()) {
    if (LL_TIM_IsEnabledIT_UPDATE(TIMx)) {
      // prevent Interrupt generation from refresh()
      LL_TIM_DisableIT_UPDATE(TIMx);
      refresh();
      LL_TIM_ClearFlag_UPDATE(TIMx);
      LL_TIM_EnableIT_UPDATE(TIMx);
    } else {
      refresh();
    }
  }
}

/**
  * @brief  HardwareTimer destructor
  * @retval None
  */
HardwareTimer::~HardwareTimer()
{
  uint32_t index = get_timer_index(_timerObj.instance);
  disableTimerClock(_timerObj.instance);
  HardwareTimer_Handle[index] = NULL;
  _timerObj.__this = NULL;
}

/**
  * @brief  return timer index from timer handle
  * @param  htim : one of the defined timer
  * @retval timer index
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
    index = TIMER22_INDEX;
  }
#endif
  if (index == UNKNOWN_TIMER) {
    Error_Handler();
  }
  return index;
}

/**
  * @brief  This function return the timer clock frequency.
  * @param  None
  * @retval frequency in Hz
  */
uint32_t HardwareTimer::getTimerClkFreq()
{
#if defined(STM32MP1xx)
  uint8_t timerClkSrc = getTimerClkSrc(_timerObj.instance);
  uint64_t clkSelection = timerClkSrc == 1 ? RCC_PERIPHCLK_TIMG1 : RCC_PERIPHCLK_TIMG2;
  return HAL_RCCEx_GetPeriphCLKFreq(clkSelection);
#elif defined(STM32WB0x) || defined(STM32WL3x)
  return SystemCoreClock;
#elif defined(STM32C5xx)
  return HAL_RCC_GetHCLKFreq();
#else
  RCC_ClkInitTypeDef    clkconfig = {};
  uint32_t              pFLatency = 0U;
  uint32_t              uwTimclock = 0U, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  switch (getTimerClkSrc(_timerObj.instance)) {
    case 1:
      uwAPBxPrescaler = clkconfig.APB1CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK1Freq();
      break;
#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32U0xx)
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
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
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
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
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
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
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
  * @param  None
  * @retval None
  */
void HardwareTimer::timerHandleDeinit()
{
#if defined(USE_HALV2_DRIVER)
  HAL_TIM_Stop_IT(&(_timerObj.handle));
  HAL_TIM_DeInit(&(_timerObj.handle));
  disableTimerClock(_timerObj.instance);
  HAL_CORTEX_NVIC_DisableIRQ(getTimerUpIrq(_timerObj.instance));
  HAL_CORTEX_NVIC_DisableIRQ(getTimerCCIrq(_timerObj.instance));
#else
  HAL_TIM_Base_Stop_IT(&(_timerObj.handle));
  HAL_TIM_Base_DeInit(&(_timerObj.handle));
#endif
}

/******************************************************************************/
/*                            TIMx IRQ HANDLER                                */
/******************************************************************************/
extern "C" {

#if defined(USE_HALV2_DRIVER)
  void HAL_TIM_InputCaptureCallback(hal_tim_handle_t *htim,
                                    hal_tim_channel_t channel)
  {
    HardwareTimer::captureCompareCallback(htim, channel);
  }
  void HAL_TIM_CompareMatchCallback(hal_tim_handle_t *htim,
                                    hal_tim_channel_t channel)
  {
    HardwareTimer::captureCompareCallback(htim, channel);
  }
  void HAL_TIM_UpdateCallback(hal_tim_handle_t *htim)
  {
    HardwareTimer::updateCallback(htim);
  }
#else
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
#endif

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
#if defined(STM32G0xx) && defined(TIM4_BASE)
    if (HardwareTimer_Handle[TIMER4_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER4_INDEX]->handle);
    }
#endif
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
#if defined(TIM13_BASE)
    if (HardwareTimer_Handle[TIMER13_INDEX]) {
      HAL_TIM_IRQHandler(&HardwareTimer_Handle[TIMER13_INDEX]->handle);
    }
#endif // TIM13_BASE
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
#if defined(HAL_FDCAN_MODULE_ENABLED) && defined(STM32G0xx) && defined(FDCAN1_BASE)
    /* FDCAN1_IT0 and FDCAN2_IT0 Interrupt */
    if ((phfdcan1) && (__HAL_GET_PENDING_IT(HAL_ITLINE_FDCAN1_IT0) != RESET)) {
      HAL_FDCAN_IRQHandler(phfdcan1);
    }
#if defined(FDCAN2_BASE)
    if ((phfdcan2) && (__HAL_GET_PENDING_IT(HAL_ITLINE_FDCAN2_IT0) != RESET)) {
      HAL_FDCAN_IRQHandler(phfdcan2);
    }
#endif
#endif
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
#if defined(HAL_FDCAN_MODULE_ENABLED) && defined(STM32G0xx) && defined(FDCAN1_BASE)
    /* FDCAN1_IT1 and FDCAN2_IT1 Interrupt */
    if ((phfdcan1) && (__HAL_GET_PENDING_IT(HAL_ITLINE_FDCAN1_IT1) != RESET)) {
      HAL_FDCAN_IRQHandler(phfdcan1);
    }
#if defined(FDCAN2_BASE)
    if ((phfdcan2) && (__HAL_GET_PENDING_IT(HAL_ITLINE_FDCAN2_IT1) != RESET)) {
      HAL_FDCAN_IRQHandler(phfdcan2);
    }
#endif
#endif
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
