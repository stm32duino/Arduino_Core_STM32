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
#if defined(ARDUINO_GENERIC_H7R7Z8JX) || defined(ARDUINO_GENERIC_H7S7Z8JX)
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
  PC_13,  // D44
  PC_14,  // D45
  PC_15,  // D46
  PD_0,   // D47
  PD_2,   // D48
  PD_3,   // D49
  PD_4,   // D50
  PD_5,   // D51
  PD_6,   // D52
  PD_7,   // D53
  PE_1,   // D54
  PE_2,   // D55
  PE_3,   // D56
  PE_4,   // D57
  PE_5,   // D58
  PE_6,   // D59
  PG_0,   // D60
  PG_1,   // D61
  PH_0,   // D62
  PH_1,   // D63
  PM_11,  // D64
  PM_12,  // D65
  PM_13,  // D66
  PM_14,  // D67
  PN_0,   // D68
  PN_1,   // D69
  PN_2,   // D70
  PN_3,   // D71
  PN_4,   // D72
  PN_5,   // D73
  PN_6,   // D74
  PN_7,   // D75
  PN_8,   // D76
  PN_9,   // D77
  PN_10,  // D78
  PN_11,  // D79
  PO_0,   // D80
  PO_1,   // D81
  PO_2,   // D82
  PO_4,   // D83
  PO_5,   // D84
  PP_0,   // D85
  PP_1,   // D86
  PP_2,   // D87
  PP_3,   // D88
  PP_4,   // D89
  PP_5,   // D90
  PP_6,   // D91
  PP_7    // D92
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
