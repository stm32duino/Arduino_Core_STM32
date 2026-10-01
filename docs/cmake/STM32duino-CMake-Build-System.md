# The STM32duino CMake Build System

Since core version 2.4.0, Arduino sketches can be built with CMake instead of
the Arduino IDE or `arduino-cli`. The CMake build system provides flexible
build descriptions, IDE integration, and incremental builds. Build times were
about 50% faster in tests on Windows 10 and Ubuntu 20.04. In return, each sketch
needs a `CMakeLists.txt`, and some of the Arduino IDE's automatic behavior must
be configured explicitly.

The build system uses custom CMake functions from the core's [`cmake/` folder](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/cmake).
Working examples are available in [stm32duino/CMake_workspace](https://github.com/stm32duino/CMake_workspace).

## Requirements

- CMake 3.21 or newer. If necessary, install a recent version with `pip install cmake`.
- Python 3.9 or newer.
- Ninja is recommended; `make` and IDE build integrations are also supported.
- The quickstart script requires the Python module `jinja2`, installable with `pip install jinja2`.
- Graphviz graph output is optional; it requires the Python `graphviz` module and executables such as `dot` and `sfdp`.

The compiler, CMSIS, and Arduino's `ctags` are downloaded when CMake is first
run. See [Setup](Setup.md) for installation details and sources.

## Create a project

Each sketch needs a `CMakeLists.txt` at the sketch root. You can generate a
starter file with the core's `cmake/scripts/cmake_easy_setup.py` script or
write one based on an example. The script's `-s` and `-b` options generate a
configuration for a sketch and board; `-o` generates a template with
placeholders. For example:

```sh
python3 cmake/scripts/cmake_easy_setup.py -b NUCLEO_F207ZG -s <sketch-folder>
```

The script requires `arduino-cli` and `jinja2`.

The board value is its **codename** from `boards.txt`, not its display name.
For example, use `NUCLEO_F207ZG` from this board definition, not `Nucleo F207ZG`:

```text
Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG
Nucleo_144.menu.pnum.NUCLEO_F207ZG.node=NODE_F207ZG
```

## Configure and build

Configure the project once to generate build files. The build directory is
conventionally named `build` inside the sketch folder:

```sh
cmake -S <sketch-folder> -B <build-folder> -G Ninja
```

For example:

```text
Blink/
|-- Blink.ino
|-- CMakeLists.txt
`-- build/
```

Build or rebuild the sketch with:

```sh
cmake --build <build-folder>
```

You can also run `ninja` or `make` from the build directory. This build command
is normally all that is needed after the initial configure; CMake reruns its
configuration when the `CMakeLists.txt` changes.

For the CMake command-line workflow, see the [User Interaction Guide](https://cmake.org/cmake/help/v3.21/guide/user-interaction/index.html).
The official [CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) explains the language and build model in more depth.

## Limitations

- Sketch and library dependencies must be listed explicitly. The CMake build does not automatically discover library dependencies as the Arduino IDE does. See [Arduino Compatibility](Arduino-%28in%29compatibility.md) for details.
- Uploading binaries is not implemented by the CMake build tools. Use a suitable upload tool; for boards that support mass-storage upload, you can copy the `.bin` file to the board's drive.
- Serial monitoring and debugging are handled separately, for example by an IDE or `arduino-cli`.

## Further documentation

Start with [Setup](Setup.md) and then follow the [Quickstart guide](Quickstart-guide.md).
For more complex build descriptions, see the [Introduction to CMake](Introduction-to-CMake.md),
[Functions Reference](Functions-reference.md), and [Advanced Usage](Advanced-usage.md).
