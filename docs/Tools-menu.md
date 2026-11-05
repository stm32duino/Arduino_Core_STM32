# Tools menu options

Depending on the selected board, some of the following options are available in the "**Tools**" menu.

For the upload method, see [Upload methods](Upload-methods.md).

## U(S)ART support
Menu: "**Tools > U(S)ART support**"

| Option | Description |
|--------|-------------|
| Enabled (generic 'Serial') | U(S)ART support is enabled and the generic `Serial` object is available. It is mapped to the board's default serial interface (e.g. the ST-LINK virtual COM port on Nucleo boards). |
| Enabled (no generic 'Serial') | U(S)ART support is enabled (`-DHAL_UART_MODULE_ENABLED -DHWSERIAL_NONE`) but the generic `Serial` is not defined. Instances have to be created by the user (e.g. `Uart Serial2(PA3, PA2);`). |
| Disabled (No Serial support) | U(S)ART support is disabled. Reduces the code size when serial is not used. |

## USB support
Menu: "**Tools > USB support (if available)**"

| Option | Description |
|--------|-------------|
| None | USB is not enabled. |
| CDC (generic 'Serial' supersede U(S)ART) | USB CDC (virtual COM port) is enabled (`-DUSBD_USE_CDC`) and the generic `Serial` is mapped to USB instead of the U(S)ART. |
| CDC (no generic 'Serial') | USB CDC is enabled (`-DUSBD_USE_CDC -DDISABLE_GENERIC_SERIALUSB`) and the generic `Serial` is not mapped to USB. Use the `SerialUSB` object instead. |
| HID (keyboard and mouse) | USB HID composite device is enabled (`-DUSBD_USE_HID_COMPOSITE`). |

> [!WARNING]
> When USB is enabled, the USB pins (e.g. `PA11`/`PA12`, and potentially others such as `PA13`) are configured by the USB initialization. This may conflict with the SWD/JTAG pins and prevent debug from being functional.
> See the [Debug](FAQ.md#debug) section of the FAQ for more details and how to avoid it.

### USB speed
Menu: "**Tools > USB speed (if available)**"

Only available on boards with a High Speed capable USB peripheral.

| Option | Description |
|--------|-------------|
| Low/Full Speed | USB runs in Low/Full Speed mode (default). |
| High Speed | USB runs in High Speed mode (`-DUSE_USB_HS`). |
| High Speed in Full Speed mode | High Speed peripheral used in Full Speed mode (`-DUSE_USB_HS -DUSE_USB_HS_IN_FS`). |

## Virtual serial support
Menu: "**Tools > Virtual serial support**"

Only available for STM32MP1 boards.

| Option | Description |
|--------|-------------|
| Disabled (no SerialVirtIO nor /dev/ttyRPMSG0 available) | VirtIO serial is disabled. |
| SerialVirtIO (= generic 'Serial') <=> /dev/ttyRPMSG0 | VirtIO serial is enabled and the generic `Serial` is mapped to it. |
| SerialVirtIO <=> /dev/ttyRPMSG0 | VirtIO serial is enabled (`-DDISABLE_GENERIC_SERIALVIRTIO`), the generic `Serial` is not mapped to it. |

## Optimize
Menu: "**Tools > Optimize**"

Sets the compiler optimization level. The `LTO` variants enable link time optimization (`-flto`), which can reduce the code size and improve performance but increases the build time.

| Option | Compiler flags |
|--------|----------------|
| Smallest (-Os default) | `-Os` |
| Smallest (-Os) with LTO | `-Os -flto` |
| Fast (-O1) | `-O1` |
| Fast (-O1) with LTO | `-O1 -flto` |
| Faster (-O2) | `-O2` |
| Faster (-O2) with LTO | `-O2 -flto` |
| Fastest (-O3) | `-O3` |
| Fastest (-O3) with LTO | `-O3 -flto` |
| Debug (-Og) | `-Og` |
| No Optimization (-O0) | `-O0` |

## Debug symbols and core logs
Menu: "**Tools > Debug symbols and core logs**"

| Option | Compiler flags | Description |
|--------|----------------|-------------|
| None | `-DNDEBUG` (default) | No debug symbols, core logs disabled. |
| Symbols Enabled (-g) | `-g -DNDEBUG` | Debug symbols are generated, needed to debug with a debugger (e.g. through SWD). Core logs are disabled. |
| Core logs Enabled | _(`NDEBUG` not defined)_ | Core logs are enabled. No debug symbols. |
| Core Logs and Symbols Enabled (-g) | `-g` | Debug symbols are generated and core logs are enabled. |

## C Runtime Library
Menu: "**Tools > C Runtime Library**"

Selects the Newlib C library variant used at link time. By default the size optimized "nano" version is used, which does not support floating point in `printf()`/`scanf()` family functions.

| Option | Linker flags | Description |
|--------|--------------|-------------|
| Newlib Nano (default) | `--specs=nano.specs` | Size optimized C library, no float support in `printf`/`scanf`. |
| Newlib Nano + Float Printf | `--specs=nano.specs -u _printf_float` | Adds float support to `printf`. |
| Newlib Nano + Float Scanf | `--specs=nano.specs -u _scanf_float` | Adds float support to `scanf`. |
| Newlib Nano + Float Printf/Scanf | `--specs=nano.specs -u _printf_float -u _scanf_float` | Adds float support to both `printf` and `scanf`. |
| Newlib Standard | _(none)_ | Standard C library, full featured but larger. |
