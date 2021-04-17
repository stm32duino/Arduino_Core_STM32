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
#if defined(ARDUINO_GENERIC_L4P5AGIXP) || defined(ARDUINO_GENERIC_L4Q5AGIXP)
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
  PC_2,   // D35/A12
  PC_3,   // D36/A13
  PC_4,   // D37/A14
  PC_5,   // D38/A15
  PC_6,   // D39
  PC_7,   // D40
  PC_8,   // D41
  PC_9,   // D42
  PC_10,  // D43
  PC_11,  // D44
  PC_12,  // D45
  PC_13,  // D46
  PC_14,  // D47
  PC_15,  // D48
  PD_0,   // D49
  PD_1,   // D50
  PD_2,   // D51
  PD_3,   // D52
  PD_4,   // D53
  PD_5,   // D54
  PD_6,   // D55
  PD_7,   // D56
  PD_8,   // D57
  PD_9,   // D58
  PD_10,  // D59
  PD_11,  // D60
  PD_12,  // D61
  PD_13,  // D62
  PD_14,  // D63
  PD_15,  // D64
  PE_0,   // D65
  PE_1,   // D66
  PE_2,   // D67
  PE_3,   // D68
  PE_4,   // D69
  PE_5,   // D70
  PE_6,   // D71
  PE_7,   // D72
  PE_8,   // D73
  PE_9,   // D74
  PE_10,  // D75
  PE_11,  // D76
  PE_12,  // D77
  PE_13,  // D78
  PE_14,  // D79
  PE_15,  // D80
  PF_0,   // D81
  PF_1,   // D82
  PF_2,   // D83
  PF_3,   // D84
  PF_4,   // D85
  PF_5,   // D86
  PF_10,  // D87
  PF_11,  // D88
  PF_12,  // D89
  PF_13,  // D90
  PF_14,  // D91
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
  PG_11,  // D104
  PG_12,  // D105
  PG_13,  // D106
  PG_14,  // D107
  PH_0,   // D108
  PH_1,   // D109
  PH_2,   // D110
  PH_3,   // D111
  PH_4,   // D112
  PH_5,   // D113
  PH_6,   // D114
  PH_7,   // D115
  PH_8,   // D116
  PH_9,   // D117
  PH_10,  // D118
  PH_12,  // D119
  PH_13,  // D120
  PH_14,  // D121
  PH_15,  // D122
  PI_0,   // D123
  PI_1,   // D124
  PI_2,   // D125
  PI_3,   // D126
  PI_4,   // D127
  PI_5,   // D128
  PI_6,   // D129
  PI_7,   // D130
  PI_8,   // D131
  PI_9,   // D132
  PI_10,  // D133
  PI_11   // D134
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
  37  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
