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
#if defined(ARDUINO_GENERIC_F048G6UX)
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
  PA_9,   // D8
  PA_10,  // D9
  PA_13,  // D10
  PA_14,  // D11
  PA_15,  // D12
  PB_0,   // D13/A8
  PB_3,   // D14
  PB_4,   // D15
  PB_5,   // D16
  PB_6,   // D17
  PB_7,   // D18
  PB_8,   // D19
  PF_0,   // D20
  PF_1,   // D21
  PA_11_R, // D22
  PA_12_R // D23
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
  13  // A8,  PB0
};

#endif /* ARDUINO_GENERIC_* */
