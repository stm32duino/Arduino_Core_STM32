/**
  ******************************************************************************
  * @file    usbd_hid_composite_if.c
  * @brief   Provide the USB HID composite interface
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
#ifdef USBD_USE_HID_COMPOSITE
#include <stdbool.h>
#include "usbd_desc.h"
#include "usbd_hid_composite_if.h"
#include "usbd_hid_composite.h"

#ifdef __cplusplus
extern "C" {
#endif

/* USB Device Core HID composite handle declaration */
USBD_HandleTypeDef hUSBD_Device_HID;

static bool HID_keyboard_initialized = false;
static bool HID_mouse_initialized = false;

/**
  * @brief  Initialize USB devices
  * @param  HID_Interface device type: HID_KEYBOARD or HID_MOUSE
  * @retval none
  */
void HID_Composite_Init(HID_Interface device)
{
  if (IS_HID_INTERFACE(device) &&
      !HID_keyboard_initialized && !HID_mouse_initialized) {
    /* Init Device Library */
    if (USBD_Init(&hUSBD_Device_HID, &USBD_Desc, 0) == USBD_OK) {
      /* Add Supported Class */
      if (USBD_RegisterClass(&hUSBD_Device_HID, USBD_COMPOSITE_HID_CLASS) == USBD_OK) {
        /* Start Device Process */
        USBD_Start(&hUSBD_Device_HID);
        HID_keyboard_initialized = true;
        HID_mouse_initialized = true;
      }
    }
  }
  if (device == HID_KEYBOARD) {
    HID_keyboard_initialized = HID_mouse_initialized;
  }
  if (device == HID_MOUSE) {
    HID_mouse_initialized = HID_keyboard_initialized;
  }
}

/**
  * @brief  DeInitialize USB devices
  * @param  HID_Interface device type: HID_KEYBOARD or HID_MOUSE
  * @retval none
  */
void HID_Composite_DeInit(HID_Interface device)
{
  if (IS_HID_INTERFACE(device) &&
      ((HID_keyboard_initialized && !HID_mouse_initialized) ||
       (HID_mouse_initialized && !HID_keyboard_initialized))) {
    /* Stop Device Process */
    USBD_Stop(&hUSBD_Device_HID);
    /* DeInit Device Library */
    USBD_DeInit(&hUSBD_Device_HID);
  }
  if (device == HID_KEYBOARD) {
    HID_keyboard_initialized = false;
  }
  if (device == HID_MOUSE) {
    HID_mouse_initialized = false;
  }
}

/**
  * @brief  Send HID mouse Report
  * @param  report pointer to report
  * @param  len report lenght
  * @retval none
  */
void HID_Composite_mouse_sendReport(uint8_t *report, uint16_t len)
{
  USBD_HID_MOUSE_SendReport(&hUSBD_Device_HID, report, len);
}

/**
  * @brief  Send HID keyboard Report
  * @param  report pointer to report
  * @param  len report lenght
  * @retval none
  */
void HID_Composite_keyboard_sendReport(uint8_t *report, uint16_t len)
{
  USBD_HID_KEYBOARD_SendReport(&hUSBD_Device_HID, report, len);
}

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_HID_COMPOSITE */
#endif /* USBCON */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
