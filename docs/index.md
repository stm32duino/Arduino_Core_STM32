# Home

The [STM32duino GitHub organization](https://github.com/stm32duino) is an open-source community developing software and libraries for using STM32 microcontrollers with Arduino. ST contributes to the community, but STM32duino is not part of ST's officially supported software ecosystem.

The organization maintains the [Arduino core for STM32-based boards](https://github.com/stm32duino/Arduino_Core_STM32), upload tools, and related libraries. This site documents the core and its libraries, including setup, supported boards, APIs, and customization.

## Get started

Since core version 2.8.0, only Arduino IDE 2 is supported. Choose the setup guide for your core version:

- [Install with Arduino IDE 2 (core 2.8.0 and newer)](Getting-Started.md)
- [Install with Legacy Arduino IDE 1.8.x (core versions before 2.8.0)](Getting-Started_V1.md)

After installation, try the [Blink example](examples/Blink-example.md). For help choosing how to program your board, see [Upload methods](Upload-methods.md).

## Find reference information

- [Supported boards](supported-boards/index.md)
- [Arduino API reference](API.md)
- [Libraries](libraries/index.md), including built-in, dedicated, and expansion-board libraries
- [Hosted library API documentation](libraries/Hosted-library-documentation.md)

## Develop and customize

- [Build from the Git repository](development/Using-git-repository.md)
- [Add support for a board variant](development/Add-a-new-variant/overview.md)
- [Customize build options](customization/Customize-build-options-using-build_opt.h.md) and [HAL configuration](customization/HAL-configuration.md)
- [Create a custom board based on an existing core](customization/Custom-board-based-on-a-core.md)
- [Debug a sketch](development/debug/How-to-debug.md)
- [Use CMake](cmake/Introduction-to-CMake.md)

## Connectivity

- [STM32duinoBLE](libraries/STM32duinoBLE.md)
- [LoRa](libraries/LoRa.md)

## Troubleshooting and support

- Check the [FAQ](FAQ.md) for common problems.

- For problems downloading or installing a board package, [report an issue in BoardManagerFiles](https://github.com/stm32duino/BoardManagerFiles/issues/new).

- For core or upload-tool problems, report an issue in the relevant repository:

- [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32/issues/new)
- [Arduino_Tools](https://github.com/stm32duino/Arduino_Tools/issues/new)

- For a library problem, open an issue in that library's source repository; find its link on the [Libraries](libraries/index.md) page.

- For community questions, visit the [STM32duino forum](http://stm32duino.com):

- [STM32 Core questions](http://stm32duino.com/viewforum.php?f=48)
- [STM32 Core bugs and enhancements](http://stm32duino.com/viewforum.php?f=49)

## External resources

- [Arduino official website](https://www.arduino.cc/)
- [STM32 microcontrollers](http://www.st.com/en/microcontrollers/stm32-32-bit-arm-cortex-mcus.html)
