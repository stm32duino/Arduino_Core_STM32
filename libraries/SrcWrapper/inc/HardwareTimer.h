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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "api/Common.h"
#include "timer.h"
#include "stm32yyxx_ll_tim.h"

#if !defined(HAL_TIM_MODULE_ONLY) &&\
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)))

/** @brief Number of Arduino channels handled per timer */
#define  TIMER_CHANNELS 4    // channel5 and channel 6 are not considered here has they don't have gpio output and they don't have interrupt

/**
 * @brief Timer channel modes (output compare, PWM and input capture)
 */
typedef enum {
  TIMER_OUTPUT_DISABLED,                  // == TIM_OCMODE_TIMING           no output, useful for only-interrupt
  // Output Compare
  TIMER_OUTPUT_COMPARE_ACTIVE,            // == TIM_OCMODE_ACTIVE           pin is set high when counter == channel compare
  TIMER_OUTPUT_COMPARE_INACTIVE,          // == TIM_OCMODE_INACTIVE         pin is set low when counter == channel compare
  TIMER_OUTPUT_COMPARE_TOGGLE,            // == TIM_OCMODE_TOGGLE           pin toggles when counter == channel compare
  TIMER_OUTPUT_COMPARE_PWM1,              // == TIM_OCMODE_PWM1             pin high when counter < channel compare, low otherwise
  TIMER_OUTPUT_COMPARE_PWM2,              // == TIM_OCMODE_PWM2             pin low when counter < channel compare, high otherwise
  TIMER_OUTPUT_COMPARE_FORCED_ACTIVE,     // == TIM_OCMODE_FORCED_ACTIVE    pin always high
  TIMER_OUTPUT_COMPARE_FORCED_INACTIVE,   // == TIM_OCMODE_FORCED_INACTIVE  pin always low

  //Input capture
  TIMER_INPUT_CAPTURE_RISING,             // == TIM_INPUTCHANNELPOLARITY_RISING
  TIMER_INPUT_CAPTURE_FALLING,            // == TIM_INPUTCHANNELPOLARITY_FALLING
  TIMER_INPUT_CAPTURE_BOTHEDGE,           // == TIM_INPUTCHANNELPOLARITY_BOTHEDGE

  // Used 2 channels for a single pin. One channel in TIM_INPUTCHANNELPOLARITY_RISING another channel in TIM_INPUTCHANNELPOLARITY_FALLING.
  // Channels must be used by pair: CH1 with CH2, or CH3 with CH4
  // This mode is very useful for Frequency and Dutycycle measurement
  TIMER_INPUT_FREQ_DUTY_MEASUREMENT,

  TIMER_NOT_USED = 0xFFFF  // This must be the last item of this enum
} TimerModes_t;

// Backward compatibility
/** @brief Deprecated alias of #TIMER_OUTPUT_DISABLED */
#define TIMER_DISABLED        TIMER_OUTPUT_DISABLED
/** @brief Deprecated alias of #TIMER_OUTPUT_DISABLED */
#define TIMER_OUTPUT_COMPARE  TIMER_OUTPUT_DISABLED

/**
 * @brief Unit of the values exchanged with overflow and counter methods
 */
typedef enum {
  TICK_FORMAT, // default
  MICROSEC_FORMAT,
  HERTZ_FORMAT,
} TimerFormat_t;

/**
 * @brief Unit of the values exchanged with capture/compare methods
 */
typedef enum {
  RESOLUTION_1B_COMPARE_FORMAT = 1,  // used for Dutycycle: [0 .. 1]
  RESOLUTION_2B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 3]
  RESOLUTION_3B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 7]
  RESOLUTION_4B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 15]
  RESOLUTION_5B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 31]
  RESOLUTION_6B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 63]
  RESOLUTION_7B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 127]
  RESOLUTION_8B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 255]
  RESOLUTION_9B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 511]
  RESOLUTION_10B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 1023]
  RESOLUTION_11B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 2047]
  RESOLUTION_12B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 4095]
  RESOLUTION_13B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 8191]
  RESOLUTION_14B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 16383]
  RESOLUTION_15B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 32767]
  RESOLUTION_16B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 65535]

  TICK_COMPARE_FORMAT = 0x80, // default
  MICROSEC_COMPARE_FORMAT,
  HERTZ_COMPARE_FORMAT,
  PERCENT_COMPARE_FORMAT, // used for Dutycycle
} TimerCompareFormat_t;

/**
 * @brief Input capture filter: sampling rate and number of events needed to
 *        validate a transition
 */
typedef enum {
#if defined(USE_HALV2_DRIVER)
  // Set with hal_tim_filter_t value
  FILTER_NONE = HAL_TIM_FDIV1,
  FILTER_CKINT_N2 = HAL_TIM_FDIV1_N2,
  FILTER_CKINT_N4 = HAL_TIM_FDIV1_N4,
  FILTER_CKINT_N8 = HAL_TIM_FDIV1_N8,
  FILTER_DTS2_N6 = HAL_TIM_FDIV2_N6,
  FILTER_DTS2_N8 = HAL_TIM_FDIV2_N8,
  FILTER_DTS4_N6 = HAL_TIM_FDIV4_N6,
  FILTER_DTS4_N8 = HAL_TIM_FDIV4_N8,
  FILTER_DTS8_N6 = HAL_TIM_FDIV8_N6,
  FILTER_DTS8_N8 = HAL_TIM_FDIV8_N8,
  FILTER_DTS16_N5 = HAL_TIM_FDIV16_N5,
  FILTER_DTS16_N6 = HAL_TIM_FDIV16_N6,
  FILTER_DTS16_N8 = HAL_TIM_FDIV16_N8,
  FILTER_DTS32_N5 = HAL_TIM_FDIV32_N5,
  FILTER_DTS32_N6 = HAL_TIM_FDIV32_N6,
  FILTER_DTS32_N8 = HAL_TIM_FDIV32_N8,
#else
  FILTER_NONE = 0,  // No filter
  FILTER_CKINT_N2,  // Sampling rate is same as clock interrupt, n=2 events
  FILTER_CKINT_N4,  // Sampling rate is same as clock interrupt, n=4 events
  FILTER_CKINT_N8,  // Sampling rate is same as clock interrupt, n=8 events
  FILTER_DTS2_N6,   // Sampling rate is DTS/2, n=6 events
  FILTER_DTS2_N8,   // Sampling rate is DTS/2, n=8 events
  FILTER_DTS4_N6,   // Sampling rate is DTS/4, n=6 events
  FILTER_DTS4_N8,   // Sampling rate is DTS/4, n=8 events
  FILTER_DTS8_N6,   // Sampling rate is DTS/8, n=6 events
  FILTER_DTS8_N8,   // Sampling rate is DTS/8, n=8 events
  FILTER_DTS16_N5,  // Sampling rate is DTS/16, n=5 events
  FILTER_DTS16_N6,  // Sampling rate is DTS/16, n=6 events
  FILTER_DTS16_N8,  // Sampling rate is DTS/16, n=8 events
  FILTER_DTS32_N5,  // Sampling rate is DTS/32, n=5 events
  FILTER_DTS32_N6,  // Sampling rate is DTS/32, n=6 events
  FILTER_DTS32_N8,  // Sampling rate is DTS/32, n=8 events
#endif
} ChannelInputFilter_t;

/**
 * @brief Action to apply on a channel interrupt (see HardwareTimer::manageIT())
 */
typedef enum {
  DISABLE_IT,  // default
  ENABLE_IT,
  CLEAR_IT,
  CLEAR_AND_ENABLE_IT,
  IS_ENABLE_IT,
} ChannelITConfig_t;

#ifdef __cplusplus

#include <functional>
/** @brief Type of the user callbacks attached to timer interrupts */
using callback_function_t = std::function<void(void)>;

/* Class --------------------------------------------------------*/
/**
 * @brief Arduino-style wrapper around an STM32 general purpose/advanced timer:
 *        PWM, output compare, input capture and update/compare interrupts
 */
class HardwareTimer {
  public:
    /**
     * @brief HardwareTimer constructor: make uninitialized timer
     *        Before calling any methods, call setup to select and setup
     *        the timer to be used.
     */
    HardwareTimer();
    /**
     * @brief HardwareTimer constructor: set default configuration values
     *        The timer will be usable directly, there is no need to call
     *        setup(). Using this constructor is not recommended for
     *        global variables that are automatically initialized at
     *        startup, since this will happen to early to report any
     *        errors. Better use the argumentless constructor and call the
     *        setup() method during initialization later.
     * @param instance Timer instance ex: TIM1, ...
     */
    HardwareTimer(TIM_TypeDef *instance);
    /**
     * @brief HardwareTimer destructor
     */
    ~HardwareTimer();

    /**
     * @brief HardwareTimer setup: configuration values. Must be called
     *        exactly once before any other methods, except when an instance is
     *        passed to the constructor.
     * @param instance Timer instance ex: TIM1, ...
     */
    void setup(TIM_TypeDef *instance);

    /**
     * @brief Pause HardwareTimer: stop timer
     */
    void pause(void);
    /**
     * @brief Pause only one channel.
     *        Timer is still running but channel is disabled (output and interrupt)
     * @param channel Arduino channel [1..4]
     */
    void pauseChannel(uint32_t channel);
    /**
     * @brief Start or resume HardwareTimer: all channels are resumed,
     *        interrupts are enabled if necessary
     */
    void resume(void);
    /**
     * @brief Configure specified channel and resume/start timer
     * @param channel Arduino channel [1..4]
     */
    void resumeChannel(uint32_t channel);

    /**
     * @brief Configure hardwareTimer prescaler
     * @param prescaler Prescaler factor
     */
    void setPrescaleFactor(uint32_t prescaler);
    /**
     * @brief Retrieve prescaler from hardware register
     * @return prescaler factor
     */
    uint32_t getPrescaleFactor();

    /**
     * @brief Set overflow (rollover)
     *
     *        Note that by default, the new value will not be applied
     *        immediately, but become effective at the next update event
     *        (usually the next timer overflow). See setPreloadEnable()
     *        for controlling this behaviour.
     * @param overflow Overflow value, depends on format parameter
     * @param format Format of overflow parameter. If omitted default format
     *               is Tick
     *           TICK_FORMAT:     overflow is the number of tick for overflow
     *           MICROSEC_FORMAT: overflow is the number of microsecondes for
     *                            overflow
     *           HERTZ_FORMAT:    overflow is the frequency in hertz for overflow
     */
    void setOverflow(uint32_t overflow, TimerFormat_t format = TICK_FORMAT);
    /**
     * @brief Retrieve overflow (rollover) value from hardware register
     * @param format Format of returned value. If omitted default format is Tick
     * @return overflow depending on format value:
     *           TICK_FORMAT:     return number of tick for overflow
     *           MICROSEC_FORMAT: return number of microsecondes for overflow
     *           HERTZ_FORMAT:    return frequency in hertz for overflow
     */
    uint32_t getOverflow(TimerFormat_t format = TICK_FORMAT);

    /**
     * @brief All in one function to configure PWM
     * @param channel Arduino channel [1..4]
     * @param pin Pin name, ex PB_0
     * @param frequency PWM frequency expressed in hertz
     * @param dutycycle PWM dutycycle expressed in percentage
     * @param PeriodCallback Timer period callback (timer rollover upon update event)
     * @param CompareCallback Timer compare callback
     */
    void setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr);
    /**
     * @brief All in one function to configure PWM, using an Arduino pin number
     * @param channel Arduino channel [1..4]
     * @param pin Arduino pin number, ex D1, 1 or PA1
     * @param frequency PWM frequency expressed in hertz
     * @param dutycycle PWM dutycycle expressed in percentage
     * @param PeriodCallback Timer period callback (timer rollover upon update event)
     * @param CompareCallback Timer compare callback
     */
    void setPWM(uint32_t channel, pin_size_t pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr);

    /**
     * @brief Set timer counter value
     * @param counter Counter value, depends on format parameter
     * @param format Format of counter parameter. If omitted default format is
     *               Tick
     *           TICK_FORMAT:     counter is the number of tick
     *           MICROSEC_FORMAT: counter is the number of microsecondes
     *           HERTZ_FORMAT:    counter is the frequency in hertz
     */
    void setCount(uint32_t counter, TimerFormat_t format = TICK_FORMAT);
    /**
     * @brief Retrieve timer counter value
     * @param format Format of returned value. If omitted default format is Tick
     * @return counter value depending on format value:
     *           TICK_FORMAT:     return number of tick for counter
     *           MICROSEC_FORMAT: return number of microsecondes for counter
     *           HERTZ_FORMAT:    return frequency in hertz for counter
     */
    uint32_t getCount(TimerFormat_t format = TICK_FORMAT);

    /**
     * @brief Set channel mode: configure timer channel with specified mode on
     *        specified pin if available
     * @param channel Arduino channel [1..4]
     * @param mode Mode configuration for the channel (see TimerModes_t)
     * @param pin Pin name, ex: PB_0
     * @param filter Input capture filter (see ChannelInputFilter_t)
     */
    void setMode(uint32_t channel, TimerModes_t mode, PinName pin = NC, ChannelInputFilter_t filter = FILTER_NONE);
    /**
     * @brief Set channel mode: configure timer channel with specified mode on
     *        specified pin if available
     * @param channel Arduino channel [1..4]
     * @param mode Mode configuration for the channel (see TimerModes_t)
     * @param pin Arduino pin number, ex: D1, 1 or PA1
     * @param filter Input capture filter (see ChannelInputFilter_t)
     */
    void setMode(uint32_t channel, TimerModes_t mode, pin_size_t pin, ChannelInputFilter_t filter = FILTER_NONE);

    /**
     * @brief Retrieves channel mode configured
     * @param channel Arduino channel [1..4]
     * @return returns configured mode
     */
    TimerModes_t getMode(uint32_t channel);

    /**
     * @brief Enable or disable preloading for overflow value
     *        When disabled, changes to the overflow value take effect
     *        immediately. When enabled (the default), the value takes
     *        effect only at the next update event (typically the next overflow).
     *
     *        Note that the capture/compare register has its own preload
     *        enable bit, which is independent and enabled in PWM modes
     *        and disabled otherwise. If you need more control of that
     *        bit, you can use the HAL functions directly.
     * @param value true to enable preloading, false to disable
     */
    void setPreloadEnable(bool value);

    /**
     * @brief Retrieve Capture/Compare value
     * @param channel Arduino channel [1..4]
     * @param format Format of return value (see TimerCompareFormat_t). If
     *               omitted default format is Tick
     *           TICK_COMPARE_FORMAT:     return value is the number of tick
     *                                    for Capture/Compare value
     *           MICROSEC_COMPARE_FORMAT: return value is the number of
     *                                    microsecondes for Capture/Compare
     *                                    value
     *           HERTZ_COMPARE_FORMAT:    return value is the frequency in
     *                                    hertz for Capture/Compare value
     *           PERCENT_COMPARE_FORMAT:  return value is the dutycycle in
     *                                    percentage
     *           RESOLUTION_nB_COMPARE_FORMAT: return value is the dutycycle
     *                                    scaled on n bits [0 .. 2^n - 1]
     * @return Capture/Compare value
     */
    uint32_t getCaptureCompare(uint32_t channel, TimerCompareFormat_t format = TICK_COMPARE_FORMAT);
    /**
     * @brief Set channel Capture/Compare register
     * @param channel Arduino channel [1..4]
     * @param compare Compare value depending on format
     * @param format Format of compare parameter (see TimerCompareFormat_t). If
     *               omitted default format is Tick
     *           TICK_COMPARE_FORMAT:     compare is the number of tick
     *           MICROSEC_COMPARE_FORMAT: compare is the number of microsecondes
     *           HERTZ_COMPARE_FORMAT:    compare is the frequency in hertz
     *           PERCENT_COMPARE_FORMAT:  compare is the dutycycle in percentage
     *           RESOLUTION_nB_COMPARE_FORMAT: compare is the dutycycle scaled
     *                                    on n bits [0 .. 2^n - 1]
     */
    void setCaptureCompare(uint32_t channel, uint32_t compare, TimerCompareFormat_t format = TICK_COMPARE_FORMAT);

    /**
     * @brief Set the priority of the interrupt
     * @note Must be call before resume()
     * @param preemptPriority The pre-emption priority for the IRQn channel
     * @param subPriority The subpriority level for the IRQ channel.
     */
    void setInterruptPriority(uint32_t preemptPriority, uint32_t subPriority);

    /**
     * @brief Attach interrupt callback on update (rollover) event
     * @param callback Interrupt callback
     */
    void attachInterrupt(callback_function_t callback);
    /**
     * @brief Detach interrupt callback on update (rollover) event
     */
    void detachInterrupt();
    /**
     * @brief Checks if there's an interrupt callback attached on Rollover event
     * @return returns true if a timer rollover interrupt has already been set
     */
    bool hasInterrupt();
    /**
     * @brief Attach interrupt callback on Capture/Compare event
     * @param channel Arduino channel [1..4]
     * @param callback Interrupt callback
     */
    void attachInterrupt(uint32_t channel, callback_function_t callback);
    /**
     * @brief Detach interrupt callback on Capture/Compare event
     * @param channel Arduino channel [1..4]
     */
    void detachInterrupt(uint32_t channel);
    /**
     * @brief Checks if there's an interrupt callback attached on Capture/Compare event
     * @param channel Arduino channel [1..4]
     * @return returns true if a channel compare match interrupt has already been set
     */
    bool hasInterrupt(uint32_t channel);
    /**
     * @brief This function will reset the timer
     */
    void timerHandleDeinit();

    /**
     * @brief Generate an update event to force all registers (Autoreload,
     *        prescaler, compare) to be taken into account
     * @note Refresh() can only be called after timer has been initialized,
     *       either by calling setup() function or thanks to constructor with
     *       TIM instance parameter.
     *       It is useful while timer is running after some registers update
     */
    void refresh(void);

    /**
     * @brief This function return the timer clock frequency.
     * @return frequency in Hz
     */
    uint32_t getTimerClkFreq();

#if defined(USE_HALV2_DRIVER)
    /**
     * @brief Generic Capture and Compare callback which will call user callback
     * @param htim HAL timer handle
     * @param hal_channel HAL channel which triggered the callback
     */
    static void captureCompareCallback(hal_tim_handle_t *htim, hal_tim_channel_t hal_channel);
    /**
     * @brief Generic Update (rollover) callback which will call user callback
     * @param htim HAL timer handle
     */
    static void updateCallback(hal_tim_handle_t *htim);
#else
    /**
     * @brief Generic Capture and Compare callback which will call user callback
     * @param htim HAL timer handle
     */
    static void captureCompareCallback(TIM_HandleTypeDef *htim);
    /**
     * @brief Generic Update (rollover) callback which will call user callback
     * @param htim HAL timer handle
     */
    static void updateCallback(TIM_HandleTypeDef *htim);
#endif
    /**
     * @brief Take into account registers update immediately if timer is not
     *        running, (independently from Preload setting)
     * @param TIMx Timer instance
     */
    void updateRegistersIfNotRunning(TIM_TypeDef *TIMx);

    /**
     * @brief Check whether HardwareTimer is running (paused or resumed).
     * @return return true if the HardwareTimer is running
     */
    bool isRunning();
    /**
     * @brief Check whether channel is running (paused or resumed).
     * @param channel Arduino channel [1..4]
     * @return return true if HardwareTimer is running and the channel is enabled
     */
    bool isRunningChannel(uint32_t channel);

    // The following function(s) are available for more advanced timer options
#if defined(USE_HALV2_DRIVER)
    /**
     * @brief Return the timer object handle object for more advanced setup
     * @note Using this function and editing the Timer handle is at own risk!
     *       No support will be provided whatsoever if the HardwareTimer does
     *       not work as expected when editing the handle using the HAL
     *       functionality or other custom coding.
     * @return hal_tim_handle_t address
     */
    hal_tim_handle_t *getHandle();
    /**
     * @brief Convert arduino channel into HAL channel
     * @param channel Arduino channel [1..4]
     * @param complementary true to get the complementary (N) channel, false
     *                      for the regular one
     * @return HAL channel. Error handler called if arduino channel is invalid
     */
    hal_tim_channel_t getChannel(uint32_t channel, bool complementary = false);
#else
    /**
     * @brief Return the timer object handle object for more advanced setup
     * @note Using this function and editing the Timer handle is at own risk!
     *       No support will be provided whatsoever if the HardwareTimer does
     *       not work as expected when editing the handle using the HAL
     *       functionality or other custom coding.
     * @return TIM_HandleTypeDef address
     */
    TIM_HandleTypeDef *getHandle();
    /**
     * @brief Convert arduino channel into HAL channel
     * @param channel Arduino channel [1..4]
     * @return HAL channel. Error handler called if arduino channel is invalid
     */
    uint32_t getChannel(uint32_t channel);
#endif
    /**
     * @brief Convert arduino channel into LL channels used (regular and/or complementary)
     * @param channel Arduino channel [1..4]
     * @return LL channel. Error handler called if arduino channel is invalid
     */
    uint32_t getLLChannel(uint32_t channel);

    /**
     * @brief Handle itterupt based on arduino channel
     * @param channel Arduino channel [1..4]
     * @param config Configuration for the interrupt (enable, disable, clear,
     *               clear and disable)
     * @return true if interrupt is enabled, false otherwise
     */
    bool manageIT(uint32_t channel, ChannelITConfig_t config = DISABLE_IT);
    /**
     * @brief Get input associated channel
     *        Channel 1 and 2 are associated; channel 3 and 4 are associated
     * @param channel Arduino channel [1..4]
     * @return associated channel [1..4]. Error handler called if arduino
     *         channel is invalid
     */
    uint32_t getAssociatedChannel(uint32_t channel);

  private:
    // Store for each channel if regular, complementary or both are used
    // High part for complementary (COMPLEMENTARY_CHAN_MASK), low part for regular (REGULAR_CHAN_MASK)
    uint8_t __ChannelsUsed[TIMER_CHANNELS];
    TimerModes_t  _ChannelMode[TIMER_CHANNELS];
    timerObj_t _timerObj;
    callback_function_t callbacks[1 + TIMER_CHANNELS]; //Callbacks: 0 for update, 1-4 for channels. (channel5/channel6, if any, doesn't have interrupt)
};

extern timerObj_t *HardwareTimer_Handle[TIMER_NUM];

/**
 * @brief return timer index from timer handle
 * @param instance One of the defined timer
 * @return timer index
 */
extern timer_index_t get_timer_index(TIM_TypeDef *instance);

#endif /* __cplusplus */

#endif  // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
#endif  // HARDWARETIMER_H_
