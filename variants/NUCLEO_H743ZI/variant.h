#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
extern const PinName digitalPin[];

#define PG9  0  // USART_A_RX
#define PG14 1  // USART_A_TX
#define PF15 2
#define PE13 3  // TIMER_A_PWM3
#define PF14 4  // A11
#define PE11 5  // TIMER_A_PWM2
#define PE9  6  // TIMER_A_PWM1
#define PF13 7  // A12
#define PF12 8  // A13
#define PD15 9  // TIMER_B_PWM2
#define PD14 10 // SPI_A_CS/ TIM_B_PWM3
#define PA7  11 // SPI_A_MOSI/If JP6 ON used also for Ethernet PHY as RMII_DV - A14
#define PA6  12 // SPI_A_MISO - A15
#define PA5  13 // SPI_A_SCK - A16
#define PB9  14 // I2C_A_SDA
#define PB8  15 // I2C_A_SCL
#define PC6  16 // I2S_A_MCK
#define PB15 17 // I2S_A_SD
#define PB13 18 // I2S_A_CK/If JP7 ON used also for Ethernet PHY as RMII_TXD1
#define PB12 19 // I2S_A_WS
#define PA15 20 // I2S_B_WS
#define PC7  21 // I2S_B_MCK
#define PB5  22 // I2S_B_SD/SPI_B_MOSI
#define PB3  23 // I2S_B_CK/SPI_B_SCK - SWO
#define PA4  24 // SPI_B_NSS - A17
#define PB4  25 // SPI_B_MISO
#define PB6  26 // QSPI_CS
#define PB2  27 // QSPI_CLK
#define PD13 28 // QSPI_BK1_IO3
#define PD12 29 // QSPI_BK1_IO1
#define PD11 30 // QSPI_BK1_IO0
#define PE2  31 // SAI_A_MCLK/QSPI_BK1_IO2
#define PA0  32 // TIMER_C_PWM1 - A18
#define PB0  33 // TIMER_D_PWM1 - LD1 LED_GREEN
#define PE0  34 // TIMER_B_ETR
#define PB11 35 // TIMER_C_PWM3
#define PB10 36 // TIMER_C_PWM2
#define PE15 37 // TIMER_A_BKIN1
#define PE14 38
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
#define PE6  59 // SAI_A_SD
#define PE3  60 // SAI_B_SD
#define PF8  61 // SAI_B_SCK - A19
#define PF7  62 // SAI_B_MCLK - A20
#define PF9  63 // SAI_B_FS - A21
#define PG1  64
#define PG0  65
#define PD1  66 // CAN_TX
#define PD0  67 // CAN_RX
#define PF0  68 // I2C_B_SDA
#define PF1  69 // I2C_B_SCL
#define PF2  70 // I2C_B_SMBA
// 71 is PA7 (11)
// 72 is NC
#define PB7  73 // LD2 LED_BLUE
#define PB14 74 // LD3 LED_RED
#define PC13 75 // USER_BTN
#define PD9  76 // Serial Rx
#define PD8  77 // Serial Tx
#define PD10 78
#define PE1  79
#define PG4  80
#define PG5  81
#define PG8  82
#define PG10 83
#define PG12 84
#define PG15 85
#define PA3  86 // A0
#define PC0  87 // A1
#define PC3  88 // A2
#define PF3  89 // A3
#define PF5  90 // A4
#define PF10 91 // A5
#define PB1  92 // A6
#define PC2  93 // A7
#define PF4  94 // A8
#define PF6  95 // A9
#define PF11 96 // A10

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        108
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       22
#define NUM_ANALOG_FIRST        86

// On-board LED pin number
#define LED_BUILTIN             PB0  // LD1
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB7  // LD2
#define LED_RED                 PB14 // LD3

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM12

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    3 //Connected to ST-Link

// Serial pin used for console (ex: ST-Link)
// Required by Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

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
