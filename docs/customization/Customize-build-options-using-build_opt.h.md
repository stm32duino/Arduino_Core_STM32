## How to customize build options
Since the core version [1.1.1](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/1.1.1), it is possible to customize some core definitions or compiler options by adding a file named "`build_opt.h`" in the sketch directory. 

This file allow to used the "_`@file`_" parameter of gcc.

See https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html

> @file
>
>     Read command-line options from file. The options read are inserted in place of the original @file option.
>     If file does not exist, or cannot be read, then the option will be treated literally, and not removed.
>
>     Options in file are separated by whitespace. A whitespace character may be included in an option
>     by surrounding the entire option in either single or double quotes. Any character (including a backslash)
>     may be included by prefixing the character to be included with a backslash. The file may itself contain
>     additional @file options; any such options will be processed recursively.

By default, if the file does not exist an empty one is created using the [pre-build hooks](https://arduino.github.io/arduino-cli/latest/platform-specification/#pre-and-post-build-hooks-since-arduino-ide-165) feature.

### Examples of file content:
 * Enable an HAL module:

    `-DHAL_UART_MODULE_ENABLED`
 * Disable an HAL module:

    `-UHAL_UART_MODULE_ENABLED`
 * Enable an Optimization Options:

    `-faggressive-loop-optimizations`
 * Change one default define as the Serial Rx/Tx buffer size:

    `-DSERIAL_RX_BUFFER_SIZE=256 -DSERIAL_TX_BUFFER_SIZE=256`

### Warning
If you made a change in the "`build_opt.h`" file after a first build, this will not be detected by the Arduino IDE and will use the previous build object or cache core to build. To ensure the change is properly used, close the Arduino IDE or change one option in the menu (example upload method). This will force to rebuild all.
If the compilation verbose is enabled you should see this at the beginning of the build:

```Console
Build options changed, rebuilding all
```

Else you will see several:

```Console
Using previously compiled file:
```
