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
#if defined(ARDUINO_GENERIC_F302R6TX) || defined(ARDUINO_GENERIC_F302R8TX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_3,   // D3/A3
  PA_4,   // D4/A4
  PA_5,   // D5
  PA_6,   // D6/A5
  PA_7,   // D7/A6
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_0,   // D16/A7
  PB_1,   // D17/A8
  PB_2,   // D18
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_11,  // D27/A9
  PB_12,  // D28
  PB_13,  // D29/A10
  PB_14,  // D30
  PB_15,  // D31
  PC_0,   // D32/A11
  PC_1,   // D33/A12
  PC_2,   // D34/A13
  PC_3,   // D35/A14
  PC_4,   // D36
  PC_5,   // D37
  PC_6,   // D38
  PC_7,   // D39
  PC_8,   // D40
  PC_9,   // D41
  PC_10,  // D42
  PC_11,  // D43
  PC_12,  // D44
  PC_13,  // D45
  PC_14,  // D46
  PC_15,  // D47
  PD_2,   // D48
  PF_0,   // D49
  PF_1    // D50
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA4
  6,  // A5,  PA6
  7,  // A6,  PA7
  16, // A7,  PB0
  17, // A8,  PB1
  27, // A9,  PB11
  29, // A10, PB13
  32, // A11, PC0
  33, // A12, PC1
  34, // A13, PC2
  35  // A14, PC3
};

#endif /* ARDUINO_GENERIC_* */
