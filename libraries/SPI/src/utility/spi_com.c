/**
  ******************************************************************************
  * @file    spi_com.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide the SPI interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
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

#if defined(STM32F0xx) || defined(STM32G0xx)
  UNUSED(spi_inst);
  /* SPIx source CLK is PCKL1 */
  spi_freq = HAL_RCC_GetPCLK1Freq();
#elif defined(STM32MP1xx)
  /* Get source clock depending on SPI instance */
  if (spi_inst != NP) {
    switch ((uint32_t)spi_inst) {
      case (uint32_t)SPI1:
        spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI1);
        break;
      case (uint32_t)SPI2:
      case (uint32_t)SPI3:
        spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI23);
        break;
      case (uint32_t)SPI4:
      case (uint32_t)SPI5:
        spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI45);
        break;
      case (uint32_t)SPI6:
        spi_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI6);
        break;
      default:
        core_debug("CLK: SPI instance not set");
        break;
    }
  }
#else
  if (spi_inst != NP) {
    /* Get source clock depending on SPI instance */
    switch ((uint32_t)spi_inst) {
#if defined(SPI1_BASE) || defined(SPI4_BASE) || defined(SPI5_BASE) || defined(SPI6_BASE)
        /* Some STM32's (eg. STM32F302x8) have no SPI1, but do have SPI2/3. */
#if defined SPI1_BASE
      case (uint32_t)SPI1:
#endif
#if defined SPI4_BASE
      case (uint32_t)SPI4:
#endif
#if defined SPI5_BASE
      case (uint32_t)SPI5:
#endif
#if defined SPI6_BASE
      case (uint32_t)SPI6:
#endif
        /* SPI1, SPI4, SPI5 and SPI6. Source CLK is PCKL2 */
        spi_freq = HAL_RCC_GetPCLK2Freq();
        break;
#endif  /* SPI[1456]_BASE */

#if defined(SPI2_BASE) || defined (SPI3_BASE)
#if defined SPI2_BASE
      case (uint32_t)SPI2:
#endif
#if defined SPI3_BASE
      case (uint32_t)SPI3:
#endif
        /* SPI_2 and SPI_3. Source CLK is PCKL1 */
        spi_freq = HAL_RCC_GetPCLK1Freq();
        break;
#endif
      default:
        core_debug("CLK: SPI instance not set");
        break;
    }
  }
#endif
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
    spi_inst = pinmap_peripheral(obj->pin_sclk, PinMap_SPI_SCLK);

    if (spi_inst != NP) {
      spi_freq = spi_getClkFreqInst(spi_inst);
    }
  }
  return spi_freq;
}

/**
  * @brief  SPI initialization function
  * @param  obj : pointer to spi_t structure
  * @param  speed : spi output speed
  * @param  mode : one of the spi modes
  * @param  msb : set to 1 in msb first
  * @retval None
  */
void spi_init(spi_t *obj, uint32_t speed, spi_mode_e mode, uint8_t msb)
{
  if (obj == NULL) {
    return;
  }

  SPI_HandleTypeDef *handle = &(obj->handle);
  uint32_t spi_freq = 0;
  uint32_t pull = 0;

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

  handle->Init.Direction         = SPI_DIRECTION_2LINES;

  if ((mode == SPI_MODE_0) || (mode == SPI_MODE_2)) {
    handle->Init.CLKPhase          = SPI_PHASE_1EDGE;
  } else {
    handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  }

  if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1)) {
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
#if defined(STM32F0xx) || defined(STM32F3xx) || defined(STM32F7xx) ||\
    defined(STM32G0xx) || defined(STM32H7xx) || defined(STM32L4xx) ||\
    defined(STM32WBxx) || defined(STM32MP1xx)
  handle->Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
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

#if defined SPI1_BASE
  // Enable SPI clock
  if (handle->Instance == SPI1) {
    __HAL_RCC_SPI1_CLK_ENABLE();
  }
#endif

#if defined SPI2_BASE
  if (handle->Instance == SPI2) {
    __HAL_RCC_SPI2_CLK_ENABLE();
  }
#endif

#if defined SPI3_BASE
  if (handle->Instance == SPI3) {
    __HAL_RCC_SPI3_CLK_ENABLE();
  }
#endif

#if defined SPI4_BASE
  if (handle->Instance == SPI4) {
    __HAL_RCC_SPI4_CLK_ENABLE();
  }
#endif

#if defined SPI5_BASE
  if (handle->Instance == SPI5) {
    __HAL_RCC_SPI5_CLK_ENABLE();
  }
#endif

#if defined SPI6_BASE
  if (handle->Instance == SPI6) {
    __HAL_RCC_SPI6_CLK_ENABLE();
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
}

/**
  * @brief This function is implemented by user to send data over SPI interface
  * @param  obj : pointer to spi_t structure
  * @param  Data : data to be sent
  * @param  len : length in bytes of the data to be sent
  * @param  Timeout: Timeout duration in tick
  * @retval status of the send operation (0) in case of error
  */
spi_status_e spi_send(spi_t *obj, uint8_t *Data, uint16_t len, uint32_t Timeout)
{
  return spi_transfer(obj, Data, Data, len, Timeout, 1 /* SPI_TRANSMITONLY */);
}

/**
  * @brief This function is implemented by user to send/receive data over
  *         SPI interface
  * @param  obj : pointer to spi_t structure
  * @param  tx_buffer : tx data to send before reception
  * @param  rx_buffer : data to receive
  * @param  len : length in byte of the data to send and receive
  * @param  Timeout: Timeout duration in tick
  * @param  skipReceive: skip receiving data after transmit or not
  * @retval status of the send operation (0) in case of error
  */
spi_status_e spi_transfer(spi_t *obj, uint8_t *tx_buffer, uint8_t *rx_buffer,
                          uint16_t len, uint32_t Timeout, bool skipReceive)
{
  spi_status_e ret = SPI_OK;
  uint32_t tickstart, size = len;
  SPI_TypeDef *_SPI = obj->handle.Instance;

  if ((obj == NULL) || (len == 0) || (Timeout == 0U)) {
    return Timeout > 0U ? SPI_ERROR : SPI_TIMEOUT;
  }
  tickstart = HAL_GetTick();

#if defined(STM32H7xx) || defined(STM32MP1xx)
  /* Start transfer */
  LL_SPI_SetTransferSize(_SPI, size);
  LL_SPI_Enable(_SPI);
  LL_SPI_StartMasterTransfer(_SPI);
#endif

  while (size--) {
#if defined(STM32H7xx) || defined(STM32MP1xx)
    while (!LL_SPI_IsActiveFlag_TXP(_SPI));
#else
    while (!LL_SPI_IsActiveFlag_TXE(_SPI));
#endif
    LL_SPI_TransmitData8(_SPI, *tx_buffer++);

    if (!skipReceive) {
#if defined(STM32H7xx) || defined(STM32MP1xx)
      while (!LL_SPI_IsActiveFlag_RXP(_SPI));
#else
      while (!LL_SPI_IsActiveFlag_RXNE(_SPI));
#endif
      *rx_buffer++ = LL_SPI_ReceiveData8(_SPI);
    }
    if ((Timeout != HAL_MAX_DELAY) && (HAL_GetTick() - tickstart >= Timeout)) {
      ret = SPI_TIMEOUT;
      break;
    }
  }

#if defined(STM32H7xx) || defined(STM32MP1xx)
  /* Close transfer */
  /* Clear flags */
  LL_SPI_ClearFlag_EOT(_SPI);
  LL_SPI_ClearFlag_TXTF(_SPI);
  /* Disable SPI peripheral */
  LL_SPI_Disable(_SPI);
#endif

  return ret;
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
