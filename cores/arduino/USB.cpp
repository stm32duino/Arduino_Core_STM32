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

#ifdef USBCON

#include "usbd_desc.h"
#include "USB.h"
#include "wiring.h"

#ifdef USBD_USE_CDC_CLASS
  #include "usbd_cdc.h"
  #include "usbd_cdc_msc.h"
  #include "usbd_cdc_if.h"
#endif

#ifdef USBD_USE_MSC_CLASS
  #include "usbd_msc.h"
  #include "usbd_msc_storage_if.h"
#endif

USB USBDevice;

void USB::begin()
{
  if (!initialized) {
    initialize();
  }
}

#ifdef USBD_USE_MSC_CLASS
DummyUSBMscHandler dummyHandler;

void USB::registerMscHandler(USBMscHandler &handler)
{
  pSingleMscHandler = &handler;
  registerMscHandlers(1, &pSingleMscHandler, USBD_MSC_fops.pInquiry);
}

void USB::registerMscHandlers(uint8_t count, USBMscHandler **ppHandlers, uint8_t *pInquiryData)
{
  if (count == 0) {
    registerMscHandler(dummyHandler);
  } else {
    ppUsbMscHandlers = ppHandlers;
    usbMscMaxLun = count - 1;
    USBD_MSC_fops.pInquiry = pInquiryData;
  }
}
#endif

void USB::initialize()
{
  hUSBD_Device_CDC = &hUSBD_Device;


  /* Init Device Library */
  if (USBD_Init(&hUSBD_Device, &USBD_Desc, 0) != USBD_OK) {
    return;
  }

  /* Add Supported Class and register interface */
#ifdef USBD_USE_CDC
  if (USBD_RegisterClass(&hUSBD_Device, &USBD_CDC) != USBD_OK) {
    return;
  }
#elif USBD_USE_CDC_MSC
  if (USBD_RegisterClass(&hUSBD_Device, &USBD_CDC_MSC) != USBD_OK) {
    return;
  }
#elif USBD_USE_MSC
  if (USBD_RegisterClass(&hUSBD_Device, &USBD_CDC_MSC) != USBD_OK) {
    return;
  }
#endif

#ifdef USBD_USE_CDC_CLASS
  hUSBD_Device_CDC = &hUSBD_Device;
  if (USBD_CDC_RegisterInterface(&hUSBD_Device, &USBD_CDC_fops) != USBD_OK) {
    return;
  }
#endif

#ifdef USBD_USE_MSC_CLASS
  if (ppUsbMscHandlers == nullptr) {
    registerMscHandler(dummyHandler);
  }
  if (USBD_MSC_RegisterStorage(&hUSBD_Device, &USBD_MSC_fops) != USBD_OK) {
    return;
  }
#endif

  /* Start Device Process */
  USBD_Start(&hUSBD_Device);
  initialized = true;
}

void USB::end()
{
  if (initialized) {
    deinitialize();
  }
}

void USB::deinitialize()
{
  USBD_Stop(&hUSBD_Device);
  USBD_DeInit(&hUSBD_Device);
  initialized = false;
}

#endif // USBCON
