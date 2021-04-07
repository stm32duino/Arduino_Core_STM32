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
#if defined(ARDUINO_GENERIC_L496WGYXP)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1/A0
  PA_1,   // D2/A1
  PA_2,   // D3/A2
  PA_3,   // D4/A3
  PA_4,   // D5/A4
  PA_5,   // D6/A5
  PA_6,   // D7/A6
  PA_7,   // D8/A7
  PA_8,   // D9
  PA_9,   // D10
  PA_10,  // D11
  PA_11,  // D12
  PA_12,  // D13
  PA_13,  // D14
  PA_14,  // D15
  PA_15,  // D16
  PB_0,   // D17/A8
  PB_1,   // D18/A9
  PB_2,   // D19
  PB_3,   // D20
  PB_4,   // D21
  PB_5,   // D22
  PB_6,   // D23
  PB_7,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_11,  // D27
  PB_12,  // D28
  PB_13,  // D29
  PB_14,  // D30
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
  PD_4,   // D50
  PD_5,   // D51
  PD_6,   // D52
  PD_7,   // D53
  PD_8,   // D54
  PD_9,   // D55
  PD_10,  // D56
  PD_14,  // D57
  PD_15,  // D58
  PE_2,   // D59
  PE_3,   // D60
  PE_4,   // D61
  PE_5,   // D62
  PE_6,   // D63
  PE_7,   // D64
  PE_8,   // D65
  PE_9,   // D66
  PE_10,  // D67
  PE_11,  // D68
  PE_12,  // D69
  PE_13,  // D70
  PE_14,  // D71
  PE_15,  // D72
  PG_0,   // D73
  PG_1,   // D74
  PG_2,   // D75
  PG_3,   // D76
  PG_4,   // D77
  PG_5,   // D78
  PG_6,   // D79
  PG_7,   // D80
  PG_8,   // D81
  PG_9,   // D82
  PG_10,  // D83
  PG_11,  // D84
  PG_12,  // D85
  PG_13,  // D86
  PG_14,  // D87
  PH_0,   // D88
  PH_1,   // D89
  PH_3    // D90
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
