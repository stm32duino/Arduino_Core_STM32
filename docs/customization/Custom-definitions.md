# Custom definitions

Several definitions can be redefined by the end user by different ways:
 * using `build_opt.h` file, see [Customize build options using build_opt.h](Customize-build-options-using-build_opt.h.md)
 * in the `variant.h` when defining the board
 * using `hal_conf_extra.h` file, see [HAL configuration](HAL-configuration.md)
 * at sketch level for `WEAK` function

## Quick links
 * [Change interrupt priority values](#change-interrupt-priority-values)
 * [Custom startup file](#custom-startup-file)
   * [Redefine the default startup file](#redefine-the-default-startup-file)
   * [Custom startup file in the variant](#custom-startup-file-in-the-variant)
 * [Custom PinMap array](#custom-pinmap-array)
 * [I2C Timing](#i2c-timing)
 * [I2C timeout in tick unit](#i2c-timeout-in-tick-unit)
 * [F_CPU](#f_cpu)
 * [Serial Rx/Tx buffer size](#serial-rxtx-buffer-size)
 * [systemclock_config](#systemclock_config)
 * [Enable UCPD dead battery behavior](#enable-ucpd-dead-battery-behavior)

## Change interrupt priority values

Default IRQ priorities are defined in the core which can be re-defined using below definitions:
* `UART_IRQ_PRIO`
* `EXTI_IRQ_PRIO`
* `I2C_IRQ_PRIO`
* `RTC_IRQ_PRIO`
* `TIM_IRQ_PRIO`
* `USBD_IRQ_PRIO`

Same for IRQ sub-priorities:
* `UART_IRQ_SUBPRIO`
* `EXTI_IRQ_SUBPRIO`
* `I2C_IRQ_SUBPRIO`
* `RTC_IRQ_SUBPRIO`
* `TIM_IRQ_SUBPRIO`
* `USBD_IRQ_SUBPRIO`

#### Example:
Using `build_opt.h`:
```C
-DUSBD_IRQ_PRIO=2 -DUSBD_IRQ_SUBPRIO=2
```

## Custom startup file

Core use a default startup file included thanks `CMSIS_STARTUP_FILE` definition:

[https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/startup_stm32yyxx.S](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/startup_stm32yyxx.S)


which is defined thanks:

[https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32_def_build.h](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32_def_build.h)

and  provided thanks the CMSIS Device from ST (in `STM32YYxx/Source/Templates/gcc/`):

[https://github.com/stm32duino/Arduino_Core_STM32/blob/main/system/Drivers/CMSIS/Device/ST](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/system/Drivers/CMSIS/Device/ST)

It is possible to redefine the `CMSIS_STARTUP_FILE` or define a custom startup file in the variant.
    
### Redefine the default startup file

Using `build_opt.h`:
```C
-DCMSIS_STARTUP_FILE=\"mystartup_file.s\"
```

Then add your `mystartup_file.s` in the sketch folder (i.e. in a tab of your sketch files).

#### Example for _Nucleo_L476RG_:

```C
-DCMSIS_STARTUP_FILE=\"startup_stm32l476xx.s\
```

### Custom startup file in the variant

It required to define `CUSTOM_STARTUP_FILE` in the `boards.txt` and add a `*.S` file in the `variant/` folder.

Syntax in the board.txt:
`xxx.build.startup_file=-DCUSTOM_STARTUP_FILE`
    
#### Example for _Nucleo_L476RG_:

`Nucleo_64.menu.pnum.NUCLEO_L476RG.build.startup_file=-DCUSTOM_STARTUP_FILE`

Then add a `*.S` file in the `variant/NUCLEO_L476RG/` folder and add guard to only build for the selected target:
```
#if defined(ARDUINO_MALYANM200_F070CB) || defined(ARDUINO_MALYANM300_F070CB)`
/* Beginning of the startup file */
...
/* End of the startup file */
#endif /* ARDUINO_MALYANM200_F070CB || ARDUINO_MALYANM300_F070CB */
```

> [!WARNING]
> file extension must be `.S` not `.s`**

## Custom PinMap array

Each variant provides a `PeripheralPins.c` including all `PinMap` arrays per STM32 peripherals: `ADC`, `I2C`, `SPI`, `TIM`, `U(S)ART`, `USB`,...

A pin can be used with several peripheral instances anyway for a dedicated project not all possibilities are required. All those possibilities used FLASH so to save some space, those arrays can be overridden at sketch level as they are defined as `WEAK`.

#### Example for the [ADC PinMap](https://github.com/stm32duino/Arduino_Core_STM32/blob/4b8fd083b9fcd14ea8a3ba7f767e9e754027430a/variants/STM32F1xx/F103R(8-B)T/PeripheralPins.c#L35-L69) of the NUCLEO_F103RB:

```C
#ifdef HAL_ADC_MODULE_ENABLED
WEAK const PinMap PinMap_ADC[] = {
  {PA_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 0, 0)}, // ADC1_IN0
  {PA_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 0, 0)}, // ADC2_IN0
  {PA_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // ADC1_IN1
  {PA_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // ADC2_IN1
  {PA_2,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // ADC1_IN2
  {PA_2_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // ADC2_IN2
  {PA_3,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 3, 0)}, // ADC1_IN3
  {PA_3_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 3, 0)}, // ADC2_IN3
  {PA_4,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 4, 0)}, // ADC1_IN4
  {PA_4_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 4, 0)}, // ADC2_IN4
  {PA_5,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 5, 0)}, // ADC1_IN5
  {PA_5_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 5, 0)}, // ADC2_IN5
  {PA_6,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 6, 0)}, // ADC1_IN6
  {PA_6_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 6, 0)}, // ADC2_IN6
  {PA_7,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 7, 0)}, // ADC1_IN7
  {PA_7_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 7, 0)}, // ADC2_IN7
  {PB_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 8, 0)}, // ADC1_IN8
  {PB_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 8, 0)}, // ADC2_IN8
  {PB_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 9, 0)}, // ADC1_IN9
  {PB_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 9, 0)}, // ADC2_IN9
  {PC_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 10, 0)}, // ADC1_IN10
  {PC_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 10, 0)}, // ADC2_IN10
  {PC_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 11, 0)}, // ADC1_IN11
  {PC_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 11, 0)}, // ADC2_IN11
  {PC_2,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 12, 0)}, // ADC1_IN12
  {PC_2_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 12, 0)}, // ADC2_IN12
  {PC_3,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 13, 0)}, // ADC1_IN13
  {PC_3_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 13, 0)}, // ADC2_IN13
  {PC_4,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 14, 0)}, // ADC1_IN14
  {PC_4_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 14, 0)}, // ADC2_IN14
  {PC_5,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 15, 0)}, // ADC1_IN15
  {PC_5_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 15, 0)}, // ADC2_IN15
  {NC,        NP,   0}
};
#endif
```

Project will uses only `PA_0` and `PA_1` for ADC. Moreover user wants `PA_0` use `ADC2`.

So, it can be redefined at sketch level to define only those pins (_-360 bytes_):
```C
const PinMap PinMap_ADC[] = {
  {PA_0,      ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 0, 0)}, // ADC2_IN0
  {PA_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // ADC1_IN1
  {NC,    NP,    0}
};
```

## I2C Timing

Some STM32 series require to compute I2C timing value for the `TIMINGR` register depending of the specific I2C clock source configuration to ensure correct I2C speed.

As this calculation of all timing values can consume huge time. By default, only the first **8** valid timing will be computed:
```C
#ifndef I2C_VALID_TIMING_NBR
#define I2C_VALID_TIMING_NBR          8U
#endif
```

It can be redefined thanks the `variant.h` or `build_opt.h` or `hal_conf_extra.h`

#### Example to compute 64 valid timing value

* Using `build_opt.h`:
```C
-DI2C_VALID_TIMING_NBR=64
```

* Using `variant.h` or `hal_conf_extra.h`:
```C
#define I2C_VALID_TIMING_NBR 64
```

> [!WARNING]
> Higher number ensure lowest clock error but require more time to compute depending of the board.

Moreover, to avoid time spent to compute the I2C timing, it can be defined in the `variant.h` or `build_opt.h` or `hal_conf_extra.h` with:

  * `I2C_TIMING_SM` for Standard Mode (100kHz)
  * `I2C_TIMING_FM` for Fast Mode (400kHz)
  * `I2C_TIMING_FMP` for Fast Mode Plus (1000kHz) 

#### Example for a **STM32F0xx** using `HSI` clock as I2C clock source, in `variant.h`:

```C
#define I2C_TIMING_SM           0x00201D2B
#define I2C_TIMING_FM           0x0010020A
```

## I2C timeout in tick unit

> [!Note]
> Since core version higher than 1.9.0.

I2C timeout in tick unit can be redefined. Default: **100**

```C
#ifndef I2C_TIMEOUT_TICK
#define I2C_TIMEOUT_TICK        100
#endif
```

It can be redefined thanks the `variant.h` or `build_opt.h` or `hal_conf_extra.h`

#### Example to decrease or increase I2C timeout in tick unit value

* Using `build_opt.h`:
```C
-DI2C_VALID_TIMING_NBR=50
```

* Using `variant.h` or `hal_conf_extra.h`:
```C
#define I2C_VALID_TIMING_NBR 120
```

## F_CPU

To avoid any issue with `F_CPU` value, it is defined by default to `SystemCoreClock` value which is updated automatically after each clock configuration update.

Some libraries use `F_CPU` at build time for conditional purpose (example [Arduino_Core_STM32/#612](https://github.com/stm32duino/Arduino_Core_STM32/issues/612)).

`F_CPU` can be redefined at build time using `build_opt.h` or `hal_conf_extra.h` then it will be possible to define it as a constant.

> [!IMPORTANT]
> user have to ensure to set it to the proper value.

## Serial Rx/Tx buffer size

By default, Serial Rx/Tx buffer size are defined like this:

```C
#if !defined(SERIAL_TX_BUFFER_SIZE)
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#define SERIAL_RX_BUFFER_SIZE 64
#endif
```

Each size can be redefined at build time using `build_opt.h` or `hal_conf_extra.h`

> [!WARNING]
> A "_power of 2_" buffer size is recommended to dramatically optimize all the modulo operations for ring buffers.

#### Example using `build_opt.h`:
```C
-DSERIAL_RX_BUFFER_SIZE=256 -DSERIAL_TX_BUFFER_SIZE=256
```

## SystemClock_Config

Each variant define a default system clock configuration anyway user can redefine his own system clock configuration at sketch level. For example to change the source clock or decrease frequency.
It is important to prefix the new function by `extern "C"` in `ino` or `cpp` file:

```C
extern "C" void SystemClock_Config() {
  // new clock config
}
```

## Enable UCPD dead battery behavior

> [!NOTE]
> Available with STM32 core version higher than 2.9.0.

By default, UCPD dead battery behavior is disabled after reset.
After user request to be able to not disable it, user can use this definition to
not disable it:

`SKIP_DISABLING_UCPD_DEAD_BATTERY`

It can be defined thanks the `variant.h`, `build_opt.h` or `hal_conf_extra.h`

> [!WARNING]
> Enable it is under user responsibility.
