/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
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

// Mapping of STM32 GPIO pin to digital pin number
#define PA6                     0      /* PX_GPIO0 */
#define PA5                     1      /* PX_GPIO1 */
#define PA1                     2      /* PX_GPIO2 */
#define PA0                     3      /* PX_GPIO3 */
#define PC3                     4      /* PX_GPIO4 */
#define PC2                     5      /* PX_GPIO5 */
#define PC1                     6      /* PX_GPIO6 */
#define PB7                     7      /* PX_GPIO7 */
#define PH0                     8      /* PX_USR_LED */
#define PC0                     9      /* PX_LCD_BTN_1_LT */
#define PH1                     10     /* PX_LCD_BTN_2_RT */
#define PC13                    11     /* PX_LCD_BTN_3_UP */
#define PC12                    12     /* PX_LCD_BTN_4_DN */
#define PA15                    13     /* PX_LCD_BTN_5_YES */
#define PC9                     14     /* PX_LCD_BTN_6_NO */
#define PA8                     15     /* PX_USB_DET */
#define PB11                    16     /* PX_LCD_RS */
#define PB12                    17     /* PX_LCD_BACKLIGHT */
#define PC6                     18     /* PX_PWM_BUZZER */
#define PC7                     19     /* PX_VBAT_MEAS_EN */
#define PC8                     20     /* PX_PWR_HOLD */
#define PA9                     21     /* PX_UART1_TX */
#define PA10                    22     /* PX_UART1_RX */
#define PA2                     23     /* PX_UART2_TX */
#define PA3                     24     /* PX_UART2_RX */
#define PC10                    25     /* PX_UART4_TX */
#define PC11                    26     /* PX_UART4_RX */
#define PB8                     27     /* PX_I2C1_SCL */
#define PB9                     28     /* PX_I2C1_SDA */
#define PB6                     29     /* PX_SPI1_CS */
#define PB3                     30     /* PX_SPI1_SCK */
#define PB5                     31     /* PX_SPI1_MOSI */
#define PB4                     32     /* PX_SPI1_MISO */
#define PB2                     33     /* PX_SPI2_CS_SF */
#define PB10                    34     /* PX_SPI2_CS_LCD */
#define PD2                     35     /* PX_SPI2_CS_SD */
#define PB13                    36     /* PX_SPI2_SCK */
#define PB15                    37     /* PX_SPI2_MOSI */
#define PB14                    38     /* PX_SPI2_MISO */
#define PA4                     39     /* PX_DAC1 */
#define PB0                     40     /* PX_ADC0 */
#define PC5                     41     /* PX_ADC1 */
#define PC4                     42     /* PX_ADC2 */
#define PA7                     43     /* PX_ADC3 */
#define PB1                     44     /* PX_ADC_VBAT */

// Mapping of net name to digital pin number
#define PX_GPIO0                PA6    /*  0 */
#define PX_GPIO1                PA5    /*  1 */
#define PX_GPIO2                PA1    /*  2 */
#define PX_GPIO3                PA0    /*  3 */
#define PX_GPIO4                PC3    /*  4 */
#define PX_GPIO5                PC2    /*  5 */
#define PX_GPIO6                PC1    /*  6 */
#define PX_GPIO7                PB7    /*  7 */
#define PX_USR_LED              PH0    /*  8 */
#define PX_LCD_BTN_1_LT         PC0    /*  9 */
#define PX_LCD_BTN_2_RT         PH1    /* 10 */
#define PX_LCD_BTN_3_UP         PC13   /* 11 */
#define PX_LCD_BTN_4_DN         PC12   /* 12 */
#define PX_LCD_BTN_5_YES        PA15   /* 13 */
#define PX_LCD_BTN_6_NO         PC9    /* 14 */
#define PX_USB_DET              PA8    /* 15 */
#define PX_LCD_RS               PB11   /* 16 */
#define PX_LCD_BACKLIGHT        PB12   /* 17 */
#define PX_PWM_BUZZER           PC6    /* 18 */
#define PX_VBAT_MEAS_EN         PC7    /* 19 */
#define PX_PWR_HOLD             PC8    /* 20 */
#define PX_UART1_TX             PA9    /* 21 */
#define PX_UART1_RX             PA10   /* 22 */
#define PX_UART2_TX             PA2    /* 23 */
#define PX_UART2_RX             PA3    /* 24 */
#define PX_UART4_TX             PC10   /* 25 */
#define PX_UART4_RX             PC11   /* 26 */
#define PX_I2C1_SCL             PB8    /* 27 */
#define PX_I2C1_SDA             PB9    /* 28 */
#define PX_SPI1_CS              PB6    /* 29 */
#define PX_SPI1_SCK             PB3    /* 30 */
#define PX_SPI1_MOSI            PB5    /* 31 */
#define PX_SPI1_MISO            PB4    /* 32 */
#define PX_SPI2_CS_SF           PB2    /* 33 */
#define PX_SPI2_CS_LCD          PB10   /* 34 */
#define PX_SPI2_CS_SD           PD2    /* 35 */
#define PX_SPI2_SCK             PB13   /* 36 */
#define PX_SPI2_MOSI            PB15   /* 37 */
#define PX_SPI2_MISO            PB14   /* 38 */
#define PX_DAC1                 PA4    /* 39 */
#define PX_ADC0                 PB0    /* 40 */
#define PX_ADC1                 PC5    /* 41 */
#define PX_ADC2                 PC4    /* 42 */
#define PX_ADC3                 PA7    /* 43 */
#define PX_ADC_VBAT             PB1    /* 44 */

// This must be a literal
#define NUM_DIGITAL_PINS        45

// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_FIRST        PB0
#define NUM_ANALOG_INPUTS       5

// On-board LED pin number
#define LED_RED                 PH0
#define LED_BUILTIN             PH0

// On-board user button
#define USER_BTN                PA15

// SPI Definitions
#define PIN_SPI_SS              PB6
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
#define PIN_WIRE_SCL            PB8
#define PIN_WIRE_SDA            PB9

// I2C timing definitions (optional), avoid time spent to compute if defined
// * I2C_TIMING_SM for Standard Mode (100kHz)
// * I2C_TIMING_FM for Fast Mode (400kHz)
// * I2C_TIMING_FMP for Fast Mode Plus (1000kHz)
#define I2C_TIMING_SM           0x20302e37
//#define I2C_TIMING_FM           0x00000000
//#define I2C_TIMING_FMP          0x00000000

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //ex: 2 for Serial2 (USART2)

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

// Optional PIN_SERIALn_RX and PIN_SERIALn_TX where 'n' is the U(S)ART number
// Used when user instanciate a hardware Serial using its peripheral name.
// Example: HardwareSerial mySerial(USART3);
// will use PIN_SERIAL3_RX and PIN_SERIAL3_TX if defined.
#define PIN_SERIAL1_TX          PA9
#define PIN_SERIAL1_RX          PA10
#define PIN_SERIAL2_TX          PA2
#define PIN_SERIAL2_RX          PA3
#define PIN_SERIAL4_TX          PC10
#define PIN_SERIAL4_RX          PC11
#define PIN_SERIALLP1_TX        PA2
#define PIN_SERIALLP1_RX        PA3

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
