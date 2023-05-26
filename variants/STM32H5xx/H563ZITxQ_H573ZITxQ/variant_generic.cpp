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
#if defined(ARDUINO_GENERIC_H563ZITXQ) || defined(ARDUINO_GENERIC_H573ZITXQ)
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
  PB_13,  // D28
  PB_14,  // D29
  PB_15,  // D30
  PC_0,   // D31/A10
  PC_1,   // D32/A11
  PC_2,   // D33/A12
  PC_3,   // D34/A13
  PC_6,   // D35
  PC_7,   // D36
  PC_8,   // D37
  PC_9,   // D38
  PC_10,  // D39
  PC_11,  // D40
  PC_12,  // D41
  PC_13,  // D42
  PC_14,  // D43
  PC_15,  // D44
  PD_0,   // D45
  PD_1,   // D46
  PD_2,   // D47
  PD_3,   // D48
  PD_4,   // D49
  PD_5,   // D50
  PD_6,   // D51
  PD_7,   // D52
  PD_8,   // D53
  PD_9,   // D54
  PD_10,  // D55
  PD_11,  // D56
  PD_12,  // D57
  PD_13,  // D58
  PD_14,  // D59
  PD_15,  // D60
  PE_0,   // D61
  PE_1,   // D62
  PE_2,   // D63
  PE_3,   // D64
  PE_4,   // D65
  PE_5,   // D66
  PE_6,   // D67
  PE_7,   // D68
  PE_8,   // D69
  PE_9,   // D70
  PE_10,  // D71
  PE_11,  // D72
  PE_12,  // D73
  PE_13,  // D74
  PE_14,  // D75
  PE_15,  // D76
  PF_0,   // D77
  PF_1,   // D78
  PF_2,   // D79
  PF_3,   // D80
  PF_4,   // D81
  PF_5,   // D82
  PF_6,   // D83
  PF_7,   // D84
  PF_8,   // D85
  PF_9,   // D86
  PF_10,  // D87
  PF_11,  // D88/A14
  PF_12,  // D89/A15
  PF_13,  // D90/A16
  PF_14,  // D91/A17
  PF_15,  // D92
  PG_0,   // D93
  PG_1,   // D94
  PG_2,   // D95
  PG_3,   // D96
  PG_4,   // D97
  PG_5,   // D98
  PG_6,   // D99
  PG_7,   // D100
  PG_8,   // D101
  PG_9,   // D102
  PG_10,  // D103
  PG_12,  // D104
  PG_13,  // D105
  PG_14,  // D106
  PG_15,  // D107
  PH_0,   // D108
  PH_1    // D109
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
  88, // A14, PF11
  89, // A15, PF12
  90, // A16, PF13
  91  // A17, PF14
};

#endif /* ARDUINO_GENERIC_* */
