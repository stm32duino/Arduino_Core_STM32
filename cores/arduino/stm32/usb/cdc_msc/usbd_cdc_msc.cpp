/**
  ******************************************************************************
  * @file    usbd_template.c
  * @author  MCD Application Team
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *
  *          ===================================================================
  *                                COMPOSITE Class Description
  *          ===================================================================
  *
  *
  *
  *
  *
  *
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *
  *
  *  @endverbatim
  *
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

#include "usbd_ep_conf.h"

#ifdef USBCON
#ifdef USBD_USE_CDC_MSC

#include "usbd_cdc_msc.h"
#include "usbd_ctlreq.h"

static uint8_t  USBD_COMPOSITE_Init(USBD_HandleTypeDef *pdev,
                                    uint8_t cfgidx);

static uint8_t  USBD_COMPOSITE_DeInit(USBD_HandleTypeDef *pdev,
                                      uint8_t cfgidx);

static uint8_t  USBD_COMPOSITE_Setup(USBD_HandleTypeDef *pdev,
                                     USBD_SetupReqTypedef *req);

static uint8_t  *USBD_COMPOSITE_GetHSCfgDesc(uint16_t *length);

static uint8_t  *USBD_COMPOSITE_GetFSCfgDesc(uint16_t *length);

static uint8_t  *USBD_COMPOSITE_GetOtherSpeedCfgDesc(uint16_t *length);

static uint8_t  *USBD_COMPOSITE_GetDeviceQualifierDesc(uint16_t *length);

static uint8_t  USBD_COMPOSITE_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_COMPOSITE_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_COMPOSITE_EP0_RxReady(USBD_HandleTypeDef *pdev);


USBD_ClassTypeDef  USBD_CDC_MSC = {
  USBD_COMPOSITE_Init,
  USBD_COMPOSITE_DeInit,
  USBD_COMPOSITE_Setup,
  nullptr,
  USBD_COMPOSITE_EP0_RxReady,
  USBD_COMPOSITE_DataIn,
  USBD_COMPOSITE_DataOut,
  nullptr,
  nullptr,
  nullptr,
  USBD_COMPOSITE_GetHSCfgDesc,
  USBD_COMPOSITE_GetFSCfgDesc,
  USBD_COMPOSITE_GetOtherSpeedCfgDesc,
  USBD_COMPOSITE_GetDeviceQualifierDesc,
};


#define EP_ATTR_BULK      0x02
#define EP_ATTR_INTERRUPT 0x03

#define IF_CLASS_COMM     0x02
#define IF_CLASS_CDC      0x0A
#define IF_CLASS_MSC      0x08

#define IF_SUBCLASS_NONE              0x00
#define IF_SUBCLASS_ACM               0x02
#define IF_SUBCLASS_SCSI_TRANSPARENT  0x06

#define ENDPOINT_DESCRIPTOR(_EP_ADDR, _ATTR, _PACKET_SIZE, _BINTERVAL) \
  0x07,                           /* bLength: Endpoint Descriptor size */ \
  USB_DESC_TYPE_ENDPOINT,         /* bDescriptorType: Endpoint */ \
  _EP_ADDR,                       /* bEndpointAddress */ \
  _ATTR,                          /* bmAttributes: Interrupt */ \
  LOBYTE(_PACKET_SIZE),           /* wMaxPacketSize: */ \
  HIBYTE(_PACKET_SIZE), \
  _BINTERVAL                      /* bInterval: */


/* ACM Interface Descriptor */
#define INTERFACE_DESCRIPTOR(_IF_NUM, _EP_COUNT, _CLASS, _SUBCLASS, _PROT) \
  0x09,   /* bLength: Interface Descriptor size */ \
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */ \
  /* Interface descriptor type */ \
  _IF_NUM,   /* bInterfaceNumber: Number of Interface */ \
  0x00,   /* bAlternateSetting: Alternate setting */ \
  _EP_COUNT,   /* bNumEndpoints: One endpoints used */ \
  _CLASS,   /* bInterfaceClass: Communication Interface Class */ \
  _SUBCLASS,   /* bInterfaceSubClass: Abstract Control Model */ \
  _PROT,   /* bInterfaceProtocol: Common AT commands */ \
  0x05   /* iInterface: */



#define USB_DESC_TYPE_INTERFACE_ASSOC_DESC        0x0B

#define CONFIGURATION_DESCRIPTOR() \
  0x09, /* bLength: Configuation Descriptor size */   \
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */ \
  USB_CDC_MSC_CONFIG_DESC_SIZ, /* wTotalLength: Bytes returned */   \
  0x00,                                               \
  0x03, /*bNumInterfaces: 3 interface*/               \
  0x01, /*bConfigurationValue: Configuration value*/  \
  0x02, /*iConfiguration: Index of string descriptor describing the configuration*/ \
  0xC0, /*bmAttributes: bus powered and Supports Remote Wakeup */ \
  0x32  /*MaxPower 100 mA: this current is used for detecting Vbus*/
/* 09 */

/******** IAD should be positioned just before the CDC interfaces ******
          IAD to associate the two CDC interfaces */
#define IAD_DESCRIPTOR() \
  0x08, /* bLength: Interface Descriptor size */  \
  USB_DESC_TYPE_INTERFACE_ASSOC_DESC, /* bDescriptorType: Interface */  \
  0x00, /* bFirstInterface */     \
  0x02, /* bInterfaceCount */     \
  0x02, /* bFunctionClass */      \
  0x02, /* bFunctionSubClass */   \
  0x01, /* bFunctionProtocol */   \
  0x04    /* iFunction (Index of string descriptor describing this function) */
/* 08 */

/* ACM Interface Descriptor */
#define ACM_INTERFACE_DESCRIPTOR() INTERFACE_DESCRIPTOR(CDC_ACM_INTERFACE, 0x01, IF_CLASS_COMM, IF_SUBCLASS_ACM, 0x01)

/* Header Functional Descriptor */
#define ACM_HEADER_FUNCTIONAL_DESCRIPTOR() \
  0x05,   /* bLength: Endpoint Descriptor size */ \
  0x24,   /* bDescriptorType: CS_INTERFACE */ \
  0x00,   /* bDescriptorSubtype: Header Func Desc */ \
  0x10,   /* bcdCDC: spec release number */ \
  0x01

/* ACM Call Management Functional Descriptor */
#define ACM_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR() \
  0x05,   /* bFunctionLength */ \
  0x24,   /* bDescriptorType: CS_INTERFACE */ \
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */ \
  0x00,   /* bmCapabilities: D0+D1 */ \
  CDC_COM_INTERFACE   /* bDataInterface: 1 */ \

/* ACM Functional Descriptor */
#define ACM_FUNCTIONAL_DESCRIPTOR() \
  0x04,   /* bFunctionLength */ \
  0x24,   /* bDescriptorType: CS_INTERFACE */ \
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */ \
  0x02    /* bmCapabilities */

#define ACM_UNION_FUNCTIONAL_DESCRIPTOR() \
  0x05,   /* bFunctionLength */ \
  0x24,   /* bDescriptorType: CS_INTERFACE */ \
  0x06,   /* bDescriptorSubtype: Union func desc */ \
  CDC_ACM_INTERFACE,   /* bMasterInterface: Communication class interface */ \
  CDC_COM_INTERFACE   /* bSlaveInterface0: Data Class Interface */

#define ACM_EP_DESCRIPTOR(_BINTERVAL) ENDPOINT_DESCRIPTOR(CDC_CMD_EP, EP_ATTR_INTERRUPT, CDC_CMD_PACKET_SIZE, _BINTERVAL)

#define CDC_INTERFACE_DESCRIPTOR() INTERFACE_DESCRIPTOR(CDC_COM_INTERFACE, 0x02, IF_CLASS_CDC, IF_SUBCLASS_NONE, 0x00)
#define CDC_EP_OUT_DESCRIPTOR(_PACKET_SIZE) ENDPOINT_DESCRIPTOR(CDC_OUT_EP, EP_ATTR_BULK, _PACKET_SIZE, 0x00)
#define CDC_EP_IN_DESCRIPTOR(_PACKET_SIZE) ENDPOINT_DESCRIPTOR(CDC_IN_EP, EP_ATTR_BULK, _PACKET_SIZE, 0x00)

#define MSC_INTERFACE_DESCRIPTOR() INTERFACE_DESCRIPTOR(MSC_INTERFACE, 0x02, IF_CLASS_MSC, IF_SUBCLASS_SCSI_TRANSPARENT, 0x50)
#define MSC_EP_IN_DESCRIPTOR(_PACKET_SIZE) ENDPOINT_DESCRIPTOR(MSC_EPIN_ADDR, EP_ATTR_BULK, _PACKET_SIZE, 0x00)
#define MSC_EP_OUT_DESCRIPTOR(_PACKET_SIZE) ENDPOINT_DESCRIPTOR(MSC_EPOUT_ADDR, EP_ATTR_BULK, _PACKET_SIZE, 0x00)


#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif


/* USB COMPOSITE device Configuration Descriptor */
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
static uint8_t USBD_COMPOSITE_HSCfgDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] = {
  CONFIGURATION_DESCRIPTOR(),
  IAD_DESCRIPTOR(),

  ACM_INTERFACE_DESCRIPTOR(),
  ACM_HEADER_FUNCTIONAL_DESCRIPTOR(),
  ACM_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR(),
  ACM_FUNCTIONAL_DESCRIPTOR(),
  ACM_UNION_FUNCTIONAL_DESCRIPTOR(),
  ACM_EP_DESCRIPTOR(CDC_HS_BINTERVAL),

  CDC_INTERFACE_DESCRIPTOR(),
  CDC_EP_OUT_DESCRIPTOR(CDC_DATA_HS_MAX_PACKET_SIZE),
  CDC_EP_IN_DESCRIPTOR(CDC_DATA_HS_MAX_PACKET_SIZE),

  MSC_INTERFACE_DESCRIPTOR(),
  MSC_EP_IN_DESCRIPTOR(MSC_MAX_HS_PACKET),
  MSC_EP_OUT_DESCRIPTOR(MSC_MAX_HS_PACKET)
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
/* USB COMPOSITE device Configuration Descriptor */
static uint8_t USBD_COMPOSITE_FSCfgDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] = {
  CONFIGURATION_DESCRIPTOR(),
  IAD_DESCRIPTOR(),

  ACM_INTERFACE_DESCRIPTOR(),
  ACM_HEADER_FUNCTIONAL_DESCRIPTOR(),
  ACM_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR(),
  ACM_FUNCTIONAL_DESCRIPTOR(),
  ACM_UNION_FUNCTIONAL_DESCRIPTOR(),
  ACM_EP_DESCRIPTOR(CDC_FS_BINTERVAL),

  CDC_INTERFACE_DESCRIPTOR(),
  CDC_EP_OUT_DESCRIPTOR(CDC_DATA_FS_MAX_PACKET_SIZE),
  CDC_EP_IN_DESCRIPTOR(CDC_DATA_FS_MAX_PACKET_SIZE),

  MSC_INTERFACE_DESCRIPTOR(),
  MSC_EP_IN_DESCRIPTOR(MSC_MAX_FS_PACKET),
  MSC_EP_OUT_DESCRIPTOR(MSC_MAX_FS_PACKET)
};


#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
/* USB COMPOSITE device Configuration Descriptor */
static uint8_t USBD_COMPOSITE_OtherSpeedCfgDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] = {
  CONFIGURATION_DESCRIPTOR(),
  IAD_DESCRIPTOR(),

  ACM_INTERFACE_DESCRIPTOR(),
  ACM_HEADER_FUNCTIONAL_DESCRIPTOR(),
  ACM_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR(),
  ACM_FUNCTIONAL_DESCRIPTOR(),
  ACM_UNION_FUNCTIONAL_DESCRIPTOR(),
  ACM_EP_DESCRIPTOR(CDC_FS_BINTERVAL),

  CDC_INTERFACE_DESCRIPTOR(),
  CDC_EP_OUT_DESCRIPTOR(CDC_DATA_FS_MAX_PACKET_SIZE),
  CDC_EP_IN_DESCRIPTOR(CDC_DATA_FS_MAX_PACKET_SIZE),

  MSC_INTERFACE_DESCRIPTOR(),
  MSC_EP_IN_DESCRIPTOR(MSC_MAX_FS_PACKET),
  MSC_EP_OUT_DESCRIPTOR(MSC_MAX_FS_PACKET)
};


#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
/* USB Standard Device Descriptor */
static uint8_t USBD_COMPOSITE_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] = {
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

int cdcMscInitialised;

/**
  * @brief  USBD_COMPOSITE_Init
  *         Initialize the COMPOSITE interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_Init(USBD_HandleTypeDef *pdev,
                                    uint8_t cfgidx)
{
  USBD_MSC.Init(pdev, cfgidx);

  USBD_CDC.Init(pdev, cfgidx);

  pdev->pClassData = &cdcMscInitialised;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_COMPOSITE_Init
  *         DeInitialize the COMPOSITE layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_DeInit(USBD_HandleTypeDef *pdev,
                                      uint8_t cfgidx)
{
  USBD_MSC.DeInit(pdev, cfgidx);

  USBD_CDC.DeInit(pdev, cfgidx);

  if (pdev->pClassData == &cdcMscInitialised) {
    pdev->pClassData = nullptr;
  }

  return USBD_OK;
}

/**
  * @brief  USBD_COMPOSITE_Setup
  *         Handle the COMPOSITE specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_Setup(USBD_HandleTypeDef *pdev,
                                     USBD_SetupReqTypedef *req)
{
  switch (req->bmRequest & USB_REQ_RECIPIENT_MASK) {
    case USB_REQ_RECIPIENT_INTERFACE:
      switch (req->wIndex) {
        case CDC_ACM_INTERFACE:
        case CDC_COM_INTERFACE:
          return USBD_CDC.Setup(pdev, req);
          break;

        case MSC_INTERFACE:
          return USBD_MSC.Setup(pdev, req);
          break;

        // invalid interface
        default:
          return USBD_FAIL;
      }
      break;

    case USB_REQ_RECIPIENT_ENDPOINT:
      switch (req->wIndex) {
        case CDC_IN_EP:
        case CDC_OUT_EP:
        case CDC_CMD_EP:
          return USBD_CDC.Setup(pdev, req);

        case MSC_EPIN_ADDR:
        case MSC_EPOUT_ADDR:
          return USBD_MSC.Setup(pdev, req);

        // invalid endpoint
        default:
          return USBD_FAIL;
      }
      break;

    default:
      break;
  }

  return USBD_OK;
}


/**
  * @brief  USBD_COMPOSITE_GetHSCfgDesc
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_COMPOSITE_GetHSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_COMPOSITE_HSCfgDesc);
  return USBD_COMPOSITE_HSCfgDesc;
}

/**
  * @brief  USBD_COMPOSITE_GetFSCfgDesc
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_COMPOSITE_GetFSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_COMPOSITE_FSCfgDesc);
  return USBD_COMPOSITE_FSCfgDesc;
}

/**
  * @brief  USBD_COMPOSITE_GetOtherSpeedCfgDesc
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_COMPOSITE_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_COMPOSITE_OtherSpeedCfgDesc);
  return USBD_COMPOSITE_OtherSpeedCfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_COMPOSITE_DeviceQualifierDescriptor(uint16_t *length)
{
  *length = sizeof(USBD_COMPOSITE_DeviceQualifierDesc);
  return USBD_COMPOSITE_DeviceQualifierDesc;
}


/**
  * @brief  USBD_COMPOSITE_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_DataIn(USBD_HandleTypeDef *pdev,
                                      uint8_t epnum)
{
  switch (epnum) {
    case CDC_IN_EP:
    case CDC_CMD_EP:
    case CDC_OUT_EP:
      return USBD_CDC.DataIn(pdev, epnum);

    case MSC_EPIN_ADDR:
    case MSC_EPOUT_ADDR:
      return USBD_MSC.DataIn(pdev, epnum);

    // invalid endpoint
    default:
      return USBD_FAIL;
  }
}

/**
  * @brief  USBD_COMPOSITE_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
  // only needed by CDC
  return USBD_CDC.EP0_RxReady(pdev);
}

/**
  * @brief  USBD_COMPOSITE_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_COMPOSITE_DataOut(USBD_HandleTypeDef *pdev,
                                       uint8_t epnum)
{
  switch (epnum) {
    case CDC_IN_EP:
    case CDC_CMD_EP:
    case CDC_OUT_EP:
      return USBD_CDC.DataOut(pdev, epnum);

    case MSC_EPIN_ADDR:
    case MSC_EPOUT_ADDR:
      return USBD_MSC.DataOut(pdev, epnum);

    // invalid endpoint
    default:
      return USBD_FAIL;
  }
}

/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_COMPOSITE_GetDeviceQualifierDesc(uint16_t *length)
{
  *length = sizeof(USBD_COMPOSITE_DeviceQualifierDesc);
  return USBD_COMPOSITE_DeviceQualifierDesc;
}

#endif /* USBD_USE_MSC_CLASS */
#endif /* USBCON */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
