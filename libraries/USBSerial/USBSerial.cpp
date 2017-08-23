/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @brief USB virtual serial terminal
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#ifdef USBCON

#include <string.h>

#include "wiring.h"
#include "USBSerial.h"
#include "usbd_desc.h"
#include "usbd_desc_cdc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

#define USB_TIMEOUT 50
/* USB Device Core handle declaration */
USBD_HandleTypeDef hUSBD_Device_CDC;
extern __IO  uint32_t device_connection_status;
extern __IO  uint32_t lineState;
extern __IO uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];
extern __IO uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern __IO uint32_t UserTxBufPtrIn;
extern __IO uint32_t UserTxBufPtrOut;
extern __IO uint32_t UserRxBufPtrIn;
extern __IO uint32_t UserRxBufPtrOut;
__IO  uint32_t usbEnableBlockingTx;

USBSerial SerialUSB;


USBSerial::USBSerial(void) {
}

/* USBSerial is always available and instantiated in main.cpp */
void USBSerial::begin(void) {
  if (USBD_Init(&hUSBD_Device_CDC, &CDC_Desc, DEVICE_FS) == USBD_OK) {

    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK) {

      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_Interface_fops_FS) == USBD_OK) {

        /* Start Device Process */
        USBD_Start(&hUSBD_Device_CDC);
      }
    }
  }
}

void USBSerial::begin(int) {
  if (USBD_Init(&hUSBD_Device_CDC, &CDC_Desc, DEVICE_FS) == USBD_OK) {

    /* Add Supported Class */
    if (USBD_RegisterClass(&hUSBD_Device_CDC, USBD_CDC_CLASS) == USBD_OK) {

      /* Add CDC Interface Class */
      if (USBD_CDC_RegisterInterface(&hUSBD_Device_CDC, &USBD_Interface_fops_FS) == USBD_OK) {

        /* Start Device Process */
        USBD_Start(&hUSBD_Device_CDC);
      }
    }
  }
}

void USBSerial::end(void) {

  USBD_LL_DeInit(&hUSBD_Device_CDC);
}

int USBSerial::availableForWrite(void)
{
  int ret_val;

  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();

  if(UserTxBufPtrIn >= UserTxBufPtrOut)
  {
    ret_val = (APP_TX_DATA_SIZE - 1 - UserTxBufPtrIn + UserTxBufPtrOut);
  } else
  {
    ret_val = (UserTxBufPtrOut - UserTxBufPtrIn - 1);
  }

  CDC_enable_TIM_Interrupt();

  return ret_val;
}

size_t USBSerial::write(uint8_t ch) {

  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();

  if(((UserTxBufPtrIn + 1) % APP_TX_DATA_SIZE) == UserTxBufPtrOut)
  {
    // Buffer full!!! Force a flush to not loose data and go on
    CDC_flush();
  }
  UserTxBufferFS[UserTxBufPtrIn] = ch;
  UserTxBufPtrIn = ((UserTxBufPtrIn + 1) % APP_TX_DATA_SIZE);

  CDC_enable_TIM_Interrupt();

  return 1;
}

int USBSerial::available(void) {
  int ret;

  CDC_disable_TIM_Interrupt();
  ret = ((APP_RX_DATA_SIZE + (UserRxBufPtrIn - UserRxBufPtrOut)) % APP_RX_DATA_SIZE);
  CDC_enable_TIM_Interrupt();

  return ret;
}

int USBSerial::read(void) {
  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();
  if(UserRxBufPtrOut == UserRxBufPtrIn)
  {
    CDC_enable_TIM_Interrupt();
    return -1;
  } else
  {
    unsigned char c = UserRxBufferFS[UserRxBufPtrOut];
    UserRxBufPtrOut = ((UserRxBufPtrOut + 1) % APP_RX_DATA_SIZE);
    CDC_enable_TIM_Interrupt();
    return c;
  }
}

int USBSerial::peek(void)
{
  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();
  if(UserRxBufPtrOut == UserRxBufPtrIn)
  {
    CDC_enable_TIM_Interrupt();
    return -1;
  } else
  {
    unsigned char c = UserRxBufferFS[UserRxBufPtrOut];
    CDC_enable_TIM_Interrupt();
    return c;
  }
}

void USBSerial::flush(void)
{
  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();
  CDC_flush();
  CDC_enable_TIM_Interrupt();

#if 0
  /* Flush EP1 for data IN */
  USBD_LL_FlushEP(&hUSBD_Device_CDC, CDC_IN_EP);
  /* Flush EP1 for data OUT */
  USBD_LL_FlushEP(&hUSBD_Device_CDC, CDC_IN_EP);
  /* Flush EP1 for CDC commands */
  USBD_LL_FlushEP(&hUSBD_Device_CDC, CDC_IN_EP);

  return;
#endif

}

uint8_t USBSerial::pending(void) {
//    return usbGetPending(); // No equivalent in HAL
  return 0;
}

uint8_t USBSerial::isConnected(void) {

  if(device_connection_status == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

uint8_t USBSerial::getDTR(void) {
//    return usbGetDTR();
  return 0;
}

uint8_t USBSerial::getRTS(void) {
//    return usbGetRTS();
  return 0;
}

USBSerial::operator bool() {
  bool result = false;
  if (lineState == 1)
    result = true;
  delay(10);
 return result;
}

#endif // USBCON
