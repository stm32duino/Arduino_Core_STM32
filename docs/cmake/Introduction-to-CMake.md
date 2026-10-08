# Introduction to CMake

## Trivia

[CMake](https://cmake.org/) is a meta build system: it generates configuration files for an actual build system to use.
Historically, that second tool has been `make`; we now encourage using `ninja` or your IDE's internal.

CMake configuration files are always named "CMakeLists.txt" (case-sensitively).
They should be put along the actual source files of the project to build, and treated in the same way.

CMake also handles modules, whose name end in ".cmake"; these are usually put in a separate folder, often `/cmake` at the root of the project.
They do not describe the build, but provide additional functionalities to be used in the build description.

Both these kinds of files are written using CMake's own language; cf. below.

## Using CMake

Whatever the user interface (system shell, cmake-gui, IDE, ...), there always are two main steps: configuration and build.

- In the __configuration step__, CMake reads the build description (CMakeLists.txt) and generates files for the build tool to use (e.g., `Makefile` or `build.ninja`).
- In the __build step__, the build tool is called, either directly or indirectly, to perform the build and generate the required build artifacts.
In case CMake needs to be re-run (maybe because one of the CMakeLists.txt has been edited), this is handled automatically without requiring the user to go through another configuration step. This means the _configuration step needs only to be invoked once_ explicitly, even when rebuilding an updated project.

CMake projects are usually built "out-of-source", meaning the build artifacts end up in a parallel directory tree,
as opposed to "in-source" builds, where they are mixed with the source files.

Using a system shell, the full process looks like the following :

```sh
# configuration step
cmake -S /path_to_source/ -B /path_to_source/build -G Ninja # -G denotes the build tool, default to `make`

# build step
cmake --build /path_to_source/build
# Alternatively, cd /path_to_source/build, then:
make # if you are using `make`
ninja # if you are using `ninja`
```

## CMake language

The syntax of the CMake language is very simple: the only statement is the function call, the only value type is the string.
You may want to read [the CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) to get a comprehensive overview of the features CMake offers.

For a detailed list of the functions this project provides, please refer to [Functions reference](Functions-reference.md).
Below is an introduction to general-purpose CMake; most of it is abstracted away in said functions.

Here are some key points about the structure of a `CMakeLists.txt` (Also read [the documentation](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)):

- The main file must start with a call to [`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html), to make sure the version of CMake meets the expectations;
- A call to [`project()`](https://cmake.org/cmake/help/latest/command/project.html) must occur before tackling any file or target;
- You can include a subpart of your project by calling [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html). This will run the `CMakeLists.txt` in the target subdirectory. Modularizing your project in this way is highly encouraged!
- Projects are structured into logical "targets":

  - [executables](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#binary-executables);
  - [static libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#normal-libraries);
  - [shared libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#normal-libraries);
  - [object libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries);
  - [interface libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries);
  - [custom targets](https://cmake.org/cmake/help/latest/command/add_custom_target.html);

  These logical targets can have dependencies on one another.
  Except for the interface libraries, they are visible to the build tool, and can be build independently.
  _(Illustration: when running `make clean ; make all ; make install`, `clean`, `all`, `install` are targets)_

  All these targets have build settings that can, optionally, be propagated to the targets depending on them:

  - [compiler definitions](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html) (e.g., `-Dxxx` flags for GCC)
  - [`#include` search paths](https://cmake.org/cmake/help/latest/command/target_include_directories.html) (e.g., `-Ixxx` flags for GCC)
  - [compiler options](https://cmake.org/cmake/help/latest/command/target_compile_options.html) (generic compiler flags: warnings, optimizations, ...)
  - [linker options](https://cmake.org/cmake/help/latest/command/target_link_options.html) (`-Wl,xxx` for GCC)
  - [link search paths](https://cmake.org/cmake/help/latest/command/target_link_directories.html) (`-Lxxx` for gcc)
  - [dependencies](https://cmake.org/cmake/help/latest/command/target_link_libraries.html) (`-lxxx` for GCC)

  These commands make use of the `PUBLIC`, `INTERFACE` or `PRIVATE` keywords.

  - `PUBLIC` and `INTERFACE` will apply the setting to all the dependers of the target in question;
  - `INTERFACE` and `PRIVATE` also apply the setting to the target itself.

## Further readings

### Official documentation from Kitware

- CMake [User Interaction Guide](https://cmake.org/cmake/help/v3.21/guide/user-interaction/index.html)
- [CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [Converting existing systems to CMake](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Converting%20Existing%20Systems%20To%20CMake.html)

### Third-party resources

The links below are not endorsed by STMicroelectonics nor Kitware, but have proven useful in practice for users learning to use CMake "sanely".

- [LLVM's CMake introduction](https://llvm.org/docs/CMakePrimer.html)
- [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [C++: Compiling, Linking, and CMake](https://courses.grainger.illinois.edu/cs126/sp2020/notes/cmake/)
- [CMake Part 1 – The Dark Arts](https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/), [Part 2 – Release and Debug builds](https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/), [Part 3 – Source File Organisation](https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/)
- [How to Use CMake Without the Agonizing Pain - Part 1](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html), [Part 2](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-2.html)
