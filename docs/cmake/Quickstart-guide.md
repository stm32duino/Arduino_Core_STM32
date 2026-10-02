The goal of this page is to provide instructions to get a simple sketch to compile using CMake.
Be sure to read [Setup](Setup.md) through first!

# Using CMake

The page [Introduction to CMake](Introduction-to-CMake.md) covers much more than this section.
You are advised to read it if you want to write a more complex build description.

Briefly, CMake is a meta build system: it generates configuration files for an actual build system to use.
Historically, that second tool has been `make`; we encourage using `ninja` or your IDE's internal.
In the following, we will walk through the process of building manually, using your system shell;
IDEs also often support doing (part of) this process for you, either natively or through a plugin.

The building process can be described as follows:
1. Write a CMake configuration file, always called `CMakeLists.txt`, at the root of your project (sketch).
   This file is written using CMake's own build description language.
   In our case, it should also follow a (quite rigid) template, as illustrated in this repository: [https://github.com/stm32duino/CMake_workspace](https://github.com/stm32duino/CMake_workspace).
   Alternatively, please read below about the script to help generate it.
1. "Configure step": Have CMake generate the secondary tool's build files, in a dedicated folder at the root of the project ("out-of-source build").
   This is usually "source_folder/build".
   ```sh
   cmake -S [source folder] -B [build folder] -G Ninja
   ```
1. "Build step": actually run the second tool, either directly or wrapped through CMake.
   ```sh
   # Run either of these commands, they have the same effect
   cmake --build [build folder]
   ninja # from inside the build folder
   ```

Past the initial setup, when rebuilding, only the last step is necessary; if CMake eventually needs to be re-run, this will be recognized and done automatically.

# Quickstart script

We provide a "quickstart script" [here](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/cmake/scripts/cmake_easy_setup.py).
This Python script uses jinja and arduino-cli to generate a CMakeLists.txt for you to get started more easily.

This script can be used in two ways:
- Using the `-s` and `-b` options, it will generate a CMakeLists.txt _for a given sketch_, filling everything with the appropriate value;
- Using the `-o` option, optionally `-b`, it will generate a cmake file filled with placeholders,
that can be imported into your actual CMakeLists.txt to use the variables it defines (path to this repo, path to your Arduino libraries...)

Note about the `--board` option: the right value to pass there is your board _codename_, not actual name.
If you don't know it, you can find it in [boards.txt](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/boards.txt).
In the following excerpt, the board codename is "NUCLEO_F207ZG", _not_ "Nucleo F207ZG".
> Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG

```
usage: cmake_easy_setup.py [-h] [--cli CLI] [--board BOARD] [--fire] (--output OUTPUT | --sketch SKETCH)

optional arguments:
  -h, --help            show this help message and exit
  --cli CLI, -x CLI     path to arduino-cli
  --board BOARD, -b BOARD
                        board name
  --fire                launch the build immediately (use with caution!)
  --output OUTPUT, -o OUTPUT
                        output file (CMake) with placeholders
  --sketch SKETCH, -s SKETCH
                        output a file (CMake) filled given a sketch folder
```

__Notice:__ This script is really only meant to get started on a simple project with few dependencies (e.g., Blink...).
For more complex projects that use libraries, the generated CMakeLists.txt should be proofread
to fill in the dependency relationships between (the sketch and) the libraries.

# Further readings

## In this wiki
- [Introduction to CMake](Introduction-to-CMake.md)
- [Functions reference](Functions-reference.md)
- [Arduino (in)compatibility](Arduino-%28in%29compatibility.md)
