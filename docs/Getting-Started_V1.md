> [!WARNING]
> This page is dedicated to Legacy Arduino IDE (1.8.X) usage.
> Legacy Arduino IDE (1.8.X) can be used only with core version prio to 2.8.0.
> For core version higher or equal to 2.8.0, see the [Getting Started](Getting-Started.md)

# Install Arduino.cc IDE
Download and install [Arduino software (IDE)](https://www.arduino.cc/en/software) for the required OS.
([Windows](https://docs.arduino.cc/software/ide-v1/tutorials/Windows), [Linux](https://docs.arduino.cc/software/ide-v1/tutorials/Linux) or [Mac](https://docs.arduino.cc/software/ide-v1/tutorials/macOS/) instructions)

## About Boards manager concept
Arduino.cc IDE allows to add easily new board thanks the "**Boards Managers**".
More information about "**Boards Managers**" is available on Arduino.cc official website:

[Installing additional Arduino Cores](https://docs.arduino.cc/learn/starting-guide/cores)

The corresponding STM32 cores packages are provided thanks to:

https://github.com/stm32duino/BoardManagerFiles

Follow the below steps to get STM32 boards installed to your Arduino IDE.

# Add STM32 boards support to Arduino
This is the needed step to get STM32 targets added to Arduino.
So carefully follow the following steps.

## Installing STM32 Cores

1- Launch Arduino.cc IDE. Click on "**File**" menu and then "**Preferences**".

![Preferences](img/v1/preferences.png)

The "**Preferences**" dialog will open, then add the following link to the "*Additional Boards Managers URLs*" field:

https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

Click "**Ok**"

2- Click on "**Tools**" menu and then "**Boards > Boards Manager**"

![BoardsManager Menu](img/v1/menu_bm.png)

The board manager will open and you will see a list of installed and available boards. 

Select "**Contributed**" type.

![BoardsManager dialog](img/v1/boardsmanager.png)

Select the "**STM32 MCU based boards**" and click on install.

![BoardsManager dialog](img/v1/boardsmanager2.png)

After installation is complete an "*INSTALLED*" tag appears next to the core name. 

You can close the Board Manager.

![Boards list](img/v1/boardslist.png)

Now you can find the STM32 boards package in the "**Board**" menu.

Select the desired boards series: _Nucleo-64 / Nucleo-144 / Discovery / ..._

![Select boards](img/v1/SelectBoard.png)

Then you can find the Nucleo-64 boards available in a sub-menu of the "Tools" menu.

## Extra step

To upload through SWD (STLink), Serial or DFU, [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) needs to be installed. See [Upload-methods#stm32cubeprogrammer](Upload-methods.md).

## Troubleshooting

If you have any issue to download/use a package, you could [file an issue on Github](https://github.com/stm32duino/BoardManagerFiles/issues/new).

### Proxy
If you have any issue to download a package, ensure to not be behind a proxy.

Else configure the proxy in the Arduino.cc IDE (open the "**Preferences**" dialog and select "**Network**" tab).

# Configuring IDE 
1. Connect a board to the computer USB port. For this example: [Nucleo L476RG]

2. Launch the Arduino software

    ![Arduino icon](img/v1/arduino.png)

3. Select the [Nucleo L476RG] board in two steps:

a. From the "**Tools > Board**" menu, select the STM32 boards groups: _Nucleo-64_

  ![Board selection](img/v1/boardslist.png)

b. Then from the "**Tools > Board part number**" menu, select the [Nucleo L476RG]

  ![Board selection](img/v1/SelectBoard.png)

3. Select the serial port from the "**Tools > Port**" menu

    * On Mac, it's something like _/dev/tty.usbmodem-1511_.
    * On Windows, it's often the highest-numbered COM port. In this example, it's _COM5_
    * On Linux, it's something like _/dev/ttyACM0_.

    (Or unplug the board, check the menu, and then plug the board and check what new port appears)

  ![Port selection](img/v1/SelectPort.png)

## Upload methods
Depending of the board, several upload methods could be proposed, thanks the "**Tools > Upload Method**" menu.

See [Upload methods](Upload-methods.md) for more details.

![Upload Method](img/v1/UploadMethod.png)

# Examples
* [Blink example](examples/Blink-example.md)


[Nucleo L476RG]: http://www.st.com/en/evaluation-tools/nucleo-l476rg.html