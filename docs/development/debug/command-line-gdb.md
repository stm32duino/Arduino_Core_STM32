# Command Line GDB

## 1. Requirements

- Linux with a POSIX-compatible shell; the commands below can be adapted for other operating systems.
- Arduino IDE with the STM32 core installed.
- An ST-LINK-compatible debug probe.
- An STM32 board; the example uses a Blue Pill, but the same workflow applies to other supported boards.

## 2. Compiling for Debug

- In the Arduino IDE, enable compilation output in **File > Preferences**.
- Open your sketch, for example the Blink sketch.
- In the Arduino IDE, select **Tools > Optimize > Debug**. This includes `-g` in the compilation process and adds debug symbols.
- Connect the ST-LINK probe to the board and the computer.
- Compile and upload the sketch in the Arduino IDE. The compilation output identifies the generated ELF file.

The output includes information similar to this:

```text
<path-to-arm-none-eabi-size> -A <path-to-sketch-elf>/Blink-stm32.ino.elf
Sketch uses 9816 bytes (14%) of program storage space. Maximum is 65536 bytes.
Global variables use 588 bytes (2%) of dynamic memory, leaving 19892 bytes for local variables. Maximum is 20480 bytes for local variables.
```

## 3. Debugging with Command Line GDB

- Open a terminal and start a GDB server, for example with `st-util`:

  ```sh
  st-util
  ```

  The default server address is `localhost:4242`.
- Open another terminal and run `<path-to-arm-none-eabi-gdb> <path-to-sketch-elf>/Blink-stm32.ino.elf` to start the GDB executable provided by the STM32 core. The Arduino IDE compilation output shows the location of the generated ELF file.
- In the GDB console, run the following commands:

```text
target remote localhost:4242

# Add breakpoints to the setup and loop functions.
b setup
b loop
# Run until setup is reached and show the source.
c
l
# Run until loop is reached and show the source.
c
l
# Set a breakpoint in the middle of the toggle loop.
b 37
# Continue execution.
c
c
c
c
c
```

## 4. Debugging with GUI GDB

- To use a GUI such as `ddd`, install it with `sudo apt-get install -y ddd` on Debian-based Linux distributions.
- Run `ddd --debugger <path-to-arm-none-eabi-gdb> <path-to-sketch-elf>/Blink-stm32.ino.elf`.

> [!NOTE]
> Replace the placeholders with the paths to the GDB executable and ELF file on your system.

> [!WARNING]
> This is a community/tool-specific workflow and is not the officially supported STM32duino debugging path. The officially supported workflow is documented in [Arduino IDE 2](How-to-debug.md).
