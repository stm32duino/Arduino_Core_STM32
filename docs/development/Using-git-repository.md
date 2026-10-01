# Using the Git Repository

To use the [Arduino_Core_STM32] Git repository instead of the packaged version, follow these steps. This replaces the installed STM32 core while keeping the Arduino IDE and its tools installed.

The STM32 core is installed in the Arduino data directory, not in the Arduino IDE application directory. The default locations are:

| Operating system | Arduino data directory |
| --- | --- |
| Linux | `~/.arduino15` |
| Windows | `%LOCALAPPDATA%\Arduino15` |
| macOS | `~/Library/Arduino15` |

The paths below use `<Arduino data directory>` as a placeholder.

## 1. Install the STM32 Core packages

To develop from the `main` branch, install the versions of the required dependencies declared by [platform.txt](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/platform.txt):

- [CMSIS](https://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php): ARM® Cortex® Microcontroller Software Interface Standard
- [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks [The xPack GNU Arm Embedded GCC](https://xpack.github.io/arm-none-eabi-gcc/): https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack
- [OpenOCD](https://openocd.org/): the Open On-Chip Debugger provides on-chip programming and debugging support with a layered architecture of JTAG interface and TAP support. Packages are provided thanks [The xPack OpenOCD](https://xpack-dev-tools.github.io/openocd-xpack/): https://xpack-dev-tools.github.io/openocd-xpack/
- [STM32Tools](https://github.com/stm32duino/Arduino_Tools): upload tools for STM32 based boards and some other useful scripts
- [stm32_svd](https://github.com/stm32duino/stm32_svd): System View Description files. It is the description of the system contained in the stm32, in particular, the memory mapped registers of peripherals.

> [!IMPORTANT]
> The Git repository can require newer tool dependencies than the latest release. Check the [development package index](https://github.com/stm32duino/BoardManagerFiles/blob/dev/package_stmicroelectronics_index.json) before building. A package version with a `-dev` suffix indicates that development dependencies have changed.

See [Getting Started](../Getting-Started.md) for the installation procedure. In the Arduino IDE's **Additional Boards Manager URLs** field, use this development index instead of the release index:

https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/dev/package_stmicroelectronics_index.json

> [!IMPORTANT]
> Select the matching `-dev` package version when installing dependencies. The folder name used later must match the version selected in the Arduino IDE.

## 2. Prepare the installed STM32 core directory

Close the Arduino IDE before changing the installed package. Go to the installed package directory; see [Where are sources](Where-are-sources.md) if you need help finding it:

`<Arduino data directory>/packages/STMicroelectronics/hardware/stm32/`

Move the installed STM32 version directory to a backup location outside this directory. For example:

`<Arduino data directory>/packages/STMicroelectronics/hardware/stm32/<version>`

Move it to:

`<backup directory>/<version>`

> [!IMPORTANT]
> Do not leave the backup directory alongside the active version directory. If both the packaged core and the Git checkout remain under `hardware/stm32`, the Arduino IDE can show duplicate STM32 board menus.

## 3. Clone the Git repository in its place

Clone the repository into the same version directory that you moved in step 2:

`git clone --branch main --recurse-submodules https://github.com/stm32duino/Arduino_Core_STM32.git <Arduino data directory>/packages/STMicroelectronics/hardware/stm32/<version>`

`<version>` must exactly match the installed package version, for example `2.8.1-dev` when that is the version selected in the Arduino IDE. This directory name is how the Arduino IDE associates the checkout with the installed platform package.

Since ArduinoCore-API has been deployed, the repository contains a git submodule.
If the repository was not cloned with `--recurse-submodules`, initialize it with:

`git submodule update --init --recursive`

Verify the checkout before restarting the Arduino IDE:

```sh
git status
git submodule status
```

> [!TIP]
> Of course you can use a [fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) of the [Arduino_Core_STM32] to be able to contribute and easily create [Pull Requests](https://help.github.com/articles/about-pull-requests/)

> [!TIP]
> You can clone the repository elsewhere and create a symlink named `<version>` inside the `hardware/stm32` directory. This is useful when the Arduino data directory is managed separately from your development checkout.

> [!CAUTION]
> Uninstalling the STM32 board package from the Boards Manager removes the Git checkout if it is still inside the Arduino data directory.

## 4. Update an existing checkout

Run these commands from the cloned repository when you need the latest `main` branch and submodule contents:

```sh
git pull --recurse-submodules
git submodule update --init --recursive
```

If the development package index reports a new `-dev` dependency version, install that package version through the Boards Manager before building the checkout. Do not replace the checkout with a release package unless you intend to stop developing from `main`.


[Arduino_Core_STM32]: https://github.com/stm32duino/Arduino_Core_STM32
