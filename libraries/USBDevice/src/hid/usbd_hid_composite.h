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
  *                      www.st.com/SLA0044
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
/** @defgroup USBD_HID USBD HID Composite Class
  * @brief This file is the Header file for usbd_hid_composite.c
  * @{
  */


/** @defgroup USBD_HID_Exported_Defines USBD HID Exported Defines
  * @brief HID interface numbers, descriptor sizes, class request codes and
  *        endpoint polling intervals.
  * @{
  */
/** @name Interface numbers */
/** @{ */
#define HID_MOUSE_INTERFACE           0x00U
#define HID_KEYBOARD_INTERFACE        0x01U
/** @} */

/** @name Descriptor sizes, in bytes */
/** @{ */
#define USB_COMPOSITE_HID_CONFIG_DESC_SIZ       59U
#define USB_HID_DESC_SIZ              9U
#define HID_MOUSE_REPORT_DESC_SIZE    74U
#define HID_KEYBOARD_REPORT_DESC_SIZE 45U
/** @} */

/** @name Descriptor types */
/** @{ */
#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22
/** @} */

#ifndef HID_HS_BINTERVAL
/**
 * @brief Endpoint polling interval at high speed, as bInterval
 *        (2^(bInterval-1) microframes). Can be overridden.
 */
#define HID_HS_BINTERVAL              0x07U
#endif /* HID_HS_BINTERVAL */

#ifndef HID_FS_BINTERVAL
/** @brief Endpoint polling interval at full speed, in ms. Can be overridden. */
#define HID_FS_BINTERVAL            0x0AU
#endif /* HID_FS_BINTERVAL */

/** @name HID class request codes */
/** @{ */
#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U
/** @} */
/**
  * @}
  */


/** @defgroup USBD_HID_Exported_Types USBD HID Exported Types
  * @brief Types used by the USB HID composite class.
  * @{
  */
/** @brief HID transfer state. */
typedef enum {
  HID_IDLE = 0, /**< Ready to send a report. */
  HID_BUSY,     /**< A report is being sent. */
} HID_StateTypeDef;


/** @brief HID composite class instance data. */
typedef struct {
  uint32_t             Protocol;      /**< Active HID protocol. */
  uint32_t             IdleState;     /**< Idle rate set by the host. */
  /** Alternate setting of the interface. */
  uint32_t             AltSetting;
  /** Transfer state of the mouse IN endpoint. */
  HID_StateTypeDef     Mousestate;
  /** Transfer state of the keyboard IN endpoint. */
  HID_StateTypeDef     Keyboardstate;
} USBD_HID_HandleTypeDef;

/**
 * @brief HID descriptor, as defined in HID Class specification version 1.1, section 6.2.1.
 */
typedef struct {
  /** Size of the descriptor, in bytes. */
  uint8_t           bLength;
  /** Descriptor type (HID_DESCRIPTOR_TYPE). */
  uint8_t           bDescriptorType;
  /** HID specification release number (BCD). */
  uint16_t          bcdHID;
  /** Country code of the localized hardware. */
  uint8_t           bCountryCode;
  uint8_t           bNumDescriptors;    /**< Number of class descriptors. */
  /** Type of the first class descriptor (HID_REPORT_DESC). */
  uint8_t           bHIDDescriptorType;
  /** Size of the first class descriptor, in bytes. */
  uint16_t          wItemLength;
} __PACKED USBD_HIDDescTypeDef;

/**
  * @}
  */

/** @defgroup USBD_HID_Exported_Variables USBD HID Exported Variables
  * @brief Class driver exported by the USB HID composite class.
  * @{
  */

/** @brief HID composite (mouse and keyboard) class driver. */
extern USBD_ClassTypeDef  USBD_COMPOSITE_HID;
/**
 * @brief Pointer to the HID composite class driver, as expected by USBD_RegisterClass().
 */
#define USBD_COMPOSITE_HID_CLASS    &USBD_COMPOSITE_HID
/**
  * @}
  */

/** @defgroup USBD_HID_Exported_Functions USBD HID Exported Functions
  * @brief Functions used by the application to send HID reports.
  * @{
  */
/**
 * @brief Send a HID mouse report.
 * @param pdev Pointer to the device instance.
 * @param report Pointer to the report data.
 * @param len Length of the report, in bytes.
 * @param ClassId Class instance ID. Only present when USE_USBD_COMPOSITE is defined.
 * @return USBD_OK on success or if the device is not configured,
 *         USBD_BUSY if the previous report is still pending,
 *         USBD_FAIL if the class instance is not allocated.
 */
#ifdef USE_USBD_COMPOSITE
uint8_t USBD_HID_MOUSE_SendReport(USBD_HandleTypeDef *pdev,
                                  uint8_t *report,
                                  uint16_t len,
                                  uint8_t ClassId);
#else
uint8_t USBD_HID_MOUSE_SendReport(USBD_HandleTypeDef *pdev,
                                  uint8_t *report,
                                  uint16_t len);
#endif /* USE_USBD_COMPOSITE */

/**
 * @brief Send a HID keyboard report.
 * @param pdev Pointer to the device instance.
 * @param report Pointer to the report data.
 * @param len Length of the report, in bytes.
 * @param ClassId Class instance ID. Only present when USE_USBD_COMPOSITE is defined.
 * @return USBD_OK on success or if the device is not configured,
 *         USBD_BUSY if the previous report is still pending,
 *         USBD_FAIL if the class instance is not allocated.
 */
#ifdef USE_USBD_COMPOSITE
uint8_t USBD_HID_KEYBOARD_SendReport(USBD_HandleTypeDef *pdev,
                                     uint8_t *report,
                                     uint16_t len,
                                     uint8_t ClassId);
#else
uint8_t USBD_HID_KEYBOARD_SendReport(USBD_HandleTypeDef *pdev,
                                     uint8_t *report,
                                     uint16_t len);
#endif /* USE_USBD_COMPOSITE */

/**
 * @brief Get the polling interval from the HID endpoint descriptor.
 * @param pdev Pointer to the device instance.
 * @return Polling interval in ms, computed from HID_HS_BINTERVAL when the
 *         device runs at high speed, or taken from HID_FS_BINTERVAL otherwise.
 */
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
