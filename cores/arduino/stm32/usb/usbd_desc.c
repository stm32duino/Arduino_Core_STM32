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

#ifdef USB_SUPPORT_USER_STRING_DESC
  uint8_t *USBD_Class_USRStringDesc(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);
#endif /* USB_SUPPORT_USER_STRING_DESC */

/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef USBD_Desc = {
  USBD_Class_DeviceDescriptor,
  USBD_LangIDStrDescriptor,
  USBD_ManufacturerStrDescriptor,
  USBD_Class_ProductStrDescriptor,
  USBD_SerialStrDescriptor,
  USBD_Class_ConfigStrDescriptor,
  USBD_Class_InterfaceStrDescriptor,
};

#ifdef USBD_USE_HID_COMPOSITE
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_Class_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
  0x00,                       /* bcdUSB */
  0x02,
  0x00,                       /* bDeviceClass */
  0x00,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idProduct */
  HIBYTE(USBD_PID),           /* idProduct */
  0x00,                       /* bcdDevice rel. 0.00 */
  0x00,
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
  0x00,                       /* bcdUSB */
  0x02,
  0x02,                       /* bDeviceClass */
  0x02,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idProduct */
  HIBYTE(USBD_PID),           /* idProduct */
  0x00,                       /* bcdDevice rel. 0.00 */
  0x00,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */
#endif /* USBD_USE_CDC */

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
  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = *(uint32_t *)DEVICE_ID1;
  deviceserial1 = *(uint32_t *)DEVICE_ID2;
  deviceserial2 = *(uint32_t *)DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0U) {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8U);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4U);
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
