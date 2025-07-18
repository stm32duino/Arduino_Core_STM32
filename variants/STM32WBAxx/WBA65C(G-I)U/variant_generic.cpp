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
#if defined(ARDUINO_GENERIC_WBA65CGUX) || defined(ARDUINO_GENERIC_WBA65CIUX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_1,   // D0/A0
  PA_2,   // D1/A1
  PA_5,   // D2/A2
  PA_6,   // D3/A3
  PA_7,   // D4/A4
  PA_8,   // D5/A5
  PA_9,   // D6
  PA_10,  // D7
  PA_11,  // D8
  PA_12,  // D9
  PA_13,  // D10
  PA_14,  // D11
  PA_15,  // D12
  PB_0,   // D13
  PB_1,   // D14
  PB_2,   // D15
  PB_3,   // D16
  PB_4,   // D17
  PB_8,   // D18
  PB_12,  // D19
  PB_14,  // D20
  PB_15,  // D21
  PC_13,  // D22
  PC_14,  // D23
  PC_15,  // D24
  PD_6,   // D25
  PD_7,   // D26
  PD_8,   // D27
  PD_9,   // D28
  PH_3    // D29
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA1
  1,  // A1,  PA2
  2,  // A2,  PA5
  3,  // A3,  PA6
  4,  // A4,  PA7
  5   // A5,  PA8
};

#endif /* ARDUINO_GENERIC_* */
