/**
  ******************************************************************************
  * @file    usbd_ep_conf.h
  * @brief   USB Device endpoints configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_EP_CONF_H
#define __USBD_EP_CONF_H

#ifdef USBCON

#include <stdint.h>
#include "usbd_def.h"

typedef struct {
  uint32_t ep_adress; /* Endpoint address */
  uint32_t ep_size;   /* Endpoint size */
#if defined (USB)
  uint32_t ep_kind;   /* PCD Endpoint Kind: PCD_SNG_BUF or PCD_DBL_BUF */
#endif
} ep_desc_t;


/* CDC Endpoints Configurations */
#ifdef USBD_USE_CDC

  #define CDC_OUT_EP                    0x01U  /* EP1 for data OUT */
  #define CDC_IN_EP                     0x82U  /* EP1 for data IN */
  #define CDC_CMD_EP                    0x83U  /* EP2 for CDC commands */

  #define DEV_NUM_EP                    0x04U   /* Device Endpoints number including EP0 */

  /* CDC Endpoints parameters*/
  #define CDC_DATA_HS_MAX_PACKET_SIZE   USB_HS_MAX_PACKET_SIZE  /* Endpoint IN & OUT Packet size */
  #define CDC_DATA_FS_MAX_PACKET_SIZE   USB_FS_MAX_PACKET_SIZE  /* Endpoint IN & OUT Packet size */
  #define CDC_CMD_PACKET_SIZE                               8U  /* Control Endpoint Packet size */
#endif /* USBD_USE_CDC */


/* HID composite (Mouse + Keyboard) Endpoints Configurations */
#ifdef USBD_USE_HID_COMPOSITE
  #define HID_MOUSE_EPIN_ADDR           0x81U
  #define HID_KEYBOARD_EPIN_ADDR        0x82U

  #define HID_MOUSE_EPIN_SIZE           0x04U
  #define HID_KEYBOARD_EPIN_SIZE        0x08U

  #define DEV_NUM_EP                    0x03U   /* Device Endpoints number including EP0 */
#endif /* USBD_USE_HID_COMPOSITE */

/* Require DEV_NUM_EP to be defined */
#if defined (USB)
/* Size in words, byte size divided by 2 */
#define PMA_EP0_OUT_ADDR    (8 * DEV_NUM_EP)
#define PMA_EP0_IN_ADDR     (PMA_EP0_OUT_ADDR + USB_MAX_EP0_SIZE)

#ifdef USBD_USE_CDC
#define PMA_CDC_OUT_BASE    (PMA_EP0_IN_ADDR + USB_MAX_EP0_SIZE)
#define PMA_CDC_OUT_ADDR    ((PMA_CDC_OUT_BASE + USB_FS_MAX_PACKET_SIZE) | \
                            (PMA_CDC_OUT_BASE << 16U))
#define PMA_CDC_IN_ADDR     (PMA_CDC_OUT_BASE + USB_FS_MAX_PACKET_SIZE * 2)
#define PMA_CDC_CMD_ADDR    (PMA_CDC_IN_ADDR + CDC_CMD_PACKET_SIZE)
#endif /* USBD_USE_CDC */
#ifdef USBD_USE_HID_COMPOSITE
  #define PMA_MOUSE_IN_ADDR   (PMA_EP0_IN_ADDR + HID_MOUSE_EPIN_SIZE)
  #define PMA_KEYBOARD_IN_ADDR    (PMA_MOUSE_IN_ADDR + HID_KEYBOARD_EPIN_SIZE)
#endif /* USBD_USE_HID_COMPOSITE */
#endif /* USB */

extern const ep_desc_t ep_def[DEV_NUM_EP + 1];


#endif /* USBCON */
#endif /* __USBD_EP_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/