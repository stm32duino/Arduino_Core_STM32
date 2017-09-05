/****************************************************************************
 *
 * USBSerial core library for Arduino STM32 + HAL + CubeMX (HALMX).
 *
 * Copyright (c) 2016 by Vassilis Serasidis <info@serasidis.gr>
 * Home: http://www.serasidis.gr
 * email: avrsite@yahoo.gr
 *
 * Arduino_STM32 forum: http://www.stm32duino.com
 *
 * The USBSerial.h file follows the function prototypes of
 * the Arduino CDC.h file that was written by Peter Barrett
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 *
 ****************************************************************************/

#ifndef _SERIAL_USB_H_INCLUDED
#define _SERIAL_USB_H_INCLUDED

#if defined(SERIAL_USB) && defined(USBCON)
#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

#include "RingBuffer.h"
#include "Stream.h"
#include "chip.h"


//================================================================================
//	Serial over CDC (Serial1 is the physical port)
//================================================================================
class USBSerial : public Stream{

  public:
    USBSerial();
    void begin(uint32_t baud_count);
    void begin(uint32_t baud_count, uint8_t config);
    void end(void);

    virtual int available(void);
    virtual int availableForWrite(void);
    //virtual void accept(void);
    virtual int peek(void);
    virtual int read(void);
    virtual void flush(void);
    virtual size_t write(uint8_t c);
    virtual size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) from Print
    operator bool();
    void CDC_RxHandler(uint8_t* Buf, uint16_t Len);
    void CDC_TxHandler(void);
	// These return the settings specified by the USB host for the
	// serial port. These aren't really used, but are offered here
	// in case a sketch wants to act on these settings.
    uint32_t baud();
	  uint8_t stopbits();
	  uint8_t paritytype();
	  uint8_t numbits();
    bool dtr();
    bool rts();
    enum {
      ONE_STOP_BIT = 0,
      ONE_AND_HALF_STOP_BIT = 1,
      TWO_STOP_BITS = 2,
    };
    enum {
      NO_PARITY = 0,
      ODD_PARITY = 1,
      EVEN_PARITY = 2,
      MARK_PARITY = 3,
      SPACE_PARITY = 4,
    };
  protected:
    void init(void);
    struct ring_buffer{
      uint8_t buffer[CDC_SERIAL_BUFFER_SIZE];
      volatile uint16_t iHead;
      volatile uint16_t iTail;
    };
    ring_buffer rx_buffer;
    //ring_buffer tx_buffer;
    GPIO_InitTypeDef GPIO_InitStruct;
};

#endif /* SERIAL_USB */

#endif /* _SERIAL_USB_H_INCLUDED */
