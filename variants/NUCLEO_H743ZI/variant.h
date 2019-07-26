#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#ifdef ARDUINO_NUCLEO_H743ZI2
#define PB7  0  // USART_A_RX
#define PB6  1  // USART_A_TX
#define PG14 2
#else
#define PG9  0  // USART_A_RX
#define PG14 1  // USART_A_TX
#define PF15 2
#endif
#define PE13 3  // TIMER_A_PWM3
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PE14 4
#else
#define PF14 4
#endif
#define PE11 5  // TIMER_A_PWM2
#define PE9  6  // TIMER_A_PWM1
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PG12 7
#define PF3  8
#else
#define PF13 7
#define PF12 8
#endif
#define PD15 9  // TIMER_B_PWM2
#define PD14 10 // SPI_A_CS/ TIM_B_PWM3
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PB5  11 // SPI_A_MOSI/ PA7 if SB33 ON and SB35 OFF
#else
#define PA7  11 // SPI_A_MOSI/ Used by ETH when JP6 ON
#endif
#define PA6  12 // SPI_A_MISO
#define PA5  13 // SPI_A_SCK
#define PB9  14 // I2C_A_SDA
#define PB8  15 // I2C_A_SCL
#define PC6  16 // I2S_A_MCK
#define PB15 17 // I2S_A_SD
#define PB13 18 // I2S_A_CK / Used by ETH when JP7(ZI)/JP6(ZI2) ON
#define PB12 19 // I2S_A_WS
#define PA15 20 // I2S_B_WS
#define PC7  21 // I2S_B_MCK
#ifdef ARDUINO_NUCLEO_H743ZI2
// 22 is PB5 (11)
#else
#define PB5  22 // I2S_B_SD/SPI_B_MOSI
#endif
#define PB3  23 // I2S_B_CK/SPI_B_SCK - SWO
#define PA4  24 // SPI_B_NSS
#define PB4  25 // SPI_B_MISO
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PG6  26 // QSPI_CS
#else
#define PB6  26 // QSPI_CS
#endif
#define PB2  27 // QSPI_CLK
#define PD13 28 // QSPI_BK1_IO3
#define PD12 29 // QSPI_BK1_IO1
#define PD11 30 // QSPI_BK1_IO0
#define PE2  31 // SAI_A_MCLK/QSPI_BK1_IO2
#define PA0  32 // TIMER_C_PWM1
#define PB0  33 // TIMER_D_PWM1 - LD1 LED_GREEN
#define PE0  34 // TIMER_B_ETR
#define PB11 35 // TIMER_C_PWM3
#define PB10 36 // TIMER_C_PWM2
#define PE15 37 // TIMER_A_BKIN1
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PE6  38
#else
#define PE14 38
#endif
#define PE12 39 // TIMER_A_PWM3N
#define PE10 40 // TIMER_A_PWM2N
#define PE7  41 // TIMER_A_ETR
#define PE8  42 // TIMER_A_PWM1N
#define PC8  43 // SDMMC1_D0
#define PC9  44 // SDMMC1_D1/I2S_A_CKIN
#define PC10 45 // SDMMC1_D2
#define PC11 46 // SDMMC1_D3
#define PC12 47 // SDMMC1_CK
#define PD2  48 // SDMMC1_CMD
#define PG2  49
#define PG3  50
#define PD7  51 // USART_B_SCLK
#define PD6  52 // USART_B_RX
#define PD5  53 // USART_B_TX
#define PD4  54 // USART_B_RTS
#define PD3  55 // USART_B_CTS
// 56 is PE2 (31)
#define PE4  57 // SAI_A_FS
#define PE5  58 // SAI_A_SCK
#ifdef ARDUINO_NUCLEO_H743ZI2
// 59 is PE6 (38)
#else
#define PE6  59 // SAI_A_SD
#endif
#define PE3  60 // SAI_B_SD
#define PF8  61 // SAI_B_SCK
#define PF7  62 // SAI_B_MCLK
#define PF9  63 // SAI_B_FS
#define PG1  64
#define PG0  65
#define PD1  66 // CAN_TX
#define PD0  67 // CAN_RX
#define PF0  68 // I2C_B_SDA
#define PF1  69 // I2C_B_SCL
#define PF2  70 // I2C_B_SMBA
#ifdef ARDUINO_NUCLEO_H743ZI2
// 71 is PE9 (6)
// 72 is PB2 (27)
#define PE1  73 // LD2 LED_BLUE
#else
// 71 is PA7 (11)
// 72 is NC
#define PB7  73 // LD2 LED_BLUE
#endif
#define PB14 74 // LD3 LED_RED
#define PC13 75 // USER_BTN
#define PD9  76 // Serial Rx
#define PD8  77 // Serial Tx
#define PA3  78 // A0
#define PC0  79 // A1
#define PC3  80 // A2
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PB1  81 // A3
#define PC2  82 // A4
#else
#define PF3  81 // A3
#define PF5  82 // A4
#endif
#define PF10 83 // A5
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PF4  84 // A6
#define PF5  85 // A7
#define PF6  86 // A8
#else
#define PB1  84 // A6
#define PC2  85 // A7
#define PF4  86 // A8
#endif
#define PF11 87 // A9
#define PD10 88
#define PG4  89
#define PG5  90
#define PG8  91
#define PG10 92
#define PG15 93
#ifdef ARDUINO_NUCLEO_H743ZI2
#define PA7  94 // SPI_A_MOSI/Used by ETH when SB31 ON
#define PF12 95
#define PF13 96
#define PF14 97
#define PF15 98
#define PG9  99
#else
#define PE1  94
#define PF6  95
#define PG6  96
#define PG12 97
#endif

// This must be a literal with the same value as PEND
#ifdef ARDUINO_NUCLEO_H743ZI2
#define NUM_DIGITAL_PINS        99
#else
#define NUM_DIGITAL_PINS        97
#endif
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       10
#define NUM_ANALOG_FIRST        78

// On-board LED pin number
#define LED_BUILTIN             PB0  // LD1
#define LED_GREEN               LED_BUILTIN
#ifdef ARDUINO_NUCLEO_H743ZI2
#define LED_YELLOW              PE1  // LD2
#else
#define LED_BLUE                PB7  // LD2
#endif
#define LED_RED                 PB14 // LD3

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    3 //Connected to ST-Link

// Serial pin used for console (ex: ST-Link)
// Required by Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_ETH_MODULE_ENABLED

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
#define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
