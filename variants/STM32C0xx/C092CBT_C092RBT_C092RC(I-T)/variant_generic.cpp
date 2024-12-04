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
#if defined(ARDUINO_GENERIC_C092CBTX) || defined(ARDUINO_GENERIC_C092RBTX) ||\
    defined(ARDUINO_GENERIC_C092RCIX) || defined(ARDUINO_GENERIC_C092RCTX)
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
  PA_13,  // D13/A9
  PA_14,  // D14/A10
  PA_15,  // D15
  PB_0,   // D16/A11
  PB_1,   // D17/A12
  PB_2,   // D18/A13
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26/A14
  PB_11,  // D27/A15
  PB_12,  // D28/A16
  PB_13,  // D29
  PB_14,  // D30
  PB_15,  // D31
  PC_0,   // D32
  PC_1,   // D33
  PC_2,   // D34
  PC_3,   // D35
  PC_4,   // D36/A17
  PC_5,   // D37/A18
  PC_6,   // D38
  PC_7,   // D39
  PC_8,   // D40
  PC_9,   // D41
  PC_10,  // D42
  PC_11,  // D43
  PC_12,  // D44
  PC_13,  // D45
  PC_14,  // D46
  PC_15,  // D47
  PD_0,   // D48
  PD_1,   // D49
  PD_2,   // D50
  PD_3,   // D51
  PD_4,   // D52
  PD_5,   // D53
  PD_6,   // D54
  PD_8,   // D55
  PD_9,   // D56
  PF_0,   // D57
  PF_1,   // D58
  PF_2,   // D59
  PF_3    // D60
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
  13, // A9,  PA13
  14, // A10, PA14
  16, // A11, PB0
  17, // A12, PB1
  18, // A13, PB2
  26, // A14, PB10
  27, // A15, PB11
  28, // A16, PB12
  36, // A17, PC4
  37  // A18, PC5
};

#endif /* ARDUINO_GENERIC_* */
