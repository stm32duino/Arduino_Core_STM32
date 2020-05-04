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
#define PC9 3
#define PC8 4
#define PD2 5
#define PC12 6
#define PG10 7
#define PG11 8
#define PB4 9
#define PB5 10
#define PB8 11
#define PB9 12
#define PB6 13
#define PB7 14
#define  PC0 15
#define  PA3 16
#define  PB1 17
#define  PA7 18
#define  PA6 19
#define  PC1 20
#define  PC4 21
#define  PA5 22
#define  PA4 23
#define  PA1 24
#define  PA0 25
#define  PD11 26
#define  PG9 27
#define  PA2 28
#define  PB14 29
#define  PB15 30

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        31
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       12
#define NUM_ANALOG_FIRST        15

// On-board LED pin number
#define LED_BUILTIN             PC7  
#define LED_RED                 LED_BUILTIN

// On-board user button
// #define USER_BTN                No User Button Available...

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    1 // Pins PB6, PB7

// Serial pin used for console (ex: ST-Link)
// Required by Firmata
#define PIN_SERIAL_RX           PB6
#define PIN_SERIAL_TX           PB7

// HSE default value is 25MHz in HAL
// HSE_BYPASS is 8MHz ?
  // HSE is 16MHz on Daisy Seed.
#ifndef HSE_BYPASS_NOT_USED
#define HSE_VALUE 16000000
#endif

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_QSPI_MODULE_ENABLED

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
