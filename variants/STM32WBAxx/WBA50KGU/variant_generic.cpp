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
#if defined(ARDUINO_GENERIC_WBA50KGUX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_1,   // D1/A1
  PA_2,   // D2/A2
  PA_5,   // D3/A3
  PA_6,   // D4/A4
  PA_7,   // D5/A5
  PA_8,   // D6/A6
  PA_12,  // D7
  PA_13,  // D8
  PA_14,  // D9
  PA_15,  // D10
  PB_3,   // D11
  PB_4,   // D12
  PB_8,   // D13
  PB_9,   // D14/A7
  PB_12,  // D15
  PB_15,  // D16
  PC_14,  // D17
  PC_15,  // D18
  PH_3    // D19
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA1
  2,  // A2,  PA2
  3,  // A3,  PA5
  4,  // A4,  PA6
  5,  // A5,  PA7
  6,  // A6,  PA8
  14  // A7,  PB9
};

#endif /* ARDUINO_GENERIC_* */
