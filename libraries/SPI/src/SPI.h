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
#include <stdio.h>
extern "C" {
#include "utility/spi_com.h"
}

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

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

class SPISettings {
  public:
    constexpr SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode, SPIDeviceMode deviceMode = SPI_MASTER)
      : clockFreq(clock),
        bitOrder(bitOrder),
        dataMode((SPIMode)dataMode),
        deviceMode(deviceMode)
    { }
    constexpr SPISettings(uint32_t clock, BitOrder bitOrder, SPIMode dataMode, SPIDeviceMode deviceMode = SPI_MASTER)
      : clockFreq(clock),
        bitOrder(bitOrder),
        dataMode(dataMode),
        deviceMode(deviceMode)
    { }
    constexpr SPISettings()
      : clockFreq(SPI_SPEED_CLOCK_DEFAULT),
        bitOrder(MSBFIRST),
        dataMode(SPI_MODE0),
        deviceMode(SPI_MASTER)
    { }

    bool operator==(const SPISettings &rhs) const
    {
      if ((this->clockFreq == rhs.clockFreq) &&
          (this->bitOrder == rhs.bitOrder) &&
          (this->dataMode == rhs.dataMode) &&
          (this->deviceMode == rhs.deviceMode)) {
        return true;
      }
      return false;
    }

    bool operator!=(const SPISettings &rhs) const
    {
      return !(*this == rhs);
    }

  private:
    uint32_t clockFreq;       // specifies the spi bus maximum clock speed
    BitOrder bitOrder;        // bit order (MSBFirst or LSBFirst)
    SPIMode  dataMode;        // one of the data mode
    SPIDeviceMode deviceMode; // device mode: master or slave

    friend class SPIClass;
};

class SPIClass {
  public:
    SPIClass(uint32_t mosi = MOSI, uint32_t miso = MISO, uint32_t sclk = SCK, uint32_t ssel = PNUM_NOT_DEFINED);

    // setMISO/MOSI/SCLK/SSEL have to be called before begin()
    void setMISO(uint32_t miso)
    {
      _spi.pin_miso = digitalPinToPinName(miso);
    };
    void setMOSI(uint32_t mosi)
    {
      _spi.pin_mosi = digitalPinToPinName(mosi);
    };
    void setSCLK(uint32_t sclk)
    {
      _spi.pin_sclk = digitalPinToPinName(sclk);
    };
    void setSSEL(uint32_t ssel)
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

    void setDirection(uint32_t direction)
    {
      _spi.direction = direction;
      if (direction == SPI_DIRECTION_1LINE)
        _spi.duplex = false;
      else
        _spi.duplex = true;
    };

    void setDeviceMode(SPIDeviceMode deviceMode)
    {
      _spiSettings.deviceMode = deviceMode;
    };

    bool begin(SPIDeviceMode device = SPI_MASTER);
    void end(void);

    /* This function should be used to configure the SPI instance in case you
     * don't use default parameters.
     */
    bool beginTransaction(SPISettings settings);
    void endTransaction(void);

    /* Transfer functions: must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     */
    uint8_t transfer(uint8_t data, bool skipReceive = SPI_TRANSMITRECEIVE);
    uint16_t transfer16(uint16_t data, bool skipReceive = SPI_TRANSMITRECEIVE);
    void transfer(void *buf, size_t count, bool skipReceive = SPI_TRANSMITRECEIVE);

    /* Expand SPI API
     * https://github.com/arduino/ArduinoCore-API/discussions/189
     */
    spi_status_e transfer(const void *tx_buf, void *rx_buf, size_t count);

    /* These methods are deprecated and kept for compatibility.
     * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
     */
    void setBitOrder(BitOrder);
    void setDataMode(uint8_t);
    void setDataMode(SPIMode);
    void setClockDivider(uint8_t);

    // Not implemented functions. Kept for compatibility.
    void usingInterrupt(int interruptNumber);
    void notUsingInterrupt(int interruptNumber);
    void attachInterrupt(void);
    void detachInterrupt(void);

    // Could be used to mix Arduino API and STM32Cube HAL API (ex: DMA). Use at your own risk.
    SPI_HandleTypeDef *getHandle(void)
    {
      return &(_spi.handle);
    }

    // Dedicated to SPI Slave
    void attachSlaveInterrupt(uint8_t pin, callback_function_t callback)
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
    bool init;

  private:
    /* Current SPISettings */
    SPISettings   _spiSettings = SPISettings();
};

extern SPIClass SPI;

#if defined(SUBGHZSPI_BASE)
class SUBGHZSPIClass : public SPIClass {
  public:
    SUBGHZSPIClass(): SPIClass{NC, NC, NC, NC}
    {
      _spi.spi = SUBGHZSPI;
    }

    void enableDebugPins(uint32_t mosi = DEBUG_SUBGHZSPI_MOSI, uint32_t miso = DEBUG_SUBGHZSPI_MISO, uint32_t sclk = DEBUG_SUBGHZSPI_SCLK, uint32_t ssel = DEBUG_SUBGHZSPI_SS);
};

#endif

#endif /* _SPI_H_INCLUDED */
