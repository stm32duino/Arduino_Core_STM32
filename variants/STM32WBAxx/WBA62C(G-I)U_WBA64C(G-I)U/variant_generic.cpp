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
#if defined(ARDUINO_GENERIC_WBA62CGUX) || defined(ARDUINO_GENERIC_WBA62CIUX) ||\
    defined(ARDUINO_GENERIC_WBA64CGUX) || defined(ARDUINO_GENERIC_WBA64CIUX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_1,   // D0/A0
  PA_2,   // D1/A1
  PA_3,   // D2/A2
  PA_5,   // D3/A3
  PA_6,   // D4/A4
  PA_7,   // D5/A5
  PA_8,   // D6/A6
  PA_9,   // D7
  PA_10,  // D8
  PA_11,  // D9
  PA_12,  // D10
  PA_13,  // D11
  PA_14,  // D12
  PA_15,  // D13
  PB_0,   // D14
  PB_1,   // D15
  PB_2,   // D16
  PB_3,   // D17
  PB_4,   // D18
  PB_8,   // D19
  PB_10,  // D20
  PB_11,  // D21
  PB_12,  // D22
  PB_13,  // D23
  PB_14,  // D24
  PB_15,  // D25
  PC_13,  // D26
  PC_14,  // D27
  PC_15,  // D28
  PD_6,   // D29
  PD_7,   // D30
  PD_8,   // D31
  PD_9,   // D32
  PH_3    // D33
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA1
  1,  // A1,  PA2
  2,  // A2,  PA3
  3,  // A3,  PA5
  4,  // A4,  PA6
  5,  // A5,  PA7
  6   // A6,  PA8
};

#endif /* ARDUINO_GENERIC_* */
