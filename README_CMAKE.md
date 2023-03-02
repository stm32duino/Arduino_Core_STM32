CMake can now be used to build Arduino sketches with this core.
Examples of use can be found on this repo: [stm32duino/CMake_workspace](https://github.com/stm32duino/CMake_workspace).

This README only provides a quick walk-through.
For all the glorious details, please head over to [the wiki](https://github.com/stm32duino/Arduino_Core_STM32/wiki/CMake_presentation).

# Prerequisites

- CMake version >= 3.21
- Python3 version >= 3.9
- `make` / `ninja` (prefer `ninja`)
- graphviz layout engines: `dot`, `sfdp` (optional)
- Python modules: `graphviz`, `jinja2`; install them with `pip install ...`

Some additional dependencies (toolchain...) will be downloaded on the first build.

If your system does not provide a recent enough version of CMake, a suitable version may be installed with [`pip`](https://pypi.org/): `pip install cmake`.

# Usage

This section will describe the process of building a sketch "by hand", with a system shell. Other methods, such as with an IDE plug-in, may require adaptations.

Please see [stm32duino/CMake_workspace](https://github.com/stm32duino/CMake_workspace) for some quick examples; more may be added over time.

First of all, there has to be a CMakeLists.txt in the sketch folder.

- easy way: fire `cmake/scripts/cmake_easy_setup.py -b <board> -s <sketch folder>` (this requires arduino-cli and jinja)
- advanced way: write your own by adapting from an example

--------

__Board name__: either through the script or directly in the CMakeLists.txt, the board name is the identifier found in boards.txt. (Yes, CMake is made aware of boards.txt/platform.txt.)
In the following example, the value to retain would be "NUCLEO_F207ZG" (the part after "menu.pnum."):
```
# NUCLEO_F207ZG board
Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG
Nucleo_144.menu.pnum.NUCLEO_F207ZG.node=NODE_F207ZG
```

--------

Then CMake can be run to launch the configuration step. This is only needed on the very first time, at the beginning of the project.
```sh
cmake -S [sketch folder] -B [build folder] -G Ninja # "-G Ninja" -> generate ninja files (default = make)
```
The build folder is conventionally located at the root of the sketch folder and named `build`, e.g. :
```
.
|-- Blink/
|   |-- Blink.ino
|   |-- CMakeLists.txt
|   `-- build/
```

Finally, the sketch can be (re-)built with `cmake --build <build folder>`.
This can also be done by invoking the build tool (usually `make` or `ninja`) directly from the build folder.
**This last step is the only one needed in order to rebuild the project, even if some source files, or even the CMakeLists.txt, have changed.**

For more details on how to use CMake, please read the CMake [User Interaction Guide](https://cmake.org/cmake/help/v3.21/guide/user-interaction/index.html).

The official [CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) may also be useful for users looking to understand all the implementation details.

# Caveats

- The CMake build model makes it hard to auto-detect dependencies between the sketch and the Arduino libraries, and between Arduino libraries. Thus, you have to specify them manually; see the examples to see how.
- Uploading the binaries to the board is not implemented; this step is up to you, using the appropriate tool. If your board supports the "mass storage" method, you can simply copy the .bin file to your board drive in the file explorer.
