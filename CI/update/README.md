# stm32variant

By default, generates:
 - *PeripheralPins.c*
 - *PinNamesVar.h*
 - *variant_generic.cpp*
 - *variant_generic.h*
 - *boards_entry.txt*
 - *generic_clock.c*

for all xml files description available in [STM32CubeMX](http://www.st.com/en/development-tools/stm32cubemx.html) database.
By default, the database used is the one from GitHub:
        https://github.com/STMicroelectronics/STM32_open_pin_data
The internal database from STM32CubeMX directory can also be used.
The path have to be defined in `update_config.json`.

After file generation, review them carefully and please report any issue
[here](https://github.com/stm32duino/Arduino_Core_STM32/issues).

## Update the STM32duino library list

Run `python CI/update/stm32libraries.py` from the `Arduino_Core_STM32` repository
to fetch public STM32duino repositories that contain a root-level
`library.properties` and refresh the generated section in
`docs/libraries/index.md`. The script groups libraries by their declared
category, puts expansion-board libraries in a separate section, includes
declared dependencies (linking STM32duino dependencies when available), and
sorts entries alphabetically. Review and commit the updated documentation
manually; this script is not run by CI.

`REPO_STM32DUINO` in `update_config.json` selects the local directory where
library repositories are cloned or fetched. Absolute paths are used as
configured; relative paths are resolved from the `Arduino_Core_STM32` repository
root. If the file or setting is missing, the script writes the default
`REPO_STM32DUINO` path (the core repository root), asks you to check the
configuration, and exits; run it again after reviewing the generated setting.
