# Requirements

## CMake

No surprise here: you need CMake to begin with. The actual requirement is version >= 3.21.
The most straightforward way is to get it from [https://cmake.org/download/](https://cmake.org/download/).

Alternative installation methods:
- [Kitware's APT repository](https://apt.kitware.com/) (Debian, Debian-based)
- [snap package](https://snapcraft.io/cmake) (Ubuntu, mostly)
- [Chocolatey package](https://community.chocolatey.org/packages/cmake) (Windows)
- [pip package](https://pypi.org/project/cmake/) (universal)
- Your IDE may also have a plug-in to support CMake; please refer to its documentation when appropriate

> [!NOTE]
> thanks to Alex Reinking for this [summary](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html)!

## Ninja

We advise using [`ninja`](https://ninja-build.org/) to perform the actual build. `make` or your IDE's build system should work too, though.
To quote their home page:
> You can [download the Ninja binary](https://github.com/ninja-build/ninja/releases) or [find it in your system's package manager](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

## Python

This project makes heavy use of Python scripts to emulate some of Arduino's *dark magic* (understand: handy automation)...
We demand version >= 3.9. Please browse the official [Python download page](https://www.python.org/downloads/). Alternatively, most Linux distributions package it themselves (e.g., APT...).

## Python modules

These are available on [PyPi](https://pypi.org/), meaning you can install them with `pip install <package>`. When using third-party modules, in order not to impact any other project you may be working on, it is customary (but not mandatory!) to set up a [virtual environment](https://packaging.python.org/en/latest/tutorials/installing-packages/#creating-virtual-environments) (Look up `virtualenv`, `virtualenvwrapper` on PyPi for more information on this process).

The following modules are used throughout the project:
- `jinja2`, a templating engine to autogenerate some CMake configuration files.
- `graphviz`, a rendering engine to generate graphs as insights into the project

## Graphviz

This is the counterpart of the associated Python module. Its rendering engines turn `.gv` text files into `.svg` pictures.
You can read about installation on their [download page](https://graphviz.org/download/).

The two (this, and the Python module) are really optional requirement; if you only care about getting your code to compile, you may skip them.

## arduino-cli

You may use the [Quickstart-guide](Quickstart-guide.md) to get started easily.
This tool uses `arduino-cli` to inherit from your default Arduino installation.
Learn how to install it [here](https://arduino.github.io/arduino-cli/latest/installation/).

## Compiler

As with Arduino IDE, there is nothing to do here! The compiler (`arm-none-eabi-g++` *et al.*) will be downloaded when you first run CMake, in a separate folder in your user home directory.
For the curious user, here is where we get it: [https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack](https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack)

## CMSIS

As with the compiler, this will be downloaded silently (really, no, you get a message, but you see what I mean...).
It comes from there: [https://github.com/stm32duino/ArduinoModule-CMSIS](https://github.com/stm32duino/ArduinoModule-CMSIS)

## ctags

Nothing to do here either: this tool is also downloaded when first running CMake.
It is used by Arduino to preprocess the sketches.
The trick is that we are not talking about any of the ["usual" ctags implementations](https://ctags.io/) that you may install through e.g., `apt`, but [Arduino's own](https://github.com/arduino/ctags).
It has a small additional feature that is absolutely necessary for the task at hand, so don't get fooled!
