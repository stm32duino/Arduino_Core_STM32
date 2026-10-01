Welcome to the CMake port of Arduino_Core_STM32!

--------------------------
_**Support available since 2.4.0 release.**_


The goal of this tool is to let users build Arduino sketches for STM32 boards, without using neither Arduino IDE nor `arduino-cli`.
Advantages of this approach include:

- faster build time (about -50%, tested on Windows 10 and Ubuntu20.04);
- flexibility: CMake has a full language centered around build description;
- integration with IDEs: CMake integrates with most recent IDEs, easing the work of those who code outside of Arduino IDE;
- better support of incremental compilation;
- overstepping limits set by Arduino: sketch filename, library selection...

Of course, this all has a cost: building is no longer as simple as hitting "build" in Arduino IDE; there is a CMake file to write and maintain.
However, much has been done to make the file as high-level as possible: it is written in CMake's own syntax, but makes heavy use of the custom functions defined here in the [`cmake/` folder](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/cmake).
Didactic examples can be found on a separate repository: [https://github.com/stm32duino/CMake_workspace](https://github.com/stm32duino/CMake_workspace).

Before delving into this guide, be sure to read [the dedicated README](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/README_CMAKE.md) first!


## Pages in this section:
- [Setup](Setup.md)
- [Quickstart guide](Quickstart-guide.md)
- [Introduction to CMake](Introduction-to-CMake.md)
- [Functions reference](Functions-reference.md)
- [Arduino (in)compatibility](Arduino-%28in%29compatibility.md)
- [Advanced usage](Advanced-usage.md)
- [cubeIDE](cubeIDE.md)
