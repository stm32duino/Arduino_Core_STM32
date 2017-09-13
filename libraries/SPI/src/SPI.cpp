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

#include "SPI.h"

/* The following contructors are available:
- SPIClass SPI
- SPIClass SPI(mosi,miso,sclk)
- SPIClass SPI(mosi,miso,sclk,ss)
*/
SPIClass SPI;

SPIClass::SPIClass() : _CSpin(-1)
{
  _spi.pin_miso = digitalPinToPinName(MISO);
  _spi.pin_mosi = digitalPinToPinName(MOSI);
  _spi.pin_sclk = digitalPinToPinName(SCK);
  _spi.pin_ssel = NC;
}

/* By default hardware SS pin is not used. To use hardware SS pin you should set
ssel pin. Enable this pin disable software CS. See microcontroller documentation
for the list of available SS pins. */
SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel) : _CSpin(-1)
{
  _spi.pin_miso = digitalPinToPinName(miso);
  _spi.pin_mosi = digitalPinToPinName(mosi);
  _spi.pin_sclk = digitalPinToPinName(sclk);

  if(ssel != 0xFF) {
    _spi.pin_ssel = digitalPinToPinName(ssel);
  } else {
    _spi.pin_ssel = NC;
  }
}

//begin using the default chip select
void SPIClass::begin()
{
  begin(CS_PIN_CONTROLLED_BY_USER);
}

//Begin with a chip select defined
void SPIClass::begin(uint8_t _pin)
{
  uint8_t idx;

  if(_pin > NUM_DIGITAL_PINS)
    return;

  idx = pinIdx(_pin, ADD_NEW_PIN);
  if(idx == NB_SPI_SETTINGS)
    return;

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
  }

  spi_init(&_spi, spiSettings[idx].clk,
                  spiSettings[idx].dMode,
                  spiSettings[idx].msb);
  _CSpin = _pin;
#if __has_include("WiFi.h")
  // Wait wifi shield initialization.
  // Should be better to do in SpiDrv::begin() of WiFi library but it seems
  // there is no more update on this library as shield is retired.
  delay(2000);
#endif

}

void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
  UNUSED(interruptNumber);
  //Not implemented
}

void SPIClass::beginTransaction(uint8_t _pin, SPISettings settings)
{
  uint8_t idx;

  if(_pin > NUM_DIGITAL_PINS)
    return;

  idx = pinIdx(_pin, ADD_NEW_PIN);
  if(idx == NB_SPI_SETTINGS) {
    return;
  }

  spiSettings[idx].clk = settings.clk;
  spiSettings[idx].dMode = settings.dMode;
  spiSettings[idx].bOrder = settings.bOrder;
  if(spiSettings[idx].bOrder == MSBFIRST) {
    spiSettings[idx].msb = MSBFIRST;
  } else {
    spiSettings[idx].msb = LSBFIRST;
  }

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
  }

  spi_init(&_spi, spiSettings[idx].clk,
                  spiSettings[idx].dMode,
                  spiSettings[idx].msb);
  _CSpin = _pin;
}

void SPIClass::endTransaction(uint8_t _pin)
{
  if(_pin > NUM_DIGITAL_PINS)
    return;

  RemovePin(_pin);
  _CSpin = -1;
}

void SPIClass::end()
{
  spi_deinit(&_spi);
  RemoveAllPin();
  _CSpin = -1;
}

void SPIClass::setBitOrder(uint8_t _pin, BitOrder _bitOrder)
{
  if(_pin > NUM_DIGITAL_PINS)
    return;

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if(idx == NB_SPI_SETTINGS) {
    return;
  }

  if(MSBFIRST == _bitOrder) {
    spiSettings[idx].msb = MSBFIRST;
    spiSettings[idx].bOrder = MSBFIRST;
  } else {
    spiSettings[idx].msb = LSBFIRST;
    spiSettings[idx].bOrder = LSBFIRST;
  }

  spi_init(&_spi, spiSettings[idx].clk,
                  spiSettings[idx].dMode,
                  spiSettings[idx].msb);
}

void SPIClass::setDataMode(uint8_t _pin, uint8_t _mode)
{
  if(_pin > NUM_DIGITAL_PINS)
    return;

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if(idx == NB_SPI_SETTINGS) {
    return;
  }

  if(SPI_MODE0 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_0;
  } else if(SPI_MODE1 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_1;
  } else if(SPI_MODE2 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_2;
  } else if(SPI_MODE3 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_3;
  }

  spi_init(&_spi, spiSettings[idx].clk,
                  spiSettings[idx].dMode,
                  spiSettings[idx].msb);
}

/*
 * This function should not be used in new projects.
 * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
 */
void SPIClass::setClockDivider(uint8_t _pin, uint8_t _divider)
{
  if(_pin > NUM_DIGITAL_PINS)
    return;

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if(idx == NB_SPI_SETTINGS) {
    return;
  }

  /* Get clk freq of the SPI instance */
  uint32_t spiClkFreq = spi_getClkFreq(&_spi);

  switch(_divider) {
    case (SPI_CLOCK_DIV2) :
    case (SPI_CLOCK_DIV4) :
    case (SPI_CLOCK_DIV8) :
    case (SPI_CLOCK_DIV16) :
    case (SPI_CLOCK_DIV32) :
    case (SPI_CLOCK_DIV64) :
    case (SPI_CLOCK_DIV128) :
      spiSettings[idx].clk = spiClkFreq/_divider;
    break;
    default:
      spiSettings[idx].clk = SPI_SPEED_CLOCK_DEFAULT;
    break;
  }

  spi_init(&_spi, spiSettings[idx].clk,
                  spiSettings[idx].dMode,
                  spiSettings[idx].msb);
}


/* Transfer a message on the selected SPI. The _pin is the CS.
 * The transfer function can reconfigure the SPI instance if the CS pin is
 * different from the previous one.
 * If the _mode is set to SPI_CONTINUE, keep the spi instance alive. That means
 * the CS pin is not reset. Be careful in case you use several CS pin.
 */
byte SPIClass::transfer(uint8_t _pin, uint8_t data, SPITransferMode _mode)
{
  uint8_t rx_buffer = 0;

  if (_pin > NUM_DIGITAL_PINS)
    return rx_buffer;

  if(_pin != _CSpin) {
    uint8_t idx = pinIdx(_pin, GET_IDX);
    if(idx == NB_SPI_SETTINGS) {
      return rx_buffer;
    }
    spi_init(&_spi, spiSettings[idx].clk,
                    spiSettings[idx].dMode,
                    spiSettings[idx].msb);
    _CSpin = _pin;
  }

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, &data, &rx_buffer, sizeof(uint8_t), SPI_TRANSFER_TIMEOUT);

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, HIGH);

  return rx_buffer;
}

uint16_t SPIClass::transfer16(uint8_t _pin, uint16_t data, SPITransferMode _mode)
{
  uint16_t rx_buffer = 0;
  uint16_t tmp;

  if (_pin > NUM_DIGITAL_PINS)
    return rx_buffer;

  if (spiSettings[_pin].msb) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }

  if(_pin != _CSpin) {
    uint8_t idx = pinIdx(_pin, GET_IDX);
    if(idx == NB_SPI_SETTINGS) {
      return rx_buffer;
    }
    spi_init(&_spi, spiSettings[idx].clk,
                    spiSettings[idx].dMode,
                    spiSettings[idx].msb);
    _CSpin = _pin;
  }

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, (uint8_t *)&data, (uint8_t *)&rx_buffer, sizeof(uint16_t), SPI_TRANSFER_TIMEOUT);

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, HIGH);

  if (spiSettings[_pin].msb) {
    tmp = ((rx_buffer & 0xff00) >> 8) | ((rx_buffer & 0xff) << 8);
    rx_buffer = tmp;
  }

  return rx_buffer;
}

void SPIClass::transfer(uint8_t _pin, void *_buf, size_t _count, SPITransferMode _mode)
{
  if ((_count == 0) || (_buf == NULL) || (_pin > NUM_DIGITAL_PINS))
    return;

  if(_pin != _CSpin) {
    uint8_t idx = pinIdx(_pin, GET_IDX);
    if(idx == NB_SPI_SETTINGS) {
      return;
    }
    spi_init(&_spi, spiSettings[idx].clk,
                    spiSettings[idx].dMode,
                    spiSettings[idx].msb);
    _CSpin = _pin;
  }

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, ((uint8_t*)_buf), ((uint8_t*)_buf), _count, SPI_TRANSFER_TIMEOUT);

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, HIGH);
}

void SPIClass::transfer(byte _pin, void *_bufout, void *_bufin, size_t _count, SPITransferMode _mode)
{
  if ((_count == 0) || (_bufout == NULL) || (_bufin == NULL)  || (_pin > NUM_DIGITAL_PINS))
    return;

  if(_pin != _CSpin) {
    uint8_t idx = pinIdx(_pin, GET_IDX);
    if(idx == NB_SPI_SETTINGS) {
      return;
    }
    spi_init(&_spi, spiSettings[idx].clk,
                    spiSettings[idx].dMode,
                    spiSettings[idx].msb);
    _CSpin = _pin;
  }

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, ((uint8_t*)_bufout), ((uint8_t*)_bufin), _count, SPI_TRANSFER_TIMEOUT);

  if((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC))
    digitalWrite(_pin, HIGH);
}

void SPIClass::attachInterrupt(void) {
	// Should be enableInterrupt()
}

void SPIClass::detachInterrupt(void) {
	// Should be disableInterrupt()
}
