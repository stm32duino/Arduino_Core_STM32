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

void init( void ) ;

#endif /* _BOARD_H_ */
