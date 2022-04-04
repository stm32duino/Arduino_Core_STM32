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
#if defined(ARDUINO_GENERIC_WB5MMGHX)
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
  PA_8,   // D8/A8
  PA_9,   // D9/A9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_2,   // D16
  PB_3,   // D17
  PB_4,   // D18
  PB_5,   // D19
  PB_6,   // D20
  PB_7,   // D21
  PB_8,   // D22
  PB_9,   // D23
  PB_10,  // D24
  PB_11,  // D25
  PB_12,  // D26
  PB_13,  // D27
  PB_14,  // D28
  PB_15,  // D29
  PC_0,   // D30/A10
  PC_1,   // D31/A11
  PC_2,   // D32/A12
  PC_3,   // D33/A13
  PC_4,   // D34/A14
  PC_5,   // D35/A15
  PC_6,   // D36
  PC_7,   // D37
  PC_8,   // D38
  PC_9,   // D39
  PC_10,  // D40
  PC_11,  // D41
  PC_12,  // D42
  PC_13,  // D43
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
  PE_1,   // D61
  PE_2,   // D62
  PE_3,   // D63
  PE_4,   // D64
  PH_0,   // D65
  PH_1,   // D66
  PH_3    // D67
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
  8,  // A8,  PA8
  9,  // A9,  PA9
  30, // A10, PC0
  31, // A11, PC1
  32, // A12, PC2
  33, // A13, PC3
  34, // A14, PC4
  35  // A15, PC5
};

#endif /* ARDUINO_GENERIC_* */
