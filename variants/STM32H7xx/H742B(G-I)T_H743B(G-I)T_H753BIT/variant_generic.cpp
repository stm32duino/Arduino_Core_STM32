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
#if defined(ARDUINO_GENERIC_H742BGTX) || defined(ARDUINO_GENERIC_H742BITX) ||\
    defined(ARDUINO_GENERIC_H743BGTX) || defined(ARDUINO_GENERIC_H743BITX) ||\
    defined(ARDUINO_GENERIC_H753BITX)
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
  PB_8,   // D25
  PB_9,   // D26
  PB_10,  // D27
  PB_11,  // D28
  PB_12,  // D29
  PB_13,  // D30
  PB_14,  // D31
  PB_15,  // D32
  PC_0,   // D33/A10
  PC_1,   // D34/A11
  PC_4,   // D35/A12
  PC_5,   // D36/A13
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
  PE_1,   // D64
  PE_2,   // D65
  PE_3,   // D66
  PE_4,   // D67
  PE_5,   // D68
  PE_6,   // D69
  PE_7,   // D70
  PE_8,   // D71
  PE_9,   // D72
  PE_10,  // D73
  PE_11,  // D74
  PE_12,  // D75
  PE_13,  // D76
  PE_14,  // D77
  PE_15,  // D78
  PF_0,   // D79
  PF_1,   // D80
  PF_2,   // D81
  PF_3,   // D82/A14
  PF_4,   // D83/A15
  PF_5,   // D84/A16
  PF_6,   // D85/A17
  PF_7,   // D86/A18
  PF_8,   // D87/A19
  PF_9,   // D88/A20
  PF_10,  // D89/A21
  PF_11,  // D90/A22
  PF_12,  // D91/A23
  PF_13,  // D92/A24
  PF_14,  // D93/A25
  PF_15,  // D94
  PG_0,   // D95
  PG_1,   // D96
  PG_2,   // D97
  PG_3,   // D98
  PG_4,   // D99
  PG_5,   // D100
  PG_6,   // D101
  PG_7,   // D102
  PG_8,   // D103
  PG_9,   // D104
  PG_10,  // D105
  PG_11,  // D106
  PG_12,  // D107
  PG_13,  // D108
  PG_14,  // D109
  PG_15,  // D110
  PH_0,   // D111
  PH_1,   // D112
  PH_2,   // D113/A26
  PH_3,   // D114/A27
  PH_4,   // D115/A28
  PH_5,   // D116/A29
  PH_6,   // D117
  PH_7,   // D118
  PH_8,   // D119
  PH_9,   // D120
  PH_10,  // D121
  PH_11,  // D122
  PH_12,  // D123
  PH_13,  // D124
  PH_14,  // D125
  PH_15,  // D126
  PI_0,   // D127
  PI_1,   // D128
  PI_2,   // D129
  PI_3,   // D130
  PI_4,   // D131
  PI_5,   // D132
  PI_6,   // D133
  PI_7,   // D134
  PI_8,   // D135
  PI_9,   // D136
  PI_10,  // D137
  PI_11,  // D138
  PI_12,  // D139
  PI_13,  // D140
  PI_14,  // D141
  PI_15,  // D142
  PJ_0,   // D143
  PJ_1,   // D144
  PJ_2,   // D145
  PJ_3,   // D146
  PJ_4,   // D147
  PJ_5,   // D148
  PJ_6,   // D149
  PJ_7,   // D150
  PJ_8,   // D151
  PJ_9,   // D152
  PJ_10,  // D153
  PJ_11,  // D154
  PJ_12,  // D155
  PJ_13,  // D156
  PJ_14,  // D157
  PJ_15,  // D158
  PK_0,   // D159
  PK_1,   // D160
  PK_2,   // D161
  PK_3,   // D162
  PK_4,   // D163
  PK_5,   // D164
  PK_6,   // D165
  PK_7,   // D166
  PC_2_C, // D167/A30
  PC_3_C  // D168/A31
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
  34, // A12, PC4
  35, // A13, PC5
  81, // A14, PF3
  82, // A15, PF4
  83, // A16, PF5
  84, // A17, PF6
  85, // A18, PF7
  86, // A19, PF8
  87, // A20, PF9
  88, // A21, PF10
  89, // A22, PF11
  90, // A23, PF12
  91, // A24, PF13
  92, // A25, PF14
  112, // A26, PH2
  113, // A27, PH3
  114, // A28, PH4
  115, // A29, PH5
  166, // A30, PC2_C
  167 // A31, PC3_C
};

#endif /* ARDUINO_GENERIC_* */
