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

#include "USBSerial.h"

#include "cdc/usbd_cdc.h"
#include "cdc_msc/usbd_cdc_msc.h"
#include "cdc/usbd_cdc_if.h"
#include "usbd_desc.h"
#include "wiring.h"

void USB::begin() {
  if (!initialized) initialize();
}

void USB::initialize() {
  hUSBD_Device_CDC = &hUSBD_Device;

  /* Init Device Library */
  if (USBD_Init(&hUSBD_Device, &USBD_Desc, 0) == USBD_OK) {
  #ifdef USBD_USE_CDC
    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK) {
      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_CDC_fops) == USBD_OK) {
        /* Start Device Process */
        USBD_Start(&hUSBD_Device_CDC);
        initialized = true;
      }
    }
  #elif USBD_USE_CDC_MSC
    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device, USBD_CDC_MSC_CLASS) == USBD_OK) {
      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device, &USBD_CDC_fops) == USBD_OK) {
          /* Add MSC Interface Class */
        if (USBD_MSC_RegisterStorage(&hUSBD_Device, &USBD_MSC_fops) == USBD_OK) {
          /* Start Device Process */
          USBD_Start(&hUSBD_Device);
          initialized = true;
        }
      }
    }
  #endif
  }
}

void USB::end() {
  if (initialized) deinitialize();
}

void USB::deinitialize() {
  USBD_Stop(&hUSBD_Device_CDC);
  USBD_CDC_DeInit();
  USBD_DeInit(&hUSBD_Device_CDC);
  initialized = false;
}