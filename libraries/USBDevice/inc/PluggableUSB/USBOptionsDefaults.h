/*
 * USBOptionsDefaults.h
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#pragma once

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

  #include <stm32_def.h>

  // These defaults are for values that depend on a certain board

  #if defined(USB)
    #define PACKETBUFFER_COUNT_DEFAULT 3
  #elif defined(USB_OTG_FS)
    #define PACKETBUFFER_COUNT_DEFAULT 2
  #endif

  #if defined(USB)
    #define PACKETBUFFER_ALLOW_OVERWRITE_DEFAULT true
  #elif defined(USB_OTG_FS)
    #define PACKETBUFFER_ALLOW_OVERWRITE_DEFAULT false
  #endif

#endif
