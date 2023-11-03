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

// SPI mode parameters for SPISettings
#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#define SPI_TRANSMITRECEIVE 0x0
#define SPI_TRANSMITONLY 0x1

// Defines a default timeout delay in milliseconds for the SPI transfer
#ifndef SPI_TRANSFER_TIMEOUT
  #define SPI_TRANSFER_TIMEOUT 1000
#endif

class SPISettings {
  public:
    constexpr SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode, bool noRecv = SPI_TRANSMITRECEIVE)
      : clk(clock),
        bOrder(bitOrder),
        dMode((spi_mode_e)(
                (SPI_MODE0 == dataMode) ? SPI_MODE_0 :
                (SPI_MODE1 == dataMode) ? SPI_MODE_1 :
                (SPI_MODE2 == dataMode) ? SPI_MODE_2 :
                (SPI_MODE3 == dataMode) ? SPI_MODE_3 :
                SPI_MODE0
              )),
        noReceive(noRecv)
    { }
    constexpr SPISettings()
      : clk(SPI_SPEED_CLOCK_DEFAULT),
        bOrder(MSBFIRST),
        dMode(SPI_MODE_0),
        noReceive(SPI_TRANSMITRECEIVE)
    { }
  private:
    uint32_t clk;       //specifies the spi bus maximum clock speed
    BitOrder bOrder;    //bit order (MSBFirst or LSBFirst)
    spi_mode_e dMode;   //one of the data mode
    //Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
    //SPI_MODE0             0                     0
    //SPI_MODE1             0                     1
    //SPI_MODE2             1                     0
    //SPI_MODE3             1                     1
    friend class SPIClass;
    bool noReceive;
};

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

    virtual void begin();
    void end(void);

    /* This function should be used to configure the SPI instance in case you
     * don't use default parameters.
     */
    void beginTransaction(SPISettings settings);
    virtual void endTransaction(void);

    /* Transfer functions: must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     */
    virtual byte transfer(uint8_t _data);
    virtual uint16_t transfer16(uint16_t _data);
    virtual void transfer(void *_buf, size_t _count);

    /* These methods are deprecated and kept for compatibility.
     * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
     */
    void setBitOrder(BitOrder);
    void setDataMode(uint8_t);
    void setClockDivider(uint8_t);

    // Not implemented functions. Kept for backward compatibility.
    void usingInterrupt(uint8_t interruptNumber);
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
