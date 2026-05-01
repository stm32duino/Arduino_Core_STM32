/*
 * USBEP.h
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#pragma once

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

  #include "USBOptions.h"

  #define MAX_USB_EP_SIZE 64

  #if defined(USB_OTG_FS)
    #define USB_MAX_EPS 3
  #else
    #define USB_MAX_EPS 7
  #endif
  #define USB_MAX_EPS_SLOTS (USB_MAX_EPS - 1)

  #define USB_ENDPOINT_DIRECTION_MASK 0x80
  #define USB_ENDPOINT_OUT(addr)      (lowByte((addr) | 0x00))
  #define USB_ENDPOINT_IN(addr)       (lowByte((addr) | 0x80))

  #define USB_ENDPOINT_TYPE_MASK        0x03
  #define USB_ENDPOINT_TYPE_CONTROL     0x00
  #define USB_ENDPOINT_TYPE_ISOCHRONOUS 0x01
  #define USB_ENDPOINT_TYPE_BULK        0x02
  #define USB_ENDPOINT_TYPE_INTERRUPT   0x03

#endif
