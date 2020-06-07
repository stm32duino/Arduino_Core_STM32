/**
  ******************************************************************************
  * @file    usbd_cdc_msc_core.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   header file for the usbd_cdc_msc_core.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

#ifndef __USB_CDC_MSC_CORE_H_
#define __USB_CDC_MSC_CORE_H_

#include "usbd_cdc.h"
#include "usbd_msc.h"
#include "usbd_ioreq.h"

#define CDC_ACM_INTERFACE   0x0
#define CDC_COM_INTERFACE   0x1
#define MSC_INTERFACE       0x2

#define USB_CDC_MSC_CONFIG_DESC_SIZ  (USB_CDC_CONFIG_DESC_SIZ - 9 + 8 + USB_MSC_CONFIG_DESC_SIZ)

extern USBD_ClassTypeDef  USBD_CDC_MSC;

#endif  /* __USB_CDC_MSC_CORE_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
