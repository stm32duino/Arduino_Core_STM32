/*
  Boards.h - Hardware Abstraction Layer for Firmata library
  Copyright (c) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2009-2015 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  Last updated December 19th, 2015
*/

#ifndef Firmata_Boards_h
#define Firmata_Boards_h

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"  // for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

// Normally Servo.h must be included before Firmata.h (which then includes
// this file).  If Servo.h wasn't included, this allows the code to still
// compile, but without support for any Servos.  Hopefully that's what the
// user intended by not including Servo.h
#ifndef MAX_SERVOS
#define MAX_SERVOS 0
#endif

/*
    Firmata Hardware Abstraction Layer

Firmata is built on top of the hardware abstraction functions of Arduino,
specifically digitalWrite, digitalRead, analogWrite, analogRead, and
pinMode.  While these functions offer simple integer pin numbers, Firmata
needs more information than is provided by Arduino.  This file provides
all other hardware specific details.  To make Firmata support a new board,
only this file should require editing.

The key concept is every "pin" implemented by Firmata may be mapped to
any pin as implemented by Arduino.  Usually a simple 1-to-1 mapping is
best, but such mapping should not be assumed.  This hardware abstraction
layer allows Firmata to implement any number of pins which map onto the
Arduino implemented pins in almost any arbitrary way.


General Constants:

These constants provide basic information Firmata requires.

TOTAL_PINS: The total number of pins Firmata implemented by Firmata.
    Usually this will match the number of pins the Arduino functions
    implement, including any pins pins capable of analog or digital.
    However, Firmata may implement any number of pins.  For example,
    on Arduino Mini with 8 analog inputs, 6 of these may be used
    for digital functions, and 2 are analog only.  On such boards,
    Firmata can implement more pins than Arduino's pinMode()
    function, in order to accommodate those special pins.  The
    Firmata protocol supports a maximum of 128 pins, so this
    constant must not exceed 128.

TOTAL_ANALOG_PINS: The total number of analog input pins implemented.
    The Firmata protocol allows up to 16 analog inputs, accessed
    using offsets 0 to 15.  Because Firmata presents the analog
    inputs using different offsets than the actual pin numbers
    (a legacy of Arduino's analogRead function, and the way the
    analog input capable pins are physically labeled on all
    Arduino boards), the total number of analog input signals
    must be specified.  16 is the maximum.

VERSION_BLINK_PIN: When Firmata starts up, it will blink the version
    number.  This constant is the Arduino pin number where a
    LED is connected.


Pin Mapping Macros:

These macros provide the mapping between pins as implemented by
Firmata protocol and the actual pin numbers used by the Arduino
functions.  Even though such mappings are often simple, pin
numbers received by Firmata protocol should always be used as
input to these macros, and the result of the macro should be
used with with any Arduino function.

When Firmata is extended to support a new pin mode or feature,
a pair of macros should be added and used for all hardware
access.  For simple 1:1 mapping, these macros add no actual
overhead, yet their consistent use allows source code which
uses them consistently to be easily adapted to all other boards
with different requirements.

IS_PIN_XXXX(pin): The IS_PIN macros resolve to true or non-zero
    if a pin as implemented by Firmata corresponds to a pin
    that actually implements the named feature.

PIN_TO_XXXX(pin): The PIN_TO macros translate pin numbers as
    implemented by Firmata to the pin numbers needed as inputs
    to the Arduino functions.  The corresponding IS_PIN macro
    should always be tested before using a PIN_TO macro, so
    these macros only need to handle valid Firmata pin
    numbers for the named feature.


Port Access Inline Funtions:

For efficiency, Firmata protocol provides access to digital
input and output pins grouped by 8 bit ports.  When these
groups of 8 correspond to actual 8 bit ports as implemented
by the hardware, these inline functions can provide high
speed direct port access.  Otherwise, a default implementation
using 8 calls to digitalWrite or digitalRead is used.

When porting Firmata to a new board, it is recommended to
use the default functions first and focus only on the constants
and macros above.  When those are working, if optimized port
access is desired, these inline functions may be extended.
The recommended approach defines a symbol indicating which
optimization to use, and then conditional complication is
used within these functions.

readPort(port, bitmask):  Read an 8 bit port, returning the value.
   port:    The port number, Firmata pins port*8 to port*8+7
   bitmask: The actual pins to read, indicated by 1 bits.

writePort(port, value, bitmask):  Write an 8 bit port.
   port:    The port number, Firmata pins port*8 to port*8+7
   value:   The 8 bit value to write
   bitmask: The actual pins to write, indicated by 1 bits.
*/

/*==============================================================================
 * Board Specific Configuration
 *============================================================================*/

#ifndef digitalPinHasPWM
#define digitalPinHasPWM(p)     IS_PIN_DIGITAL(p)
#endif

// Arduino Duemilanove, Diecimila, and NG
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#if defined(NUM_ANALOG_INPUTS) && NUM_ANALOG_INPUTS == 6
#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              20 // 14 digital + 6 analog
#else
#define TOTAL_ANALOG_PINS       8
#define TOTAL_PINS              22 // 14 digital + 8 analog
#endif
#define VERSION_BLINK_PIN       13
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) <= 19)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) < 14 + TOTAL_ANALOG_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) - 2 < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 18 || (p) == 19)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)
#define ARDUINO_PINOUT_OPTIMIZE 1


// Wiring (and board)
#elif defined(WIRING)
#define VERSION_BLINK_PIN       WLED
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= FIRST_ANALOG_PIN && (p) < (FIRST_ANALOG_PIN+TOTAL_ANALOG_PINS))
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == SDA || (p) == SCL)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - FIRST_ANALOG_PIN)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// old Arduinos
#elif defined(__AVR_ATmega8__)
#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              20 // 14 digital + 6 analog
#define VERSION_BLINK_PIN       13
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) <= 19)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 19)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) - 2 < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 18 || (p) == 19)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)
#define ARDUINO_PINOUT_OPTIMIZE 1


// Arduino Mega
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TOTAL_ANALOG_PINS       16
#define TOTAL_PINS              70 // 54 digital + 16 analog
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          19
#define PIN_SERIAL1_TX          18
#define PIN_SERIAL2_RX          17
#define PIN_SERIAL2_TX          16
#define PIN_SERIAL3_RX          15
#define PIN_SERIAL3_TX          14
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 54 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 2 && (p) - 2 < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 20 || (p) == 21)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) > 13 && (p) < 20)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 54)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)


// Arduino DUE
#elif defined(__SAM3X8E__)
#define TOTAL_ANALOG_PINS       12
#define TOTAL_PINS              66 // 54 digital + 12 analog
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          19
#define PIN_SERIAL1_TX          18
#define PIN_SERIAL2_RX          17
#define PIN_SERIAL2_TX          16
#define PIN_SERIAL3_RX          15
#define PIN_SERIAL3_TX          14
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 54 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 2 && (p) - 2 < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 20 || (p) == 21) // 70 71
#define IS_PIN_SERIAL(p)        ((p) > 13 && (p) < 20)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 54)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)


// Arduino/Genuino MKR1000
#elif defined(ARDUINO_SAMD_MKR1000)
#define TOTAL_ANALOG_PINS       7
#define TOTAL_PINS              22 // 8 digital + 3 spi + 2 i2c + 2 uart + 7 analog
#define IS_PIN_DIGITAL(p)       (((p) >= 0 && (p) <= 21) && !IS_PIN_SERIAL(p))
#define IS_PIN_ANALOG(p)        ((p) >= 15 && (p) < 15 + TOTAL_ANALOG_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) < MAX_SERVOS) // deprecated since v2.4
#define IS_PIN_I2C(p)           ((p) == 11 || (p) == 12) // SDA = 11, SCL = 12
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == PIN_SERIAL1_RX || (p) == PIN_SERIAL1_TX) //defined in variant.h  RX = 13, TX = 14
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 15)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p) // deprecated since v2.4


// Arduino Zero
// Note this will work with an Arduino Zero Pro, but not with an Arduino M0 Pro
// Arduino M0 Pro does not properly map pins to the board labeled pin numbers
#elif defined(_VARIANT_ARDUINO_ZERO_)
#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              25 // 14 digital + 6 analog + 2 i2c + 3 spi
#define TOTAL_PORTS             3  // set when TOTAL_PINS > num digitial I/O pins
#define VERSION_BLINK_PIN       LED_BUILTIN
//#define PIN_SERIAL1_RX          0 // already defined in zero core variant.h
//#define PIN_SERIAL1_TX          1 // already defined in zero core variant.h
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) <= 19)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) < 14 + TOTAL_ANALOG_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) < MAX_SERVOS) // deprecated since v2.4
#define IS_PIN_I2C(p)           ((p) == 20 || (p) == 21) // SDA = 20, SCL = 21
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK) // SS = A2
#define IS_PIN_SERIAL(p)        ((p) == 0 || (p) == 1)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p) // deprecated since v2.4


// Teensy 1.0
#elif defined(_VARIANT_ARDUINO_101_X_)
#define TOTAL_ANALOG_PINS       NUM_ANALOG_INPUTS
#define TOTAL_PINS              NUM_DIGITAL_PINS // 15 digital (including ATN pin) + 6 analog
#define VERSION_BLINK_PIN       LED_BUILTIN
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) <= 20)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) < 14 + TOTAL_ANALOG_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p) // 3, 5, 6, 9
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) < MAX_SERVOS) // deprecated since v2.4
#define IS_PIN_I2C(p)           ((p) == SDA || (p) == SCL) // SDA = 18, SCL = 19
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 0 || (p) == 1)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p) // deprecated since v2.4


// Teensy 1.0
#elif defined(__AVR_AT90USB162__)
#define TOTAL_ANALOG_PINS       0
#define TOTAL_PINS              21 // 21 digital + no analog
#define VERSION_BLINK_PIN       6
#define PIN_SERIAL1_RX          2
#define PIN_SERIAL1_TX          3
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        (0)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           (0)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 2 || (p) == 3)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (0)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Teensy 2.0
#elif defined(__AVR_ATmega32U4__) && defined(CORE_TEENSY)
#define TOTAL_ANALOG_PINS       12
#define TOTAL_PINS              25 // 11 digital + 12 analog
#define VERSION_BLINK_PIN       11
#define PIN_SERIAL1_RX          7
#define PIN_SERIAL1_TX          8
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 11 && (p) <= 22)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 5 || (p) == 6)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 7 || (p) == 8)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (((p) < 22) ? 21 - (p) : 11)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Teensy 3.0, 3.1 and 3.2
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
#define TOTAL_ANALOG_PINS       14
#define TOTAL_PINS              38 // 24 digital + 10 analog-digital + 4 analog
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define PIN_SERIAL2_RX          9
#define PIN_SERIAL2_TX          10
#define PIN_SERIAL3_RX          7
#define PIN_SERIAL3_TX          8
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) <= 33)
#define IS_PIN_ANALOG(p)        (((p) >= 14 && (p) <= 23) || ((p) >= 34 && (p) <= 38))
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 18 || (p) == 19)
#define IS_PIN_SERIAL(p)        (((p) > 6 && (p) < 11) || ((p) == 0 || (p) == 1))
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (((p) <= 23) ? (p) - 14 : (p) - 24)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Teensy-LC
#elif defined(__MKL26Z64__)
#define TOTAL_ANALOG_PINS       13
#define TOTAL_PINS              27 // 27 digital + 13 analog-digital
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define PIN_SERIAL2_RX          9
#define PIN_SERIAL2_TX          10
#define PIN_SERIAL3_RX          7
#define PIN_SERIAL3_TX          8
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) <= 26)
#define IS_PIN_ANALOG(p)        ((p) >= 14)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 18 || (p) == 19)
#define IS_PIN_SERIAL(p)        (((p) > 6 && (p) < 11) || ((p) == 0 || (p) == 1))
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Teensy++ 1.0 and 2.0
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define TOTAL_ANALOG_PINS       8
#define TOTAL_PINS              46 // 38 digital + 8 analog
#define VERSION_BLINK_PIN       6
#define PIN_SERIAL1_RX          2
#define PIN_SERIAL1_TX          3
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 38 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 0 || (p) == 1)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 2 || (p) == 3)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 38)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Leonardo
#elif defined(__AVR_ATmega32U4__)
#define TOTAL_ANALOG_PINS       12
#define TOTAL_PINS              30 // 14 digital + 12 analog + 4 SPI (D14-D17 on ISP header)
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define IS_PIN_DIGITAL(p)       ((p) >= 0 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 18 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11 || (p) == 13)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 2 || (p) == 3)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 0 || (p) == 1)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (p) - 18
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         (p)


// Intel Galileo Board (gen 1 and 2) and Intel Edison
#elif defined(ARDUINO_LINUX)
#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              20 // 14 digital + 6 analog
#define VERSION_BLINK_PIN       13
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) <= 19)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 19)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         (IS_PIN_DIGITAL(p) && (p) - 2 < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == SDA || (p) == SCL)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 0 || (p) == 1)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)


// Sanguino
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
#define TOTAL_ANALOG_PINS       8
#define TOTAL_PINS              32 // 24 digital + 8 analog
#define VERSION_BLINK_PIN       0
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 24 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 16 || (p) == 17)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 24)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)


// Illuminato
#elif defined(__AVR_ATmega645__)
#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              42 // 36 digital + 6 analog
#define VERSION_BLINK_PIN       13
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) < TOTAL_PINS)
#define IS_PIN_ANALOG(p)        ((p) >= 36 && (p) < TOTAL_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         ((p) >= 0 && (p) < MAX_SERVOS)
#define IS_PIN_I2C(p)           ((p) == 4 || (p) == 5)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 36)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)


// Pic32 chipKIT FubarinoSD
#elif defined(_BOARD_FUBARINO_SD_)
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS  // 15
#define TOTAL_PINS              NUM_DIGITAL_PINS // 45, All pins can be digital
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       1
#define IS_PIN_ANALOG(p)        ((p) >= 30 && (p) <= 44)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 1 || (p) == 2)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (14 - (p - 30))
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT FubarinoMini
// Note, FubarinoMini analog pin 20 will not function in Firmata as analog input due to limitation in analog mapping
#elif defined(_BOARD_FUBARINO_MINI_)
#define TOTAL_ANALOG_PINS       14 // We have to fake this because of the poor analog pin mapping planning in FubarinoMini
#define TOTAL_PINS              NUM_DIGITAL_PINS // 33
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) != 14 && (p) != 15 && (p) != 31 && (p) != 32)
#define IS_PIN_ANALOG(p)        ((p) == 0 || ((p) >= 3 && (p) <= 13))
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 25 || (p) == 26)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (p)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT UNO32
#elif defined(_BOARD_UNO_) && defined(__PIC32)  // NOTE: no _BOARD_UNO32_ to use
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS // 12
#define TOTAL_PINS              NUM_DIGITAL_PINS // 47 All pins can be digital
#define MAX_SERVOS              NUM_DIGITAL_PINS // All pins can be servo with SoftPWMservo
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) >= 2)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 25)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 45 || (p) == 46)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT DP32
#elif defined(_BOARD_DP32_)
#define TOTAL_ANALOG_PINS       15  // Really only has 9, but have to override because of mistake in variant file
#define TOTAL_PINS              NUM_DIGITAL_PINS // 19
#define MAX_SERVOS              NUM_DIGITAL_PINS // All pins can be servo with SoftPWMservo
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       (((p) != 1) && ((p) != 4) && ((p) != 5) && ((p) != 15) && ((p) != 16))
#define IS_PIN_ANALOG(p)        ((p) >= 6 && (p) <= 14)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 2 || (p) == 3)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (p)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT uC32
#elif defined(_BOARD_UC32_)
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS  // 12
#define TOTAL_PINS              NUM_DIGITAL_PINS // 47 All pins can be digital
#define MAX_SERVOS              NUM_DIGITAL_PINS // All pins can be servo with SoftPWMservo
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) >= 2)
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 25)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 45 || (p) == 46)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT WF32
#elif defined(_BOARD_WF32_)
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS
#define TOTAL_PINS              NUM_DIGITAL_PINS
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) <= 49)     // Accounts for SD and WiFi dedicated pins
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 25)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 34 || (p) == 35)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT WiFire
#elif defined(_BOARD_WIFIRE_)
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS  // 14
#define TOTAL_PINS              NUM_DIGITAL_PINS // 71
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) >= 2 && (p) <= 47)     // Accounts for SD and WiFi dedicated pins
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 25)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 34 || (p) == 35)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) <= 25 ? ((p) - 14) : (p) - 36)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT MAX32
#elif defined(_BOARD_MEGA_) && defined(__PIC32)  // NOTE: no _BOARD_MAX32_ to use
#define TOTAL_ANALOG_PINS       NUM_ANALOG_PINS  // 16
#define TOTAL_PINS              NUM_DIGITAL_PINS // 87
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       ((p) >= 2)
#define IS_PIN_ANALOG(p)        ((p) >= 54 && (p) <= 69)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 34 || (p) == 35)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 54)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)


// Pic32 chipKIT Pi
#elif defined(_BOARD_CHIPKIT_PI_)
#define TOTAL_ANALOG_PINS       16
#define TOTAL_PINS              NUM_DIGITAL_PINS // 19
#define MAX_SERVOS              NUM_DIGITAL_PINS
#define VERSION_BLINK_PIN       PIN_LED1
#define IS_PIN_DIGITAL(p)       (((p) >= 2) && ((p) <= 3) || (((p) >= 8) && ((p) <= 13)) || (((p) >= 14) && ((p) <= 17)))
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) <= 17)
#define IS_PIN_PWM(p)           IS_PIN_DIGITAL(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == 16 || (p) == 17)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) <= 15 ? (p) - 14 : (p) - 12)
//#define PIN_TO_ANALOG(p)        (((p) <= 16) ? ((p) - 14) : ((p) - 16))
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)

// Pinoccio Scout
// Note: digital pins 9-16 are usable but not labeled on the board numerically.
// SS=9, MOSI=10, MISO=11, SCK=12, RX1=13, TX1=14, SCL=15, SDA=16
#elif defined(ARDUINO_PINOCCIO)
#define TOTAL_ANALOG_PINS       8
#define TOTAL_PINS              NUM_DIGITAL_PINS // 32
#define VERSION_BLINK_PIN       23
#define PIN_SERIAL1_RX          13
#define PIN_SERIAL1_TX          14
#define IS_PIN_DIGITAL(p)       (((p) >= 2) && ((p) <= 16)) || (((p) >= 24) && ((p) <= 31))
#define IS_PIN_ANALOG(p)        ((p) >= 24 && (p) <= 31)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           ((p) == SCL || (p) == SDA)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 13 || (p) == 14)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 24)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)
#define PIN_TO_SERVO(p)         ((p) - 2)

// STM32 based boards
#elif defined(STM32)
#define TOTAL_ANALOG_PINS       MAX_ANALOG_IOS
#define TOTAL_PINS              MAX_DIGITAL_IOS
#define TOTAL_PORTS             MAX_NB_PORT
#define VERSION_BLINK_PIN       LED_BUILTIN
// PIN_SERIALY_RX/TX defined in the variant.h
#define IS_PIN_DIGITAL(p)       ((p != PIN_SERIAL_RX) && (p != PIN_SERIAL_TX) &&(p < TOTAL_PINS))
#define IS_PIN_ANALOG(p)        (pin_in_pinmap(digitalToPinName(p), PinMap_ADC))
#define IS_PIN_PWM(p)           (pin_in_pinmap(digitalToPinName(p), PinMap_PWM))
#define IS_PIN_SERVO(p)         IS_PIN_DIGITAL(p)
#define IS_PIN_I2C(p)           (pin_in_pinmap(digitalToPinName(p), PinMap_I2C_SDA) || pin_in_pinmap(digitalToPinName(p), PinMap_I2C_SCL))
#define IS_PIN_SPI(p)           (pin_in_pinmap(digitalToPinName(p), PinMap_SPI_MOSI) || pin_in_pinmap(digitalToPinName(p), PinMap_SPI_MISO) ||\
                                 pin_in_pinmap(digitalToPinName(p), PinMap_SPI_SCLK) || pin_in_pinmap(digitalToPinName(p), PinMap_SPI_SSEL))
#define IS_PIN_SERIAL(p)        (pin_in_pinmap(digitalToPinName(p), PinMap_UART_RX) || pin_in_pinmap(digitalToPinName(p), PinMap_UART_TX))
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (p)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)

// anything else
#else
#error "Please edit Boards.h with a hardware abstraction for this board"
#endif

// as long this is not defined for all boards:
#ifndef IS_PIN_SPI
#define IS_PIN_SPI(p)           0
#endif

#ifndef IS_PIN_SERIAL
#define IS_PIN_SERIAL(p)        0
#endif


/*==============================================================================
 * readPort() - Read an 8 bit port
 *============================================================================*/

static inline unsigned char readPort(byte, byte) __attribute__((always_inline, unused));
static inline unsigned char readPort(byte port, byte bitmask)
{
#if defined(ARDUINO_PINOUT_OPTIMIZE)
  if (port == 0) return (PIND & 0xFC) & bitmask; // ignore Rx/Tx 0/1
  if (port == 1) return ((PINB & 0x3F) | ((PINC & 0x03) << 6)) & bitmask;
  if (port == 2) return ((PINC & 0x3C) >> 2) & bitmask;
  return 0;
#else
  unsigned char out = 0, pin = port * 8;
  if (IS_PIN_DIGITAL(pin + 0) && (bitmask & 0x01) && digitalRead(PIN_TO_DIGITAL(pin + 0))) out |= 0x01;
  if (IS_PIN_DIGITAL(pin + 1) && (bitmask & 0x02) && digitalRead(PIN_TO_DIGITAL(pin + 1))) out |= 0x02;
  if (IS_PIN_DIGITAL(pin + 2) && (bitmask & 0x04) && digitalRead(PIN_TO_DIGITAL(pin + 2))) out |= 0x04;
  if (IS_PIN_DIGITAL(pin + 3) && (bitmask & 0x08) && digitalRead(PIN_TO_DIGITAL(pin + 3))) out |= 0x08;
  if (IS_PIN_DIGITAL(pin + 4) && (bitmask & 0x10) && digitalRead(PIN_TO_DIGITAL(pin + 4))) out |= 0x10;
  if (IS_PIN_DIGITAL(pin + 5) && (bitmask & 0x20) && digitalRead(PIN_TO_DIGITAL(pin + 5))) out |= 0x20;
  if (IS_PIN_DIGITAL(pin + 6) && (bitmask & 0x40) && digitalRead(PIN_TO_DIGITAL(pin + 6))) out |= 0x40;
  if (IS_PIN_DIGITAL(pin + 7) && (bitmask & 0x80) && digitalRead(PIN_TO_DIGITAL(pin + 7))) out |= 0x80;
  return out;
#endif
}

/*==============================================================================
 * writePort() - Write an 8 bit port, only touch pins specified by a bitmask
 *============================================================================*/

static inline unsigned char writePort(byte, byte, byte) __attribute__((always_inline, unused));
static inline unsigned char writePort(byte port, byte value, byte bitmask)
{
#if defined(ARDUINO_PINOUT_OPTIMIZE)
  if (port == 0) {
    bitmask = bitmask & 0xFC;  // do not touch Tx & Rx pins
    byte valD = value & bitmask;
    byte maskD = ~bitmask;
    cli();
    PORTD = (PORTD & maskD) | valD;
    sei();
  } else if (port == 1) {
    byte valB = (value & bitmask) & 0x3F;
    byte valC = (value & bitmask) >> 6;
    byte maskB = ~(bitmask & 0x3F);
    byte maskC = ~((bitmask & 0xC0) >> 6);
    cli();
    PORTB = (PORTB & maskB) | valB;
    PORTC = (PORTC & maskC) | valC;
    sei();
  } else if (port == 2) {
    bitmask = bitmask & 0x0F;
    byte valC = (value & bitmask) << 2;
    byte maskC = ~(bitmask << 2);
    cli();
    PORTC = (PORTC & maskC) | valC;
    sei();
  }
  return 1;
#else
  byte pin = port * 8;
  if ((bitmask & 0x01)) digitalWrite(PIN_TO_DIGITAL(pin + 0), (value & 0x01));
  if ((bitmask & 0x02)) digitalWrite(PIN_TO_DIGITAL(pin + 1), (value & 0x02));
  if ((bitmask & 0x04)) digitalWrite(PIN_TO_DIGITAL(pin + 2), (value & 0x04));
  if ((bitmask & 0x08)) digitalWrite(PIN_TO_DIGITAL(pin + 3), (value & 0x08));
  if ((bitmask & 0x10)) digitalWrite(PIN_TO_DIGITAL(pin + 4), (value & 0x10));
  if ((bitmask & 0x20)) digitalWrite(PIN_TO_DIGITAL(pin + 5), (value & 0x20));
  if ((bitmask & 0x40)) digitalWrite(PIN_TO_DIGITAL(pin + 6), (value & 0x40));
  if ((bitmask & 0x80)) digitalWrite(PIN_TO_DIGITAL(pin + 7), (value & 0x80));
  return 1;
#endif
}




#ifndef TOTAL_PORTS
#define TOTAL_PORTS             ((TOTAL_PINS + 7) / 8)
#endif


#endif /* Firmata_Boards_h */
