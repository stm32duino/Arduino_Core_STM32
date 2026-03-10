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
#if defined(ARDUINO_GENERIC_H7R7I8TX) || defined(ARDUINO_GENERIC_H7S7I8TX)
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
  PE_0,   // D56
  PE_1,   // D57
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
  PF_0,   // D72
  PF_1,   // D73
  PF_2,   // D74
  PF_3,   // D75
  PF_4,   // D76
  PF_5,   // D77
  PF_6,   // D78
  PF_7,   // D79
  PF_8,   // D80
  PF_9,   // D81
  PF_10,  // D82
  PF_11,  // D83/A16
  PG_0,   // D84
  PG_1,   // D85
  PG_2,   // D86
  PH_0,   // D87
  PH_1,   // D88
  PM_11,  // D89
  PM_12,  // D90
  PM_13,  // D91
  PM_14,  // D92
  PN_0,   // D93
  PN_1,   // D94
  PN_2,   // D95
  PN_3,   // D96
  PN_4,   // D97
  PN_5,   // D98
  PN_6,   // D99
  PN_7,   // D100
  PN_8,   // D101
  PN_9,   // D102
  PN_10,  // D103
  PN_11,  // D104
  PO_0,   // D105
  PO_1,   // D106
  PO_2,   // D107
  PO_4,   // D108
  PO_5,   // D109
  PP_0,   // D110
  PP_1,   // D111
  PP_2,   // D112
  PP_3,   // D113
  PP_4,   // D114
  PP_5,   // D115
  PP_6,   // D116
  PP_7    // D117
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
  37, // A15, PC5
  83  // A16, PF11
};

#endif /* ARDUINO_GENERIC_* */
