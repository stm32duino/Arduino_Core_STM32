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
#if defined(ARDUINO_GENERIC_F303ZDTX) || defined(ARDUINO_GENERIC_F303ZETX)
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
  PB_11,  // D27/A11
  PB_12,  // D28/A12
  PB_13,  // D29/A13
  PB_14,  // D30/A14
  PB_15,  // D31/A15
  PC_0,   // D32/A16
  PC_1,   // D33/A17
  PC_2,   // D34/A18
  PC_3,   // D35/A19
  PC_4,   // D36/A20
  PC_5,   // D37/A21
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
  PD_8,   // D56/A22
  PD_9,   // D57/A23
  PD_10,  // D58/A24
  PD_11,  // D59/A25
  PD_12,  // D60/A26
  PD_13,  // D61/A27
  PD_14,  // D62/A28
  PD_15,  // D63
  PE_0,   // D64
  PE_1,   // D65
  PE_2,   // D66
  PE_3,   // D67
  PE_4,   // D68
  PE_5,   // D69
  PE_6,   // D70
  PE_7,   // D71/A29
  PE_8,   // D72/A30
  PE_9,   // D73/A31
  PE_10,  // D74/A32
  PE_11,  // D75/A33
  PE_12,  // D76/A34
  PE_13,  // D77/A35
  PE_14,  // D78/A36
  PE_15,  // D79/A37
  PF_0,   // D80
  PF_1,   // D81
  PF_2,   // D82/A38
  PF_3,   // D83
  PF_4,   // D84/A39
  PF_5,   // D85
  PF_6,   // D86
  PF_7,   // D87
  PF_8,   // D88
  PF_9,   // D89
  PF_10,  // D90
  PF_11,  // D91
  PF_12,  // D92
  PF_13,  // D93
  PF_14,  // D94
  PF_15,  // D95
  PG_0,   // D96
  PG_1,   // D97
  PG_2,   // D98
  PG_3,   // D99
  PG_4,   // D100
  PG_5,   // D101
  PG_6,   // D102
  PG_7,   // D103
  PG_8,   // D104
  PG_9,   // D105
  PG_10,  // D106
  PG_11,  // D107
  PG_12,  // D108
  PG_13,  // D109
  PG_14,  // D110
  PG_15,  // D111
  PH_0,   // D112
  PH_1,   // D113
  PH_2    // D114
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
  18, // A10, PB2
  27, // A11, PB11
  28, // A12, PB12
  29, // A13, PB13
  30, // A14, PB14
  31, // A15, PB15
  32, // A16, PC0
  33, // A17, PC1
  34, // A18, PC2
  35, // A19, PC3
  36, // A20, PC4
  37, // A21, PC5
  56, // A22, PD8
  57, // A23, PD9
  58, // A24, PD10
  59, // A25, PD11
  60, // A26, PD12
  61, // A27, PD13
  62, // A28, PD14
  71, // A29, PE7
  72, // A30, PE8
  73, // A31, PE9
  74, // A32, PE10
  75, // A33, PE11
  76, // A34, PE12
  77, // A35, PE13
  78, // A36, PE14
  79, // A37, PE15
  82, // A38, PF2
  84  // A39, PF4
};

#endif /* ARDUINO_GENERIC_* */
