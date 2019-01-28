/**
  ******************************************************************************
  * @file    usbd_interface.c
  * @brief   Provide the USB device interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifdef USBCON
#include "usbd_desc.h"
#include "usbd_interface.h"
#ifdef USBD_USE_HID_COMPOSITE
#include "usbd_hid_composite.h"
#endif
#ifdef USBD_USE_CDC
#include "usbd_cdc_if.h"
#endif

#ifdef __cplusplus
 extern "C" {
#endif

/* USB Device Core handle declaration */
#ifdef USBD_USE_HID_COMPOSITE
USBD_HandleTypeDef hUSBD_Device_HID;
#endif /* USBD_USE_HID_COMPOSITE*/
#ifdef USBD_USE_CDC
USBD_HandleTypeDef hUSBD_Device_CDC;
#endif /* USBD_USE_CDC */

/**
  * @brief  initialize USB devices
  * @param  none
  * @retval none
  */
__attribute__((weak))
void usbd_interface_init(void)
{
#ifdef USBD_USE_HID_COMPOSITE
  /* Init Device Library */
  USBD_Init(&hUSBD_Device_HID, &HID_Desc, 0);

  /* Add Supported Class */
  USBD_RegisterClass(&hUSBD_Device_HID, USBD_COMPOSITE_HID_CLASS);

  /* Start Device Process */
  USBD_Start(&hUSBD_Device_HID);
#endif /* USBD_USE_HID_COMPOSITE */
#ifdef USBD_USE_CDC
  /* Init Device Library */
  if (USBD_Init(&hUSBD_Device_CDC, &CDC_Desc, 0) == USBD_OK) {

    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK) {

      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_CDC_fops) == USBD_OK) {
        /* Start Device Process */
        USBD_Start(&hUSBD_Device_CDC);
      }
    }
  }
#endif /* USBD_USE_CDC */
}

#ifdef USBD_USE_HID_COMPOSITE
/**
  * @brief  Send HID mouse Report
  * @param  report pointer to report
  * @param  len report lenght
  * @retval none
  */
void usbd_interface_mouse_sendReport(uint8_t *report, uint16_t len)
{
  USBD_HID_MOUSE_SendReport(&hUSBD_Device_HID, report, len);
}

/**
  * @brief  Send HID keyboard Report
  * @param  report pointer to report
  * @param  len report lenght
  * @retval none
  */
void usbd_interface_keyboard_sendReport(uint8_t *report, uint16_t len)
{
  USBD_HID_KEYBOARD_SendReport(&hUSBD_Device_HID, report, len);
}
#endif /* USBD_USE_HID_COMPOSITE */

#ifdef __cplusplus
}
#endif
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
