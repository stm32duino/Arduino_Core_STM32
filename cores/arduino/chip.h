/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _CHIP_H_
#define _CHIP_H_

/*
 * Core and peripherals registers definitions
 */
#include "hw_config.h"
#include "digital_io.h"
#include "clock.h"
#include "hal_uart_emul.h"
#include "uart.h"
#include "uart_emul.h"
#include "analog.h"
#include "interrupt.h"
#include "spi_com.h"
#include "timer.h"
#include "twi.h"
#include "stm32_eeprom.h"
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

/*
 * Peripherals
 */


#endif /* _CHIP_H_ */
