## **Watchdog Library V1.0** for Arduino

**Written by:** _Venelin Efremov_.  

### **What is the Watchdog library.**

Th Watchdog library provides an interface to the independent watchdog module (IWDG) inside STM32 chips.
The IWDG module is used in production systems to generate a reset signal to the CPU in case some
catastrophic event in causes the software to become "stuck" or unresponsive.

The IWDG module contains a count-down timer. The module would generate a reset condition when the timer reaches zero. In normal operation mode the software running on the CPU would reload the timer periodically to
prevent the reset condition from happening. However if a software bug or other error causes the CPU to execute a different code path for too long, the reload would not happen and the IWDG module would reset the CPU.

### **How to use it**
The Watchdog library is included with the STM32 core download. To add its functionality to your sketch you'll need to reference the library header file. You do this by adding an include directive to the top of your sketch.

```Arduino
#include <Watchdog.h>

void setup() {
    ...
    // Initialize the IWDG with 4 seconds timeout.
    // This would cause a CPU reset if the IWDG timer
    // is not reloaded in approximately 4 seconds.
    watchdog_init(4000);
}

void loop() {
    ...your code here...
    // make sure the code in this loop is executed in
    // less than 2 seconds to leave 50% headroom for
    // the timer reload.
    watchdog_reset();
}

```

### **Library functions**

#### **`watchdog_init(uint16_t timeout_ms)`**

The `watchdog_init()` function would initialize the IWDG hardware block.
 
The timeout_ms parameter would set the timer reset timeout. When the
timer reaches zero the hardware block would generate a reset signal
for the CPU.

When specifying timeout value plan to refresh the timer at least twice
as often. The `watchdog_reset()` operation is not expensive.

The downside of slecting a very large timeout value is that your system
may be left in a "stuck" state for too long, before the reset is
generated.

Valid timeout values are between 1ms and 32,768ms (~32.8 seconds). For
values above 4095 the timeout paramater starts to loose precision:

 | timeout value range | timeout value precision |
 | ------------------- |:-----------------------:|
 | 1 - 4096            | 1ms
 | 4097 - 8192         | 2ms
 | 8193 - 16384        | 4ms
 | 16385 - 32768       | 8ms
 
Calling the `watchdog_init()` method with value outside of the valid range
would return without initializing the watchdog timer.

**WARNING:**
*Once started the watchdog timer can not be stopped. If you are
planning to debug the live system, the watchdog timer may cause the
system to be reset while you are stopped in the debugger. Also consider
the watchdog timer implications if you are designing a system which puts
the CPU in sleep mode.*

#### **`watchdog_reset()`**

The `watchdog_reset()` function would reset the watchdog timer.

Once you have initialized the watchdog you **HAVE** to call `watchdog_reset()`
periodically to prevent the CPU being reset.

