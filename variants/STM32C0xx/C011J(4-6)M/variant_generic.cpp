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
#if defined(ARDUINO_GENERIC_C011J4MX) || defined(ARDUINO_GENERIC_C011J6MX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_8,   // D3/A3
  PA_11,  // D4/A4
  PA_12,  // D5/A5
  PA_13,  // D6/A6
  PA_14,  // D7/A7
  PB_6,   // D8
  PB_7,   // D9
  PC_14,  // D10
  PC_15,  // D11
  PF_2,   // D12
  PA_9_R, // D13
  PA_10_R // D14
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA8
  4,  // A4,  PA11
  5,  // A5,  PA12
  6,  // A6,  PA13
  7   // A7,  PA14
};

#endif /* ARDUINO_GENERIC_* */
