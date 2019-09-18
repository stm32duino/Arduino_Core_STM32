/**
  ******************************************************************************
  * @file    usbd_ep_conf.c
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
#if defined(HAL_PCD_MODULE_ENABLED) && defined(USBCON)
/* Includes ------------------------------------------------------------------*/
#include "usbd_ep_conf.h"

#ifdef USBD_USE_CDC
const ep_desc_t ep_def[] = {
#ifdef USE_USB_HS
  {0x00,       CDC_DATA_HS_MAX_PACKET_SIZE},
  {0x80,       CDC_DATA_HS_MAX_PACKET_SIZE},
  {CDC_OUT_EP, CDC_DATA_HS_MAX_PACKET_SIZE},
  {CDC_IN_EP,  CDC_DATA_HS_MAX_PACKET_SIZE},
  {CDC_CMD_EP, CDC_CMD_PACKET_SIZE}
#else /* USE_USB_FS */
#ifdef USB_OTG_FS
  {0x00,       CDC_DATA_FS_MAX_PACKET_SIZE},
  {0x80,       CDC_DATA_FS_MAX_PACKET_SIZE},
  {CDC_OUT_EP, CDC_DATA_FS_MAX_PACKET_SIZE},
  {CDC_IN_EP,  CDC_DATA_FS_MAX_PACKET_SIZE},
  {CDC_CMD_EP, CDC_CMD_PACKET_SIZE}
#else
  {0x00,       PMA_EP0_OUT_ADDR, PCD_SNG_BUF},
  {0x80,       PMA_EP0_IN_ADDR,  PCD_SNG_BUF},
  {CDC_OUT_EP, PMA_CDC_OUT_ADDR, PCD_DBL_BUF},
  {CDC_IN_EP,  PMA_CDC_IN_ADDR,  PCD_SNG_BUF},
  {CDC_CMD_EP, PMA_CDC_CMD_ADDR, PCD_SNG_BUF}
#endif
#endif
};
#endif /* USBD_USE_CDC */

#ifdef USBD_USE_HID_COMPOSITE
const ep_desc_t ep_def[] = {
#if !defined (USB)
#ifdef USE_USB_HS
  {0x00,                   USB_HS_MAX_PACKET_SIZE},
  {0x80,                   USB_HS_MAX_PACKET_SIZE},
#else
  {0x00,                   USB_FS_MAX_PACKET_SIZE},
  {0x80,                   USB_FS_MAX_PACKET_SIZE},
#endif
  {HID_MOUSE_EPIN_ADDR,    HID_MOUSE_EPIN_SIZE},
  {HID_KEYBOARD_EPIN_ADDR, HID_KEYBOARD_EPIN_SIZE},
#else
  {0x00,                   PMA_EP0_OUT_ADDR,     PCD_SNG_BUF},
  {0x80,                   PMA_EP0_IN_ADDR,      PCD_SNG_BUF},
  {HID_MOUSE_EPIN_ADDR,    PMA_MOUSE_IN_ADDR,    PCD_SNG_BUF},
  {HID_KEYBOARD_EPIN_ADDR, PMA_KEYBOARD_IN_ADDR, PCD_SNG_BUF},
#endif
};
#endif /* USBD_USE_HID_COMPOSITE */

#endif /* HAL_PCD_MODULE_ENABLED && USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

