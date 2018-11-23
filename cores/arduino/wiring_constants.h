/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_CONSTANTS_
#define _WIRING_CONSTANTS_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
#include <algorithm>
using std::min;
using std::max;
#else // C
#include <stdlib.h>
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif // abs

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif // min

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif // max

#endif // __cplusplus

/* Official Arduino */
#define INPUT			    0x0
#define OUTPUT              0x1
#define INPUT_PULLUP        0x2
/* STM32 extension */
#define INPUT_FLOATING      INPUT
#define INPUT_PULLDOWN      0x3
#define INPUT_ANALOG        0x4
#define OUTPUT_OPEN_DRAIN   0x5

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

#define LOW     0x0
#define HIGH    0x1
#define CHANGE  0x2
#define FALLING 0x3
#define RISING  0x4

#define DEFAULT 1
#define EXTERNAL 0

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))
//macro added for compatibility
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#ifndef cbi
#define cbi(reg, bitmask) *reg &= ~bitmask
#endif
#ifndef sbi
#define sbi(reg, bitmask) *reg |= bitmask
#endif

typedef unsigned int word;

typedef bool boolean ;

typedef uint8_t byte ;

#endif /* _WIRING_CONSTANTS_ */
