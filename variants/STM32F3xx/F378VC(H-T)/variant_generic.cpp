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
#if defined(ARDUINO_GENERIC_F378VCHX) || defined(ARDUINO_GENERIC_F378VCTX)
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
  PB_14,  // D26
  PB_15,  // D27
  PC_0,   // D28/A10
  PC_1,   // D29/A11
  PC_2,   // D30/A12
  PC_3,   // D31/A13
  PC_4,   // D32/A14
  PC_5,   // D33/A15
  PC_6,   // D34
  PC_7,   // D35
  PC_8,   // D36
  PC_9,   // D37
  PC_10,  // D38
  PC_11,  // D39
  PC_12,  // D40
  PC_13,  // D41
  PC_14,  // D42
  PC_15,  // D43
  PD_0,   // D44
  PD_1,   // D45
  PD_2,   // D46
  PD_3,   // D47
  PD_4,   // D48
  PD_5,   // D49
  PD_6,   // D50
  PD_7,   // D51
  PD_8,   // D52
  PD_9,   // D53
  PD_10,  // D54
  PD_11,  // D55
  PD_12,  // D56
  PD_13,  // D57
  PD_14,  // D58
  PD_15,  // D59
  PE_0,   // D60
  PE_1,   // D61
  PE_2,   // D62
  PE_3,   // D63
  PE_4,   // D64
  PE_5,   // D65
  PE_6,   // D66
  PE_7,   // D67
  PE_8,   // D68
  PE_9,   // D69
  PE_10,  // D70
  PE_11,  // D71
  PE_12,  // D72
  PE_13,  // D73
  PE_14,  // D74
  PE_15,  // D75
  PF_0,   // D76
  PF_1,   // D77
  PF_2,   // D78
  PF_4,   // D79
  PF_6,   // D80
  PF_9,   // D81
  PF_10   // D82
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
  28, // A10, PC0
  29, // A11, PC1
  30, // A12, PC2
  31, // A13, PC3
  32, // A14, PC4
  33  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
