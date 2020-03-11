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
#include "timer.h"
#include "stm32yyxx_ll_tim.h"

#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)

#define  TIMER_CHANNELS 4    // channel5 and channel 6 are not considered here has they don't have gpio output and they don't have interrupt

typedef enum {
  TIMER_DISABLED,
  // Output Compare
  TIMER_OUTPUT_COMPARE,                   // == TIM_OCMODE_TIMING           no output, useful for only-interrupt
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

typedef enum {
  TICK_FORMAT, // default
  MICROSEC_FORMAT,
  HERTZ_FORMAT,
} TimerFormat_t;

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

#ifdef __cplusplus

#include <functional>
using callback_function_t = std::function<void(void)>;

/* Class --------------------------------------------------------*/
class HardwareTimer {
  public:
    HardwareTimer(TIM_TypeDef *instance);
    ~HardwareTimer();  // destructor

    void pause(void);  // Pause counter and all output channels
    void pauseChannel(uint32_t channel); // Timer is still running but channel (output and interrupt) is disabled
    void resume(void); // Resume counter and all output channels
    void resumeChannel(uint32_t channel); // Resume only one channel

    void setPrescaleFactor(uint32_t prescaler); // set prescaler register (which is factor value - 1)
    uint32_t getPrescaleFactor();

    void setOverflow(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set AutoReload register depending on format provided
    uint32_t getOverflow(TimerFormat_t format = TICK_FORMAT); // return overflow depending on format provided

    void setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr); // Set all in one command freq in HZ, Duty in percentage. Including both interrup.
    void setPWM(uint32_t channel, uint32_t pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr);

    void setCount(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set timer counter to value 'val' depending on format provided
    uint32_t getCount(TimerFormat_t format = TICK_FORMAT);  // return current counter value of timer depending on format provided

    void setMode(uint32_t channel, TimerModes_t mode, PinName pin = NC); // Configure timer channel with specified mode on specified pin if available
    void setMode(uint32_t channel, TimerModes_t mode, uint32_t pin);

    TimerModes_t getMode(uint32_t channel);  // Retrieve configured mode

    void setPreloadEnable(bool value); // Configure overflow preload enable setting

    uint32_t getCaptureCompare(uint32_t channel, TimerCompareFormat_t format = TICK_COMPARE_FORMAT); // return Capture/Compare register value of specified channel depending on format provided
    void setCaptureCompare(uint32_t channel, uint32_t compare, TimerCompareFormat_t format = TICK_COMPARE_FORMAT);  // set Compare register value of specified channel depending on format provided

    void setInterruptPriority(uint32_t preemptPriority, uint32_t subPriority); // set interrupt priority

    //Add interrupt to period update
    void attachInterrupt(callback_function_t callback); // Attach interrupt callback which will be called upon update event (timer rollover)
    void detachInterrupt();  // remove interrupt callback which was attached to update event
    bool hasInterrupt();  //returns true if a timer rollover interrupt has already been set
    //Add interrupt to capture/compare channel
    void attachInterrupt(uint32_t channel, callback_function_t callback); // Attach interrupt callback which will be called upon compare match event of specified channel
    void detachInterrupt(uint32_t channel);  // remove interrupt callback which was attached to compare match event of specified channel
    bool hasInterrupt(uint32_t channel);  //returns true if an interrupt has already been set on the channel compare match
    void timerHandleDeinit();  // Timer deinitialization

    // Refresh() is usefull while timer is running after some registers update
    void refresh(void); // Generate update event to force all registers (Autoreload, prescaler, compare) to be taken into account

    uint32_t getTimerClkFreq();  // return timer clock frequency in Hz.

    static void captureCompareCallback(TIM_HandleTypeDef *htim); // Generic Caputre and Compare callback which will call user callback
    static void updateCallback(TIM_HandleTypeDef *htim);  // Generic Update (rollover) callback which will call user callback

    // The following function(s) are available for more advanced timer options
    TIM_HandleTypeDef *getHandle();  // return the handle address for HAL related configuration
    int getChannel(uint32_t channel);
    int getLLChannel(uint32_t channel);
    int getIT(uint32_t channel);
    int getAssociatedChannel(uint32_t channel);
#if defined(TIM_CCER_CC1NE)
    bool isComplementaryChannel[TIMER_CHANNELS];
#endif
  private:
    TimerModes_t  _ChannelMode[TIMER_CHANNELS];
    timerObj_t _timerObj;
    callback_function_t callbacks[1 + TIMER_CHANNELS]; //Callbacks: 0 for update, 1-4 for channels. (channel5/channel6, if any, doesn't have interrupt)
};

extern timerObj_t *HardwareTimer_Handle[TIMER_NUM];

extern timer_index_t get_timer_index(TIM_TypeDef *htim);

#endif /* __cplusplus */

#endif  // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
#endif  // HARDWARETIMER_H_
