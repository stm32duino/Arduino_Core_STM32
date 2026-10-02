# HAL configuration

Since core version greater than **1.5.0**, a default STM32 HAL configuration is provided per STM32 series.
As those files were almost the same for the same series, a default one per series avoid to add one for each variant.

Each required STM32 HAL configuration file is in `system/STM32YYxx/` (where `YY` is the MCU series).<br>

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
Each `stm32yyxx_hal_conf_default.h` file disabled all HAL modules and include the same `stm32yyxx_hal_conf.h` file available here: [cores/arduino/stm32/stm32yyxx_hal_conf.h](
https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32yyxx_hal_conf.h)

This file handles:
 * mandatory HAL modules definition
the default list of modules to be used in the HAL driver
 * HAL module enabled by default which can be disabled
 * HAL modules not defined by default

##### Customize HAL or variant definition
Extra HAL configuration can be enabled/disabled in `variant.h` (if required) or in a file named (at sketch level):
 * `hal_conf_extra.h`
    
Custom HAL configuration file can replace the default one by adding a file named (at sketch level):
 * `hal_conf_custom.h`

### HAL modules configuration 

> [!IMPORTANT]
> Below HAL modules or definitions are listed for convenience but may not be up to date. Refer to [cores/arduino/stm32/stm32yyxx_hal_conf.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32yyxx_hal_conf.h) to make sure having up to date values.

#### Mandatory HAL module enabled by default
* `HAL_MODULE_ENABLED`
* `HAL_CORTEX_MODULE_ENABLED`
* `HAL_DMA_MODULE_ENABLED`: Required by other modules
* `HAL_FLASH_MODULE_ENABLED`
* `HAL_GPIO_MODULE_ENABLED`
* `HAL_PWR_MODULE_ENABLED`
* `HAL_RCC_MODULE_ENABLED`

#### HAL module enabled by default which can be disabled
* `HAL_ADC_MODULE_ENABLED`
* `HAL_I2C_MODULE_ENABLED`
* `HAL_RTC_MODULE_ENABLED`
* `HAL_SPI_MODULE_ENABLED`
* `HAL_TIM_MODULE_ENABLED`

#### HAL modules not defined by default
* `HAL_CAN_MODULE_ENABLED`
* `HAL_DAC_MODULE_ENABLED`
* `HAL_ETH_MODULE_ENABLED`
* `HAL_SD_MODULE_ENABLED`
* `HAL_QSPI_MODULE_ENABLED`

#### HAL modules not defined, handled thanks Arduino menu
* `HAL_UART_MODULE_ENABLED`
* `HAL_PCD_MODULE_ENABLED`

#### List of `HAL_*_MODULE_DISABLED` definition
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
> Disable unused features can reduce significantly FLASH and RAM usage.

##### Example of `Blink.ino` for Nucleo-L031K6 with 32768 bytes of Flash and 8192 bytes of RAM:

| Core 2.0.0 | Flash Size(%) | RAM Size(%) |
| :---: | :---: | :---: |
| Default (Serial enabled) | 11796 (35%) | 876 (10%) |
| HAL disabled* | 5340 (16%) | 60 (0%) |
| diff size(%) | -6456 (-19%) | -716 (-9%) |

\*With all `HAL_*_MODULE_DISABLED` defined in `hal_conf_extra.h` and `Serial` disabled

### Other HAL configuration

> [!IMPORTANT]
> Below HAL configurations are listed for convenience but may not be up to date. Refer to the required default STM32 HAL configuration file `stm32yyxx_hal_conf_default.h` in `system/STM32YYxx/` (where `YY` is the MCU series) to make sure having up to date values.

#### Oscillator Values adaptation
Hereafter, list of possible oscillator values which can be redefined:

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
* `LSI2_VALUE`:Value of the Internal Low Speed 2 oscillator in Hz. The real value may vary depending on the variations in voltage and temperature.
* `LSE_VALUE`: Value of the External Low Speed oscillator in Hz`
* `LSE_STARTUP_TIMEOUT`: Time out for LSE start up, in ms
* `EXTERNAL_CLOCK_VALUE`: External clock source for I2S peripheral
* `EXTERNAL_SAI1_CLOCK_VALUE`: Value of the SAI1 External clock source in Hz
* `EXTERNAL_SAI2_CLOCK_VALUE`: Value of the SAI2 External clock source in Hz

#### HAL system configuration
Hereafter, list of possible HAL system configuration values which can be redefined:

* `VDD_VALUE`: Value of VDD in mv
* `TICK_INT_PRIORITY`: tick interrupt priority
* `PREFETCH_ENABLE`: To enable prefetch
* `INSTRUCTION_CACHE_ENABLE`: Use to enable I-cache
* `DATA_CACHE_ENABLE`: Use to enable D-cache
* `USE_SPI_CRC`:  Use to activate CRC feature inside HAL SPI Driver
* `ART_ACCLERATOR_ENABLE`: To enable ART Accelerator
* `USE_SD_TRANSCEIVER`: To use µSD Transceiver

# HAL module only
STM32 peripherals have many powerful features. Some of them are used by default by the Arduino API: I2C, SPI, TIM, U(S)ART, ... and take over IRQ Handlers (ex: `TIMx_IRQHandler`) and other HAL weaked functions (ex: `HAL_XXX_MspInit()`).
For advanced user applications, it could be useful to take control of those IRQ handlers. 

Since core version greater than **1.7.0**, it is possible to disable the use of the HAL modules by the Arduino API.

Defining `HAL_PPP_MODULE_ONLY` in `build_opt.h` or `hal_conf_extra.h` allows HAL peripheral (_PPP_ ) module usage without any usage by the core.

Hereafter list of possible definition:
* `HAL_UART_MODULE_ONLY`
* `HAL_TIM_MODULE_ONLY`
* `HAL_ADC_MODULE_ONLY`
* `HAL_DAC_MODULE_ONLY`
* `HAL_RTC_MODULE_ONLY`
* `HAL_PWR_MODULE_ONLY`

I2C and SPI do not required definition as used only thanks built-in library. Do not include `Wire.h` or `SPI.h` will allow to use the HAL module.

# HAL assertion management

> [!NOTE]
> Required core version higher than 2.7.1.

HAL and LL include assertions which can be enabled by defining `USE_FULL_ASSERT` in `build_opt.h`.

By default, `assert_failed(uint8_t *file, uint32_t line)` will print the assertion location (file and line) and loop forever. Print rely on `_Error_Handler(const char *msg, int val)` so it is available only when debug is enabled anyway end user can redefine it as it is a `WEAK` function.

#### Example at sketch level

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

# HAL FDCAN for STM32G0xx series

> [!NOTE]
> Required core version higher or equal to 2.8.0.

STM23G0xx series shared an irq with the `HardwareTimer` but the default irq handler did not managed the `FDCAN` one as the core does not support it.

Since https://github.com/stm32duino/Arduino_Core_STM32/pull/2301 the handler properly forward to the correct handler.

Anyway, application have to declare the `phfdcan1` and `phfdcan2` handles.

Example:
```C
FDCAN_HandleTypeDef myhfdcan1;
FDCAN_HandleTypeDef *phfdcan1 = &myhfdcan1;
#if defined(FDCAN2_BASE)
FDCAN_HandleTypeDef *phfdcan2 = NULL;
#endif
```
