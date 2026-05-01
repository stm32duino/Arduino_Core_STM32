/*
 * USBCore_stm32.h
 * Template generated with Stm32CubeMX "usbd_customhid.h":
 * Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 * Implementation/modification:
 * Copyright (C) 2022-2025 Levi Gillis - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU Lesser General Public License v3.0 license.
 */

#ifndef __USBCORE_STM32_H__
#define __USBCORE_STM32_H__

#if defined(USBCON) && defined(PLUGGABLE_USB_ENABLED)

#include "USB_EP.h"
#include "usbd_ioreq.h"

#define HID_DESCRIPTOR_TYPE 0x21
#define HID_REPORT_DESC     0x22

#ifndef HID_HS_BINTERVAL
  #define HID_HS_BINTERVAL 0x07U
#endif /* HID_HS_BINTERVAL */

#ifndef HID_FS_BINTERVAL
  #define HID_FS_BINTERVAL 0x0AU
#endif /* HID_FS_BINTERVAL */

#define HID_REQ_SET_PROTOCOL 0x0BU
#define HID_REQ_GET_PROTOCOL 0x03U

#define HID_REQ_SET_IDLE 0x0AU
#define HID_REQ_GET_IDLE 0x02U

#define HID_REQ_SET_REPORT 0x09U
#define HID_REQ_GET_REPORT 0x01U

typedef enum {
  HID_IDLE = 0,
  HID_BUSY,
} HID_StateTypeDef;

typedef struct {
  uint32_t Protocol;
  uint32_t IdleState;
  uint32_t AltSetting;
  HID_StateTypeDef EPstate[USB_MAX_EPS];
} USBD_HID_HandleTypeDef;

#endif /* USBCON */
#endif /* __USBCORE_STM32_H__ */
