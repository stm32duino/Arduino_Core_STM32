/*
 *******************************************************************************
 * Copyright (c) 2016, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "Arduino.h"
#include "PeripheralPins.h"

// =====
// Note: Commented lines are alternative possibilities which are not used per default.
//       If you change them, you will have to know what you do
// =====


//*** ADC ***

const PinMap PinMap_ADC[] = {
  {PA0,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 0, 0)}, // ADC1_IN0
  // {PA0,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 0, 0)}, // ADC2_IN0
  {PA1,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // ADC1_IN1
  // {PA1,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // ADC2_IN1
  {PA2,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // ADC1_IN2
  // {PA2,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // ADC2_IN2
  {PA3,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 3, 0)}, // ADC1_IN3
  // {PA3,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 3, 0)}, // ADC2_IN3
  {PA4,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 4, 0)}, // ADC1_IN4
  // {PA4,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 4, 0)}, // ADC2_IN4
  {PA5,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 5, 0)}, // ADC1_IN5
  // {PA5,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 5, 0)}, // ADC2_IN5
  {PA6,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 6, 0)}, // ADC1_IN6
  // {PA6,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 6, 0)}, // ADC2_IN6
  {PA7,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 7, 0)}, // ADC1_IN7
  // {PA7,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 7, 0)}, // ADC2_IN7
  {PB0,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 8, 0)}, // ADC1_IN8
  // {PB0,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 8, 0)}, // ADC2_IN8
  {PB1,   ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 9, 0)}, // ADC1_IN9
  // {PB1,   ADC2,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 9, 0)}, // ADC2_IN9
  {NC,   NC,    0}
};

//*** DAC ***

const PinMap PinMap_DAC[] = {
    {NC,   NC,    0}
};

//*** I2C ***

const PinMap PinMap_I2C_SDA[] = {
    {PB7,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {PB9,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 2)}, // GPIO_Remap_I2C1
    {PB11,  I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PB6,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {PB8,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 2)}, // GPIO_Remap_I2C1
    {PB10,  I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, 0)},
    {NC,    NC,    0}
};

//*** PWM ***

const PinMap PinMap_PWM[] = {
    {PA0,   TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 1, 0)},  // TIM2_CH1
    {PA1,   TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 2, 0)},  // TIM2_CH2
    {PA2,   TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 3, 0)},  // TIM2_CH3
    {PA3,   TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 4, 0)},  // TIM2_CH4
    {PA6,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 1, 0)},  // TIM3_CH1
    // {PA7,   TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 6, 1, 1)},  // TIM1_CH1N - GPIO_PartialRemap_TIM1
    {PA7,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 2, 0)},  // TIM3_CH2
    {PA8,   TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 1, 0)},  // TIM1_CH1
    {PA9,   TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 2, 0)},  // TIM1_CH2
    {PA10,  TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 3, 0)},  // TIM1_CH3
    {PA11,  TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 4, 0)},  // TIM1_CH4
    {PA15,  TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 8, 1, 0)},  // TIM2_CH1 - GPIO_FullRemap_TIM2
    // {PB0,   TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 6, 2, 1)},  // TIM1_CH2N - GPIO_PartialRemap_TIM1
    {PB0,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 3, 0)},  // TIM3_CH3
    // {PB1,   TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 6, 3, 1)},  // TIM1_CH3N - GPIO_PartialRemap_TIM1
    {PB1,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 4, 0)},  // TIM3_CH4
    {PB3,   TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 8, 2, 0)},  // TIM2_CH2 - GPIO_FullRemap_TIM2
    {PB4,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 7, 1, 0)},  // TIM3_CH1 - GPIO_PartialRemap_TIM3
    {PB5,   TIM3,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 7, 2, 0)},  // TIM3_CH2 - GPIO_PartialRemap_TIM3
    {PB6,   TIM4,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 1, 0)},  // TIM4_CH1
    {PB7,   TIM4,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 2, 0)},  // TIM4_CH2
    {PB8,   TIM4,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 3, 0)},  // TIM4_CH3
    {PB9,   TIM4,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 4, 0)},  // TIM4_CH4
    {PB10,  TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 8, 3, 0)},  // TIM2_CH3 - GPIO_FullRemap_TIM2
    {PB11,  TIM2,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 8, 4, 0)},  // TIM2_CH4 - GPIO_FullRemap_TIM2
    {PB13,  TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 1, 1)},  // TIM1_CH1N
    {PB14,  TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 2, 1)},  // TIM1_CH2N
    {PB15,  TIM1,   STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, 0, 3, 1)},  // TIM1_CH3N
    {NC,    NC,    0}
};

//*** SERIAL ***

const PinMap PinMap_UART_TX[] = {
    {PA2,   USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA9,   USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB6,   USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 3)}, // GPIO_Remap_USART1
    {PB10,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_UART_RX[] = {
    {PA3,   USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA10,  USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB7,   USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 3)}, // GPIO_Remap_USART1
    {PB11,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_UART_RTS[] = {
    {PA1,   USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA12,  USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB14,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_UART_CTS[] = {
    {PA0,   USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA11,  USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB13,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

//*** SPI ***

const PinMap PinMap_SPI_MOSI[] = {
    {PA7,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB5,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 1)}, // GPIO_Remap_SPI1
    {PB15,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PA6,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB4,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 1)}, // GPIO_Remap_SPI1
    {PB14,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_SCLK[] = {
    {PA5,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PB3,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 1)}, // GPIO_Remap_SPI1
    {PB13,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PA4,   SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {PA15,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 1)}, // GPIO_Remap_SPI1
    {PB12,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, 0)},
    {NC,    NC,    0}
};

//*** CAN ***

const PinMap PinMap_CAN_RD[] = {
    {PA11,  CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PB8,   CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 10)}, // Remap CAN_RX to PB_9
    {NC,    NC,    0}
};

const PinMap PinMap_CAN_TD[] = {
    {PA12,  CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 0)},
    {PB9,   CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, 10)}, // Remap CAN_TX to PB_9
    {NC,    NC,    0}
};
