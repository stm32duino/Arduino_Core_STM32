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
#if defined(ARDUINO_GENERIC_WB06CCVX) || defined(ARDUINO_GENERIC_WB07CCVX)
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
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13/A0
  PA_14,  // D14
  PA_15,  // D15/A1
  PB_0,   // D16
  PB_1,   // D17/A2
  PB_2,   // D18
  PB_3,   // D19/A3
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
  PB_15   // D31
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  13, // A0,  PA13
  15, // A1,  PA15
  17, // A2,  PB1
  19  // A3,  PB3
};

#endif /* ARDUINO_GENERIC_* */
