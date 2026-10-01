# HAL configuration

Since core version 1.6.0, a default STM32 HAL configuration is provided for each STM32 series. This avoids maintaining a separate configuration file for every variant in the series.

Each required STM32 HAL configuration file is in `system/STM32YYxx/`, where `YY` is the MCU series.

## Choose a configuration method

Use the method that matches the scope of the change:

- Use `hal_conf_extra.h` for sketch-specific HAL module and configuration overrides.
- Use `hal_conf_custom.h` when the sketch must replace the complete default HAL configuration.
- Use `build_opt.h` for preprocessor definitions that can be passed as compiler options.
- Use `variant.h` only for board-package or variant-specific defaults.

For general customization guidance, see [Custom definitions](Custom-definitions.md) and [Customize build options with build_opt.h](Customize-build-options-using-build_opt.h.md).

It allows to wrap to the correct HAL configurations. Example for a STM32F2: [stm32f2xx_hal_conf.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/system/STM32F2xx/stm32f2xx_hal_conf.h)
```C
/* STM32F2xx specific HAL configuration options. */
#if __has_include("hal_conf_custom.h")
#include "hal_conf_custom.h"
#else
#if __has_include("hal_conf_extra.h")
#include "hal_conf_extra.h"
#endif
#include "stm32f2xx_hal_conf_default.h"
#endif
```
Each `stm32yyxx_hal_conf_default.h` file disables HAL modules that are not required by the core and includes the common `stm32yyxx_hal_conf.h` file available here: [cores/arduino/stm32/stm32yyxx_hal_conf.h](
https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32yyxx_hal_conf.h)

This file handles:

- Mandatory HAL modules definition, including the default list of modules to be used in the HAL driver
- HAL modules enabled by default which can be disabled
- HAL modules not defined by default

## Configuration file precedence

Place sketch-level configuration files beside the sketch `.ino` file:

```text
MySketch/
|-- MySketch.ino
|-- hal_conf_extra.h
`-- hal_conf_custom.h
```

The series-specific wrapper applies the following precedence:

1. If `hal_conf_custom.h` exists, it replaces the default HAL configuration.
2. Otherwise, if `hal_conf_extra.h` exists, it is included before the default configuration.
3. The default series configuration is used for the remaining settings.

`hal_conf_custom.h` is not an additive override. It must provide every definition required by the selected HAL configuration.

## Customize HAL or variant definitions

Extra HAL configuration can also be enabled or disabled in `variant.h` when the setting belongs to a board package. For a sketch-level change, use:

- `hal_conf_extra.h`

To replace the default configuration completely, use:

- `hal_conf_custom.h`

After changing any of these files, force a clean rebuild. In Arduino IDE 2.3.10 and later, hold **Shift** while clicking **Verify**. With Arduino CLI, use `arduino-cli compile --clean`.

## HAL modules configuration

> [!IMPORTANT]
> Below HAL modules or definitions are listed for convenience but may not be up to date. Refer to [cores/arduino/stm32/stm32yyxx_hal_conf.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32yyxx_hal_conf.h) to make sure having up to date values.

### HAL modules enabled by default
* `HAL_MODULE_ENABLED`
* `HAL_CORTEX_MODULE_ENABLED`
* `HAL_DMA_MODULE_ENABLED`: Required by other modules
* `HAL_FLASH_MODULE_ENABLED`
* `HAL_GPIO_MODULE_ENABLED`
* `HAL_PWR_MODULE_ENABLED`
* `HAL_RCC_MODULE_ENABLED`

### HAL modules enabled by default that can be disabled
* `HAL_ADC_MODULE_ENABLED`
* `HAL_I2C_MODULE_ENABLED`
* `HAL_RTC_MODULE_ENABLED`
* `HAL_SPI_MODULE_ENABLED`
* `HAL_TIM_MODULE_ENABLED`

### HAL modules not enabled by default
* `HAL_CAN_MODULE_ENABLED`
* `HAL_DAC_MODULE_ENABLED`
* `HAL_ETH_MODULE_ENABLED`
* `HAL_SD_MODULE_ENABLED`
* `HAL_QSPI_MODULE_ENABLED`

### HAL modules controlled by Arduino board menus
* `HAL_UART_MODULE_ENABLED`
* `HAL_PCD_MODULE_ENABLED`

### List of `HAL_*_MODULE_DISABLED` definition
* `HAL_ADC_MODULE_DISABLED`
* `HAL_I2C_MODULE_DISABLED`
* `HAL_RTC_MODULE_DISABLED`
* `HAL_SPI_MODULE_DISABLED`
* `HAL_TIM_MODULE_DISABLED`
* `HAL_DAC_MODULE_DISABLED`
* `HAL_EXTI_MODULE_DISABLED`: interrupt API does not used HAL EXTI module anyway API is cleaned with this
* `HAL_ETH_MODULE_DISABLED`
* `HAL_SD_MODULE_DISABLED`
* `HAL_QSPI_MODULE_DISABLED`

> [!TIP]
> Disabling unused modules can significantly reduce flash and RAM usage. Do not disable a module used by an Arduino API or another enabled library.

For example, these definitions disable unused modules in `hal_conf_extra.h`:

```c
#define HAL_ADC_MODULE_DISABLED
#define HAL_I2C_MODULE_DISABLED
```

The equivalent `build_opt.h` entries are:

```text
-DHAL_ADC_MODULE_DISABLED
-DHAL_I2C_MODULE_DISABLED
```

### Historical size example

The following measurements were made with core 2.0.0 for a Nucleo-L031K6 with 32768 bytes of flash and 8192 bytes of RAM. They are indicative only; results depend on the core, compiler, optimization settings, board variant, and enabled Arduino APIs.

| Core 2.0.0 | Flash Size(%) | RAM Size(%) |
| :---: | :---: | :---: |
| Default (Serial enabled) | 11796 (35%) | 876 (10%) |
| HAL disabled* | 5340 (16%) | 60 (0%) |
| diff size(%) | -6456 (-19%) | -716 (-9%) |

\*With all `HAL_*_MODULE_DISABLED` defined in `hal_conf_extra.h` and `Serial` disabled

## Other HAL configuration

> [!IMPORTANT]
> Below HAL configurations are listed for convenience but may not be up to date. Refer to the required default STM32 HAL configuration file `stm32yyxx_hal_conf_default.h` in `system/STM32YYxx/` (where `YY` is the MCU series) to make sure having up to date values.

### Oscillator values

Override these values only when they match the actual clock sources fitted to the board. Incorrect values can affect system timing, baud rates, timers, RTC, USB, and delay functions.

* `HSE_VALUE`: Value of the External oscillator in Hz
* `HSE_STARTUP_TIMEOUT`: Time out for HSE start up, in ms
* `MSI_VALUE`: Value of the Internal Multiple Speed oscillator in Hz
* `CSI_VALUE`: Value of the Internal oscillator in Hz
* `HSI_VALUE`: Value of the Internal High Speed oscillator in Hz
* `HSI_STARTUP_TIMEOUT`: Time out for HSI start up, in ms
* `HSI14_VALUE`: Value of the Internal High Speed oscillator for ADC in Hz. The real value may vary depending on the variations in voltage and temperature.
* `HSI48_VALUE`: Value of the Internal High Speed oscillator for USB in Hz. The real value may vary depending on the variations in voltage and temperature.
* `LSI_VALUE`: Value of the Internal Low Speed oscillator in Hz. The real value may vary depending on the variations in voltage and temperature.
* `LSI1_VALUE`: Value of the Internal Low Speed 1 oscillator in Hz. The real value may vary depending on the variations in voltage and temperature.
* `LSI2_VALUE`: Value of the Internal Low Speed 2 oscillator in Hz. The real value may vary depending on the variations in voltage and temperature.
* `LSE_VALUE`: Value of the External Low Speed oscillator in Hz
* `LSE_STARTUP_TIMEOUT`: Time out for LSE start up, in ms
* `EXTERNAL_CLOCK_VALUE`: External clock source for I2S peripheral
* `EXTERNAL_SAI1_CLOCK_VALUE`: Value of the SAI1 External clock source in Hz
* `EXTERNAL_SAI2_CLOCK_VALUE`: Value of the SAI2 External clock source in Hz

### HAL system configuration

The following HAL system configuration values can be redefined:

* `VDD_VALUE`: Value of VDD in mV
* `TICK_INT_PRIORITY`: tick interrupt priority
* `PREFETCH_ENABLE`: To enable prefetch
* `INSTRUCTION_CACHE_ENABLE`: Enable the instruction cache
* `DATA_CACHE_ENABLE`: Enable the data cache
* `USE_SPI_CRC`: Enable the CRC feature in the HAL SPI driver
* `ART_ACCLERATOR_ENABLE`: Enable the ART accelerator
* `USE_SD_TRANSCEIVER`: Enable the microSD transceiver

## Use HAL modules without Arduino ownership
STM32 peripherals have many powerful features. Some of them are used by default by the Arduino API: I2C, SPI, TIM, U(S)ART, ... and take over IRQ Handlers (ex: `TIMx_IRQHandler`) and other HAL weaked functions (ex: `HAL_XXX_MspInit()`).
For advanced user applications, it could be useful to take control of those IRQ handlers.

Since core version 1.8.0, it is possible to disable the use of selected HAL modules by the Arduino API.

Defining `HAL_PPP_MODULE_ONLY` in `build_opt.h` or `hal_conf_extra.h` allows the application to use a HAL peripheral module without having the Arduino core use that peripheral.

For example, in `hal_conf_extra.h`:

```c
#define HAL_UART_MODULE_ONLY
```

The application is then responsible for peripheral initialization, interrupt handlers, callbacks, and avoiding conflicts with Arduino libraries.

Hereafter list of possible definition:

- `HAL_UART_MODULE_ONLY`
- `HAL_TIM_MODULE_ONLY`
- `HAL_ADC_MODULE_ONLY`
- `HAL_DAC_MODULE_ONLY`
- `HAL_RTC_MODULE_ONLY`
- `HAL_PWR_MODULE_ONLY`

I2C and SPI do not require a `HAL_*_MODULE_ONLY` definition because they are used by the core only through their built-in libraries. Do not include `Wire.h` or `SPI.h` when the application must use those HAL modules directly.

## HAL assertion management

> [!NOTE]
> Requires core version 2.8.0 or later.

HAL and LL include assertions which can be enabled by defining `USE_FULL_ASSERT` in `build_opt.h`. Assertions increase code size and are normally enabled only while debugging.

By default, `assert_failed(uint8_t *file, uint32_t line)` prints the assertion location and loops forever. The example below assumes that `printf()` is connected to an initialized output. The weak `_Error_Handler(const char *msg, int val)` function can also be redefined by the application when required.

### Example at sketch level

```C++
extern "C" void assert_failed(uint8_t *file, uint32_t line) {
  // Custom code
  printf("Assert failed: %s (%lu)\n", (char *)file, line);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  assert_param(LED_BUILTIN == 0);
  pinMode(LED_BUILTIN, OUTPUT);
}
```

## HAL FDCAN for STM32G0xx series

> [!NOTE]
> Requires core version 2.8.0 or later.

The STM32G0xx series shares an IRQ with `HardwareTimer`, but the default IRQ handler did not forward the FDCAN interrupt because the core did not support FDCAN.

Since [PR #2301](https://github.com/stm32duino/Arduino_Core_STM32/pull/2301), the handler forwards the interrupt to the correct FDCAN handler.

The application must declare the `phfdcan1` and, when applicable, `phfdcan2` handles before using FDCAN:

Example:
```C
FDCAN_HandleTypeDef myhfdcan1;
FDCAN_HandleTypeDef *phfdcan1 = &myhfdcan1;
#if defined(FDCAN2_BASE)
FDCAN_HandleTypeDef *phfdcan2 = NULL;
#endif
```
