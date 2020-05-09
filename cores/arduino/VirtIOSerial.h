/**
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

#ifndef _VIRTIOSERIAL_H_
#define _VIRTIOSERIAL_H_

#if defined (VIRTIOCON)
#include "Stream.h"
#include "openamp.h"
#include "wiring.h"
#include "virtio_buffer.h"

//================================================================================
// Serial over OpenAMP

// This structure is used to be able to get VirtIOSerial instance (C++ class)
// from handler (C structure) specially for rpmsg message management
typedef struct  {
  // Those 2 first fields must remain in this order at the beginning of the structure
  void    *__this;
  VIRT_UART_HandleTypeDef handle;
  bool initialized;
  bool first_message_discarded;
  virtio_buffer_t ring;
} VirtIOSerialObj_t;


class VirtIOSerial : public Stream {
  public:
    void begin(void);
    void begin(uint32_t);
    void begin(uint32_t, uint8_t);
    void end(void);

    virtual int available(void);
    virtual int availableForWrite(void);
    virtual int peek(void);
    virtual int read(void);
    virtual size_t readBytes(char *buffer, size_t length);  // read chars from stream into buffer
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual void flush(void);

    static void rxGenericCallback(VIRT_UART_HandleTypeDef *huart);
    void rxCallback(VIRT_UART_HandleTypeDef *huart);

    using Print::write; // pull in write(str) from Print
    operator bool(void)
    {
      return true;
    }

  private:
    static uint32_t VirtIOSerial_index;
    VirtIOSerialObj_t _VirtIOSerialObj;
    void checkMessageFromISR(void);
};

extern VirtIOSerial SerialVirtIO;

#endif /* VIRTIOCON */
#endif /* _VIRTIOSERIAL_H_ */
