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
#if defined(ARDUINO_GENERIC_F301R6TX) || defined(ARDUINO_GENERIC_F301R8TX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1/A0
  PA_1,   // D2/A1
  PA_2,   // D3/A2
  PA_3,   // D4/A3
  PA_4,   // D5/A4
  PA_5,   // D6
  PA_6,   // D7/A5
  PA_7,   // D8/A6
  PA_8,   // D9
  PA_9,   // D10
  PA_10,  // D11
  PA_11,  // D12
  PA_12,  // D13
  PA_13,  // D14
  PA_14,  // D15
  PA_15,  // D16
  PB_0,   // D17/A7
  PB_1,   // D18/A8
  PB_2,   // D19
  PB_3,   // D20
  PB_4,   // D21
  PB_5,   // D22
  PB_6,   // D23
  PB_7,   // D24
  PB_8,   // D25
  PB_9,   // D26
  PB_10,  // D27
  PB_11,  // D28/A9
  PB_12,  // D29
  PB_13,  // D30/A10
  PB_14,  // D31
  PB_15,  // D32
  PC_0,   // D33/A11
  PC_1,   // D34/A12
  PC_2,   // D35/A13
  PC_3,   // D36/A14
  PC_4,   // D37
  PC_5,   // D38
  PC_6,   // D39
  PC_7,   // D40
  PC_8,   // D41
  PC_9,   // D42
  PC_10,  // D43
  PC_11,  // D44
  PC_12,  // D45
  PC_13,  // D46
  PC_14,  // D47
  PC_15,  // D48
  PD_2,   // D49
  PF_0,   // D50
  PF_1    // D51
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA3
  4,  // A4,  PA4
  6,  // A5,  PA6
  7,  // A6,  PA7
  16, // A7,  PB0
  17, // A8,  PB1
  27, // A9,  PB11
  29, // A10, PB13
  32, // A11, PC0
  33, // A12, PC1
  34, // A13, PC2
  35  // A14, PC3
};

#endif /* ARDUINO_GENERIC_* */
