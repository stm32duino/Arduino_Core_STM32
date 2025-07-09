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
#if defined(ARDUINO_GENERIC_WB06CCFX) || defined(ARDUINO_GENERIC_WB07CCFX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3
  PA_4,   // D4
  PA_5,   // D5
  PA_7,   // D6
  PA_8,   // D7
  PA_9,   // D8
  PA_10,  // D9
  PA_11,  // D10
  PA_12,  // D11
  PA_13,  // D12/A0
  PA_14,  // D13
  PA_15,  // D14/A1
  PB_0,   // D15
  PB_1,   // D16/A2
  PB_2,   // D17
  PB_3,   // D18/A3
  PB_4,   // D19
  PB_5,   // D20
  PB_6,   // D21
  PB_7,   // D22
  PB_8,   // D23
  PB_9,   // D24
  PB_12,  // D25
  PB_13,  // D26
  PB_14,  // D27
  PB_15   // D28
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  12, // A0,  PA13
  14, // A1,  PA15
  16, // A2,  PB1
  18  // A3,  PB3
};

#endif /* ARDUINO_GENERIC_* */
