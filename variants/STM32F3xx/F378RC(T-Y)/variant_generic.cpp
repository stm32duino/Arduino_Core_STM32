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
#if defined(ARDUINO_GENERIC_F378RCTX) || defined(ARDUINO_GENERIC_F378RCYX)
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
  PB_14,  // D25
  PB_15,  // D26
  PC_0,   // D27/A10
  PC_1,   // D28/A11
  PC_2,   // D29/A12
  PC_3,   // D30/A13
  PC_4,   // D31/A14
  PC_5,   // D32/A15
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
  PD_8,   // D44
  PE_8,   // D45
  PE_9,   // D46
  PF_0,   // D47
  PF_1,   // D48
  PF_6,   // D49
  PF_7    // D50
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
  27, // A10, PC0
  28, // A11, PC1
  29, // A12, PC2
  30, // A13, PC3
  31, // A14, PC4
  32  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
