/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
// board doesn't breakout r3 connectors so listing in chip order
// LEFT
#define PC13 0 // PHASE_UL
#define PC14 1 // CAN_TERM
#define PC15 2 // x (NOT_CONNECTED)
#define PF0  3 // OSC_IN
#define PF1  4 // OSC_OUT
#define PG10 5 // NRST
#define PA0  6 // VBUS
#define PA1  7 // CURR1_H
#define PA2  8 // OP1_OUT
#define PA3  9 // CURR1_L
#define PA4  10 // BEMF1
// BOTTOM
#define PA5  11 // CURR2_L
#define PA6  12 // OP2_OUT
#define PA7  13 // CURR2_H
#define PC4  14  // BEMF2
#define PB0  15 // CURR3_H
#define PB1  16 // OP3_OUT
#define PB2  17 // CURR3_L
#define PB10 18  // x
#define PB11 19 // BEMF3
// RIGHT
#define PB12 20 // POTENTIOMETER
#define PB13 21 // x
#define PB14 22 // TEMPERATURE
#define PB15 23 // PHASE_WL
#define PC6  24 // LED_BUILTIN
#define PA8  25  // PHASE_UH
#define PA9  26  // PHASE_VH
#define PA10 27  // PHASE_WH
#define PA11 28 // CAN_RX
#define PA12 29 // PHASE_VL
#define PA13 30 // SWDIO
// TOP
#define PA14 31 // SWCLK
#define PA15 32 // PWM
#define PC10 33 // BUTTON
#define PC11 34 // CAN_SHDN
#define PB3  35  // USART2_TX
#define PB4  36  // USART2_RX
#define PB5  37  // GPIO_BEMF
#define PB6  38 // HALL1/ENCODER_A
#define PB7  39 // HALL2/ENCODER_B
#define PB8  40 // HALL3/ENCODER_Z
#define PB9  41 // CAN_TX

// This must be a literal
#define NUM_DIGITAL_PINS        42
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16


#define PHASE_UL      PC13
#define CAN_TERM      PC14
#define VBUS          PA0
#define CURR1_H       PA1
#define OP1_OUT       PA2 
#define CURR1_L       PA3 
#define BEMF1         PA4 
#define CURR2_L       PA5 
#define OP2_OUT       PA6 
#define CURR2_H       PA7 
#define BEMF2         PC4 
#define CURR3_H       PB0
#define OP3_OUT       PB1 
#define CURR3_L       PB2 
#define BEMF3         PB11 
#define POTENTIOMETER PB12 
#define TEMPERATURE   PB14
#define PHASE_WL      PB15
#define LED_BUILTIN   PC6 
#define PHASE_UH      PA8 
#define PHASE_VH      PA9 
#define PHASE_WH      PA10 
#define CAN_RX        PA11
#define PHASE_VL      PA12
#define SWDIO         PA13 
#define SWCLK         PA14 
#define PWM           PA15 
#define BUTTON        PC10 
#define CAN_SHDN      PC11 
#define USART2_TX     PB3 
#define USART2_RX     PB4 
#define GPIO_BEMF     PB5 
#define HALL1         PB6
#define HALL2         PB7
#define HALL3         PB8
#define ENCODER_A     PB6
#define ENCODER_B     PB7
#define ENCODER_Z     PB8
#define CAN_TX        PB9


// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           USART2_TX
#define PIN_SERIAL_TX           USART2_TX

/* HAL configuration */
#define HSE_VALUE               (24000000UL)

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  SerialLP1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
