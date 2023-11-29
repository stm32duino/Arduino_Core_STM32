/*
 * Copyright (c) 2016 Frederic Pillon <frederic.pillon@st.com> for
 * STMicroelectronics. All right reserved.
 * Header utility of the spi module for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_COM_H
#define __SPI_COM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

struct spi_s {
  SPI_HandleTypeDef handle;
  SPI_TypeDef *spi;
  PinName pin_miso;
  PinName pin_mosi;
  PinName pin_sclk;
  PinName pin_ssel;
#if defined(SPI_IFCR_EOTC)
  // Delay before disabling SPI.
  // See https://github.com/stm32duino/Arduino_Core_STM32/issues/1294
  uint32_t disable_delay;
#endif
};

typedef struct spi_s spi_t;


///@brief specifies the SPI speed bus in HZ.
#define SPI_SPEED_CLOCK_DEFAULT     4000000

#define SPI_SPEED_CLOCK_DIV2_MHZ    ((uint32_t)2)
#define SPI_SPEED_CLOCK_DIV4_MHZ    ((uint32_t)4)
#define SPI_SPEED_CLOCK_DIV8_MHZ    ((uint32_t)8)
#define SPI_SPEED_CLOCK_DIV16_MHZ   ((uint32_t)16)
#define SPI_SPEED_CLOCK_DIV32_MHZ   ((uint32_t)32)
#define SPI_SPEED_CLOCK_DIV64_MHZ   ((uint32_t)64)
#define SPI_SPEED_CLOCK_DIV128_MHZ  ((uint32_t)128)
#define SPI_SPEED_CLOCK_DIV256_MHZ  ((uint32_t)256)

// Defines a default timeout delay in milliseconds for the SPI transfer
#ifndef SPI_TRANSFER_TIMEOUT
#define SPI_TRANSFER_TIMEOUT 1000
#elif SPI_TRANSFER_TIMEOUT <= 0
#error "SPI_TRANSFER_TIMEOUT cannot be less or equal to 0!"
#endif

///@brief specifies the SPI mode to use
//Mode          Clock Polarity (CPOL)       Clock Phase (CPHA)
//SPI_MODE0             0                         0
//SPI_MODE1             0                         1
//SPI_MODE2             1                         0
//SPI_MODE3             1                         1
//enum definitions coming from SPI.h of SAM
// SPI mode parameters for SPISettings
typedef enum {
  SPI_MODE0 = 0,
  SPI_MODE1 = 1,
  SPI_MODE2 = 2,
  SPI_MODE3 = 3,
} SPIMode;

///@brief SPI errors
typedef enum {
  SPI_OK = 0,
  SPI_TIMEOUT = 1,
  SPI_ERROR = 2
} spi_status_e;

/* Exported functions ------------------------------------------------------- */
void spi_init(spi_t *obj, uint32_t speed, SPIMode mode, uint8_t msb);
void spi_deinit(spi_t *obj);
spi_status_e spi_transfer(spi_t *obj, const uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t len);
uint32_t spi_getClkFreq(spi_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_COM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
