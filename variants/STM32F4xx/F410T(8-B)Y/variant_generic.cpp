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
#if defined(ARDUINO_GENERIC_F410T8YX) || defined(ARDUINO_GENERIC_F410TBYX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0/A0
  PA_2,   // D1/A1
  PA_3,   // D2/A2
  PA_5,   // D3/A3
  PA_8,   // D4
  PA_12,  // D5
  PA_13,  // D6
  PA_14,  // D7
  PA_15,  // D8
  PB_2,   // D9
  PB_3,   // D10
  PB_4,   // D11
  PB_5,   // D12
  PB_6,   // D13
  PB_7,   // D14
  PB_8,   // D15
  PB_10,  // D16
  PB_12,  // D17
  PC_13,  // D18
  PC_14,  // D19
  PC_15,  // D20
  PH_0,   // D21
  PH_1    // D22
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA2
  2,  // A2,  PA3
  3   // A3,  PA5
};

#endif /* ARDUINO_GENERIC_* */
