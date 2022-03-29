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
#if defined(ARDUINO_GENERIC_H745ZGTX) || defined(ARDUINO_GENERIC_H745ZITX) ||\
    defined(ARDUINO_GENERIC_H755ZITX)
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
  PF_6,   // D78/A14
  PF_7,   // D79/A15
  PF_8,   // D80/A16
  PF_9,   // D81/A17
  PF_10,  // D82/A18
  PF_11,  // D83/A19
  PF_14,  // D84/A20
  PF_15,  // D85
  PG_6,   // D86
  PG_7,   // D87
  PG_8,   // D88
  PG_9,   // D89
  PG_10,  // D90
  PG_11,  // D91
  PG_12,  // D92
  PG_13,  // D93
  PG_14,  // D94
  PH_0,   // D95
  PH_1,   // D96
  PC_2_C, // D97/A21
  PC_3_C  // D98/A22
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
  78, // A14, PF6
  79, // A15, PF7
  80, // A16, PF8
  81, // A17, PF9
  82, // A18, PF10
  83, // A19, PF11
  84, // A20, PF14
  97, // A21, PC2_C
  98  // A22, PC3_C
};

#endif /* ARDUINO_GENERIC_* */
