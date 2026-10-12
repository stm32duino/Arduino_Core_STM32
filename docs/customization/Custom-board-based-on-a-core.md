# Create a custom board package based on the STM32 core

Arduino supports custom board packages that reuse another core, variant, or tool. This is useful when a board is specific to a project or organization and should be maintained separately from the official STM32 core.

If the board should be added to the official STM32 core, follow the [dedicated board guide](../development/Add-a-new-variant/dedicated-board.md) instead. If the board needs a new generic MCU variant, see the [generic variant guide](../development/Add-a-new-variant/generic-variant.md).

## How it works

A custom platform provides its own `boards.txt` and references the STM32 core in the board definition. The Arduino build system then uses the STM32 core's compilation rules and tools while applying the custom platform's board settings.

For example, this entry tells Arduino to use the `arduino` core from the platform installed with the `STM32` vendor name:

```text
bluepill.build.core=STM32:arduino
```

The vendor and architecture names must match the STM32 core package installed by the Board Manager. The STM32 core's `platform.txt` defines the compiler and linker commands; the custom platform can override board properties and add its own tools.

## Platform layout

A minimal custom platform contains `boards.txt`. Other files and directories are optional and depend on the board:

```text
<vendor>/<architecture>/
|-- boards.txt
|-- platform.txt       optional custom tools and commands
|-- programmers.txt    optional programmer definitions
|-- variants/          optional board-specific variants
|-- bootloaders/       optional bootloader files
|-- libraries/         optional board-specific libraries
`-- tools/             optional custom tools
```

Use a unique vendor and architecture name for the custom platform. In `boards.txt`, reference the STM32 core for the board and set the board-specific properties, such as the variant, flash and RAM limits, upload method, and upload tool:

```text
bluepill=BluePill (custom)
bluepill.build.core=STM32:arduino
bluepill.build.variant=bluepill
bluepill.upload.maximum_size=65536
bluepill.upload.maximum_data_size=20480
bluepill.upload.tool=STM32:stlink_upload
```

Only add a custom `variant/` directory when the board requires different pin definitions, board initialization, or other board-specific files. Use the [custom definitions](Custom-definitions.md) page for sketch-level customization instead of creating a platform package.

## Install a local platform

For development, install the custom platform in the `hardware` directory of the Arduino sketchbook. The directory must include both the vendor and architecture names:

```text
<Arduino sketchbook>/hardware/<vendor>/<architecture>/boards.txt
```

Install the official STM32 core with the Board Manager first. Then copy or clone the custom platform into the sketchbook `hardware` directory, restart Arduino IDE, and select the custom board from the board selector.

The same layout can be used by `arduino-cli`. Use the CLI configuration's sketchbook path when it differs from the Arduino IDE sketchbook path.

## Distribute with the Board Manager

For distribution, publish the custom platform as an Arduino package and provide a package index JSON file. Users can then add the package index URL under **Additional Boards Manager URLs** and install the platform through Board Manager.

The package index must identify the custom vendor, architecture, platform version, download archive, and supported host systems. Keep the package vendor name unique and use HTTPS for hosted archives and package indexes.

See the Arduino documentation for [referencing another core, variant, or tool](https://arduino.github.io/arduino-cli/latest/platform-specification/#referencing-another-core-variant-or-tool) and the [package index specification](https://arduino.github.io/arduino-cli/latest/package_index_json-specification/) for the complete format.

## Version compatibility

The custom package depends on the STM32 core's package layout and `platform.txt` properties. Record the STM32 core version used during development and test updates before changing the dependency.

When updating the STM32 core, verify at least the following:

- The referenced core name is still `STM32:arduino`.
- The board variant and linker settings are still accepted.
- The compiler, linker, and upload tools still resolve correctly.
- Flash and RAM limits match the target board.
- A representative sketch compiles and uploads successfully.

The historical [RickKimball vendor-platform example](https://github.com/RickKimball/vendor) demonstrates this approach with a custom BluePill board. It was created for STM32 core version 1.4.0 and has not been verified against current releases; use it as a reference rather than as a ready-to-install package.

## Verify the board

After installation, select the custom board and compile a minimal sketch. With verbose output enabled, confirm that the expected custom board and STM32 core are selected. Then verify the upload path with a small test sketch such as Blink.

If the board is installed through `arduino-cli`, first confirm that the expected fully qualified board name is listed:

```console
arduino-cli board listall | grep -i bluepill
```

Then compile with the reported FQBN:

```console
arduino-cli compile --fqbn <vendor>:<architecture>:<board> <sketch-directory>
```

## Troubleshooting

- If the board does not appear, check the vendor and architecture directory names and restart the IDE.
- If the FQBN is unknown, check that `boards.txt` is in the expected platform directory and that the package is installed for the active Arduino CLI configuration.
- If the variant cannot be found, check `build.variant` and the variant directory name.
- If compilation uses the wrong core, verify the `build.core=STM32:arduino` entry and the installed STM32 core vendor name.
- If upload fails, verify the `upload.tool`, upload protocol, programmer settings, and board-specific reset requirements.
- If the binary is too large or the linker reports memory errors, check `upload.maximum_size`, `upload.maximum_data_size`, and the variant linker script.
