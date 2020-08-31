/**
  ******************************************************************************
  * @file    usbd_msc_data.c
  * @author  MCD Application Team
  * @brief   This file provides all the vital inquiry pages and sense data.
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

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
- "stm32xxxxx_{eval}{discovery}{adafruit}_sd.c"
EndBSPDependencies */

#include "usbd_ep_conf.h"

#ifdef USBCON
#ifdef USBD_USE_MSC_CLASS

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc_data.h"


/* USB Mass storage Page 0 Inquiry Data */
uint8_t MSC_Page00_Inquiry_Data[LENGTH_INQUIRY_PAGE00] = {
  0x00,
  0x00,
  0x00,
  (LENGTH_INQUIRY_PAGE00 - 4U),
  0x00,
  0x80
};

/* USB Mass storage VPD Page 0x80 Inquiry Data for Unit Serial Number */
uint8_t MSC_Page80_Inquiry_Data[LENGTH_INQUIRY_PAGE80] = {
  0x00,
  0x80,
  0x00,
  LENGTH_INQUIRY_PAGE80,
  0x20,     /* Put Product Serial number */
  0x20,
  0x20,
  0x20
};

/* USB Mass storage sense 6 Data */
uint8_t MSC_Mode_Sense6_data[MODE_SENSE6_LEN] = {
  0x22,
  0x00,
  0x00,
  0x00,
  0x08,
  0x12,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};


/* USB Mass storage sense 10  Data */
uint8_t MSC_Mode_Sense10_data[MODE_SENSE10_LEN] = {
  0x00,
  0x26,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x08,
  0x12,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};


#endif /* USBD_USE_MSC_CLASS */
#endif /* USBCON */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
