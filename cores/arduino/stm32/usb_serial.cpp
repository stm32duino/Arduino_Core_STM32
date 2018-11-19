/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2018 MCCI Corporation
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @brief USB virtual serial terminal
 */

/*
 * Arduino srl - www.arduino.org
 */

#ifdef USBCON

#include <string.h>

#include "wiring.h"
#include "usb_serial.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_desc.h"
#include "usbd_cdc_if.h"

/* USB Device Core handle declaration */
USBD_HandleTypeDef hUSBD_Device_CDC;

USBSerial SerialUSB;


USBSerial::USBSerial(void)
{
  m_Started = false;
}

/* USBSerial is always available and instantiated in main.cpp */
void USBSerial::begin(void)
{
  if (m_Started || ! USBD_LL_ConnectionState())
    return;

  if (USBD_Init(&hUSBD_Device_CDC, &CDC_Desc, DEVICE_FS) == USBD_OK)
  {

    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK)
    {

      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_Interface_fops_FS) == USBD_OK)
      {

        /* Start Device Process */
        USBD_Start(&hUSBD_Device_CDC);
        m_Started = true;
      }
    }
  }
}

void USBSerial::end(void)
{
  if (m_Started)
  {
    m_Started = false;
    USBD_DeInit(&hUSBD_Device_CDC);
  }
}

int USBSerial::availableForWrite(void)
{
  return CDC_AvailableForWrite();
}

size_t USBSerial::write(uint8_t ch)
{
  if (hUSBD_Device_CDC.pClassData)
    return CDC_Write(&ch, 1);

  m_Started = false;
  return 1;
}

size_t USBSerial::write(const uint8_t *buffer, size_t size)
{
  if (hUSBD_Device_CDC.pClassData)
    return CDC_Write(buffer, size);

  m_Started = false;
  return size;
}

int USBSerial::available(void)
{
  return CDC_AvailableForRead();
}

int USBSerial::read(void)
{
  if (hUSBD_Device_CDC.pClassData)
    return CDC_Read();

  m_Started = false;
  return -1;
}

int USBSerial::peek(void)
{
  if (hUSBD_Device_CDC.pClassData)
    return CDC_Peek();

  m_Started = false;
  return -1;
}

void USBSerial::flush(void)
{
  if (hUSBD_Device_CDC.pClassData)
    CDC_Flush();
}

bool USBSerial::dtr(void)
{
  uint32_t LineState = CDC_LineState();

  if (LineState == 0)
    begin();

  return LineState & 1;
}

bool USBSerial::rts(void)
{
  uint32_t LineState = CDC_LineState();

  if (LineState == 0)
    begin();

  return (LineState & 2) >> 1;
}

bool USBSerial::isConnected(void)
{
  return USBD_LL_ConnectionState();
}

USBSerial::operator bool()
{
  bool result = false;
  uint32_t LineState = CDC_LineState();

  if (LineState == 0)
    begin();

  if (LineState & 1)
    result = true;

  return result;
}

#endif /* USBCON */
