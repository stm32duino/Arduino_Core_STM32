# Adding MCCI Boards

In order to ensure consistency in menu entries, `boards.txt` is created by processing the template file `boards.template` using the bright script `generate_boards.bri` and the input file `boards.json`.

`boards.json` defines two objects, `defaults` and `boards`.

- `defaults` contains the default macro values to be used for variables in case no specific value is given.
- `boards` is an array of definitions, one entry per board; each entry contains the macro values to be used for that board.

In both objects, a special array variable is used to parameterize the lines in the expanded text. `extra_sections` is an array containing 0 or more objects. Each object is either of the form

   ```json
   { "name": "{{inputname}}" }
   ```

   or

   ```json
   { "name": "{{inputname}}",
     "using": "{{replacementname}}" }
   ```

After section substitution, the board specification is scanned for strings within doubled-curly-braces (`{{...}}`). These are taken as macro names; the name is looked up, first in `boards.json` object `boards`, then in object `defaults`. If found, the value is substituted. Substitutions are further macro-expanded.

The template file is divided into sections.

The section beginning with `%%+prefix` and ending with `%%-prefix` is used as the prefix for the file. It should contain the menu definitions. The prefix file is not macro-expanded.

The section beginning with `%%+boards` and ending with `%%-boards` is repeated once for each board in the `boards` section of the JSON file.

Text in the template file outside the marked sections is ignored.

Lines in the boards template of the form `$section` _`name`_ are references to other named sections in the template file. Processing is conditional, and works in the following ways.

- If _`name`_ doesn't appear in `extra_sections` for this board, then the section is not expanded.
- If _`name`_ appears in `extra_sections` with a `using` clause, then the section named by the `using` clause is inserted instead of the `$section` _`name`_ line.
- If _`name`_ appears in `extra_sections` without a `using` clause, then section _`name`_  from the template is inserted.

Here's a simple example.  Suppose that `boards.template` is

```ini
%%+prefix
# prefix
%%-prefix

%%+boards
# {{modelnumber}}
$section usb
%%-boards

%%+usb
# usb section
%%-usb

%%+usb_disable
# no usb
%%-usb_disable
```

And `boards.json` is

```json
    {
    "boards":
        [
            {
            "modelnumber": "one",
            "extra_sections": []
            },
            {
            "modelnumber": "two",
            "extra_sections": [
                {"name": "usb"}
                ]
            },
            {
            "modelnumber": "three",
            "extra_sections": [
                {"name": "usb"},
                {"using": "usb_disable" }
                ]
            }
        ]
    }
```

Then the output will be:

```ini
# prefix
# one
# two
# usb section
# three
# usb section
```

The following template macros are used in `boards.template`.

- `{{board}}` identifies the board tuple to the Arduino IDE. It is conventionally `mcci_catena_{{modelnumber}}`. Characters should be chosen from C++ identifier characters (`[a-zA-Z0-9_]`).
- `{{modelnumber}}` is assigned by marketing; it's typically a number but might have a regional suffix. Characters should be chosen from C++ identifier characters (`[a-zA-Z0-9_]`).
- `{{name}}` is the UI name of the board, assigned by marketing; it's typically `MCCI Catena {{modelnumber}}`.
- `{{build_board}}` is used to form the C pre-processor symbol for the board. It's normally `MCCI_CATENA_{{modelnumber}}`. Characters should be chosen from C++ identifier characters (`[a-zA-Z0-9_]`).  `platform.txt` normally arranges for `ARDUINO_{{build_board}}` to be defined at compile time.
- `{{vid}}` is the USB vendor ID: for MCCI products, it's 040E.  This should be four hexadecimal digits.
- `{{pid}}` is the USB product ID -- a 4-digit hex number. This is controlled by MCCI sysadmin. This should be four hexadecimal digits.
- `{{build_variant}}` is the directory name (in `variants/`) for the variant-specific source files for this board. Note that this might be shared with other boards.{}
- `{{build_variant_extra_flags}}` specifies additional compile flags for this variant.

The following command is used to generate `boards.txt`.

```shell
bright generate_boards.bri boards.template boards.json > boards.txt
```
