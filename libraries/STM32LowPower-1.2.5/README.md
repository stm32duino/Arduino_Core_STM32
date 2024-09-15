# STM32LowPower
Arduino library to support STM32 Low Power.

## Requirement
 * [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32) version >= 1.3.0
 * [STM32RTC](https://github.com/stm32duino/STM32RTC)

## API

* **`void begin()`**: configure the Low Power

* **`void idle(uint32_t ms)`**: enter in idle mode
**param** ms (optional): number of milliseconds before to exit the mode. The RTC is used in alarm mode to wakeup the chip in ms milliseconds.

* **`void sleep(uint32_t ms)`**: enter in sleep mode
**param** ms (optional): number of milliseconds before to exit the mode. The RTC is used in alarm mode to wakeup the chip in ms milliseconds.

* **`void deepSleep(uint32_t ms)`**: enter in deepSleep mode
**param** ms (optional): number of milliseconds before to exit the mode. The RTC is used in alarm mode to wakeup the chip in ms milliseconds.

* **`void shutdown(uint32_t ms)`**: enter in shutdown mode
**param** ms (optional): number of milliseconds before to exit the mode. The RTC is used in alarm mode to wakeup the board in ms milliseconds.

> [!Note]
> With [STM32RTC](https://github.com/stm32duino/STM32RTC) version lower than 1.1.0, the minimum number of milliseconds is 1000 ms.**

* **`void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode, LP_Mode LowPowerMode)`**: Enable GPIO pin in interrupt mode. If the pin is a wakeup pin, it is configured as wakeup source (see board documentation).
**param** pin: pin number  
**param** callback: pointer to callback  
**param** mode: interrupt mode (HIGH, LOW, RISING, FALLING or CHANGE)
**param** LowPowerMode: Low power mode which will be used (IDLE_MODE, SLEEP_MODE, DEEP_SLEEP_MODE or SHUTDOWN_MODE). In case of SHUTDOWN_MODE only, Wakeup pin capability is activated.

* **`void enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback)`**: enable a UART peripheral in low power mode. See board documentation for low power mode compatibility.  
**param** serial: pointer to a UART  
**param** callback: pointer to a callback to call when the board is waked up.  

* **`void enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void * data)`**
attach a callback to the RTC peripheral.  
**param** rtc: pointer to RTC. Could be NULL as RTC is a Singleton.  
**param** callback: pointer to a callback to call when the board is waked up.  
**param** callback: data: optional pointer to callback data parameters (default NULL).  

* **`void enableWakeupFrom(TwoWire *wire, voidFuncPtrVoid callback)`**:
enable an I2C peripheral in low power mode. See board documentation for low power mode compatibility. **Currently not available.**  
**param** wire: pointer to I2C  
**param** callback: pointer to a callback to call when the board is waked up.  


`Begin()` function must be called at least once before `idle()`, `sleep()`, `deepSleep()` or `shutdown()` functions.  

`attachInterruptWakeup()` or `enableWakeupFrom()` functions should be called before `idle()`, `sleep()`, `deepSleep()` or `shutdown()` functions.  

> [!Important]
> * HardwareSerial used as Wakeup source will configure it to use HSI clock source even if another peripheral clock is configured.
>
> * RTC used as Wakeup source requires to have LSE or LSI as clock source. If one of them is used nothing is changed else it will configure it to use LSI clock source. One exception exists when `SHUTDOWN_MODE` is requested and `PWR_CR1_LPMS` is defined, in that case LSE is required. So, if the board does not have LSE, it will fail.
>
> * The board will restart when exit shutdown mode.

## Hardware state

* **Idle mode**: low wake-up latency (µs range) (e.g. ARM WFI). Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself.

* **sleep mode**: low wake-up latency (µs range) (e.g. ARM WFI), Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself but
higher than idle mode.

* **deep sleep mode**: medium latency (ms range), clocks are gated to reduced. Memories
and voltage supplies are retained. If supported, Peripherals wake-up is possible (UART, I2C ...).

* **shutdown mode**: high wake-up latency (possible hundereds of ms or second
timeframe), voltage supplies are cut except always-on domain, memory content
are lost and system basically reboots.

## Source

You can find the source files at  
https://github.com/stm32duino/STM32LowPower
