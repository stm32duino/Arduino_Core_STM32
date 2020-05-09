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

/**
  * @brief  Default constructor. Uses pin configuration of variant.h.
  */
SPIClass::SPIClass() : _CSPinConfig(NO_CONFIG)
{
  _spi.pin_miso = digitalPinToPinName(MISO);
  _spi.pin_mosi = digitalPinToPinName(MOSI);
  _spi.pin_sclk = digitalPinToPinName(SCK);
  _spi.pin_ssel = NC;
}

/**
  * @brief  Constructor to create another SPI instance attached to another SPI
  *         peripheral different of the default SPI. All pins must be attached to
  *         the same SPI peripheral. See datasheet of the microcontroller.
  * @param  mosi: SPI mosi pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy).
  * @param  miso: SPI miso pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy).
  * @param  sclk: SPI clock pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy).
  * @param  ssel: SPI ssel pin (optional). Accepted format: number or
  *         Arduino format (Dx) or ST format (Pxy). By default is set to NC.
  *         This pin must correspond to a hardware CS pin which can be managed
  *         by the SPI peripheral itself. See the datasheet of the microcontroller
  *         or look at PinMap_SPI_SSEL[] inside the file PeripheralPins.c
  *         corresponding to the board. If you configure this pin you can't use
  *         another CS pin and don't pass a CS pin as parameter to any functions
  *         of the class.
  */
SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel) : _CSPinConfig(NO_CONFIG)
{
  _spi.pin_miso = digitalPinToPinName(miso);
  _spi.pin_mosi = digitalPinToPinName(mosi);
  _spi.pin_sclk = digitalPinToPinName(sclk);
  _spi.pin_ssel = digitalPinToPinName(ssel);
}

/**
  * @brief  Initialize the SPI instance.
  * @param  _pin: chip select pin (optional). If this parameter is filled,
  *         it gives the management of the CS pin to the SPI class. In this case
  *         do not manage the CS pin outside of the SPI class.
  */
void SPIClass::begin(uint8_t _pin)
{
  uint8_t idx;

  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  idx = pinIdx(_pin, ADD_NEW_PIN);
  if (idx >= NB_SPI_SETTINGS) {
    return;
  }

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
  }

  _spi.handle.State = HAL_SPI_STATE_RESET;
  spi_init(&_spi, spiSettings[idx].clk,
           spiSettings[idx].dMode,
           spiSettings[idx].bOrder);
  _CSPinConfig = _pin;
#if __has_include("WiFi.h")
  // Wait wifi shield initialization.
  // Should be better to do in SpiDrv::begin() of WiFi library but it seems
  // there is no more update on this library as shield is retired.
  delay(2000);
#endif

}

/**
  * @brief  This function should be used to configure the SPI instance in case you
  *         don't use the default parameters set by the begin() function.
  * @param  _pin: CS pin (optional). This pin will be attached with the settings.
  * @param  settings: SPI settings(clock speed, bit order, data mode).
  * @Note   For each SPI instance you are able to manage until NB_SPI_SETTINGS
  *         devices attached to the same SPI peripheral. You need to indicate the
  *         CS pin used to the transfer() function and the SPI instance will be
  *         configured with the right settings.
  */
void SPIClass::beginTransaction(uint8_t _pin, SPISettings settings)
{
  uint8_t idx;

  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  idx = pinIdx(_pin, ADD_NEW_PIN);
  if (idx >= NB_SPI_SETTINGS) {
    return;
  }

  spiSettings[idx].clk = settings.clk;
  spiSettings[idx].dMode = settings.dMode;
  spiSettings[idx].bOrder = settings.bOrder;
  spiSettings[idx].noReceive = settings.noReceive;

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
  }

  spi_init(&_spi, spiSettings[idx].clk,
           spiSettings[idx].dMode,
           spiSettings[idx].bOrder);
  _CSPinConfig = _pin;
}

/**
  * @brief  Remove the CS pin and the settings associated to the SPI instance.
  * @param  _pin: CS pin (optional)
  */
void SPIClass::endTransaction(uint8_t _pin)
{
  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  RemovePin(_pin);
  _CSPinConfig = NO_CONFIG;
}

/**
  * @brief  Deinitialize the SPI instance and stop it.
  */
void SPIClass::end()
{
  spi_deinit(&_spi);
  RemoveAllPin();
  _CSPinConfig = NO_CONFIG;
}

/**
  * @brief  Deprecated function.
  *         Configure the bit order: MSB first or LSB first.
  * @param  _pin: CS pin associated to a configuration (optional).
  * @param  _bitOrder: MSBFIRST or LSBFIRST
  */
void SPIClass::setBitOrder(uint8_t _pin, BitOrder _bitOrder)
{
  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (idx >= NB_SPI_SETTINGS) {
    return;
  }

  spiSettings[idx].bOrder = _bitOrder;

  spi_init(&_spi, spiSettings[idx].clk,
           spiSettings[idx].dMode,
           spiSettings[idx].bOrder);
}

/**
  * @brief  Deprecated function.
  *         Configure the data mode (clock polarity and clock phase)
  * @param  _pin: CS pin associated to a configuration (optional).
  * @param  _mode: SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3
  * @note
  *         Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
  *         SPI_MODE0             0                     0
  *         SPI_MODE1             0                     1
  *         SPI_MODE2             1                     0
  *         SPI_MODE3             1                     1
  */
void SPIClass::setDataMode(uint8_t _pin, uint8_t _mode)
{
  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (idx >= NB_SPI_SETTINGS) {
    return;
  }

  if (SPI_MODE0 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_0;
  } else if (SPI_MODE1 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_1;
  } else if (SPI_MODE2 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_2;
  } else if (SPI_MODE3 == _mode) {
    spiSettings[idx].dMode = SPI_MODE_3;
  }

  spi_init(&_spi, spiSettings[idx].clk,
           spiSettings[idx].dMode,
           spiSettings[idx].bOrder);
}

/**
  * @brief  Deprecated function.
  *         Configure the clock speed
  * @param  _pin: CS pin associated to a configuration (optional).
  * @param  _divider: the SPI clock can be divided by values from 1 to 255.
  *         If 0, default SPI speed is used.
  */
void SPIClass::setClockDivider(uint8_t _pin, uint8_t _divider)
{
  if (_pin > NUM_DIGITAL_PINS) {
    return;
  }

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (idx >= NB_SPI_SETTINGS) {
    return;
  }
  if (_divider == 0) {
    spiSettings[idx].clk = SPI_SPEED_CLOCK_DEFAULT;
  } else {
    /* Get clk freq of the SPI instance and compute it */
    spiSettings[idx].clk = spi_getClkFreq(&_spi) / _divider;
  }

  spi_init(&_spi, spiSettings[idx].clk,
           spiSettings[idx].dMode,
           spiSettings[idx].bOrder);
}

/**
  * @brief  Transfer one byte on the SPI bus.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  _pin: CS pin to select a device (optional). If the previous transfer
  *         used another CS pin then the SPI instance will be reconfigured.
  * @param  data: byte to send.
  * @param  _mode: (optional) can be SPI_CONTINUE in case of multiple successive
  *         send or SPI_LAST to indicate the end of send.
  *         If the _mode is set to SPI_CONTINUE, keep the SPI instance alive.
  *         That means the CS pin is not reset. Be careful in case you use
  *         several CS pin.
  * @return byte received from the slave.
  */
byte SPIClass::transfer(uint8_t _pin, uint8_t data, SPITransferMode _mode)
{
  uint8_t rx_buffer = 0;

  if (_pin > NUM_DIGITAL_PINS) {
    return rx_buffer;
  }
  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (_pin != _CSPinConfig) {
    if (idx >= NB_SPI_SETTINGS) {
      return rx_buffer;
    }
    spi_init(&_spi, spiSettings[idx].clk,
             spiSettings[idx].dMode,
             spiSettings[idx].bOrder);
    _CSPinConfig = _pin;
  }

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, LOW);
  }

  spi_transfer(&_spi, &data, &rx_buffer, sizeof(uint8_t), SPI_TRANSFER_TIMEOUT, spiSettings[idx].noReceive);

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, HIGH);
  }

  return rx_buffer;
}

/**
  * @brief  Transfer two bytes on the SPI bus in 16 bits format.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  _pin: CS pin to select a device (optional). If the previous transfer
  *         used another CS pin then the SPI instance will be reconfigured.
  * @param  data: bytes to send.
  * @param  _mode: (optional) can be SPI_CONTINUE in case of multiple successive
  *         send or SPI_LAST to indicate the end of send.
  *         If the _mode is set to SPI_CONTINUE, keep the SPI instance alive.
  *         That means the CS pin is not reset. Be careful in case you use
  *         several CS pin.
  * @return bytes received from the slave in 16 bits format.
  */
uint16_t SPIClass::transfer16(uint8_t _pin, uint16_t data, SPITransferMode _mode)
{
  uint16_t rx_buffer = 0;
  uint16_t tmp;

  if (_pin > NUM_DIGITAL_PINS) {
    return rx_buffer;
  }

  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (idx >= NB_SPI_SETTINGS) {
    return rx_buffer;
  }

  if (_pin != _CSPinConfig) {
    spi_init(&_spi, spiSettings[idx].clk,
             spiSettings[idx].dMode,
             spiSettings[idx].bOrder);
    _CSPinConfig = _pin;
  }

  if (spiSettings[idx].bOrder) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, LOW);
  }

  spi_transfer(&_spi, (uint8_t *)&data, (uint8_t *)&rx_buffer, sizeof(uint16_t),
               SPI_TRANSFER_TIMEOUT, spiSettings[idx].noReceive);

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, HIGH);
  }

  if (spiSettings[idx].bOrder) {
    tmp = ((rx_buffer & 0xff00) >> 8) | ((rx_buffer & 0xff) << 8);
    rx_buffer = tmp;
  }

  return rx_buffer;
}

/**
  * @brief  Transfer several bytes. Only one buffer used to send and receive data.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  _pin: CS pin to select a device (optional). If the previous transfer
  *         used another CS pin then the SPI instance will be reconfigured.
  * @param  _buf: pointer to the bytes to send. The bytes received are copy in
  *         this buffer.
  * @param  _count: number of bytes to send/receive.
  * @param  _mode: (optional) can be SPI_CONTINUE in case of multiple successive
  *         send or SPI_LAST to indicate the end of send.
  *         If the _mode is set to SPI_CONTINUE, keep the SPI instance alive.
  *         That means the CS pin is not reset. Be careful in case you use
  *         several CS pin.
  */
void SPIClass::transfer(uint8_t _pin, void *_buf, size_t _count, SPITransferMode _mode)
{
  if ((_count == 0) || (_buf == NULL) || (_pin > NUM_DIGITAL_PINS)) {
    return;
  }
  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (_pin != _CSPinConfig) {
    if (idx >= NB_SPI_SETTINGS) {
      return;
    }
    spi_init(&_spi, spiSettings[idx].clk,
             spiSettings[idx].dMode,
             spiSettings[idx].bOrder);
    _CSPinConfig = _pin;
  }

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, LOW);
  }

  spi_transfer(&_spi, ((uint8_t *)_buf), ((uint8_t *)_buf), _count,
               SPI_TRANSFER_TIMEOUT, spiSettings[idx].noReceive);

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, HIGH);
  }
}

/**
  * @brief  Transfer several bytes. One buffer contains the data to send and
  *         another one will contains the data received. begin() or
  *         beginTransaction() must be called at least once before.
  * @param  _pin: CS pin to select a device (optional). If the previous transfer
  *         used another CS pin then the SPI instance will be reconfigured.
  * @param  _bufout: pointer to the bytes to send.
  * @param  _bufin: pointer to the bytes received.
  * @param  _count: number of bytes to send/receive.
  * @param  _mode: (optional) can be SPI_CONTINUE in case of multiple successive
  *         send or SPI_LAST to indicate the end of send.
  *         If the _mode is set to SPI_CONTINUE, keep the SPI instance alive.
  *         That means the CS pin is not reset. Be careful in case you use
  *         several CS pin.
  */
void SPIClass::transfer(byte _pin, void *_bufout, void *_bufin, size_t _count, SPITransferMode _mode)
{
  if ((_count == 0) || (_bufout == NULL) || (_bufin == NULL)  || (_pin > NUM_DIGITAL_PINS)) {
    return;
  }
  uint8_t idx = pinIdx(_pin, GET_IDX);
  if (_pin != _CSPinConfig) {
    if (idx >= NB_SPI_SETTINGS) {
      return;
    }
    spi_init(&_spi, spiSettings[idx].clk,
             spiSettings[idx].dMode,
             spiSettings[idx].bOrder);
    _CSPinConfig = _pin;
  }

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, LOW);
  }

  spi_transfer(&_spi, ((uint8_t *)_bufout), ((uint8_t *)_bufin), _count,
               SPI_TRANSFER_TIMEOUT, spiSettings[idx].noReceive);

  if ((_pin != CS_PIN_CONTROLLED_BY_USER) && (_mode == SPI_LAST) && (_spi.pin_ssel == NC)) {
    digitalWrite(_pin, HIGH);
  }
}

/**
  * @brief  Not implemented.
  */
void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
  UNUSED(interruptNumber);
}

/**
  * @brief  Not implemented.
  */
void SPIClass::attachInterrupt(void)
{
  // Should be enableInterrupt()
}

/**
  * @brief  Not implemented.
  */
void SPIClass::detachInterrupt(void)
{
  // Should be disableInterrupt()
}
