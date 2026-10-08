# Custom definitions

Several core definitions can be overridden by the user. Choose the location based on the scope of the change:

| Location | Typical use | Scope |
| --- | --- | --- |
| `build_opt.h` | Compiler definitions and per-sketch options; see [Customize build options using build_opt.h](Customize-build-options-using-build_opt.h.md) | Current sketch |
| `hal_conf_extra.h` | HAL module and configuration overrides; see [HAL configuration](HAL-configuration.md) | Current sketch |
| `variant.h` | Board or variant defaults | Board package |
| Sketch-level weak override | Replacement of weak functions or arrays | Current sketch |

Prefer a sketch-level override for application-specific changes. Modify `variant.h` or board files only when maintaining a board package.

## Rebuild after changing definitions

After changing `build_opt.h`, `hal_conf_extra.h`, or another custom definition, force a clean rebuild so the Arduino IDE does not reuse previously compiled core objects. Enable verbose compilation output and look for `Build options changed, rebuilding all`.

If the output contains `Using previously compiled file:`, hold the **Shift** key while clicking the **Verify** button to run a clean compile/verify in [Arduino IDE 2.3.10 or later](https://github.com/arduino/arduino-ide/releases/tag/2.3.10). With Arduino CLI, use `arduino-cli compile --clean --fqbn <fqbn> <sketch-directory>`. You can also close and reopen the Arduino IDE or change an applicable board option before compiling again. See [Customize build options using build_opt.h](Customize-build-options-using-build_opt.h.md) for more details.

## Change interrupt priority values

The core and related STM32duino libraries define default IRQ priorities that can be overridden with the following definitions:

- `UART_IRQ_PRIO`
- `EXTI_IRQ_PRIO`
- `I2C_IRQ_PRIO`
- `RTC_IRQ_PRIO`
- `TIM_IRQ_PRIO`
- `USBD_IRQ_PRIO`
- `IPCC_IRQ_PRIO` when `VIRTIOCON` is enabled

The same applies to IRQ sub-priorities:

- `UART_IRQ_SUBPRIO`
- `EXTI_IRQ_SUBPRIO`
- `I2C_IRQ_SUBPRIO`
- `RTC_IRQ_SUBPRIO`
- `TIM_IRQ_SUBPRIO`
- `USBD_IRQ_SUBPRIO`
- `IPCC_IRQ_SUBPRIO` when `VIRTIOCON` is enabled

`RTC_IRQ_PRIO` and `RTC_IRQ_SUBPRIO` are provided by the separate [STM32RTC library](https://github.com/stm32duino/STM32RTC), not by the core itself.

#### Example

Using `build_opt.h`:

```console
-DUSBD_IRQ_PRIO=2 -DUSBD_IRQ_SUBPRIO=2
```

## Custom startup file

The core uses a default startup file selected by the `CMSIS_STARTUP_FILE` definition:

[default startup file](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/startup_stm32yyxx.S)

The definition is provided by [`stm32_def_build.h`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cores/arduino/stm32/stm32_def_build.h). The startup implementation is provided by the CMSIS device package in the [`system/Drivers/CMSIS/Device/ST/`](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/system/Drivers/CMSIS/Device/ST) directory.

You can redefine `CMSIS_STARTUP_FILE` for a sketch or define a custom startup file in a variant.

### Redefine the default startup file

Using `build_opt.h`:

```console
-DCMSIS_STARTUP_FILE=\"mystartup_file.s\"
```

Then add your `mystartup_file.s` in the sketch folder (i.e. in a tab of your sketch files).

#### Example for _Nucleo_L476RG_:

```console
-DCMSIS_STARTUP_FILE=\"startup_stm32l476xx.s\"
```

### Custom startup file in the variant

It is required to define `CUSTOM_STARTUP_FILE` in `boards.txt` and add a `*.S` file in the `variant/` folder.

Syntax in the board.txt:
`xxx.build.startup_file=-DCUSTOM_STARTUP_FILE`

#### Example for _Nucleo_L476RG_:

`Nucleo_64.menu.pnum.NUCLEO_L476RG.build.startup_file=-DCUSTOM_STARTUP_FILE`

Then add a `*.S` file in the `variant/NUCLEO_L476RG/` folder and guard it so that it is compiled only for the selected target:

```
#if defined(ARDUINO_NUCLEO_L476RG)
/* Beginning of the startup file */
...
/* End of the startup file */
#endif /* ARDUINO_NUCLEO_L476RG */
```

> [!WARNING]
> The variant startup file extension must be `.S`, not `.s`.

## Custom PinMap array

Each variant provides a `PeripheralPins.c` including `PinMap` arrays for STM32 peripherals such as `ADC`, `I2C`, `SPI`, `TIM`, `U(S)ART`, and `USB`.

A pin can be used with several peripheral instances. A dedicated project may not need all of those possibilities, and every entry consumes flash. Because these arrays are defined as `WEAK`, they can be replaced at sketch level to keep only the required entries. Replacing an array removes all entries that are not copied into the replacement.

#### Example for the [ADC PinMap](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32F1xx/F103R(8-B)H/PeripheralPins.c#L35-L68) of the NUCLEO_F103RB

```C
#ifdef HAL_ADC_MODULE_ENABLED
WEAK const PinMap PinMap_ADC[] = {
  {PA_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 0, 0)}, // ADC1_IN0
  {PA_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 0, 0)}, // ADC2_IN0
  {PA_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 1, 0)}, // ADC1_IN1
  {PA_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 1, 0)}, // ADC2_IN1
  {PA_2,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 2, 0)}, // ADC1_IN2
  {PA_2_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 2, 0)}, // ADC2_IN2
  {PA_3,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 3, 0)}, // ADC1_IN3
  {PA_3_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 3, 0)}, // ADC2_IN3
  {PA_4,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 4, 0)}, // ADC1_IN4
  {PA_4_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 4, 0)}, // ADC2_IN4
  {PA_5,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 5, 0)}, // ADC1_IN5
  {PA_5_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 5, 0)}, // ADC2_IN5
  {PA_6,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 6, 0)}, // ADC1_IN6
  {PA_6_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 6, 0)}, // ADC2_IN6
  {PA_7,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 7, 0)}, // ADC1_IN7
  {PA_7_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 7, 0)}, // ADC2_IN7
  {PB_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 8, 0)}, // ADC1_IN8
  {PB_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 8, 0)}, // ADC2_IN8
  {PB_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 9, 0)}, // ADC1_IN9
  {PB_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 9, 0)}, // ADC2_IN9
  {PC_0,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 10, 0)}, // ADC1_IN10
  {PC_0_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 10, 0)}, // ADC2_IN10
  {PC_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 11, 0)}, // ADC1_IN11
  {PC_1_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 11, 0)}, // ADC2_IN11
  {PC_2,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 12, 0)}, // ADC1_IN12
  {PC_2_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 12, 0)}, // ADC2_IN12
  {PC_4,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 14, 0)}, // ADC1_IN14
  {PC_4_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 14, 0)}, // ADC2_IN14
  {PC_5,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 15, 0)}, // ADC1_IN15
  {PC_5_ALT1, ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 15, 0)}, // ADC2_IN15
  {NC,        NP,   0}
};
#endif
```

The project uses only `PA_0` and `PA_1` for ADC, and requires `PA_0` to use `ADC2`.

It can therefore be redefined at sketch level to define only those pins, saving approximately 360 bytes in this example:
```C
const PinMap PinMap_ADC[] = {
  {PA_0,      ADC2, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 0, 0)}, // ADC2_IN0
  {PA_1,      ADC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0, 1, 0)}, // ADC1_IN1
  {NC,    NP,    0}
};
```

## I2C Timing

Some STM32 series require to compute I2C timing value for the `TIMINGR` register depending of the specific I2C clock source configuration to ensure correct I2C speed.

Calculating all timing values can take a significant amount of time. By default, only the first **8** valid timings are computed:
```C
#ifndef I2C_VALID_TIMING_NBR
#define I2C_VALID_TIMING_NBR          8U
#endif
```

It can be redefined in `variant.h`, `build_opt.h`, or `hal_conf_extra.h`.

#### Example to compute 64 valid timing values

Using `build_opt.h`:
```C
-DI2C_VALID_TIMING_NBR=64
```

Using `variant.h` or `hal_conf_extra.h`:
```C
#define I2C_VALID_TIMING_NBR 64
```

> [!WARNING]
> A higher number can reduce the clock error, but requires more computation time depending on the board.

Moreover, to avoid time spent to compute the I2C timing, it can be defined in the `variant.h` or `build_opt.h` or `hal_conf_extra.h` with:

  * `I2C_TIMING_SM` for Standard Mode (100kHz)
  * `I2C_TIMING_FM` for Fast Mode (400kHz)
  * `I2C_TIMING_FMP` for Fast Mode Plus (1000kHz)

#### Example for an **STM32F0xx** using the `HSI` clock as the I2C clock source, in `variant.h`:

```C
#define I2C_TIMING_SM           0x00201D2B
#define I2C_TIMING_FM           0x0010020A
```

## I2C timeout in tick unit

> [!Note]
> Available since core version 1.9.0.

I2C timeout in tick unit can be redefined. Default: **100**

```C
#ifndef I2C_TIMEOUT_TICK
#define I2C_TIMEOUT_TICK        100
#endif
```

It can be redefined in `variant.h`, `build_opt.h`, or `hal_conf_extra.h`.

#### Example to decrease or increase the I2C timeout in ticks

* Using `build_opt.h`:

```console
-DI2C_TIMEOUT_TICK=50
```

* Using `variant.h` or `hal_conf_extra.h`:

```C
#define I2C_TIMEOUT_TICK 120
```

## F_CPU

To avoid any issue with `F_CPU` value, it is defined by default to `SystemCoreClock` value which is updated automatically after each clock configuration update.

Some libraries use `F_CPU` at build time for conditional purpose (example [issue #612](https://github.com/stm32duino/Arduino_Core_STM32/issues/612)).

`F_CPU` can be redefined at build time using `build_opt.h` or `hal_conf_extra.h` then it will be possible to define it as a constant.

For example, in `build_opt.h`:

```console
-DF_CPU=8000000
```

> [!IMPORTANT]
> The user must set `F_CPU` to the actual compile-time frequency expected by the library. An incorrect value can cause timing or peripheral configuration errors.

## Serial Rx/Tx buffer size

By default, Serial Rx/Tx buffer sizes are defined like this:

```C
#if !defined(SERIAL_TX_BUFFER_SIZE)
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#define SERIAL_RX_BUFFER_SIZE 64
#endif
```

Each size can be redefined at build time using `build_opt.h` or `hal_conf_extra.h`. Larger buffers improve burst handling but consume RAM.

> [!WARNING]
> A "_power of 2_" buffer size is recommended to dramatically optimize all the modulo operations for ring buffers.

#### Example using `build_opt.h`:
```C
-DSERIAL_RX_BUFFER_SIZE=256 -DSERIAL_TX_BUFFER_SIZE=256
```

## SystemClock_Config

Each variant defines a default system clock configuration. The user can replace it at sketch level, for example to change the clock source or reduce the frequency. An incorrect clock configuration can affect USB, serial timing, timers, and delay functions.

Prefix the replacement function with `extern "C"` in an `.ino` or `.cpp` file:

```C
extern "C" void SystemClock_Config() {
  // new clock config
}
```

## Enable UCPD dead battery behavior

> [!NOTE]
> Available with STM32 core version higher than 2.9.0.

By default, UCPD dead battery behavior is disabled after reset.
Following a user request to preserve this behavior, you can use this definition
to avoid disabling it:

`SKIP_DISABLING_UCPD_DEAD_BATTERY`

It can be defined in `variant.h`, `build_opt.h`, or `hal_conf_extra.h`.

> [!WARNING]
> Enabling this behavior is the user's responsibility.
