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
#if defined(ARDUINO_GENERIC_U535JEYXQ) || defined(ARDUINO_GENERIC_U545JEYXQ)
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
  PA_15,  // D15
  PB_0,   // D16/A8
  PB_1,   // D17/A9
  PB_2,   // D18/A10
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_10,  // D25
  PB_13,  // D26
  PB_14,  // D27
  PB_15,  // D28
  PC_1,   // D29/A11
  PC_13,  // D30
  PC_14,  // D31
  PC_15,  // D32
  PG_2,   // D33
  PG_3,   // D34
  PG_4,   // D35
  PG_5,   // D36
  PG_6,   // D37
  PG_7,   // D38
  PG_8,   // D39
  PG_9,   // D40
  PG_10,  // D41
  PG_11,  // D42
  PG_12,  // D43
  PG_13,  // D44
  PG_14,  // D45
  PG_15,  // D46
  PH_0,   // D47
  PH_1,   // D48
  PH_3    // D49
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
  16, // A8,  PB0
  17, // A9,  PB1
  18, // A10, PB2
  29  // A11, PC1
};

#endif /* ARDUINO_GENERIC_* */
