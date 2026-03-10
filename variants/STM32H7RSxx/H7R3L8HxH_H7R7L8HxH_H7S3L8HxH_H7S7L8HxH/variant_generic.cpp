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
#if defined(ARDUINO_GENERIC_H7R3L8HXH) || defined(ARDUINO_GENERIC_H7R7L8HXH) ||\
    defined(ARDUINO_GENERIC_H7S3L8HXH) || defined(ARDUINO_GENERIC_H7S7L8HXH)
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
  PF_3,   // D79
  PF_4,   // D80
  PF_5,   // D81
  PF_6,   // D82
  PF_7,   // D83
  PF_8,   // D84
  PF_9,   // D85
  PF_10,  // D86
  PF_11,  // D87/A16
  PF_12,  // D88/A17
  PF_13,  // D89/A18
  PF_14,  // D90/A19
  PF_15,  // D91
  PG_0,   // D92
  PG_1,   // D93
  PG_2,   // D94
  PG_3,   // D95
  PG_11,  // D96
  PG_12,  // D97
  PG_13,  // D98
  PG_14,  // D99
  PG_15,  // D100
  PH_0,   // D101
  PH_1,   // D102
  PM_0,   // D103
  PM_1,   // D104
  PM_2,   // D105
  PM_3,   // D106
  PM_5,   // D107
  PM_6,   // D108
  PM_8,   // D109
  PM_9,   // D110
  PM_11,  // D111
  PM_12,  // D112
  PM_13,  // D113
  PM_14,  // D114
  PN_0,   // D115
  PN_1,   // D116
  PN_2,   // D117
  PN_3,   // D118
  PN_4,   // D119
  PN_5,   // D120
  PN_6,   // D121
  PN_7,   // D122
  PN_8,   // D123
  PN_9,   // D124
  PN_10,  // D125
  PN_11,  // D126
  PN_12,  // D127
  PO_0,   // D128
  PO_1,   // D129
  PO_2,   // D130
  PO_3,   // D131
  PO_4,   // D132
  PO_5,   // D133
  PP_0,   // D134
  PP_1,   // D135
  PP_2,   // D136
  PP_3,   // D137
  PP_4,   // D138
  PP_5,   // D139
  PP_6,   // D140
  PP_7,   // D141
  PP_8,   // D142
  PP_9,   // D143
  PP_10,  // D144
  PP_11,  // D145
  PP_12,  // D146
  PP_13,  // D147
  PP_14,  // D148
  PP_15   // D149
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
  87, // A16, PF11
  88, // A17, PF12
  89, // A18, PF13
  90  // A19, PF14
};

#endif /* ARDUINO_GENERIC_* */
