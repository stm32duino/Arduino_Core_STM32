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
#if defined(ARDUINO_GENERIC_H7R3V8TX) || defined(ARDUINO_GENERIC_H7S3V8TX)
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
  PC_10,  // D34
  PC_11,  // D35
  PC_12,  // D36
  PC_13,  // D37
  PC_14,  // D38
  PC_15,  // D39
  PH_0,   // D40
  PH_1,   // D41
  PM_0,   // D42
  PM_1,   // D43
  PM_2,   // D44
  PM_3,   // D45
  PM_5,   // D46
  PM_6,   // D47
  PM_8,   // D48
  PM_9,   // D49
  PM_11,  // D50
  PM_12,  // D51
  PM_13,  // D52
  PM_14,  // D53
  PO_0,   // D54
  PO_1,   // D55
  PO_2,   // D56
  PO_4,   // D57
  PO_5,   // D58
  PP_0,   // D59
  PP_1,   // D60
  PP_2,   // D61
  PP_3,   // D62
  PP_4,   // D63
  PP_5,   // D64
  PP_6,   // D65
  PP_7    // D66
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
  33  // A11, PC1
};

#endif /* ARDUINO_GENERIC_* */
