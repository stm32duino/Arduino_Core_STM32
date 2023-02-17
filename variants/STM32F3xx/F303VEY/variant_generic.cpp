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
#if defined(ARDUINO_GENERIC_F303VEYX)
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
  PD_7,   // D53
  PD_9,   // D54/A22
  PD_10,  // D55/A23
  PD_11,  // D56/A24
  PD_12,  // D57/A25
  PD_13,  // D58/A26
  PD_14,  // D59/A27
  PD_15,  // D60
  PE_0,   // D61
  PE_1,   // D62
  PE_2,   // D63
  PE_3,   // D64
  PE_4,   // D65
  PE_5,   // D66
  PE_6,   // D67
  PE_7,   // D68/A28
  PE_8,   // D69/A29
  PE_11,  // D70/A30
  PE_12,  // D71/A31
  PF_0,   // D72
  PF_1,   // D73
  PF_2,   // D74/A32
  PF_6,   // D75
  PF_9,   // D76
  PF_10   // D77
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
  54, // A22, PD9
  55, // A23, PD10
  56, // A24, PD11
  57, // A25, PD12
  58, // A26, PD13
  59, // A27, PD14
  68, // A28, PE7
  69, // A29, PE8
  70, // A30, PE11
  71, // A31, PE12
  74  // A32, PF2
};

#endif /* ARDUINO_GENERIC_* */
