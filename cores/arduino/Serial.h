/*
  Serial.h - Hardware serial library for Wiring
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

#include "api/Common.h"
#include "HardwareSerial.h"
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
// call of overloaded Uart(int, int)
// So defining a dedicated type
typedef enum {
  HALF_DUPLEX_DISABLED,
  HALF_DUPLEX_ENABLED
} HalfDuplexMode_t;

// below configs are not supported by STM32
#undef SERIAL_PARITY_MARK
#undef SERIAL_PARITY_SPACE
#undef SERIAL_STOP_BIT_1_5

#undef SERIAL_5M1
#undef SERIAL_6M1
#undef SERIAL_7M1
#undef SERIAL_8M1
#undef SERIAL_5M2
#undef SERIAL_6M2
#undef SERIAL_7M2
#undef SERIAL_8M2
#undef SERIAL_5S1
#undef SERIAL_6S1
#undef SERIAL_7S1
#undef SERIAL_8S1
#undef SERIAL_5S2
#undef SERIAL_6S2
#undef SERIAL_7S2
#undef SERIAL_8S2

#undef SERIAL_DATA_5
#undef SERIAL_5N1
#undef SERIAL_5N2
#undef SERIAL_5E1
#undef SERIAL_5E2
#undef SERIAL_5O1
#undef SERIAL_5O2

#undef SERIAL_6N1
#undef SERIAL_6N2

#if !defined(UART_WORDLENGTH_7B) && !defined(HAL_UART_WORD_LENGTH_7_BIT)
  #undef SERIAL_7N1
  #undef SERIAL_7N2
  #undef SERIAL_6E1
  #undef SERIAL_6E2
  #undef SERIAL_6O1
  #undef SERIAL_6O2
#endif

/**
 * @brief STM32 hardware UART. Implements the Arduino Stream and HardwareSerial API.
 *
 * Use one of the constructors to bind a UART to pins or to a peripheral, then call begin().
 */
class Uart : public arduino::HardwareSerial {
  protected:
    // Has any byte been written to the UART since begin()
    bool _written;
    bool _rx_invert;
    bool _tx_invert;
    bool _data_invert;

    // Don't put any members after these buffers, since only the first
    // 32 bytes of this struct can be accessed quickly using the ldd
    // instruction.
    unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

    serial_t _serial;

  public:
    /**
     * @brief Create a UART from Arduino digital pin numbers.
     *
     * @param _rx Digital pin used for RX.
     * @param _tx Digital pin used for TX.
     * @param _rts Digital pin used for RTS flow control, NUM_DIGITAL_PINS if unused.
     * @param _cts Digital pin used for CTS flow control, NUM_DIGITAL_PINS if unused.
     */
    Uart(pin_size_t _rx, pin_size_t _tx, pin_size_t _rts = NUM_DIGITAL_PINS, pin_size_t _cts = NUM_DIGITAL_PINS);
    /**
     * @brief Create a UART from STM32 pin names.
     *
     * @param _rx Pin used for RX.
     * @param _tx Pin used for TX.
     * @param _rts Pin used for RTS flow control, NC if unused.
     * @param _cts Pin used for CTS flow control, NC if unused.
     */
    Uart(PinName _rx, PinName _tx, PinName _rts = NC, PinName _cts = NC);
    /**
     * @brief Create a UART from an STM32 USART/UART peripheral. Pins are taken from the variant.
     *
     * @param peripheral USART/UART peripheral instance, e.g. USART1.
     * @param halfDuplex HALF_DUPLEX_ENABLED to use the TX pin only.
     */
    Uart(void *peripheral, HalfDuplexMode_t halfDuplex = HALF_DUPLEX_DISABLED);
    /**
     * @brief Create a half-duplex UART on a single digital pin. The pin is used as TX and RX is NC.
     *
     * @param _rxtx Digital pin used for TX.
     */
    Uart(pin_size_t _rxtx);
    /**
     * @brief Create a half-duplex UART on a single STM32 pin. The pin is used as TX and RX is NC.
     *
     * @param _rxtx Pin used for TX.
     */
    Uart(PinName _rxtx);
    /**
     * @brief Start the UART with 8 data bits, no parity and 1 stop bit (SERIAL_8N1).
     *
     * @param baud Baud rate in bits per second.
     */
    void begin(unsigned long baud) override
    {
      begin(baud, SERIAL_8N1);
    }
    /**
     * @brief Start the UART with the given baud rate and frame format.
     *
     * @param baud Baud rate in bits per second.
     * @param config Frame format, e.g. SERIAL_8N1 or SERIAL_8E1.
     */
    void begin(unsigned long baud, uint16_t config) override ;

    // Implement all pure virtuals
    /**
     * @brief Wait for pending transmission, stop the UART, release its pins and clear the receive buffer.
     */
    void end() override;
    /**
     * @brief Get the number of bytes available to read.
     *
     * @return Number of bytes in the receive buffer.
     */
    int available(void) override;
    /**
     * @brief Read the next byte without removing it from the receive buffer.
     *
     * @return Next byte, or -1 if none is available.
     */
    int peek(void) override;
    /**
     * @brief Read and remove the next byte from the receive buffer.
     *
     * @return Next byte, or -1 if none is available.
     */
    int read(void) override;
    /**
     * @brief Wait until all queued bytes are transmitted.
     */
    void flush() override;
    /**
     * @brief Write one byte.
     *
     * @param c Byte to write.
     * @return Number of bytes written: 1, or 0 if the UART is not started.
     */
    size_t write(uint8_t) override;
    /**
     * @brief Check whether the UART is started.
     *
     * @return true if begin() was called and the UART is ready.
     */
    operator bool() override
    {
      return _ready;
    }

    // STM32 extension
    /**
     * @brief Get the number of bytes that can be written without blocking.
     *
     * @return Free space in the transmit buffer, in bytes.
     */
    int availableForWrite(void);
    /**
     * @brief Wait until all queued bytes are transmitted, or until a timeout elapses.
     *
     * @param timeout Maximum wait in milliseconds. 0 waits without limit.
     *        On timeout, the pending transmit data is discarded.
     */
    void flush(uint32_t timeout);

    /**
     * @brief Write one byte, truncating the value to 8 bits.
     *
     * @param n Value to write.
     * @return Number of bytes written.
     */
    inline size_t write(unsigned long n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write one byte, truncating the value to 8 bits.
     *
     * @param n Value to write.
     * @return Number of bytes written.
     */
    inline size_t write(long n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write one byte, truncating the value to 8 bits.
     *
     * @param n Value to write.
     * @return Number of bytes written.
     */
    inline size_t write(unsigned int n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write one byte, truncating the value to 8 bits.
     *
     * @param n Value to write.
     * @return Number of bytes written.
     */
    inline size_t write(int n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write a buffer of bytes.
     *
     * @param buffer Data to write.
     * @param size Number of bytes in buffer.
     * @return Number of bytes written, 0 if the UART is not started.
     */
    size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) from Print

    /**
     * @brief Set the RX pin by Arduino pin number. Call before begin().
     *
     * @param _rx Digital pin used for RX.
     */
    void setRx(pin_size_t _rx);
    /**
     * @brief Set the TX pin by Arduino pin number. Call before begin().
     *
     * @param _tx Digital pin used for TX.
     */
    void setTx(pin_size_t _tx);
    /**
     * @brief Set the RX pin by STM32 pin name. Call before begin().
     *
     * @param _rx Pin used for RX.
     */
    void setRx(PinName _rx);
    /**
     * @brief Set the TX pin by STM32 pin name. Call before begin().
     *
     * @param _tx Pin used for TX.
     */
    void setTx(PinName _tx);

    // Enable HW flow control on RTS, CTS or both
    /**
     * @brief Enable hardware RTS flow control on a digital pin. Call before begin().
     *
     * @param _rts Digital pin used for RTS.
     */
    void setRts(pin_size_t _rts);
    /**
     * @brief Enable hardware CTS flow control on a digital pin. Call before begin().
     *
     * @param _cts Digital pin used for CTS.
     */
    void setCts(pin_size_t _cts);
    /**
     * @brief Enable hardware RTS and CTS flow control on digital pins. Call before begin().
     *
     * @param _rts Digital pin used for RTS.
     * @param _cts Digital pin used for CTS.
     */
    void setRtsCts(pin_size_t _rts, pin_size_t _cts);
    /**
     * @brief Enable hardware RTS flow control on an STM32 pin. Call before begin().
     *
     * @param _rts Pin used for RTS.
     */
    void setRts(PinName _rts);
    /**
     * @brief Enable hardware CTS flow control on an STM32 pin. Call before begin().
     *
     * @param _cts Pin used for CTS.
     */
    void setCts(PinName _cts);
    /**
     * @brief Enable hardware RTS and CTS flow control on STM32 pins. Call before begin().
     *
     * @param _rts Pin used for RTS.
     * @param _cts Pin used for CTS.
     */
    void setRtsCts(PinName _rts, PinName _cts);

    // Enable half-duplex mode by setting the Rx pin to NC
    // This needs to be done before the call to begin()
    /**
     * @brief Enable half-duplex mode by setting the RX pin to NC. Call before begin().
     */
    void setHalfDuplex(void);
    /**
     * @brief Check whether the UART is in half-duplex mode.
     *
     * @return true if the RX pin is NC.
     */
    bool isHalfDuplex(void) const;
    /**
     * @brief Enable reception in half-duplex mode after the pending transmission ends.
     */
    void enableHalfDuplexRx(void);

    // Enable HW Rx/Tx/data inversion
    // This needs to be done before the call to begin()
    /**
     * @brief Invert the RX line in hardware. Call before begin().
     */
    void setRxInvert(void);
    /**
     * @brief Invert the TX line in hardware. Call before begin().
     */
    void setTxInvert(void);
    /**
     * @brief Invert the data bits in hardware. Call before begin().
     */
    void setDataInvert(void);

    friend class STM32LowPower;

    // Interrupt handlers
    /**
     * @brief RX interrupt handler. Stores the received byte in the receive buffer.
     *
     * @param obj UART object that received the byte.
     */
    static void _rx_complete_irq(serial_t *obj);
    /**
     * @brief TX interrupt handler. Starts the next chunk of queued data, if any.
     *
     * @param obj UART object whose transfer completed.
     * @return -1 if a new transfer was started, 0 if the transmit buffer is empty.
     */
    static int _tx_complete_irq(serial_t *obj);

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
    // Could be used to mix Arduino API and STM32Cube HAL API (ex: DMA). Use at your own risk.
#if defined(USE_HALV2_DRIVER)
    /**
     * @brief Get the underlying HAL UART handle.
     *
     * @return Pointer to the HAL UART handle.
     */
    hal_uart_handle_t *getHandle(void)
#else
    /**
     * @brief Get the underlying HAL UART handle.
     *
     * @return Pointer to the HAL UART handle.
     */
    UART_HandleTypeDef *getHandle(void)
#endif
    {
      return &(_serial.handle);
    }
#endif // HAL_UART_MODULE_ENABLED && !HAL_UART_MODULE_ONLY

  private:
    bool _ready;
    bool _rx_enabled;
    uint16_t _config;
    unsigned long _baud;
    /**
     * @brief Initialize the UART object with STM32 pin names.
     *
     * @param _rx Pin used for RX.
     * @param _tx Pin used for TX.
     * @param _rts Pin used for RTS, NC if unused.
     * @param _cts Pin used for CTS, NC if unused.
     */
    void init(PinName _rx, PinName _tx, PinName _rts = NC, PinName _cts = NC);
    /**
     * @brief Reconfigure the UART for low-power operation.
     */
    void configForLowPower(void);
};



#if defined(USART1)
  /**
   * @brief Hardware serial port 1 (USART1).
   */
  extern Uart Serial1;
#endif
#if defined(USART2)
  /**
   * @brief Hardware serial port 2 (USART2).
   */
  extern Uart Serial2;
#endif
#if defined(USART3)
  /**
   * @brief Hardware serial port 3 (USART3).
   */
  extern Uart Serial3;
#endif
#if defined(UART4) || defined(USART4)
  /**
   * @brief Hardware serial port 4 (UART4 or USART4).
   */
  extern Uart Serial4;
#endif
#if defined(UART5) || defined(USART5)
  /**
   * @brief Hardware serial port 5 (UART5 or USART5).
   */
  extern Uart Serial5;
#endif
#if defined(USART6)
  /**
   * @brief Hardware serial port 6 (USART6).
   */
  extern Uart Serial6;
#endif
#if defined(UART7) || defined(USART7)
  /**
   * @brief Hardware serial port 7 (UART7 or USART7).
   */
  extern Uart Serial7;
#endif
#if defined(UART8) || defined(USART8)
  /**
   * @brief Hardware serial port 8 (UART8 or USART8).
   */
  extern Uart Serial8;
#endif
#if defined(UART9)
  /**
   * @brief Hardware serial port 9 (UART9).
   */
  extern Uart Serial9;
#endif
#if defined(UART10) || defined(USART10)
  /**
   * @brief Hardware serial port 10 (UART10 or USART10).
   */
  extern Uart Serial10;
#endif
#if defined(LPUART1)
  /**
   * @brief Low-power serial port 1 (LPUART1).
   */
  extern Uart SerialLP1;
#endif
#if defined(LPUART2)
  /**
   * @brief Low-power serial port 2 (LPUART2).
   */
  extern Uart SerialLP2;
#endif
#if defined(LPUART3)
  /**
   * @brief Low-power serial port 3 (LPUART3).
   */
  extern Uart SerialLP3;
#endif
#endif
