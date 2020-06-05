#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#define PB12 0
#define PC11 1
#define PC10 2
#define PC9  3
#define PC8  4
#define PD2  5
#define PC12 6
#define PG10 7
#define PG11 8
#define PB4  9
#define PB5  10
#define PB8  11
#define PB9  12
#define PB6  13
#define PB7  14
#define PC0  A0
#define PA3  A1
#define PB1  A2
#define PA7  A3
#define PA6  A4
#define PC1  A5
#define PC4  A6
#define PA5  A7
#define PA4  A8
#define PA1  A9
#define PA0  A10
#define PD11 26
#define PG9  27
#define PA2  A11
#define PB14 29
#define PB15 30
#define PC7  31 // LED_BUILTIN

// This must be a literal
#define NUM_DIGITAL_PINS        32
// This must be a literal
#define NUM_ANALOG_INPUTS       12

// On-board LED pin number
#define LED_BUILTIN             PC7
#define LED_RED                 LED_BUILTIN

// SPI Definitions
#define PIN_SPI_SS              PG10
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PG11

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// I2C timing definitions (optional), avoid time spent to compute if defined
#define I2C_TIMING_SM           0x30E0628A
#define I2C_TIMING_FM           0x20D01132
#define I2C_TIMING_FMP          0x1080091A

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Serial pin used for console
// Required by Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

// HSE is 16MHz on Daisy Seed.
#define HSE_VALUE 16000000

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
  #define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
