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
#if defined(ARDUINO_GENERIC_F205VBTX) || defined(ARDUINO_GENERIC_F205VCTX) ||\
    defined(ARDUINO_GENERIC_F205VETX) || defined(ARDUINO_GENERIC_F205VFTX) ||\
    defined(ARDUINO_GENERIC_F205VGTX) || defined(ARDUINO_GENERIC_F215VETX) ||\
    defined(ARDUINO_GENERIC_F215VGTX)
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
  PB_11,  // D27
  PB_12,  // D28
  PB_13,  // D29
  PB_14,  // D30
  PB_15,  // D31
  PC_0,   // D32/A10
  PC_1,   // D33/A11
  PC_2,   // D34/A12
  PC_3,   // D35/A13
  PC_4,   // D36/A14
  PC_5,   // D37/A15
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
  PD_0,   // D48
  PD_1,   // D49
  PD_2,   // D50
  PD_3,   // D51
  PD_4,   // D52
  PD_5,   // D53
  PD_6,   // D54
  PD_7,   // D55
  PD_8,   // D56
  PD_9,   // D57
  PD_10,  // D58
  PD_11,  // D59
  PD_12,  // D60
  PD_13,  // D61
  PD_14,  // D62
  PD_15,  // D63
  PE_0,   // D64
  PE_1,   // D65
  PE_2,   // D66
  PE_3,   // D67
  PE_4,   // D68
  PE_5,   // D69
  PE_6,   // D70
  PE_7,   // D71
  PE_8,   // D72
  PE_9,   // D73
  PE_10,  // D74
  PE_11,  // D75
  PE_12,  // D76
  PE_13,  // D77
  PE_14,  // D78
  PE_15,  // D79
  PH_0,   // D80
  PH_1    // D81
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
  32, // A10, PC0
  33, // A11, PC1
  34, // A12, PC2
  35, // A13, PC3
  36, // A14, PC4
  37  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
