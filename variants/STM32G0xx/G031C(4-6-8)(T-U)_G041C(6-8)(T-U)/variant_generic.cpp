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
#if defined(ARDUINO_GENERIC_G031C4TX) || defined(ARDUINO_GENERIC_G031C4UX) ||\
    defined(ARDUINO_GENERIC_G031C6TX) || defined(ARDUINO_GENERIC_G031C6UX) ||\
    defined(ARDUINO_GENERIC_G031C8TX) || defined(ARDUINO_GENERIC_G031C8UX) ||\
    defined(ARDUINO_GENERIC_G041C6TX) || defined(ARDUINO_GENERIC_G041C6UX) ||\
    defined(ARDUINO_GENERIC_G041C8TX) || defined(ARDUINO_GENERIC_G041C8UX)
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
  PA_13,  // D13/A8
  PA_14,  // D14/A9
  PA_15,  // D15
  PB_0,   // D16/A10
  PB_1,   // D17/A11
  PB_2,   // D18/A12
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26/A13
  PB_11,  // D27/A14
  PB_12,  // D28/A15
  PB_13,  // D29
  PB_14,  // D30
  PB_15,  // D31
  PC_6,   // D32
  PC_7,   // D33
  PC_13,  // D34
  PC_14,  // D35
  PC_15,  // D36
  PD_0,   // D37
  PD_1,   // D38
  PD_2,   // D39
  PD_3,   // D40
  PF_0,   // D41
  PF_1,   // D42
  PF_2,   // D43
  PA_9_R, // D44
  PA_10_R // D45
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
  13, // A8,  PA13
  14, // A9,  PA14
  16, // A10, PB0
  17, // A11, PB1
  18, // A12, PB2
  26, // A13, PB10
  27, // A14, PB11
  28  // A15, PB12
};

#endif /* ARDUINO_GENERIC_* */
