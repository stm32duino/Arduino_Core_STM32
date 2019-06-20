/*

Module: mcci_common_uart.h

Function:
    Common UART-steering macros for all variants in this package.

Copyright:
    See accompanying LICENSE file.

Author:
    Terry Moore, MCCI Corporation   June 2019

*/

#ifndef _MCCI_COMMON_UART_H_
# define _MCCI_COMMON_UART_H_

#pragma once

#ifndef _PERIPHERALPINS_H
# include "PeripheralPins.h"
#endif

/*

# Module documentation

This block of code establishes the following post-conditions.

1. ARDUINO_BSP_CONFIG_SERIAL_MASK is defined.  It is interpreted as a mask
   of ports to be configured.  Bit 0 enables USB serial. Bit 1 enables USART1.
   Bit 2 enables USART2. Bit 3 enables LPUAR1 as "Serial3". Bit 4 enables
   USART4. Bit 5 enables USART5.

2. Serial is defined as a reference variable to either `SerialNo` (if the
   serial mask is zero), to USB (if configured), otherwise to the lowest-
   numbered serial port that is enabled.

3. SERIAL_PORT_MONITOR is defined to Serial

4. SERIAL_PORT_USBVIRTUAL is defined to SerialUSB if configured,
   otherwise SerialNo.

5. SERIAL_PORT_HARDWARE is defined to the lowest configured physical
   serial port, otherwise SerialNo.

6. SERIAL_PORT_HARDWRE_OPEN, SERIAL_PORT_LINUXBRIDGE are left undefined.

7. PIN_SERIAL_RX and PIN_SERIAL_TX are defined to D0 and D1 if
   Serial1 is enabled, otherwise to -1 and -1.

Some constexprs are used, and are defined in the McciArduino namespace
for safety.

Note that support for a UART or a USB in this file does not imply
support on the targeted board. We assume info from the boards.txt
is correct.

`variant.h` originally only defined any of the following symbols if compiling
C++ code; otherwise Serial<whatever> isn't in scope. In refactoring this, we
decided to make some of these settings available to C compiles. However,
`variant.h` doesn't call this file unless it detects a C++ compile. You have to
explicitly include this file in a C compile if you want the macros and settings
available.

*/

#define ARDUINO_BSP_SERIAL_UART_IS_ENABLED(iSerial) \
         (((iSerial) > 0) &&   \
         ((ARDUINO_BSP_CONFIG_SERIAL_MASK & (1u << (iSerial))) != 0))

#define ARDUINO_BSP_SERIAL_USB_IS_ENABLED() \
        ((ARDUINO_BSP_CONFIG_SERIAL_MASK & 1) != 0)

#define ARDUINO_BSP_SERIAL_ANY_UART_IS_ENABLED() \
        ((ARDUINO_BSP_CONFIG_SERIAL_MASK & ~1u) != 0)

//
// If ARDUINO_BSP_CONFIG_SERIAL_MASK is not defined, we try to calculate a suitable
// value based on other configuration settings.
//
// Post-condition: ARDUINO_BSP_CONFIG_SERiAL_MASK is defined
//
#ifndef ARDUINO_BSP_CONFIG_SERIAL_MASK

  // we want to encourage people to migrate, but we'll be gentle for now.
  // however, we'll enforce this more rigorously in the future.
# warning "ARDUINO_BSP_CONFIG_SERIAL_MASK must be defined in boards.txt"

  //
  // compute a suitable value for ARDUINO_BSP_CONFIG_SERIAL_MASK
  //
# if defined(NO_HWSERIAL) && ! defined(USBCON)
   // legacy configuration: no USB serial, no UART
#  define ARDUINO_BSP_CONFIG_SERIAL_MASK    0
# elif defined(NO_HWSERIAL) && defined(USBCON)
   // legacy configuration: USB serial, no UART
#  define ARDUINO_BSP_CONFIG_SERIAL_MASK    1
# elif defined(FIRST_THIRD_HWSERIAL)
#  error "FIRST_THIRD_HWSERIAL Not supported for this BSP, use ARDUINO_BSP_CONFIG_SERIAL_MASK"
# elif defined(ALL_HWSERIAL)
#  error "ALL_HWSERIAL Not supported for this BSP, use ARDUINO_BSP_CONFIG_SERIAL_MASK"
# elif defined(USBCON)
   // USB, no UART
#  define ARDUINO_BSP_CONFIG_SERIAL_MASK    1
# else
   // with no other knowledge, assume generic uart, no USB
#  define ARDUINO_BSP_CONFIG_SERIAL_MASK    2
# endif
#endif /* ndef ARDUINO_BSP_CONFIG_SERIAL_MASK */

//
// check that the explicit configuration doesn't conflict with the
// configuration implied by -D switches on the compile line.
//
#if defined(USBCON) && ! ARDUINO_BSP_SERIAL_USB_IS_ENABLED()
# error "USBCON defined but not enabled in ARDUINO_BSP_CONFIG_SERIAL_MASK"
#endif

#if ! defined(USBCON) && ARDUINO_BSP_SERIAL_USB_IS_ENABLED()
// we'll take care of this below.
#endif

#if defined(NO_HWSERIAL) && ARDUINO_BSP_SERIAL_ANY_UART_IS_ENABLED()
# error "NO_HWSERIAL defined but uarts are enabled in ARDUINO_BSP_CONFIG_SERIAL_MASK"
#endif

#if !defined(NO_HWSERIAL) && !ARDUINO_BSP_SERIAL_ANY_UART_IS_ENABLED()
// we'll take care of this below.
#endif

//
// Post condition: Serial and SerialEvent are pointing to the desired Serial<x>,
// and SERIAL_PORT_MONITOR points to the desired Serial<x>.
//
// This is C++ only.
//
#ifdef __cplusplus
# if ARDUINO_BSP_SERIAL_USB_IS_ENABLED()
#  define Serial SerialUSB
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(1)
#  define Serial Serial1
#  define SerialEvent SerialEvent1
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(2)
#  define Serial Serial2
#  define SerialEvent SerialEvent2
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(3)
#  define Serial Serial3
#  define SerialEvent SerialEvent3
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(4)
#  define Serial Serial4
#  define SerialEvent SerialEvent4
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(5)
#  define Serial Serial5
#  define SerialEvent SerialEvent5
# else
#  define Serial SerialNo
# endif
# define SERIAL_PORT_MONITOR    Serial
#endif // __cplusplus

//
// Post condition: SERIAL_PORT_HARDWARE is the lowest-numbered HardwareSerial
// Serial<x> port.
//
// C++ only
//
#ifdef __cplusplus
# if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(1)
#  define SERIAL_PORT_HARDWARE   Serial1
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(2)
#  define SERIAL_PORT_HARDWARE   Serial2
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(3)
#  define SERIAL_PORT_HARDWARE   Serial3
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(4)
#  define SERIAL_PORT_HARDWARE   Serial4
# elif ARDUINO_BSP_SERIAL_UART_IS_ENABLED(5)
#  define SERIAL_PORT_HARDWARE   Serial5
# else
#  define SERIAL_PORT_HARDWARE   SerialNo
# endif
#endif // __cplusplus

//
// Post condition: the appropriate ENABLE_HWSERIALx or NO_HWSERIAL symbols
// are defined, based on the configuration.
//
// This is C or C++.
//
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(1)
# define ENABLE_HWSERIAL1
#endif
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(2)
# define ENABLE_HWSERIAL2
#endif
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(3)
# define ENABLE_HWSERIAL3
#endif
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(4)
# define ENABLE_HWSERIAL4
#endif
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(5)
# define ENABLE_HWSERIAL5
#endif
#if ! ARDUINO_BSP_SERIAL_ANY_UART_IS_ENABLED()
# define NO_HWSERIAL
#endif

//
// Post-condition: PIN_SERIAL_RX and _TX are defined.
// to be D0 and D1, otherwise -1/-1, based on UART1
// being enabled.
//
// This is C or C++
//
#if ARDUINO_BSP_SERIAL_UART_IS_ENABLED(1)
# define PIN_SERIAL_RX           D0
# define PIN_SERIAL_TX           D1
#else
# define PIN_SERIAL_RX           (-1)
# define PIN_SERIAL_TX           (-1)
#endif

// end of file.
#endif /* _MCCI_COMMON_UART_H_ */
