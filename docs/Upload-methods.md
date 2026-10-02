# Upload methods

## Mass Storage

This upload method is mainly dedicated to boards manufactured by ST which integrate a ST-Link: [Nucleo], [Discovery], [Eval].

This enables drag-and-drop flash programming, so there is no need for a separate debug probe. 
The mass storage device of the ST-Link is a virtual disk, copy on this disk a binary will program it.
Once programmed into the MCU the copied binary disappears from the virtual disk.

## STM32CubeProgrammer

[STM32CubeProgrammer] allows to write and verify device memory through both the debug interface (JTAG and SWD) and the bootloader interface (UART, USB DFU, I2C, SPI, and CAN).

Three upload methods are based on the [STM32CubeProgrammer] CLI (command-line interface):

* [SWD](#swd)
* [Serial](#serial)
* [DFU](#dfu)

### Requirement

To use those upload methods, [STM32CubeProgrammer] have to be installed manually as **it is not provided** through the tools packages.

User can change the default install path but in this case, the new path have to be added in the [PATH](https://en.wikipedia.org/wiki/PATH_(variable)) environment variable.

Default path of [STM32CubeProgrammer] binary:
 * **Linux**: `$HOME/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin`
 * **Mac**: `/Applications/STMicroelectronics/STM32Cube/STM32CubeProgrammer/STM32CubeProgrammer.app/Contents/MacOs/bin`
 * **Windows**:
   * _32 bits_: `%ProgramFiles(X86)%\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin`
   * _64 bits_: `%ProgramW6432%\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin`

To add your custom installation path you can refer to this [HowTo](https://gist.github.com/jesperorb/836cb398e4bb8dc149902d68d3711295#environment-variables)

In any case, if the [STM32CubeProgrammer] binary is not found, user will be warned like this:

```Console
STM32_Programmer.sh/STM32_Programmer_CLI.exe not found.
Please install it or add '<STM32CubeProgrammer path>/bin' to your PATH environment:`
https://www.st.com/en/development-tools/stm32cubeprog.html`
Aborting!
```

> [!WARNING]
> **Linux user** having _`STM32_Programmer.sh` not found_, 2 cases have been identified:
>
>  1 . Arduino IDE installed from the "Software" package manager (See Ubuntu user issue about this: https://github.com/stm32duino/Arduino_Tools/issues/63)
>
>  It means snap has been used to install Arduino IDE and snap does not use the default user `PATH`:
>  https://snapcraft.io/docs/environment-variables
>
>  **In that case, up to end user to provide the correct environment by adding the correct path of the STM32CubeProgrammer to the snap environment.**
>
>  2 . A desktop entry has been created (using the `install.sh`) then the `PATH` variable is not populated. In that case edit the Arduino desktop entry file (`arduino-arduinoide.desktop`) to set `PATH` like this:
>
> ```patch
> - Exec="<arduino path installation>/arduino"
> + Exec=sh -c "PATH=<STM32CubeProgrammer path installation>/bin:$PATH <arduino path installation>/arduino"
> ```

### Arduino integration

Unique script has been deployed thanks [STM32 Tools](https://github.com/stm32duino/Arduino_Tools) packages to ease Arduino integration and allow to have only one definition of the tool in the `platform.txt`:

* [stm32CubeProg.sh](https://github.com/stm32duino/Arduino_Tools/blob/main/stm32CubeProg.sh)

`{upload.protocol}` allows to select the right interface to use:
  * 0: SWD
  * 1: Serial (using the built-in ST bootloader)
  * 2: DFU (using the built-in ST bootloader)

See [AN2606](https://www.st.com/content/ccc/resource/technical/document/application_note/b9/9b/16/3a/12/1e/40/0c/CD00167594.pdf/files/CD00167594.pdf/jcr:content/translations/en.CD00167594.pdf) for STM32 microcontroller system memory boot mode.

`{upload.options}` is used to pass extra options:
 * `-rst` for SWD to reset the device after the flash
 * `{serial.port.file} -s` for Serial

> [!NOTE]
> I2C, SPI, CAN could be added as supported by the [STM32CubeProgrammer] tool.

### SWD

Requires a [ST-Link/V2](https://www.st.com/content/st_com/en/products/development-tools/hardware-development-tools/hardware-development-tools-for-stm32/st-link-v2.html) or [ST-Link/V3](https://www.st.com/en/development-tools/stlink-v3set.html) device connected to the PC over USB and to the board via the SWD interface.

> [!TIP]
> Several boards manufactured by ST integrate ST-Link: [Nucleo], [Discovery], [Eval].

Be sure that the necessary driver for Windows is installed ([available here](https://www.st.com/en/development-tools/stsw-link009.html)) and the ST-Link adapter is updated to the latest firmware ([application to upgrade the firmware](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link007.html)).

Only 3 pins are required for basic programming and debugging of the STM32 MCU devices (4 if the board is powered by the programmer) using Serial Debug Wire (SWD):

* GND
* SWDIO
* SWCLK
* 3.3V (optional)

> [!CAUTION]
> **Avoid wired 3.3V to the target board if it is already powered by an other source (external supply, USB,..) else you may damage the board, programmer, USB port or external supply.**

Refers to [ST-Link V2](https://www.st.com/resource/en/user_manual/dm00026748.pdf) or [ST-Link V3](https://www.st.com/resource/en/user_manual/dm00526767-stlinkv3set-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) user Manual and to the board documentations (User Manual, schematics,...) to ensure connect to the right pins.

### Serial

This requires to restart the STM32 in 'native bootloader' mode and rely on `Boot` pins. Check in [STM32 microcontroller system memory boot mode AN2606](https://www.st.com/content/ccc/resource/technical/document/application_note/b9/9b/16/3a/12/1e/40/0c/CD00167594.pdf/files/CD00167594.pdf/jcr:content/translations/en.CD00167594.pdf) which pattern to apply to activate the bootloader for the dedicated STM32 MCU. Check also which U(S)ART is used.

> [!WARNING]
> A serial port or additional USB to Serial adapter is needed.

Connect `power`, `GND`, and `Tx/Rx` pins of the serial adapter to your STM32 U(S)ART. 

Adapter `Tx` goes to STM32 `Rx` and `Rx` goes to STM32 `Tx`.

### DFU

This requires to restart the STM32 in 'native bootloader' mode and rely on `Boot` pins. Check in [STM32 microcontroller system memory boot mode AN2606](https://www.st.com/content/ccc/resource/technical/document/application_note/b9/9b/16/3a/12/1e/40/0c/CD00167594.pdf/files/CD00167594.pdf/jcr:content/translations/en.CD00167594.pdf) which pattern to apply to activate the bootloader for the dedicated STM32 MCU.

> [!WARNING]
> **USB cable have to be plug to enter in DFU mode.**

> [!TIP]
> On Linux with some boards like the black pill, press and hold the boot button then plug the board in. Check dmsg to see if the board is was recognized as in DFU mode.

> [!NOTE]
> on Linux you may need udev rules setup if the programmer cannot access your board. After putting the board in DFU mode, check the kernel using dmesg, you should see your board.  Install dfu-util and run dfu-util -l as root and if it works, run as your user.  If it fails, you need to setup UDEV.  See the 45-maple.rules file for an example.

Edit /etc/udev/rules.d/45-maple.rules.  The first lines are for Maple.  The last line defines your board (the info reported by dfu-util -l or from running dmesg).  This was tested on Fedora 33.
```Console
  45-maple.rules:
  ATTRS{idProduct}=="1001", ATTRS{idVendor}=="0110", MODE="664", GROUP="plugdev"
  ATTRS{idProduct}=="1002", ATTRS{idVendor}=="0110", MODE="664", GROUP="plugdev"
  ATTRS{idProduct}=="0003", ATTRS{idVendor}=="1eaf", MODE="664", GROUP="plugdev" SYMLINK+="maple", ENV{ID_MM_DEVICE_IGNORE}="1"
  ATTRS{idProduct}=="0004", ATTRS{idVendor}=="1eaf", MODE="664", GROUP="plugdev" SYMLINK+="maple", ENV{ID_MM_DEVICE_IGNORE}="1"
  ATTRS{idProduct}=="df11", ATTRS{idVendor}=="0483", MODE="664", GROUP="dialout" SYMLINK+="blackpill", ENV{ID_MM_DEVICE_IGNORE}="1"
```

After running this, tell udev to reload the rules:  
```Console
   sudo udevadm control --reload-rules
```

## BMP (Black Magic Probe)

Refers to [Black Magic Probe](https://github.com/blacksphere/blackmagic) site and its [Getting-Started](https://github.com/blacksphere/blackmagic/wiki/Getting-Started) Wiki.

> [!WARNING]
> **On Windows [Black Magic Probe](https://github.com/blacksphere/blackmagic) has a restriction**:
> for ports `>= COM10` the command line requires to add this prefix `\\.\`.
> This is not handled by the core as it is tools restriction. To be able to use it:
>
> Go into the **Device manager**, select "**Show hidden devices**" and go to the "**Ports**" section, right-click on one COM port below COM10 and select "_Uninstall device_" to delete it. Free at least 2 COM port bleow 10. Then connect your BMP again.

## HID Bootloader 2.2 (HID BL)

This is a driverless USB bootloader for `STM32F10x` and `STM32F4xx` MCUs and is based on [HID protocol](https://en.wikipedia.org/wiki/Human_interface_device). No special USB drivers are needed, even on Windows.


The bootloader is installed at `0x8000000` address.
On **STM32F103**, the bootloader consumes only `2 kB` of flash memory (0x800). 
The user code area starts at `0x8000800`

The **STM32F4xx** MCUs have built-in `DFU` (Device Firmware Upgrade) but you can also use HID BL for uploading firmwares.

* The advantage of using HID BL instead of the DFU bootloader is that the entire firmware update process is automatic. You do not have to press any button or set any PCB jumper. 

* The downside is that the `F4` HID BL firmware is larger than the `F1` version, consuming `16kB` (0x4000) of available flash memory.

The `hid-flash` tool is available on Windows, Linux and MacOS.

Details of HID bootloader v2.2 (and newer) hid-flash tool as well as ready-to-use binary files can be found at the GitHub repository: https://github.com/Serasidis/STM32_HID_Bootloader

> [!WARNING]
> USB CDC have to be enable else you will not be able to upload automatically as bootloader reset sequence are managed through the USB CDC communication port.

## Maple DFU Bootloader

Extract from the legacy wiki page about bootloaders (https://web.archive.org/web/20190316155415/http://wiki.stm32duino.com/index.php?title=Bootloader):

In order to simplify the upload process leveraging the USB device, Leaflabs developed a custom DFU bootloader that needs to be uploaded in the MCU at address `0x08000000` via one of the standard STM upload methods (ST Link or standard STM serial bootloader); this custom bootloader is called the **_original Maple bootloader_**.
Leaflabs' documentation about the original Maple bootloader can be found here: 
http://docs.leaflabs.com/static.leaflabs.com/pub/leaflabs/maple-docs/latest/bootloader.html

[stm32duino.com](http://stm32duino.com/) guys modified the **_original Maple bootloader_** in order to:
 * enable support for STM32F103 non-Maple boards (blue pill and other generic boards)
 * fix issues found in the original Maple bootloader
 * reduce the bootloader size so that enlarging the memory available to user sketches
 * remove the option to upload to RAM

This modified version of the _Maple bootloader_ is known as STM32duino-bootloader or also **_bootloader 2.0_**.
Details about the STM32duino-bootloader as well as ready to use binary files can be found in the GitHub repository: https://github.com/rogerclarkmelbourne/STM32duino-bootloader

> [!NOTE]
> * Maple devices (including clones) generally come with the original Maple bootloader preloaded.
> * Generic STM32F103 boards on the other side come with no custom bootloader installed.
> * Maple bootloader 2.0 consumes 8KB of flash.
> * Maple bootloader original consumes 20kb of flash and some of the SRAM.

> [!WARNING]
> USB CDC have to be enable else you will not be able to upload automatically as bootloader reset sequence are managed through the USB CDC communication port.


[Discovery]: https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-discovery-kits.html
[Eval]: https://www.st.com/en/evaluation-tools/stm32-eval-boards.html
[Nucleo]: https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html
[STM32CubeProgrammer]: https://www.st.com/en/development-tools/stm32cubeprog.html