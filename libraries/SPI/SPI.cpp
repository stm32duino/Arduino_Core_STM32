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


SPIClass SPI;

SPIClass::SPIClass() : g_active_id(-1)
{
  _spi.pin_miso = digitalToPinName(MISO);
  _spi.pin_mosi = digitalToPinName(MOSI);
  _spi.pin_sclk = digitalToPinName(SCLK);
  _spi.pin_ssel = NC;
}

SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel) : g_active_id(-1)
{
  _spi.pin_miso = digitalToPinName(miso);
  _spi.pin_mosi = digitalToPinName(mosi);
  _spi.pin_sclk = digitalToPinName(sclk);
  // If no ssel pin used, set it to value NUM_DIGITAL_PINS
  _spi.pin_ssel = digitalToPinName(ssel);
}

//begin using the default chip select
void SPIClass::begin()
{
  begin(BOARD_SPI_OWN_SS);
}

//Begin with a chip select defined
void SPIClass::begin(uint8_t _pin)
{
  if(_pin > SPI_CHANNELS_NUM)
    return;

  if(_pin != BOARD_SPI_OWN_SS) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
  }

  spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
  g_active_id = _pin;
}

void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
  UNUSED(interruptNumber);
  //Not implemented
}

void SPIClass::beginTransaction(uint8_t _pin, SPISettings settings)
{
  if(_pin > SPI_CHANNELS_NUM)
    return;

  spiSettings[_pin].clk = settings.clk;
  spiSettings[_pin].dMode = settings.dMode;
  spiSettings[_pin].bOrder = settings.bOrder;
  if(spiSettings[_pin].bOrder == MSBFIRST) {
    spiSettings[_pin].msb = MSBFIRST;
  } else {
    spiSettings[_pin].msb = LSBFIRST;
  }

  spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
  g_active_id = _pin;
}

void SPIClass::endTransaction(void)
{
  g_active_id = -1;
}

void SPIClass::end(uint8_t _pin)
{
  UNUSED(_pin);
  end();
}

void SPIClass::end()
{
  spi_deinit(&_spi);
  g_active_id = -1;
}

void SPIClass::setBitOrder(uint8_t _pin, BitOrder _bitOrder)
{
  if(_pin > SPI_CHANNELS_NUM)
    return;

  if(MSBFIRST == _bitOrder) {
    spiSettings[_pin].msb = MSBFIRST;
    spiSettings[_pin].bOrder = MSBFIRST;
  } else {
    spiSettings[_pin].msb = LSBFIRST;
    spiSettings[_pin].bOrder = LSBFIRST;
  }

  spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
  g_active_id = _pin;
}

void SPIClass::setDataMode(uint8_t _pin, uint8_t _mode)
{
  if(_pin > SPI_CHANNELS_NUM)
    return;

  if(SPI_MODE0 == _mode) {
    spiSettings[_pin].dMode = SPI_MODE_0;
  } else if(SPI_MODE1 == _mode) {
    spiSettings[_pin].dMode = SPI_MODE_1;
  } else if(SPI_MODE2 == _mode) {
    spiSettings[_pin].dMode = SPI_MODE_2;
  } else if(SPI_MODE3 == _mode) {
    spiSettings[_pin].dMode = SPI_MODE_3;
  }

  spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
  g_active_id = _pin;
}

/*
 * This function should not be used in new projects.
 * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
 */
void SPIClass::setClockDivider(uint8_t _pin, uint8_t _divider)
{
  if(_pin > SPI_CHANNELS_NUM)
    return;

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
      spiSettings[_pin].clk = spiClkFreq/_divider;
    break;
    default:
      spiSettings[_pin].clk = SPI_SPEED_CLOCK_DEFAULT;
    break;
  }

  spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
  g_active_id = _pin;
}


//Transfer a message on the selected SPI. The _pin is the CS of the SPI that
//identifies the SPI instance.
//If the _mode is set to SPI_CONTINUE, keep the spi instance alive.
byte SPIClass::transfer(uint8_t _pin, uint8_t data, SPITransferMode _mode)
{
  uint8_t rx_buffer = 0;

  if (_pin > SPI_CHANNELS_NUM)
    return rx_buffer;

  if(_pin != g_active_id) {
    spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
    g_active_id = _pin;
  }

  if(_pin != BOARD_SPI_OWN_SS)
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, &data, &rx_buffer, sizeof(uint8_t), 10000000);

  if((_pin != BOARD_SPI_OWN_SS) && (_mode == SPI_LAST))
    digitalWrite(_pin, HIGH);

  return rx_buffer;
}

uint16_t SPIClass::transfer16(uint8_t _pin, uint16_t data, SPITransferMode _mode)
{
  uint16_t rx_buffer = 0;

  if (_pin > SPI_CHANNELS_NUM)
    return rx_buffer;

  if(_pin != g_active_id) {
    spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
    g_active_id = _pin;
  }

  if(_pin != BOARD_SPI_OWN_SS)
    digitalWrite(_pin, LOW);

  spi_transfer(&_spi, (uint8_t *)&data, (uint8_t *)&rx_buffer, sizeof(uint16_t), 10000000);

  if((_pin != BOARD_SPI_OWN_SS) && (_mode == SPI_LAST))
    digitalWrite(_pin, HIGH);

  return rx_buffer;
}

void SPIClass::transfer(uint8_t _pin, void *_buf, size_t _count, SPITransferMode _mode)
{
  if ((_count == 0) || (_pin > SPI_CHANNELS_NUM))
    return;

  if(_pin != g_active_id) {
    spi_init(&_spi, spiSettings[_pin].clk, spiSettings[_pin].dMode, spiSettings[_pin].msb);
    g_active_id = _pin;
  }

  if(_pin != BOARD_SPI_OWN_SS)
    digitalWrite(_pin, LOW);

  spi_send(&_spi,(uint8_t *)_buf, _count,10000);

  if((_pin != BOARD_SPI_OWN_SS) && (_mode == SPI_LAST))
    digitalWrite(_pin, HIGH);
}

void SPIClass::attachInterrupt(void) {
	// Should be enableInterrupt()
}

void SPIClass::detachInterrupt(void) {
	// Should be disableInterrupt()
}
