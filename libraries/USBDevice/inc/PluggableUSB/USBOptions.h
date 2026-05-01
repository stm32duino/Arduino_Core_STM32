/*
 * USBOptions.h
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#pragma once

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

  #include "USBOptionsDefaults.h"

  // These options can be changed by adding -D Option=value to your compiler arguments
  /*
  For PIO, in platformio.ini:
  build_flags =
  -D USBCON
  -D HAL_PCD_MODULE_ENABLED
  -D Option=value
  */

  #ifndef USB_EP0_SIZE
    // This should really stay at max size, but in theory can be lowered
    #define USB_EP0_SIZE MAX_USB_EP_SIZE
  #endif
  #ifndef USB_EP_SIZE
    // This definitions is useful if you want to reduce the EP_SIZE to save ram
    // Don't forget to also make the epsize smaller in the interface definition
    #define USB_EP_SIZE 64
  #endif

  #ifndef EP0_PACKETBUFFER_COUNT
    // This should stay at 2
    #define EP0_PACKETBUFFER_COUNT 2
  #endif

  #ifndef PACKETBUFFER_COUNT
    // Packetbuffer count determines the buffer size,
    // this can be lowered to 2 to save ram, but more missed data may occur.
    // 2 should be stable on USB_OTG_FS, 3 on USB.
    // If you have missing packets, increase the size
    #define PACKETBUFFER_COUNT PACKETBUFFER_COUNT_DEFAULT
  #endif

  #ifndef PACKETBUFFER_ALLOW_OVERWRITE
    // Allows buffers to be overwritten in case of data overload,
    // this prevents hangs but might cause data loss if polling rate is too low
    // recommended for stm32 with "classic" USB, not needed for stm32 with USB_OTF_FS
    #define PACKETBUFFER_ALLOW_OVERWRITE PACKETBUFFER_ALLOW_OVERWRITE_DEFAULT
  #endif

  #ifndef PACKETBUFFER_USE_FAST_AVAILABLE
    // Allows a faster version of available calculations,
    // some libraries might not work and not see incoming data
    #define PACKETBUFFER_USE_FAST_AVAILABLE true
  #endif

  #ifndef PACKETBUFFER_USE_TX_BUFFERS
    // Adds TX buffers that buffer sent data,
    // this prevents hangs but uses more ram
    #define PACKETBUFFER_USE_TX_BUFFERS true
  #endif

  #ifndef USB_WRITE_TIMEOUT
    // Sets a timeout for the USB_Send and USB_Flush function
    #define USB_WRITE_TIMEOUT 100
  #endif

  #ifndef USB_SERIAL_USE_ACM_EP
    // Enables the third ACM endpoint of USB serial which is in this library normally
    // disabled to use the EP for other libraries but might not be compatible with some OSses
    // or programs that might need it to be enabled
    #define USB_SERIAL_USE_ACM_EP false
  #endif

#endif
