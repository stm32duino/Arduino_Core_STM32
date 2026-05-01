/*
 * USBEP_conf.h
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#pragma once

#include "USB_EP.h"
#include <stdint.h>
#include <stm32_def.h>

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#define SMALL_EP(Ep) (Ep & 0xFU)
#define IN_EP(Ep)    (lowByte((Ep) | 0x80))
#define IS_IN_EP(Ep) ((Ep & 0x80) == 0x80)

#ifndef PCD_USE_DBL_BUF
  #define PCD_USE_DBL_BUF 0
#endif

#ifndef PCD_DEF_BUF
  #if PCD_USE_DBL_BUF
    #define PCD_DEF_BUF PCD_DBL_BUF
  #else
    #define PCD_DEF_BUF PCD_SNG_BUF
  #endif
#endif

#if defined(USB_OTG_FS)
  // words not bytes
  #define USB_ABS_EP0_SIZE    (11 + ((USB_EP0_SIZE / 4) + 1) * 2)
  #define USB_ABS_EP0_TX_SIZE (USB_EP0_SIZE / 4)
  #define USB_ABS_EP_SIZE     (USB_EP_SIZE / 4)
#elif defined(USB)
  #define USB_ABS_EP0_SIZE    (PCD_USE_DBL_BUF ? USB_EP0_SIZE * 2 : USB_EP0_SIZE)
  #define USB_ABS_EP0_TX_SIZE (PCD_USE_DBL_BUF ? USB_EP0_SIZE * 2 : USB_EP0_SIZE)
  #define USB_ABS_EP_SIZE     (PCD_USE_DBL_BUF ? USB_EP_SIZE * 2 : USB_EP_SIZE)
#else
  #error "unsupported USB"
#endif

#if defined(USB_OTG_FS)
  #define PMA_MAX_SIZE 320
#elif defined(USB)
  #define PMA_BASE_ADDR (4 * 2 * USB_MAX_EPS)
  #ifndef PMA_MAX_SIZE
    #define PMA_MAX_SIZE (512 - PMA_BASE_ADDR)
  #endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
  uint32_t ep_num;  /* Endpoint number+direction */
  uint32_t ep_type; /* Endpoint type */
} ep_desc_t;

void USB_EP_ClearEndpoints();
uint8_t USB_EP_AddEndpoint(uint32_t ep_type);
uint_fast8_t USB_EP_GetNumEndpoints();
const ep_desc_t *USB_EP_GetEndpointsSlots();

#ifdef __cplusplus
}
#endif

#endif
