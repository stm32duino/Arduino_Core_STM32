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
#if defined(ARDUINO_GENERIC_WL3RK8VX) || defined(ARDUINO_GENERIC_WL3RK8VXX) ||\
    defined(ARDUINO_GENERIC_WL3RKBVX) || defined(ARDUINO_GENERIC_WL3RKBVXX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3/A0
  PA_7,   // D4
  PA_8,   // D5
  PA_9,   // D6
  PA_10,  // D7
  PA_11,  // D8
  PB_0,   // D9
  PB_1,   // D10/A1
  PB_2,   // D11
  PB_6,   // D12
  PB_7,   // D13
  PB_12,  // D14
  PB_13,  // D15
  PB_14,  // D16
  PB_15   // D17
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  3,  // A0,  PA3
  10  // A1,  PB1
};

#endif /* ARDUINO_GENERIC_* */
