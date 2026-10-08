# Where are the STM32 sources and tools?

Arduino IDE stores board packages and tools in its data directory. This is different from the directory that contains the Arduino IDE application.

The default Arduino data directories are:

* `~/.arduino15/` on Linux
* `~/Library/Arduino15/` on macOS
* `%LOCALAPPDATA%\Arduino15\` on Windows 10 and 11

The examples below use `<Arduino data directory>` as a placeholder. First make sure you have installed the STM32 core using the
[Arduino Boards Manager](../Getting-Started.md#about-boards-manager-concept).

## STM32 core source files

The STM32 core files can be found in:

`<Arduino data directory>/packages/STMicroelectronics/hardware/stm32/<core-version>`

> [!NOTE]
> `<core-version>` depends on the STM32 core version installed through Boards Manager. A development package may use a version ending in `-dev`.

The core directory contains files such as `cores/`, `libraries/`, `variants/`, `platform.txt`, and `boards.txt`.

## STM32 tool files

STM32 tool packages are installed below:

`<Arduino data directory>/packages/STMicroelectronics/tools/`

Common tool locations include:

* `STM32Tools/<version>/`: upload tools and helper scripts.
* `CMSIS/<version>/`: ARM CMSIS headers and device support.
* `CMSIS_DSP/<version>/`: CMSIS-DSP sources and headers, when installed.
* `CMSIS_NN/<version>/`: CMSIS-NN sources and headers, when installed.
* `STM32_SVD/<version>/svd/`: STM32 System View Description files.
* `xpack-arm-none-eabi-gcc/<version>/bin/`: the Arm GCC compiler and tools, including `arm-none-eabi-gcc` and `arm-none-eabi-gdb`.
* `xpack-openocd/<version>/bin/`: OpenOCD and its support files, when installed.

> [!NOTE]
> Tool package names and versions depend on the STM32 core release. Do not assume that all packages are installed for every board or core version.

## Finding the installed versions

On Linux or macOS, list the installed STM32 packages with:

```sh
ls <Arduino data directory>/packages/STMicroelectronics/hardware/stm32
ls <Arduino data directory>/packages/STMicroelectronics/tools
```

On Windows, open the corresponding `Arduino15\packages\STMicroelectronics` directory in File Explorer or use PowerShell:

```powershell
Get-ChildItem "$env:LOCALAPPDATA\Arduino15\packages\STMicroelectronics\tools"
```

The Boards Manager version determines the core directory name. The tool directories contain their own installed version names. Use the paths from the selected package when configuring the compiler, debugger, uploader, or SVD file.
