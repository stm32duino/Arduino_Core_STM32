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
#if defined(ARDUINO_GENERIC_U595RITXQ) || defined(ARDUINO_GENERIC_U595RJTXQ) ||\
    defined(ARDUINO_GENERIC_U5A5RJTXQ)
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
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_0,   // D16/A8
  PB_1,   // D17/A9
  PB_2,   // D18/A10
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_10,  // D25
  PB_13,  // D26
  PB_14,  // D27
  PB_15,  // D28
  PC_0,   // D29/A11
  PC_1,   // D30/A12
  PC_2,   // D31/A13
  PC_3,   // D32/A14
  PC_6,   // D33
  PC_7,   // D34
  PC_8,   // D35
  PC_9,   // D36
  PC_10,  // D37
  PC_11,  // D38
  PC_12,  // D39
  PC_13,  // D40
  PC_14,  // D41
  PC_15,  // D42
  PD_2,   // D43
  PH_0,   // D44
  PH_1,   // D45
  PH_3    // D46
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
  16, // A8,  PB0
  17, // A9,  PB1
  18, // A10, PB2
  29, // A11, PC0
  30, // A12, PC1
  31, // A13, PC2
  32  // A14, PC3
};

#endif /* ARDUINO_GENERIC_* */
