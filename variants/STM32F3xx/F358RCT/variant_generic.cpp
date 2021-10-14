/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_GENERIC_F358RCTX)
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
  PB_3,   // D18
  PB_4,   // D19
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_9,   // D24
  PB_10,  // D25
  PB_11,  // D26
  PB_12,  // D27/A10
  PB_13,  // D28/A11
  PB_14,  // D29/A12
  PB_15,  // D30/A13
  PC_0,   // D31/A14
  PC_1,   // D32/A15
  PC_2,   // D33/A16
  PC_3,   // D34/A17
  PC_4,   // D35/A18
  PC_5,   // D36/A19
  PC_6,   // D37
  PC_7,   // D38
  PC_8,   // D39
  PC_9,   // D40
  PC_10,  // D41
  PC_11,  // D42
  PC_12,  // D43
  PC_13,  // D44
  PC_14,  // D45
  PC_15,  // D46
  PD_2,   // D47
  PF_0,   // D48
  PF_1,   // D49
  PF_4    // D50/A20
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
  27, // A10, PB12
  28, // A11, PB13
  29, // A12, PB14
  30, // A13, PB15
  31, // A14, PC0
  32, // A15, PC1
  33, // A16, PC2
  34, // A17, PC3
  35, // A18, PC4
  36, // A19, PC5
  50  // A20, PF4
};

#endif /* ARDUINO_GENERIC_* */
