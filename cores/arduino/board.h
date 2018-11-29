#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Core and peripherals registers definitions
*/
#include "interrupt.h"
#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
#include "analog.h"
#include "clock.h"
#include "core_callback.h"
#include "digital_io.h"
#include "hw_config.h"
#include "low_power.h"
#include "rtc.h"
#include "spi_com.h"
#include "stm32_eeprom.h"
#include "timer.h"
#include "twi.h"
#include "uart.h"
#ifdef USBCON
#if !defined(USB_BASE) && !defined(USB_OTG_DEVICE_BASE)
#error "This board does not support USB! Select 'None' in the 'Tools->USB interface' menu"
#endif
#if defined(USE_USB_HS) && !defined(USB_OTG_HS)
#error "This board does not support USB High Speed! Select 'Full Speed' in the 'Tools->USB interface' menu"
#endif
#include "usb_interface.h"
#endif /* USBCON */

void init( void ) ;
#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* _BOARD_H_ */
