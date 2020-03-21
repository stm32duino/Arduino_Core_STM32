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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(USB_BASE)

#if defined(STM32F1xx)
#define USB_IRQn USB_LP_CAN1_RX0_IRQn
#define USB_IRQHandler USB_LP_CAN1_RX0_IRQHandler
#elif defined(STM32F3xx)
/* ToDo: Check remap on USB_LP_IRQn */
#ifndef USE_USB_INTERRUPT_REMAPPED
#define USB_IRQn USB_LP_CAN_RX0_IRQn
#define USB_IRQHandler USB_LP_CAN_RX0_IRQHandler
#else
#define USB_IRQn USB_LP_IRQn
#define USB_IRQHandler USB_LP_IRQHandler
#endif /* USE_USB_INTERRUPT_REMAPPED */
#elif defined(STM32L1xx)
#define USB_IRQn USB_LP_IRQn
#define USB_IRQHandler USB_LP_IRQHandler
#endif

#endif /* USB_BASE */

#ifndef __HAL_PCD_GATE_PHYCLOCK
#define __HAL_PCD_GATE_PHYCLOCK(_DUMMY_)
#endif

#ifndef __HAL_PCD_UNGATE_PHYCLOCK
#define __HAL_PCD_UNGATE_PHYCLOCK(_DUMMY_)
#endif

#ifndef USBD_MAX_NUM_INTERFACES
#define USBD_MAX_NUM_INTERFACES             2U
#endif /* USBD_MAX_NUM_INTERFACES */

#ifndef USBD_MAX_STR_DESC_SIZ
#define USBD_MAX_STR_DESC_SIZ               0x100U
#endif /* USBD_MAX_STR_DESC_SIZ */

#ifndef USBD_DEBUG_LEVEL
#define USBD_DEBUG_LEVEL                    0U
#endif /* USBD_DEBUG_LEVEL */

/* MSC Class Config */
#ifndef MSC_MEDIA_PACKET
#define MSC_MEDIA_PACKET                    8192U
#endif /* MSC_MEDIA_PACKET */

/* CDC Class Config */
#ifndef USBD_CDC_INTERVAL
#define USBD_CDC_INTERVAL                   2000U
#endif /* USBD_CDC_INTERVAL */

/* DFU Class Config */
#ifndef USBD_DFU_MAX_ITF_NUM
#define USBD_DFU_MAX_ITF_NUM                1U
#endif /* USBD_DFU_MAX_ITF_NUM */
#ifndef USBD_DFU_XFERS_IZE
#define USBD_DFU_XFERS_IZE                  1024U
#endif /* USBD_DFU_XFERS_IZE */

/* AUDIO Class Config */
#ifndef USBD_AUDIO_FREQ
#define USBD_AUDIO_FREQ                     22100U
#endif /* USBD_AUDIO_FREQ */

/* Interrupt priority */
#ifndef USBD_IRQ_PRIO
#define USBD_IRQ_PRIO                       1
#endif /* USBD_IRQ_PRIO */
#ifndef USBD_IRQ_SUBPRIO
#define USBD_IRQ_SUBPRIO                    0
#endif /* USBD_IRQ_SUBPRIO */

/* Memory management macros */
#ifndef USBD_malloc
#define USBD_malloc               malloc
#endif /* USBD_malloc */
#ifndef USBD_free
#define USBD_free                 free
#endif /* USBD_free */
#ifndef USBD_memset
#define USBD_memset               memset
#endif /* USBD_memset */
#ifndef USBD_memcpy
#define USBD_memcpy               memcpy
#endif /* USBD_memcpy */

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

#endif /* USBCON */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
