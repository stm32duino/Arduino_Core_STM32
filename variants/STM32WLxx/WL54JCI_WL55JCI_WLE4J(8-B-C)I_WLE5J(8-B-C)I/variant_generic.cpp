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
#if defined(ARDUINO_GENERIC_WL54JCIX) || defined(ARDUINO_GENERIC_WL55JCIX) ||\
    defined(ARDUINO_GENERIC_WLE4J8IX) || defined(ARDUINO_GENERIC_WLE4JBIX) ||\
    defined(ARDUINO_GENERIC_WLE4JCIX) || defined(ARDUINO_GENERIC_WLE5J8IX) ||\
    defined(ARDUINO_GENERIC_WLE5JBIX) || defined(ARDUINO_GENERIC_WLE5JCIX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3
  PA_4,   // D4
  PA_5,   // D5
  PA_6,   // D6
  PA_7,   // D7
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10/A0
  PA_11,  // D11/A1
  PA_12,  // D12/A2
  PA_13,  // D13/A3
  PA_14,  // D14/A4
  PA_15,  // D15/A5
  PB_0,   // D16
  PB_1,   // D17/A6
  PB_2,   // D18/A7
  PB_3,   // D19/A8
  PB_4,   // D20/A9
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_11,  // D27
  PB_12,  // D28
  PB_13,  // D29/A10
  PB_14,  // D30/A11
  PB_15,  // D31
  PC_0,   // D32
  PC_1,   // D33
  PC_2,   // D34
  PC_3,   // D35
  PC_4,   // D36
  PC_5,   // D37
  PC_6,   // D38
  PC_13,  // D39
  PC_14,  // D40
  PC_15,  // D41
  PH_3    // D42
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  10, // A0,  PA10
  11, // A1,  PA11
  12, // A2,  PA12
  13, // A3,  PA13
  14, // A4,  PA14
  15, // A5,  PA15
  17, // A6,  PB1
  18, // A7,  PB2
  19, // A8,  PB3
  20, // A9,  PB4
  29, // A10, PB13
  30  // A11, PB14
};

#endif /* ARDUINO_GENERIC_* */
