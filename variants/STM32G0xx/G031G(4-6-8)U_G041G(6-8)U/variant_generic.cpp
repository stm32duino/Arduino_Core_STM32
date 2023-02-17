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
#if defined(ARDUINO_GENERIC_G031G4UX) || defined(ARDUINO_GENERIC_G031G6UX) ||\
    defined(ARDUINO_GENERIC_G031G8UX) || defined(ARDUINO_GENERIC_G041G6UX) ||\
    defined(ARDUINO_GENERIC_G041G8UX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_3,   // D3/A3
  PA_4,   // D4/A4
  PA_5,   // D5/A5
  PA_6,   // D6/A6
  PA_7,   // D7/A7
  PA_8,   // D8
  PA_11,  // D9/A8
  PA_12,  // D10/A9
  PA_13,  // D11/A10
  PA_14,  // D12/A11
  PA_15,  // D13
  PB_0,   // D14/A12
  PB_1,   // D15/A13
  PB_3,   // D16
  PB_4,   // D17
  PB_5,   // D18
  PB_6,   // D19
  PB_7,   // D20/A14
  PB_8,   // D21
  PC_6,   // D22
  PC_14,  // D23
  PC_15,  // D24
  PF_2,   // D25
  PA_9_R, // D26
  PA_10_R // D27
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA4
  5,  // A5,  PA5
  6,  // A6,  PA6
  7,  // A7,  PA7
  9,  // A8,  PA11
  10, // A9,  PA12
  11, // A10, PA13
  12, // A11, PA14
  14, // A12, PB0
  15, // A13, PB1
  20  // A14, PB7
};

#endif /* ARDUINO_GENERIC_* */
