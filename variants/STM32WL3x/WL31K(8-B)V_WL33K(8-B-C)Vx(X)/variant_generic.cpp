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
#if defined(ARDUINO_GENERIC_WL31K8VX) || defined(ARDUINO_GENERIC_WL31KBVX) ||\
    defined(ARDUINO_GENERIC_WL33K8VX) || defined(ARDUINO_GENERIC_WL33K8VXX) ||\
    defined(ARDUINO_GENERIC_WL33KBVX) || defined(ARDUINO_GENERIC_WL33KBVXX) ||\
    defined(ARDUINO_GENERIC_WL33KCVX) || defined(ARDUINO_GENERIC_WL33KCVXX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D0
  PA_1,   // D1
  PA_2,   // D2
  PA_3,   // D3/A0
  PA_8,   // D4
  PA_9,   // D5
  PA_10,  // D6
  PA_11,  // D7
  PB_0,   // D8
  PB_1,   // D9/A1
  PB_2,   // D10
  PB_6,   // D11
  PB_7,   // D12
  PB_12,  // D13
  PB_13,  // D14
  PB_14,  // D15
  PB_15   // D16
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  3,  // A0,  PA3
  9   // A1,  PB1
};

#endif /* ARDUINO_GENERIC_* */
