/**
  ******************************************************************************
  * @file    usbd_hid_composite.h
  * @author  MCD Application Team
  * @brief   Header file for the usbd_hid_core.c file.
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
#ifndef __USB_HID_COMPOSITE_H
#define __USB_HID_COMPOSITE_H

#ifdef USBCON
#ifdef USBD_USE_HID_COMPOSITE

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"
#include "usbd_ep_conf.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */
/** @defgroup USBD_HID
  * @brief This file is the Header file for usbd_hid.c
  * @{
  */


/** @defgroup USBD_HID_Exported_Defines
  * @{
  */
#define HID_MOUSE_INTERFACE           0x00U
#define HID_KEYBOARD_INTERFACE        0x01U

#define USB_COMPOSITE_HID_CONFIG_DESC_SIZ       59U
#define USB_HID_DESC_SIZ              9U
#define HID_MOUSE_REPORT_DESC_SIZE    74U
#define HID_KEYBOARD_REPORT_DESC_SIZE 45U

#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22

#ifndef HID_HS_BINTERVAL
#define HID_HS_BINTERVAL              0x07U
#endif /* HID_HS_BINTERVAL */

#ifndef HID_FS_BINTERVAL
#define HID_FS_BINTERVAL            0x0AU
#endif /* HID_FS_BINTERVAL */

#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U
/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum {
  HID_IDLE = 0,
  HID_BUSY,
}
HID_StateTypeDef;


typedef struct {
  uint32_t             Protocol;
  uint32_t             IdleState;
  uint32_t             AltSetting;
  HID_StateTypeDef     Mousestate;
  HID_StateTypeDef     Keyboardstate;
}
USBD_HID_HandleTypeDef;
/**
  * @}
  */



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef  USBD_COMPOSITE_HID;
#define USBD_COMPOSITE_HID_CLASS    &USBD_COMPOSITE_HID
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
uint8_t USBD_HID_MOUSE_SendReport(USBD_HandleTypeDef *pdev,
                                  uint8_t *report,
                                  uint16_t len);
uint8_t USBD_HID_KEYBOARD_SendReport(USBD_HandleTypeDef *pdev,
                                     uint8_t *report,
                                     uint16_t len);

uint32_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef *pdev);

#ifdef __cplusplus
}
#endif

#endif /* USBD_USE_HID_COMPOSITE */
#endif /* USBCON */
#endif /* __USB_HID_COMPOSITE_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
