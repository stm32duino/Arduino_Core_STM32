/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_GENERIC_H5E5ZJTX) || defined(ARDUINO_GENERIC_H5E5ZKTX) ||\
    defined(ARDUINO_GENERIC_H5F5ZJTX)
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
  PB_2,   // D18/A10
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_12,  // D27
  PB_13,  // D28
  PB_14,  // D29
  PB_15,  // D30
  PC_0,   // D31/A11
  PC_1,   // D32/A12
  PC_2,   // D33/A13
  PC_3,   // D34/A14
  PC_4,   // D35/A15
  PC_5,   // D36/A16
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
  PE_2,   // D61
  PE_3,   // D62
  PE_4,   // D63
  PE_5,   // D64
  PE_6,   // D65
  PE_7,   // D66/A17
  PE_8,   // D67/A18
  PE_9,   // D68/A19
  PE_10,  // D69/A20
  PE_11,  // D70/A21
  PE_12,  // D71/A22
  PE_13,  // D72/A23
  PE_14,  // D73/A24
  PE_15,  // D74/A25
  PF_0,   // D75
  PF_1,   // D76
  PF_2,   // D77
  PF_3,   // D78
  PF_4,   // D79
  PF_5,   // D80
  PF_6,   // D81
  PF_7,   // D82
  PF_8,   // D83
  PF_9,   // D84
  PF_10,  // D85
  PF_11,  // D86/A26
  PF_12,  // D87/A27
  PF_13,  // D88/A28
  PF_14,  // D89/A29
  PF_15,  // D90
  PG_0,   // D91
  PG_1,   // D92
  PG_2,   // D93
  PG_3,   // D94
  PG_4,   // D95
  PG_5,   // D96
  PG_6,   // D97
  PG_7,   // D98
  PG_9,   // D99
  PG_10,  // D100
  PG_11,  // D101
  PG_12,  // D102
  PG_13,  // D103
  PG_14,  // D104
  PG_15,  // D105
  PH_0,   // D106
  PH_1    // D107
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
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
  18, // A10, PB2
  31, // A11, PC0
  32, // A12, PC1
  33, // A13, PC2
  34, // A14, PC3
  35, // A15, PC4
  36, // A16, PC5
  66, // A17, PE7
  67, // A18, PE8
  68, // A19, PE9
  69, // A20, PE10
  70, // A21, PE11
  71, // A22, PE12
  72, // A23, PE13
  73, // A24, PE14
  74, // A25, PE15
  86, // A26, PF11
  87, // A27, PF12
  88, // A28, PF13
  89  // A29, PF14
};

#endif /* ARDUINO_GENERIC_* */
