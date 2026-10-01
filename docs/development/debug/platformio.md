# PlatformIO

[PlatformIO](https://platformio.org/) is an open source ecosystem for IoT development with a cross-platform IDE, unified debugger, remote unit testing, and firmware updates.

PlatformIO supports the [STM32duino core](https://github.com/stm32duino/Arduino_Core_STM32). See the [STM32 platform configuration](https://docs.platformio.org/en/latest/platforms/ststm32.html#configuration) documentation for installation, board selection, and project configuration.

For debugging, enable debug symbols in the PlatformIO project configuration and use an ST-LINK-compatible probe connected through SWD. The generated ELF file in the PlatformIO `.pio/build/<environment>/` directory is the file to select in a GDB or `cortex-debug` configuration.

> [!WARNING]
> PlatformIO is a community/tool-specific workflow and is not the officially supported STM32duino debugging path. The officially supported workflow is documented in [Arduino IDE 2](How-to-debug.md).
