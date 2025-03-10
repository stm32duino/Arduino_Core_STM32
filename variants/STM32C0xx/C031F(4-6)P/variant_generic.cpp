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
#if defined(ARDUINO_GENERIC_C031F4PX) || defined(ARDUINO_GENERIC_C031F6PX)
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
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11/A9
  PA_12,  // D12/A10
  PA_13,  // D13/A11
  PA_14,  // D14/A12
  PB_6,   // D15
  PB_7,   // D16
  PC_14,  // D17
  PC_15,  // D18
  PF_2    // D19
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
  11, // A9,  PA11
  12, // A10, PA12
  13, // A11, PA13
  14  // A12, PA14
};

#endif /* ARDUINO_GENERIC_* */
