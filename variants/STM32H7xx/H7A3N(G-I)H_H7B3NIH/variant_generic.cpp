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
#if defined(ARDUINO_GENERIC_H7A3NGHX) || defined(ARDUINO_GENERIC_H7A3NIHX) ||\
    defined(ARDUINO_GENERIC_H7B3NIHX)
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
  PC_4,   // D34/A12
  PC_5,   // D35/A13
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
  PD_3,   // D49
  PD_4,   // D50
  PD_5,   // D51
  PD_6,   // D52
  PD_7,   // D53
  PD_8,   // D54
  PD_9,   // D55
  PD_10,  // D56
  PD_11,  // D57
  PD_12,  // D58
  PD_13,  // D59
  PD_14,  // D60
  PD_15,  // D61
  PE_0,   // D62
  PE_1,   // D63
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
  PF_0,   // D78
  PF_1,   // D79
  PF_2,   // D80
  PF_3,   // D81
  PF_4,   // D82
  PF_5,   // D83
  PF_6,   // D84
  PF_7,   // D85
  PF_8,   // D86
  PF_9,   // D87
  PF_10,  // D88
  PF_11,  // D89/A14
  PF_12,  // D90/A15
  PF_13,  // D91/A16
  PF_14,  // D92/A17
  PF_15,  // D93
  PG_0,   // D94
  PG_1,   // D95
  PG_2,   // D96
  PG_3,   // D97
  PG_4,   // D98
  PG_5,   // D99
  PG_6,   // D100
  PG_7,   // D101
  PG_8,   // D102
  PG_9,   // D103
  PG_10,  // D104
  PG_11,  // D105
  PG_12,  // D106
  PG_13,  // D107
  PG_14,  // D108
  PG_15,  // D109
  PH_0,   // D110
  PH_1,   // D111
  PH_2,   // D112
  PH_3,   // D113
  PH_4,   // D114
  PH_5,   // D115
  PH_6,   // D116
  PH_7,   // D117
  PH_8,   // D118
  PH_9,   // D119
  PH_10,  // D120
  PH_11,  // D121
  PH_12,  // D122
  PH_13,  // D123
  PH_14,  // D124
  PH_15,  // D125
  PI_0,   // D126
  PI_1,   // D127
  PI_2,   // D128
  PI_3,   // D129
  PI_4,   // D130
  PI_5,   // D131
  PI_6,   // D132
  PI_7,   // D133
  PI_8,   // D134
  PI_9,   // D135
  PI_10,  // D136
  PI_11,  // D137
  PI_12,  // D138
  PI_13,  // D139
  PI_14,  // D140
  PI_15,  // D141
  PJ_0,   // D142
  PJ_1,   // D143
  PJ_2,   // D144
  PJ_3,   // D145
  PJ_4,   // D146
  PJ_5,   // D147
  PJ_6,   // D148
  PJ_7,   // D149
  PJ_8,   // D150
  PJ_9,   // D151
  PJ_10,  // D152
  PJ_11,  // D153
  PJ_12,  // D154
  PJ_13,  // D155
  PJ_14,  // D156
  PJ_15,  // D157
  PK_0,   // D158
  PK_1,   // D159
  PK_2,   // D160
  PK_3,   // D161
  PK_4,   // D162
  PK_5,   // D163
  PK_6,   // D164
  PK_7,   // D165
  PC_2_C, // D166/A18
  PC_3_C  // D167/A19
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
  89, // A14, PF11
  90, // A15, PF12
  91, // A16, PF13
  92, // A17, PF14
  166, // A18, PC2_C
  167 // A19, PC3_C
};

#endif /* ARDUINO_GENERIC_* */
