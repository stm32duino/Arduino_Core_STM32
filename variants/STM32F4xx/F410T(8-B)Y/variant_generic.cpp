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
#if defined(ARDUINO_GENERIC_F410T8YX) || defined(ARDUINO_GENERIC_F410TBYX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1/A0
  PA_2,   // D2/A1
  PA_3,   // D3/A2
  PA_5,   // D4/A3
  PA_8,   // D5
  PA_12,  // D6
  PA_13,  // D7
  PA_14,  // D8
  PA_15,  // D9
  PB_2,   // D10
  PB_3,   // D11
  PB_4,   // D12
  PB_5,   // D13
  PB_6,   // D14
  PB_7,   // D15
  PB_8,   // D16
  PB_10,  // D17
  PB_12,  // D18
  PC_13,  // D19
  PC_14,  // D20
  PC_15,  // D21
  PH_0,   // D22
  PH_1    // D23
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  0,  // A0,  PA0
  1,  // A1,  PA2
  2,  // A2,  PA3
  3   // A3,  PA5
};

#endif /* ARDUINO_GENERIC_* */
