/**
  ******************************************************************************
  * @file    usbd_printer.c
  * @author  MCD Application Team
  * @brief   This file provides the high layer firmware functions to manage the
  *          following functionalities of the USB printer Class:
  *           - Initialization and Configuration of high and low layer
  *           - Enumeration as printer Device (and enumeration for each implemented memory interface)
  *           - OUT data transfer
  *           - Command OUT transfer (class requests management)
  *           - Error management
  *
  *  @verbatim
  *
  *          ===================================================================
  *                                PRINTER Class Driver Description
  *          ===================================================================
  *           This driver manages the "Universal Serial Bus Class Definitions for Communications Devices
  *           Revision 1.2 November 16, 2007" and the sub-protocol specification of "Universal Serial Bus
  *           printer Class Subclass Specification for PSTN Devices Revision 1.2 February 9, 2007"
  *           This driver implements the following aspects of the specification:
  *             - Device descriptor management
  *             - Configuration descriptor management
  *             - Enumeration as printer device with 2 data endpoints (IN and OUT)
  *             - Control Requests management (PRNT_GET_DEVICE_ID,PRNT_GET_PORT_STATUS,PRNT_SOFT_RESET)
  *             - protocol USB_PRNT_BIDIRECTIONAL
  *
  *
  *
  *           These aspects may be enriched or modified for a specific user application.
  *
  *            This driver doesn't implement the following aspects of the specification
  *            (but it is possible to manage these features with some modifications on this driver):
  *             - Any class-specific aspect relative to communication classes should be managed by user application.
  *             - All communication classes other than PSTN are not managed
  *
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                     www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_printer.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_PRNT
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_PRNT_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */
static uint32_t usbd_PRNT_altset = 0U;

/** @defgroup USBD_PRNT_Private_Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup USBD_PRNT_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_PRNT_Private_FunctionPrototypes
  * @{
  */
static uint8_t USBD_PRNT_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_PRNT_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_PRNT_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);
static uint8_t USBD_PRNT_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_PRNT_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t *USBD_PRNT_GetFSCfgDesc(uint16_t *length);
static uint8_t *USBD_PRNT_GetHSCfgDesc(uint16_t *length);
static uint8_t *USBD_PRNT_GetOtherSpeedCfgDesc(uint16_t *length);
static uint8_t *USBD_PRNT_GetOtherSpeedCfgDesc(uint16_t *length);
uint8_t *USBD_PRNT_GetDeviceQualifierDescriptor(uint16_t *length);

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_PRNT_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/**
  * @}
  */

/** @defgroup USBD_PRNT_Private_Variables
  * @{
  */

/* PRNT interface class callbacks structure */
USBD_ClassTypeDef USBD_PRNT =
{
  USBD_PRNT_Init,
  USBD_PRNT_DeInit,
  USBD_PRNT_Setup,
  NULL,
  NULL,
  USBD_PRNT_DataIn,
  USBD_PRNT_DataOut,
  NULL,
  NULL,
  NULL,
  USBD_PRNT_GetHSCfgDesc,
  USBD_PRNT_GetFSCfgDesc,
  USBD_PRNT_GetOtherSpeedCfgDesc,
  USBD_PRNT_GetDeviceQualifierDescriptor,
};

/* USB PRNT device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_PRNT_CfgHSDesc[] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,                                /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,         /* bDescriptorType: Configuration */
  USB_PRNT_CONFIG_DESC_SIZ,            /* wTotalLength:no of returned bytes */
  0x00,
  0x01,                                /* bNumInterfaces: 1 interface */
  0x01,                                /* bConfigurationValue: Configuration value */
  0x00,                                /* iConfiguration: Index of string descriptor describing the configuration */
#if (USBD_SELF_POWERED == 1U)
  0xC0,                                /* bmAttributes: Self Powered according to user configuration */
#else
  0x80,                                /* bmAttributes: Bus Powered according to user configuration */
#endif
  USBD_MAX_POWER,                      /* MaxPower in mA */

  /* Interface Descriptor */
  0x09,                                /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,             /* bDescriptorType: Interface */
  0x00,                                /* bInterfaceNumber: Number of Interface */
  0x00,                                /* bAlternateSetting: Alternate setting */
  0x02,                                /* bNumEndpoints: 2 endpoints used */
  0x07,                                /* bInterfaceClass: Communication Interface Class */
  0x01,                                /* bInterfaceSubClass: Abstract Control Model */
  USB_PRNT_BIDIRECTIONAL,              /* bDeviceProtocol */
  0x00,                                /* iInterface */

  /* Endpoint IN Descriptor */
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_IN_EP,                          /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_HS_IN_PACKET_SIZE), /* wMaxPacketSize */
  HIBYTE(PRNT_DATA_HS_IN_PACKET_SIZE),
  0x00,                                /* bInterval */

  /* Endpoint OUT Descriptor */
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_OUT_EP,                         /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_HS_OUT_PACKET_SIZE),/* wMaxPacketSize */
  HIBYTE(PRNT_DATA_HS_OUT_PACKET_SIZE),
  0x00                                 /* bInterval */
};


/* USB PRNT device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_PRNT_CfgFSDesc[] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,                                /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,         /* bDescriptorType: Configuration */
  USB_PRNT_CONFIG_DESC_SIZ,            /* wTotalLength:no of returned bytes */
  0x00,
  0x01,                                /* bNumInterfaces: 1 interface */
  0x01,                                /* bConfigurationValue: Configuration value */
  0x00,                                /* iConfiguration: Index of string descriptor describing the configuration */
#if (USBD_SELF_POWERED == 1U)
  0xC0,                                /* bmAttributes: Self Powered according to user configuration */
#else
  0x80,                                /* bmAttributes: Bus Powered according to user configuration */
#endif
  USBD_MAX_POWER,                      /* MaxPower in mA */

  /*Interface Descriptor */
  0x09,                                /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,             /* bDescriptorType: Interface */
  0x00,                                /* bInterfaceNumber: Number of Interface */
  0x00,                                /* bAlternateSetting: Alternate setting */
  0x02,                                /* bNumEndpoints: 2 endpoints used */
  0x07,                                /* bInterfaceClass: Communication Interface Class */
  0x01,                                /* bInterfaceSubClass: Abstract Control Model */
  USB_PRNT_BIDIRECTIONAL,              /* bDeviceProtocol */
  0x00,                                /* iInterface */

  /*Endpoint IN Descriptor*/
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_IN_EP,                          /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_FS_IN_PACKET_SIZE), /* wMaxPacketSize */
  HIBYTE(PRNT_DATA_FS_IN_PACKET_SIZE),
  0x00,                                /* bInterval */

  /*Endpoint OUT Descriptor*/
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_OUT_EP,                         /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_FS_OUT_PACKET_SIZE),/* wMaxPacketSize */
  HIBYTE(PRNT_DATA_FS_OUT_PACKET_SIZE),
  0x00                                 /* bInterval */
};

__ALIGN_BEGIN static uint8_t USBD_PRNT_OtherSpeedCfgDesc[] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,                                /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,         /* bDescriptorType: Configuration */
  USB_PRNT_CONFIG_DESC_SIZ,            /* wTotalLength:no of returned bytes */
  0x00,
  0x01,                                /* bNumInterfaces: 1 interface */
  0x01,                                /* bConfigurationValue: Configuration value */
  0x00,                                /* iConfiguration: Index of string descriptor describing the configuration */
#if (USBD_SELF_POWERED == 1U)
  0xC0,                                /* bmAttributes: Self Powered according to user configuration */
#else
  0x80,                                /* bmAttributes: Bus Powered according to user configuration */
#endif
  USBD_MAX_POWER,                      /* MaxPower in mA */

  /*Interface Descriptor */
  0x09,                                /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,             /* bDescriptorType: Interface */
  0x00,                                /* bInterfaceNumber: Number of Interface */
  0x00,                                /* bAlternateSetting: Alternate setting */
  0x02,                                /* bNumEndpoints: 2 endpoints used */
  0x07,                                /* bInterfaceClass: Communication Interface Class */
  0x01,                                /* bInterfaceSubClass: Abstract Control Model */
  USB_PRNT_BIDIRECTIONAL,              /* bDeviceProtocol */
  0x00,                                /* iInterface */

  /*Endpoint IN Descriptor*/
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_IN_EP,                          /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_FS_IN_PACKET_SIZE), /* wMaxPacketSize */
  HIBYTE(PRNT_DATA_FS_IN_PACKET_SIZE),
  0x00,                                /* bInterval */

  /*Endpoint OUT Descriptor*/
  0x07,                                /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,              /* bDescriptorType: Endpoint */
  PRNT_OUT_EP,                         /* bEndpointAddress */
  0x02,                                /* bmAttributes: Bulk */
  LOBYTE(PRNT_DATA_FS_OUT_PACKET_SIZE),/* wMaxPacketSize */
  HIBYTE(PRNT_DATA_FS_OUT_PACKET_SIZE),
  0x00                                 /* bInterval */
};

/**
  * @}
  */

/** @defgroup USBD_PRNT_Private_Functions
  * @{
  */

/**
  * @brief  USBD_PRNT_Init
  *         Initialize the PRNT interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_PRNT_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  USBD_PRNT_HandleTypeDef *hPRNT;
  uint16_t mps;
  hPRNT = (USBD_PRNT_HandleTypeDef *)USBD_malloc(sizeof(USBD_PRNT_HandleTypeDef));

  if (hPRNT == NULL)
  {
    pdev->pClassData = NULL;
    return (uint8_t)USBD_EMEM;
  }

  /* Setup the pClassData pointer */
  pdev->pClassData = (void *)hPRNT;

  /* Setup the max packet size according to selected speed */
  if (pdev->dev_speed == USBD_SPEED_HIGH)
  {
    mps = PRNT_DATA_HS_IN_PACKET_SIZE;
  }
  else
  {
    mps = PRNT_DATA_FS_IN_PACKET_SIZE;
  }

  /* Open EP IN */
  (void)USBD_LL_OpenEP(pdev, PRNT_IN_EP, USBD_EP_TYPE_BULK, mps);

  /* Set endpoint as used */
  pdev->ep_in[PRNT_IN_EP & 0xFU].is_used = 1U;

  /* Open EP OUT */
  (void)USBD_LL_OpenEP(pdev, PRNT_OUT_EP, USBD_EP_TYPE_BULK, mps);

  /* Set endpoint as used */
  pdev->ep_out[PRNT_OUT_EP & 0xFU].is_used = 1U;

  /* Init  physical Interface components */
  ((USBD_PRNT_ItfTypeDef *)pdev->pUserData)->Init();

  /* Prepare Out endpoint to receive next packet */
  (void)USBD_LL_PrepareReceive(pdev, PRNT_OUT_EP, hPRNT->RxBuffer, mps);

  /* End of initialization phase */
  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_PRNT_DeInit
  *         DeInitialize the PRNT layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_PRNT_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  /* Close EP IN */
  (void)USBD_LL_CloseEP(pdev, PRNT_IN_EP);
  pdev->ep_in[PRNT_IN_EP & 0xFU].is_used = 0U;

  /* Close EP OUT */
  (void)USBD_LL_CloseEP(pdev, PRNT_OUT_EP);
  pdev->ep_out[PRNT_OUT_EP & 0xFU].is_used = 0U;

  /* DeInit physical Interface components */
  if (pdev->pClassData != NULL)
  {
    ((USBD_PRNT_ItfTypeDef *)pdev->pUserData)->DeInit();
    (void)USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }

  return 0U;
}

/**
  * @brief  USBD_PRNT_Setup
  *         Handle the PRNT specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t USBD_PRNT_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  USBD_PRNT_HandleTypeDef   *hPRNT = (USBD_PRNT_HandleTypeDef *)pdev->pClassData;
  USBD_PRNT_ItfTypeDef      *hPRNTitf = (USBD_PRNT_ItfTypeDef *)pdev->pUserData;

  USBD_StatusTypeDef ret = USBD_OK;
  uint16_t status_info = 0U;
  uint16_t data_length;

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
    case USB_REQ_TYPE_CLASS :
      if (req->wLength != 0U)
      {
        data_length = MIN(req->wLength, PRNT_DATA_HS_MAX_PACKET_SIZE);

        if ((req->bmRequest & 0x80U) != 0U)
        {
          /* Call the User class interface function to process the command */
          hPRNTitf->Control_req(req->bRequest, (uint8_t *)hPRNT->data, &data_length);

          /* Return the answer to host */
          (void) USBD_CtlSendData(pdev, (uint8_t *)hPRNT->data, data_length);
        }
        else
        {
          /* Prepare for control data reception */
          (void) USBD_CtlPrepareRx(pdev, (uint8_t *)hPRNT->data, data_length);
        }
      }
      else
      {
        data_length = 0U;
        hPRNTitf->Control_req(req->bRequest, (uint8_t *)req, &data_length);
      }
      break;

    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest)
      {
        case USB_REQ_GET_STATUS:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_GET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&usbd_PRNT_altset, 1U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE:
          if (pdev->dev_state != USBD_STATE_CONFIGURED)
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_CLEAR_FEATURE:
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
      break;
  }

  return (uint8_t)ret;
}

/**
  * @brief  USBD_PRNT_DataIn
  *         Data sent on non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t USBD_PRNT_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_PRNT_HandleTypeDef *hPRNT = (USBD_PRNT_HandleTypeDef *)pdev->pClassData;
  PCD_HandleTypeDef *hpcd = pdev->pData;

  if (hPRNT == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  if ((pdev->ep_in[epnum].total_length > 0U) &&
      ((pdev->ep_in[epnum].total_length % hpcd->IN_ep[epnum].maxpacket) == 0U))
  {
    /* Update the packet total length */
    pdev->ep_in[epnum].total_length = 0U;

    /* Send ZLP */
    (void) USBD_LL_Transmit(pdev, epnum, NULL, 0U);
  }
  else
  {
    hPRNT->TxState = 0U;
  }

  return (uint8_t)USBD_OK;
}
/**
  * @brief  USBD_PRNT_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t USBD_PRNT_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_PRNT_HandleTypeDef *hPRNT = (USBD_PRNT_HandleTypeDef *)pdev->pClassData;

  if (hPRNT == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  /* Get the received data length */
  hPRNT->RxLength = USBD_LL_GetRxDataSize(pdev, epnum);

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the application Xfer */
  ((USBD_PRNT_ItfTypeDef *)pdev->pUserData)->Receive(hPRNT->RxBuffer, &hPRNT->RxLength);

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_PRNT_GetFSCfgDesc
  *         Return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_PRNT_GetFSCfgDesc(uint16_t *length)
{
  *length = (uint16_t) sizeof(USBD_PRNT_CfgFSDesc);
  return USBD_PRNT_CfgFSDesc;
}

/**
  * @brief  USBD_PRNT_GetHSCfgDesc
  *         Return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_PRNT_GetHSCfgDesc(uint16_t *length)
{
  *length = (uint16_t) sizeof(USBD_PRNT_CfgHSDesc);
  return USBD_PRNT_CfgHSDesc;
}

/**
  * @brief  USBD_PRNT_GetOtherSpeedCfgDesc
  *         Return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_PRNT_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = (uint16_t) sizeof(USBD_PRNT_OtherSpeedCfgDesc);
  return USBD_PRNT_OtherSpeedCfgDesc;
}

/**
  * @brief  USBD_PRNT_GetDeviceQualifierDescriptor
  *         return Device Qualifier descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
uint8_t *USBD_PRNT_GetDeviceQualifierDescriptor(uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_PRNT_DeviceQualifierDesc);
  return USBD_PRNT_DeviceQualifierDesc;
}

/**
  * @brief  USBD_PRNT_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: Interface callbacks
  * @retval status
  */
uint8_t USBD_PRNT_RegisterInterface(USBD_HandleTypeDef *pdev, USBD_PRNT_ItfTypeDef *fops)
{
  /* Check if the fops pointer is valid */
  if (fops == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  /* Setup the fops pointer */
  pdev->pUserData = fops;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_PRNT_SetRxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Rx Buffer
  * @retval status
  */
uint8_t USBD_PRNT_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff)
{
  USBD_PRNT_HandleTypeDef *hPRNT = (USBD_PRNT_HandleTypeDef *) pdev->pClassData;

  hPRNT->RxBuffer = pbuff;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_PRNT_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t USBD_PRNT_ReceivePacket(USBD_HandleTypeDef *pdev)
{
  USBD_PRNT_HandleTypeDef *hPRNT = (USBD_PRNT_HandleTypeDef *)pdev->pClassData;

  if (hPRNT == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  if (pdev->dev_speed == USBD_SPEED_HIGH)
  {
    /* Prepare Out endpoint to receive next packet */
    (void)USBD_LL_PrepareReceive(pdev, PRNT_OUT_EP, hPRNT->RxBuffer,
                                 PRNT_DATA_HS_OUT_PACKET_SIZE);
  }
  else
  {
    /* Prepare Out endpoint to receive next packet */
    (void)USBD_LL_PrepareReceive(pdev, PRNT_OUT_EP, hPRNT->RxBuffer,
                                 PRNT_DATA_FS_OUT_PACKET_SIZE);
  }

  return (uint8_t)USBD_OK;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
