# PlatformIO

> [!WARNING]
> The [STM32duino GitHub organization] does not officially support PlatformIO-related issues. The Arduino IDE is the officially supported development environment. This page provides a community-maintained PlatformIO reference based on [PR #1413] from [@brianredbeard].

## Install PlatformIO

Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html) for command-line use, or install the [PlatformIO IDE extension for Visual Studio Code](https://docs.platformio.org/en/latest/integration/ide/vscode.html).

Verify a command-line installation with:

```console
pio --version
```

## Create a project

PlatformIO projects use a `platformio.ini` file. A project can be created from the PlatformIO home page in Visual Studio Code, or from the command line:

```console
pio project init --board <platformio-board-id>
```

Replace `<platformio-board-id>` with the identifier from the [PlatformIO STM32 board list](https://docs.platformio.org/en/latest/boards/ststm32.html). The command creates a `platformio.ini` file and the standard project directories.

## Configure the environment

Configure the environment in `platformio.ini` with the STM32 platform, the Arduino framework, and the selected board:

```ini
[env:my_board]
platform = ststm32
board = <platformio-board-id>
framework = arduino
```

PlatformIO downloads the [ST STM32 development platform] and its dependencies. The STM32duino core is provided through the `framework-arduinostm32` package, whose PlatformIO package name is defined in [`package.json`].

The board identifier determines the MCU family, board defaults, upload protocol, and other build settings. Do not replace it with the Arduino board display name; use the identifier from the PlatformIO board list.

Optional settings can be added when they match the hardware:

```ini
upload_protocol = stlink
monitor_speed = 115200
```

The available upload protocols depend on the selected board and programmer. See the [PlatformIO upload options](https://docs.platformio.org/en/latest/projectconf/sections/env/options/upload/upload_protocol.html) documentation for details.

## Project structure

A typical PlatformIO Arduino project has this layout:

```text
project/
├── platformio.ini
├── include/
├── lib/
├── src/
└── test/
```

Place the main Arduino source file in `src/main.cpp` and include the Arduino API explicitly:

```cpp
#include <Arduino.h>

void setup() {
}

void loop() {
}
```

## Build, upload, and monitor

Run these commands from the project directory:

```console
pio run
pio run --target upload
pio device monitor
```

The same operations are available through the Build, Upload, and Monitor actions in the PlatformIO panel in Visual Studio Code. If more than one environment is defined, select the intended environment or pass it explicitly with `-e <environment>`:

```console
pio run -e my_board
pio run -e my_board --target upload
```

## Troubleshooting

- **Unknown board:** verify the `board` value against the [PlatformIO STM32 board list](https://docs.platformio.org/en/latest/boards/index.html#st-stm32).
- **Framework package is not found:** remove the incomplete PlatformIO package download and run `pio pkg install` again from the project directory.
- **ST-LINK is not detected:** verify the ST-LINK driver or udev permissions, the USB connection, and the selected `upload_protocol`.
- **Serial monitor cannot open the port:** close other applications using the port and check the port permissions on Linux.
- **`Arduino.h` cannot be found:** confirm that `framework = arduino` is set and that the source file is under `src/`.
- **The selected core version is unexpected:** check the installed PlatformIO platform and framework package versions before comparing behavior with Arduino IDE builds.

## Debugging

For debug symbols, probe setup, and PlatformIO-specific debugger configuration, see [Debugging with PlatformIO](../debug/platformio.md). PlatformIO debugging remains a community/tool-specific workflow; the officially supported debugging workflow is documented in [How to debug with Arduino IDE 2](../debug/How-to-debug.md).

The [ST STM32 development platform](https://github.com/platformio/platform-ststm32) is a PlatformIO package and should not be confused with this Arduino core repository.


[STM32duino GitHub organization]: https://github.com/stm32duino
[PlatformIO]: https://platformio.org/
[ST STM32 development platform]: https://github.com/platformio/platform-ststm32
[`package.json`]: https://github.com/stm32duino/Arduino_Core_STM32/blob/main/package.json
[@brianredbeard]: https://github.com/brianredbeard
[PR #1413]: https://github.com/stm32duino/Arduino_Core_STM32/pull/1413
