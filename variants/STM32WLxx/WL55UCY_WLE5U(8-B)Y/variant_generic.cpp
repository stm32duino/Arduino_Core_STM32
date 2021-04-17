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
#if defined(ARDUINO_GENERIC_WL55UCYX) || defined(ARDUINO_GENERIC_WLE5U8YX) ||\
    defined(ARDUINO_GENERIC_WLE5UBYX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1
  PA_1,   // D2
  PA_2,   // D3
  PA_3,   // D4
  PA_4,   // D5
  PA_5,   // D6
  PA_6,   // D7
  PA_7,   // D8
  PA_8,   // D9
  PA_9,   // D10
  PA_10,  // D11/A0
  PA_11,  // D12/A1
  PA_12,  // D13/A2
  PA_13,  // D14/A3
  PA_14,  // D15/A4
  PA_15,  // D16/A5
  PB_0,   // D17
  PB_3,   // D18/A6
  PB_4,   // D19/A7
  PC_14,  // D20
  PC_15,  // D21
  PH_3    // D22
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  10, // A0,  PA10
  11, // A1,  PA11
  12, // A2,  PA12
  13, // A3,  PA13
  14, // A4,  PA14
  15, // A5,  PA15
  17, // A6,  PB3
  18  // A7,  PB4
};

#endif /* ARDUINO_GENERIC_* */
