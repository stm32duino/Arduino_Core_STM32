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
#if defined(ARDUINO_GENERIC_L496WGYXP)
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
  PB_9,   // D24
  PB_10,  // D25
  PB_11,  // D26
  PB_12,  // D27
  PB_13,  // D28
  PB_14,  // D29
  PC_0,   // D30/A10
  PC_1,   // D31/A11
  PC_2,   // D32/A12
  PC_3,   // D33/A13
  PC_4,   // D34/A14
  PC_5,   // D35/A15
  PC_6,   // D36
  PC_7,   // D37
  PC_8,   // D38
  PC_9,   // D39
  PC_10,  // D40
  PC_11,  // D41
  PC_12,  // D42
  PC_13,  // D43
  PC_14,  // D44
  PC_15,  // D45
  PD_0,   // D46
  PD_1,   // D47
  PD_2,   // D48
  PD_4,   // D49
  PD_5,   // D50
  PD_6,   // D51
  PD_7,   // D52
  PD_8,   // D53
  PD_9,   // D54
  PD_10,  // D55
  PD_14,  // D56
  PD_15,  // D57
  PE_2,   // D58
  PE_3,   // D59
  PE_4,   // D60
  PE_5,   // D61
  PE_6,   // D62
  PE_7,   // D63
  PE_8,   // D64
  PE_9,   // D65
  PE_10,  // D66
  PE_11,  // D67
  PE_12,  // D68
  PE_13,  // D69
  PE_14,  // D70
  PE_15,  // D71
  PG_0,   // D72
  PG_1,   // D73
  PG_2,   // D74
  PG_3,   // D75
  PG_4,   // D76
  PG_5,   // D77
  PG_6,   // D78
  PG_7,   // D79
  PG_8,   // D80
  PG_9,   // D81
  PG_10,  // D82
  PG_11,  // D83
  PG_12,  // D84
  PG_13,  // D85
  PG_14,  // D86
  PH_0,   // D87
  PH_1,   // D88
  PH_3    // D89
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
  30, // A10, PC0
  31, // A11, PC1
  32, // A12, PC2
  33, // A13, PC3
  34, // A14, PC4
  35  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
