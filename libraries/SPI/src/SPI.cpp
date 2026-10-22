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

SPIClass::SPIClass(pin_size_t mosi, pin_size_t miso, pin_size_t sclk, pin_size_t ssel)
{
  memset((void *)&_spi, 0, sizeof(_spi));
  _spi.pin_miso = digitalPinToPinName(miso);
  _spi.pin_mosi = digitalPinToPinName(mosi);
  _spi.pin_sclk = digitalPinToPinName(sclk);
  _spi.pin_ssel = digitalPinToPinName(ssel);
}

void SPIClass::begin(SPIBusMode busMode)
{
#if !defined(USE_HALV2_DRIVER)
  _spi.handle.State = HAL_SPI_STATE_RESET;
#endif

  _spiSettings = SPISettings(4000000, MSBFIRST, SPI_MODE0, busMode);
  spi_init(&_spi, _spiSettings.getClockFreq(), (spi_mode_e)_spiSettings.getDataMode(),
           _spiSettings.getBitOrder(), (spi_busmode_e)_spiSettings.getBusMode());
}

void SPIClass::beginTransaction(SPISettings settings)
{
  if (_spiSettings != settings) {
    _spiSettings = settings;
    spi_init(&_spi, _spiSettings.getClockFreq(), (spi_mode_e)_spiSettings.getDataMode(),
             _spiSettings.getBitOrder(), (spi_busmode_e)_spiSettings.getBusMode());
  }
}

void SPIClass::endTransaction(void)
{

}

void SPIClass::end(void)
{
  spi_deinit(&_spi);
}

uint8_t SPIClass::transfer(uint8_t data, bool skipReceive)
{
  spi_transfer(&_spi, &data, (!skipReceive) ? &data : NULL, sizeof(uint8_t));
  return data;
}

uint16_t SPIClass::transfer16(uint16_t data, bool skipReceive)
{
  uint16_t tmp;

  if (_spiSettings.getBitOrder()) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }
  spi_transfer(&_spi, (uint8_t *)&data, (!skipReceive) ? (uint8_t *)&data : NULL, sizeof(uint16_t));

  if (_spiSettings.getBitOrder()) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }

  return data;
}

void SPIClass::transfer(void *buf, size_t count, bool skipReceive)
{
  spi_transfer(&_spi, (uint8_t *)buf, (!skipReceive) ? (uint8_t *)buf : NULL, count);

}

void SPIClass::transfer(const void *tx_buf, void *rx_buf, size_t count)
{
  spi_transfer(&_spi, ((const uint8_t *)tx_buf), ((uint8_t *)rx_buf), count);
}


void SPIClass::usingInterrupt(int interruptNumber)
{
  (void)interruptNumber;
}

void SPIClass::notUsingInterrupt(int interruptNumber)
{
  (void)interruptNumber;
}

void SPIClass::attachInterrupt(void)
{
  // Should be enableInterrupt()
}

void SPIClass::detachInterrupt(void)
{
  // Should be disableInterrupt()
}

#if defined(SUBGHZSPI_BASE)
void SUBGHZSPIClass::enableDebugPins(pin_size_t mosi, pin_size_t miso, pin_size_t sclk, pin_size_t ssel)
{
  /* Configure SPI GPIO pins */
  pinmap_pinout(digitalPinToPinName(mosi), PinMap_SPI_MOSI);
  pinmap_pinout(digitalPinToPinName(miso), PinMap_SPI_MISO);
  pinmap_pinout(digitalPinToPinName(sclk), PinMap_SPI_SCLK);
  pinmap_pinout(digitalPinToPinName(ssel), PinMap_SPI_SSEL);
}
#endif
