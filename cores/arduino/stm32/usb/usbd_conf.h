/**
  ******************************************************************************
  * @file    usbd_conf.h
  * @author  MCD Application Team
  * @brief   Header file for the usbd_conf.c file
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
#ifndef __USBD_CONF_H
#define __USBD_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USBCON
/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#if !defined(USB_BASE) && !defined(USB_OTG_DEVICE_BASE)
#error "This board does not support USB! Select 'None' in the 'Tools->USB interface' menu"
#endif
#if defined(USE_USB_HS) && !defined(USB_OTG_HS)
#error "This board does not support USB High Speed! Select 'Full Speed' in the 'Tools->USB interface' menu"
#endif
#if !defined(USB_BASE) && !defined(USB_OTG_FS) && defined(USB_OTG_HS) && !defined(USE_USB_HS)
#error "This board support only USB High Speed! Select 'High Speed' or 'High Speed in Full Speed mode' in the 'Tools->USB interface' menu"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(USB_BASE)

#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx) || \
    defined(STM32L1xx) || defined(STM32WBxx)
#if defined(SYSCFG_CFGR1_USB_IT_RMP) && !defined(USE_USB_INTERRUPT_REMAPPED)
#define USB_IRQn            USB_LP_CAN_RX0_IRQn
#define USB_IRQHandler      USB_LP_CAN_RX0_IRQHandler
#define USB_H_IRQn          USB_HP_CAN_TX_IRQn
#define USB_H_IRQHandler    USB_HP_CAN_TX_IRQHandler
#define USB_WKUP_IRQn       USBWakeUp_IRQn
#define USB_WKUP_IRQHandler USBWakeUp_IRQHandler
#else
#define USB_IRQn            USB_LP_IRQn
#define USB_IRQHandler      USB_LP_IRQHandler
#define USB_H_IRQn          USB_HP_IRQn
#define USB_H_IRQHandler    USB_HP_IRQHandler
#if defined(SYSCFG_CFGR1_USB_IT_RMP) && defined(USE_USB_INTERRUPT_REMAPPED)
#define USB_WKUP_IRQn       USBWakeUp_RMP_IRQn
#define USB_WKUP_IRQHandler USBWakeUp_RMP_IRQHandler
#elif defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx)
#define USB_WKUP_IRQn       USBWakeUp_IRQn
#define USB_WKUP_IRQHandler USBWakeUp_IRQHandler
#elif defined(STM32L1xx)
#define USB_WKUP_IRQn       USB_FS_WKUP_IRQn
#define USB_WKUP_IRQHandler USB_FS_WKUP_IRQHandler
#endif
#endif
#elif defined(STM32G0xx)
#define USB_IRQn USB_UCPD1_2_IRQn
#define USB_IRQHandler USB_UCPD1_2_IRQHandler
#elif defined(STM32U5xx) && !defined(USB_DRD_FS)
#define USB_IRQn OTG_FS_IRQn
#define USB_IRQHandler OTG_FS_IRQHandler
#elif defined(STM32L5xx)
#define USB_IRQn            USB_FS_IRQn
#define USB_IRQHandler      USB_FS_IRQHandler
#endif

#endif /* USB_BASE */

#ifndef __HAL_PCD_GATE_PHYCLOCK
#define __HAL_PCD_GATE_PHYCLOCK(_DUMMY_)
#endif

#ifndef __HAL_PCD_UNGATE_PHYCLOCK
#define __HAL_PCD_UNGATE_PHYCLOCK(_DUMMY_)
#endif

#ifndef USBD_MAX_NUM_INTERFACES
#define USBD_MAX_NUM_INTERFACES                     2U
#endif /* USBD_MAX_NUM_INTERFACES */

#ifndef USBD_MAX_NUM_CONFIGURATION
#define USBD_MAX_NUM_CONFIGURATION                  1U
#endif /* USBD_MAX_NUM_CONFIGURATION */

#ifndef USBD_MAX_STR_DESC_SIZ
#define USBD_MAX_STR_DESC_SIZ                       0x100U
#endif /* USBD_MAX_STR_DESC_SIZ */

#ifndef USBD_SELF_POWERED
#define USBD_SELF_POWERED                           1U
#endif /* USBD_SELF_POWERED */

#ifndef USBD_DEBUG_LEVEL
#define USBD_DEBUG_LEVEL                            0U
#endif /* USBD_DEBUG_LEVEL */

/* ECM, RNDIS, DFU Class Config */
#ifndef USBD_SUPPORT_USER_STRING_DESC
#define USBD_SUPPORT_USER_STRING_DESC               0U
#endif /* USBD_SUPPORT_USER_STRING_DESC */

/* BillBoard Class Config */
#ifndef USBD_CLASS_USER_STRING_DESC
#define USBD_CLASS_USER_STRING_DESC                 1U
#endif /* USBD_CLASS_USER_STRING_DESC */

#ifndef USBD_CLASS_BOS_ENABLED
#define USBD_CLASS_BOS_ENABLED                      0U
#endif /* USBD_CLASS_BOS_ENABLED */

#ifndef USB_BB_MAX_NUM_ALT_MODE
#define USB_BB_MAX_NUM_ALT_MODE                     0x2U
#endif /* USB_BB_MAX_NUM_ALT_MODE */

/* MSC Class Config */
#ifndef MSC_MEDIA_PACKET
#define MSC_MEDIA_PACKET                            8192U
#endif /* MSC_MEDIA_PACKET */

/* CDC Class Config */
#ifndef USBD_CDC_INTERVAL
#define USBD_CDC_INTERVAL                           2000U
#endif /* USBD_CDC_INTERVAL */

/* DFU Class Config */
#ifndef USBD_DFU_MAX_ITF_NUM
#define USBD_DFU_MAX_ITF_NUM                        1U
#endif /* USBD_DFU_MAX_ITF_NUM */
#ifndef USBD_DFU_XFERS_IZE
#define USBD_DFU_XFERS_IZE                          1024U
#endif /* USBD_DFU_XFERS_IZE */

/* AUDIO Class Config */
#ifndef USBD_AUDIO_FREQ
#define USBD_AUDIO_FREQ                             22100U
#endif /* USBD_AUDIO_FREQ */

/* CustomHID Class Config */
#ifndef CUSTOM_HID_HS_BINTERVAL
#define CUSTOM_HID_HS_BINTERVAL                     0x05U
#endif /* CUSTOM_HID_HS_BINTERVAL */
#ifndef CUSTOM_HID_FS_BINTERVAL
#define CUSTOM_HID_FS_BINTERVAL                     0x05U
#endif /* CUSTOM_HID_FS_BINTERVAL */
#ifndef USBD_CUSTOMHID_OUTREPORT_BUF_SIZE
#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE           0x02U
#endif /* USBD_CUSTOMHID_OUTREPORT_BUF_SIZE */
#ifndef USBD_CUSTOM_HID_REPORT_DESC_SIZE
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE            163U
#endif /* USBD_CUSTOM_HID_REPORT_DESC_SIZE */

/* VIDEO Class Config */
#ifndef UVC_1_1
#define UVC_1_1 /* #define UVC_1_0 */
#endif /* UVC_1_1 */

/* To be used only with YUY2 and NV12 Video format, shouldn't be defined for MJPEG format */
#ifndef USBD_UVC_FORMAT_UNCOMPRESSED
#define USBD_UVC_FORMAT_UNCOMPRESSED
#endif /* USBD_UVC_FORMAT_UNCOMPRESSED */

#ifdef USBD_UVC_FORMAT_UNCOMPRESSED
#ifndef UVC_BITS_PER_PIXEL
#define UVC_BITS_PER_PIXEL                          12U
#endif /* UVC_BITS_PER_PIXEL */
#ifndef UVC_UNCOMPRESSED_GUID
#define UVC_UNCOMPRESSED_GUID                       UVC_GUID_NV12 /* UVC_GUID_YUY2 */
#endif /* UVC_UNCOMPRESSED_GUID */

/* refer to Table 3-18 Color Matching Descriptor video class v1.1 */
#ifndef UVC_COLOR_PRIMARIE
#define UVC_COLOR_PRIMARIE                          0x01U
#endif /* UVC_COLOR_PRIMARIE */
#ifndef UVC_TFR_CHARACTERISTICS
#define UVC_TFR_CHARACTERISTICS                     0x01U
#endif /* UVC_TFR_CHARACTERISTICS */
#ifndef UVC_MATRIX_COEFFICIENTS
#define UVC_MATRIX_COEFFICIENTS                     0x04U
#endif /* UVC_MATRIX_COEFFICIENTS */
#endif

/* Video Stream frame width and height */
#ifndef UVC_WIDTH
#define UVC_WIDTH                                   176U
#endif /* UVC_WIDTH */
#ifndef UVC_HEIGHT
#define UVC_HEIGHT                                  144U
#endif /* UVC_HEIGHT */

/* bEndpointAddress in Endpoint Descriptor */
#ifndef UVC_IN_EP
#define UVC_IN_EP                                   0x81U
#endif /* UVC_IN_EP */

#ifndef UVC_CAM_FPS_FS
#define UVC_CAM_FPS_FS                              10U
#endif /* UVC_CAM_FPS_FS */
#ifndef UVC_CAM_FPS_HS
#define UVC_CAM_FPS_HS                              5U
#endif /* UVC_CAM_FPS_HS */

#ifndef UVC_ISO_HS_MPS
#define UVC_ISO_FS_MPS                              512U
#endif /* UVC_ISO_HS_MPS */
#ifndef UVC_ISO_HS_MPS
#define UVC_ISO_HS_MPS                              512U
#endif /* UVC_ISO_HS_MPS */

#ifndef UVC_PACKET_SIZE
#define UVC_PACKET_SIZE                             UVC_ISO_FS_MPS
#endif /* UVC_PACKET_SIZE */
/* To be used with Device Only IP supporting double buffer mode */
/* #define UVC_HEADER_PACKET_CNT                     0x02U */
/* #define UVC_PACKET_SIZE                           (UVC_ISO_FS_MPS * UVC_HEADER_PACKET_CNT) */

#ifndef UVC_MAX_FRAME_SIZE
#define UVC_MAX_FRAME_SIZE                          (UVC_WIDTH * UVC_HEIGHT * 16U / 8U)
#endif /* UVC_MAX_FRAME_SIZE */

/* Interrupt priority */
#ifndef USBD_IRQ_PRIO
#define USBD_IRQ_PRIO                               1
#endif /* USBD_IRQ_PRIO */

#ifndef USBD_IRQ_SUBPRIO
#define USBD_IRQ_SUBPRIO                            0
#endif /* USBD_IRQ_SUBPRIO */

/* Memory management macros make sure to use static memory allocation */
/* Currently dynamic memory allocation usage */
/** Alias for memory allocation. */
#ifndef USBD_malloc
#define USBD_malloc         malloc
#endif /* USBD_malloc */

/** Alias for memory release. */
#ifndef USBD_free
#define USBD_free           free
#endif /* USBD_free */

/** Alias for memory set. */
#ifndef USBD_memset
#define USBD_memset         memset
#endif /* USBD_memset */

/** Alias for memory copy. */
#ifndef USBD_memcpy
#define USBD_memcpy         memcpy
#endif /* USBD_memcpy */

/** Alias for delay. */
#ifndef USBD_Delay
#define USBD_Delay          HAL_Delay
#endif /* USBD_Delay */

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0U)
#define  USBD_UsrLog(...)   do { \
                                 printf(__VA_ARGS__); \
                                 printf("\n"); \
                               } while (0)
#else
#define USBD_UsrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)

#define  USBD_ErrLog(...) do { \
                               printf("ERROR: ") ; \
                               printf(__VA_ARGS__); \
                               printf("\n"); \
                             } while (0)
#else
#define USBD_ErrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 2U)
#define  USBD_DbgLog(...)   do { \
                                 printf("DEBUG : ") ; \
                                 printf(__VA_ARGS__); \
                                 printf("\n"); \
                               } while (0)
#else
#define USBD_DbgLog(...) do {} while (0)
#endif

/* Exported functions -------------------------------------------------------*/
void *USBD_static_malloc(uint32_t size);
void USBD_static_free(void *p);

#endif /* USBCON */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
