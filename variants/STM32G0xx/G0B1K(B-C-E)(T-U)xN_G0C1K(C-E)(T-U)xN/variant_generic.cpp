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
#if defined(ARDUINO_GENERIC_G0B1KBTXN) || defined(ARDUINO_GENERIC_G0B1KBUXN) ||\
    defined(ARDUINO_GENERIC_G0B1KCTXN) || defined(ARDUINO_GENERIC_G0B1KCUXN) ||\
    defined(ARDUINO_GENERIC_G0B1KETXN) || defined(ARDUINO_GENERIC_G0B1KEUXN) ||\
    defined(ARDUINO_GENERIC_G0C1KCTXN) || defined(ARDUINO_GENERIC_G0C1KCUXN) ||\
    defined(ARDUINO_GENERIC_G0C1KETXN) || defined(ARDUINO_GENERIC_G0C1KEUXN)
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
  PA_7,   // D7/A7
  PA_8,   // D8
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PB_0,   // D15/A8
  PB_1,   // D16/A9
  PB_6,   // D17
  PB_7,   // D18
  PB_8,   // D19
  PB_9,   // D20
  PB_15,  // D21
  PC_14,  // D22
  PC_15,  // D23
  PD_0,   // D24
  PD_1,   // D25
  PD_2,   // D26
  PD_3,   // D27
  PF_2,   // D28
  PA_9_R, // D29
  PA_10_R // D30
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
  15, // A8,  PB0
  16  // A9,  PB1
};

#endif /* ARDUINO_GENERIC_* */
