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
#if defined(ARDUINO_GENERIC_F469AEHX) || defined(ARDUINO_GENERIC_F469AEYX) ||\
    defined(ARDUINO_GENERIC_F469AGHX) || defined(ARDUINO_GENERIC_F469AGYX) ||\
    defined(ARDUINO_GENERIC_F469AIHX) || defined(ARDUINO_GENERIC_F469AIYX) ||\
    defined(ARDUINO_GENERIC_F479AGHX) || defined(ARDUINO_GENERIC_F479AGYX) ||\
    defined(ARDUINO_GENERIC_F479AIHX) || defined(ARDUINO_GENERIC_F479AIYX)
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
  PC_6,   // D34
  PC_7,   // D35
  PC_8,   // D36
  PC_9,   // D37
  PC_10,  // D38
  PC_11,  // D39
  PC_12,  // D40
  PC_13,  // D41
  PC_14,  // D42
  PC_15,  // D43
  PD_0,   // D44
  PD_1,   // D45
  PD_2,   // D46
  PD_3,   // D47
  PD_4,   // D48
  PD_5,   // D49
  PD_6,   // D50
  PD_7,   // D51
  PD_8,   // D52
  PD_9,   // D53
  PD_10,  // D54
  PD_11,  // D55
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
  PF_3,   // D79/A12
  PF_4,   // D80/A13
  PF_5,   // D81/A14
  PF_10,  // D82/A15
  PF_11,  // D83
  PF_12,  // D84
  PF_13,  // D85
  PF_14,  // D86
  PF_15,  // D87
  PG_0,   // D88
  PG_1,   // D89
  PG_2,   // D90
  PG_3,   // D91
  PG_4,   // D92
  PG_5,   // D93
  PG_6,   // D94
  PG_7,   // D95
  PG_8,   // D96
  PG_9,   // D97
  PG_10,  // D98
  PG_11,  // D99
  PG_12,  // D100
  PG_13,  // D101
  PG_15,  // D102
  PH_0,   // D103
  PH_1,   // D104
  PH_2,   // D105
  PH_3,   // D106
  PH_4,   // D107
  PH_5,   // D108
  PH_8,   // D109
  PH_9,   // D110
  PH_10,  // D111
  PH_11,  // D112
  PH_12,  // D113
  PH_13,  // D114
  PH_14,  // D115
  PH_15,  // D116
  PI_0,   // D117
  PI_1,   // D118
  PI_2,   // D119
  PI_3,   // D120
  PI_4,   // D121
  PI_5,   // D122
  PI_6,   // D123
  PI_7,   // D124
  PI_9,   // D125
  PI_10,  // D126
  PI_11   // D127
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
  79, // A12, PF3
  80, // A13, PF4
  81, // A14, PF5
  82  // A15, PF10
};

#endif /* ARDUINO_GENERIC_* */
