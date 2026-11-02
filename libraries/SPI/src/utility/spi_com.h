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

/**
  * @brief SPI instance data.
  */
struct spi_s {
#if defined(USE_HALV2_DRIVER)
  hal_spi_handle_t handle;  /**< HAL SPI handle. */
#else
  SPI_HandleTypeDef handle; /**< HAL SPI handle. */
#endif
  SPI_TypeDef *spi;   /**< SPI peripheral instance. */
  PinName pin_miso;   /**< MISO pin. */
  PinName pin_mosi;   /**< MOSI pin. */
  PinName pin_sclk;   /**< SCLK pin. */
  PinName pin_ssel;   /**< Hardware SSEL pin, NC if not used. */
#if defined(SPI_IFCR_EOTC)
  /**
    * @brief Delay in microseconds before disabling SPI, to avoid truncating the
    *        last bit/clock.
    *        See https://github.com/stm32duino/Arduino_Core_STM32/issues/1294
    */
  uint32_t disable_delay;
#endif
};

/** @brief SPI instance type. */
typedef struct spi_s spi_t;


/** @brief Default SPI bus speed in Hz. */
#define SPI_SPEED_CLOCK_DEFAULT     4000000

/** @name SPI speed dividers
  * @brief Divider values (2 to 256) applied to the SPI peripheral clock.
  * @{
  */
#define SPI_SPEED_CLOCK_DIV2_MHZ    ((uint32_t)2)
#define SPI_SPEED_CLOCK_DIV4_MHZ    ((uint32_t)4)
#define SPI_SPEED_CLOCK_DIV8_MHZ    ((uint32_t)8)
#define SPI_SPEED_CLOCK_DIV16_MHZ   ((uint32_t)16)
#define SPI_SPEED_CLOCK_DIV32_MHZ   ((uint32_t)32)
#define SPI_SPEED_CLOCK_DIV64_MHZ   ((uint32_t)64)
#define SPI_SPEED_CLOCK_DIV128_MHZ  ((uint32_t)128)
#define SPI_SPEED_CLOCK_DIV256_MHZ  ((uint32_t)256)
/** @} */

/**
  * @brief Default timeout delay in milliseconds for the SPI transfer.
  *        Can be overridden before including this file, it must be greater than 0.
  */
#ifndef SPI_TRANSFER_TIMEOUT
#define SPI_TRANSFER_TIMEOUT 1000
#elif SPI_TRANSFER_TIMEOUT <= 0
#error "SPI_TRANSFER_TIMEOUT cannot be less or equal to 0!"
#endif

/**
  * @brief SPI data mode.
  *
  * Mode          Clock Polarity (CPOL)       Clock Phase (CPHA)
  * SPI_MODE0             0                         0
  * SPI_MODE1             0                         1
  * SPI_MODE2             1                         0
  * SPI_MODE3             1                         1
  * @note Enum definitions coming from SPI.h of SAM.
  */
typedef enum {
  SPI_MODE0_C = 0,
  SPI_MODE1_C = 1,
  SPI_MODE2_C = 2,
  SPI_MODE3_C = 3,
} spi_mode_e;

/** @brief SPI bus mode. */
typedef enum {
  SPI_CONTROLLER_C = 0,
  SPI_PERIPHERAL_C = 1,
} spi_busmode_e;

/** @brief SPI status codes. */
typedef enum {
  SPI_OK = 0,
  SPI_TIMEOUT = 1,
  SPI_ERROR = 2
} spi_status_e;

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Initialize the SPI instance.
  * @param  obj Pointer to spi_t structure.
  * @param  speed Clock speed of the SPI bus in Hz.
  * @param  dataMode One of the SPI data modes (spi_mode_e).
  * @param  msbFirst true for MSB first, false for LSB first.
  * @param  busMode SPI bus mode: controller or peripheral.
  */
void spi_init(spi_t *obj, uint32_t speed, spi_mode_e dataMode, bool msbFirst, spi_busmode_e busMode);
/**
  * @brief  Deinitialize the SPI interface (IOs and SPI block).
  * @param  obj Pointer to spi_t structure.
  */
void spi_deinit(spi_t *obj);
/**
  * @brief  Send and receive data over the SPI interface.
  * @param  obj Pointer to spi_t structure.
  * @param  tx_buffer Data to send before reception. If NULL, dummy 0xFF bytes
  *         are clocked out.
  * @param  rx_buffer Buffer to store the received data. If NULL, the received
  *         data is discarded.
  * @param  len Length in bytes of the data to send and receive.
  * @retval SPI_OK on success.
  * @retval SPI_TIMEOUT if SPI_TRANSFER_TIMEOUT elapsed during the transfer.
  * @retval SPI_ERROR if len is 0.
  */
spi_status_e spi_transfer(spi_t *obj, const uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t len);
/**
  * @brief  Return the clock frequency of an SPI instance.
  * @param  obj Pointer to spi_t structure.
  * @return Clock frequency of the instance, or SystemCoreClock if not found.
  */
uint32_t spi_getClkFreq(spi_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_COM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
