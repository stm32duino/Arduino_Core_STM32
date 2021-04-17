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
#if defined(ARDUINO_GENERIC_G473CBUX) || defined(ARDUINO_GENERIC_G473CCUX) ||\
    defined(ARDUINO_GENERIC_G473CEUX) || defined(ARDUINO_GENERIC_G474CBUX) ||\
    defined(ARDUINO_GENERIC_G474CCUX) || defined(ARDUINO_GENERIC_G474CEUX) ||\
    defined(ARDUINO_GENERIC_G483CEUX) || defined(ARDUINO_GENERIC_G484CEUX)
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
  PA_8,   // D9/A8
  PA_9,   // D10/A9
  PA_10,  // D11
  PA_11,  // D12
  PA_12,  // D13
  PA_13,  // D14
  PA_14,  // D15
  PA_15,  // D16
  PB_0,   // D17/A10
  PB_1,   // D18/A11
  PB_2,   // D19/A12
  PB_3,   // D20
  PB_4,   // D21
  PB_5,   // D22
  PB_6,   // D23
  PB_7,   // D24
  PB_8,   // D25
  PB_9,   // D26
  PB_10,  // D27
  PB_11,  // D28/A13
  PB_12,  // D29/A14
  PB_13,  // D30/A15
  PB_14,  // D31/A16
  PB_15,  // D32/A17
  PC_4,   // D33/A18
  PC_6,   // D34
  PC_10,  // D35
  PC_11,  // D36
  PC_13,  // D37
  PC_14,  // D38
  PC_15,  // D39
  PF_0,   // D40/A19
  PF_1,   // D41/A20
  PG_10   // D42
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
  9,  // A9,  PA9
  16, // A10, PB0
  17, // A11, PB1
  18, // A12, PB2
  27, // A13, PB11
  28, // A14, PB12
  29, // A15, PB13
  30, // A16, PB14
  31, // A17, PB15
  32, // A18, PC4
  39, // A19, PF0
  40  // A20, PF1
};

#endif /* ARDUINO_GENERIC_* */
