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
#if defined(ARDUINO_GENERIC_U5F9VITXQ) || defined(ARDUINO_GENERIC_U5F9VJTXQ) ||\
    defined(ARDUINO_GENERIC_U5G9VJTXQ)
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
  PB_13,  // D26
  PB_14,  // D27
  PB_15,  // D28
  PC_0,   // D29/A11
  PC_1,   // D30/A12
  PC_2,   // D31/A13
  PC_3,   // D32/A14
  PC_10,  // D33
  PC_11,  // D34
  PC_12,  // D35
  PC_13,  // D36
  PC_14,  // D37
  PC_15,  // D38
  PD_0,   // D39
  PD_1,   // D40
  PD_2,   // D41
  PD_3,   // D42
  PD_4,   // D43
  PD_5,   // D44
  PE_7,   // D45
  PE_8,   // D46
  PE_9,   // D47
  PE_10,  // D48
  PH_0,   // D49
  PH_1,   // D50
  PH_3,   // D51
  PH_9,   // D52
  PH_10,  // D53
  PH_11,  // D54
  PH_12,  // D55
  PH_13,  // D56
  PH_14,  // D57
  PH_15,  // D58
  PI_0,   // D59
  PI_1,   // D60
  PI_2,   // D61
  PI_3    // D62
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
  29, // A11, PC0
  30, // A12, PC1
  31, // A13, PC2
  32  // A14, PC3
};

#endif /* ARDUINO_GENERIC_* */
