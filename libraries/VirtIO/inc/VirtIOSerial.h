/*
 * MIT License:
 * Copyright (c) 2019 Bumsik kim <k.bumsik@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @file    VirtIOSerial.h
 * @brief   Serial (Stream) over OpenAMP to communicate with the Linux host.
 */

#ifndef _VIRTIOSERIAL_H_
#define _VIRTIOSERIAL_H_

#if defined (VIRTIOCON)
#include "Stream.h"
#include "openamp.h"
#include "wiring.h"
#include "virtio_buffer.h"

//================================================================================
// Serial over OpenAMP

/**
 * @brief Context of a VirtIOSerial instance.
 *
 * Used to get the VirtIOSerial instance (C++ class) from the VIRT_UART
 * handle (C structure), specially for rpmsg message management.
 * @note The first two fields (__this and handle) must remain in this order
 * at the beginning of the structure.
 */
typedef struct  {
  void    *__this;
  VIRT_UART_HandleTypeDef handle;
  bool initialized;
  bool first_message_discarded;
  virtio_buffer_t ring;
} VirtIOSerialObj_t;

/**
 * @brief Serial (Stream) over OpenAMP, used to communicate with the Linux host.
 */
class VirtIOSerial : public Stream {
  public:
    /**
     * @brief Start the serial link. Blocks until the Linux host sends its first message.
     */
    void begin(void);

    /**
     * @brief Start the serial link. The baud rate is ignored, OpenAMP has
     *        no UART configuration.
     * @param baud_count Baud rate (ignored).
     */
    void begin(uint32_t baud_count);

    /**
     * @brief Start the serial link. The baud rate and configuration are
     *        ignored, OpenAMP has no UART configuration.
     * @param baud_count Baud rate (ignored).
     * @param config Serial configuration (ignored).
     */
    void begin(uint32_t baud_count, uint8_t config);

    /**
     * @brief Stop the serial link and release the OpenAMP resources.
     */
    void end(void);

    /**
     * @brief Get the number of bytes available to read.
     * @return Number of bytes in the receive buffer.
     */
    virtual int available(void);

    /**
     * @brief Get the maximum number of bytes that one write() can send.
     * @return RPMSG_VRING_PAYLOAD_SIZE.
     */
    virtual int availableForWrite(void);

    /**
     * @brief Get the next byte without removing it from the receive buffer.
     * @return The next byte, or -1 if the receive buffer is empty.
     */
    virtual int peek(void);

    /**
     * @brief Read one byte from the receive buffer.
     * @return The byte read, or -1 if the receive buffer is empty.
     */
    virtual int read(void);

    /**
     * @brief Read bytes from the receive buffer into a buffer.
     * @param buffer Destination buffer.
     * @param length Maximum number of bytes to read.
     * @return Number of bytes read.
     */
    virtual size_t readBytes(char *buffer, size_t length);

    /**
     * @brief Write one byte.
     * @param ch Byte to write.
     * @return Number of bytes written: 1 on success, 0 on failure.
     */
    virtual size_t write(uint8_t ch);

    /**
     * @brief Write a buffer of bytes.
     *
     * The implementation is synchronous: it blocks until all bytes are sent.
     * @param buffer Data to send.
     * @param size Number of bytes to send. Must not exceed availableForWrite().
     * @return Number of bytes written, or 0 on failure.
     */
    virtual size_t write(const uint8_t *buffer, size_t size);

    /**
     * @brief Wait until all written bytes are sent. Does nothing, because
     *        write() already blocks until the data is sent.
     */
    virtual void flush(void);

    /**
     * @brief Static RX callback registered with the VIRT_UART driver.
     * @param huart VIRT_UART handle that received the message.
     */
    static void rxGenericCallback(VIRT_UART_HandleTypeDef *huart);

    /**
     * @brief RX callback for one VirtIOSerial instance. Copies the received
     *        data into the receive ring buffer.
     * @param huart VIRT_UART handle that received the message.
     * @note  The first message from the Linux host is a dummy, and is discarded.
     */
    void rxCallback(VIRT_UART_HandleTypeDef *huart);

    using Print::write; // pull in write(str) from Print

    /**
     * @brief Check whether the serial port is available.
     * @return Always true.
     */
    operator bool(void)
    {
      return true;
    }

  private:
    static uint32_t VirtIOSerial_index;
    VirtIOSerialObj_t _VirtIOSerialObj;

    /**
     * @brief Check if an RPMsg message arrived from the IPCC ISR.
     * @note  Call this as often as possible to consume the RPMsg ring
     *        buffers, so that the host processor can send more messages quickly.
     */
    void checkMessageFromISR(void);
};

/**
 * @brief Default VirtIOSerial instance.
 */
extern VirtIOSerial SerialVirtIO;

/**
 * @example loopback.ino
 * Echo the data received from the Linux host through VirtIOSerial.
 */

#endif /* VIRTIOCON */
#endif /* _VIRTIOSERIAL_H_ */
