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
#if defined(ARDUINO_GENERIC_H503EBYX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_5,   // D1/A1
  PA_7,   // D2/A2
  PA_8,   // D3
  PA_9,   // D4
  PA_11,  // D5
  PA_12,  // D6
  PA_13,  // D7
  PA_14,  // D8
  PA_15,  // D9
  PB_3,   // D10
  PB_4,   // D11
  PB_5,   // D12
  PB_6,   // D13
  PB_7,   // D14
  PB_8,   // D15
  PB_15,  // D16
  PC_14,  // D17
  PC_15   // D18
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA5
  2   // A2,  PA7
};

#endif /* ARDUINO_GENERIC_* */
