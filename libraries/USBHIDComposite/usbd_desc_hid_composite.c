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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define USBD_HID_PRODUCT_HS_STRING        CONCATS(USB_PRODUCT, "HID in HS Mode")
#define USBD_HID_PRODUCT_FS_STRING        CONCATS(USB_PRODUCT, "HID in FS Mode")
#define USBD_HID_CONFIGURATION_HS_STRING  CONCATS(USB_PRODUCT, "HID Config")
#define USBD_HID_INTERFACE_HS_STRING      CONCATS(USB_PRODUCT, "HID Interface")
#define USBD_HID_CONFIGURATION_FS_STRING  CONCATS(USB_PRODUCT, "HID Config")
#define USBD_HID_INTERFACE_FS_STRING      CONCATS(USB_PRODUCT, "HID Interface")

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t *USBD_HID_ProductStrDescriptor (USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
#ifdef USB_SUPPORT_USER_STRING_DESC
static uint8_t *USBD_HID_USRStringDesc (USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);
#endif /* USB_SUPPORT_USER_STRING_DESC */

/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef HID_Desc = {
  USBD_DeviceDescriptor,
  USBD_LangIDStrDescriptor,
  USBD_ManufacturerStrDescriptor,
  USBD_HID_ProductStrDescriptor,
  USBD_SerialStrDescriptor,
  USBD_HID_ConfigStrDescriptor,
  USBD_HID_InterfaceStrDescriptor,
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN static uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Returns the product string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_HID_PRODUCT_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_PRODUCT_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the configuration string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_HID_CONFIGURATION_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_CONFIGURATION_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Returns the interface string descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_HID_INTERFACE_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_HID_INTERFACE_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

#endif // USBCON
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
