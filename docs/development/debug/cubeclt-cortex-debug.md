# Visual Studio Code + STM32CubeCLT + `cortex-debug`

These settings were extracted from the [STM32 VS Code extension](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension)'s generated launch configuration. That extension currently only supports `CMake` projects, so it is not yet appropriate for all STM32duino development use cases.

## Prerequisites

1. Download and install the latest [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html).
2. Install the [`cortex-debug`](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) extension in VS Code.
3. Build the sketch with debug information and identify the generated ELF file.
4. Restart Windows after installation so the system environment variables are reloaded.

   On Linux, you might need to define the appropriate environment variable yourself, using the correct installation path:

   ```shell
   echo "export STM32CLT_PATH=/opt/st/stm32cubeclt_<version>" >> ~/.bashrc
   ```

## Debug launch settings

Adapt the MCU, ELF path, SVD file, and tool paths to your installation and board. The example below uses an STM32H563 target and ST-LINK:

```jsonc
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug w/ ST-Link",
      "type": "cortex-debug",
      "executable": "myproject.elf",
      "request": "launch",
      "servertype": "stlink",
      "device": "STM32H563ZITx",
      "interface": "swd",
      "serialNumber": "",
      "runToEntryPoint": "main",
      "svdFile": "${env:STM32CLT_PATH}/STMicroelectronics_CMSIS_SVD/STM32H563.svd",
      "v1": false,
      "serverpath": "${env:STM32CLT_PATH}/STLink-gdb-server/bin/ST-LINK_gdbserver",
      "stm32cubeprogrammer": "${env:STM32CLT_PATH}/STM32CubeProgrammer/bin",
      "stlinkPath": "${env:STM32CLT_PATH}/STLink-gdb-server/bin/ST-LINK_gdbserver",
      "armToolchainPath": "${env:STM32CLT_PATH}/GNU-tools-for-STM32/bin",
      "gdbPath": "${env:STM32CLT_PATH}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",
      "serverArgs": [
        "-m",
        "1"
      ]
    },
    {
      "name": "Attach w/ ST-Link",
      "cwd": "${workspaceFolder}",
      "type": "cortex-debug",
      "executable": "myproject.elf",
      "request": "attach",
      "servertype": "stlink",
      "device": "STM32H563ZITx",
      "interface": "swd",
      "serialNumber": "",
      "svdFile": "${env:STM32CLT_PATH}/STMicroelectronics_CMSIS_SVD/STM32H563.svd",
      "v1": false,
      "serverpath": "${env:STM32CLT_PATH}/STLink-gdb-server/bin/ST-LINK_gdbserver",
      "stm32cubeprogrammer": "${env:STM32CLT_PATH}/STM32CubeProgrammer/bin",
      "stlinkPath": "${env:STM32CLT_PATH}/STLink-gdb-server/bin/ST-LINK_gdbserver",
      "armToolchainPath": "${env:STM32CLT_PATH}/GNU-tools-for-STM32/bin",
      "gdbPath": "${env:STM32CLT_PATH}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",
      "serverArgs": [
        "-m",
        "1"
      ]
    }
  ]
}
```

> [!NOTE]
> This configuration requires an ELF file with debug symbols. Change `device`, `svdFile`, and the STM32CubeCLT paths for the MCU and operating system being used.

> [!WARNING]
> This is a community/tool-specific workflow and is not the officially supported STM32duino debugging path. The officially supported workflow is documented in [Arduino IDE 2](How-to-debug.md).
