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
  * @brief  Default Constructor. Uses pin configuration of default SPI
  *         defined in the variant*.h.
  *         To create another SPI instance attached to another SPI
  *         peripheral gave the pins as parameters to the constructor.
  * @note   All pins must be attached to the same SPI peripheral.
  *         See datasheet of the microcontroller.
  * @param  mosi: SPI mosi pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy). Default is MOSI pin of the default SPI peripheral.
  * @param  miso: SPI miso pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy). Default is MISO pin of the default SPI peripheral.
  * @param  sclk: SPI clock pin. Accepted format: number or Arduino format (Dx)
  *         or ST format (Pxy). Default is SCK pin of the default SPI peripheral.
  * @param  ssel: SPI ssel pin (optional). Accepted format: number or
  *         Arduino format (Dx) or ST format (Pxy). By default is set to NC.
  *         This pin must correspond to a hardware CS pin which can be managed
  *         by the SPI peripheral itself. See the datasheet of the microcontroller
  *         or look at PinMap_SPI_SSEL[] inside the file PeripheralPins.c
  *         corresponding to the board. If you configure this pin you can't use
  *         another CS pin and don't pass a CS pin as parameter to any functions
  *         of the class.
  */
SPIClass::SPIClass(uint32_t mosi, uint32_t miso, uint32_t sclk, uint32_t ssel)
{
  memset((void *)&_spi, 0, sizeof(_spi));
  _spi.pin_miso = digitalPinToPinName(miso);
  _spi.pin_mosi = digitalPinToPinName(mosi);
  _spi.pin_sclk = digitalPinToPinName(sclk);
  _spi.pin_ssel = digitalPinToPinName(ssel);

  // Default configuration
  _spi.duplex = true;
  _spi.direction = SPI_DIRECTION_2LINES;
  _spi.mode = SPI_MODE_MASTER;
}

/**
  * @brief  Initialize the SPI instance.
  * @param  device: device mode (optional), SPI_MASTER or SPI_SLAVE. Default is master.
  */
bool SPIClass::begin(SPIDeviceMode device)
{
  _spi.handle.State = HAL_SPI_STATE_RESET;
  _spiSettings = SPISettings();
  _spiSettings.deviceMode = device;
  auto error = spi_init(&_spi, _spiSettings.clockFreq, _spiSettings.dataMode,
           _spiSettings.bitOrder, _spiSettings.deviceMode);
  if (error != SPI_OK) {
    Serial.printf("SPI init error: %d\n", error);
  }

  init = error == SPI_OK;
  return init;
}

/**
  * @brief  This function should be used to configure the SPI instance in case you
  *         don't use the default parameters set by the begin() function.
  * @param  settings: SPI settings(clock speed, bit order, data mode, device mode).
  */
bool SPIClass::beginTransaction(SPISettings settings)
{
  if (_spiSettings != settings) {
    _spiSettings = settings;
    auto error = spi_init(&_spi, _spiSettings.clockFreq,
             _spiSettings.dataMode,
             _spiSettings.bitOrder, _spiSettings.deviceMode);
    if (error != SPI_OK) {
      Serial.printf("SPI init error: %d\n", error);
    }
    init = error == SPI_OK;
  }

  return init;
}

/**
  * @brief  End the transaction after beginTransaction usage
  */
void SPIClass::endTransaction(void)
{
  // Nothing to do here
}

/**
  * @brief  Deinitialize the SPI instance and stop it.
  */
void SPIClass::end(void)
{
  spi_deinit(&_spi);
}

/**
  * @brief  Deprecated function.
  *         Configure the bit order: MSB first or LSB first.
  * @param  bitOrder: MSBFIRST or LSBFIRST
  */
void SPIClass::setBitOrder(BitOrder bitOrder)
{
  _spiSettings.bitOrder = bitOrder;

  spi_init(&_spi, _spiSettings.clockFreq, _spiSettings.dataMode,
           _spiSettings.bitOrder, _spiSettings.deviceMode);
}

/**
  * @brief  Deprecated function.
  *         Configure the data mode (clock polarity and clock phase)
  * @param  mode: SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3
  * @note
  *         Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
  *         SPI_MODE0             0                     0
  *         SPI_MODE1             0                     1
  *         SPI_MODE2             1                     0
  *         SPI_MODE3             1                     1
  */
void SPIClass::setDataMode(uint8_t mode)
{
  setDataMode((SPIMode)mode);
}

void SPIClass::setDataMode(SPIMode mode)
{
  _spiSettings.dataMode = mode;
  spi_init(&_spi, _spiSettings.clockFreq, _spiSettings.dataMode,
           _spiSettings.bitOrder, _spiSettings.deviceMode);
}

/**
  * @brief  Deprecated function.
  *         Configure the clock speed
  * @param  divider: the SPI clock can be divided by values from 1 to 255.
  *         If 0, default SPI speed is used.
  */
void SPIClass::setClockDivider(uint8_t divider)
{
  if (divider == 0) {
    _spiSettings.clockFreq = SPI_SPEED_CLOCK_DEFAULT;
  } else {
    /* Get clk freq of the SPI instance and compute it */
    _spiSettings.clockFreq = spi_getClkFreq(&_spi) / divider;
  }

  spi_init(&_spi, _spiSettings.clockFreq, _spiSettings.dataMode,
           _spiSettings.bitOrder, _spiSettings.deviceMode);
}

/**
  * @brief  Transfer one byte on the SPI bus.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  data: byte to send.
  * @param  skipReceive: skip receiving data after transmit or not.
  *         SPI_TRANSMITRECEIVE or SPI_TRANSMITONLY.
  *         Optional, default: SPI_TRANSMITRECEIVE.
  * @return byte received from the slave.
  */
uint8_t SPIClass::transfer(uint8_t data, bool skipReceive)
{
  spi_transfer(&_spi, &data, (!skipReceive) ? &data : NULL, sizeof(uint8_t));
  return data;
}

/**
  * @brief  Transfer two bytes on the SPI bus in 16 bits format.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  data: bytes to send.
  * @param  skipReceive: skip receiving data after transmit or not.
  *         SPI_TRANSMITRECEIVE or SPI_TRANSMITONLY.
  *         Optional, default: SPI_TRANSMITRECEIVE.
  * @return bytes received from the slave in 16 bits format.
  */
uint16_t SPIClass::transfer16(uint16_t data, bool skipReceive)
{
  uint16_t tmp;

  if (_spiSettings.bitOrder) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }
  spi_transfer(&_spi, (uint8_t *)&data, (!skipReceive) ? (uint8_t *)&data : NULL, sizeof(uint16_t));

  if (_spiSettings.bitOrder) {
    tmp = ((data & 0xff00) >> 8) | ((data & 0xff) << 8);
    data = tmp;
  }

  return data;
}

/**
  * @brief  Transfer several bytes. Only one buffer used to send and receive data.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  buf: pointer to the bytes to send. The bytes received are copy in
  *         this buffer.
  * @param  count: number of bytes to send/receive.
  * @param  skipReceive: skip receiving data after transmit or not.
  *         SPI_TRANSMITRECEIVE or SPI_TRANSMITONLY.
  *         Optional, default: SPI_TRANSMITRECEIVE.
  */
void SPIClass::transfer(void *buf, size_t count, bool skipReceive)
{
  spi_transfer(&_spi, (uint8_t *)buf, (!skipReceive) ? (uint8_t *)buf : NULL, count);

}

/**
  * @brief  Transfer several bytes. One constant buffer used to send and
  *         one to receive data.
  *         begin() or beginTransaction() must be called at least once before.
  * @param  tx_buf: array of Tx bytes that is filled by the user before starting
  *                 the SPI transfer. If NULL, default dummy 0xFF bytes will be
  *                 clocked out.
  * @param  rx_buf: array of Rx bytes that will be filled by the slave during
  *                 the SPI transfer. If NULL, the received data will be discarded.
  * @param  count: number of bytes to send/receive.
  */
spi_status_e SPIClass::transfer(const void *tx_buf, void *rx_buf, size_t count)
{
  return spi_transfer(&_spi, ((const uint8_t *)tx_buf), ((uint8_t *)rx_buf), count);
}


/**
  * @brief  Not implemented.
  */
void SPIClass::usingInterrupt(int interruptNumber)
{
  UNUSED(interruptNumber);
}

/**
  * @brief  Not implemented.
  */
void SPIClass::notUsingInterrupt(int interruptNumber)
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

#if defined(SUBGHZSPI_BASE)
void SUBGHZSPIClass::enableDebugPins(uint32_t mosi, uint32_t miso, uint32_t sclk, uint32_t ssel)
{
  /* Configure SPI GPIO pins */
  pinmap_pinout(digitalPinToPinName(mosi), PinMap_SPI_MOSI);
  pinmap_pinout(digitalPinToPinName(miso), PinMap_SPI_MISO);
  pinmap_pinout(digitalPinToPinName(sclk), PinMap_SPI_SCLK);
  pinmap_pinout(digitalPinToPinName(ssel), PinMap_SPI_SSEL);
}
#endif
