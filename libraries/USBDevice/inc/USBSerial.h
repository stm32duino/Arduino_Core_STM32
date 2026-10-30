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

#ifndef _USBSERIAL_H_
#define _USBSERIAL_H_

#if defined (USBCON) && defined(USBD_USE_CDC)
#include "Stream.h"
#include "usbd_core.h"

//================================================================================
// Serial over CDC
/**
 * @brief Serial port over USB CDC (virtual COM port).
 *        Implements the Arduino Stream API on top of the CDC transmit and
 *        receive queues. Use the SerialUSB global instance.
 */
class USBSerial : public Stream {
  public:
    /**
     * @brief Initialize the USB CDC serial port.
     */
    void begin(void);

    /**
     * @brief Initialize the USB CDC serial port.
     * @note  The baud rate argument is ignored by USB CDC. It only exists
     *        for compatibility with the HardwareSerial API.
     * @param baud_count Baud rate (ignored).
     */
    void begin(uint32_t baud_count);

    /**
     * @brief Initialize the USB CDC serial port.
     * @note  The baud rate and serial configuration arguments are ignored
     *        by USB CDC. They only exist for compatibility with the HardwareSerial API.
     * @param baud_count Baud rate (ignored).
     * @param config Serial configuration (ignored).
     */
    void begin(uint32_t baud_count, uint8_t config);

    /**
     * @brief Stop the USB CDC serial port.
     */
    void end(void);

    /**
     * @brief Get the number of bytes available to read.
     * @return Number of bytes in the receive queue.
     */
    virtual int available(void);

    /**
     * @brief Get the number of bytes that can be written without blocking.
     * @return Free space in the transmit queue, in bytes.
     */
    virtual int availableForWrite(void);

    /**
     * @brief Get the next byte without removing it from the receive queue.
     * @return The next byte, or -1 if the receive queue is empty.
     */
    virtual int peek(void);

    /**
     * @brief Read one byte from the receive queue.
     * @return The byte read, or -1 if the receive queue is empty.
     */
    virtual int read(void);

    /**
     * @brief Read bytes from the stream into a buffer. Stops at the timeout
     *        set by setTimeout().
     * @param buffer Destination buffer.
     * @param length Maximum number of bytes to read.
     * @return Number of bytes read.
     */
    virtual size_t readBytes(char *buffer, size_t length);

    /**
     * @brief Read bytes from the stream into a buffer. Same as the char overload.
     * @param buffer Destination buffer.
     * @param length Maximum number of bytes to read.
     * @return Number of bytes read.
     */
    size_t readBytes(uint8_t *buffer, size_t length)
    {
      return readBytes((char *)buffer, length);
    }

    /**
     * @brief Read bytes from the stream into a buffer, stopping after the
     *        terminator character. Stops at the timeout set by setTimeout().
     * @param terminator Character that ends the read. It is consumed but not
     *                   stored in the buffer.
     * @param buffer Destination buffer.
     * @param length Maximum number of bytes to read.
     * @return Number of bytes stored in the buffer, terminator excluded.
     */
    virtual size_t readBytesUntil(char terminator, char *buffer, size_t length);

    /**
     * @brief Read bytes until the terminator character. Same as the char overload.
     * @param terminator Character that ends the read. It is consumed but not
     *                   stored in the buffer.
     * @param buffer Destination buffer.
     * @param length Maximum number of bytes to read.
     * @return Number of bytes stored in the buffer, terminator excluded.
     */
    size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length)
    {
      return readBytesUntil(terminator, (char *)buffer, length);
    }

    /**
     * @brief Wait until all written bytes are sent over USB.
     */
    virtual void flush(void);

    /**
     * @brief Write one byte. Blocks until the byte is queued, or until the host disconnects.
     * @param ch Byte to write.
     * @return Number of bytes written: 1 on success, 0 on failure.
     */
    virtual size_t write(uint8_t ch);

    /**
     * @brief Write a buffer of bytes. Blocks until all bytes are queued, or
     *        until the host disconnects.
     * @param buffer Data to send.
     * @param size Number of bytes to send.
     * @return Number of bytes written.
     */
    virtual size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) from Print

    /**
     * @brief Check whether the USB host has opened the port.
     * @note  Waits 10 ms before reading the DTR state.
     * @return The DTR state set by the host.
     */
    operator bool(void);

    /**
     * @brief Get the baud rate set by the USB host.
     * @note  The value is informational. It is not used by USB CDC.
     * @return Baud rate.
     */
    uint32_t baud();

    /**
     * @brief Get the stop bits set by the USB host.
     * @note  The value is informational. It is not used by USB CDC.
     * @return Stop bits setting, one of ONE_STOP_BIT, ONE_AND_HALF_STOP_BIT, or TWO_STOP_BITS.
     */
    uint8_t stopbits();

    /**
     * @brief Get the parity type set by the USB host.
     * @note  The value is informational. It is not used by USB CDC.
     * @return Parity setting, one of NO_PARITY, ODD_PARITY, EVEN_PARITY,
     *         MARK_PARITY, or SPACE_PARITY.
     */
    uint8_t paritytype();

    /**
     * @brief Get the number of data bits set by the USB host.
     * @note  The value is informational. It is not used by USB CDC.
     * @return Number of data bits.
     */
    uint8_t numbits();

    /**
     * @brief Set the DTR line state.
     * @param enable true to set DTR, false to clear it.
     */
    void dtr(bool enable);

    /**
     * @brief Get the DTR line state.
     * @return The DTR state.
     */
    bool dtr();

    /**
     * @brief Get the RTS line state.
     * @return The RTS state set by the host.
     */
    bool rts();

    /** @brief Stop bits values returned by stopbits(). */
    enum {
      ONE_STOP_BIT = 0,
      ONE_AND_HALF_STOP_BIT = 1,
      TWO_STOP_BITS = 2,
    };
    /** @brief Parity values returned by paritytype(). */
    enum {
      NO_PARITY = 0,
      ODD_PARITY = 1,
      EVEN_PARITY = 2,
      MARK_PARITY = 3,
      SPACE_PARITY = 4,
    };
};

/** @brief Global USB CDC serial port instance. */
extern USBSerial SerialUSB;
#endif /* USBCON */
#endif /* _USBSERIAL_H_ */
