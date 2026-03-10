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
#if defined(ARDUINO_GENERIC_H7R7A8IX) || defined(ARDUINO_GENERIC_H7S7A8IX)
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
  PD_9,   // D57
  PD_10,  // D58
  PE_0,   // D59
  PE_1,   // D60
  PE_2,   // D61
  PE_3,   // D62
  PE_4,   // D63
  PE_5,   // D64
  PE_6,   // D65
  PE_7,   // D66
  PE_8,   // D67
  PE_9,   // D68
  PE_10,  // D69
  PE_11,  // D70
  PE_12,  // D71
  PE_13,  // D72
  PE_14,  // D73
  PF_0,   // D74
  PF_1,   // D75
  PF_2,   // D76
  PF_6,   // D77
  PF_7,   // D78
  PF_8,   // D79
  PF_9,   // D80
  PF_11,  // D81/A16
  PG_0,   // D82
  PG_1,   // D83
  PG_2,   // D84
  PH_0,   // D85
  PH_1,   // D86
  PM_11,  // D87
  PM_12,  // D88
  PM_13,  // D89
  PM_14,  // D90
  PN_0,   // D91
  PN_1,   // D92
  PN_2,   // D93
  PN_3,   // D94
  PN_4,   // D95
  PN_5,   // D96
  PN_6,   // D97
  PN_7,   // D98
  PN_8,   // D99
  PN_9,   // D100
  PN_10,  // D101
  PN_11,  // D102
  PN_12,  // D103
  PO_0,   // D104
  PO_1,   // D105
  PO_2,   // D106
  PO_4,   // D107
  PO_5,   // D108
  PP_0,   // D109
  PP_1,   // D110
  PP_2,   // D111
  PP_3,   // D112
  PP_4,   // D113
  PP_5,   // D114
  PP_6,   // D115
  PP_7    // D116
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
  81  // A16, PF11
};

#endif /* ARDUINO_GENERIC_* */
