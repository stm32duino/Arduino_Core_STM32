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
#if defined(ARDUINO_GENERIC_WL54CCUX) || defined(ARDUINO_GENERIC_WL55CCUX) ||\
    defined(ARDUINO_GENERIC_WLE4C8UX) || defined(ARDUINO_GENERIC_WLE4CBUX) ||\
    defined(ARDUINO_GENERIC_WLE4CCUX) || defined(ARDUINO_GENERIC_WLE5C8UX) ||\
    defined(ARDUINO_GENERIC_WLE5CBUX) || defined(ARDUINO_GENERIC_WLE5CCUX)
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
  PB_2,   // D17/A6
  PB_3,   // D18/A7
  PB_4,   // D19/A8
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_12,  // D24
  PC_13,  // D25
  PC_14,  // D26
  PC_15,  // D27
  PH_3    // D28
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  10, // A0,  PA10
  11, // A1,  PA11
  12, // A2,  PA12
  13, // A3,  PA13
  14, // A4,  PA14
  15, // A5,  PA15
  17, // A6,  PB2
  18, // A7,  PB3
  19  // A8,  PB4
};

#endif /* ARDUINO_GENERIC_* */
