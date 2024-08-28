/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>

#include "Stream.h"
#include "uart.h"

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
// NOTE: a "power of 2" buffer size is recommended to dramatically
//       optimize all the modulo operations for ring buffers.
#if !defined(SERIAL_TX_BUFFER_SIZE)
  #define SERIAL_TX_BUFFER_SIZE 64
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
  #define SERIAL_RX_BUFFER_SIZE 64
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
  typedef uint16_t tx_buffer_index_t;
#else
  typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
  typedef uint16_t rx_buffer_index_t;
#else
  typedef uint8_t rx_buffer_index_t;
#endif

// A bool should be enough for this
// But it brings an build error due to ambiguous
// call of overloaded HardwareSerial(int, int)
// So defining a dedicated type
typedef enum {
  HALF_DUPLEX_DISABLED,
  HALF_DUPLEX_ENABLED
} HalfDuplexMode_t;

// Define config for Serial.begin(baud, config);
// below configs are not supported by STM32
//#define SERIAL_5N1 0x00
//#define SERIAL_5N2 0x08
//#define SERIAL_5E1 0x20
//#define SERIAL_5E2 0x28
//#define SERIAL_5O1 0x30
//#define SERIAL_5O2 0x38
//#define SERIAL_6N1 0x02
//#define SERIAL_6N2 0x0A

#ifdef UART_WORDLENGTH_7B
  #define SERIAL_7N1 0x04
  #define SERIAL_7N2 0x0C
  #define SERIAL_6E1 0x22
  #define SERIAL_6E2 0x2A
  #define SERIAL_6O1 0x32
  #define SERIAL_6O2 0x3A
#endif
#define SERIAL_8N1 0x06
#define SERIAL_8N2 0x0E
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Stream {
  protected:
    // Has any byte been written to the UART since begin()
    bool _written;

    // Don't put any members after these buffers, since only the first
    // 32 bytes of this struct can be accessed quickly using the ldd
    // instruction.
    unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

    serial_t _serial;

  public:
    HardwareSerial(uint32_t _rx, uint32_t _tx, uint32_t _rts = NUM_DIGITAL_PINS, uint32_t _cts = NUM_DIGITAL_PINS);
    HardwareSerial(PinName _rx, PinName _tx, PinName _rts = NC, PinName _cts = NC);
    HardwareSerial(void *peripheral, HalfDuplexMode_t halfDuplex = HALF_DUPLEX_DISABLED);
    HardwareSerial(uint32_t _rxtx);
    HardwareSerial(PinName _rxtx);
    void begin(unsigned long baud)
    {
      begin(baud, SERIAL_8N1);
    }
    void begin(unsigned long, uint8_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush();
    void flush(uint32_t timeout);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n)
    {
      return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
      return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
      return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
      return write((uint8_t)n);
    }
    size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) from Print
    operator bool()
    {
      return true;
    }

    void setRx(uint32_t _rx);
    void setTx(uint32_t _tx);
    void setRx(PinName _rx);
    void setTx(PinName _tx);

    // Enable HW flow control on RTS, CTS or both
    void setRts(uint32_t _rts);
    void setCts(uint32_t _cts);
    void setRtsCts(uint32_t _rts, uint32_t _cts);
    void setRts(PinName _rts);
    void setCts(PinName _cts);
    void setRtsCts(PinName _rts, PinName _cts);

    // Enable half-duplex mode by setting the Rx pin to NC
    // This needs to be done before the call to begin()
    void setHalfDuplex(void);
    bool isHalfDuplex(void) const;
    void enableHalfDuplexRx(void);

    friend class STM32LowPower;

    // Interrupt handlers
    static void _rx_complete_irq(serial_t *obj);
    static int _tx_complete_irq(serial_t *obj);

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
    // Could be used to mix Arduino API and STM32Cube HAL API (ex: DMA). Use at your own risk.
    UART_HandleTypeDef *getHandle(void)
    {
      return &(_serial.handle);
    }
#endif // HAL_UART_MODULE_ENABLED && !HAL_UART_MODULE_ONLY

  private:
    bool _rx_enabled;
    uint8_t _config;
    unsigned long _baud;
    void init(PinName _rx, PinName _tx, PinName _rts = NC, PinName _cts = NC);
    void configForLowPower(void);
};

#if defined(USART1)
  extern HardwareSerial Serial1;
#endif
#if defined(USART2)
  extern HardwareSerial Serial2;
#endif
#if defined(USART3)
  extern HardwareSerial Serial3;
#endif
#if defined(UART4) || defined(USART4)
  extern HardwareSerial Serial4;
#endif
#if defined(UART5) || defined(USART5)
  extern HardwareSerial Serial5;
#endif
#if defined(USART6)
  extern HardwareSerial Serial6;
#endif
#if defined(UART7) || defined(USART7)
  extern HardwareSerial Serial7;
#endif
#if defined(UART8) || defined(USART8)
  extern HardwareSerial Serial8;
#endif
#if defined(UART9)
  extern HardwareSerial Serial9;
#endif
#if defined(UART10) || defined(USART10)
  extern HardwareSerial Serial10;
#endif
#if defined(LPUART1)
  extern HardwareSerial SerialLP1;
#endif
#if defined(LPUART2)
  extern HardwareSerial SerialLP2;
#endif
#endif
