/**
  ******************************************************************************
  * @file    usbd_desc.c
  * @author  MCD Application Team
  * @brief   This file provides the USBD descriptors and string formatting method.
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

/**
  ******************************************************************************
  *
  * The composite MSC CDC USB device is mainly adapted from the GPSlogger
  * repository https://github.com/grafalex82/GPSLogger/tree/master/Libs/USB
  *
  * See the article "CDC + MSC USB Composite Device for STM32 HAL" (URL:
  * https://habr.com/en/post/335018/) for the theory behind the MSC CDC
  * composite device as implemented in the above repository.
  *
  * The composite MSC CDC USB device requires a modified USBD_HandleTypeDef
  * structure.  The MSC and CDC classes require dedicated data structures.
  *
  ******************************************************************************
  */

#if defined(USBCON) && defined(USBD_USE_CDC_COMPOSITE)
/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "utils.h"

#include "usbd_cdc.h"
#include "usbd_ctlreq.h"
#include "usbd_msc_cdc_composite.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if USBD_VID == 0x2341
  #define USBD_MANUFACTURER_STRING "Arduino LLC"
#elif USBD_VID == 0x2A03
#define USBD_MANUFACTURER_STRING "Arduino srl"
#elif USBD_VID == 0x0483
#define USBD_MANUFACTURER_STRING "STMicroelectronics"
#elif !defined(USB_MANUFACTURER)
// Fall through to unknown if no manufacturer name was provided in a macro
#define USBD_MANUFACTURER_STRING "Unknown"
#else
#define USBD_MANUFACTURER_STRING USB_MANUFACTURER
#endif

#define USBD_LANGID_STRING                0x409   /* 1033 US.S English */

#define USBD_CDC_PID                      0x5740  // 22336
#define USBD_CDC_PRODUCT_HS_STRING        CONCATS(USB_PRODUCT, "MSC & CDC in HS Mode")
#define USBD_CDC_PRODUCT_FS_STRING        CONCATS(USB_PRODUCT, "MSC & CDC in FS Mode")
#define USBD_CDC_CONFIGURATION_HS_STRING  CONCATS(USB_PRODUCT, "CDC Config")
#define USBD_CDC_INTERFACE_HS_STRING      CONCATS(USB_PRODUCT, "CDC Interface")
#define USBD_CDC_CONFIGURATION_FS_STRING  CONCATS(USB_PRODUCT, "CDC Config")
#define USBD_CDC_INTERFACE_FS_STRING      CONCATS(USB_PRODUCT, "CDC Interface")
#define USBD_MSC_INTERFACE_STRING         CONCATS(USB_PRODUCT, "MSC Interface")


/**
 *  Possible values of class
 */

#define  CDC_CLASS_DEVICE     0x02  //!< USB Communication Device Class
#define  CDC_CLASS_COMM       0x02  //!< CDC Communication Class Interface
#define  CDC_CLASS_DATA       0x0A  //!< CDC Data Class Interface
#define  CDC_CLASS_MULTI      0xEF  //!< CDC Multi-interface Function


//USB CDC Subclass IDs

#define  CDC_SUBCLASS_DLCM    0x01  // Direct Line Control Model
#define  CDC_SUBCLASS_ACM     0x02  // Abstract Control Model
#define  CDC_SUBCLASS_TCM     0x03  // Telephone Control Model
#define  CDC_SUBCLASS_MCCM    0x04  // Multi-Channel Control Model
#define  CDC_SUBCLASS_CCM     0x05  // CAPI Control Model
#define  CDC_SUBCLASS_ETH     0x06  // Ethernet Networking Control Model
#define  CDC_SUBCLASS_ATM     0x07  // ATM Networking Control Model

//USB CDC Communication Interface Protocol IDs

#define  CDC_PROTOCOL_V25TER  0x01  // Common AT commands


/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Common function */
uint8_t *USBD_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

/* Class specific */
uint8_t *USBD_CDC_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *USBD_Class_USRStringDesc(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);
#endif /* USB_SUPPORT_USER_STRING_DESC */

/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef CDC_Desc = {
  USBD_CDC_DeviceDescriptor,
  USBD_LangIDStrDescriptor,
  USBD_ManufacturerStrDescriptor,
  USBD_CDC_ProductStrDescriptor,
  USBD_SerialStrDescriptor,
  USBD_CDC_ConfigStrDescriptor,
  USBD_CDC_InterfaceStrDescriptor,
};


/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_CDC_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                      /* bLength */
  USB_DESC_TYPE_DEVICE,      /* bDescriptorType */
  0x00,                      /* bcdUSB (USB version, minor)*/
  0x02,                      /* bcdUSB (USB version, major)*/
  CDC_CLASS_MULTI,           /* bDeviceClass (MULTI 0xEF) */
  CDC_SUBCLASS_ACM,          /* bDeviceSubClass */
  CDC_PROTOCOL_V25TER,       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,          /* bMaxPacketSize */
  LOBYTE(USBD_VID),          /* idVendor */
  HIBYTE(USBD_VID),          /* idVendor */
  LOBYTE(USBD_CDC_PID),          /* idVendor */
  HIBYTE(USBD_CDC_PID),          /* idVendor */
  0x00,                      /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,          /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,      /* Index of product string */
  USBD_IDX_SERIAL_STR,       /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */

/* USB Standard Device Descriptor */
__ALIGN_BEGIN   uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
  USB_LEN_LANGID_STR_DESC,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING),
};

uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] = {
  USB_SIZ_STRING_SERIAL,
  USB_DESC_TYPE_STRING,
};

__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

/* Private functions ---------------------------------------------------------*/
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len);
static void Get_SerialNum(void);

/**
  * @brief  Returns the device descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_CDC_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_CDC_DeviceDesc);
  return (uint8_t *)USBD_CDC_DeviceDesc;
}

/**
  * @brief  Returns the LangID string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_LangIDDesc);
  return (uint8_t *)USBD_LangIDDesc;
}

/**
  * @brief  Returns the product string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_CDC_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CDC_PRODUCT_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CDC_PRODUCT_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the manufacturer string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

/**
  * @brief  Returns the serial number string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = USB_SIZ_STRING_SERIAL;

  /* Update the serial number string descriptor with the data from the unique ID*/
  Get_SerialNum();

  return (uint8_t *)USBD_StringSerial;
}

/**
  * @brief  Returns the configuration string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_CDC_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CDC_CONFIGURATION_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CDC_CONFIGURATION_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the interface string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_CDC_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CDC_INTERFACE_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CDC_INTERFACE_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the interface string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_MSC_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  USBD_GetString((uint8_t *)USBD_MSC_INTERFACE_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}



/**
  * @brief  Create the serial number string descriptor
  * @param  None
  * @retval None
  */
static void Get_SerialNum(void)
{

  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = *(uint32_t *)DEVICE_ID1;
  deviceserial1 = *(uint32_t *)DEVICE_ID2;
  deviceserial2 = *(uint32_t *)DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0) {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4);
  }
}

/**
  * @brief  Convert Hex 32Bits value into char
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
  uint8_t idx = 0;

  for (idx = 0 ; idx < len ; idx ++) {
    if (((value >> 28)) < 0xA) {
      pbuf[ 2 * idx] = (value >> 28) + '0';
    } else {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[ 2 * idx + 1] = 0;
  }
}





/**
 *  Composite MSC CDC
 *
 *  Source:
 *  https://github.com/grafalex82/GPSLogger/tree/master/Libs/USB/
 *  file: usbd_msc_cdc.c
 *
 *  Articles:
 *  https://weekly-geekly.github.io/articles/335018/index.html
 *
 *  Copyright??
 *
 *  License??
 *
 *  AUTHOR
 *
 */

/* Includes ------------------------------------------------------------------*/



/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_MSC_CDC
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_MSC_CDC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_MSC_CDC_Private_Defines
  * @{
  */

/** @defgroup MSC_CORE_Private_FunctionPrototypes
  * @{
  */



#if defined (__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif

#define USB_MSC_CDC_CONFIG_DESC_SIZ       98

/////////////////////////////////////////////////////////////////////////////
//  MSC_CDC_HS
/////////////////////////////////////////////////////////////////////////////

/* USB MSC+CDC device Configuration Descriptor */
uint8_t USBD_MSC_CDC_HSCfgDesc[USB_MSC_CDC_CONFIG_DESC_SIZ] = {
  0x09,        /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_MSC_CDC_CONFIG_DESC_SIZ, /* wTotalLength: Bytes returned */
  0x00,
  0x03,        /*bNumInterfaces: 3 interface*/
  0x01,        /*bConfigurationValue: Configuration value*/
  0x02,        /*iConfiguration: Index of string descriptor describing the configuration*/
  0xC0,        /*bmAttributes: bus powered and Supports Remote Wakeup */
  0x32,        /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 bytes */



  /******** IAD should be positioned just before the CDC interfaces ******
       IAD to associate the two CDC interfaces */

  0x08, /* bLength */
  0x0B, /* bDescriptorType */
  0x00, /* bFirstInterface */
  0x02, /* bInterfaceCount */
  0x02, /* bFunctionClass */
  0x02, /* bFunctionSubClass */
  0x01, /* bFunctionProtocol */
  0x04, /* iFunction (Index of string descriptor describing this function) */
  /* 08 bytes */

  /********************  CDC interfaces ********************/

  /*Interface Descriptor */
  0x09,  /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE, /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x01,  /* bNumEndpoints: One endpoints used */
  0x02,  /* bInterfaceClass: Communication Interface Class */
  0x02,  /* bInterfaceSubClass: Abstract Control Model */
  0x01,  /* bInterfaceProtocol: Common AT commands */
  0x05,  /* iInterface: */
  /* 09 bytes */

  /*Header Functional Descriptor*/
  0x05,  /* bLength: Endpoint Descriptor size */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x00,  /* bDescriptorSubtype: Header Func Desc */
  0x10,  /* bcdCDC: spec release number */
  0x01,
  /* 05 bytes */

  /*ACM Functional Descriptor*/
  0x04,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x02,  /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,  /* bmCapabilities */
  /* 04 bytes */

  /*Union Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x06,  /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_IDX,  /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_IDX + 1,  /* bSlaveInterface0: Data Class Interface */
  /* 05 bytes */

  /*Call Management Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x01,  /* bDescriptorSubtype: Call Management Func Desc */
  0x03,
  CDC_INTERFACE_IDX + 1,  /* bDataInterface: 1 */
  /* 05 bytes */



  /*Endpoint 2 Descriptor*/
  0x07,                         /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                   /* bEndpointAddress */
  0x03,                         /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x10,                         /* bInterval: */
  /* 07 bytes */

  /*Data class interface descriptor*/
  0x09,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,      /* bDescriptorType: */
  0x01,                         /* bInterfaceNumber: Number of Interface */
  0x00,                         /* bAlternateSetting: Alternate setting */
  0x02,                         /* bNumEndpoints: Two endpoints used */
  0x0A,                         /* bInterfaceClass: CDC */
  0x00,                         /* bInterfaceSubClass: */
  0x00,                         /* bInterfaceProtocol: */
  0x05,                         /* iInterface: */
  /* 09 bytes */

  /*Endpoint IN Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_IN_EP,                    /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00,                         /* bInterval */
  /* 07 bytes */

  /*Endpoint OUT Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                   /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00,                         /* bInterval: ignore for Bulk transfer */
  /* 07 bytes */



  /********************  Mass Storage interface ********************/
  0x09,  /* bLength: Interface Descriptor size */
  0x04,  /* bDescriptorType: */
  0x02,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x02,  /* bNumEndpoints*/
  0x08,  /* bInterfaceClass: MSC Class */
  0x06,  /* bInterfaceSubClass : SCSI transparent command set*/
  0x50,  /* nInterfaceProtocol */
  0x00, /* iInterface: */
  /* 09 bytes */

  /********************  Mass Storage Endpoints ********************/
  0x07,  /*Endpoint descriptor length = 7*/
  0x05,  /*Endpoint descriptor type */
  MSC_EPIN_ADDR,  /*Endpoint address (IN, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,  /*Polling interval in milliseconds */
  /* 07 bytes */

  0x07,  /*Endpoint descriptor length = 7 */
  0x05,  /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,  /*Endpoint address (OUT, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,    /*Polling interval in milliseconds*/
  /* 07 bytes */



};

/////////////////////////////////////////////////////////////////////////////
//  MSC_CDC_FS
//////////////////////////////////////////////////////////////////////////////

/* USB MSC+CDC device Configuration Descriptor */
uint8_t USBD_MSC_CDC_FSCfgDesc[USB_MSC_CDC_CONFIG_DESC_SIZ] = {
  0x09,        /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_MSC_CDC_CONFIG_DESC_SIZ, /* wTotalLength: Bytes returned */
  0x00,
  0x03,        /*bNumInterfaces: 3 interface*/
  0x01,        /*bConfigurationValue: Configuration value*/
  0x02,        /*iConfiguration: Index of string descriptor describing the configuration*/
  0xC0,        /*bmAttributes: bus powered and Supports Remote Wakeup */
  0x32,        /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 bytes */



  /********************  CDC interface ********************/

  /******** IAD should be positioned just before the CDC interfaces ******
       IAD to associate the two CDC interfaces */

  0x08, /* bLength */
  0x0B, /* bDescriptorType */
  0x00, /* bFirstInterface */
  0x02, /* bInterfaceCount */
  0x02, /* bFunctionClass */
  0x02, /* bFunctionSubClass */
  0x01, /* bFunctionProtocol */
  0x04, /* iFunction (Index of string descriptor describing this function) */
  /* 08 bytes */

  /********************  CDC interfaces ********************/

  /*Interface Descriptor */
  0x09,  /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE, /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x01,  /* bNumEndpoints: One endpoints used */
  0x02,  /* bInterfaceClass: Communication Interface Class */
  0x02,  /* bInterfaceSubClass: Abstract Control Model */
  0x01,  /* bInterfaceProtocol: Common AT commands */
  0x05,  /* iInterface: */
  /* 09 bytes */

  /*Header Functional Descriptor*/
  0x05,  /* bLength: Endpoint Descriptor size */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x00,  /* bDescriptorSubtype: Header Func Desc */
  0x10,  /* bcdCDC: spec release number */
  0x01,
  /* 05 bytes */

  /*ACM Functional Descriptor*/
  0x04,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x02,  /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,  /* bmCapabilities */
  /* 04 bytes */

  /*Union Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x06,  /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_IDX,  /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_IDX + 1,  /* bSlaveInterface0: Data Class Interface */
  /* 05 bytes */

  /*Call Management Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x01,  /* bDescriptorSubtype: Call Management Func Desc */
  0x03,
  CDC_INTERFACE_IDX + 1,  /* bDataInterface: 1 */
  /* 05 bytes */



  /*CMD Endpoint Descriptor*/
  0x07,                         /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                   /* bEndpointAddress */
  0x03,                         /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x10,                         /* bInterval: */
  /* 07 bytes */

  /*Data class interface descriptor*/
  0x09,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,      /* bDescriptorType: */
  0x01,                         /* bInterfaceNumber: Number of Interface */
  0x00,                         /* bAlternateSetting: Alternate setting */
  0x02,                         /* bNumEndpoints: Two endpoints used */
  0x0A,                         /* bInterfaceClass: CDC */
  0x00,                         /* bInterfaceSubClass: */
  0x00,                         /* bInterfaceProtocol: */
  0x05,                         /* iInterface: */
  /* 09 bytes */

  /*Endpoint IN Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_IN_EP,                    /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                         /* bInterval */
  /* 07 bytes */

  /*Endpoint OUT Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                   /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                         /* bInterval: ignore for Bulk transfer */
  /* 07 bytes */


  /********************  Mass Storage interface ********************/
  0x09,  /* bLength: Interface Descriptor size */
  0x04,  /* bDescriptorType: */
  0x02,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x02,  /* bNumEndpoints*/
  0x08,  /* bInterfaceClass: MSC Class */
  0x06,  /* bInterfaceSubClass : SCSI transparent command set*/
  0x50,  /* nInterfaceProtocol */
  0x00, /* iInterface: */
  /* 09 bytes */

  /********************  Mass Storage Endpoints ********************/
  0x07,  /*Endpoint descriptor length = 7*/
  0x05,  /*Endpoint descriptor type */
  MSC_EPIN_ADDR,  /*Endpoint address (IN, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,  /*Polling interval in milliseconds */
  /* 07 bytes */

  0x07,  /*Endpoint descriptor length = 7 */
  0x05,  /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,  /*Endpoint address (OUT, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,    /*Polling interval in milliseconds*/
  /* 07 bytes */

};

/////////////////////////////////////////////////////////////////////////////
// MSC_CDC_OtherSpeed
/////////////////////////////////////////////////////////////////////////////

/* USB MSC+CDC device Configuration Descriptor */
uint8_t USBD_MSC_CDC_OtherSpeedCfgDesc[USB_MSC_CDC_CONFIG_DESC_SIZ] = {
  0x09,        /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_MSC_CDC_CONFIG_DESC_SIZ, /* wTotalLength: Bytes returned */
  0x00,
  0x03,        /*bNumInterfaces: 3 interface*/
  0x01,        /*bConfigurationValue: Configuration value*/
  0x02,        /*iConfiguration: Index of string descriptor describing the configuration*/
  0xC0,        /*bmAttributes: bus powered and Supports Remote Wakeup */
  0x32,        /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 bytes */


  /******** IAD should be positioned just before the CDC interfaces ******
       IAD to associate the two CDC interfaces */

  0x08, /* bLength */
  0x0B, /* bDescriptorType */
  0x00, /* bFirstInterface */
  0x02, /* bInterfaceCount */
  0x02, /* bFunctionClass */
  0x02, /* bFunctionSubClass */
  0x01, /* bFunctionProtocol */
  0x04, /* iFunction (Index of string descriptor describing this function) */
  /* 08 bytes */

  /********************  CDC interfaces ********************/

  /*Interface Descriptor */
  0x09,  /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE, /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x01,  /* bNumEndpoints: One endpoints used */
  0x02,  /* bInterfaceClass: Communication Interface Class */
  0x02,  /* bInterfaceSubClass: Abstract Control Model */
  0x01,  /* bInterfaceProtocol: Common AT commands */
  0x05,  /* iInterface: */
  /* 09 bytes */

  /*Header Functional Descriptor*/
  0x05,  /* bLength: Endpoint Descriptor size */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x00,  /* bDescriptorSubtype: Header Func Desc */
  0x10,  /* bcdCDC: spec release number */
  0x01,
  /* 05 bytes */

  /*ACM Functional Descriptor*/
  0x04,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x02,  /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,  /* bmCapabilities */
  /* 04 bytes */

  /*Union Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x06,  /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_IDX,  /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_IDX + 1,  /* bSlaveInterface0: Data Class Interface */
  /* 05 bytes */

  /*Call Management Functional Descriptor*/
  0x05,  /* bFunctionLength */
  0x24,  /* bDescriptorType: CS_INTERFACE */
  0x01,  /* bDescriptorSubtype: Call Management Func Desc */
  0x03,
  CDC_INTERFACE_IDX + 1,  /* bDataInterface: 1 */
  /* 05 bytes */



  /*CMD Endpoint Descriptor*/
  0x07,                         /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                   /* bEndpointAddress */
  0x02,                         /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x10,                         /* bInterval: */
  /* 07 bytes */

  /*Data class interface descriptor*/
  0x09,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,      /* bDescriptorType: */
  0x01,                         /* bInterfaceNumber: Number of Interface */
  0x00,                         /* bAlternateSetting: Alternate setting */
  0x02,                         /* bNumEndpoints: Two endpoints used */
  0x0A,                         /* bInterfaceClass: CDC */
  0x00,                         /* bInterfaceSubClass: */
  0x00,                         /* bInterfaceProtocol: */
  0x05,                         /* iInterface: */
  /* 09 bytes */

  /*Endpoint IN Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_IN_EP,                    /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  0x40,                         /* wMaxPacketSize: */
  0x00,
  0x00,                         /* bInterval: ignore for Bulk transfer */
  /* 07 bytes */

  /*Endpoint OUT Descriptor*/
  0x07,  /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,       /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                   /* bEndpointAddress */
  0x02,                         /* bmAttributes: Bulk */
  0x40,                         /* wMaxPacketSize: */
  0x00,
  0x00,                         /* bInterval: ignore for Bulk transfer */
  /* 07 bytes */


  /********************  Mass Storage interface ********************/
  0x09,  /* bLength: Interface Descriptor size */
  0x04,  /* bDescriptorType: */
  0x02,  /* bInterfaceNumber: Number of Interface */
  0x00,  /* bAlternateSetting: Alternate setting */
  0x02,  /* bNumEndpoints*/
  0x08,  /* bInterfaceClass: MSC Class */
  0x06,  /* bInterfaceSubClass : SCSI transparent command set*/
  0x50,  /* nInterfaceProtocol */
  0x00, /* iInterface: */
  /* 09 bytes */

  /********************  Mass Storage Endpoints ********************/
  0x07,  /*Endpoint descriptor length = 7*/
  0x05,  /*Endpoint descriptor type */
  MSC_EPIN_ADDR,  /*Endpoint address (IN, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,  /*Polling interval in milliseconds */
  /* 07 bytes */

  0x07,  /*Endpoint descriptor length = 7 */
  0x05,  /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,  /*Endpoint address (OUT, address 1) */
  0x02,  /*Bulk endpoint type */
  LOBYTE(USB_MSC_PACKET_SIZE),
  HIBYTE(USB_MSC_PACKET_SIZE),
  0x00,    /*Polling interval in milliseconds*/
  /* 07 bytes */
  
};

#if defined (__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
/* USB Standard Device Descriptor */
uint8_t USBD_MSC_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] = {
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  USB_MAX_PACKET_SIZE,
  0x01,
  0x00,
};


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



uint8_t  USBD_MSC_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

uint8_t  USBD_MSC_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

uint8_t  USBD_MSC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

uint8_t  USBD_MSC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

uint8_t  USBD_MSC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

/**
  * @}
  */


/** @defgroup USBD_MSC_CDC_Private_Macros
  * @{
  */

/**
  * @}
  */



/** @defgroup USBD_CDC_Private_FunctionPrototypes
  * @{
  */


uint8_t  USBD_CDC_EP_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

uint8_t  USBD_CDC_EP_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

uint8_t  USBD_CDC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

uint8_t  USBD_CDC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

uint8_t  USBD_CDC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

uint8_t  USBD_CDC_EP0_RxReady(USBD_HandleTypeDef *pdev);



/** @defgroup USBD_MSC_CDC_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_MSC_CDC_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t  USBD_MSC_CDC_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t  USBD_MSC_CDC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

static uint8_t  USBD_MSC_CDC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_MSC_CDC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t *USBD_MSC_CDC_GetFSCfgDesc(uint16_t *length);

static uint8_t *USBD_MSC_CDC_GetHSCfgDesc(uint16_t *length);

static uint8_t *USBD_MSC_CDC_GetOtherSpeedCfgDesc(uint16_t *length);

uint8_t *USBD_CDC_GetDeviceQualifierDescriptor(uint16_t *length);

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END = {
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

/** @defgroup USBD_MSC_CDC_Private_Variables
  * @{
  */


USBD_ClassTypeDef  USBD_MSC_CDC_ClassDriver = {
  USBD_MSC_CDC_Init,
  USBD_MSC_CDC_DeInit,
  USBD_MSC_CDC_Setup,
  NULL, //USBD_MSC_CDC_EP0_TxReady,
  USBD_CDC_EP0_RxReady,
  USBD_MSC_CDC_DataIn,
  USBD_MSC_CDC_DataOut,
  NULL, //USBD_MSC_CDC_SOF,
  NULL, //USBD_MSC_CDC_IsoINIncomplete,
  NULL, //USBD_MSC_CDC_IsoOutIncomplete,
  USBD_MSC_CDC_GetHSCfgDesc,
  USBD_MSC_CDC_GetFSCfgDesc,
  USBD_MSC_CDC_GetOtherSpeedCfgDesc,
  USBD_CDC_GetDeviceQualifierDescriptor,
};




/** @defgroup MSC_CORE_Private_Functions
  * @{
  */

/**
  * @brief  USBD_MSC_Init
  *         Initialize  the mass storage configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
uint8_t  USBD_MSC_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  if (pdev->dev_speed == USBD_SPEED_HIGH) {
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, MSC_EPOUT_ADDR, USBD_EP_TYPE_BULK, MSC_MAX_HS_PACKET);
    pdev->ep_out[MSC_EPOUT_ADDR & 0xFU].is_used = 1U;

    /* Open EP IN */
    USBD_LL_OpenEP(pdev, MSC_EPIN_ADDR, USBD_EP_TYPE_BULK, MSC_MAX_HS_PACKET);
    pdev->ep_in[MSC_EPIN_ADDR & 0xFU].is_used = 1U;
  } else {
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, MSC_EPOUT_ADDR, USBD_EP_TYPE_BULK, MSC_MAX_FS_PACKET);
    pdev->ep_out[MSC_EPOUT_ADDR & 0xFU].is_used = 1U;

    /* Open EP IN */
    USBD_LL_OpenEP(pdev, MSC_EPIN_ADDR, USBD_EP_TYPE_BULK, MSC_MAX_FS_PACKET);
    pdev->ep_in[MSC_EPIN_ADDR & 0xFU].is_used = 1U;
  }
  pdev->pClassDataMSC = USBD_malloc(sizeof(USBD_MSC_BOT_HandleTypeDef));

  if (pdev->pClassDataMSC == NULL) {
    return USBD_FAIL;
  }

  /* Init the BOT  layer */
  MSC_BOT_Init(pdev);

  return USBD_OK;
}

/**
  * @brief  USBD_MSC_DeInit
  *         DeInitilaize  the mass storage configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
uint8_t  USBD_MSC_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* Close MSC EPs */
  USBD_LL_CloseEP(pdev, MSC_EPOUT_ADDR);
  pdev->ep_out[MSC_EPOUT_ADDR & 0xFU].is_used = 0U;

  /* Close EP IN */
  USBD_LL_CloseEP(pdev, MSC_EPIN_ADDR);
  pdev->ep_in[MSC_EPIN_ADDR & 0xFU].is_used = 0U;

  /* De-Init the BOT layer */
  MSC_BOT_DeInit(pdev);

  /* Free MSC Class Resources */
  if (pdev->pClassDataMSC != NULL) {
    USBD_free(pdev->pClassDataMSC);
    pdev->pClassDataMSC  = NULL;
  }
  return USBD_OK;
}


/**
* @brief  USBD_MSC_DataIn
*         handle data IN Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_MSC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  MSC_BOT_DataIn(pdev, epnum);
  return USBD_OK;
}

/**
* @brief  USBD_MSC_DataOut
*         handle data OUT Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_MSC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  MSC_BOT_DataOut(pdev, epnum);
  return USBD_OK;
}

/** @defgroup USBD_CDC_Private_Functions
  * @{
  */

/**
  * @brief  USBD_CDC_Init
  *         Initialize the CDC interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  USBD_CDC_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  uint8_t ret = 0U;
  UNUSED(cfgidx);
  USBD_CDC_HandleTypeDef *hcdc;

  if (pdev->dev_speed == USBD_SPEED_HIGH) {
    /* Open EP IN */
    USBD_LL_OpenEP(pdev, CDC_IN_EP, USBD_EP_TYPE_BULK,
                   CDC_DATA_HS_IN_PACKET_SIZE);

    pdev->ep_in[CDC_IN_EP & 0xFU].is_used = 1U;

    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, CDC_OUT_EP, USBD_EP_TYPE_BULK,
                   CDC_DATA_HS_OUT_PACKET_SIZE);

    pdev->ep_out[CDC_OUT_EP & 0xFU].is_used = 1U;

  } else {
    /* Open EP IN */
    USBD_LL_OpenEP(pdev, CDC_IN_EP, USBD_EP_TYPE_BULK,
                   CDC_DATA_FS_IN_PACKET_SIZE);

    pdev->ep_in[CDC_IN_EP & 0xFU].is_used = 1U;

    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, CDC_OUT_EP, USBD_EP_TYPE_BULK,
                   CDC_DATA_FS_OUT_PACKET_SIZE);

    pdev->ep_out[CDC_OUT_EP & 0xFU].is_used = 1U;
  }
  /* Open Command IN EP */
  USBD_LL_OpenEP(pdev, CDC_CMD_EP, USBD_EP_TYPE_INTR, CDC_CMD_PACKET_SIZE);
  pdev->ep_in[CDC_CMD_EP & 0xFU].is_used = 1U;

  pdev->pClassDataCDC = USBD_malloc(sizeof(USBD_CDC_HandleTypeDef));

  if (pdev->pClassDataCDC == NULL) {
    ret = 1U;
  } else {
    hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

    /* Init  physical Interface components */
    ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->Init();

    /* Init Xfer states */
    hcdc->TxState = 0U;
    hcdc->RxState = 0U;

    if (pdev->dev_speed == USBD_SPEED_HIGH) {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev, CDC_OUT_EP, hcdc->RxBuffer,
                             CDC_DATA_HS_OUT_PACKET_SIZE);
    } else {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev, CDC_OUT_EP, hcdc->RxBuffer,
                             CDC_DATA_FS_OUT_PACKET_SIZE);
    }
  }
  return ret;
}

/**
  * @brief  USBD_CDC_Init
  *         DeInitialize the CDC layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  USBD_CDC_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  uint8_t ret = 0U;
  UNUSED(cfgidx);

  /* Close EP IN */
  USBD_LL_CloseEP(pdev, CDC_IN_EP);
  pdev->ep_in[CDC_IN_EP & 0xFU].is_used = 0U;

  /* Close EP OUT */
  USBD_LL_CloseEP(pdev, CDC_OUT_EP);
  pdev->ep_out[CDC_OUT_EP & 0xFU].is_used = 0U;

  /* Close Command IN EP */
  USBD_LL_CloseEP(pdev, CDC_CMD_EP);
  pdev->ep_in[CDC_CMD_EP & 0xFU].is_used = 0U;

  /* DeInit  physical Interface components */
  if (pdev->pClassDataCDC != NULL) {
    ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->DeInit();
    USBD_free(pdev->pClassDataCDC);
    pdev->pClassDataCDC = NULL;
  }

  return ret;
}

/**
  * @brief  USBD_CDC_Setup
  *         Handle the CDC specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
uint8_t  USBD_CDC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;
  uint8_t ifalt = 0U;
  uint16_t status_info = 0U;
  uint8_t ret = USBD_OK;

  switch (req->bmRequest & USB_REQ_TYPE_MASK) {
    case USB_REQ_TYPE_CLASS :
      if (req->wLength) {
        if (req->bmRequest & 0x80U) {
          ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->Control(req->bRequest,
                                                                             (uint8_t *)(void *)hcdc->data,
                                                                             req->wLength);

          USBD_CtlSendData(pdev, (uint8_t *)(void *)hcdc->data, req->wLength);
        } else {
          hcdc->CmdOpCode = req->bRequest;
          hcdc->CmdLength = (uint8_t)req->wLength;

          USBD_CtlPrepareRx(pdev, (uint8_t *)(void *)hcdc->data, req->wLength);
        }
      } else {
        ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->Control(req->bRequest,
                                                                           (uint8_t *)(void *)req, 0U);
      }
      break;

    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest) {
        case USB_REQ_GET_STATUS:
          if (pdev->dev_state == USBD_STATE_CONFIGURED) {
            USBD_CtlSendData(pdev, (uint8_t *)(void *)&status_info, 2U);
          } else {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_GET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED) {
            USBD_CtlSendData(pdev, &ifalt, 1U);
          } else {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE:
          if (pdev->dev_state != USBD_STATE_CONFIGURED) {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
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

  return ret;
}

/**
  * @brief  USBD_CDC_DataIn
  *         Data sent on non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  USBD_CDC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *)pdev->pClassDataCDC;
  PCD_HandleTypeDef *hpcd = pdev->pPCDHandle;
  USBD_CDC_ItfTypeDef *ctrl = (USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC;

  if (pdev->pClassDataCDC != NULL) {
    if ((hcdc->TxLastLength > 0U) && ((hcdc->TxLastLength % hpcd->IN_ep[epnum].maxpacket) == 0U)) {
      /* Update the packet total length */
      hcdc->TxLastLength = 0U;

      /* Send ZLP */
      USBD_LL_Transmit(pdev, epnum, NULL, 0U);
    } else {
      hcdc->TxState = 0U;
      if (ctrl->Transferred) {
        ctrl->Transferred();
      }
    }
    return USBD_OK;
  } else {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_CDC_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  USBD_CDC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  /* Get the received data length */
  hcdc->RxLength = USBD_LL_GetRxDataSize(pdev, epnum);

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the application Xfer */
  if (pdev->pClassDataCDC != NULL) {
    ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->Receive(hcdc->RxBuffer, &hcdc->RxLength);

    return USBD_OK;
  } else {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_CDC_EP0_RxReady
  *         Handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_CDC_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  if ((pdev->pClassSpecificInterfaceCDC != NULL) && (hcdc->CmdOpCode != 0xFFU)) {
    ((USBD_CDC_ItfTypeDef *)pdev->pClassSpecificInterfaceCDC)->Control(hcdc->CmdOpCode,
                                                                       (uint8_t *)(void *)hcdc->data,
                                                                       (uint16_t)hcdc->CmdLength);
    hcdc->CmdOpCode = 0xFFU;

  }
  return USBD_OK;
}

/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_CDC_GetDeviceQualifierDescriptor(uint16_t *length)
{
  *length = sizeof(USBD_CDC_DeviceQualifierDesc);
  return USBD_CDC_DeviceQualifierDesc;
}

/**
* @brief  USBD_CDC_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: CD  Interface callback
  * @retval status
  */
uint8_t  USBD_CDC_RegisterInterface(USBD_HandleTypeDef *pdev,
                                    USBD_CDC_ItfTypeDef *fops)
{
  uint8_t  ret = USBD_FAIL;

  if (fops != NULL) {
    pdev->pClassSpecificInterfaceCDC = fops;
    ret = USBD_OK;
  }

  return ret;
}

/**
  * @brief  USBD_CDC_SetTxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Tx Buffer
  * @retval status
  */
uint8_t  USBD_CDC_SetTxBuffer(USBD_HandleTypeDef *pdev,
                              uint8_t *pbuff,
                              uint16_t length)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  hcdc->TxBuffer = pbuff;
  hcdc->TxLength = length;

  return USBD_OK;
}


/**
  * @brief  USBD_CDC_SetRxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Rx Buffer
  * @retval status
  */
uint8_t  USBD_CDC_SetRxBuffer(USBD_HandleTypeDef *pdev,
                              uint8_t *pbuff)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  hcdc->RxBuffer = pbuff;

  return USBD_OK;
}

/**
  * @brief  USBD_CDC_TransmitPacket
  *         Transmit packet on IN endpoint
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_CDC_TransmitPacket(USBD_HandleTypeDef *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  if (pdev->pClassDataCDC != NULL) {
    if (hcdc->TxState == 0U) {
      /* Tx Transfer in progress */
      hcdc->TxState = 1U;

      /* Update the packet total length */
      hcdc->TxLastLength = hcdc->TxLength;

      /* Transmit next packet */
      USBD_LL_Transmit(pdev, CDC_IN_EP, hcdc->TxBuffer,
                       (uint16_t)hcdc->TxLength);

      return USBD_OK;
    } else {
      return USBD_BUSY;
    }
  } else {
    return USBD_FAIL;
  }
}


/**
  * @brief  USBD_CDC_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_CDC_ReceivePacket(USBD_HandleTypeDef *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *) pdev->pClassDataCDC;

  /* Suspend or Resume USB Out process */
  if (pdev->pClassDataCDC != NULL) {
    if (pdev->dev_speed == USBD_SPEED_HIGH) {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             CDC_OUT_EP,
                             hcdc->RxBuffer,
                             CDC_DATA_HS_OUT_PACKET_SIZE);
    } else {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             CDC_OUT_EP,
                             hcdc->RxBuffer,
                             CDC_DATA_FS_OUT_PACKET_SIZE);
    }
    return USBD_OK;
  } else {
    return USBD_FAIL;
  }
}

/**
  * @}
  */

/** @defgroup USBD_MSC_CDC_Private_Functions
  * @{
  */

/**
  * @brief  USBD_MSC_CDC_Init
  *         Initialize the MSC+CDC interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_MSC_CDC_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* CDC initialization */
  uint8_t ret = USBD_CDC_Init(pdev, cfgidx);
  if (ret != 0) {
    return ret;
  }
  pdev->pClassDataMSC =  USBD_malloc(sizeof(USBD_MSC_BOT_HandleTypeDef));

  /* MSC initialization */
  ret = USBD_MSC_Init(pdev, cfgidx);
  if (ret != 0) {
    return ret;
  }

  /* Open EP OUT */
  USBD_LL_OpenEP(pdev, MSC_EPOUT_ADDR, USBD_EP_TYPE_BULK, USB_MAX_PACKET_SIZE);

  /* Open EP IN */
  USBD_LL_OpenEP(pdev, MSC_EPIN_ADDR, USBD_EP_TYPE_BULK, USB_MAX_PACKET_SIZE);


  /* Init the BOT  layer */
  MSC_BOT_Init(pdev);
  ret = 0;

  return ret;
}

/**
  * @brief  USBD_MSC_CDC_DeInit
  *         DeInitialize the MSC+CDC layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_MSC_CDC_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* MSC De-initialization */
  USBD_MSC_DeInit(pdev, cfgidx);

  /* CDC De-initialization */
  USBD_CDC_DeInit(pdev, cfgidx);

  return USBD_OK;
}


/**
* @brief  USBD_MSC_Setup
*         Handle the MSC specific requests
* @param  pdev: device instance
* @param  req: USB request
* @retval status
*/
uint8_t  USBD_MSC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = pdev->pClassDataMSC;

  switch (req->bmRequest & USB_REQ_TYPE_MASK) {

    /* Class request */
    case USB_REQ_TYPE_CLASS :
      switch (req->bRequest) {
        case BOT_GET_MAX_LUN :

          if ((req->wValue  == 0) &&
              (req->wLength == 1) &&
              ((req->bmRequest & 0x80) == 0x80)) {
            hmsc->max_lun = pdev->pClassSpecificInterfaceMSC->GetMaxLun();
            USBD_CtlSendData(pdev, (uint8_t *)&hmsc->max_lun, 1);
          } else {

            USBD_CtlError(pdev, req);
            return USBD_FAIL;
          }
          break;

        case BOT_RESET :
          if ((req->wValue  == 0) &&
              (req->wLength == 0) &&
              ((req->bmRequest & 0x80) != 0x80)) {
            MSC_BOT_Reset(pdev);
          } else {

            USBD_CtlError(pdev, req);
            return USBD_FAIL;
          }
          break;

        default:
          USBD_CtlError(pdev, req);
          return USBD_FAIL;
      }
      break;
    /* Interface & Endpoint request */
    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest) {
        case USB_REQ_GET_INTERFACE :
          USBD_CtlSendData(pdev, (uint8_t *)&hmsc->interface, 1);
          break;

        case USB_REQ_SET_INTERFACE :
          hmsc->interface = (uint8_t)(req->wValue);
          break;

        case USB_REQ_CLEAR_FEATURE:

          /* Flush the FIFO and Clear the stall status */
          USBD_LL_FlushEP(pdev, (uint8_t)req->wIndex);

          /* Reactivate the EP */
          USBD_LL_CloseEP(pdev, (uint8_t)req->wIndex);
          if ((((uint8_t)req->wIndex) & 0x80) == 0x80) {
            /* Open EP IN */
            USBD_LL_OpenEP(pdev, MSC_EPIN_ADDR, USBD_EP_TYPE_BULK, USB_MAX_PACKET_SIZE);
          } else {

            /* Open EP OUT */
            USBD_LL_OpenEP(pdev, MSC_EPOUT_ADDR, USBD_EP_TYPE_BULK, USB_MAX_PACKET_SIZE);
          }

          /* Handle BOT error */
          MSC_BOT_CplClrFeature(pdev, (uint8_t)req->wIndex);
          break;

      }
      break;

    default:
      break;
  }
  return 0;
}

/**
  * @brief  USBD_MSC_CDC_Setup
  *         Handle the MSC+CDC specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
uint8_t USBD_MSC_CDC_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  // Route requests to MSC interface or its endpoints to MSC class implementaion
  if (((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_INTERFACE && req->wIndex == MSC_INTERFACE_IDX) ||
      ((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_ENDPOINT && ((req->wIndex & 0x7F) == MSC_EP_IDX))) {
    return USBD_MSC_Setup(pdev, req);
  }

  return USBD_CDC_Setup(pdev, req);
}

/**
  * @brief  USBD_MSC_CDC_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_MSC_CDC_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  if (epnum == MSC_EP_IDX) {
    return USBD_MSC_DataIn(pdev, epnum);
  }
  return USBD_CDC_DataIn(pdev, epnum);
}

/**
  * @brief  USBD_MSC_CDC_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_MSC_CDC_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  if (epnum == MSC_EPOUT_ADDR) {
    return USBD_MSC_DataOut(pdev, epnum);
  }
  return USBD_CDC_DataOut(pdev, epnum);
}

//////////////////////////////////////////////////////////////
//  HS
//////////////////////////////////////////////////////////////



/**
  * @brief  USBD_MSC_CDC_GetFSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_MSC_CDC_GetFSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_MSC_CDC_FSCfgDesc);
  return USBD_MSC_CDC_FSCfgDesc;
}

/**
  * @brief  USBD_MSC_CDC_GetHSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_MSC_CDC_GetHSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_MSC_CDC_HSCfgDesc);
  return USBD_MSC_CDC_HSCfgDesc;
}

/**
  * @brief  USBD_MSC_CDC_GetOtherSpeedCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_MSC_CDC_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_MSC_CDC_OtherSpeedCfgDesc);
  return USBD_MSC_CDC_OtherSpeedCfgDesc;
}

#endif /* USBCON && USBD_USE_CDC_COMPOSITE */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
