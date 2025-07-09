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
#if defined(ARDUINO_GENERIC_WB05KZVX) || defined(ARDUINO_GENERIC_WB05TZFX) ||\
    defined(ARDUINO_GENERIC_WB09KEVX) || defined(ARDUINO_GENERIC_WB09TEFX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3/A0
  PA_8,   // D4
  PA_9,   // D5
  PA_10,  // D6
  PA_11,  // D7
  PB_0,   // D8
  PB_1,   // D9/A1
  PB_2,   // D10
  PB_3,   // D11/A2
  PB_4,   // D12
  PB_5,   // D13/A3
  PB_6,   // D14
  PB_7,   // D15
  PB_12,  // D16
  PB_13,  // D17
  PB_14,  // D18
  PB_15   // D19
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  3,  // A0,  PA3
  9,  // A1,  PB1
  11, // A2,  PB3
  13  // A3,  PB5
};

#endif /* ARDUINO_GENERIC_* */
