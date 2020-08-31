/**
  ******************************************************************************
  * @file    usbd_msc_data.h
  * @author  MCD Application Team
  * @brief   Header for the usbd_msc_data.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
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
#ifndef __USBD_MSC_DATA_H
#define __USBD_MSC_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_conf.h"


#define MODE_SENSE6_LEN                    0x17U
#define MODE_SENSE10_LEN                   0x1BU
#define LENGTH_INQUIRY_PAGE00              0x06U
#define LENGTH_INQUIRY_PAGE80              0x08U
#define LENGTH_FORMAT_CAPACITIES           0x14U


extern uint8_t MSC_Page00_Inquiry_Data[LENGTH_INQUIRY_PAGE00];
extern uint8_t MSC_Page80_Inquiry_Data[LENGTH_INQUIRY_PAGE80];
extern uint8_t MSC_Mode_Sense6_data[MODE_SENSE6_LEN];
extern uint8_t MSC_Mode_Sense10_data[MODE_SENSE10_LEN];


#ifdef __cplusplus
}
#endif

#endif /* __USBD_MSC_DATA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
