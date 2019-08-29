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

#ifdef HAL_TIM_MODULE_ENABLED

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
  TICK_COMPARE_FORMAT, // default
  MICROSEC_COMPARE_FORMAT,
  HERTZ_COMPARE_FORMAT,
  PERCENT_COMPARE_FORMAT,  // used for Dutycycle
  RESOLUTION_8B_COMPARE_FORMAT,  // used for Dutycycle: [0.. 255]
  RESOLUTION_12B_COMPARE_FORMAT  // used for Dutycycle: [0.. 4095]
} TimerCompareFormat_t;

// This structure is used to be able to get HardwareTimer instance (C++ class)
// from handler (C structure) specially for interrupt management
typedef struct  {
  // Those 2 first fields must remain in this order at the beginning of the structure
  void    *__this;
  TIM_HandleTypeDef handle;
} HardwareTimerObj_t;

#ifdef __cplusplus

/* Class --------------------------------------------------------*/
class HardwareTimer {
  public:
    HardwareTimer(TIM_TypeDef *instance);
    ~HardwareTimer();  // destructor

    void pause(void);  // Pause counter and all output channels
    void resume(void); // Resume counter and all output channels

    void setPrescaleFactor(uint32_t prescaler); // set prescaler register (which is factor value - 1)
    uint32_t getPrescaleFactor();

    void setOverflow(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set AutoReload register depending on format provided
    uint32_t getOverflow(TimerFormat_t format = TICK_FORMAT); // return overflow depending on format provided

    void setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, void (*PeriodCallback)(HardwareTimer *) = NULL, void (*CompareCallback)(HardwareTimer *) = NULL); // Set all in one command freq in HZ, Duty in percentage. Including both interrup.
    void setPWM(uint32_t channel, uint32_t pin, uint32_t frequency, uint32_t dutycycle, void (*PeriodCallback)(HardwareTimer *) = NULL, void (*CompareCallback)(HardwareTimer *) = NULL);


    void setCount(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set timer counter to value 'val' depending on format provided
    uint32_t getCount(TimerFormat_t format = TICK_FORMAT);  // return current counter value of timer depending on format provided

    void setMode(uint32_t channel, TimerModes_t mode, PinName pin = NC); // Configure timer channel with specified mode on specified pin if available
    void setMode(uint32_t channel, TimerModes_t mode, uint32_t pin);

    uint32_t getCaptureCompare(uint32_t channel, TimerCompareFormat_t format = TICK_COMPARE_FORMAT); // return Capture/Compare register value of specified channel depending on format provided

    void setCaptureCompare(uint32_t channel, uint32_t compare, TimerCompareFormat_t format = TICK_COMPARE_FORMAT);  // set Compare register value of specified channel depending on format provided

    //Add interrupt to period update
    void attachInterrupt(void (*handler)(HardwareTimer *)); // Attach interrupt callback which will be called upon update event (timer rollover)
    void detachInterrupt();  // remove interrupt callback which was attached to update event
    //Add interrupt to capture/compare channel
    void attachInterrupt(uint32_t channel, void (*handler)(HardwareTimer *)); // Attach interrupt callback which will be called upon compare match event of specified channel
    void detachInterrupt(uint32_t channel);  // remove interrupt callback which was attached to compare match event of specified channel

    void timerHandleDeinit();  // Timer deinitialization

    // Refresh() can only be called after a 1st call to resume() to be sure timer is initialised.
    // It is usefull while timer is running after some registers update
    void refresh(void); // Generate update event to force all registers (Autoreload, prescaler, compare) to be taken into account


    uint32_t getTimerClkFreq();  // return timer clock frequency in Hz.

    static void captureCompareCallback(TIM_HandleTypeDef *htim); // Generic Caputre and Compare callback which will call user callback
    static void updateCallback(TIM_HandleTypeDef *htim);  // Generic Update (rollover) callback which will call user callback

  private:
    TIM_OC_InitTypeDef _channelOC[TIMER_CHANNELS];
    TIM_IC_InitTypeDef _channelIC[TIMER_CHANNELS];
    HardwareTimerObj_t _HardwareTimerObj;
    void (*callbacks[1 + TIMER_CHANNELS])(HardwareTimer *); //Callbacks: 0 for update, 1-4 for channels. (channel5/channel6, if any, doesn't have interrupt)

    int getChannel(uint32_t channel);
    void resumeChannel(uint32_t channel);
#if defined(TIM_CCER_CC1NE)
    bool isComplementaryChannel[TIMER_CHANNELS];
#endif
};

HardwareTimerObj_t *get_timer_obj(TIM_HandleTypeDef *htim);

extern HardwareTimerObj_t *HardwareTimer_Handle[TIMER_NUM];

extern timer_index_t get_timer_index(TIM_TypeDef *htim);

#endif /* __cplusplus */

#endif  // HAL_TIM_MODULE_ENABLED
#endif  // HARDWARETIMER_H_