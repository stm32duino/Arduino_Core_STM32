# Define a dedicated board

A specific board uses the generic MCU variant as a base and adds the board's physical pin mapping, default peripherals, memory settings, and upload configuration. For example, the Nucleo-G0B1RE uses the generic `STM32G0xx/G0B1R(B-C-E)T_G0C1R(C-E)T` variant folder and adds `variant_NUCLEO_G0B1RE.h` and `variant_NUCLEO_G0B1RE.cpp`.

> [!TIP]
> The example of all the steps below is available in [PR #1398](https://github.com/stm32duino/Arduino_Core_STM32/pull/1398).

### 1 - Identify the MCU variant

Find the MCU folder and generic variant that match the board's exact MCU reference. Use the board schematic and the MCU datasheet to confirm the package, flash size, RAM size, and available pins. Complete [Define a new generic variant](generic-variant.md) first if the MCU is not already supported.

The specific board files must be placed in the matching generic variant folder:

```text
variants/
`-- STM32G0xx/
        `-- G0B1R(B-C-E)T_G0C1R(C-E)T/
                |-- variant_NUCLEO_G0B1RE.h
                `-- variant_NUCLEO_G0B1RE.cpp
```

Do not modify the generated `PinNamesVar.h`, `PeripheralPins.c`, `variant_generic.cpp`, or `variant_generic.h` files in place. They are shared by the generic and specific board variants and are automatically generated.

### 2 - Define the board pin mapping

For most boards, the easiest approach is to copy the generic variant files and rename them:

```sh
cp variant_generic.h variant_<BOARD>.h
cp variant_generic.cpp variant_<BOARD>.cpp
```

Then update the copied files using the board schematic and pinout. The generic files already contain the MCU pin definitions and the standard variant structure, so usually the main task is to reorder the Arduino pin numbers to match the board connectors and update board-specific constants such as `LED_BUILTIN` and `USER_BTN`.

For a board with an Arduino UNO R3-compatible layout, use the usual Arduino order as the starting point:

- Digital header pins `D0` through `D13`, with `D0` and `D1` normally assigned to the default serial interface.
- Analog header pins `A0` through `A5` in analog connector order.
- `D13` assigned to the board's user LED when appropriate.

The board may expose additional pins on STM32 or vendor-specific headers. Add those after the standard Arduino pins and document their connector names. Do not assume that the Arduino pin number is the same as the STM32 `PinName`; the copied variant header maps the physical `PinName` to the Arduino number.

The digital pin numbers must match the order of the `digitalPin[]` array in `variant_<BOARD>.cpp`. Analog aliases such as `A0` must point to the corresponding entries in `analogInputPin[]`. Use `PinName` values from `PinNamesVar.h` for the physical STM32 pins.

For example, an UNO R3-style board can define the board-facing aliases in `variant_<BOARD>.h`:

```cpp
#define PA9           0  // D0 / RX
#define PA10          1  // D1 / TX
#define PB3           13 // D13 / LED
#define LED_BUILTIN   PB3
```

In `variant_<BOARD>.cpp`, reorder the arrays to use the same numbering:

```cpp
const PinName digitalPin[] = {
    PA9,  // D0 / RX
    PA10, // D1 / TX
    /* D2 through D12 */
    PB3   // D13 / LED
};

const pin_size_t analogInputPin[] = {
    /* A0, A1, ... in the board connector order */
};
```

Add any board-specific `SystemClock_Config()` implementation to this file when the default generic clock configuration is not suitable. Keep the implementation compatible with the MCU family HAL and verify the required peripheral clocks against the board design.

### 3 - Configure the board-specific clock

Use [STM32CubeMX] with the exact MCU, package, and board schematic. Configure the oscillator that is physically present on the board: HSE crystal, HSE bypass, or an internal `HSI`, `CSI`, `MSI`, or `HSI48` source. Do not copy a clock function generated for a different oscillator frequency or board.

Before copying `SystemClock_Config()` into `variant_<BOARD>.cpp`, check the complete clock tree:

- Set the PLL multipliers and dividers, voltage scaling, and flash latency within the MCU reference-manual limits. Verify `SYSCLK`, `HCLK`, and every APB frequency.
- If the board uses an external oscillator whose frequency differs from the core default, define `HSE_VALUE` in the board-specific header in hertz. For example, an 8 MHz crystal requires `8000000U`. This is the oscillator frequency, not the PLL or system-clock frequency.
- Select an LPUART kernel-clock source that supports the required baud rates. For 9600 baud, check the device limits, typically `3 * 9600` through `4096 * 9600` Hz, and verify the generated `PeriphClkInit.LpuartxClockSelection`.
- Configure an exact 48 MHz source for USB FS and any other board peripheral requiring 48 MHz, such as SDIO/SDMMC where applicable. Do not assume that `HCLK` is a valid USB clock.
- Check ADC and DAC kernel-clock limits, I2C timing, timer clocks, audio clocks, FDCAN, Ethernet, RNG, and all other peripherals enabled for the board. Recalculate timing values after changing the clock tree.
- Include the required peripheral clock mux configuration from the generated CubeMX code. Remove application-only functions and retain only initialization needed by the Arduino variant.

For example, define a non-default HSE value before the HAL clock configuration is compiled:

```cpp
#ifndef HSE_VALUE
    #define HSE_VALUE 8000000U /*!< External oscillator frequency in Hz */
#endif
```

If the board uses only internal clocks, do not define `HSE_VALUE` just to use HSE. Configure CubeMX and the RCC code for the actual internal source instead.

### 4 - Board-specific peripheral pin maps

The generated `PeripheralPins.c` contains the generic peripheral routes. If the board needs a different default route, create `PeripheralPins_<BOARD>.c` and define only the required board-specific `PinMap` arrays. Protect the file with the board guard.

When this file replaces the generated peripheral map, enable `CUSTOM_PERIPHERAL_PINS` in the board entry as described below. The generated `PeripheralPins.c` is conditionally disabled when this macro is defined, preventing conflicting generic and board-specific definitions.

The source file should start and end like this:

```c
#if defined(ARDUINO_<BOARD>)

#include "Arduino.h"
#include "PeripheralPins.h"

/* Board-specific PinMap arrays. */

#endif /* ARDUINO_<BOARD> */
```

The generic arrays are commonly declared `WEAK`, so a board-specific definition can provide the default route for that board. Do not remove valid routes without checking all core features that use the affected peripheral. For a sketch-only override, see [Custom definitions](../../customization/Custom-definitions.md#custom-pinmap-array).

### 5 - Protect board-specific variant files

Use the exact uppercase `build.board` value from `boards.txt` in the guard. For example, files for `NUCLEO_G0B1RE` must use `ARDUINO_NUCLEO_G0B1RE` at the top and bottom:

```cpp
// variant_NUCLEO_G0B1RE.h
#pragma once

#if defined(ARDUINO_NUCLEO_G0B1RE)
/* Board-specific pin definitions. */
#endif /* ARDUINO_NUCLEO_G0B1RE */
```

```cpp
// variant_NUCLEO_G0B1RE.cpp
#if defined(ARDUINO_NUCLEO_G0B1RE)
#include "pins_arduino.h"

/* Board-specific digitalPin[], analogInputPin[], and clock code. */

#endif /* ARDUINO_NUCLEO_G0B1RE */
```

Apply the same guard to `PeripheralPins_<BOARD>.c`. Matching guards prevent board-specific definitions from being compiled into another board's variant.

### 6 - Add the board entry

Add the board to the appropriate menu in [`boards.txt`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/boards.txt). Keep entries in alphabetical order. A board entry normally defines:

- The menu label and `build.board` identifier.
- The `build.series`, `build.product_line`, and `build.mcu` values.
- `build.variant`, pointing to the generic variant folder.
- `build.peripheral_pins=-DCUSTOM_PERIPHERAL_PINS` when the board supplies a custom `PeripheralPins_<BOARD>.c`.
- `upload.maximum_size` and `upload.maximum_data_size` from the linker script and MCU memory.
- The upload, debug, and optional ST-LINK settings required by the board.

Example:

```ini
Nucleo_64.menu.pnum.NUCLEO_G0B1RE=Nucleo G0B1RE
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.node=NOD_G0B1RE
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.upload.maximum_size=262144
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.upload.maximum_data_size=147456
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.mcu=cortex-m0plus
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.board=NUCLEO_G0B1RE
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.series=STM32G0xx
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.product_line=STM32G0B1xx
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.variant=STM32G0xx/G0B1R(B-C-E)T_G0C1R(C-E)T
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.build.st_extra_flags=-D{build.product_line} {build.enable_usb} {build.xSerial} -D__CORTEX_SC=0
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.openocd.target=stm32g0x
Nucleo_64.menu.pnum.NUCLEO_G0B1RE.debug.svd_file={runtime.tools.STM32_SVD.path}/svd/STM32G0xx/STM32G0B1.svd
```

The `build.variant` value selects the generic variant folder; the `build.board` value selects `variant_NUCLEO_G0B1RE.h` and `variant_NUCLEO_G0B1RE.cpp` through the `ARDUINO_NUCLEO_G0B1RE` board definition.

For a board with custom peripheral pins, add the dedicated build define to the same board entry:

```ini
Disco.menu.pnum.B_G431B_ESC1.build.board=B_G431B_ESC1
Disco.menu.pnum.B_G431B_ESC1.build.peripheral_pins=-DCUSTOM_PERIPHERAL_PINS
```

`platform.txt` forwards `build.peripheral_pins` to the compiler. This define is a board build property, not a manual CMake setting; run `python3 cmake/scripts/cmake_updater_hook.py` after adding the board entry and source file.

### 7 - Document and verify the board

Add any board-specific README or documentation required by the hardware. The [Supported boards](../../supported-boards/index.md) page is generated from `boards.txt`; do not edit it manually. Add optional documentation metadata directly above the board option in `boards.txt`, then regenerate the page with `python docs/hooks/supported_boards.py` and commit the generated result.

For example:

```ini
# Docs: release=2.1.0
# Docs: url=https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html
Nucleo_64.menu.pnum.NUCLEO_G0B1RE=Nucleo G0B1RE
```

The supported metadata fields are `release`, `mcu`, `url`, and `notes`. A `release` value records the first supported core release; if it is omitted, the generator determines the first release from the Git tags, or displays `Next release` when no release tag contains the board. Use `url` for the board product page and `notes` for short user-facing information.

Build and run the [CheckVariant example](https://github.com/stm32duino/STM32Examples/tree/main/examples/NonReg/CheckVariant). Check at least the following:

- Every digital and analog pin maps to the intended board pin.
- `LED_BUILTIN`, `USER_BTN`, and default `Serial` settings work.
- The selected upload method programs and resets the board.
- The linker limits match the usable flash and RAM.
- The required peripheral pin routes are present in `PeripheralPins.c`.

Build the board with the core's normal CI or Arduino CLI checks before submitting the change.

[pin number]: ../../Pin-naming.md#arduino-pin-numbers-and-variant-aliases
[variants folder]: https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants
[Arduino boards.txt specification]: https://arduino.github.io/arduino-cli/latest/platform-specification/#boardstxt
[CheckVariant example]: https://github.com/stm32duino/STM32Examples/tree/main/examples/NonReg/CheckVariant
[Nucleo-G0B1RE]: https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html
[STM32_open_pin_data]: https://github.com/STMicroelectronics/STM32_open_pin_data
[STM32CubeMX]: http://www.st.com/en/development-tools/stm32cubemx.html
[Arduino_Core_STM32]: https://github.com/stm32duino/Arduino_Core_STM32
