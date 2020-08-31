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

#if defined(USB_OTG_FS) || defined(USE_USB_HS)
  #define EP_DESC(ADDR, SIZE, KIND_TYP) {ADDR, SIZE}
#else
  #define EP_DESC(ADDR, SIZE, KIND_TYP)  {ADDR, SIZE, KIND_TYP}
#endif

// *INDENT-OFF*

#ifdef USBD_USE_CDC
  #ifdef USE_USB_HS
    #define CDC_DATA_MAX_PACKET_SIZE  CDC_DATA_HS_MAX_PACKET_SIZE
  #else /* USE_USB_FS */
    #define CDC_DATA_MAX_PACKET_SIZE  CDC_DATA_FS_MAX_PACKET_SIZE
  #endif


  const ep_desc_t ep_def[] = {
    EP_DESC(0x00,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(0x80,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(CDC_OUT_EP, CDC_DATA_MAX_PACKET_SIZE, PCD_DBL_BUF),
    EP_DESC(CDC_IN_EP,  CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(CDC_CMD_EP, CDC_CMD_PACKET_SIZE,      PCD_SNG_BUF)
  };
#endif /* USBD_USE_CDC */

#ifdef USBD_USE_MSC
  #ifdef USE_USB_HS
    #define MSC_DATA_MAX_PACKET_SIZE  MSC_DATA_HS_MAX_PACKET_SIZE
  #else /* USE_USB_FS */
    #define MSC_DATA_MAX_PACKET_SIZE  MSC_DATA_FS_MAX_PACKET_SIZE
  #endif


  const ep_desc_t ep_def[] = {
    EP_DESC(0x00,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(0x80,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(MSC_EPIN_ADDR,  MSC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(MSC_EPOUT_ADDR, MSC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF)
  };
#endif /* USBD_USE_MSC */

#ifdef USBD_USE_CDC_MSC
  #ifdef USE_USB_HS
    #define CDC_DATA_MAX_PACKET_SIZE  CDC_DATA_HS_MAX_PACKET_SIZE
    #define MSC_DATA_MAX_PACKET_SIZE  MSC_DATA_HS_MAX_PACKET_SIZE
  #else /* USE_USB_FS */
    #define CDC_DATA_MAX_PACKET_SIZE  CDC_DATA_FS_MAX_PACKET_SIZE
    #define MSC_DATA_MAX_PACKET_SIZE  MSC_DATA_FS_MAX_PACKET_SIZE
  #endif


  const ep_desc_t ep_def[] = {
    EP_DESC(0x00,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(0x80,       CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(CDC_OUT_EP, CDC_DATA_MAX_PACKET_SIZE, PCD_DBL_BUF),
    EP_DESC(CDC_IN_EP,  CDC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(CDC_CMD_EP, CDC_CMD_PACKET_SIZE,      PCD_SNG_BUF),
    EP_DESC(MSC_EPIN_ADDR,  MSC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(MSC_EPOUT_ADDR, MSC_DATA_MAX_PACKET_SIZE, PCD_SNG_BUF)
  };
#endif /* USBD_USE_CDC */


#ifdef USBD_USE_HID_COMPOSITE
  #ifdef USE_USB_HS
    #define HID_MAX_PACKET_SIZE  USB_HS_MAX_PACKET_SIZE
  #else /* USE_USB_FS */
    #define HID_MAX_PACKET_SIZE  USB_FS_MAX_PACKET_SIZE
  #endif

  const ep_desc_t ep_def[] = {
    EP_DESC(0x00,                   HID_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(0x80,                   HID_MAX_PACKET_SIZE, PCD_SNG_BUF),
    EP_DESC(HID_MOUSE_EPIN_ADDR,    HID_MOUSE_EPIN_SIZE, PCD_SNG_BUF),
    EP_DESC(HID_KEYBOARD_EPIN_ADDR, HID_MOUSE_EPIN_SIZE, PCD_SNG_BUF)
  };
#endif /* USBD_USE_HID_COMPOSITE */

// *INDENT-OFF*

#endif /* HAL_PCD_MODULE_ENABLED && USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

