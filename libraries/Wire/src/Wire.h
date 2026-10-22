/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
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

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#ifndef TwoWire_h
#define TwoWire_h

#include <functional>

#include "Arduino.h"
#include "api/HardwareI2C.h"
extern "C" {
#include "utility/twi.h"
}

// Minimal buffer length. Buffers length will be increased when needed,
// but TX buffer is limited to a maximum to avoid too much stack consumption
// Note: Buffer length and max buffer length are limited by uin16_t type
#define BUFFER_LENGTH 32
#if !defined(WIRE_MAX_TX_BUFF_LENGTH)
  #define WIRE_MAX_TX_BUFF_LENGTH       1024U
#endif

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

/**
 * @brief TWI/I2C (Wire) controller, usable as master or slave.
 */
class TwoWire : public arduino::HardwareI2C {
  public:
    /** @brief Callback type for slave receive events, called with the number of bytes received. */
    typedef std::function<void(int)> cb_function_receive_t;
    /** @brief Callback type for slave request events. */
    typedef std::function<void(void)> cb_function_request_t;

  private:
    uint8_t *rxBuffer;
    uint16_t rxBufferAllocated;
    uint16_t rxBufferIndex;
    uint16_t rxBufferLength;

    uint8_t txAddress;
    uint8_t *txBuffer;
    uint16_t txBufferAllocated;
    uint16_t txDataSize;

    uint8_t transmitting;

    uint8_t ownAddress;
    i2c_t _i2c;

    std::function<void(int)> user_onReceive;
    std::function<void(void)> user_onRequest;

    /**
     * @brief Behind the scenes function called when a slave request event occurs. Calls the user onRequest callback.
     * @param obj Pointer to the I2C instance of the event.
     */
    static void onRequestService(i2c_t *obj);
    /**
     * @brief Behind the scenes function called when a slave receive event occurs. Copies the received data and calls the user onReceive callback.
     * @param obj Pointer to the I2C instance of the event.
     */
    static void onReceiveService(i2c_t *obj);

    /**
     * @brief Allocate the Rx buffer to the requested length if needed.
     * @note Minimum allocated size is BUFFER_LENGTH.
     * @param length Number of bytes to allocate.
     */
    void allocateRxBuffer(size_t length);
    /**
     * @brief Allocate the Tx buffer to the requested length if needed.
     * @note Minimum allocated size is BUFFER_LENGTH.
     * @param length Number of bytes to allocate.
     * @return Number of bytes that can be stored in the Tx buffer, 0 if length is greater than WIRE_MAX_TX_BUFF_LENGTH.
     */
    size_t allocateTxBuffer(size_t length);

    /**
     * @brief Reset the Rx buffer content to 0.
     */
    void resetRxBuffer(void);
    /**
     * @brief Reset the Tx buffer content to 0.
     */
    void resetTxBuffer(void);
    /**
     * @brief Send a clear bus (clock pulse) sequence to recover the bus.
     *
     * Useful if the bus is stuck after a reset. Called by begin() in master mode.
     */
    void recoverBus(void);

  public:
    // setSCL/SDA have to be called before begin()
    /**
     * @brief Construct a TwoWire instance using the given pins.
     * @param sda Pin used for SDA. Default: SDA.
     * @param scl Pin used for SCL. Default: SCL.
     */
    TwoWire(pin_size_t sda = SDA, pin_size_t scl = SCL);
    /**
     * @brief Destroy the instance, stopping the TWI interface and releasing its buffers (calls end()).
     */
    ~TwoWire();
    /**
     * @brief Set the SCL pin. Must be called before begin().
     * @param scl Pin used for SCL.
     */
    void setSCL(pin_size_t scl)
    {
      _i2c.scl = digitalPinToPinName(scl);
    };
    /**
     * @brief Set the SDA pin. Must be called before begin().
     * @param sda Pin used for SDA.
     */
    void setSDA(pin_size_t sda)
    {
      _i2c.sda = digitalPinToPinName(sda);
    };
    /**
     * @brief Set the SCL pin. Must be called before begin().
     * @param scl PinName used for SCL.
     */
    void setSCL(PinName scl)
    {
      _i2c.scl = scl;
    };
    /**
     * @brief Set the SDA pin. Must be called before begin().
     * @param sda PinName used for SDA.
     */
    void setSDA(PinName sda)
    {
      _i2c.sda = sda;
    };
    /**
     * @brief Initialize the TWI interface as master.
     * @param generalCall true to enable the general call address. Default: false.
     */
    void begin(bool generalCall);
    /**
     * @brief Initialize the TWI interface as master using the given pins.
     * @param sda Pin used for SDA.
     * @param scl Pin used for SCL.
     */
    void begin(pin_size_t sda, pin_size_t scl);
    /**
     * @brief Initialize the TWI interface as master or slave.
     *
     * The reserved address 0x01 initializes the interface as master,
     * any other address initializes it as slave using this address.
     * @param address 7-bit own address for slave mode, 0x01 for master mode.
     * @param generalCall true to enable the general call address. Default: false.
     * @param NoStretchMode true to disable clock stretching. Default: false.
     */
    void begin(uint8_t address, bool generalCall = false, bool NoStretchMode = false);
    /**
     * @brief Initialize the TWI interface as master or slave.
     *
     * The reserved address 0x01 initializes the interface as master,
     * any other address initializes it as slave using this address.
     * @param address 7-bit own address for slave mode, 0x01 for master mode.
     * @param generalCall true to enable the general call address. Default: false.
     * @param NoStretchMode true to disable clock stretching. Default: false.
     */
    void begin(int address, bool generalCall = false, bool NoStretchMode = false);
    /**
     * @brief Initialize the TWI interface as master with the default pins.
     */
    void begin() override
    {
      begin(false);
    }
    /**
     * @brief Initialize the TWI interface as master or slave with the default pins.
     * @param address 7-bit own address for slave mode, 0x01 for master mode.
     */
    void begin(uint8_t address) override
    {
      begin(address, false, false);
    }
    /**
     * @brief Stop the TWI interface and free the Rx and Tx buffers.
     */
    void end() override;
    /**
     * @brief Set the TWI clock frequency.
     * @param freq Clock frequency in Hz.
     */
    void setClock(uint32_t freq) override;
    /**
     * @brief Begin a transmission to a slave device. Data is stored with write() and sent by endTransmission().
     * @param address 7-bit address of the slave device.
     */
    void beginTransmission(uint8_t address) override;
    /**
     * @brief Begin a transmission to a slave device. Data is stored with write() and sent by endTransmission().
     * @param address 7-bit address of the slave device.
     */
    void beginTransmission(int address);
    /**
     * @brief Send the buffered data to the slave device, ending with a STOP.
     *
     * Equivalent to endTransmission(true).
     * @return 0: success, 1: data too long, 2: NACK on address, 3: NACK on data, 4: other error.
     */
    uint8_t endTransmission(void) override;
    /**
     * @brief Send the buffered data to the slave device and end the transmission.
     *
     * Calling endTransmission(false) allows a repeated start.
     * @warning Nothing keeps track of whether the bus tenure has been ended with a STOP.
     * Leaving the bus without a STOP can hang it, and some I2C devices misbehave without a STOP.
     * @param stopBit true to send a STOP at the end of the transmission, false to keep the bus for a repeated start.
     * @return 0: success, 1: data too long, 2: NACK on address, 3: NACK on data, 4: other error.
     */
    uint8_t endTransmission(bool stopBit) override;

    /**
     * @brief Request bytes from a slave device.
     * @param address 7-bit address of the slave device.
     * @param len Number of bytes to request.
     * @param stopBit true to send a STOP after the request, false to keep the bus for a repeated start.
     * @return Number of bytes read, 0 on error. Read them with available() and read().
     */
    size_t requestFrom(uint8_t address, size_t len, bool stopBit) override;
    /**
     * @brief Request bytes from a slave device, sending a STOP after the request.
     * @param address 7-bit address of the slave device.
     * @param len Number of bytes to request.
     * @return Number of bytes read, 0 on error. Read them with available() and read().
     */
    size_t requestFrom(uint8_t address, size_t len) override;

    /**
     * @brief Request bytes from a slave device after writing an internal register address.
     *
     * This allows a repeated start to access the internal registers of a device.
     * @param address 7-bit address of the slave device.
     * @param len Number of bytes to request.
     * @param iaddress Internal register address to write before the request.
     * @param isize Size in bytes of the internal address (most significant byte first), limited to 3.
     * @param stopBit true to send a STOP after the request, false to keep the bus for a repeated start.
     * @return Number of bytes read, 0 on error. Read them with available() and read().
     */
    size_t requestFrom(uint8_t address, size_t len, uint32_t iaddress, uint8_t isize, bool stopBit);

    /**
     * @brief Write a byte.
     *
     * In master transmitter mode the byte is stored in the Tx buffer, in slave mode it is sent to the master.
     * Must be called in the slave tx event callback or after beginTransmission() and before endTransmission().
     * @param data Byte to write.
     * @return Number of bytes ready to write: 1 on success, 0 on error.
     */
    size_t write(uint8_t data) override;
    /**
     * @brief Write bytes.
     *
     * Must be called in the slave tx event callback or after beginTransmission() and before endTransmission().
     * @param data Pointer to the buffer data.
     * @param quantity Number of bytes to write.
     * @return Number of bytes ready to write.
     */
    size_t write(const uint8_t *data, size_t quantity) override;
    /**
     * @brief Get the number of bytes available for reading from the Rx buffer.
     *
     * Must be called in the slave rx event callback or after requestFrom().
     * @return Number of bytes available.
     */
    int available(void) override;
    /**
     * @brief Read a byte from the Rx buffer.
     *
     * Must be called in the slave rx event callback or after requestFrom().
     * @return Next byte, -1 if no data is available.
     */
    int read(void) override;
    /**
     * @brief Read the next byte from the Rx buffer without consuming it.
     *
     * Must be called in the slave rx event callback or after requestFrom().
     * @return Next byte, -1 if no data is available.
     */
    int peek(void) override;
    /**
     * @brief Discard the content of the Rx and Tx buffers.
     */
    void flush(void) override;

    /**
     * @brief Register the function called when a slave receives data from a master.
     * @param function Function called with the number of bytes received.
     */
    void onReceive(cb_function_receive_t function);
    /**
     * @brief Register the function called when a slave receives data from a master.
     * @param function Function called with the number of bytes received.
     */
    void onReceive(void (*)(int)) override;
    /**
     * @brief Register the function called when a master requests data from this slave.
     * @param function Function called on request.
     */
    void onRequest(cb_function_request_t function);
    /**
     * @brief Register the function called when a master requests data from this slave.
     * @param function Function called on request.
     */
    void onRequest(void (*)(void)) override;

    /**
     * @brief Write a value as a single byte.
     * @param n Value to write, truncated to a byte.
     * @return Number of bytes written.
     */
    inline size_t write(unsigned long n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write a value as a single byte.
     * @param n Value to write, truncated to a byte.
     * @return Number of bytes written.
     */
    inline size_t write(long n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write a value as a single byte.
     * @param n Value to write, truncated to a byte.
     * @return Number of bytes written.
     */
    inline size_t write(unsigned int n)
    {
      return write((uint8_t)n);
    }
    /**
     * @brief Write a value as a single byte.
     * @param n Value to write, truncated to a byte.
     * @return Number of bytes written.
     */
    inline size_t write(int n)
    {
      return write((uint8_t)n);
    }
    using Print::write;

    /**
     * @brief Get the I2C handle, to mix the Arduino API and the STM32Cube HAL API (e.g. DMA). Use at your own risk.
     * @return Pointer to the I2C handle.
     */
#if defined(USE_HALV2_DRIVER)
    hal_i2c_handle_t *getHandle(void)
#else
    I2C_HandleTypeDef *getHandle(void)
#endif
    {
      return &(_i2c.handle);
    }
};



extern TwoWire Wire;

#endif
