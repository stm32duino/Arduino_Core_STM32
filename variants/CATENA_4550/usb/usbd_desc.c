/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Src/usbd_desc.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    06-May-2016
  * @brief   This file provides the USBD descriptors and string formatting method.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2016 STMicroelectronics International N.V.
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
/* Includes ------------------------------------------------------------------*/
#ifdef USBCON
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"
#include "utils.h"
#include "stm32l0xx_ll_utils.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//ID
#define USBD_LANGID_STRING            0x409 //1033
#if USBD_VID == 0x2341
#define USBD_MANUFACTURER_STRING "Arduino LLC"
#elif USBD_VID == 0x2A03
#define USBD_MANUFACTURER_STRING "Arduino srl"
#elif USBD_VID == 0x0483
#define USBD_MANUFACTURER_STRING "STMicroelectronics"
#elif USBD_VID == 0x040E
#define USBD_MANUFACTURER_STRING "MCCI Corporation"
#elif !defined(USB_MANUFACTURER)
// Fall through to unknown if no manufacturer name was provided in a macro
#define USBD_MANUFACTURER_STRING "Unknown"
#else
#define USBD_MANUFACTURER_STRING USB_MANUFACTURER
#endif

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* USB Standard Device Descriptor */
const static uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
  0x00,                       /* bcdUSB */
  0x02,
  0xef,                       /* bDeviceClass */
  0x02,                       /* bDeviceSubClass */
  0x01,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idVendor */
  HIBYTE(USBD_PID),           /* idVendor */
  0x00,                       /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */

/* USB Standard Device Descriptor */
const static uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] = {
  USB_LEN_LANGID_STR_DESC,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING),
};

/* make word aligned buffer */
uint16_t USBD_CtrBuf[(USBD_MAX_STR_DESC_SIZ + 1) / 2];

/* Private functions ---------------------------------------------------------*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
static uint8_t *Get_SerialNum(uint8_t *pbuf);

/**
  * @brief  USBD_CopyDesc
  *         Copy descriptor to aligned buffer
  * @param  desc : descriptor buffer
  * @param  len : descriptor length
  * @param  sizedesc : size of descriptor buffer
  * @retval pointer of descriptor descriptor
  */
uint8_t *USBD_CopyDesc(uint16_t *length, const uint8_t *desc, uint16_t sizedesc)
{
  *length = sizedesc;
  return memcpy(USBD_CtrBuf, desc, sizedesc);
}

/**
  * @brief  USBD_MakeString
  *         Make string descriptor
  * @param  desc : string buffer
  * @param  len : descriptor length
  * @param  sizedesc : size of string buffer
  * @retval pointer of string descriptor
  */
uint8_t *USBD_MakeStrDesc(const char *desc, uint16_t *length, uint16_t sizedesc)
{
  uint8_t *unicode = (uint8_t *)USBD_CtrBuf;
  uint8_t idx = 0;
  
  if (desc != NULL) 
  {
    *length =  (sizedesc - 1) * 2 + 2;
    unicode[idx++] = *length;
    unicode[idx++] =  USB_DESC_TYPE_STRING;
    
    while (*desc != '\0') 
    {
      unicode[idx++] = *desc++;
      unicode[idx++] =  0x00;
    }
  } 
  return unicode;
}

/**
  * @brief  Returns the device descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);

  return USBD_CopyDesc(length, USBD_DeviceDesc, sizeof(USBD_DeviceDesc));
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

  return USBD_CopyDesc(length, USBD_LangIDDesc, sizeof(USBD_LangIDDesc));
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

  return USBD_MakeStrDesc(USBD_MANUFACTURER_STRING, length, sizeof(USBD_MANUFACTURER_STRING));
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
  return Get_SerialNum((uint8_t*)USBD_CtrBuf);
}

/**
  * @brief  Create the serial number string descriptor
  * @param  None
  * @retval None
  */
static uint8_t *Get_SerialNum(uint8_t *pbuf)
{
  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = LL_GetUID_Word0();
  deviceserial1 = LL_GetUID_Word1();
  deviceserial2 = LL_GetUID_Word2();

  deviceserial0 += deviceserial2;

  pbuf[0] = USB_SIZ_STRING_SERIAL;
  pbuf[1] = USB_DESC_TYPE_STRING;

  IntToUnicode (deviceserial0, &pbuf[2] ,8);
  IntToUnicode (deviceserial1, &pbuf[18] ,4);
  return pbuf;
}

/**
  * @brief  Convert Hex 32Bits value into char
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;

  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[ 2* idx + 1] = 0;
  }
}
#endif // USBCON
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
