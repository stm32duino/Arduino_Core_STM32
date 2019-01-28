/**
  ******************************************************************************
  * @file    usbd_desc.h
  * @author  MCD Application Team
  * @brief   Header for usbd_desc.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_DESC_H
#define __USBD_DESC_H
#ifdef USBCON
/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define  DEVICE_ID1                  (UID_BASE)
#define  DEVICE_ID2                  (UID_BASE+0x4)
#define  DEVICE_ID3                  (UID_BASE+0x8)

#define  USB_SIZ_STRING_SERIAL       0x1A

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#ifdef USBD_USE_HID_COMPOSITE
extern USBD_DescriptorsTypeDef HID_Desc;
#endif
#ifdef USBD_USE_CDC
extern USBD_DescriptorsTypeDef CDC_Desc;
#endif
#endif /* USBCON */
#endif /* __USBD_DESC_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
