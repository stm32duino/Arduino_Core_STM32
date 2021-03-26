/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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
#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Digital connector 1
#define PA3   0
#define PA2   1
#define PA0   2
#define PA1   3
#define PB5   4
#define PB6   5
#define PA8   6
#define PA9   7

// Digital connector 2
#define PA10  8
#define PB7   9
#define PA4   10
#define PA7   11
#define PA6   12
#define PA5   13
#define PB8   14

// Analog connector
#define PC0   15
#define PC1   16
#define PC2   17
#define PC3   18
#define PC4   19
#define PC5   20

#define PC13  21

// GPIO extention
#define PC15  23
#define PB9   24
#define PD2   25
#define PC10  26
#define PB0   27
#define PB1   28
#define PB10  29
#define PB11  30
#define PB12  31
#define PB13  32
#define PB14  33
#define PB15  34
#define PC6   35
#define PC7   36
#define PC8   37

// UEXT_PWR
#define PF4   38

// GPIO extention
#define EXT_GPIO1 23
#define EXT_GPIO2 24
#define EXT_GPIO3 25
#define EXT_GPIO4 26
#define EXT_GPIO5 27
#define EXT_GPIO6 28
#define EXT_GPIO7 29
#define EXT_GPIO8 30
#define EXT_GPIO9 31
#define EXT_GPIO10  32
#define EXT_GPIO11  33
#define EXT_GPIO12  34
#define EXT_GPIO13  35
#define EXT_GPIO14  36
#define EXT_GPIO15  37

// UEXT
#define UEXTPWR 38
#define UEXT3 29
#define UEXT4 30
#define UEXT5 7
#define UEXT6 8
#define UEXT7 12
#define UEXT8 11
#define UEXT9 13
#define UEXT10  4
//#define UEXT10  10


// This must be a literal
#define NUM_DIGITAL_PINS        39
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        15

// On-board LED pin number
#define LED1    13
#define LED_GREEN LED1
#define LED2    3
#define LED_YELLOW  LED2

// On-board button pin button
#define BUTTON    22

// SPI Definitions
// SPI1
#define PIN_SPI_SS    PA4   // D10
#define PIN_SPI_SCK   PA5   // D13
#define PIN_SPI_MISO  PA6   // D12
#define PIN_SPI_MOSI  PA7   // D11

// SPI2
#define PIN_SPI2_SS   PB12  // D31
#define PIN_SPI2_SCK  PB13  // D32
#define PIN_SPI2_MISO PB14  // D33
#define PIN_SPI2_MOSI PB15  // D34

// SPI3
// #define  PIN_SPI3_SS   -1  // PA_15
// #define  PIN_SPI3_SCK  -1  // PB_3
// #define  PIN_SPI3_MISO -1  // PB_4
// #define  PIN_SPI3_MOSI -1  // PB_5

// SD card SPI2 definitions
#define SDCARD_SPI    SPI_2
#define SDCARD_SS_PIN PIN_SPI2_SS   // D31  SPI2_#SS
#define SDCARD_SCK_PIN  PIN_SPI2_SCK  // D32
#define SDCARD_MISO_PIN PIN_SPI2_MISO // D33
#define SDCARD_MOSI_PIN PIN_SPI2_MOSI // D34

// I2C Definitions
#define PIN_WIRE_SDA            PA10
#define PIN_WIRE_SCL            PA9

// Timer Definitions
// Use TIM6 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM2

// UART Definitions
#define HAVE_HWSERIAL1
#define PIN_SERIAL1_TX           PB6  // D5
#define PIN_SERIAL1_RX           PB7  // D9

#define HAVE_HWSERIAL2
#define PIN_SERIAL2_TX           PA2  // D1
#define PIN_SERIAL2_RX           PA3  // D0

#define HAVE_HWSERIAL3
#define PIN_SERIAL3_TX           PB10 // TX GPIO29
#define PIN_SERIAL3_RX           PB11 // RX GPIO30

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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial1
  #define SERIAL_PORT_USBVIRTUAL  SerialUSB
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
