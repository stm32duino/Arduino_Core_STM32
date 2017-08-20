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
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "stm32_def.h"
#include "hw_config.h"
#include "spi_com.h"
#include "PinAF_STM32F1.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Functions
  * @{
  */
/**
  * @brief  return clock freq of an SPI instance
  * @param  spi_inst : SPI instance
  * @retval clock freq of the instance else SystemCoreClock
  */
uint32_t spi_getClkFreqInst(SPI_TypeDef * spi_inst)
{
  uint32_t spi_freq = SystemCoreClock;

#ifdef STM32F0xx
  UNUSED(spi_inst);
  /* SPIx source CLK is PCKL1 */
  spi_freq = HAL_RCC_GetPCLK1Freq();
#else
  if(spi_inst != NP) {
    /* Get source clock depending on SPI instance */
    switch ((uint32_t)spi_inst) {
      case (uint32_t)SPI1:
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
        printf("CLK: SPI instance not set");
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

  if(obj != NULL) {
	spi_inst = pinmap_peripheral(obj->pin_sclk, PinMap_SPI_SCLK);

    if(spi_inst != NP) {
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
  if(obj == NULL)
    return;

  SPI_HandleTypeDef *handle = &(obj->handle);
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_TypeDef *port;
  uint32_t spi_freq = 0;

  // Determine the SPI to use
  SPI_TypeDef *spi_mosi = pinmap_peripheral(obj->pin_mosi, PinMap_SPI_MOSI);
  SPI_TypeDef *spi_miso = pinmap_peripheral(obj->pin_miso, PinMap_SPI_MISO);
  SPI_TypeDef *spi_sclk = pinmap_peripheral(obj->pin_sclk, PinMap_SPI_SCLK);
  SPI_TypeDef *spi_ssel = pinmap_peripheral(obj->pin_ssel, PinMap_SPI_SSEL);

  /* Pins MOSI/MISO/SCLK must not be NP. ssel can be NP. */
  if(spi_mosi == NP || spi_miso == NP || spi_sclk == NP) {
    return;
  }

  SPI_TypeDef *spi_data = pinmap_merge_peripheral(spi_mosi, spi_miso);
  SPI_TypeDef *spi_cntl = pinmap_merge_peripheral(spi_sclk, spi_ssel);

  obj->spi = pinmap_merge_peripheral(spi_data, spi_cntl);

  // Are all pins connected to the same SPI instance?
  if(obj->spi == NP) {
    printf("ERROR: SPI pins mismatch\n");
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
  if(speed >= (spi_freq/SPI_SPEED_CLOCK_DIV2_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  } else if(speed >= (spi_freq/SPI_SPEED_CLOCK_DIV4_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV8_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV16_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV32_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV64_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV128_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  } else if (speed >= (spi_freq/SPI_SPEED_CLOCK_DIV256_MHZ)) {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  } else {
    handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  }

  handle->Init.Direction         = SPI_DIRECTION_2LINES;

  if((mode == SPI_MODE_0)||(mode == SPI_MODE_2)) {
    handle->Init.CLKPhase          = SPI_PHASE_1EDGE;
  } else {
    handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  }

  if((mode == SPI_MODE_0)||(mode == SPI_MODE_1)) {
    handle->Init.CLKPolarity       = SPI_POLARITY_LOW;
  } else {
    handle->Init.CLKPolarity       = SPI_POLARITY_HIGH;
  }

  handle->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  handle->Init.CRCPolynomial     = 7;
  handle->Init.DataSize          = SPI_DATASIZE_8BIT;

  if(msb == 0) {
    handle->Init.FirstBit          = SPI_FIRSTBIT_LSB;
  } else {
    handle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  }

  handle->Init.TIMode            = SPI_TIMODE_DISABLE;

  if(obj->pin_mosi != NC) {
    port = set_GPIO_Port_Clock(STM_PORT(obj->pin_mosi));
    GPIO_InitStruct.Pin       = STM_GPIO_PIN(obj->pin_mosi);
    GPIO_InitStruct.Mode      = STM_PIN_MODE(pinmap_function(obj->pin_mosi,PinMap_SPI_MOSI));
    GPIO_InitStruct.Pull      = STM_PIN_PUPD(pinmap_function(obj->pin_mosi,PinMap_SPI_MOSI));
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
#ifdef STM32F1xx
    pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_mosi,PinMap_SPI_MOSI)));
#else
    GPIO_InitStruct.Alternate = STM_PIN_AFNUM(pinmap_function(obj->pin_mosi,PinMap_SPI_MOSI));
#endif /* STM32F1xx */
    HAL_GPIO_Init(port, &GPIO_InitStruct);
  }

  if(obj->pin_miso != NC) {
    port = set_GPIO_Port_Clock(STM_PORT(obj->pin_miso));
    GPIO_InitStruct.Pin       = STM_GPIO_PIN(obj->pin_miso);
    GPIO_InitStruct.Mode      = STM_PIN_MODE(pinmap_function(obj->pin_miso,PinMap_SPI_MISO));
    GPIO_InitStruct.Pull      = STM_PIN_PUPD(pinmap_function(obj->pin_miso,PinMap_SPI_MISO));
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
#ifdef STM32F1xx
    pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_miso,PinMap_SPI_MISO)));
#else
    GPIO_InitStruct.Alternate = STM_PIN_AFNUM(pinmap_function(obj->pin_miso,PinMap_SPI_MISO));
#endif /* STM32F1xx */
    HAL_GPIO_Init(port, &GPIO_InitStruct);
  }

  if(obj->pin_sclk != NC) {
    port = set_GPIO_Port_Clock(STM_PORT(obj->pin_sclk));
    GPIO_InitStruct.Pin       = STM_GPIO_PIN(obj->pin_sclk);
    GPIO_InitStruct.Mode      = STM_PIN_MODE(pinmap_function(obj->pin_sclk,PinMap_SPI_SCLK));
    /*
     * According the STM32 Datasheet for SPI peripheral we need to PULLDOWN
     * or PULLUP the SCK pin according the polarity used.
     */
    if(handle->Init.CLKPolarity == SPI_POLARITY_LOW) {
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    } else {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
#ifdef STM32F1xx
    pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_sclk,PinMap_SPI_SCLK)));
#else
    GPIO_InitStruct.Alternate = STM_PIN_AFNUM(pinmap_function(obj->pin_sclk,PinMap_SPI_SCLK));
#endif /* STM32F1xx */
    HAL_GPIO_Init(port, &GPIO_InitStruct);
  }

  if(obj->pin_ssel != NC) {
    port = set_GPIO_Port_Clock(STM_PORT(obj->pin_ssel));
    GPIO_InitStruct.Pin       = STM_GPIO_PIN(obj->pin_ssel);
    GPIO_InitStruct.Mode      = STM_PIN_MODE(pinmap_function(obj->pin_ssel,PinMap_SPI_SSEL));
    GPIO_InitStruct.Pull      = STM_PIN_PUPD(pinmap_function(obj->pin_ssel,PinMap_SPI_SSEL));
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
#ifdef STM32F1xx
    pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_ssel,PinMap_SPI_SSEL)));
#else
    GPIO_InitStruct.Alternate = STM_PIN_AFNUM(pinmap_function(obj->pin_ssel,PinMap_SPI_SSEL));
#endif /* STM32F1xx */
    HAL_GPIO_Init(port, &GPIO_InitStruct);
  }

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
  if(obj == NULL)
    return;

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
  spi_status_e ret = SPI_OK;
  HAL_StatusTypeDef hal_status;

  if((obj == NULL) || (len == 0)) {
    return SPI_ERROR;
  }

  hal_status = HAL_SPI_Transmit(&(obj->handle), Data, len, Timeout);

  if(hal_status == HAL_TIMEOUT) {
    ret = SPI_TIMEOUT;
  } else if(hal_status != HAL_OK) {
    ret = SPI_ERROR;
  }

  return ret;
}

/**
  * @brief This function is implemented by user to send/receive data over
  *         SPI interface
  * @param  obj : pointer to spi_t structure
  * @param  tx_buffer : tx data to send before reception
  * @param  rx_buffer : data to receive
  * @param  len : length in byte of the data to send and receive
  * @param  Timeout: Timeout duration in tick
  * @retval status of the send operation (0) in case of error
  */
spi_status_e spi_transfer(spi_t *obj, uint8_t * tx_buffer,
                      uint8_t * rx_buffer, uint16_t len, uint32_t Timeout)
{
  spi_status_e ret = SPI_OK;
  HAL_StatusTypeDef hal_status;

  if((obj == NULL) || (len == 0)) {
    return SPI_ERROR;
  }

  hal_status = HAL_SPI_TransmitReceive(&(obj->handle), tx_buffer, rx_buffer, len, Timeout);

  if(hal_status == HAL_TIMEOUT) {
    ret = SPI_TIMEOUT;
  } else if(hal_status != HAL_OK) {
    ret = SPI_ERROR;
  }

  return ret;
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
