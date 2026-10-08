# Development environments

The STM32 Arduino core can be used with several development environments. **Arduino IDE 2 is the officially supported environment**; the other workflows are provided for specific tools or community use cases.

## Arduino IDE 2

Use [Arduino IDE 2](../../Getting-Started.md) to install the STM32 core, select a board, compile sketches, and upload firmware. For debugging, follow the [Arduino IDE 2 debugging guide](../debug/How-to-debug.md).

## PlatformIO

[PlatformIO](PlatformIO.md) provides a project-based workflow with command-line tools, Visual Studio Code integration, build automation, and support for multiple environments. It is community-supported by the STM32duino project.

See the [PlatformIO setup guide](PlatformIO.md) and the [PlatformIO debugging guide](../debug/platformio.md).

## Other workflows

Some tools are documented for specific development or debugging workflows:

- [Eclipse and Sloeber](../debug/eclipse-sloeber.md) provides an Eclipse-based Arduino workflow.
- [Visual Studio and VisualGDB](../debug/visualgdb.md) provides a VisualGDB-based workflow.
- [Visual Studio Code with STM32CubeCLT and `cortex-debug`](../debug/cubeclt-cortex-debug.md) documents a CMake-based debugging workflow.
- [STM32CubeIDE with CMake](../../cmake/cubeIDE.md) documents CMake project integration.
- [Command-line GDB](../debug/command-line-gdb.md) documents debugging without an IDE.

These workflows may require different project types, debuggers, toolchains, or upload tools. Check each guide's support notes and prerequisites before choosing one.

> [!WARNING]
> Only Arduino IDE 2 is officially supported by the STM32duino project. Questions about other environments should generally be directed to the documentation and support channels for those tools.
