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
#if defined(ARDUINO_GENERIC_WBA65RGVX) || defined(ARDUINO_GENERIC_WBA65RIVX)
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
  PA_8,   // D8/A8
  PA_9,   // D9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_0,   // D16
  PB_1,   // D17
  PB_2,   // D18
  PB_3,   // D19
  PB_4,   // D20
  PB_8,   // D21
  PB_9,   // D22/A9
  PB_10,  // D23
  PB_11,  // D24
  PB_12,  // D25
  PB_13,  // D26
  PB_14,  // D27
  PB_15,  // D28
  PC_3,   // D29
  PC_4,   // D30
  PC_5,   // D31
  PC_13,  // D32
  PC_14,  // D33
  PC_15,  // D34
  PD_5,   // D35
  PD_6,   // D36
  PD_7,   // D37
  PD_8,   // D38
  PD_9,   // D39
  PD_14,  // D40
  PE_0,   // D41
  PE_1,   // D42
  PE_2,   // D43
  PE_3,   // D44
  PH_3    // D45
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
  8,  // A8,  PA8
  22  // A9,  PB9
};

#endif /* ARDUINO_GENERIC_* */
