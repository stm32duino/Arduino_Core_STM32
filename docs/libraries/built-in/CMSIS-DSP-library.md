# CMSIS-DSP

Available in core version greater than **1.7.0**

CMSIS-DSP is a suite of common signal-processing functions for Cortex-M devices.

The library is divided into a number of functions each covering a specific category:

- Basic math functions
- Fast math functions
- Complex math functions
- Filters
- Matrix functions
- Transform functions
- Motor control functions
- Statistical functions
- Support functions
- Interpolation functions.

The library has separate functions for operating on 8-bit integers, 16-bit integers, 32-bit integers and 32-bit floating-point values.

More info:

For cores based on CMSIS 6, CMSIS-DSP is provided as a separate package with its own version.
See the [CMSIS-DSP documentation](https://arm-software.github.io/CMSIS-DSP/) and the
[CMSIS-DSP repository](https://github.com/ARM-software/CMSIS-DSP) for package and source details.

For cores based on CMSIS 5, see the legacy documentation:
https://arm-software.github.io/CMSIS_5/DSP/html/index.html

To use it, include:
```C++
#include <CMSIS_DSP.h>
```

`arm_math.h` is then included automatically.
