/**
  ******************************************************************************
  * @file    usbd_hid_composite_if.h
  * @brief   Header for USB HID composite interface
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_HID_COMPOSITE_IF_H
#define __USBD_HID_COMPOSITE_IF_H
#ifdef USBCON
#ifdef USBD_USE_HID_COMPOSITE

/* Includes ------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  HID_KEYBOARD,
  HID_MOUSE
} HID_Interface;

/* Exported macro ------------------------------------------------------------*/
#define IS_HID_INTERFACE(DEVICE)    (((DEVICE) == HID_KEYBOARD) ||\
                                     ((DEVICE) == HID_MOUSE))

/* Exported functions ------------------------------------------------------- */
void HID_Composite_Init(HID_Interface device);
void HID_Composite_DeInit(HID_Interface device);

void HID_Composite_mouse_sendReport(uint8_t *report, uint16_t len);
void HID_Composite_keyboard_sendReport(uint8_t *report, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /* USBD_USE_HID_COMPOSITE */
#endif /* USBCON */

#endif /* __USBD_HID_COMPOSITE_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
