# HardwareTimer
<!-- vscode-markdown-toc -->
  1. [Introduction](#Introduction)
  2. [API](#API)
  3. [Usage](#Usage)
  4. [Examples](#Examples)
  5. [Dependencies](#Dependencies)
  6. [Restriction](#Restriction)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

> [!WARNING]
> Requires *Arduino_Core_STM32* version 1.7.0 or later.

##  1. <a name='Introduction'></a>Introduction

The HardwareTimer library provides access to commonly used STM32 hardware-timer features. If other features are required, they can be accessed through [STM32Cube](https://www.st.com/content/st_com/en/stm32cube-ecosystem.html) HAL/LL APIs.

This library assumes basic knowledge of STM32 hardware-timer architecture. Timers are not equivalent and do not support the same features; refer to the reference manual for your MCU.

__Example__:

- `TIM6` and `TIM7` doesn't have outpin and this is the reason why, when available, they are used to implement Tone and Servo.
- Some timers have up to 4 output channels with 4 complementary channels whereas other timers have no complementary, or have only 1 or 2 channels...

Each timer may provide several channels. All channels of the same timer share the same counter, prescaler, and overflow value, and therefore have the same period/frequency. Only their compare values, duty cycles, or capture events can differ.

> [!WARNING]
> For genericity purpose, HardwareTimer library uses all timers like a 16bits timer (even if some may be wider).

This limits the directly configured counter period and compare values to the 16-bit range. Longer periods can often be obtained by increasing the prescaler.


##  2. <a name='API'></a>API

```C++
    void pause(void);  // Pause counter and all output channels
    void pauseChannel(uint32_t channel); // Timer is still running but channel (output and interrupt) is disabled
    void resume(void); // Resume counter and all output channels
    void resumeChannel(uint32_t channel); // Resume only one channel

    void setPrescaleFactor(uint32_t prescaler); // set prescaler register (which is factor value - 1)
    uint32_t getPrescaleFactor();

    void setOverflow(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set AutoReload register depending on format provided
    uint32_t getOverflow(TimerFormat_t format = TICK_FORMAT); // return overflow depending on format provided

    void setPWM(uint32_t channel, PinName pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr); // Set all in one command freq in HZ, Duty in percentage. Including both interrupt.
    void setPWM(uint32_t channel, uint32_t pin, uint32_t frequency, uint32_t dutycycle, callback_function_t PeriodCallback = nullptr, callback_function_t CompareCallback = nullptr);

    void setCount(uint32_t val, TimerFormat_t format = TICK_FORMAT); // set timer counter to value 'val' depending on format provided
    uint32_t getCount(TimerFormat_t format = TICK_FORMAT);  // return current counter value of timer depending on format provided

    void setMode(uint32_t channel, TimerModes_t mode, PinName pin = NC, ChannelInputFilter_t filter = FILTER_NONE); // Configure timer channel with specified mode on specified pin if available
    void setMode(uint32_t channel, TimerModes_t mode, uint32_t pin, ChannelInputFilter_t filter = FILTER_NONE);

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

    // Refresh() is useful while timer is running after some registers update
    void refresh(void); // Generate update event to force all registers (Autoreload, prescaler, compare) to be taken into account

    uint32_t getTimerClkFreq();  // return timer clock frequency in Hz.

    static void captureCompareCallback(TIM_HandleTypeDef *htim); // Generic Capture and Compare callback which will call user callback
    static void updateCallback(TIM_HandleTypeDef *htim);  // Generic Update (rollover) callback which will call user callback

    // The following function(s) are available for more advanced timer options
    TIM_HandleTypeDef *getHandle();  // return the handle address for HAL related configuration
    uint32_t getChannel(uint32_t channel);
    uint32_t getLLChannel(uint32_t channel);
    uint32_t getIT(uint32_t channel);
    uint32_t getAssociatedChannel(uint32_t channel);
#if defined(TIM_CCER_CC1NE)
    bool isComplementaryChannel[TIMER_CHANNELS];
#endif
```
##  3. <a name='Usage'></a>Usage

`HardwareTimer` is a C++ class. Instantiate it with a `TIM` instance as parameter. Keep the object alive for as long as the timer is needed: a local object created inside `setup()` is destroyed when `setup()` returns. The recommended pattern is to declare a global or static object outside `setup()`:

> [!NOTE]
> Some instances are used by Servo, Tone and SoftSerial (see TIMER_SERVO, TIMER_TONE and TIMER_SERIAL) but only when they are used. Just be sure there is no conflict with your own usage.

__Example__:
```C++
// Global object: it remains available after setup() returns.
HardwareTimer timer(TIM3);  // TIM3 is an MCU hardware peripheral instance provided by CMSIS
```

If the timer must be created inside `setup()`, store it in a pointer so it remains alive after `setup()` returns:

```C++
HardwareTimer *timer;

void setup() {
    timer = new HardwareTimer(TIM3);
}
```

The STM32Examples HardwareTimer sketches use this pointer-based pattern. Do not delete the object while the timer is in use. A global or static object is generally simpler because it avoids dynamic allocation.

Then it is possible to configure mode of a channel.

> [!NOTE]
> No need to configure pin mode (output/input/AlternateFunction), it will be done automatically by HardwareTimer library.

> [!NOTE]
> Channel range [1..4], but not all timers support 4 channels.

The selected channel and pin must be a valid route for the selected timer in the board variant's `PeripheralPins.c`. A pin that works with `TIM3_CH1` on one board may not support that route on another board. Timers such as `TIM6` and `TIM7` have no GPIO output channels.

__Example__:
```C++
    timer.setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
```


> [!CAUTION]
> Since core release 2.9.0: `TIMER_DISABLED` and `TIMER_OUTPUT_COMPARE` are obsolete and replaced by `TIMER_OUTPUT_DISABLED`.

Supported Mode:
```C
typedef enum {
  TIMER_OUTPUT_DISABLED,                         // == TIM_OCMODE_TIMING           no output, useful for only-interrupt
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
```

Then it is possible to configure *PrescalerFactor*. The timer clock is divided by this factor (if the timer clock is 10 kHz and the prescaler factor is 2, the counter runs at 5 kHz).


> [!NOTE]
> Configuration of *prescaler* is automatic when using method `setOverflow` with `format == MICROSEC_FORMAT` or `format == HERTZ_FORMAT`.

> [!NOTE]
> *Prescaler* is for timer counter and thus is common to all channel.

> [!NOTE]
> *PrescalerFactor* range: [1.. 0x10000]  (Hardware register will range [0..0xFFFF]).

__Example__:
```C++
    timer.setPrescaleFactor(8);
```

Then it is possible to configure *overflow* (also called rollover or update). The timer clock and prescaler determine the counter tick frequency, while the overflow determines the shared period of all channels.

For __output__ it correspond to period or frequency.

For __input capture__ it is suggested to use max value: 0x10000 to avoid rollover before capture occurs .

> [!NOTE]
> Configuration of *prescaler* is automatic when using method `setOverflow` with `format == MICROSEC_FORMAT` or `format == HERTZ_FORMAT`.

> [!NOTE]
> *overflow* is common to all channel.

> [!NOTE]
> *Overflow* range: [1.. 0x10000] (Hardware register will range [0..0xFFFF]).

__Example__:
```C++
    timer.setOverflow(10000); // Default format is TICK_FORMAT. Rollover occurs after 10000 ticks (the counter runs from 0 to 9999)
    timer.setOverflow(10000, TICK_FORMAT);
    timer.setOverflow(10000, MICROSEC_FORMAT); // 10000 microseconds = 10 milliseconds
    timer.setOverflow(10000, HERTZ_FORMAT); // 10 kHz
```

Then it is possible to configure *CaptureCompare* (channel specific CaptureCompare register).

> [!NOTE]
> *CaptureCompare* is for one channel only.

> [!NOTE]
> *CaptureCompare* range: [0.. 0xFFFF]

__Example__:
```C++
    timer.setCaptureCompare(channel, 50); // Default format is TICK_FORMAT. 50 ticks
    timer.setCaptureCompare(channel, 50, TICK_COMPARE_FORMAT);
    timer.setCaptureCompare(channel, 50, MICROSEC_COMPARE_FORMAT); // 50 microseconds between counter reset and compare
    timer.setCaptureCompare(channel, 50, HERTZ_COMPARE_FORMAT); // 50 Hertz -> 1/50 seconds between counter reset and compare
    timer.setCaptureCompare(channel, 50, RESOLUTION_8B_COMPARE_FORMAT); // used for duty cycle: [0..255]
    timer.setCaptureCompare(channel, 50, RESOLUTION_12B_COMPARE_FORMAT); // used for duty cycle: [0..4095]
```

It is possible to attach a user callback on update interrupt (rollover) and/or on Capture/Compare interrupt.
If no channel is specified, the user callback is attach to update event.
Note that the Update Interrupt Flag (UIF) is set when an update event occurs and generates an interrupt, and is automatically cleared by the HAL driver **before** the user callback is executed. There is no need for the user callback to clear the UIF explicitly.

__Example__:
```C++
    timer.attachInterrupt(Update_IT_callback); // See the Examples section for callback patterns.
    timer.attachInterrupt(channel, Compare_IT_callback);
```

It is now time to start timer.

> [!NOTE]
> All channel of the same timer are started at the same time (as there is only 1 counter per timer).

__Example__:
```C++
    timer.resume();
```

Timer can be paused then resumed
```C++
    timer.pause();
    ...
    timer.resume();
```

Below is an example of full PWM configuration.

__Example__:
```C++
    timer.setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
    // timer.setPrescaleFactor(8); // setOverflow computes the prescaler automatically.
    timer.setOverflow(100000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
    timer.setCaptureCompare(channel, 50, PERCENT_COMPARE_FORMAT); // 50%
    timer.attachInterrupt(Update_IT_callback);
    timer.attachInterrupt(channel, Compare_IT_callback);
    timer.resume();
```

To simplify basic PWM configuration, a dedicated all-in-one API is provided.
Overflow/frequency is in hertz, dutycycle in percentage.
`setPWM()` configures the channel and starts the timer automatically. Verify that the requested pin supports the selected timer channel before calling it.

__Example__:
```C++
    timer.setPWM(channel, pin, 5, 10, NULL, NULL); // No callback required; the shorter form is equivalent.
    timer.setPWM(channel, pin, 5, 10); // 5 Hertz, 10% duty cycle
```

Some additional APIs allow to retrieve configurations:
```C++
    getPrescaleFactor();
    getOverflow();
    getCaptureCompare(); // In InputCapture mode, this method doesn't retrieve configuration   but retrieve the captured counter value
    getCount();
```

Also, to get ride of Interrupt callback:
```C++
    detachInterrupt()
```
> [!NOTE]
> Once the timer is started with the callback enabled you can disable and enable the callback through `detachInterrupt` and `attachInterrupt` freely, how many times you want. However, if the first `resume` (= timer start) is done without **before** calling `attachInterrupt`, the HardwareTimer will **not** be able to attach the interrupt later (for performance reasons the timer will be started with interrupts disabled)

If you detach and attach interrupts while the timer is running, starting from version 1.8.0, you can also know if there's a callback already attached (without the need to track it externally) through the method
```C++
    hasInterrupt()
```

### Callback rules

Timer callbacks run from interrupt handling. Keep them short and non-blocking; do not call `delay()`, perform lengthy calculations, allocate memory, or rely on serial output from a callback. Set the interrupt priority before starting the timer:

```C++
timer.setInterruptPriority(5, 0);
timer.attachInterrupt(timerCallback);
timer.resume();
```

### Applying configuration changes

When the timer is running, changes to the prescaler, overflow, or compare registers may be applied at the next update event. Use `pause()` while configuring, or call `refresh()` after the timer has been initialized when the new values must be applied immediately. `setPreloadEnable()` controls whether selected register changes are deferred until an update event.

The timer clock can be inspected when calculating timing limits:

```C++
uint32_t timerClock = timer.getTimerClkFreq();
uint32_t prescaler = timer.getPrescaleFactor();
```

### Troubleshooting

- No PWM output: verify the timer, channel, and pin route in the selected variant's `PeripheralPins.c`.
- No callback: attach the callback before the first `resume()` and verify that the timer supports the requested interrupt.
- Unexpected frequency: check `getTimerClkFreq()`, the prescaler, and the shared overflow value.
- Input capture rollover: use a sufficiently large overflow value and account for counter wraparound when calculating periods.
- Timer stops or behaves unexpectedly: check for conflicts with `Servo`, `Tone`, `SoftSerial`, or another user of the same timer.

##  4. <a name='Examples'></a>Examples
Following examples are provided in [STM32Examples](https://github.com/stm32duino/STM32Examples) library (available with Arduino Library manager):

   * [Timebase_callback.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/Timebase_callback/Timebase_callback.ino)

        This example shows how to configure HardwareTimer to execute a callback at regular interval.
        Callback toggles pin.
        Once configured, there is only CPU load for callbacks executions.

   * Alternate timebase callback simple example

```C++
HardwareTimer timer1(TIM1);

void timerCallback() {
  // Toggle led pin.
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  timer1.pause();
  timer1.setOverflow(500000, MICROSEC_FORMAT);  //set the period
  timer1.attachInterrupt(timerCallback);
  timer1.refresh();
  timer1.resume();
}

void loop() {
  // nothing to do
}
```

   * [Timebase_callback_with_parameter.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/Timebase_callback_with_parameter/Timebase_callback_with_parameter.ino)

        This example shows how to configure HardwareTimer to execute a callback with parameter at regular interval.
        Callback toggles pin.
        Once configured, there is only CPU load for callbacks executions.

   * [PWM_FullConfiguration.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/PWM_FullConfiguration/PWM_FullConfiguration.ino)

        This example shows how to fully configure a PWM with HardwareTimer.
        PWM is generated on `LED_BUILTIN` if available.
        PWM is generated by hardware: no CPU load.
        Nevertheless, in this example both interruption callback are used on Compare match (Falling edge of PWM1 mode) and update event (rising edge of PWM1 mode).
        Those call back are used to toggle a second pin: `pin2`.
        Once configured, there is only CPU load for callbacks executions.

   * [All-in-one_setPWM.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/All-in-one_setPWM/All-in-one_setPWM.ino)

        This example shows how to configure a PWM with HardwareTimer in one single function call.
        PWM is generated on `LED_BUILTIN` if available.
        No interruption callback used: PWM is generated by hardware.
        Once configured, there is no CPU load.

   * [InputCapture.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/InputCapture/InputCapture.ino)

        This example shows how to configure HardwareTimer in inputcapture to measure external signal frequency.
        Each time a rising edge is detected on the input pin, hardware will save counter value into CaptureCompare register.
        External signal (signal generator for example) should be connected to `D2`.
        Measured frequency is displayed on Serial Monitor.

   * [Frequency_Dutycycle_measurement.ino](https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/HardwareTimer/Frequency_Dutycycle_measurement/Frequency_Dutycycle_measurement.ino)

        This example shows how to configure HardwareTimer to measure external signal frequency and dutycycle.
        The input pin will be connected to 2 channel of the timer, one for rising edge the other for falling edge.
        Each time a rising edge is detected on the input pin, hardware will save counter value into one of the CaptureCompare register.
        Each time a falling edge is detected on the input pin, hardware will save counter value into the other CaptureCompare register.
        External signal (signal generator for example) should be connected to `D2`.

##  5. <a name='Dependencies'></a>Dependencies
> [!WARNING]
> Requires *Arduino_Core_STM32* version 1.7.0 or later.

*Tone*, *Servo* and *analogwrite* have been updated to use *HardwareTimer*.

New optional parameter *destruct* has been added to *noTone* to decide whether to destruct/free HardwareTimer object.
```C++
noTone(uint8_t _pin, bool destruct = false)
```
##  6. <a name= Restriction ></a> Restriction
There is a special case where period is set to its maximum value 0xFFFF and 100% duty cycle is requested.
It is not possible to achieve this from hardware point of view (except changing mode to `TIMER_OUTPUT_COMPARE_FORCED_ACTIVE`).
In this specific case there will be 1 tick (the last one) which will be LOW. Then we lose only 1 tick out of 65535 => 99,998..%
