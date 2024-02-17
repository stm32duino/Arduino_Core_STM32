/*
 * Copyright (c) 2016 Frederic Pillon <frederic.pillon@st.com> for
 * STMicroelectronics. All right reserved.
 * Interface utility of the spi module for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#include "wiring_time.h"
#include "core_debug.h"
#include "stm32_def.h"
#include "utility/spi_com.h"
#include "PinAF_STM32F1.h"
#include "pinconfig.h"
#include "stm32yyxx_ll_spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Private Functions */
/**
  * @brief  return clock freq of an SPI instance
  * @param  spi_inst : SPI instance
  * @retval clock freq of the instance else SystemCoreClock
  */
uint32_t spi_getClkFreqInst(SPI_TypeDef *spi_inst)
{
  uint32_t spi_freq = SystemCoreClock;
  if (spi_inst != NP) {
#if defined(STM32C0xx) || defined(STM32F0xx) || defined(STM32G0xx)
    /* SPIx source CLK is PCKL1 */
    spi_freq = HAL_RCC_GetPCLK1Freq();
#else
#if defined(SPI1_BASE)
    if (spi_inst == SPI1) {
#if defined(RCC_PERIPHCLK_SPI1) || defined(RCC_PERIPHCLK_SPI123)
#ifdef RCC_PERIPHCLK_SPI1
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI1);
#else
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
#endif
      if (spi_freq == 0)
#endif
      {
        /* SPI1, SPI4, SPI5 and SPI6. Source CLK is PCKL2 */
        spi_freq = HAL_RCC_GetPCLK2Freq();
      }
    }
#endif // SPI1_BASE
#if defined(SPI2_BASE)
    if (spi_inst == SPI2) {
#if defined(RCC_PERIPHCLK_SPI2) || defined(RCC_PERIPHCLK_SPI123) ||\
    defined(RCC_PERIPHCLK_SPI23)
#ifdef RCC_PERIPHCLK_SPI2
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI2);
#elif defined(RCC_PERIPHCLK_SPI123)
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
#else
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI23);
#endif
      if (spi_freq == 0)
#endif
      {
        /* SPI_2 and SPI_3. Source CLK is PCKL1 */
        spi_freq = HAL_RCC_GetPCLK1Freq();
      }
    }
#endif // SPI2_BASE
#if defined(SPI3_BASE)
    if (spi_inst == SPI3) {
#if defined(RCC_PERIPHCLK_SPI3) || defined(RCC_PERIPHCLK_SPI123) ||\
    defined(RCC_PERIPHCLK_SPI23)
#ifdef RCC_PERIPHCLK_SPI3
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI3);
#elif defined(RCC_PERIPHCLK_SPI123)
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
#else
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI23);
#endif
      if (spi_freq == 0)
#endif
      {
        /* SPI_2 and SPI_3. Source CLK is PCKL1 */
        spi_freq = HAL_RCC_GetPCLK1Freq();
      }
    }
#endif // SPI3_BASE
#if defined(SPI4_BASE)
    if (spi_inst == SPI4) {
#if defined(RCC_PERIPHCLK_SPI4) || defined(RCC_PERIPHCLK_SPI45)
#ifdef RCC_PERIPHCLK_SPI4
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI4);
#else
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI45);
#endif
      if (spi_freq == 0)
#endif
      {
        /* SPI1, SPI4, SPI5 and SPI6. Source CLK is PCKL2 */
        spi_freq = HAL_RCC_GetPCLK2Freq();
      }
    }
#endif // SPI4_BASE
#if defined(SPI5_BASE)
    if (spi_inst == SPI5) {
#if defined(RCC_PERIPHCLK_SPI5) || defined(RCC_PERIPHCLK_SPI45)
#ifdef RCC_PERIPHCLK_SPI5
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI5);
#else
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI45);
#endif
      if (spi_freq == 0)
#endif
      {
        /* SPI1, SPI4, SPI5 and SPI6. Source CLK is PCKL2 */
        spi_freq = HAL_RCC_GetPCLK2Freq();
      }
    }
#endif // SPI5_BASE
#if defined(SPI6_BASE)
    if (spi_inst == SPI6) {
#if defined(RCC_PERIPHCLK_SPI6)
      spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI6);
      if (spi_freq == 0)
#endif
      {
        /* SPI1, SPI4, SPI5 and SPI6. Source CLK is PCKL2 */
        spi_freq = HAL_RCC_GetPCLK2Freq();
      }
    }
#endif // SPI6_BASE
#if defined(SUBGHZSPI_BASE)
    if (spi_inst == SUBGHZSPI) {
      /* Source CLK is APB3 (PCLK3) is derived from AHB3 clock  */
      spi_freq = HAL_RCC_GetHCLK3Freq();
    }
#endif // SUBGHZSPI_BASE
#endif
  }
  return spi_freq;
}

/**
  * @brief  return clock freq of an SPI instance
  * @param  obj : pointer to spi_t structure
  * @retval clock freq of the instance else SystemCoreClock
  */
uint32_t spi_getClkFreq(spi_t *obj)
{
  SPI_TypeDef *spi_inst = NP;
  uint32_t spi_freq = SystemCoreClock;

  if (obj != NULL) {
#if defined(SUBGHZSPI_BASE)
    if (obj->handle.Instance == SUBGHZSPI) {
      spi_inst = SUBGHZSPI;
    } else
#endif
    {
      spi_inst = pinmap_peripheral(obj->pin_sclk, PinMap_SPI_SCLK);
    }

    if (spi_inst != NP) {
      spi_freq = spi_getClkFreqInst(spi_inst);
    }
  }
  return spi_freq;
}


#if defined(SPI_IFCR_EOTC)
/**
  * @brief  Compute delay before disabling SPI
  *         See https://github.com/stm32duino/Arduino_Core_STM32/issues/1294
  *         Computed delay is half SPI clock
  * @param  obj : pointer to spi_t structure
  * @retval Disable delay in microsecondes
  */
static uint32_t compute_disable_delay(spi_t *obj)
{
  uint32_t spi_freq = spi_getClkFreqInst(obj->spi);
  uint32_t disable_delay;
  uint32_t prescaler;
  SPI_HandleTypeDef *handle = &(obj->handle);

  prescaler = 1 << ((handle->Init.BaudRatePrescaler >> SPI_CFG1_MBR_Pos) + 1);
  disable_delay = (((prescaler * 1000000) / spi_freq) / 2) + 1;
  return disable_delay;
}
#endif

/**
  * @brief  SPI initialization function
  * @param  obj : pointer to spi_t structure
  * @param  speed : spi output speed
  * @param  mode : one of the spi modes
  * @param  msb : set to 1 in msb first
  * @retval None
  */
void spi_init(spi_t *obj, uint32_t speed, SPIMode mode, uint8_t msb)
{
  if (obj == NULL) {
    return;
  }

  SPI_HandleTypeDef *handle = &(obj->handle);
  uint32_t spi_freq = 0;
  uint32_t pull = 0;

#if defined(SUBGHZSPI_BASE)
  if (obj->spi != SUBGHZSPI) {
#endif
    // Determine the SPI to use
    SPI_TypeDef *spi_mosi = pinmap_peripheral(obj->pin_mosi, PinMap_SPI_MOSI);
    SPI_TypeDef *spi_miso = pinmap_peripheral(obj->pin_miso, PinMap_SPI_MISO);
    SPI_TypeDef *spi_sclk = pinmap_peripheral(obj->pin_sclk, PinMap_SPI_SCLK);
    SPI_TypeDef *spi_ssel = pinmap_peripheral(obj->pin_ssel, PinMap_SPI_SSEL);

    /* Pins MOSI/MISO/SCLK must not be NP. ssel can be NP. */
    if (spi_mosi == NP || spi_miso == NP || spi_sclk == NP) {
      core_debug("ERROR: at least one SPI pin has no peripheral\n");
      return;
    }

    SPI_TypeDef *spi_data = pinmap_merge_peripheral(spi_mosi, spi_miso);
    SPI_TypeDef *spi_cntl = pinmap_merge_peripheral(spi_sclk, spi_ssel);

    obj->spi = pinmap_merge_peripheral(spi_data, spi_cntl);

    // Are all pins connected to the same SPI instance?
    if (spi_data == NP || spi_cntl == NP || obj->spi == NP) {
      core_debug("ERROR: SPI pins mismatch\n");
      return;
    }
#if defined(SUBGHZSPI_BASE)
  } else {
    if (obj->pin_mosi != NC || obj->pin_miso != NC || obj->pin_sclk != NC || obj->pin_ssel != NC) {
      core_debug("ERROR: SUBGHZ_SPI cannot define custom pins\n");
      return;
    }
  }
#endif

  // Configure the SPI pins
  if (obj->pin_ssel != NC) {
    handle->Init.NSS = SPI_NSS_HARD_OUTPUT;
  } else {
    handle->Init.NSS = SPI_NSS_SOFT;
  }

  /* Fill default value */
  handle->Instance               = obj->spi;
  handle->Init.Mode              = SPI_MODE_MASTER;

  spi_freq = spi_getClkFreqInst(obj->spi);
  /* For SUBGHZSPI,  'SPI_BAUDRATEPRESCALER_*' == 'SUBGHZSPI_BAUDRATEPRESCALER_*' */
  if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV2_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV4_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV8_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV16_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV32_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV64_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV128_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  } else {
    /*
     * As it is not possible to go below (spi_freq / SPI_SPEED_CLOCK_DIV256_MHZ).
     * Set prescaler at max value so get the lowest frequency possible.
     */
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  }

#if defined(SPI_IFCR_EOTC)
  // Compute disable delay as baudrate has been modified
  obj->disable_delay = compute_disable_delay(obj);
#endif

  handle->Init.Direction         = SPI_DIRECTION_2LINES;

  if ((mode == SPI_MODE0) || (mode == SPI_MODE2)) {
    handle->Init.CLKPhase          = SPI_PHASE_1EDGE;
  } else {
    handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  }

  if ((mode == SPI_MODE0) || (mode == SPI_MODE1)) {
    handle->Init.CLKPolarity       = SPI_POLARITY_LOW;
  } else {
    handle->Init.CLKPolarity       = SPI_POLARITY_HIGH;
  }

  handle->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  handle->Init.CRCPolynomial     = 7;
  handle->Init.DataSize          = SPI_DATASIZE_8BIT;

  if (msb == 0) {
    handle->Init.FirstBit          = SPI_FIRSTBIT_LSB;
  } else {
    handle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  }

  handle->Init.TIMode            = SPI_TIMODE_DISABLE;
#if defined(SPI_NSS_PULSE_DISABLE)
  handle->Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
#endif
#ifdef SPI_MASTER_KEEP_IO_STATE_ENABLE
  handle->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;  /* Recommended setting to avoid glitches */
#endif

#if defined(SUBGHZSPI_BASE)
  if (handle->Instance != SUBGHZSPI) {
#endif
    /* Configure SPI GPIO pins */
    pinmap_pinout(obj->pin_mosi, PinMap_SPI_MOSI);
    pinmap_pinout(obj->pin_miso, PinMap_SPI_MISO);
    pinmap_pinout(obj->pin_sclk, PinMap_SPI_SCLK);
    /*
    * According the STM32 Datasheet for SPI peripheral we need to PULLDOWN
    * or PULLUP the SCK pin according the polarity used.
    */
    pull = (handle->Init.CLKPolarity == SPI_POLARITY_LOW) ? GPIO_PULLDOWN : GPIO_PULLUP;
    pin_PullConfig(get_GPIO_Port(STM_PORT(obj->pin_sclk)), STM_LL_GPIO_PIN(obj->pin_sclk), pull);
    pinmap_pinout(obj->pin_ssel, PinMap_SPI_SSEL);
#if defined(SUBGHZSPI_BASE)
  }
#endif
#if defined SPI1_BASE
  // Enable SPI clock
  if (handle->Instance == SPI1) {
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();
  }
#endif

#if defined SPI2_BASE
  if (handle->Instance == SPI2) {
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_SPI2_FORCE_RESET();
    __HAL_RCC_SPI2_RELEASE_RESET();
  }
#endif

#if defined SPI3_BASE
  if (handle->Instance == SPI3) {
    __HAL_RCC_SPI3_CLK_ENABLE();
    __HAL_RCC_SPI3_FORCE_RESET();
    __HAL_RCC_SPI3_RELEASE_RESET();
  }
#endif

#if defined SPI4_BASE
  if (handle->Instance == SPI4) {
    __HAL_RCC_SPI4_CLK_ENABLE();
    __HAL_RCC_SPI4_FORCE_RESET();
    __HAL_RCC_SPI4_RELEASE_RESET();
  }
#endif

#if defined SPI5_BASE
  if (handle->Instance == SPI5) {
    __HAL_RCC_SPI5_CLK_ENABLE();
    __HAL_RCC_SPI5_FORCE_RESET();
    __HAL_RCC_SPI5_RELEASE_RESET();
  }
#endif

#if defined SPI6_BASE
  if (handle->Instance == SPI6) {
    __HAL_RCC_SPI6_CLK_ENABLE();
    __HAL_RCC_SPI6_FORCE_RESET();
    __HAL_RCC_SPI6_RELEASE_RESET();
  }
#endif

#if defined SUBGHZSPI_BASE
  if (handle->Instance == SUBGHZSPI) {
    __HAL_RCC_SUBGHZSPI_CLK_ENABLE();
    __HAL_RCC_SUBGHZSPI_FORCE_RESET();
    __HAL_RCC_SUBGHZSPI_RELEASE_RESET();
  }
#endif

  HAL_SPI_Init(handle);

  /* In order to set correctly the SPI polarity we need to enable the peripheral */
  __HAL_SPI_ENABLE(handle);
}

/**
  * @brief This function is implemented to deinitialize the SPI interface
  *        (IOs + SPI block)
  * @param  obj : pointer to spi_t structure
  * @retval None
  */
void spi_deinit(spi_t *obj)
{
  if (obj == NULL) {
    return;
  }

  SPI_HandleTypeDef *handle = &(obj->handle);

  HAL_SPI_DeInit(handle);

#if defined SPI1_BASE
  // Reset SPI and disable clock
  if (handle->Instance == SPI1) {
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();
    __HAL_RCC_SPI1_CLK_DISABLE();
  }
#endif
#if defined SPI2_BASE
  if (handle->Instance == SPI2) {
    __HAL_RCC_SPI2_FORCE_RESET();
    __HAL_RCC_SPI2_RELEASE_RESET();
    __HAL_RCC_SPI2_CLK_DISABLE();
  }
#endif

#if defined SPI3_BASE
  if (handle->Instance == SPI3) {
    __HAL_RCC_SPI3_FORCE_RESET();
    __HAL_RCC_SPI3_RELEASE_RESET();
    __HAL_RCC_SPI3_CLK_DISABLE();
  }
#endif

#if defined SPI4_BASE
  if (handle->Instance == SPI4) {
    __HAL_RCC_SPI4_FORCE_RESET();
    __HAL_RCC_SPI4_RELEASE_RESET();
    __HAL_RCC_SPI4_CLK_DISABLE();
  }
#endif

#if defined SPI5_BASE
  if (handle->Instance == SPI5) {
    __HAL_RCC_SPI5_FORCE_RESET();
    __HAL_RCC_SPI5_RELEASE_RESET();
    __HAL_RCC_SPI5_CLK_DISABLE();
  }
#endif

#if defined SPI6_BASE
  if (handle->Instance == SPI6) {
    __HAL_RCC_SPI6_FORCE_RESET();
    __HAL_RCC_SPI6_RELEASE_RESET();
    __HAL_RCC_SPI6_CLK_DISABLE();
  }
#endif

#if defined SUBGHZSPI_BASE
  if (handle->Instance == SUBGHZSPI) {
    __HAL_RCC_SUBGHZSPI_FORCE_RESET();
    __HAL_RCC_SUBGHZSPI_RELEASE_RESET();
    __HAL_RCC_SUBGHZSPI_CLK_DISABLE();
  }
#endif
}

/**
  * @brief This function is implemented by user to send/receive data over
  *         SPI interface
  * @param  obj : pointer to spi_t structure
  * @param  tx_buffer : tx data to send before reception
  * @param  rx_buffer : rx data to receive if not numm
  * @param  len : length in byte of the data to send and receive
  * @retval status of the send operation (0) in case of error
  */
spi_status_e spi_transfer(spi_t *obj, const uint8_t *tx_buffer, uint8_t *rx_buffer,
                          uint16_t len)
{
  spi_status_e ret = SPI_OK;
  uint32_t tickstart, size = len;
  SPI_TypeDef *_SPI = obj->handle.Instance;
  uint8_t *tx_buf = (uint8_t *)tx_buffer;

  if (len == 0) {
    ret = SPI_ERROR;
  } else {
    tickstart = HAL_GetTick();

#if defined(SPI_CR2_TSIZE)
    /* Start transfer */
    LL_SPI_SetTransferSize(_SPI, size);
    LL_SPI_Enable(_SPI);
    LL_SPI_StartMasterTransfer(_SPI);
#endif

    while (size--) {
#if defined(SPI_SR_TXP)
      while (!LL_SPI_IsActiveFlag_TXP(_SPI));
#else
      while (!LL_SPI_IsActiveFlag_TXE(_SPI));
#endif
      LL_SPI_TransmitData8(_SPI, tx_buf ? *tx_buf++ : 0XFF);

#if defined(SPI_SR_RXP)
      while (!LL_SPI_IsActiveFlag_RXP(_SPI));
#else
      while (!LL_SPI_IsActiveFlag_RXNE(_SPI));
#endif
      if (rx_buffer) {
        *rx_buffer++ = LL_SPI_ReceiveData8(_SPI);
      } else {
        LL_SPI_ReceiveData8(_SPI);
      }
      if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
          (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
        ret = SPI_TIMEOUT;
        break;
      }
    }

#if defined(SPI_IFCR_EOTC)
    // Add a delay before disabling SPI otherwise last-bit/last-clock may be truncated
    // See https://github.com/stm32duino/Arduino_Core_STM32/issues/1294
    // Computed delay is half SPI clock
    delayMicroseconds(obj->disable_delay);

    /* Close transfer */
    /* Clear flags */
    LL_SPI_ClearFlag_EOT(_SPI);
    LL_SPI_ClearFlag_TXTF(_SPI);
    /* Disable SPI peripheral */
    LL_SPI_Disable(_SPI);
#else
    /* Wait for end of transfer */
    while (LL_SPI_IsActiveFlag_BSY(_SPI));
#endif
  }
  return ret;
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
