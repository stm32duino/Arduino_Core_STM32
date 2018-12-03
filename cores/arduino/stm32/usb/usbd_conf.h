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
  *                      http://www.st.com/SLA0044
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

#define USBD_MAX_NUM_INTERFACES             2U
#define USBD_MAX_NUM_CONFIGURATION          1U
#define USBD_MAX_STR_DESC_SIZ               0x100U
#define USBD_SUPPORT_USER_STRING            0U
#define USBD_SELF_POWERED                   1U
#define USBD_DEBUG_LEVEL                    0U

/* MSC Class Config */
#define MSC_MEDIA_PACKET                    8192U

/* CDC Class Config */
#define USBD_CDC_INTERVAL                   2000U

/* DFU Class Config */
#define USBD_DFU_MAX_ITF_NUM                1U
#define USBD_DFU_XFERS_IZE                  1024U

/* AUDIO Class Config */
#define USBD_AUDIO_FREQ                     22100U

/* Memory management macros */
#define USBD_malloc               malloc
#define USBD_free                 free
#define USBD_memset               memset
#define USBD_memcpy               memcpy

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
