/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_GENERIC_WBA25HEFX)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_5,   // D0/A0
  PA_6,   // D1/A1
  PA_8,   // D2/A2
  PA_12,  // D3
  PA_13,  // D4
  PA_14,  // D5
  PA_15,  // D6
  PB_3,   // D7
  PB_4,   // D8
  PB_8,   // D9
  PB_9,   // D10
  PB_15,  // D11
  PC_14,  // D12
  PC_15,  // D13
  PH_3    // D14
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  0,  // A0,  PA5
  1,  // A1,  PA6
  2   // A2,  PA8
};

#endif /* ARDUINO_GENERIC_* */
