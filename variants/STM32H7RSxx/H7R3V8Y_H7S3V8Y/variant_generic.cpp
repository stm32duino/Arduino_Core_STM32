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
#if defined(ARDUINO_GENERIC_H7R3V8YX) || defined(ARDUINO_GENERIC_H7S3V8YX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_4,   // D3/A3
  PA_5,   // D4/A4
  PA_6,   // D5/A5
  PA_7,   // D6/A6
  PA_8,   // D7
  PA_9,   // D8
  PA_10,  // D9
  PA_11,  // D10
  PA_12,  // D11
  PA_13,  // D12
  PA_14,  // D13
  PA_15,  // D14
  PB_0,   // D15/A7
  PB_1,   // D16/A8
  PB_2,   // D17
  PB_3,   // D18
  PB_4,   // D19
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_10,  // D24
  PB_11,  // D25
  PB_12,  // D26
  PB_14,  // D27
  PB_15,  // D28
  PC_0,   // D29/A9
  PC_1,   // D30/A10
  PC_10,  // D31
  PC_11,  // D32
  PC_13,  // D33
  PC_14,  // D34
  PC_15,  // D35
  PD_7,   // D36
  PD_12,  // D37
  PH_0,   // D38
  PH_1,   // D39
  PM_0,   // D40
  PM_1,   // D41
  PM_2,   // D42
  PM_3,   // D43
  PM_5,   // D44
  PM_6,   // D45
  PM_8,   // D46
  PM_9,   // D47
  PM_11,  // D48
  PM_12,  // D49
  PM_13,  // D50
  PM_14,  // D51
  PO_0,   // D52
  PO_1,   // D53
  PO_2,   // D54
  PO_4,   // D55
  PO_5,   // D56
  PP_0,   // D57
  PP_1,   // D58
  PP_2,   // D59
  PP_3,   // D60
  PP_4,   // D61
  PP_5,   // D62
  PP_6,   // D63
  PP_7    // D64
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA4
  4,  // A4,  PA5
  5,  // A5,  PA6
  6,  // A6,  PA7
  15, // A7,  PB0
  16, // A8,  PB1
  29, // A9,  PC0
  30  // A10, PC1
};

#endif /* ARDUINO_GENERIC_* */
