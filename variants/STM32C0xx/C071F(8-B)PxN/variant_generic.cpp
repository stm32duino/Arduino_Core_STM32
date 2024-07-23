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
#if defined(ARDUINO_GENERIC_C071F8PXN) || defined(ARDUINO_GENERIC_C071FBPXN)
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
  PA_8,   // D7/A7
  PA_11,  // D8
  PA_12,  // D9
  PA_13,  // D10/A8
  PA_14,  // D11/A9
  PA_15,  // D12
  PB_3,   // D13
  PB_4,   // D14
  PB_5,   // D15
  PB_6,   // D16
  PB_7,   // D17
  PB_8,   // D18
  PC_14,  // D19
  PC_15,  // D20
  PF_2    // D21
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
  7,  // A7,  PA8
  10, // A8,  PA13
  11  // A9,  PA14
};

#endif /* ARDUINO_GENERIC_* */
