/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#endif
#if GCC_VERSION < 60300
#error "GCC version 6.3 or higher is required"
#endif

// MCCI Arduino Version
#define _mcci_arduino_version_calc(major, minor, patch, local)	\
	(((major) << 24u) | ((minor) << 16u) | ((patch) << 8u) | (local))

#define	_mcci_arduino_version	_mcci_arduino_version_calc(2, 4, 0, 90)	/* v2.4.0.90 */

#define	_mcci_arduino_version_get_major(v)	\
	(((v) >> 24u) & 0xFFu)

#define	_mcci_arduino_version_get_minor(v)	\
	(((v) >> 16u) & 0xFFu)

#define	_mcci_arduino_version_get_patch(v)	\
	(((v) >> 8u) & 0xFFu)

#define	_mcci_arduino_version_get_local(v)	\
	((v) & 0xFFu)

#include "wiring.h"

/* sketch */

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
extern void setup( void ) ;
extern void loop( void ) ;

void yield(void);
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

// Include pins variant
#include "pins_arduino.h"

#endif // Arduino_h
