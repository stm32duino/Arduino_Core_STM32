# Servo
<!-- vscode-markdown-toc -->
  1. [Introduction](#Introduction)
  2. [API](#API)
  3. [Implementation](#Implementation)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  1. <a name='Introduction'></a>Introduction

The Servo library allows to control upt to 12 RC (hobby) servo motors on any GPIO pin. 

##  2. <a name='API'></a>API
STM32duino Servo API is the same as Arduino Servo API:
https://docs.arduino.cc/libraries/servo/
```C++
    Servo();
    uint8_t attach(int pin, int value = DEFAULT_PULSE_WIDTH);  // attach the given pin to the next free channel, sets pinMode, set angle value, returns channel number or 0 if failure
    uint8_t attach(int pin, int min, int max, int value = DEFAULT_PULSE_WIDTH); // as above but also sets min and max values for writes.
    void detach();
    void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
    void writeMicroseconds(int value); // Write pulse width in microseconds
    int read();                        // returns current pulse width as an angle between 0 and 180 degrees
    int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
    bool attached();                   // return true if this servo is attached, otherwise false
```

##  3. <a name='Implementation'></a>Implementation

In order to be able to attach servo on any GPIO pin,  
HardwareTimer is used as time base (and not as PWM output generator),  
and signal generation will be achieved by software.  
Only one single instance of timer is used : `TIMER_SERVO`.  
`TIMER_SERVO `can be redefined with usual methods: variant.h, build_opt.h  
Up to 12 servo motors can be controlled with this timer instance.

Servo signal generation will be done within interrupt routine.  
Time base controls when signals should be set or reset.  
Each servo will be managed one after the other:  
when 1st servo pulse is finished, 2nd servo pulse starts, ...
```
           ___                                    ___
Servo1 ___|   |__________________________________|   |___
               ____                                   ____
Servo2 _______|    |_________________________________|    |__
```
> [!WARNING]
> To avoid CPU load, it is possible to use [HardwareTimer library](../../HardwareTimer-library.md) directly to control servo motors.
> But is this case, all GPIO are not eligible to control servo,
> only the GPIO that have HardwareTimer output capability.
> One timer channel is required per servo.
> Frequency should be 20ms, Pulse: between 1ms and 2ms.
