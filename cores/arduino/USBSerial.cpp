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
extern __IO  uint32_t lineState;

USBSerial SerialUSB;

void USBSerial::begin() {
  pinMode(PA12, OUTPUT);
  digitalWrite(PA12, LOW);
  delay(100);
  CDC_init();
}

void USBSerial::begin(uint32_t /* baud_count */) {
  begin();
}

void USBSerial::begin(uint32_t /* baud_count */, uint8_t /* config */) {
  begin();
}

void USBSerial::end() {
  CDC_deInit();
}

int USBSerial::availableForWrite()
{
    // just transmit queue size, available for write
    return static_cast<int>(CDC_TransmitQueue_WriteSize(&TransmitQueue));
}

size_t USBSerial::write(uint8_t ch) {
    // just write single-byte buffer.
    return write(&ch, 1);
}

size_t USBSerial::write(const uint8_t *buffer, size_t size){
    size_t rest = size;
    while(rest > 0) {
        // Determine buffer size available for write
        auto portion = (size_t)CDC_TransmitQueue_WriteSize(&TransmitQueue);
        // Truncate it to content size (if rest is greater)
        if (rest < portion) {
            portion = rest;
        }
        if (portion > 0) {
            // Only if some space in the buffer exists.
            // TS: Only main thread calls write and writeSize methods,
            // it's thread-safe since IRQ does not affects
            // TransmitQueue write position
            CDC_TransmitQueue_Enqueue(&TransmitQueue, buffer, portion);
            rest -= portion;
            buffer += portion;
            // After storing data, start transmitting process
            CDC_continue_transmit();
        }
    }
    return size;
}

int USBSerial::available(void) {
    // just ReceiveQueue size, available for reading
    return static_cast<int>(CDC_ReceiveQueue_ReadSize(&ReceiveQueue));
}

int USBSerial::read(void) {
    // Empty ReceiveQueue - nothing to return
    if (CDC_ReceiveQueue_ReadSize(&ReceiveQueue) <= 0) {
        return -1;
    }
    // Dequeue only one char from queue
    // TS: it safe, because only main thread affects ReceiveQueue->read pos
    char ch = CDC_ReceiveQueue_Dequeue(&ReceiveQueue);
    // resume receive process, if possible
    CDC_resume_receive();
    return ch;
}

int USBSerial::peek(void)
{
    // Empty ReceiveQueue - nothing to return
    if (CDC_ReceiveQueue_ReadSize(&ReceiveQueue) <= 0) {
        return -1;
    }
    // Peek one symbol, it can't change receive avaiablity
    return CDC_ReceiveQueue_Peek(&ReceiveQueue);
}

void USBSerial::flush(void)
{
    // Wait for TransmitQueue read size becomes zero
    // TS: safe, because it not be stopped while receive 0
    while(CDC_TransmitQueue_ReadSize(&TransmitQueue) > 0) {}
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
