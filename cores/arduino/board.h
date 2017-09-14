#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Core and peripherals registers definitions
 */
#include "analog.h"
#include "clock.h"
#include "core_callback.h"
#include "digital_io.h"
#include "hal_uart_emul.h"
#include "hw_config.h"
#include "interrupt.h"
#include "spi_com.h"
#include "stm32_eeprom.h"
#include "timer.h"
#include "twi.h"
#include "uart.h"
#include "uart_emul.h"
#ifdef USBCON
#include "usb_interface.h"
#endif //USBCON

/* Define attribute */
#if defined (  __GNUC__  ) /* GCC CS3 */
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
    #define WEAK __weak
#endif

/* Define NO_INIT attribute */
#if defined (  __GNUC__  )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#endif

void init( void ) ;

#endif /* _BOARD_H_ */
