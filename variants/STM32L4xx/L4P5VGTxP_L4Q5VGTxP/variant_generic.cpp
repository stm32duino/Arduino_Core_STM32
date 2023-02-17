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
#if defined(ARDUINO_GENERIC_L4P5VGTXP) || defined(ARDUINO_GENERIC_L4Q5VGTXP)
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
  PB_2,   // D18
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_12,  // D27
  PB_13,  // D28
  PB_14,  // D29
  PB_15,  // D30
  PC_0,   // D31/A10
  PC_1,   // D32/A11
  PC_2,   // D33/A12
  PC_3,   // D34/A13
  PC_4,   // D35/A14
  PC_5,   // D36/A15
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
  PD_0,   // D47
  PD_1,   // D48
  PD_2,   // D49
  PD_3,   // D50
  PD_4,   // D51
  PD_5,   // D52
  PD_6,   // D53
  PD_7,   // D54
  PD_8,   // D55
  PD_9,   // D56
  PD_10,  // D57
  PD_11,  // D58
  PD_12,  // D59
  PD_13,  // D60
  PD_14,  // D61
  PD_15,  // D62
  PE_0,   // D63
  PE_2,   // D64
  PE_3,   // D65
  PE_4,   // D66
  PE_5,   // D67
  PE_6,   // D68
  PE_7,   // D69
  PE_8,   // D70
  PE_9,   // D71
  PE_10,  // D72
  PE_11,  // D73
  PE_12,  // D74
  PE_13,  // D75
  PE_14,  // D76
  PE_15,  // D77
  PH_0,   // D78
  PH_1,   // D79
  PH_3    // D80
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
  31, // A10, PC0
  32, // A11, PC1
  33, // A12, PC2
  34, // A13, PC3
  35, // A14, PC4
  36  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
