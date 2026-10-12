# How to debug

Debugging an STM32 Arduino sketch requires a debug probe, a firmware image with debug symbols, and a debugger configuration that matches the target MCU. The Arduino IDE 2 workflow is the recommended and officially supported option; the other sections describe community or tool-specific alternatives.

Before starting, verify that:

- The board is powered and the debug probe is connected to the SWD pins. ST-LINK/V2 and ST-LINK/V3 are supported by the recommended workflow.
- The selected board and upload/debug interface are supported by the tool being used.
- The sketch is compiled with debug information. In Arduino IDE 2, select **Optimize for debugging**; in other tools, use the equivalent `-g` or `Debug` build option.
- You know where the generated ELF file is located. GDB needs the ELF file to resolve symbols, even when the board was programmed with a BIN or HEX file.

> [!WARNING]
> **Only the Arduino IDE 2 is officially supported.**

## Arduino IDE 2 (Supported and recommended way)

> [!Note]
> Requires a [ST-Link/V2](https://www.st.com/content/st_com/en/products/development-tools/hardware-development-tools/hardware-development-tools-for-stm32/st-link-v2.html) or [ST-Link/V3](https://www.st.com/en/development-tools/stlink-v3set.html) device connected to the PC over USB and to the board via the SWD interface.

1. If not already done, [Getting Started](../../Getting-Started.md#install-arduinocc-ide)

2. Configure the IDE to the desired board. Here the [Nucleo L476RG](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html) which already includes a ST-Link.

  See [Getting Started](../../Getting-Started.md#configuring-ide)

3. Open the Blink sketch from the "**File> Examples > 01.Basics > Blink**".

4. Select the "**Optimize for debugging**" in the "**Sketch**" menu:

  ![Optimize for debugging](../../img/debug/arduino/OptimizeDebug.png)

5. Click the upload button

  See [Getting Started](../../Getting-Started.md#upload-methods) to change the upload method.

  ![Upload](../../img/v2/Upload.png)

6. Click the start debugging button:

  ![Start debugging](../../img/debug/arduino/startDebug.png)

  ![Debugging session](../../img/debug/arduino/debugSession.png)

> [!TIP]
> Refer to official documentation to see how [Using the Debugger](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger/#using-the-debugger).
