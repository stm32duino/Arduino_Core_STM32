/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "Arduino.h"
#include "api/HardwareSPI.h"
#include <stdio.h>
extern "C" {
#include "utility/spi_com.h"
}

#define SPI_TRANSMITRECEIVE false
#define SPI_TRANSMITONLY true

using namespace arduino;

/**
 * @brief SPI controller or peripheral instance. The default instance is SPI.
 */
class SPIClass : public HardwareSPI {
  public:
    /**
     * @brief Construct an SPI instance using the given pins.
     *
     * Default values are the pins of the default SPI peripheral defined in the variant.
     * All pins must be attached to the same SPI peripheral, see the datasheet of the microcontroller.
     * @param mosi SPI MOSI pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     * @param miso SPI MISO pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     * @param sclk SPI clock pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     * @param ssel Optional SPI SSEL pin, must be a hardware CS pin managed by the SPI peripheral itself
     * (see PinMap_SPI_SSEL in PeripheralPins.c). If set, do not pass a CS pin to any function of the class.
     * Default: not defined (no hardware SSEL).
     */
    SPIClass(pin_size_t mosi = MOSI, pin_size_t miso = MISO, pin_size_t sclk = SCK, pin_size_t ssel = PNUM_NOT_DEFINED);

    // setMISO/MOSI/SCLK/SSEL have to be called before begin()
    /**
     * @brief Set the MISO pin. Must be called before begin().
     * @param miso MISO pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     */
    void setMISO(pin_size_t miso)
    {
      _spi.pin_miso = digitalPinToPinName(miso);
    };
    /**
     * @brief Set the MOSI pin. Must be called before begin().
     * @param mosi MOSI pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     */
    void setMOSI(pin_size_t mosi)
    {
      _spi.pin_mosi = digitalPinToPinName(mosi);
    };
    /**
     * @brief Set the SCLK pin. Must be called before begin().
     * @param sclk SCLK pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     */
    void setSCLK(pin_size_t sclk)
    {
      _spi.pin_sclk = digitalPinToPinName(sclk);
    };
    /**
     * @brief Set the SSEL pin. Must be called before begin().
     * @param ssel SSEL pin. Accepted format: number, Arduino format (Dx) or ST format (Pxy).
     */
    void setSSEL(pin_size_t ssel)
    {
      _spi.pin_ssel = digitalPinToPinName(ssel);
    };

    /**
     * @brief Set the MISO pin. Must be called before begin().
     * @param miso MISO PinName.
     */
    void setMISO(PinName miso)
    {
      _spi.pin_miso = (miso);
    };
    /**
     * @brief Set the MOSI pin. Must be called before begin().
     * @param mosi MOSI PinName.
     */
    void setMOSI(PinName mosi)
    {
      _spi.pin_mosi = (mosi);
    };
    /**
     * @brief Set the SCLK pin. Must be called before begin().
     * @param sclk SCLK PinName.
     */
    void setSCLK(PinName sclk)
    {
      _spi.pin_sclk = (sclk);
    };
    /**
     * @brief Set the SSEL pin. Must be called before begin().
     * @param ssel SSEL PinName.
     */
    void setSSEL(PinName ssel)
    {
      _spi.pin_ssel = (ssel);
    };

    /**
     * @brief Initialize the SPI instance with the default parameters: 4 MHz, MSBFIRST, SPI_MODE0.
     * @param busMode Bus mode: controller or peripheral.
     */
    void begin(SPIBusMode busMode);
    /**
     * @brief Initialize the SPI instance as controller with the default parameters.
     */
    void begin() override
    {
      begin(SPI_CONTROLLER);
    }
    /**
     * @brief Deinitialize the SPI instance and stop it.
     */
    void end(void) override ;

    /**
     * @brief Configure the SPI instance with the given settings, when the default parameters of begin() are not suitable.
     * @param settings SPI settings (clock speed, bit order, data mode, bus mode).
     */
    void beginTransaction(SPISettings settings) override;
    /**
     * @brief End the transaction started with beginTransaction().
     */
    void endTransaction(void) override;

    /**
     * @brief Transfer one byte on the SPI bus.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param data Byte to send.
     * @param skipReceive true to skip receiving data (SPI_TRANSMITONLY), false to receive (SPI_TRANSMITRECEIVE).
     * @return Byte received from the peripheral.
     */
    uint8_t transfer(uint8_t data, bool skipReceive);
    /**
     * @brief Transfer one byte on the SPI bus and receive data.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param data Byte to send.
     * @return Byte received from the peripheral.
     */
    uint8_t transfer(uint8_t data) override
    {
      return transfer(data, SPI_TRANSMITRECEIVE);
    }
    /**
     * @brief Transfer two bytes on the SPI bus in 16-bit format.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param data Bytes to send.
     * @param skipReceive true to skip receiving data (SPI_TRANSMITONLY), false to receive (SPI_TRANSMITRECEIVE).
     * @return Bytes received from the peripheral in 16-bit format.
     */
    uint16_t transfer16(uint16_t data, bool skipReceive);
    /**
     * @brief Transfer two bytes on the SPI bus in 16-bit format and receive data.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param data Bytes to send.
     * @return Bytes received from the peripheral in 16-bit format.
     */
    uint16_t transfer16(uint16_t data) override
    {
      return transfer16(data, SPI_TRANSMITRECEIVE);
    }
    /**
     * @brief Transfer several bytes using one buffer to send and receive.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param buf Pointer to the bytes to send. The bytes received are copied in this buffer.
     * @param count Number of bytes to send/receive.
     * @param skipReceive true to skip receiving data (SPI_TRANSMITONLY), false to receive (SPI_TRANSMITRECEIVE).
     */
    void transfer(void *buf, size_t count, bool skipReceive);
    /**
     * @brief Transfer several bytes using one buffer to send and receive data.
     *
     * begin() or beginTransaction() must be called at least once before.
     * @param buf Pointer to the bytes to send. The bytes received are copied in this buffer.
     * @param count Number of bytes to send/receive.
     */
    void transfer(void *buf, size_t count) override
    {
      transfer(buf, count, SPI_TRANSMITRECEIVE);
    }

    /**
     * @brief Transfer several bytes using one constant Tx buffer and one Rx buffer.
     *
     * begin() or beginTransaction() must be called at least once before.
     * See https://github.com/arduino/ArduinoCore-API/discussions/189
     * @param tx_buf Array of Tx bytes filled by the user before the transfer. If NULL, dummy 0xFF bytes are clocked out.
     * @param rx_buf Array of Rx bytes filled by the peripheral during the transfer. If NULL, the received data is discarded.
     * @param count Number of bytes to send/receive.
     */
    void transfer(const void *tx_buf, void *rx_buf, size_t count);

    /**
     * @brief Not implemented. Kept for compatibility.
     * @param interruptNumber Unused.
     */
    void usingInterrupt(int interruptNumber) override;
    /**
     * @brief Not implemented. Kept for compatibility.
     * @param interruptNumber Unused.
     */
    void notUsingInterrupt(int interruptNumber) override;
    /**
     * @brief Not implemented. Kept for compatibility.
     */
    void attachInterrupt(void) override;
    /**
     * @brief Not implemented. Kept for compatibility.
     */
    void detachInterrupt(void) override;

    /**
     * @brief Get the SPI handle to mix the Arduino API and the STM32Cube HAL API (e.g. DMA). Use at your own risk.
     * @return Pointer to the SPI handle.
     */
#if defined(USE_HALV2_DRIVER)
    hal_spi_handle_t *getHandle(void)
#else
    SPI_HandleTypeDef *getHandle(void)
#endif
    {
      return &(_spi.handle);
    }

    /**
     * @brief Attach a callback on the falling edge of a pin, used for SPI slave chip select.
     * @param pin Pin number.
     * @param callback Function called on the falling edge.
     */
    void attachSlaveInterrupt(uint8_t pin, voidFuncPtr callback)
    {
      ::attachInterrupt(pin, callback, FALLING);
    }

    /**
     * @brief Detach the callback attached with attachSlaveInterrupt().
     * @param pin Pin number.
     */
    void detachSlaveInterrupt(uint8_t pin)
    {
      ::detachInterrupt(pin);
    }

  protected:
    // spi instance
    spi_t         _spi;

  private:
    /* Current SPISettings */
    SPISettings   _spiSettings = SPISettings();
};

extern SPIClass SPI;

#if defined(SUBGHZSPI_BASE)
class SUBGHZSPIClass : public SPIClass {
  public:
    /**
     * @brief Constructor. Attaches the SPI instance to the SubGHz radio peripheral.
     */
    SUBGHZSPIClass(): SPIClass{NC, NC, NC, NC}
    {
      _spi.spi = SUBGHZSPI;
    }

    /**
     * @brief Route the SubGHz SPI signals to debug pins, for logic analyzer use.
     * @param mosi MOSI debug pin.
     * @param miso MISO debug pin.
     * @param sclk SCLK debug pin.
     * @param ssel SSEL debug pin.
     */
    void enableDebugPins(pin_size_t mosi = DEBUG_SUBGHZSPI_MOSI, pin_size_t miso = DEBUG_SUBGHZSPI_MISO, pin_size_t sclk = DEBUG_SUBGHZSPI_SCLK, pin_size_t ssel = DEBUG_SUBGHZSPI_SS);
};

#endif

#endif /* _SPI_H_INCLUDED */
