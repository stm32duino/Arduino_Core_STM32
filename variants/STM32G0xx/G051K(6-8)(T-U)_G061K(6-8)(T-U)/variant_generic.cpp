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
#if defined(ARDUINO_GENERIC_G051K6TX) || defined(ARDUINO_GENERIC_G051K6UX) ||\
    defined(ARDUINO_GENERIC_G051K8TX) || defined(ARDUINO_GENERIC_G051K8UX) ||\
    defined(ARDUINO_GENERIC_G061K6TX) || defined(ARDUINO_GENERIC_G061K6UX) ||\
    defined(ARDUINO_GENERIC_G061K8TX) || defined(ARDUINO_GENERIC_G061K8UX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   // D1/A0
  PA_1,   // D2/A1
  PA_2,   // D3/A2
  PA_3,   // D4/A3
  PA_4,   // D5/A4
  PA_5,   // D6/A5
  PA_6,   // D7/A6
  PA_7,   // D8/A7
  PA_8,   // D9
  PA_9,   // D10
  PA_10,  // D11
  PA_11,  // D12/A8
  PA_12,  // D13/A9
  PA_13,  // D14/A10
  PA_14,  // D15/A11
  PA_15,  // D16
  PB_0,   // D17/A12
  PB_1,   // D18/A13
  PB_2,   // D19/A14
  PB_3,   // D20
  PB_4,   // D21
  PB_5,   // D22
  PB_6,   // D23
  PB_7,   // D24/A15
  PB_8,   // D25
  PB_9,   // D26
  PC_6,   // D27
  PC_14,  // D28
  PC_15,  // D29
  PF_2,   // D30
  PA_9_R, // D31
  PA_10_R // D32
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
  11, // A8,  PA11
  12, // A9,  PA12
  13, // A10, PA13
  14, // A11, PA14
  16, // A12, PB0
  17, // A13, PB1
  18, // A14, PB2
  23  // A15, PB7
};

#endif /* ARDUINO_GENERIC_* */
