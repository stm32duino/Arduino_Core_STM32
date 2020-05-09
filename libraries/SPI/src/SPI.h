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

// Transfer mode
enum SPITransferMode {
  SPI_CONTINUE, /* Transfer not finished: CS pin kept active */
  SPI_LAST      /* Transfer ended: CS pin released */
};

// Indicates the user controls himself the CS pin outside of the spi class
#define CS_PIN_CONTROLLED_BY_USER  NUM_DIGITAL_PINS

// Indicates there is no configuration selected
#define NO_CONFIG   ((int16_t)(-1))

// Defines a default timeout delay in milliseconds for the SPI transfer
#ifndef SPI_TRANSFER_TIMEOUT
  #define SPI_TRANSFER_TIMEOUT 1000
#endif

/*
 * Defines the number of settings saved per SPI instance. Must be in range 1 to 254.
 * Can be redefined in variant.h
 */
#ifndef NB_SPI_SETTINGS
  #define NB_SPI_SETTINGS 4
#endif

class SPISettings {
  public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode, bool noRecv = SPI_TRANSMITRECEIVE)
    {
      clk = clock;
      bOrder = bitOrder;
      noReceive = noRecv;

      if (SPI_MODE0 == dataMode) {
        dMode = SPI_MODE_0;
      } else if (SPI_MODE1 == dataMode) {
        dMode = SPI_MODE_1;
      } else if (SPI_MODE2 == dataMode) {
        dMode = SPI_MODE_2;
      } else if (SPI_MODE3 == dataMode) {
        dMode = SPI_MODE_3;
      }
    }
    SPISettings()
    {
      pinCS = -1;
      clk = SPI_SPEED_CLOCK_DEFAULT;
      bOrder = MSBFIRST;
      dMode = SPI_MODE_0;
    }
  private:
    int16_t pinCS;      //CS pin associated to the configuration
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
    SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel = (uint8_t)NC);

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

    void begin(uint8_t _pin = CS_PIN_CONTROLLED_BY_USER);
    void end(void);

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

    /* These methods are deprecated and kept for compatibility.
     * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
     */
    void setBitOrder(uint8_t _pin, BitOrder);
    void setBitOrder(BitOrder _order)
    {
      setBitOrder(CS_PIN_CONTROLLED_BY_USER, _order);
    }

    void setDataMode(uint8_t _pin, uint8_t);
    void setDataMode(uint8_t _mode)
    {
      setDataMode(CS_PIN_CONTROLLED_BY_USER, _mode);
    }

    void setClockDivider(uint8_t _pin, uint8_t);
    void setClockDivider(uint8_t _div)
    {
      setClockDivider(CS_PIN_CONTROLLED_BY_USER, _div);
    }

    // Not implemented functions. Kept for backward compatibility.
    void usingInterrupt(uint8_t interruptNumber);
    void attachInterrupt(void);
    void detachInterrupt(void);

  private:
    /* Contains various spiSettings for the same spi instance. Each spi spiSettings
    is associated to a CS pin. */
    SPISettings   spiSettings[NB_SPI_SETTINGS];

    // Use to know which configuration is selected.
    int16_t       _CSPinConfig;

    // spi instance
    spi_t         _spi;


    typedef enum {
      GET_IDX = 0,
      ADD_NEW_PIN = 1
    } pin_option_t;

    uint8_t pinIdx(uint8_t _pin, pin_option_t option)
    {
      uint8_t i;

      if (_pin > NUM_DIGITAL_PINS) {
        return NB_SPI_SETTINGS;
      }

      for (i = 0; i < NB_SPI_SETTINGS; i++) {
        if (_pin == spiSettings[i].pinCS) {
          return i;
        }
      }

      if (option == ADD_NEW_PIN) {
        for (i = 0; i < NB_SPI_SETTINGS; i++) {
          if (spiSettings[i].pinCS == -1) {
            spiSettings[i].pinCS = _pin;
            return i;
          }
        }
      }
      return i;
    }

    void RemovePin(uint8_t _pin)
    {
      if (_pin > NUM_DIGITAL_PINS) {
        return;
      }

      for (uint8_t i = 0; i < NB_SPI_SETTINGS; i++) {
        if (spiSettings[i].pinCS == _pin) {
          spiSettings[i].pinCS = -1;
          spiSettings[i].clk = SPI_SPEED_CLOCK_DEFAULT;
          spiSettings[i].bOrder = MSBFIRST;
          spiSettings[i].dMode = SPI_MODE_0;
        }
      }
    }

    void RemoveAllPin(void)
    {
      for (uint8_t i = 0; i < NB_SPI_SETTINGS; i++) {
        spiSettings[i].pinCS = -1;
        spiSettings[i].clk = SPI_SPEED_CLOCK_DEFAULT;
        spiSettings[i].bOrder = MSBFIRST;
        spiSettings[i].dMode = SPI_MODE_0;
      }
    }
};

extern SPIClass SPI;

#endif
