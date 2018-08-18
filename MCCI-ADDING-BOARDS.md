# Adding MCCI Boards

In order to ensure consistency in menu entries, `boards.txt` is created by processing the template file `boards.template` using the bright script `generate_boards.bri` and the input file `boards.json`.

`boards.json` defines two objects, `defaults` and `boards`.

- `defaults` contains the default macro values to be used for variables in case no specific value is given.
- `boards` is an array of definitions, one entry per board; each entry contains the macro values to be used for that board.

The template file is treated as a simple text array, except that strings within doubled-curly-braces (`{{...}}`) are taken as macro names; the name is looked up, first in `boards` then in `defaults`, and if found, the value is substituted. Substitutions are further macro-expanded.

The following template macros are used in `boards.template`.

- `{{board}}` identifies the board tuple to the Arduino IDE. It is conventionally `mcci_catena_{{modelnumber}}`. Characters should be chosen from C++ indentifier characters (`[a-zA-Z0-9_]`).
- `{{modelnumber}}` is assigned by marketing; it's typically a number but might have a regional suffix. Characters should be chosen from C++ indentifier characters (`[a-zA-Z0-9_]`).
- `{{name}}` is the UI name of the board, assigned by marketing; it's typically `MCCI Catena {{modelnumber}}`.
- `{{build_board}}` is used to form the C pre-processor symbol for the board. It's normally `CATENA_{{modelnumber}}`. Characters should be chosen from C++ indentifier characters (`[a-zA-Z0-9_]`).  `platform.txt` normally arranges for `ARDUINO_{{build_board}}` to be defined at compile time.
- `{{vid}}` is the USB vendor ID: for MCCI products, it's 040E.  This should be four hexadecimal digits.
- `{{pid}}` is the USB product ID -- a 4-digit hex number. This is controlled by MCCI sysadmin. This should be four hexadecimal digits.
- `{{build_variant}}` is the directory name (in `variants/`) for the variant-specfic source files for this board. Note that this might be shared with other boards.
- `{{build_variant_extra_flags}}` specifies additional compile flags for this variant.

The template file is divided into sections.

The section beginning with `%%+prefix` and ending with `%%-prefix` is used as the prefix for the file. It should contain the menu definitions. The prefix file is not macro-expanded.

The section beginning with `%%+boards` and ending with `%%-boards` is repeated once for each board in the `boards` section of the JSON file.

Text in the template file outside the marked sections is ignored.

The following command is used to generate `boards.txt`.

```shell
bright generate_boards.bri boards.template boards.json > boards.txt
```
