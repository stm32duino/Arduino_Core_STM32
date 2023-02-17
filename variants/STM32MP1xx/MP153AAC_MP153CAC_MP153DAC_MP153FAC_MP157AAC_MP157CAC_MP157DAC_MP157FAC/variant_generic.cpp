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
#if defined(ARDUINO_GENERIC_MP153AACX) || defined(ARDUINO_GENERIC_MP153CACX) ||\
    defined(ARDUINO_GENERIC_MP153DACX) || defined(ARDUINO_GENERIC_MP153FACX) ||\
    defined(ARDUINO_GENERIC_MP157AACX) || defined(ARDUINO_GENERIC_MP157CACX) ||\
    defined(ARDUINO_GENERIC_MP157DACX) || defined(ARDUINO_GENERIC_MP157FACX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  ANA_0,  // D0/A0
  ANA_1,  // D1/A1
  PA_0,   // D2/A2
  PA_1,   // D3/A3
  PA_2,   // D4/A4
  PA_3,   // D5/A5
  PA_4,   // D6/A6
  PA_5,   // D7/A7
  PA_6,   // D8/A8
  PA_7,   // D9/A9
  PA_8,   // D10
  PA_9,   // D11
  PA_10,  // D12
  PA_11,  // D13
  PA_12,  // D14
  PA_13,  // D15
  PA_14,  // D16
  PA_15,  // D17
  PB_0,   // D18/A10
  PB_1,   // D19/A11
  PB_2,   // D20
  PB_3,   // D21
  PB_4,   // D22
  PB_5,   // D23
  PB_6,   // D24
  PB_7,   // D25
  PB_8,   // D26
  PB_9,   // D27
  PB_10,  // D28
  PB_11,  // D29
  PB_12,  // D30
  PB_13,  // D31
  PB_14,  // D32
  PB_15,  // D33
  PC_0,   // D34/A12
  PC_1,   // D35/A13
  PC_2,   // D36/A14
  PC_3,   // D37/A15
  PC_4,   // D38/A16
  PC_5,   // D39/A17
  PC_6,   // D40
  PC_7,   // D41
  PC_8,   // D42
  PC_9,   // D43
  PC_10,  // D44
  PC_11,  // D45
  PC_12,  // D46
  PC_13,  // D47
  PC_14,  // D48
  PC_15,  // D49
  PD_0,   // D50
  PD_1,   // D51
  PD_2,   // D52
  PD_3,   // D53
  PD_4,   // D54
  PD_5,   // D55
  PD_6,   // D56
  PD_7,   // D57
  PD_8,   // D58
  PD_9,   // D59
  PD_10,  // D60
  PD_11,  // D61
  PD_12,  // D62
  PD_13,  // D63
  PD_14,  // D64
  PD_15,  // D65
  PE_0,   // D66
  PE_1,   // D67
  PE_2,   // D68
  PE_3,   // D69
  PE_4,   // D70
  PE_5,   // D71
  PE_6,   // D72
  PE_7,   // D73
  PE_8,   // D74
  PE_9,   // D75
  PE_10,  // D76
  PE_11,  // D77
  PE_12,  // D78
  PE_13,  // D79
  PE_14,  // D80
  PE_15,  // D81
  PF_0,   // D82
  PF_1,   // D83
  PF_2,   // D84
  PF_3,   // D85
  PF_4,   // D86
  PF_5,   // D87
  PF_6,   // D88
  PF_7,   // D89
  PF_8,   // D90
  PF_9,   // D91
  PF_10,  // D92
  PF_11,  // D93/A18
  PF_12,  // D94/A19
  PF_13,  // D95/A20
  PF_14,  // D96/A21
  PF_15,  // D97
  PG_0,   // D98
  PG_1,   // D99
  PG_2,   // D100
  PG_3,   // D101
  PG_4,   // D102
  PG_5,   // D103
  PG_6,   // D104
  PG_7,   // D105
  PG_8,   // D106
  PG_9,   // D107
  PG_10,  // D108
  PG_11,  // D109
  PG_12,  // D110
  PG_13,  // D111
  PG_14,  // D112
  PG_15,  // D113
  PH_0,   // D114
  PH_1,   // D115
  PH_2,   // D116
  PH_3,   // D117
  PH_4,   // D118
  PH_5,   // D119
  PH_6,   // D120
  PH_7,   // D121
  PH_8,   // D122
  PH_9,   // D123
  PH_10,  // D124
  PH_11,  // D125
  PH_12,  // D126
  PH_13,  // D127
  PH_14,  // D128
  PH_15,  // D129
  PI_0,   // D130
  PI_1,   // D131
  PI_2,   // D132
  PI_3,   // D133
  PI_4,   // D134
  PI_5,   // D135
  PI_6,   // D136
  PI_7,   // D137
  PI_8,   // D138
  PI_9,   // D139
  PI_10,  // D140
  PI_11,  // D141
  PZ_0,   // D142
  PZ_1,   // D143
  PZ_2,   // D144
  PZ_3,   // D145
  PZ_4,   // D146
  PZ_5,   // D147
  PZ_6,   // D148
  PZ_7    // D149
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  ANA0
  1,  // A1,  ANA1
  2,  // A2,  PA0
  3,  // A3,  PA1
  4,  // A4,  PA2
  5,  // A5,  PA3
  6,  // A6,  PA4
  7,  // A7,  PA5
  8,  // A8,  PA6
  9,  // A9,  PA7
  18, // A10, PB0
  19, // A11, PB1
  34, // A12, PC0
  35, // A13, PC1
  36, // A14, PC2
  37, // A15, PC3
  38, // A16, PC4
  39, // A17, PC5
  93, // A18, PF11
  94, // A19, PF12
  95, // A20, PF13
  96  // A21, PF14
};

#endif /* ARDUINO_GENERIC_* */
