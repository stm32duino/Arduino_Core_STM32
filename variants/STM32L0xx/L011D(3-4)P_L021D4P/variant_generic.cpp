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
#if defined(ARDUINO_GENERIC_L011D3PX) || defined(ARDUINO_GENERIC_L011D4PX) ||\
    defined(ARDUINO_GENERIC_L021D4PX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1/A0
  PA_1,   // D2/A1
  PA_4,   // D3/A2
  PA_7,   // D4/A3
  PA_9,   // D5
  PA_10,  // D6
  PA_13,  // D7
  PA_14,  // D8
  PB_9,   // D9
  PC_14,  // D10
  PC_15   // D11
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA4
  3   // A3,  PA7
};

#endif /* ARDUINO_GENERIC_* */
