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
#if defined(ARDUINO_GENERIC_H7R7I8KX) || defined(ARDUINO_GENERIC_H7S7I8KX)
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
  PD_8,   // D56
  PE_0,   // D57
  PE_1,   // D58
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
  PF_0,   // D73
  PF_1,   // D74
  PF_2,   // D75
  PF_3,   // D76
  PF_4,   // D77
  PF_5,   // D78
  PF_6,   // D79
  PF_7,   // D80
  PF_8,   // D81
  PF_9,   // D82
  PF_10,  // D83
  PF_11,  // D84/A16
  PF_12,  // D85/A17
  PF_13,  // D86/A18
  PG_0,   // D87
  PG_1,   // D88
  PG_2,   // D89
  PG_3,   // D90
  PH_0,   // D91
  PH_1,   // D92
  PM_11,  // D93
  PM_12,  // D94
  PM_13,  // D95
  PM_14,  // D96
  PN_0,   // D97
  PN_1,   // D98
  PN_2,   // D99
  PN_3,   // D100
  PN_4,   // D101
  PN_5,   // D102
  PN_6,   // D103
  PN_7,   // D104
  PN_8,   // D105
  PN_9,   // D106
  PN_10,  // D107
  PN_11,  // D108
  PO_0,   // D109
  PO_1,   // D110
  PO_2,   // D111
  PO_4,   // D112
  PO_5,   // D113
  PP_0,   // D114
  PP_1,   // D115
  PP_2,   // D116
  PP_3,   // D117
  PP_4,   // D118
  PP_5,   // D119
  PP_6,   // D120
  PP_7    // D121
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
  84, // A16, PF11
  85, // A17, PF12
  86  // A18, PF13
};

#endif /* ARDUINO_GENERIC_* */
