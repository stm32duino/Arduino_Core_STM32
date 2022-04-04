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
#if defined(ARDUINO_GENERIC_G473MEYX) || defined(ARDUINO_GENERIC_G474MEYX) ||\
    defined(ARDUINO_GENERIC_G483MEYX) || defined(ARDUINO_GENERIC_G484MEYX)
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
  PA_9,   // D9/A9
  PA_10,  // D10
  PA_11,  // D11
  PA_12,  // D12
  PA_13,  // D13
  PA_14,  // D14
  PA_15,  // D15
  PB_0,   // D16/A10
  PB_1,   // D17/A11
  PB_2,   // D18/A12
  PB_3,   // D19
  PB_4,   // D20
  PB_5,   // D21
  PB_6,   // D22
  PB_7,   // D23
  PB_8,   // D24
  PB_9,   // D25
  PB_10,  // D26
  PB_11,  // D27/A13
  PB_12,  // D28/A14
  PB_13,  // D29/A15
  PB_14,  // D30/A16
  PB_15,  // D31/A17
  PC_0,   // D32/A18
  PC_1,   // D33/A19
  PC_2,   // D34/A20
  PC_3,   // D35/A21
  PC_4,   // D36/A22
  PC_5,   // D37/A23
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
  PD_8,   // D51/A24
  PD_9,   // D52/A25
  PD_10,  // D53/A26
  PD_11,  // D54/A27
  PE_7,   // D55/A28
  PE_8,   // D56/A29
  PE_9,   // D57/A30
  PE_10,  // D58/A31
  PE_11,  // D59/A32
  PE_12,  // D60/A33
  PE_13,  // D61/A34
  PE_14,  // D62/A35
  PE_15,  // D63/A36
  PF_0,   // D64/A37
  PF_1,   // D65/A38
  PG_10   // D66
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
  32, // A18, PC0
  33, // A19, PC1
  34, // A20, PC2
  35, // A21, PC3
  36, // A22, PC4
  37, // A23, PC5
  51, // A24, PD8
  52, // A25, PD9
  53, // A26, PD10
  54, // A27, PD11
  55, // A28, PE7
  56, // A29, PE8
  57, // A30, PE9
  58, // A31, PE10
  59, // A32, PE11
  60, // A33, PE12
  61, // A34, PE13
  62, // A35, PE14
  63, // A36, PE15
  64, // A37, PF0
  65  // A38, PF1
};

#endif /* ARDUINO_GENERIC_* */
