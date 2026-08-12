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
#include "wiring.h"
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
#if defined(STM32WB0x) || defined(STM32WL3x)
  (void)spi_inst; // Avoid unused parameter warning
  spi_freq = SystemCoreClock / 4;
#else
  if (spi_inst != NP) {
#if defined(STM32C0xx) || defined(STM32F0xx) || defined(STM32G0xx) || \
    defined(STM32U0xx)
    /* SPIx source CLK is PCKL1 */
    spi_freq = HAL_RCC_GetPCLK1Freq();
#else
#if defined(SPI1_BASE)
    if (spi_inst == SPI1) {
#if defined(USE_HALV2_DRIVER)
      spi_freq = HAL_RCC_SPI1_GetKernelClkFreq();
#else
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
#endif
    }
#endif // SPI1_BASE
#if defined(SPI2_BASE)
    if (spi_inst == SPI2) {
#if defined(USE_HALV2_DRIVER)
      spi_freq = HAL_RCC_SPI2_GetKernelClkFreq();
#else
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
#endif
    }
#endif // SPI2_BASE
#if defined(SPI3_BASE)
    if (spi_inst == SPI3) {
#if defined(USE_HALV2_DRIVER)
      spi_freq = HAL_RCC_SPI3_GetKernelClkFreq();
#else
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
#endif
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
#endif // !STM32WB0x
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
static uint32_t compute_disable_delay(uint32_t spi_freq, uint32_t prescaler)
{
  uint32_t disable_delay;
  prescaler = 1 << ((prescaler >> SPI_CFG1_MBR_Pos) + 1);
  disable_delay = (((prescaler * 1000000) / spi_freq) / 2) + 1;
  return disable_delay;
}
#endif

/**
  * @brief  SPI initialization function
  * @param  obj : pointer to spi_t structure
  * @param  speed : spi output speed
  * @param  dataMode : one of the spi modes
  * @param  msbFirst : set to true in msb first
  * @param  busMode : spi busMode: controller or peripheral
  * @retval None
  */
void spi_init(spi_t *obj, uint32_t speed, spi_mode_e dataMode, bool msbFirst, spi_busmode_e busMode)
{
  if (obj != NULL) {
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
    if (obj->spi != SUBGHZSPI) {
#endif
      /* Configure SPI GPIO pins */
      pinmap_pinout(obj->pin_mosi, PinMap_SPI_MOSI);
      pinmap_pinout(obj->pin_miso, PinMap_SPI_MISO);
      pinmap_pinout(obj->pin_sclk, PinMap_SPI_SCLK);
      /*
      * According the STM32 Datasheet for SPI peripheral we need to PULLDOWN
      * or PULLUP the SCK pin according the polarity used.
      */
      pull = ((dataMode == SPI_MODE0_C) || (dataMode == SPI_MODE1_C)) ? LL_GPIO_PULL_DOWN : LL_GPIO_PULL_UP;
      pin_PullConfig(get_GPIO_Port(STM_PORT(obj->pin_sclk)), STM_LL_GPIO_PIN(obj->pin_sclk), pull);
      pinmap_pinout(obj->pin_ssel, PinMap_SPI_SSEL);
#if defined(SUBGHZSPI_BASE)
    }
#endif
#if defined SPI1_BASE
    // Enable SPI clock
    if (obj->spi == SPI1) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI1_EnableClock();
      HAL_RCC_SPI1_Reset();
#else
      __HAL_RCC_SPI1_CLK_ENABLE();
      __HAL_RCC_SPI1_FORCE_RESET();
      __HAL_RCC_SPI1_RELEASE_RESET();
#endif
    }
#endif

#if defined SPI2_BASE
    if (obj->spi == SPI2) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI2_EnableClock();
      HAL_RCC_SPI2_Reset();
#else
      __HAL_RCC_SPI2_CLK_ENABLE();
      __HAL_RCC_SPI2_FORCE_RESET();
      __HAL_RCC_SPI2_RELEASE_RESET();
#endif
    }
#endif

#if defined SPI3_BASE
    if (obj->spi == SPI3) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI3_EnableClock();
      HAL_RCC_SPI3_Reset();
#else
      __HAL_RCC_SPI3_CLK_ENABLE();
      __HAL_RCC_SPI3_FORCE_RESET();
      __HAL_RCC_SPI3_RELEASE_RESET();
#endif
    }
#endif

#if defined SPI4_BASE
    if (obj->spi == SPI4) {
      __HAL_RCC_SPI4_CLK_ENABLE();
      __HAL_RCC_SPI4_FORCE_RESET();
      __HAL_RCC_SPI4_RELEASE_RESET();
    }
#endif

#if defined SPI5_BASE
    if (obj->spi == SPI5) {
      __HAL_RCC_SPI5_CLK_ENABLE();
      __HAL_RCC_SPI5_FORCE_RESET();
      __HAL_RCC_SPI5_RELEASE_RESET();
    }
#endif

#if defined SPI6_BASE
    if (obj->spi == SPI6) {
      __HAL_RCC_SPI6_CLK_ENABLE();
      __HAL_RCC_SPI6_FORCE_RESET();
      __HAL_RCC_SPI6_RELEASE_RESET();
    }
#endif

#if defined SUBGHZSPI_BASE
    if (obj->spi == SUBGHZSPI) {
      __HAL_RCC_SUBGHZSPI_CLK_ENABLE();
      __HAL_RCC_SUBGHZSPI_FORCE_RESET();
      __HAL_RCC_SUBGHZSPI_RELEASE_RESET();
    }
#endif
#if defined(USE_HALV2_DRIVER)
    hal_spi_handle_t *hspi = &(obj->handle);
    hal_spi_config_t spi_config;
    // hal_status_t status = HAL_OK;
    HAL_SPI_Init(hspi, (hal_spi_t)obj->spi);
    spi_config.mode = (busMode == SPI_CONTROLLER_C) ? HAL_SPI_MODE_MASTER : HAL_SPI_MODE_SLAVE;
    spi_config.direction = HAL_SPI_DIRECTION_FULL_DUPLEX;
    spi_config.data_width = HAL_SPI_DATA_WIDTH_8_BIT;
    spi_config.clock_polarity = ((dataMode == SPI_MODE0_C) || (dataMode == SPI_MODE1_C)) ? HAL_SPI_CLOCK_POLARITY_LOW : HAL_SPI_CLOCK_POLARITY_HIGH;
    spi_config.clock_phase = ((dataMode == SPI_MODE0_C) || (dataMode == SPI_MODE2_C)) ? HAL_SPI_CLOCK_PHASE_1_EDGE : HAL_SPI_CLOCK_PHASE_2_EDGE;
    spi_config.first_bit = (msbFirst) ? HAL_SPI_MSB_FIRST : HAL_SPI_LSB_FIRST;
    spi_config.nss_pin_management = (obj->pin_ssel != NC) ? HAL_SPI_NSS_PIN_MGMT_OUTPUT : HAL_SPI_NSS_PIN_MGMT_INTERNAL;

    spi_freq = spi_getClkFreqInst(obj->spi);
    if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV2_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_2;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV4_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_4;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV8_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_8;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV16_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_16;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV32_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_32;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV64_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_64;
    } else if (speed >= (spi_freq / SPI_SPEED_CLOCK_DIV128_MHZ)) {
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_128;
    } else {
      /*
       * As it is not possible to go below (spi_freq / SPI_SPEED_CLOCK_DIV256_MHZ).
       * Set prescaler at max value so get the lowest frequency possible.
       */
      spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_256;
    }
#if defined(SPI_IFCR_EOTC)
    // Compute disable delay as baudrate has been modified
    obj->disable_delay = compute_disable_delay(spi_freq, spi_config.baud_rate_prescaler);
#endif
    HAL_SPI_SetConfig(hspi, &spi_config);
#else
    SPI_HandleTypeDef *handle = &(obj->handle);

    // Configure the SPI pins
    if (obj->pin_ssel != NC) {
      handle->Init.NSS = SPI_NSS_HARD_OUTPUT;
    } else {
      handle->Init.NSS = SPI_NSS_SOFT;
    }

    /* Fill default value */
    handle->Instance = obj->spi;
    handle->Init.Mode = (busMode == SPI_CONTROLLER_C) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;

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
    obj->disable_delay = compute_disable_delay(spi_freq, handle->Init.BaudRatePrescaler);
#endif

    handle->Init.Direction         = SPI_DIRECTION_2LINES;

    if ((dataMode == SPI_MODE0_C) || (dataMode == SPI_MODE2_C)) {
      handle->Init.CLKPhase          = SPI_PHASE_1EDGE;
    } else {
      handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
    }

    if ((dataMode == SPI_MODE0_C) || (dataMode == SPI_MODE1_C)) {
      handle->Init.CLKPolarity       = SPI_POLARITY_LOW;
    } else {
      handle->Init.CLKPolarity       = SPI_POLARITY_HIGH;
    }

    handle->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    handle->Init.CRCPolynomial     = 7;
    handle->Init.DataSize          = SPI_DATASIZE_8BIT;

    if (msbFirst) {
      handle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
    } else {
      handle->Init.FirstBit          = SPI_FIRSTBIT_LSB;
    }

    handle->Init.TIMode            = SPI_TIMODE_DISABLE;
#if defined(SPI_NSS_PULSE_DISABLE)
    handle->Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
#endif
#ifdef SPI_MASTER_KEEP_IO_STATE_ENABLE
    handle->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;  /* Recommended setting to avoid glitches */
#endif
    HAL_SPI_Init(handle);
#endif /* USE_HALV2_DRIVER */
    /* In order to set correctly the SPI polarity we need to enable the peripheral */
    LL_SPI_Enable(obj->spi);
  }
}

/**
  * @brief This function is implemented to deinitialize the SPI interface
  *        (IOs + SPI block)
  * @param  obj : pointer to spi_t structure
  * @retval None
  */
void spi_deinit(spi_t *obj)
{
  if (obj != NULL) {
#if defined(USE_HALV2_DRIVER)
    hal_spi_handle_t *handle = &(obj->handle);

#else
    SPI_HandleTypeDef *handle = &(obj->handle);
#endif /* USE_HALV2_DRIVER */
    HAL_SPI_DeInit(handle);
#if defined SPI1_BASE
    // Reset SPI and disable clock
    if (obj->spi == SPI1) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI1_Reset();
      HAL_RCC_SPI1_DisableClock();
#else
      __HAL_RCC_SPI1_FORCE_RESET();
      __HAL_RCC_SPI1_RELEASE_RESET();
      __HAL_RCC_SPI1_CLK_DISABLE();
#endif
    }
#endif
#if defined SPI2_BASE
    if (obj->spi == SPI2) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI2_Reset();
      HAL_RCC_SPI2_DisableClock();
#else
      __HAL_RCC_SPI2_FORCE_RESET();
      __HAL_RCC_SPI2_RELEASE_RESET();
      __HAL_RCC_SPI2_CLK_DISABLE();
#endif
    }
#endif

#if defined SPI3_BASE
    if (obj->spi == SPI3) {
#if defined(USE_HALV2_DRIVER)
      HAL_RCC_SPI3_Reset();
      HAL_RCC_SPI3_DisableClock();
#else
      __HAL_RCC_SPI3_FORCE_RESET();
      __HAL_RCC_SPI3_RELEASE_RESET();
      __HAL_RCC_SPI3_CLK_DISABLE();
#endif
    }
#endif

#if defined SPI4_BASE
    if (obj->spi == SPI4) {
      __HAL_RCC_SPI4_FORCE_RESET();
      __HAL_RCC_SPI4_RELEASE_RESET();
      __HAL_RCC_SPI4_CLK_DISABLE();
    }
#endif

#if defined SPI5_BASE
    if (obj->spi == SPI5) {
      __HAL_RCC_SPI5_FORCE_RESET();
      __HAL_RCC_SPI5_RELEASE_RESET();
      __HAL_RCC_SPI5_CLK_DISABLE();
    }
#endif

#if defined SPI6_BASE
    if (obj->spi == SPI6) {
      __HAL_RCC_SPI6_FORCE_RESET();
      __HAL_RCC_SPI6_RELEASE_RESET();
      __HAL_RCC_SPI6_CLK_DISABLE();
    }
#endif

#if defined SUBGHZSPI_BASE
    if (obj->spi == SUBGHZSPI) {
      __HAL_RCC_SUBGHZSPI_FORCE_RESET();
      __HAL_RCC_SUBGHZSPI_RELEASE_RESET();
      __HAL_RCC_SUBGHZSPI_CLK_DISABLE();
    }
#endif
  }
}



/**
  * @brief This function is implemented to reset the SPI interface
  * @param  obj : pointer to spi_t structure
  * @retval None
  */
void spi_reset(spi_t *obj)
{
  if (obj == NULL) {
    return;
  }

#if defined SPI1_BASE
  // Reset SPI
  if (obj->spi == SPI1) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_SPI1_Reset()
#else
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();
#endif
  }
#endif

#if defined SPI2_BASE
  if (obj->spi == SPI2) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_SPI2_Reset();
#else
    __HAL_RCC_SPI2_FORCE_RESET();
    __HAL_RCC_SPI2_RELEASE_RESET();
#endif
  }
#endif

#if defined SPI3_BASE
  if (obj->spi == SPI3) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_SPI3_Reset();
#else
    __HAL_RCC_SPI3_FORCE_RESET();
    __HAL_RCC_SPI3_RELEASE_RESET();
#endif
  }
#endif

#if defined SPI4_BASE
  if (obj->spi == SPI4) {
    __HAL_RCC_SPI4_FORCE_RESET();
    __HAL_RCC_SPI4_RELEASE_RESET();
  }
#endif

#if defined SPI5_BASE
  if (obj->spi == SPI5) {
    __HAL_RCC_SPI5_FORCE_RESET();
    __HAL_RCC_SPI5_RELEASE_RESET();
  }
#endif

#if defined SPI6_BASE
  if (obj->spi == SPI6) {
    __HAL_RCC_SPI6_FORCE_RESET();
    __HAL_RCC_SPI6_RELEASE_RESET();
  }
#endif

#if defined SUBGHZSPI_BASE
  if (obj->spi == SUBGHZSPI) {
    __HAL_RCC_SUBGHZSPI_FORCE_RESET();
    __HAL_RCC_SUBGHZSPI_RELEASE_RESET();
  }
#endif

#if defined(USE_HALV2_DRIVER)
  hal_spi_handle_t *hspi = &(obj->handle);
  HAL_SPI_Init(hspi, (hal_spi_t)obj->spi);
#else
  SPI_HandleTypeDef *handle = &(obj->handle);
  HAL_SPI_Init(handle);
#endif
  /* In order to correctly set the SPI polarity we need to enable the peripheral */
  LL_SPI_Enable(obj->spi);
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
  SPI_TypeDef *_SPI = obj->spi;
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


/**
  * @brief  This function is used to send/receive one byte on SPI
  * @param  obj : pointer to spi_t structure
  * @param  tx: byte to send
  * @param  rx: pointer to byte received.  If NULL the received byte will be discarded
  * @retval status. SPI_OK = 0
  */
spi_status_e spi_read_write_byte(spi_t *obj, uint8_t tx, uint8_t *rx)
{
  spi_status_e ret = SPI_OK;
  int8_t tmp;
  uint32_t tickstart;
  SPI_TypeDef *_SPI;

  if ((obj == NULL) || obj->spi == NULL) {
    return (SPI_ERROR);
  }
  _SPI = obj->spi;

  tickstart = HAL_GetTick();

#if defined(SPI_SR_TXP) // True if we have fifo threshold support
  while (!LL_SPI_IsActiveFlag_TXP(_SPI)) {
    if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
        (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
      core_debug("SPI Active flag timed out\n");
      return (SPI_TIMEOUT);
    }
  }
#else
  while (!LL_SPI_IsActiveFlag_TXE(_SPI)) { // Wait for transmit empty before sending
    if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
        (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
      core_debug("SPI Active flag timed out\n");
      return (SPI_TIMEOUT);
    }
  }
#endif
  LL_SPI_TransmitData8(_SPI, tx);

#if defined(SPI_SR_RXP)
  while (!LL_SPI_IsActiveFlag_RXP(_SPI)) {
    if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
        (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
      core_debug("SPI Rx timed out\n");
      return (SPI_TIMEOUT);
    }
  }
#else
  while (!LL_SPI_IsActiveFlag_RXNE(_SPI)) { // Wait for Rx not empty before read
    if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
        (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
      core_debug("SPI Rx timed out\n");
      return (SPI_TIMEOUT);
    }
  }
#endif
  tmp = LL_SPI_ReceiveData8(_SPI);
  if (rx != NULL) *rx = (uint8_t)tmp;

  if ((SPI_TRANSFER_TIMEOUT != HAL_MAX_DELAY) &&
      (HAL_GetTick() - tickstart >= SPI_TRANSFER_TIMEOUT)) {
    core_debug("SPI Transfer timed out\n");
    return (SPI_TIMEOUT);
  }

  return ret;
}



#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
