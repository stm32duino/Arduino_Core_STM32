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
#if defined(ARDUINO_GENERIC_H7A3VGTXQ) || defined(ARDUINO_GENERIC_H7A3VITXQ) ||\
    defined(ARDUINO_GENERIC_H7B3VITXQ)
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
  PC_4,   // D35/A12
  PC_5,   // D36/A13
  PC_6,   // D37
  PC_7,   // D38
  PC_8,   // D39
  PC_9,   // D40
  PC_10,  // D41
  PC_11,  // D42
  PC_12,  // D43
  PC_13,  // D44
  PC_14,  // D45
  PC_15,  // D46
  PD_0,   // D47
  PD_1,   // D48
  PD_2,   // D49
  PD_3,   // D50
  PD_4,   // D51
  PD_5,   // D52
  PD_8,   // D53
  PD_9,   // D54
  PD_10,  // D55
  PD_11,  // D56
  PD_12,  // D57
  PD_13,  // D58
  PD_14,  // D59
  PD_15,  // D60
  PE_0,   // D61
  PE_2,   // D62
  PE_4,   // D63
  PE_5,   // D64
  PE_7,   // D65
  PE_8,   // D66
  PH_0,   // D67
  PH_1,   // D68
  PC_2_C, // D69/A14
  PC_3_C  // D70/A15
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
  68, // A14, PC2_C
  69  // A15, PC3_C
};

#endif /* ARDUINO_GENERIC_* */
