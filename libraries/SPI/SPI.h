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

#include "variant.h"
#include <stdio.h>

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_EXTENDED_CS_PIN_HANDLING means SPI has automatic
// CS pin handling and provides the following methods:
//   - begin(pin)
//   - end(pin)
//   - setBitOrder(pin, bitorder)
//   - setDataMode(pin, datamode)
//   - setClockDivider(pin, clockdiv)
//   - transfer(pin, data, SPI_LAST/SPI_CONTINUE)
//   - beginTransaction(pin, SPISettings settings) (if transactions are available)
#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 1

// For compatibility with sketches designed for AVR @ 16 MHz
// need to go from 64MHz to 16 (/4)
// New programs should use SPI.beginTransaction to set the SPI clock
#define SPI_CLOCK_DIV2	 2
#define SPI_CLOCK_DIV4	 4
#define SPI_CLOCK_DIV8	 8
#define SPI_CLOCK_DIV16	 16
#define SPI_CLOCK_DIV32	 32
#define SPI_CLOCK_DIV64	 64
#define SPI_CLOCK_DIV128 128

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

enum SPITransferMode {
  SPI_CONTINUE,
  SPI_LAST
};

class SPISettings {
  public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
      if(clock >= SPI_SPEED_CLOCK_DIV2_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV2_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV4_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV4_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV8_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV8_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV16_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV16_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV32_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV32_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV64_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV64_MHZ;
      } else if (clock >= SPI_SPEED_CLOCK_DIV128_MHZ) {
        clk = SPI_SPEED_CLOCK_DIV128_MHZ;
      } else {
#if defined (STM32F0xx) || defined(STM32F3xx) || defined(STM32L0xx)
        clk = SPI_SPEED_CLOCK_DIV256_MHZ;
#else
        clk = SPI_SPEED_CLOCK_DIV16_MHZ;
#endif
      }

      if(bitOrder == MSBFIRST) {
        msb = 1;
      } else {
        msb = 0;
      }
      bOrder = bitOrder;

      if(SPI_MODE0 == dataMode) {
        dMode = SPI_MODE_0;
      } else if(SPI_MODE1 == dataMode) {
        dMode = SPI_MODE_1;
      } else if(SPI_MODE2 == dataMode) {
        dMode = SPI_MODE_2;
      } else if(SPI_MODE3 == dataMode) {
        dMode = SPI_MODE_3;
      }

    }
    SPISettings() {
#if defined (STM32F0xx) || defined(STM32F3xx)
      clk = SPI_SPEED_CLOCK_DIV64_MHZ;
#else
      clk = SPI_SPEED_CLOCK_DIV16_MHZ;
#endif
      bOrder = MSBFIRST;
      msb = 1;
      dMode = SPI_MODE_0;
    }
  private:
    uint32_t clk;    //specifies the spi bus maximum clock speed
    BitOrder bOrder;    //bit order (MSB/LSB first)
    spi_mode_e dMode;   //one of the data mode
                        //Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
                        //SPI_MODE0             0                     0
                        //SPI_MODE1             0                     1
                        //SPI_MODE2             1                     0
                        //SPI_MODE3             1                     1
    uint8_t msb;        //set to 1 if msb first
    friend class SPIClass;
};



class SPIClass {
  public:
    SPIClass();
    SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel);

    // Transfer functions
    byte transfer(byte _pin, uint8_t _data, SPITransferMode _mode = SPI_LAST);
    uint16_t transfer16(byte _pin, uint16_t _data, SPITransferMode _mode = SPI_LAST);
    void transfer(byte _pin, void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);


    // Transfer functions on default pin BOARD_SPI_DEFAULT_SS
    byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST)
    {
      return transfer(BOARD_SPI_OWN_SS, _data, _mode);
    }

    uint16_t transfer16(uint16_t _data, SPITransferMode _mode = SPI_LAST)
    {
      return transfer16(BOARD_SPI_OWN_SS, _data, _mode);
    }

    void transfer(void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST)
    {
      transfer(BOARD_SPI_OWN_SS, _buf, _count, _mode);
    }

    // Transaction Functions
    void usingInterrupt(uint8_t interruptNumber);

    void beginTransaction(SPISettings settings)
    {
      beginTransaction(BOARD_SPI_OWN_SS, settings);
    }

    void beginTransaction(uint8_t pin, SPISettings settings);
    void endTransaction(void);

    // SPI Configuration methods
    void attachInterrupt(void);
    void detachInterrupt(void);

    void begin(void);
    void end(void);

    // Attach/Detach pin to/from SPI controller
    void begin(uint8_t _pin);
    void end(uint8_t _pin);

    // These methods sets a parameter on a single pin
    void setBitOrder(uint8_t _pin, BitOrder);
    void setDataMode(uint8_t _pin, uint8_t);
    void setClockDivider(uint8_t _pin, uint8_t);

    // These methods sets the same parameters but on default pin BOARD_SPI_OWN_SS
    void setBitOrder(BitOrder _order) { setBitOrder(BOARD_SPI_OWN_SS, _order); };
    void setDataMode(uint8_t _mode) { setDataMode(BOARD_SPI_OWN_SS, _mode); };
    void setClockDivider(uint8_t _div) { setClockDivider(BOARD_SPI_OWN_SS, _div); };

  private:
    //uint32_t id;
    SPISettings spiSettings[SPI_CHANNELS_NUM+1];
    int8_t g_active_id;
    uint8_t _pin;
    spi_t _spi;
};

extern SPIClass SPI;

#endif
