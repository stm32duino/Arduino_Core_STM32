/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2013 by Paul Stoffregen <paul@pjrc.com> (delayMicroseconds)

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

#ifndef _WIRING_H_
#define _WIRING_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "avr/dtostrf.h"
#include "binary.h"
#include "itoa.h"

#include "wiring_analog.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "wiring_pulse.h"
#include "wiring_shift.h"
#include "wiring_time.h"
#include "WInterrupts.h"

#include <board.h>

#ifdef __cplusplus
  #include "HardwareTimer.h"
  #include "Tone.h"
  #include "WCharacter.h"
  #include "WSerial.h"
  #include "WMath.h"
  #include "WString.h"
#endif // __cplusplus


#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

#endif /* _WIRING_H_ */
