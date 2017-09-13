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

// For compatibility with sketches designed for AVR @ 16 MHz
// need to go from 64MHz to 16 (/4)
// This function should not be used in new projects.
// Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
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

// Indicates the user controls himself the CS pin
#define CS_PIN_CONTROLLED_BY_USER  NUM_DIGITAL_PINS

// Defines a default timeout delay in milliseconds for the SPI transfer
#define SPI_TRANSFER_TIMEOUT    1000

/*
 * Defines the number of settings saved per SPI instance. Must be < 254.
 * Can be redefined in variant.h
 */
#ifndef NB_SPI_SETTINGS
#define NB_SPI_SETTINGS 4
#endif

class SPISettings {
  public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
      clk = clock;

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
      pinCS = -1;
      clk = SPI_SPEED_CLOCK_DEFAULT;
      bOrder = MSBFIRST;
      msb = 1;
      dMode = SPI_MODE_0;
    }
  private:
    int16_t pinCS;
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
    SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel = 0xFF);

    /* Transfer functions: must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     * You can specify the CS pin to use.
     */
    byte transfer(uint8_t pin, uint8_t _data, SPITransferMode _mode = SPI_LAST);
    uint16_t transfer16(uint8_t pin, uint16_t _data, SPITransferMode _mode = SPI_LAST);
    void transfer(uint8_t pin, void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);
    void transfer(byte _pin, void *_bufout, void *_bufin, size_t _count, SPITransferMode _mode = SPI_LAST);

    // Transfer functions when user controls himself the CS pin.
    byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST)
    {
      return transfer(CS_PIN_CONTROLLED_BY_USER, _data, _mode);
    }

    uint16_t transfer16(uint16_t _data, SPITransferMode _mode = SPI_LAST)
    {
      return transfer16(CS_PIN_CONTROLLED_BY_USER, _data, _mode);
    }

    void transfer(void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST)
    {
      transfer(CS_PIN_CONTROLLED_BY_USER, _buf, _count, _mode);
    }

    void transfer(void *_bufout, void *_bufin, size_t _count, SPITransferMode _mode = SPI_LAST)
    {
      transfer(CS_PIN_CONTROLLED_BY_USER, _bufout, _bufin, _count, _mode);
    }

    // Transaction Functions
    void usingInterrupt(uint8_t interruptNumber);

    /* This function should be used to configure the SPI instance in case you
     * don't use default parameters.
     * You can attach another CS pin to the SPI instance and each CS pin can be
     * attach with specific SPI settings.
     */
    void beginTransaction(uint8_t pin, SPISettings settings);
    void beginTransaction(SPISettings settings)
    {
      beginTransaction(CS_PIN_CONTROLLED_BY_USER, settings);
    }

    void endTransaction(uint8_t pin);
    void endTransaction(void)
    {
      endTransaction(CS_PIN_CONTROLLED_BY_USER);
    }

    // SPI Configuration methods
    void attachInterrupt(void);
    void detachInterrupt(void);

    void begin(void);
    void end(void);

    // Attach CS pin to SPI instance
    void begin(uint8_t _pin);

    /* These methods sets a parameter on a single pin.
     * These methods must be called after initialization of the SPI
     * instance with begin() or beginTransaction().
     * @NOTE
     * These functions should not be used in new projects.
     * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
     */
    void setBitOrder(uint8_t _pin, BitOrder);
    void setDataMode(uint8_t _pin, uint8_t);
    void setClockDivider(uint8_t _pin, uint8_t);

    // These methods sets the same parameters for the default CS pin.
    void setBitOrder(BitOrder _order) {
      setBitOrder(CS_PIN_CONTROLLED_BY_USER, _order);
    }
    void setDataMode(uint8_t _mode) {
      setDataMode(CS_PIN_CONTROLLED_BY_USER, _mode);
    }
    void setClockDivider(uint8_t _div) {
      setClockDivider(CS_PIN_CONTROLLED_BY_USER, _div);
    }

  private:
    SPISettings   spiSettings[NB_SPI_SETTINGS];
    int16_t       _CSpin;
    spi_t         _spi;

    typedef enum{
      GET_IDX = 0,
      ADD_NEW_PIN = 1
    }pin_option_t;

    uint8_t pinIdx(uint8_t _pin, pin_option_t option)
    {
      uint8_t i;

      if(_pin > NUM_DIGITAL_PINS)
        return NB_SPI_SETTINGS;

      for(i = 0; i < NB_SPI_SETTINGS; i++) {
        if(_pin == spiSettings[i].pinCS)
          return i;
      }

      if(option == ADD_NEW_PIN)
      {
        for(i = 0; i < NB_SPI_SETTINGS; i++) {
          if(spiSettings[i].pinCS == -1) {
            spiSettings[i].pinCS = _pin;
            return i;
          }
        }
      }
      return i;
    }

    void RemovePin(uint8_t _pin)
    {
      if(_pin > NUM_DIGITAL_PINS)
        return;

      for(uint8_t i = 0; i < NB_SPI_SETTINGS; i++) {
        if(spiSettings[i].pinCS == _pin) {
          spiSettings[i].pinCS = -1;
          spiSettings[i].clk = SPI_SPEED_CLOCK_DEFAULT;
          spiSettings[i].bOrder = MSBFIRST;
          spiSettings[i].msb = 1;
          spiSettings[i].dMode = SPI_MODE_0;
        }
      }
    }

    void RemoveAllPin(void)
    {
      for(uint8_t i = 0; i < NB_SPI_SETTINGS; i++) {
        spiSettings[i].pinCS = -1;
        spiSettings[i].clk = SPI_SPEED_CLOCK_DEFAULT;
        spiSettings[i].bOrder = MSBFIRST;
        spiSettings[i].msb = 1;
        spiSettings[i].dMode = SPI_MODE_0;
      }
    }
};

extern SPIClass SPI;

#endif
