To use the [Arduino_Core_STM32] git repository instead of the packaged version, follow those steps:

## 1. Install the STM32 Core packages

To get started with development on `main` branch, correct versions of the required dependencies have to be installed (see: [platform.txt](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/platform.txt)):

   * [CMSIS](https://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php): ARM® Cortex® Microcontroller Software Interface Standard 
   * [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks [The xPack GNU Arm Embedded GCC](https://xpack.github.io/arm-none-eabi-gcc/): https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack
   * [OpenOCD](https://openocd.org/):  the Open On-Chip Debugger provides on-chip programming and debugging support with a layered architecture of JTAG interface and TAP support. Packages are provided thanks [The xPack OpenOCD](https://xpack-dev-tools.github.io/openocd-xpack/): https://github.com/xpack-dev-tools/openocd-xpack
   * [STM32Tools](https://github.com/stm32duino/Arduino_Tools): upload tools for STM32 based boards and some other useful scripts
   * [stm32_svd](https://github.com/stm32duino/stm32_svd): System View Description files. It is the description of the system contained in the stm32, in particular, the memory mapped registers of peripherals.

> [!IMPORTANT]
> Using the git repository requires sometimes to update tools dependencies.
> To check if you need to install new dependencies:
>  1. open the dedicated [package index](https://arduino.github.io/arduino-cli/latest/package_index_json-specification/): [package_stmicroelectronics_index.json](https://github.com/stm32duino/BoardManagerFiles/blob/dev/package_stmicroelectronics_index.json) of the [BoardManagerFiles `dev`](https://github.com/stm32duino/BoardManagerFiles) branch.
>  2. If a version is suffixed by `-dev` it means one or more dependencies have been updated else no change done since the last release, so no need to perform a new installation. Dependencies are already satisfied.

Example when the arm-none-abi-gcc toolchain or the CMSIS version are updated. New dependencies are added in this dedicated [package index](https://arduino.github.io/arduino-cli/latest/package_index_json-specification/): [package_stmicroelectronics_index.json](https://github.com/stm32duino/BoardManagerFiles/blob/dev/package_stmicroelectronics_index.json) of the [BoardManagerFiles `dev`](https://github.com/stm32duino/BoardManagerFiles) branch. 

See the [Getting Started](../Getting-Started.md) page to see how to install the core and its tools dependencies except you have to use this link in the "Additional Boards Managers URLs" field instead of the one specified if a suffixed  `-dev` version exist to install the required dependencies for the `main` branch of the [Arduino_Core_STM32]:

https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/dev/package_stmicroelectronics_index.json

> [!IMPORTANT]
> Here, it is expected you have the core and its tools dependencies installed.

## 2. Delete the stm32 core extracted package

Go to the installed package directory, see [Where are sources](Where-are-sources.md) to find it.

Then delete the stm32 version directory:

`<Arduino IDE install directory>/packages/STMicroelectronics/hardware/stm32/<x.y.z>`.

or

`<Arduino IDE install directory>/packages/STMicroelectronics/hardware/stm32/<x.y.z-dev>`.

> [!IMPORTANT]
> There must be no other directories along side the `<x.y.z>` or `<x.y.z-dev>` directory, so don't just rename the old one. If you want to keep it, move it somewhere else entirely.
> If you do not, in "**Tools > Board**" menu, you should have twice the "**STM32 board**" menu.

## 3. Cloning the git repository to replace the stm32 core version package

Directory of step 2 is now deleted.

In the `<Arduino IDE install directory>/packages/STMicroelectronics/hardware/stm32/` do the clone:

  `git clone https://github.com/stm32duino/Arduino_Core_STM32.git <version>`

where `<version>` is the same one you deleted in step [2.](#2-delete-the-stm32-core-extracted-package)

For this example: `2.8.1`:

  `git clone https://github.com/stm32duino/Arduino_Core_STM32.git 2.8.1`

Since ArduinoCore-API has been deployed, the repository contains a git submodule.
To properly init and update the repository with the submodule do:

  `git submodule update --init`

> [!TIP]
> Of course you can use a [fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) of the [Arduino_Core_STM32] to be able to contribute and easily create [Pull Requests](https://help.github.com/articles/about-pull-requests/)

> [!TIP]
> On Linux, It is possible to clone it elsewhere and create a symlink named \<version>

> [!CAUTION]
> Uninstalling from the boards managers will remove the git repository!


[Arduino_Core_STM32]: https://github.com/stm32duino/Arduino_Core_STM32