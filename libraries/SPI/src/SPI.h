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

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)

// Compatibility with sketches designed for AVR @ 16 MHz could not
// be ensured as SPI frequency depends of system clock configuration.
// user have to use appropriate divider for the SPI clock
// This function should not be used in new project.
// Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
#define SPI_CLOCK_DIV2   2
#define SPI_CLOCK_DIV4   4
#define SPI_CLOCK_DIV8   8
#define SPI_CLOCK_DIV16  16
#define SPI_CLOCK_DIV32  32
#define SPI_CLOCK_DIV64  64
#define SPI_CLOCK_DIV128 128

#define SPI_TRANSMITRECEIVE false
#define SPI_TRANSMITONLY true

using namespace arduino;

class SPIClass : public HardwareSPI {
  public:
    SPIClass(pin_size_t mosi = MOSI, pin_size_t miso = MISO, pin_size_t sclk = SCK, pin_size_t ssel = PNUM_NOT_DEFINED);

    // setMISO/MOSI/SCLK/SSEL have to be called before begin()
    void setMISO(pin_size_t miso)
    {
      _spi.pin_miso = digitalPinToPinName(miso);
    };
    void setMOSI(pin_size_t mosi)
    {
      _spi.pin_mosi = digitalPinToPinName(mosi);
    };
    void setSCLK(pin_size_t sclk)
    {
      _spi.pin_sclk = digitalPinToPinName(sclk);
    };
    void setSSEL(pin_size_t ssel)
    {
      _spi.pin_ssel = digitalPinToPinName(ssel);
    };

    void setMISO(PinName miso)
    {
      _spi.pin_miso = (miso);
    };
    void setMOSI(PinName mosi)
    {
      _spi.pin_mosi = (mosi);
    };
    void setSCLK(PinName sclk)
    {
      _spi.pin_sclk = (sclk);
    };
    void setSSEL(PinName ssel)
    {
      _spi.pin_ssel = (ssel);
    };

    void begin(SPIBusMode busMode);
    void begin() override
    {
      begin(SPI_CONTROLLER);
    }
    void end(void) override ;

    /* This function should be used to configure the SPI instance in case you
     * don't use default parameters.
     */
    void beginTransaction(SPISettings settings) override;
    void endTransaction(void) override;

    /* Transfer functions: must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     */
    uint8_t transfer(uint8_t data, bool skipReceive);
    uint8_t transfer(uint8_t data) override
    {
      return transfer(data, SPI_TRANSMITRECEIVE);
    }
    uint16_t transfer16(uint16_t data, bool skipReceive);
    uint16_t transfer16(uint16_t data) override
    {
      return transfer16(data, SPI_TRANSMITRECEIVE);
    }
    void transfer(void *buf, size_t count, bool skipReceive);
    void transfer(void *buf, size_t count) override
    {
      transfer(buf, count, SPI_TRANSMITRECEIVE);
    }

    /* Expand SPI API
     * https://github.com/arduino/ArduinoCore-API/discussions/189
     */
    void transfer(const void *tx_buf, void *rx_buf, size_t count);

    /* These methods are deprecated and kept for compatibility.
     * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
     */
    void setBitOrder(BitOrder);
    void setDataMode(uint8_t);
    void setDataMode(SPIMode);
    void setClockDivider(uint8_t);

    // Not implemented functions. Kept for compatibility.
    void usingInterrupt(int interruptNumber) override;
    void notUsingInterrupt(int interruptNumber) override;
    void attachInterrupt(void) override;
    void detachInterrupt(void) override;

    // Could be used to mix Arduino API and STM32Cube HAL API (ex: DMA). Use at your own risk.
    SPI_HandleTypeDef *getHandle(void)
    {
      return &(_spi.handle);
    }

    // Dedicated to SPI Slave
    void attachSlaveInterrupt(uint8_t pin, voidFuncPtr callback)
    {
      ::attachInterrupt(pin, callback, FALLING);
    }

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

    void applySettings(const SPISettings &settings);
};

extern SPIClass SPI;

#if defined(SUBGHZSPI_BASE)
class SUBGHZSPIClass : public SPIClass {
  public:
    SUBGHZSPIClass(): SPIClass{NC, NC, NC, NC}
    {
      _spi.spi = SUBGHZSPI;
    }

    void enableDebugPins(pin_size_t mosi = DEBUG_SUBGHZSPI_MOSI, pin_size_t miso = DEBUG_SUBGHZSPI_MISO, pin_size_t sclk = DEBUG_SUBGHZSPI_SCLK, pin_size_t ssel = DEBUG_SUBGHZSPI_SS);
};

#endif

#endif /* _SPI_H_INCLUDED */
