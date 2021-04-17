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
#if defined(ARDUINO_GENERIC_MP153AACX) || defined(ARDUINO_GENERIC_MP153CACX) ||\
    defined(ARDUINO_GENERIC_MP153DACX) || defined(ARDUINO_GENERIC_MP153FACX) ||\
    defined(ARDUINO_GENERIC_MP157AACX) || defined(ARDUINO_GENERIC_MP157CACX) ||\
    defined(ARDUINO_GENERIC_MP157DACX) || defined(ARDUINO_GENERIC_MP157FACX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  ANA_0,  // D1/A0
  ANA_1,  // D2/A1
  PA_0,   // D3/A2
  PA_1,   // D4/A3
  PA_2,   // D5/A4
  PA_3,   // D6/A5
  PA_4,   // D7/A6
  PA_5,   // D8/A7
  PA_6,   // D9/A8
  PA_7,   // D10/A9
  PA_8,   // D11
  PA_9,   // D12
  PA_10,  // D13
  PA_11,  // D14
  PA_12,  // D15
  PA_13,  // D16
  PA_14,  // D17
  PA_15,  // D18
  PB_0,   // D19/A10
  PB_1,   // D20/A11
  PB_2,   // D21
  PB_3,   // D22
  PB_4,   // D23
  PB_5,   // D24
  PB_6,   // D25
  PB_7,   // D26
  PB_8,   // D27
  PB_9,   // D28
  PB_10,  // D29
  PB_11,  // D30
  PB_12,  // D31
  PB_13,  // D32
  PB_14,  // D33
  PB_15,  // D34
  PC_0,   // D35/A12
  PC_1,   // D36/A13
  PC_2,   // D37/A14
  PC_3,   // D38/A15
  PC_4,   // D39/A16
  PC_5,   // D40/A17
  PC_6,   // D41
  PC_7,   // D42
  PC_8,   // D43
  PC_9,   // D44
  PC_10,  // D45
  PC_11,  // D46
  PC_12,  // D47
  PC_13,  // D48
  PC_14,  // D49
  PC_15,  // D50
  PD_0,   // D51
  PD_1,   // D52
  PD_2,   // D53
  PD_3,   // D54
  PD_4,   // D55
  PD_5,   // D56
  PD_6,   // D57
  PD_7,   // D58
  PD_8,   // D59
  PD_9,   // D60
  PD_10,  // D61
  PD_11,  // D62
  PD_12,  // D63
  PD_13,  // D64
  PD_14,  // D65
  PD_15,  // D66
  PE_0,   // D67
  PE_1,   // D68
  PE_2,   // D69
  PE_3,   // D70
  PE_4,   // D71
  PE_5,   // D72
  PE_6,   // D73
  PE_7,   // D74
  PE_8,   // D75
  PE_9,   // D76
  PE_10,  // D77
  PE_11,  // D78
  PE_12,  // D79
  PE_13,  // D80
  PE_14,  // D81
  PE_15,  // D82
  PF_0,   // D83
  PF_1,   // D84
  PF_2,   // D85
  PF_3,   // D86
  PF_4,   // D87
  PF_5,   // D88
  PF_6,   // D89
  PF_7,   // D90
  PF_8,   // D91
  PF_9,   // D92
  PF_10,  // D93
  PF_11,  // D94/A18
  PF_12,  // D95/A19
  PF_13,  // D96/A20
  PF_14,  // D97/A21
  PF_15,  // D98
  PG_0,   // D99
  PG_1,   // D100
  PG_2,   // D101
  PG_3,   // D102
  PG_4,   // D103
  PG_5,   // D104
  PG_6,   // D105
  PG_7,   // D106
  PG_8,   // D107
  PG_9,   // D108
  PG_10,  // D109
  PG_11,  // D110
  PG_12,  // D111
  PG_13,  // D112
  PG_14,  // D113
  PG_15,  // D114
  PH_0,   // D115
  PH_1,   // D116
  PH_2,   // D117
  PH_3,   // D118
  PH_4,   // D119
  PH_5,   // D120
  PH_6,   // D121
  PH_7,   // D122
  PH_8,   // D123
  PH_9,   // D124
  PH_10,  // D125
  PH_11,  // D126
  PH_12,  // D127
  PH_13,  // D128
  PH_14,  // D129
  PH_15,  // D130
  PI_0,   // D131
  PI_1,   // D132
  PI_2,   // D133
  PI_3,   // D134
  PI_4,   // D135
  PI_5,   // D136
  PI_6,   // D137
  PI_7,   // D138
  PI_8,   // D139
  PI_9,   // D140
  PI_10,  // D141
  PI_11,  // D142
  PZ_0,   // D143
  PZ_1,   // D144
  PZ_2,   // D145
  PZ_3,   // D146
  PZ_4,   // D147
  PZ_5,   // D148
  PZ_6,   // D149
  PZ_7    // D150
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
