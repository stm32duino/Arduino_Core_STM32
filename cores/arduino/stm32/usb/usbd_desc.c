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
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */
#ifdef USBCON
/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usbd_desc.h"
#include "utils.h"
#include <variant.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* USB VID and PID: Either both or neither must be specified. If not
 * specified, default to the ST VID, with a PID assigned to HID or a PID
 * assigned to CDC devices. */
#if !USBD_PID && !USBD_VID
  // Undef the default zero values
  #undef USBD_PID
  #undef USBD_VID
  // Define default values, based on the USB class used
  #define USBD_VID 0x0483
  #if defined(USBD_USE_HID_COMPOSITE)
    #define USBD_PID                      0x5711
  #elif defined(USBD_USE_CDC)
    #define USBD_PID                      0x5740
  #endif
#endif /* !USBD_PID && !USBD_VID */

#if !USBD_VID || !USBD_PID
  #error "USB VID or PID not specified"
#endif

/* Manufacturer string: Use the specified string if specified, guess
   based on VID otherwise */
#if defined(USB_MANUFACTURER_STRING)
  #define USBD_MANUFACTURER_STRING USB_MANUFACTURER_STRING
#elif USBD_VID == 0x2341
  #define USBD_MANUFACTURER_STRING "Arduino LLC"
#elif USBD_VID == 0x2A03
  #define USBD_MANUFACTURER_STRING "Arduino srl"
#elif USBD_VID == 0x0483
  #define USBD_MANUFACTURER_STRING "STMicroelectronics"
#else
  #define USBD_MANUFACTURER_STRING "Unknown"
#endif

#define USBD_LANGID_STRING            0x409   /* 1033 US.S English */

/* Product string: Use the specified string if specified, construct
   based on BOARD_NAME and class otherwise. */
#if defined(USB_PRODUCT_STRING)
  #define USBD_CLASS_PRODUCT_HS_STRING        USB_PRODUCT_STRING
  #define USBD_CLASS_PRODUCT_FS_STRING        USB_PRODUCT_STRING
#elif defined(USBD_USE_HID_COMPOSITE)
  #define USBD_CLASS_PRODUCT_HS_STRING        CONCATS(BOARD_NAME, "HID in HS Mode")
  #define USBD_CLASS_PRODUCT_FS_STRING        CONCATS(BOARD_NAME, "HID in FS Mode")
#elif defined(USBD_USE_CDC)
  #define USBD_CLASS_PRODUCT_HS_STRING        CONCATS(BOARD_NAME, "CDC in HS Mode")
  #define USBD_CLASS_PRODUCT_FS_STRING        CONCATS(BOARD_NAME, "CDC in FS Mode")
#else
  #define USBD_CLASS_PRODUCT_HS_STRING        CONCATS(BOARD_NAME, "in HS Mode")
  #define USBD_CLASS_PRODUCT_FS_STRING        CONCATS(BOARD_NAME, "in FS Mode")
#endif

#ifdef USBD_USE_HID_COMPOSITE
  #define USBD_CLASS_CONFIGURATION_HS_STRING  CONCATS(BOARD_NAME, "HID Config")
  #define USBD_CLASS_INTERFACE_HS_STRING      CONCATS(BOARD_NAME, "HID Interface")
  #define USBD_CLASS_CONFIGURATION_FS_STRING  CONCATS(BOARD_NAME, "HID Config")
  #define USBD_CLASS_INTERFACE_FS_STRING      CONCATS(BOARD_NAME, "HID Interface")
#endif /* USBD_USE_HID_COMPOSITE */

#ifdef USBD_USE_CDC
  #define USBD_CLASS_CONFIGURATION_HS_STRING  CONCATS(BOARD_NAME, "CDC Config")
  #define USBD_CLASS_INTERFACE_HS_STRING      CONCATS(BOARD_NAME, "CDC Interface")
  #define USBD_CLASS_CONFIGURATION_FS_STRING  CONCATS(BOARD_NAME, "CDC Config")
  #define USBD_CLASS_INTERFACE_FS_STRING      CONCATS(BOARD_NAME, "CDC Interface")
#endif /* USBD_USE_CDC */

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Common function */
uint8_t *USBD_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

/* Class specific */
uint8_t *USBD_Class_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_Class_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_Class_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_Class_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

#if (USBD_CLASS_USER_STRING_DESC == 1)
  uint8_t *USBD_Class_UserStrDescriptor(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);
#endif /* USB_CLASS_USER_STRING_DESC */
#if ((USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1))
  uint8_t *USBD_USR_BOSDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
#endif /* (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1) */
/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef USBD_Desc = {
  USBD_Class_DeviceDescriptor,
  USBD_LangIDStrDescriptor,
  USBD_ManufacturerStrDescriptor,
  USBD_Class_ProductStrDescriptor,
  USBD_SerialStrDescriptor,
  USBD_Class_ConfigStrDescriptor,
  USBD_Class_InterfaceStrDescriptor,
#if (USBD_CLASS_USER_STRING_DESC == 1)
  USBD_Class_UserStrDescriptor,
#endif /* USB_CLASS_USER_STRING_DESC */

#if ((USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1))
  USBD_USR_BOSDescriptor,
#endif /* (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1) */
};

#ifdef USBD_USE_HID_COMPOSITE
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_Class_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
#if ((USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1))
  0x01,                       /*bcdUSB */     /* changed to USB version 2.01
                                              in order to support BOS Desc */
#else
  0x00,                       /* bcdUSB */
#endif /* (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1) */
  0x02,
  0x00,                       /* bDeviceClass */
  0x00,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idProduct */
  HIBYTE(USBD_PID),           /* idProduct */
  0x00,                       /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */
#endif /* USBD_USE_HID_COMPOSITE */

#ifdef USBD_USE_CDC
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_Class_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
#if ((USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1))
  0x01,                       /*bcdUSB */     /* changed to USB version 2.01
                                              in order to support BOS Desc */
#else
  0x00,                       /* bcdUSB */
#endif
  0x02,
  0x02,                       /* bDeviceClass */
  0x02,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idProduct */
  HIBYTE(USBD_PID),           /* idProduct */
  0x00,                       /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */
#endif /* USBD_USE_CDC */

/* USB Device LPM BOS descriptor */
#if (USBD_LPM_ENABLED == 1)
__ALIGN_BEGIN  uint8_t USBD_BOSDesc[USB_SIZ_BOS_DESC] __ALIGN_END = {
  0x5,
  USB_DESC_TYPE_BOS,
  0xC,
  0x0,
  0x1,  /* 1 device capability */
  /* device capability */
  0x7,
  USB_DEVICE_CAPABITY_TYPE,
  0x2,
  0x6, /*LPM capability bit set */
  0x0,
  0x0,
  0x0
};
#endif /* USBD_LPM_ENABLED */

/* USB Device Billboard BOS descriptor Template */
#if (USBD_CLASS_BOS_ENABLED == 1)
__ALIGN_BEGIN  uint8_t USBD_BOSDesc[USB_SIZ_BOS_DESC] __ALIGN_END = {
  0x05,                                /* bLength */
  USB_DESC_TYPE_BOS,                   /* Device Descriptor Type */
  USB_SIZ_BOS_DESC,                    /* Total length of BOS descriptor and all of its sub descs */
  0x00,
  0x04,                                /* The number of separate device capability descriptors in the BOS */

  /* ----------- Device Capability Descriptor: CONTAINER_ID ---------- */
  0x14,                                /* bLength */
  0x10,                                /* bDescriptorType: DEVICE CAPABILITY Type */
  0x04,                                /* bDevCapabilityType: CONTAINER_ID */
  0x00,                                /* bReserved */
  0xa7, 0xd6, 0x1b, 0xfa,              /* ContainerID: This is a Unique 128-bit number GUID */
  0x91, 0xa6, 0xa8, 0x4e,
  0xa8, 0x21, 0x9f, 0x2b,
  0xaf, 0xf7, 0x94, 0xd4,

  /* ----------- Device Capability Descriptor: BillBoard ---------- */
  0x34,                                /* bLength */
  0x10,                                /* bDescriptorType: DEVICE CAPABILITY Type */
  0x0D,                                /* bDevCapabilityType: BILLBOARD_CAPABILITY */
  USBD_BB_URL_STRING_INDEX,            /* iAddtionalInfoURL: Index of string descriptor providing a URL where the user
                                          can go to get more detailed information about the product and the various
                                          Alternate Modes it supports */

  0x02,                                /* bNumberOfAlternateModes: Number of Alternate modes supported. The
                                        maximum value that this field can be set to is MAX_NUM_ALT_MODE. */

  0x00,                                /* bPreferredAlternateMode: Index of the preferred Alternate Mode. System
                                          software may use this information to provide the user with a better
                                          user experience. */

  0x00, 0x00,                          /* VCONN Power needed by the adapter for full functionality 000b = 1W */

  0x01, 0x00, 0x00, 0x00,              /* bmConfigured. 01b: Alternate Mode configuration not attempted or exited */
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x21, 0x01,                          /* bcdVersion = 0x0121 */
  0x00,                                /* bAdditionalFailureInfo */
  0x00,                                /* bReserved */
  LOBYTE(USBD_VID),
  HIBYTE(USBD_VID),                    /* wSVID[0]: Standard or Vendor ID. This shall match one of the SVIDs
                                        returned in response to a USB PD Discover SVIDs command */

  0x00,                                /* bAlternateMode[0] Index of the Alternate Mode within the SVID as
                                        returned in response to a Discover Modes command. Example:
                                        0  first Mode entry
                                        1  second mode entry */

  USBD_BB_ALTMODE0_STRING_INDEX,           /* iAlternateModeString[0]: Index of string descriptor describing protocol.
                                        It is optional to support this string. */
  LOBYTE(USBD_VID),
  HIBYTE(USBD_VID),                    /* wSVID[1]: Standard or Vendor ID. This shall match one of the SVIDs
                                        returned in response to a USB PD Discover SVIDs command */

  0x01,                                /* bAlternateMode[1] Index of the Alternate Mode within the SVID as
                                        returned in response to a Discover Modes command. Example:
                                        0  first Mode entry
                                        1  second Mode entry */

  USBD_BB_ALTMODE1_STRING_INDEX,       /* iAlternateModeString[1]: Index of string descriptor describing protocol.
                                        It is optional to support this string. */
  /* Alternate Mode Desc */
  /* ----------- Device Capability Descriptor: BillBoard Alternate Mode Desc ---------- */
  0x08,                                /* bLength */
  0x10,                                /* bDescriptorType: Device Descriptor Type */
  0x0F,                                /* bDevCapabilityType: BILLBOARD ALTERNATE MODE CAPABILITY */
  0x00,                                /* bIndex: Index of Alternate Mode described in the Billboard Capability Desc */
  0x10, 0x00, 0x00, 0x00,              /* dwAlternateModeVdo: contents of the Mode VDO for the alternate mode
                                          identified by bIndex */

  0x08,                                /* bLength */
  0x10,                                /* bDescriptorType: Device Descriptor Type */
  0x0F,                                /* bDevCapabilityType: BILLBOARD ALTERNATE MODE CAPABILITY */
  0x01,                                /* bIndex: Index of Alternate Mode described in the Billboard Capability Desc */
  0x20, 0x00, 0x00, 0x00,              /* dwAlternateModeVdo: contents of the Mode VDO for the alternate mode
                                          identified by bIndex */
};
#endif /* USBD_CLASS_BOS_ENABLED */


/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
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
uint8_t *USBD_Class_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_Class_DeviceDesc);
  return (uint8_t *)USBD_Class_DeviceDesc;
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
uint8_t *USBD_Class_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CLASS_PRODUCT_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CLASS_PRODUCT_FS_STRING, USBD_StrDesc, length);
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
uint8_t *USBD_Class_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CLASS_CONFIGURATION_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CLASS_CONFIGURATION_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the interface string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_Class_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if (speed == USBD_SPEED_HIGH) {
    USBD_GetString((uint8_t *)USBD_CLASS_INTERFACE_HS_STRING, USBD_StrDesc, length);
  } else {
    USBD_GetString((uint8_t *)USBD_CLASS_INTERFACE_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Create the serial number string descriptor
  * @param  None
  * @retval None
  */
static void Get_SerialNum(void)
{
  uint32_t deviceserial0;
  uint32_t deviceserial1;
  uint32_t deviceserial2;

  deviceserial0 = *(uint32_t *)DEVICE_ID1;
  deviceserial1 = *(uint32_t *)DEVICE_ID2;
  deviceserial2 = *(uint32_t *)DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0U) {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8U);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4U);
  }
}


#if ((USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1))
/**
  * @brief  USBD_USR_BOSDescriptor
  *         return the BOS descriptor
  * @param  speed : current device speed
  * @param  length : pointer to data length variable
  * @retval pointer to descriptor buffer
  */
uint8_t *USBD_USR_BOSDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_BOSDesc);
  return (uint8_t *)USBD_BOSDesc;
}
#endif /* (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1) */


#if (USBD_CLASS_USER_STRING_DESC == 1)
/**
  * @brief  Returns the Class User string descriptor.
  * @param  speed: Current device speed
  * @param  idx: index of string descriptor
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_Class_UserStrDescriptor(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length)
{
  static uint8_t USBD_StrDesc[255];
  UNUSED(speed);
  UNUSED(idx);
  UNUSED(length);
  return USBD_StrDesc;
}
#endif /* USBD_CLASS_USER_STRING_DESC */


/**
  * @brief  Convert Hex 32Bits value into char
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
  uint8_t idx = 0U;

  for (idx = 0U ; idx < len ; idx ++) {
    if (((value >> 28)) < 0xAU) {
      pbuf[ 2U * idx] = (value >> 28) + '0';
    } else {
      pbuf[2U * idx] = (value >> 28) + 'A' - 10U;
    }

    value = value << 4;

    pbuf[2U * idx + 1] = 0U;
  }
}
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
