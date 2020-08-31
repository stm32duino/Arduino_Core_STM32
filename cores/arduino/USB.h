/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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

#ifndef _USB_H_
#define _USB_H_

#ifdef USBCON

#include "usbd_core.h"
#include "usbd_ep_conf.h"

#ifdef USBD_USE_MSC_CLASS
  #include "USBMscHandler.h"
#endif

class USB {
  public:
#ifdef USBD_USE_MSC_CLASS
    void registerMscHandler(USBMscHandler &pHandler);
    void registerMscHandlers(uint8_t count, USBMscHandler **pHandlers, uint8_t *pInquiryData);
#endif

    void begin(void);

    void end(void);

  protected:
    void initialize();
    void deinitialize();

    bool initialized;

    USBD_HandleTypeDef hUSBD_Device;

#ifdef USBD_USE_MSC_CLASS
    USBMscHandler *pSingleMscHandler;
#endif
};

extern USB USBDevice;

#endif // USBCON
#endif // _USB_H_