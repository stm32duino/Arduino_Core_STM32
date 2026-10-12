# Customize build options with build_opt.h

Since core version [1.1.1](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/1.1.1), you can customize compiler definitions and options for an Arduino sketch by adding a file named `build_opt.h` to the sketch directory.

This file is consumed by the Arduino build system as a GCC response file. The build hooks copy it to a generated `build.opt` file in the temporary build directory and append options required by the core. Edit `build_opt.h`, not the generated file.

## Create the file

Place `build_opt.h` beside the sketch `.ino` file:

```text
Blink/
|-- Blink.ino
`-- build_opt.h
```

The file is optional. If it does not exist, the core's [pre-build hook](https://arduino.github.io/arduino-cli/latest/platform-specification/#pre-and-post-build-hooks-since-arduino-ide-165) starts the generated response file without user options. The hook then appends the core-required `-fmacro-prefix-map` option, so the generated `build.opt` file is not empty.

## File syntax

GCC reads options from a response file when it is referenced with the `@file` syntax. Options are separated by whitespace. Surround an option containing whitespace with single or double quotes, or escape the whitespace with a backslash. See the GCC documentation for [overall command options](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html).

Use one or more of these option types:

```text
-DNAME             Define a flag macro
-DNAME=value       Define a macro with a value
-UNAME             Undefine a macro
-foption           Add a compiler option
-Woption           Add a warning option
```

Options are passed to the toolchain, so unsupported or incompatible options can make the build fail. Check the compiler and linker documentation for options that depend on a specific toolchain version or target.

## Examples

Enable or disable an STM32 HAL module:

```text
-DHAL_UART_MODULE_ENABLED
-UHAL_UART_MODULE_ENABLED
```

Change the USB serial buffer sizes:

```text
-DSERIAL_RX_BUFFER_SIZE=256
-DSERIAL_TX_BUFFER_SIZE=256
```

Enable an optimization option:

```text
-faggressive-loop-optimizations
```

Multiple options can be placed on the same line or on separate lines:

```text
-DSERIAL_RX_BUFFER_SIZE=256 -DSERIAL_TX_BUFFER_SIZE=256
```

For HAL-specific settings, see [HAL configuration](HAL-configuration.md). For custom preprocessor definitions, see [Custom definitions](Custom-definitions.md).

## Rebuild after changes

The Arduino IDE may reuse previously compiled objects after `build_opt.h` changes. Enable verbose compilation and check for:

```text
Build options changed, rebuilding all
```

If the output contains `Using previously compiled file:`, force a clean rebuild. Since [Arduino IDE 2.3.10](https://github.com/arduino/arduino-ide/releases/tag/2.3.10), hold the **Shift** key while clicking the **Verify** button to run a clean compile/verify.

In Arduino CLI, use:

```console
arduino-cli compile --clean --fqbn <fqbn> <sketch-directory>
```

You can also close and reopen the Arduino IDE, or change a board menu option that causes the core to rebuild.

## Use with CMake

The Arduino-specific `build_opt.h` workflow is not automatically used by CMake projects. The generated `cmake/templates/easy_cmake.cmake` template already includes an optional `BUILD_OPT` entry in its `overall_settings()` call. Uncomment it to use `build.opt`:

```cmake
overall_settings(
	# Other settings ...
	BUILD_OPT ./build.opt
)
```

Adjust the path if the response file is stored elsewhere. CMake applies the response file to the compiler and linker options. Use the same option syntax described above.

## Troubleshooting

- Make sure `build_opt.h` is beside the `.ino` file, not in the core source tree or a generated build directory.
- Do not edit the generated `build.opt`; it is recreated by the build hooks and contains both user options and core-required options.
- Force a clean rebuild if the compiler output shows cached objects being reused.
- Check quoting and escaping when an option contains whitespace or special characters.
- Confirm that a macro is not defined again later in the build, which can override an earlier `-U` or `-D` option.
