/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if defined (USBCON) && defined(USBD_USE_CDC)

#include "USBSerial.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"
#include "wiring.h"

#define USB_TIMEOUT 50
/* USB Device Core handle declaration */
extern USBD_HandleTypeDef hUSBD_Device_CDC;
extern __IO  uint32_t device_connection_status;
extern __IO  uint32_t lineState;
extern __IO uint8_t UserTxBuffer[APP_TX_DATA_SIZE];
extern __IO uint8_t UserRxBuffer[APP_RX_DATA_SIZE];
extern __IO uint32_t UserTxBufPtrIn;
extern __IO uint32_t UserTxBufPtrOut;
extern __IO uint32_t UserRxBufPtrIn;
extern __IO uint32_t UserRxBufPtrOut;

USBSerial SerialUSB;

void USBSerial::begin(uint32_t /* baud_count */) {
  // uart config is ignored in USB-CDC
}

void USBSerial::begin(uint32_t /* baud_count */, uint8_t /* config */) {
  // uart config is ignored in USB-CDC
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

  if (UserTxBufPtrIn >= UserTxBufPtrOut) {
    ret_val = (APP_TX_DATA_SIZE - 1 - UserTxBufPtrIn + UserTxBufPtrOut);
  } else {
    ret_val = (UserTxBufPtrOut - UserTxBufPtrIn - 1);
  }

  CDC_enable_TIM_Interrupt();

  return ret_val;
}

size_t USBSerial::write(uint8_t ch) {

  /* UserTxBufPtrOut can be modified by TIM ISR, so in order to be sure that the */
  /* value that we read is correct, we need to disable TIM Interrupt.            */
  CDC_disable_TIM_Interrupt();

  if (((UserTxBufPtrIn + 1) % APP_TX_DATA_SIZE) == UserTxBufPtrOut) {
    // Buffer full!!! Force a flush to not loose data and go on
    CDC_flush();
  }
  UserTxBuffer[UserTxBufPtrIn] = ch;
  UserTxBufPtrIn = ((UserTxBufPtrIn + 1) % APP_TX_DATA_SIZE);

  CDC_enable_TIM_Interrupt();

  return 1;
}

size_t USBSerial::write(const uint8_t *buffer, size_t size){
  size_t i = 0;
  for (i=0; i < size; i++) {
    if (write(buffer[i]) != 1) {
      break;
	}
  }
  return i;
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
  if (UserRxBufPtrOut == UserRxBufPtrIn) {
    CDC_enable_TIM_Interrupt();
    return -1;
  } else {
    unsigned char c = UserRxBuffer[UserRxBufPtrOut];
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
  if (UserRxBufPtrOut == UserRxBufPtrIn) {
    CDC_enable_TIM_Interrupt();
    return -1;
  } else {
    unsigned char c = UserRxBuffer[UserRxBufPtrOut];
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
}

uint8_t USBSerial::pending(void) {
  return 0;
}

uint8_t USBSerial::isConnected(void) {

  if (device_connection_status == 1) {
    return 1;
  } else {
    return 0;
  }
}

uint32_t USBSerial::baud() {
  return 115200;
}

uint8_t USBSerial::stopbits() {
  return ONE_STOP_BIT;
}

uint8_t USBSerial::paritytype() {
  return NO_PARITY;
}

uint8_t USBSerial::numbits() {
  return 8;
}

bool USBSerial::dtr(void) {
  return false;
}

bool USBSerial::rts(void) {
  return false;
}

USBSerial::operator bool() {
  bool result = false;
  if (lineState == 1)
    result = true;
  delay(10);
 return result;
}

#endif // USBCON && USBD_USE_CDC
