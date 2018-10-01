/**
  ******************************************************************************
  * @file    usbd_def.h
  * @author  MCD Application Team
  * @brief   General defines for the usb device library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_DEF_H
#define __USBD_DEF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_conf.h"

/** @addtogroup STM32_USBD_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USB_DEF
  * @brief general defines for the usb device library file
  * @{
  */

/** @defgroup USB_DEF_Exported_Defines
  * @{
  */

#ifndef NULL
#define NULL                                            0U
#endif /* NULL */

#ifndef USBD_MAX_NUM_INTERFACES
#define USBD_MAX_NUM_INTERFACES                         1U
#endif /* USBD_MAX_NUM_CONFIGURATION */

#ifndef USBD_MAX_NUM_CONFIGURATION
#define USBD_MAX_NUM_CONFIGURATION                      1U
#endif /* USBD_MAX_NUM_CONFIGURATION */

#ifndef USBD_LPM_ENABLED
#define USBD_LPM_ENABLED                                0U
#endif /* USBD_LPM_ENABLED */

#ifndef USBD_SELF_POWERED
#define USBD_SELF_POWERED                               1U
#endif /*USBD_SELF_POWERED */

#ifndef USBD_SUPPORT_USER_STRING
#define USBD_SUPPORT_USER_STRING                        0U
#endif /* USBD_SUPPORT_USER_STRING */

#define  USB_LEN_DEV_QUALIFIER_DESC                     0x0AU
#define  USB_LEN_DEV_DESC                               0x12U
#define  USB_LEN_CFG_DESC                               0x09U
#define  USB_LEN_IF_DESC                                0x09U
#define  USB_LEN_EP_DESC                                0x07U
#define  USB_LEN_OTG_DESC                               0x03U
#define  USB_LEN_LANGID_STR_DESC                        0x04U
#define  USB_LEN_OTHER_SPEED_DESC_SIZ                   0x09U

#define  USBD_IDX_LANGID_STR                            0x00U
#define  USBD_IDX_MFC_STR                               0x01U
#define  USBD_IDX_PRODUCT_STR                           0x02U
#define  USBD_IDX_SERIAL_STR                            0x03U
#define  USBD_IDX_CONFIG_STR                            0x04U
#define  USBD_IDX_INTERFACE_STR                         0x05U

#define  USB_REQ_TYPE_STANDARD                          0x00U
#define  USB_REQ_TYPE_CLASS                             0x20U
#define  USB_REQ_TYPE_VENDOR                            0x40U
#define  USB_REQ_TYPE_MASK                              0x60U

#define  USB_REQ_RECIPIENT_DEVICE                       0x00U
#define  USB_REQ_RECIPIENT_INTERFACE                    0x01U
#define  USB_REQ_RECIPIENT_ENDPOINT                     0x02U
#define  USB_REQ_RECIPIENT_MASK                         0x03U

#define  USB_REQ_GET_STATUS                             0x00U
#define  USB_REQ_CLEAR_FEATURE                          0x01U
#define  USB_REQ_SET_FEATURE                            0x03U
#define  USB_REQ_SET_ADDRESS                            0x05U
#define  USB_REQ_GET_DESCRIPTOR                         0x06U
#define  USB_REQ_SET_DESCRIPTOR                         0x07U
#define  USB_REQ_GET_CONFIGURATION                      0x08U
#define  USB_REQ_SET_CONFIGURATION                      0x09U
#define  USB_REQ_GET_INTERFACE                          0x0AU
#define  USB_REQ_SET_INTERFACE                          0x0BU
#define  USB_REQ_SYNCH_FRAME                            0x0CU

#define  USB_DESC_TYPE_DEVICE                              1U
#define  USB_DESC_TYPE_CONFIGURATION                       2U
#define  USB_DESC_TYPE_STRING                              3U
#define  USB_DESC_TYPE_INTERFACE                           4U
#define  USB_DESC_TYPE_ENDPOINT                            5U
#define  USB_DESC_TYPE_DEVICE_QUALIFIER                    6U
#define  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION           7U
#define  USB_DESC_TYPE_BOS                                 0x0FU

#define USB_CONFIG_REMOTE_WAKEUP                           2U
#define USB_CONFIG_SELF_POWERED                            1U

#define USB_FEATURE_EP_HALT                                0U
#define USB_FEATURE_REMOTE_WAKEUP                          1U
#define USB_FEATURE_TEST_MODE                              2U

#define USB_DEVICE_CAPABITY_TYPE                           0x10U

#define USB_HS_MAX_PACKET_SIZE                            512
#define USB_FS_MAX_PACKET_SIZE                            64
#define USB_MAX_EP0_SIZE                                  64U

/*  Device Status */
#define USBD_STATE_DEFAULT                                1U
#define USBD_STATE_ADDRESSED                              2U
#define USBD_STATE_CONFIGURED                             3U
#define USBD_STATE_SUSPENDED                              4U


/*  EP0 State */
#define USBD_EP0_IDLE                                     0U
#define USBD_EP0_SETUP                                    1U
#define USBD_EP0_DATA_IN                                  2U
#define USBD_EP0_DATA_OUT                                 3U
#define USBD_EP0_STATUS_IN                                4U
#define USBD_EP0_STATUS_OUT                               5U
#define USBD_EP0_STALL                                    6U

#define USBD_EP_TYPE_CTRL                                 0U
#define USBD_EP_TYPE_ISOC                                 1U
#define USBD_EP_TYPE_BULK                                 2U
#define USBD_EP_TYPE_INTR                                 3U


/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_TypesDefinitions
  * @{
  */

typedef  struct  usb_setup_req
{

    uint8_t   bmRequest;
    uint8_t   bRequest;
    uint16_t  wValue;
    uint16_t  wIndex;
    uint16_t  wLength;
}USBD_SetupReqTypedef;

struct _USBD_HandleTypeDef;

typedef struct _Device_cb
{
  uint8_t  (*Init)             (struct _USBD_HandleTypeDef *pdev , uint8_t cfgidx);
  uint8_t  (*DeInit)           (struct _USBD_HandleTypeDef *pdev , uint8_t cfgidx);
 /* Control Endpoints*/
  uint8_t  (*Setup)            (struct _USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req);
  uint8_t  (*EP0_TxSent)       (struct _USBD_HandleTypeDef *pdev );
  uint8_t  (*EP0_RxReady)      (struct _USBD_HandleTypeDef *pdev );
  /* Class Specific Endpoints*/
  uint8_t  (*DataIn)           (struct _USBD_HandleTypeDef *pdev , uint8_t epnum);
  uint8_t  (*DataOut)          (struct _USBD_HandleTypeDef *pdev , uint8_t epnum);
  uint8_t  (*SOF)              (struct _USBD_HandleTypeDef *pdev);
  uint8_t  (*IsoINIncomplete)  (struct _USBD_HandleTypeDef *pdev , uint8_t epnum);
  uint8_t  (*IsoOUTIncomplete) (struct _USBD_HandleTypeDef *pdev , uint8_t epnum);

  uint8_t  *(*GetHSConfigDescriptor)(uint16_t *length);
  uint8_t  *(*GetFSConfigDescriptor)(uint16_t *length);
  uint8_t  *(*GetOtherSpeedConfigDescriptor)(uint16_t *length);
  uint8_t  *(*GetDeviceQualifierDescriptor)(uint16_t *length);
#if (USBD_SUPPORT_USER_STRING == 1U)
  uint8_t  *(*GetUsrStrDescriptor)(struct _USBD_HandleTypeDef *pdev ,uint8_t index,  uint16_t *length);
#endif

} USBD_ClassTypeDef;

/* Following USB Device Speed */
typedef enum
{
  USBD_SPEED_HIGH  = 0U,
  USBD_SPEED_FULL  = 1U,
  USBD_SPEED_LOW   = 2U,
}USBD_SpeedTypeDef;

/* Following USB Device status */
typedef enum {
  USBD_OK   = 0U,
  USBD_BUSY,
  USBD_FAIL,
}USBD_StatusTypeDef;

/* USB Device descriptors structure */
typedef struct
{
  uint8_t  *(*GetDeviceDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetLangIDStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetManufacturerStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetProductStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetSerialStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetConfigurationStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
  uint8_t  *(*GetInterfaceStrDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
#if (USBD_LPM_ENABLED == 1U)
  uint8_t  *(*GetBOSDescriptor)( USBD_SpeedTypeDef speed , uint16_t *length);
#endif
} USBD_DescriptorsTypeDef;

/* USB Device handle structure */
typedef struct
{
  uint32_t                status;
  uint32_t                is_used;
  uint32_t                total_length;
  uint32_t                rem_length;
  uint32_t                maxpacket;
} USBD_EndpointTypeDef;

/* USB Device handle structure */
typedef struct _USBD_HandleTypeDef
{
  uint8_t                 id;
  uint32_t                dev_config;
  uint32_t                dev_default_config;
  uint32_t                dev_config_status;
  USBD_SpeedTypeDef       dev_speed;
  USBD_EndpointTypeDef    ep_in[15];
  USBD_EndpointTypeDef    ep_out[15];
  uint32_t                ep0_state;
  uint32_t                ep0_data_len;
  uint8_t                 dev_state;
  uint8_t                 dev_old_state;
  uint8_t                 dev_address;
  uint8_t                 dev_connection_status;
  uint8_t                 dev_test_mode;
  uint32_t                dev_remote_wakeup;

  USBD_SetupReqTypedef    request;
  USBD_DescriptorsTypeDef *pDesc;
  USBD_ClassTypeDef       *pClass;
  void                    *pClassData;
  void                    *pUserData;
  void                    *pData;
} USBD_HandleTypeDef;

/**
  * @}
  */



/** @defgroup USBD_DEF_Exported_Macros
  * @{
  */
#define  SWAPBYTE(addr)        (((uint16_t)(*((uint8_t *)(addr)))) + \
                               (((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))

#define LOBYTE(x)  ((uint8_t)(x & 0x00FFU))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00U) >> 8U))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))


#if  defined ( __GNUC__ )
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */


/* In HS mode and when the DMA is used, all variables and data structures dealing
   with the DMA during the transaction process should be 4-bytes aligned */

#if defined   (__GNUC__)        /* GNU Compiler */
  #define __ALIGN_END    __attribute__ ((aligned (4)))
  #define __ALIGN_BEGIN
#else
  #define __ALIGN_END
  #if defined   (__CC_ARM)      /* ARM Compiler */
    #define __ALIGN_BEGIN    __align(4)
  #elif defined (__ICCARM__)    /* IAR Compiler */
    #define __ALIGN_BEGIN
  #elif defined  (__TASKING__)  /* TASKING Compiler */
    #define __ALIGN_BEGIN    __align(4)
  #endif /* __CC_ARM */
#endif /* __GNUC__ */


/**
  * @}
  */

/** @defgroup USBD_DEF_Exported_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_DEF_Exported_FunctionsPrototype
  * @{
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_DEF_H */

/**
  * @}
  */

/**
* @}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
