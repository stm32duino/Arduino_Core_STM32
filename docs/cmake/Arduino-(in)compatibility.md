# Deviations to the behavior of Arduino IDE

While the CMake toolsuite aims at replicating the behavior of Arduino IDE, there may be some deviations, by design or accident.
This page lists all such known deviations.

# Source files

Arduino IDE dynamically discovers all the source files of the sketch when rebuilding.
On the other hand, with the CMake tools, there is a hard-coded list of files to update manually (cf. [`build_sketch()`](./Functions-reference.md#build_sketch).).

This comes from the different levels at which the tools operate: Arduino IDE behaves as a build system, while CMake is a _meta_ build system.
This means that, while CMake can discover all the source files when it is manually invoked,
it may not be reinvoked (as should be) after a source file is added, since it was not "monitoring" that file in the first place.
Please reat the [warning note](https://cmake.org/cmake/help/latest/command/file.html#glob) in the CMake documentation for details.

Also, as mentioned in [the Arduino documentation](https://arduino.github.io/arduino-cli/latest/sketch-build-process/#pre-processing), all the
`.ino` files of the sketch are concatenated during the pre-processing step.
This is not implemented with CMake, as most sketches have a single `.ino` file, but if you fill the need for this feature, please submit a PR!

On the other hand, Arduino _requires_ each sketch to have a `.ino` file with the same name as the sketch folder.
In CMake, there is no such restriction; you may name your `.ino` files differently, or even not have any `.ino` file at all.

Final tweak: as part of the conversion `.ino` -> `.cpp`, Arduino IDE generates the prototypes of all the functions defined in .ino files.
This is meant mostly for beginners, so that they may write their functions in any order without the added complexity of prototypes.
This process is replicated with CMake, with the slight nuance that Arduino runs the GCC preprocessor _before_ doing this,
in order to resolve all the macros and get "sane" C++ code. As opposed to this, CMake does not model the preprocessing stage, so it has to work
on the "raw" `.ino` file. Usually this has no consequence whatsoever, but it may cause trouble if you use complex macros that alter the structure
of the code.

# Library management

Arduino IDE comes with a full library management suite, to download and update third-pary libraries as needed.
This is out of the scope of the CMake tool; users have to download and manage their libraries externally.
It is, however, possible to reuse the libraries installed by `arduino-cli`, e.g., by using the [quickstart script](./Quickstart-guide.md#quickstart-script).

Second item, Arduino IDE discovers at compile-time what libraries the sketch needs.
This is done by catching GCC errors during the preprocessing stage, and fuzzy matching the missing `#include` with all the available libraries,
as described in [their documentation](https://arduino.github.io/arduino-cli/latest/sketch-build-process/#dependency-resolution).

CMake does not have access to all these data _at configure-time_; also, it does not model the preprocessing at all.
This means the dependency resolution process, if implemented, would have been awkward and fragile.
This is why another solution has been preferred: to have the user fill in all the dependencies manually (cf. the `DEPENDS` keyword in several functions in [Functions reference](./Functions-reference.md).)


# Upload, serial monitor, debugger

These items are out of the scope of a CMake-based tool. Your IDE may handle (part of) those features; please refer to its documentation.
As a fallback, [`arduino-cli`](https://arduino.github.io/arduino-cli/latest/) may also be used to these ends.
