/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
    * Modified by Levi Gillis @ 2022-2025
      Changes can be found in the git repo https://github.com/Levi--G/USBLibrarySTM32

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

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "USBCDC.h"
#include "USBAPI.h"
#include <Arduino.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// #include "core_cm3.h"

#define CDC_SERIAL_BUFFER_SIZE 256

/* For information purpose only since RTS is not always handled by the terminal application */
#define CDC_LINESTATE_DTR 0x01 // Data Terminal Ready
#define CDC_LINESTATE_RTS 0x02 // Ready to Send

#define CDC_LINESTATE_READY (CDC_LINESTATE_RTS | CDC_LINESTATE_DTR)

typedef struct {
  uint32_t dwDTERate;
  uint8_t bCharFormat;
  uint8_t bParityType;
  uint8_t bDataBits;
  uint8_t lineState;
} LineInfo;

static volatile LineInfo _usbLineInfo = {
  115200, // dWDTERate
  0x00,   // bCharFormat
  0x00,   // bParityType
  0x08,   // bDataBits
  0x00    // lineState
};

static volatile int32_t breakValue = -1;

// CDC
#define CDC_ACM_INTERFACE  pluggedInterface              // CDC ACM
#define CDC_DATA_INTERFACE uint8_t(pluggedInterface + 1) // CDC Data

#if USB_SERIAL_USE_ACM_EP
  #define CDC_ENDPOINT_ACM pluggedEndpoint + 2
#endif
#define CDC_ENDPOINT_OUT pluggedEndpoint + 1
#define CDC_ENDPOINT_IN  pluggedEndpoint

#define CDC_RX CDC_ENDPOINT_OUT
#define CDC_TX CDC_ENDPOINT_IN

int USBCDC::getInterface(uint8_t *interfaceNum)
{
  interfaceNum[0] += 2; // uses 2
  CDCDescriptor _cdcInterface = {
    D_IAD(pluggedInterface, 2, CDC_COMMUNICATION_INTERFACE_CLASS, CDC_ABSTRACT_CONTROL_MODEL, 0),

    // CDC communication interface
#if USB_SERIAL_USE_ACM_EP
    D_INTERFACE(CDC_ACM_INTERFACE, 1, CDC_COMMUNICATION_INTERFACE_CLASS, CDC_ABSTRACT_CONTROL_MODEL, 0),
#else
    D_INTERFACE(CDC_ACM_INTERFACE, 0, CDC_COMMUNICATION_INTERFACE_CLASS, CDC_ABSTRACT_CONTROL_MODEL, 0),
#endif
    D_CDCCS(CDC_HEADER, CDC_V1_10 & 0xFF, (CDC_V1_10 >> 8) & 0x0FF), // Header (1.10 bcd)

    D_CDCCS4(CDC_ABSTRACT_CONTROL_MANAGEMENT, 6),                    // SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE supported
    D_CDCCS(CDC_UNION, CDC_ACM_INTERFACE, CDC_DATA_INTERFACE),       // Communication interface is master, data interface is slave 0
    D_CDCCS(CDC_CALL_MANAGEMENT, 1, 1),                              // Device handles call management (not)
#if USB_SERIAL_USE_ACM_EP
    D_ENDPOINT(USB_ENDPOINT_IN(CDC_ENDPOINT_ACM), USB_ENDPOINT_TYPE_INTERRUPT, 0x10, 0x10),
#endif
    // CDC data interface
    D_INTERFACE(CDC_DATA_INTERFACE, 2, CDC_DATA_INTERFACE_CLASS, 0, 0),
    D_ENDPOINT(USB_ENDPOINT_OUT(CDC_ENDPOINT_OUT), USB_ENDPOINT_TYPE_BULK, EPX_SIZE, 0),
    D_ENDPOINT(USB_ENDPOINT_IN(CDC_ENDPOINT_IN), USB_ENDPOINT_TYPE_BULK, EPX_SIZE, 0)
  };

  return USB_SendControl(0, &_cdcInterface, sizeof(_cdcInterface));
}

int USBCDC::getDescriptor(USBSetup & /* setup */)
{
  return 0;
}

static void utox8(uint32_t val, char *s)
{
  for (int i = 0; i < 8; i++) {
    int d = val & 0XF;
    val = (val >> 4);

    s[7 - i] = d > 9 ? 'A' + d - 10 : '0' + d;
  }
}

uint8_t USBCDC::getShortName(char *name)
{
  // from section 9.3.3 of the datasheet
#define SERIAL_NUMBER_WORD_0 *(volatile uint32_t *)(0x0080A00C)
#define SERIAL_NUMBER_WORD_1 *(volatile uint32_t *)(0x0080A040)
#define SERIAL_NUMBER_WORD_2 *(volatile uint32_t *)(0x0080A044)
#define SERIAL_NUMBER_WORD_3 *(volatile uint32_t *)(0x0080A048)

  utox8(SERIAL_NUMBER_WORD_0, &name[0]);
  utox8(SERIAL_NUMBER_WORD_1, &name[8]);
  utox8(SERIAL_NUMBER_WORD_2, &name[16]);
  utox8(SERIAL_NUMBER_WORD_3, &name[24]);
  return 32;
}

void USBCDC::handleEndpoint(int /* ep */)
{
}

bool USBCDC::setup(USBSetup &setup)
{
  uint8_t requestType = setup.bmRequestType;
  uint8_t r = setup.bRequest;
  uint8_t i = setup.wIndex;

  if (CDC_ACM_INTERFACE != i) {
    return false;
  }

  if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE) {
    if (r == CDC_GET_LINE_CODING) {
      USB_SendControl(0, (void *)&_usbLineInfo, 7);
      return true;
    }
  }

  if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE) {

    if (r == CDC_SET_LINE_CODING) {
      USB_RecvControl((void *)&_usbLineInfo, 7);
    }

    if (r == CDC_SET_CONTROL_LINE_STATE) {
      _usbLineInfo.lineState = setup.wValueL;
    }

    if (r == CDC_SET_LINE_CODING || r == CDC_SET_CONTROL_LINE_STATE) {
      // TODO reset
      //    NVIC_SystemReset();
      //  USB_SendZLP(0);
    }

    if (CDC_SEND_BREAK == r) {
      breakValue = ((uint16_t)setup.wValueH << 8) | setup.wValueL;
      USB_SendZLP(0);
    }
    return true;
  }
  return false;
}

USBCDC::USBCDC() : PluggableUSBModule(2, 2, epType), stalled(false)
{
  epType[0] = USB_ENDPOINT_TYPE_BULK | USB_ENDPOINT_IN(0);
  epType[1] = USB_ENDPOINT_TYPE_BULK | USB_ENDPOINT_OUT(0);
#if USB_SERIAL_USE_ACM_EP
  epType[2] = USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_IN(0);
#endif
  PluggableUSB().plug(this);
}

void USBCDC::begin(uint32_t /* baud_count */)
{
  // uart config is ignored in USB-CDC
}

void USBCDC::begin(uint32_t /* baud_count */, uint8_t /* config */)
{
  // uart config is ignored in USB-CDC
}

void USBCDC::end(void)
{
  memset((void *)&_usbLineInfo, 0, sizeof(_usbLineInfo));
}

int _serialPeek = -1;

int USBCDC::available(void)
{
  return USB_Available(CDC_ENDPOINT_OUT) + (_serialPeek != -1);
}

int USBCDC::availableForWrite(void)
{
  return USB_SendAvailable(CDC_ENDPOINT_OUT) ? USB_EP_SIZE : 0;
}

int USBCDC::peek(void)
{
  if (_serialPeek != -1) {
    return _serialPeek;
  }
  _serialPeek = read();
  return _serialPeek;
}

int USBCDC::read(void)
{
  if (_serialPeek != -1) {
    int res = _serialPeek;
    _serialPeek = -1;
    return res;
  }
  return USB_Recv(CDC_ENDPOINT_OUT);
}

size_t USBCDC::readBytes(char *buffer, size_t length)
{
  size_t count = 0;
  _startMillis = millis();
  while (count < length) {
    uint32_t n = USB_Recv(CDC_ENDPOINT_OUT, buffer + count, length - count);
    if (n == 0 && (millis() - _startMillis) >= _timeout) {
      break;
    }
    count += n;
  }
  return count;
}

void USBCDC::flush(void)
{
  USB_Flush(CDC_ENDPOINT_IN);
}

size_t USBCDC::write(const uint8_t *buffer, size_t size)
{
  uint32_t r = USB_Send(CDC_ENDPOINT_IN, buffer, size);

  if (r > 0) {
    return r;
  } else {
    setWriteError();
    return 0;
  }
}

size_t USBCDC::write(uint8_t c)
{
  return write(&c, 1);
}

// This operator is a convenient way for a sketch to check whether the
// port has actually been configured and opened by the host (as opposed
// to just being connected to the host).  It can be used, for example, in
// setup() before printing to ensure that an application on the host is
// actually ready to receive and display the data.
// We add a short delay before returning to fix a bug observed by Federico
// where the port is configured (lineState != 0) but not quite opened.
USBCDC::operator bool()
{
  // this is here to avoid spurious opening after upload
  if (millis() < 500) {
    return false;
  }

  bool result = false;

  if (_usbLineInfo.lineState > 0) {
    result = true;
  }

  delay(10);
  return result;
}

int32_t USBCDC::readBreak()
{
  uint8_t enableInterrupts = ((__get_PRIMASK() & 0x1) == 0);

  // disable interrupts,
  // to avoid clearing a breakValue that might occur
  // while processing the current break value
  __disable_irq();

  int32_t ret = breakValue;

  breakValue = -1;

  if (enableInterrupts) {
    // re-enable the interrupts
    __enable_irq();
  }

  return ret;
}

unsigned long USBCDC::baud()
{
  return _usbLineInfo.dwDTERate;
}

uint8_t USBCDC::stopbits()
{
  return _usbLineInfo.bCharFormat;
}

uint8_t USBCDC::paritytype()
{
  return _usbLineInfo.bParityType;
}

uint8_t USBCDC::numbits()
{
  return _usbLineInfo.bDataBits;
}

bool USBCDC::dtr()
{
  return ((_usbLineInfo.lineState & CDC_LINESTATE_DTR) == CDC_LINESTATE_DTR);
}

bool USBCDC::rts()
{
  return ((_usbLineInfo.lineState & CDC_LINESTATE_RTS) == CDC_LINESTATE_RTS);
}

#endif /* USBCON */
