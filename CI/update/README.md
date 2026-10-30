# Update scripts

Run scripts from the `Arduino_Core_STM32` repository root unless noted
otherwise. Most scripts use settings in `CI/update/update_config.json`; they
create default settings when needed.

## Generate generic variants

`python CI/update/stm32variant.py` generates `PeripheralPins.c`,
`PinNamesVar.h`, `variant_generic.cpp`, `variant_generic.h`, `boards_entry.txt`,
and `generic_clock.c` from STM32CubeMX XML pin descriptions. By default, it
fetches the `STM32_open_pin_data` database from GitHub and processes all
available descriptions. Use `--list` to list descriptions or
`--series <pattern>` to generate a selected series. Use `--cube` to use the
STM32CubeMX database instead; set `CUBEMX_DIRECTORY` in
`CI/update/update_config.json` for that database. The configuration also uses
`STM32CUBECLT_PATH` for STM32 target information.

`python CI/update/stm32variantv2.py` generates the same files from JSON pinout
descriptions in the newer STM32Cube device-pack repositories. Use `--list` to
list available pinout files or `--series <series>` to limit generation to one
supported series. The repositories are managed by `stm32cubev2.py`; their
location is configured with `REPOV2_LOCAL_PATH`.

After generation, review the files carefully and report any issue
[here](https://github.com/stm32duino/Arduino_Core_STM32/issues).

## Update STM32Cube content

`python CI/update/stm32cube.py` manages the HAL drivers and CMSIS device files
from the STM32Cube repositories. By default, it updates all supported series.
Use `--check` to report version differences without updating, `--series
<series>` to select a series, or `--path <directory>` to use a local STM32Cube
repository instead of fetching from GitHub. By default, updates are prepared
in a working copy; use `--local` to update the current core repository.

`python CI/update/stm32cubev2.py` performs the corresponding update for the
newer STM32Cube repository layout, including HAL, LL, and CMSIS files. It
supports the same `--check`, `--series`, `--path`, and `--local` options.

## Generate support files

`python CI/update/stm32wrapper.py` regenerates the HAL, LL, CMSIS, and related
wrapper files using content already present in the core. Optional
`--core <directory>` and `--cmsis <directory>` arguments select alternate core
and CMSIS directories.

`python CI/update/stm32svd.py` updates the SVD files in the configured
STM32duino SVD repository. Set `STM32CUBECLT_PATH` to an STM32CubeCLT
installation and `STM32_SVD_PATH` to the SVD repository in
`CI/update/update_config.json`. The script replaces the repository's `svd`
directory with files selected from that CubeCLT installation.

`python CI/update/fqbn.py` prints the STM32 board FQBNs available in an
installed Arduino core, including each board's `pnum` choices. Use `--board
<pattern>` to filter the output with a regular expression and `--path
<directory>` to specify the directory containing `arduino-cli`.

## Update ArduinoCore-API

`python CI/update/stm32api.py` synchronizes the ArduinoCore-API submodule with
the latest upstream tag, applies eligible STM32duino pull requests and local
patches, and reshapes the tree for STM32 use. It requires the submodule to be
initialized, a clean submodule worktree, and the GitHub CLI (`gh`) to retrieve
pull-request data.

## Update the STM32duino library list

Run `python CI/update/stm32libraries.py` from the `Arduino_Core_STM32`
repository to fetch public STM32duino repositories that contain a root-level
`library.properties` and refresh the generated section in
`docs/libraries/index.md`. The script groups libraries by their declared
category, puts expansion-board libraries in a separate section, includes
declared dependencies (linking STM32duino dependencies when available), and
sorts entries alphabetically. Review and commit the updated documentation
manually; this script is not run by CI.

`REPO_STM32DUINO` in `CI/update/update_config.json` selects the local directory
where library repositories are cloned or fetched. Absolute paths are used as
configured; relative paths are resolved from the `Arduino_Core_STM32`
repository root. If the file or setting is missing, the script writes the
default `REPO_STM32DUINO` path (the parent of the core repository root), asks
you to check the configuration, and exits; run it again after reviewing the
generated setting.
