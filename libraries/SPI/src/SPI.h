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

#define SPI_TRANSMITRECEIVE 0x0
#define SPI_TRANSMITONLY 0x1

// Defines a default timeout delay in milliseconds for the SPI transfer
#ifndef SPI_TRANSFER_TIMEOUT
  #define SPI_TRANSFER_TIMEOUT 1000
#endif

class SPISettings {
  public:
    SPISettings(uint32_t clock, BitOrder bitOrder, SPIMode dataMode, bool skipRecv = SPI_TRANSMITRECEIVE)
    {
      if (__builtin_constant_p(clock)) {
        init_AlwaysInline(clock, bitOrder, dataMode, skipRecv);
      } else {
        init_MightInline(clock, bitOrder, dataMode, skipRecv);
      }
    }

    SPISettings(uint32_t clock, BitOrder bitOrder, int dataMode, bool skipRecv = SPI_TRANSMITRECEIVE)
    {
      if (__builtin_constant_p(clock)) {
        init_AlwaysInline(clock, bitOrder, (SPIMode)dataMode, skipRecv);
      } else {
        init_MightInline(clock, bitOrder, (SPIMode)dataMode, skipRecv);
      }
    }

    // Default speed set to 4MHz, SPI mode set to MODE 0 and Bit order set to MSB first.
    SPISettings()
    {
      init_AlwaysInline(SPI_SPEED_CLOCK_DEFAULT, MSBFIRST, SPI_MODE0, SPI_TRANSMITRECEIVE);
    }

    bool operator==(const SPISettings &rhs) const
    {
      if ((this->clockFreq == rhs.clockFreq) &&
          (this->bitOrder == rhs.bitOrder) &&
          (this->dataMode == rhs.dataMode) &&
          (this->skipRecv == rhs.skipRecv)) {
        return true;
      }
      return false;
    }

    bool operator!=(const SPISettings &rhs) const
    {
      return !(*this == rhs);
    }

    uint32_t getClockFreq() const
    {
      return clockFreq;
    }
    SPIMode getDataMode() const
    {
      return dataMode;
    }
    BitOrder getBitOrder() const
    {
      return (bitOrder);
    }
    bool getSkipRecv() const
    {
      return skipRecv;
    }

    void setClockFreq(uint32_t clkFreq)
    {
      clockFreq = clkFreq;
    }
    void setDataMode(SPIMode mode)
    {
      dataMode = mode;
    }
    void setBitOrder(BitOrder order)
    {
      bitOrder = order;
    }
    void setSkipRecv(bool skip)
    {
      skipRecv = skip;
    }

  private:
    void init_MightInline(uint32_t clock, BitOrder bitOrder, SPIMode dataMode, bool skipRecv)
    {
      init_AlwaysInline(clock, bitOrder, dataMode, skipRecv);
    }

    // Core developer MUST use an helper function in beginTransaction() to use this data
    void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, SPIMode dataMode, bool skipRecv) __attribute__((__always_inline__))
    {
      this->clockFreq = clock;
      this->dataMode = dataMode;
      this->bitOrder = bitOrder;
      this->skipRecv = skipRecv;
    }

    uint32_t clockFreq;
    SPIMode dataMode;
    BitOrder bitOrder;
    bool skipRecv;

    friend class HardwareSPI;
};

const SPISettings DEFAULT_SPI_SETTINGS = SPISettings();

class SPIClass {
  public:
    SPIClass();
    SPIClass(uint32_t mosi, uint32_t miso, uint32_t sclk, uint32_t ssel = PNUM_NOT_DEFINED);

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

    virtual void begin(void);
    void end(void);

    /* This function should be used to configure the SPI instance in case you
     * don't use default parameters.
     */
    void beginTransaction(SPISettings settings);
    virtual void endTransaction(void);

    /* Transfer functions: must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     */
    virtual uint8_t transfer(uint8_t _data);
    virtual uint16_t transfer16(uint16_t _data);
    virtual void transfer(void *buf, size_t count);

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

  protected:
    // spi instance
    spi_t         _spi;

  private:
    /* Current SPISettings */
    SPISettings   _spiSettings = DEFAULT_SPI_SETTINGS;
};

extern SPIClass SPI;

#if defined(SUBGHZSPI_BASE)
class SUBGHZSPIClass : public SPIClass {
  public:
    SUBGHZSPIClass(): SPIClass{NC, NC, NC, NC}
    {
      _spi.spi = SUBGHZSPI;
    }

    void begin();
    void beginTransaction(SPISettings settings);
    byte transfer(uint8_t _data);
    uint16_t transfer16(uint16_t _data);
    void transfer(void *_buf, size_t _count);
    void enableDebugPins(uint32_t mosi = DEBUG_SUBGHZSPI_MOSI, uint32_t miso = DEBUG_SUBGHZSPI_MISO, uint32_t sclk = DEBUG_SUBGHZSPI_SCLK, uint32_t ssel = DEBUG_SUBGHZSPI_SS);

    using SPIClass::beginTransaction;
    using SPIClass::transfer;
    using SPIClass::transfer16;
};

#endif

#endif /* _SPI_H_INCLUDED */
