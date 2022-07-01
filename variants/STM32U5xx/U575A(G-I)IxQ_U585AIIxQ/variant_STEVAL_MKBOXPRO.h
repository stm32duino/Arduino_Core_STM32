/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
// Sensor Bus
#define PI0                     0       // MCU_SEL SPI/I2C mux switch digital
#define PB6                     1       // I2C1_SCL --> SCL
#define PB7                     2       // I2C1_SDA --> SDA
#define PI1                     3       // SPI2_SCK --> SPI
#define PI2                     4       // SPI2_MISO --> SPI
#define PI3                     5       // SPI2_MOSI --> SPI
#define PI7                     6       // SPI_Sen_CS_A
#define PI5                     7       // SPI_Sen_CS_G
#define PE9                     8       // MIC_ADF_CK
#define PE10                    9       // MIC_ADF_SD

// Sensor interrupt
#define PE6                     10      // MAG_DRDY
#define PB15                    11      // TEMP_INT
#define PE11                    12      // HUM_DRDY
#define PF2                     13      // ACC_INT2
#define PF15                    14      // ACC_INT2
#define PA4                     15      // IMU_INT1
#define PD11                    16      // IMU_INT2
#define PE8                     17      // PRESS_INT

// MICs
#define PE4                     18      // MDF1_SDI3
#define PE7                     19      // MDF1_SDI2
#define PB12                    20      // MDF1_SDI1
#define PD3                     21      // MDF1_SDI0
#define PF10                    22      // MDF1_CCK
#define PA10                    23      // SAI_SD
#define PE2                     24      // SAI_MCLK
#define PA3                     25      // SAI_MCK
#define PA8                     26      // SAI_SCK
#define PA9                     27      // SAI_FS

// SD_CARD
#define PC5                     28      // SD_DETECT
#define PC6                     29      // SD_DATA0dir
#define PC7                     30      // SD_DATA123dir
#define PC8                     31      // SD_DATA0
#define PC9                     32      // SD_DATA1
#define PC10                    33      // SD_DATA2
#define PC11                    34      // SD_DATA3
#define PC12                    35      // SD_CLK
#define PD2                     36      // SD_CMD
#define PB8                     37      // SD_CLK_f
#define PB9                     38      // SD_CMDdir
#define PH8                     39      // SEL_SD_V
#define PH10                    40      // EN_SD

// DIL24_DUT
#define PC0                     PIN_A0  // LOCK_1v8
#define PG3                     42      // DIL_GP
#define PG4                     43      // DIL_DEN
#define PG10                    44      // SPI_dut_MISO (SPI3)
#define PB5                     45      // SPI_dut_MOSI (SPI3) - interconnected with PG8
#define PG9                     46      // SPI_dut_CK (SPI3) - interconnected with PG7
#define PG1                     47      // SPI_dut_CS
#define PG12                    48      // SPI_dut_CS2
#define PG6                     49      // DIL_INT2
#define PG2                     50      // DIL_INT1
#define PG15                    51      // DIL_INT4
#define PG0                     52      // DIL_INT3
#define PG7                     53      // I2C3_SCL - interconnected with PG9
#define PG8                     54      // I2C3_SDA - interconnected with PB5

// LED and buttons
#define PF6                     55      // LED1 green
#define PH11                    56      // LED2 red (BLE shared)
#define PH12                    57      // LED3 yellow
#define PF9                     58      // LED USB enum
#define PC13                    59      // SW1 (BLE shared)
#define PE0                     60      // SW2 interconnect with PH3
#define PH3                     61      // SW2 (Boot0)
#define PB10                    62      // CH_BAT_LED

// JP4 connector
#define PE5                     63      // GPIO_JP4

// Speaker1
#define PE13                    64

// BT
#define PB1                     PIN_A1  // GPIO_0_BT
#define PB11                    66      // GPIO_1_BT
#define PE1                     67      // V_BT_EN
#define PD1                     68      // BT_BOOT
#define PD4                     69      // BT_NRST
#define PA2                     70      // BT_SPI_NSS (SPI1 RDY)
#define PA5                     71      // BT_SPI_CLK (SPI1)
#define PA6                     72      // BT_SPI_MISO (SPI1)
#define PA7                     73      // BT_SPI_MOSI (SPI1)
#define PD5                     74      // BT_USART_TX (USART2)
#define PD6                     75      // BT_USART_RX (USART2)

// NFC
#define PE12                    76      // NFC_GPIO
#define PB13                    77      // I2C_SCL
#define PB14                    78      // I2C_SDA

// USB
#define PA11                    79      // USB DM
#define PA12                    80      // USB DP
#define PF4                     81      // PU USB DP (useless as internal PU available)

// Power
#define PB0                     PIN_A2  // Vbatt_sens/3
#define PC4                     PIN_A3  // Vbatt_test
#define PC1                     PIN_A4  // PW_BT
#define PF8                     85      // SW_ON
#define PF0                     86      // VusbP
// LDFM LDO
#define PI6                     87      // V4_GOOD
#define PC3                     88      // V4_EN

// Wireless CH
#define PF7                     89      // WC_RSTB
#define PE3                     90      // WC_INTB
#define PD12                    91      // I2C4_SCL (also on Prog connector)
#define PD13                    92      // I2C4_SDA (also on Prog connector)

// Prog connector
#define PA0                     93      // UART4_TX
#define PA1                     94      // UART4_RX
#define PA13                    95      // JTMS_SWDIO
#define PA14                    96      // JTCL_SWCLK
#define PA15                    97      // JTDI
#define PB3                     98      // JTDO
#define PB4                     99      // JTNRST

// Oscillators
#define PC14                    100     // OSC32_IN
#define PC15                    101     // OSC32_OUT
#define PH0                     102     // OSC_IN
#define PH1                     103     // OSC_OUT

// Not connected
// #define PB2                     PIN_Axx
// #define PC2                     PIN_Axx
// #define PD0                     x
// #define PD7                     x
// #define PD8                     x
// #define PD9                     x
// #define PD10                    x
// #define PD14                    x
// #define PD15                    x
// #define PE14                    x
// #define PE15                    x
// #define PF1                     x
// #define PF3                     x
// #define PF5                     x
// #define PF11                    x
// #define PF12                    x
// #define PF13                    x
// #define PF14                    PIN_Ax
// #define PG5                     x
// #define PH2                     x
// #define PH4                     x
// #define PH5                     x
// #define PH6                     x
// #define PH7                     x
// #define PH9                     x
// #define PH13                    x
// #define PH14                    x
// #define PH15                    x
// #define PI4                     x

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
// #define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC6_ALT2                (PC6  | ALT2)
#define PC7_ALT1                (PC7  | ALT1)
#define PC7_ALT2                (PC7  | ALT2)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF9_ALT1                (PF9  | ALT1)
#define PH12_ALT1               (PH12 | ALT1)

#define NUM_DIGITAL_PINS        104
#define NUM_ANALOG_INPUTS       5

// On-board LED pin number
#define LED1                    PF6
#define LED2                    PH11
#define LED3                    PH12
#define LED_USB                 PF9
#define LED_GREEN               LED1
#define LED_RED                 LED2
#define LED_YELLOW              LED3
#define LED_BLUE                LED_USB
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif

// On-board user button
#define SW1_BTN                 PC13
#ifndef USER_BTN
  #define USER_BTN              SW1_BTN
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  4
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA1
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA0
#endif

/* Set default Wire instance on I2C1 Sensor Bus */
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

/* Set default SPI instance on SPI2 */
#define PIN_SPI_MOSI            PI3
#define PIN_SPI_MISO            PI2
#define PIN_SPI_SCK             PI1
#define PIN_SPI_SS              PI7 // SPI_Sen_CS_A
#define PIN_SPI_SS1             PI5 // SPI_Sen_CS_G

/* SD detect signal */
#define SD_DETECT_PIN           PC5
/* SD Transceiver */
#define USE_SD_TRANSCEIVER      1U
#define SD_TRANSCEIVER_EN       PH10
#define SD_TRANSCEIVER_SEL      PH8

// Extra HAL modules
// #if !defined(HAL_DAC_MODULE_DISABLED)
//   #define HAL_DAC_MODULE_ENABLED
// #endif
// #if !defined(HAL_OSPI_MODULE_DISABLED)
//   #define HAL_OSPI_MODULE_ENABLED
// #endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif

#if !defined(HAL_MDF_MODULE_DISABLED)
  #define HAL_MDF_MODULE_ENABLED
#endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN1_2
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN2_2
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN3_2
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN4_2
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN5_2
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN6_2
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN7_2
#define PWR_WAKEUP_PIN8_1
#define PWR_WAKEUP_PIN8_2

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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
