/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_GENERIC_WBA52CEUX) || defined(ARDUINO_GENERIC_WBA52CGUX) ||\
    defined(ARDUINO_GENERIC_WBA54CEUX) || defined(ARDUINO_GENERIC_WBA54CGUX) ||\
    defined(ARDUINO_GENERIC_WBA55HEFX) || defined(ARDUINO_GENERIC_WBA55HGFX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_3,   // D3/A3
  PA_5,   // D4/A4
  PA_6,   // D5/A5
  PA_7,   // D6/A6
  PA_8,   // D7/A7
  PA_9,   // D8
  PA_10,  // D9
  PA_11,  // D10
  PA_12,  // D11
  PA_13,  // D12
  PA_14,  // D13
  PA_15,  // D14
  PB_0,   // D15
  PB_1,   // D16
  PB_2,   // D17
  PB_3,   // D18
  PB_4,   // D19
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_9,   // D24/A8
  PB_10,  // D25
  PB_11,  // D26
  PB_12,  // D27
  PB_13,  // D28
  PB_14,  // D29
  PB_15,  // D30
  PC_13,  // D31
  PC_14,  // D32
  PC_15,  // D33
  PH_3    // D34
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA5
  5,  // A5,  PA6
  6,  // A6,  PA7
  7,  // A7,  PA8
  24  // A8,  PB9
};

#endif /* ARDUINO_GENERIC_* */
