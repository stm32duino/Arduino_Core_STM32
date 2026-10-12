# Visual Studio and VisualGDB

[VisualGDB](https://visualgdb.com/) provides an Arduino project workflow and integrated debugging from [Visual Studio](https://visualstudio.microsoft.com).

The [VisualGDB STM32 Arduino tutorial](https://visualgdb.com/tutorials/arduino/stm32/) describes how to create a project using the [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32), select an STM32 board, upload the sketch, and start a debug session.

Use an ST-LINK-compatible probe connected to the board through SWD and build with debug information enabled. Select the generated ELF file when configuring the debugger.

> [!WARNING]
> VisualGDB is a community/tool-specific workflow and is not the officially supported STM32duino debugging path. The officially supported workflow is documented in [Arduino IDE 2](How-to-debug.md).
