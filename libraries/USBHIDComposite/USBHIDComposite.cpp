/**
  ******************************************************************************
  * @file    USBHIDComposite.cpp
  * @author  WI6LABS
  * @version V1.0.0
  * @date    27-July-2016
  * @brief   USB HID composite API for Arduino
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

#include "usbd_desc_hid_composite.h"
#include "usbd_hid_composite.h"
#include "USBHIDComposite.h"


USBHIDComposite HID;

USBHIDComposite::USBHIDComposite(void)
{

}

void USBHIDComposite::begin(void)
{
  /* Init Device Library */
  USBD_Init(&hUSBD_Device, &HID_Desc, 0);

  /* Add Supported Class */
  USBD_RegisterClass(&hUSBD_Device, USBD_COMPOSITE_HID_CLASS);

  /* Start Device Process */
  USBD_Start(&hUSBD_Device);
}

void USBHIDComposite::end(void)
{
  /* Stop Device Process */
  USBD_Stop(&hUSBD_Device);
}

void USBHIDComposite::mouseSend(uint8_t *report, uint16_t len)
{
  USBD_HID_MOUSE_SendReport(&hUSBD_Device, report, len);
}

void USBHIDComposite::keyboardSend(uint8_t *report, uint16_t len)
{
  USBD_HID_KEYBOARD_SendReport(&hUSBD_Device, report, len);
}

#endif //USBCON
