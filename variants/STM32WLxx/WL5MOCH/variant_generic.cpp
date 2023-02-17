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
#if defined(ARDUINO_GENERIC_WL5MOCHX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3
  PA_4,   // D4
  PA_5,   // D5
  PA_6,   // D6
  PA_7,   // D7
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10/A0
  PA_11,  // D11/A1
  PA_12,  // D12/A2
  PA_13,  // D13/A3
  PA_14,  // D14/A4
  PA_15,  // D15/A5
  PB_1,   // D16/A6
  PB_2,   // D17/A7
  PB_3,   // D18/A8
  PB_4,   // D19/A9
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_9,   // D24
  PB_10,  // D25
  PB_11,  // D26
  PB_12,  // D27
  PB_13,  // D28/A10
  PB_14,  // D29/A11
  PB_15,  // D30
  PC_0,   // D31
  PC_1,   // D32
  PC_2,   // D33
  PC_6,   // D34
  PC_13,  // D35
  PH_3    // D36
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  10, // A0,  PA10
  11, // A1,  PA11
  12, // A2,  PA12
  13, // A3,  PA13
  14, // A4,  PA14
  15, // A5,  PA15
  16, // A6,  PB1
  17, // A7,  PB2
  18, // A8,  PB3
  19, // A9,  PB4
  28, // A10, PB13
  29  // A11, PB14
};

#endif /* ARDUINO_GENERIC_* */
