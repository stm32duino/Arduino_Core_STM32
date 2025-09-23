/**
  ******************************************************************************
  * @file    stm32wl3x_hal_dac_ex.c
  * @author  MCD Application Team
  * @brief   Extended DAC HAL module driver.
  *          This file provides firmware functions to manage the extended
  *          functionalities of the DAC peripheral.
  *
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                      ##### How to use this driver #####
  ==============================================================================
    [..]
     *** Signal generation operation ***
     ===================================
     [..]
      (+) Use HAL_DACEx_TriangleWaveGenerate() to generate Triangle signal.
      (+) Use HAL_DACEx_NoiseWaveGenerate() to generate Noise signal.

 @endverbatim
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

#ifdef HAL_DAC_MODULE_ENABLED

#if defined(DAC1)

/** @defgroup DACEx DACEx
  * @brief DAC Extended HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup DACEx_Exported_Functions DACEx Exported Functions
  * @{
  */

/** @defgroup DACEx_Exported_Functions_Group2 IO operation functions
  *  @brief    Extended IO operation functions
  *
@verbatim
  ==============================================================================
                 ##### Extended features functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable DMA transfer.
      (+) Get result of conversion.
      (+) Get result of dual mode conversion.

@endverbatim
  * @{
  */

/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @param  Amplitude Select max triangle amplitude.
  *          This parameter can be one of the following values:
  *            @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
  *            @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
  *            @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
  *            @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
  *            @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
  *            @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
  /* Check the DAC peripheral handle */
  if (hdac == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the triangle wave generation for the selected DAC channel */
  MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE) | (DAC_CR_MAMP)) << (Channel & 0x10UL),
             (DAC_CR_WAVE_1 | Amplitude) << (Channel & 0x10UL));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @param  Amplitude Unmask DAC channel LFSR for noise wave generation.
  *          This parameter can be one of the following values:
  *            @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
  /* Check the DAC peripheral handle */
  if (hdac == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the noise wave generation for the selected DAC channel */
  MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE) | (DAC_CR_MAMP)) << (Channel & 0x10UL),
             (DAC_CR_WAVE_0 | Amplitude) << (Channel & 0x10UL));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}


/**
  * @}
  */

/**
  * @brief Enable the VCM Buffer output
  * @param hdac pointer to a DAC_HandleTypeDef structure that contains
  *        the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_EnableVCMBuffer(DAC_HandleTypeDef *hdac)
{
  /* Check the DAC peripheral handle */
  if (hdac == NULL)
  {
    return HAL_ERROR;
  }

  if (hdac->State == HAL_DAC_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hdac);

    hdac->State = HAL_DAC_STATE_BUSY;

    SET_BIT(hdac->Instance->CR, (DAC_CR_VCMON | DAC_CR_VCMEN));

    /* Update the DAC state */
    hdac->State = HAL_DAC_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hdac);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Disable the VCM Buffer output
  * @param hdac pointer to a DAC_HandleTypeDef structure that contains
  *        the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_DisableVCMBuffer(DAC_HandleTypeDef *hdac)
{
  /* Check the DAC peripheral handle */
  if (hdac == NULL)
  {
    return HAL_ERROR;
  }

  if (hdac->State == HAL_DAC_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hdac);

    hdac->State = HAL_DAC_STATE_BUSY;

    CLEAR_BIT(hdac->Instance->CR, (DAC_CR_VCMON | DAC_CR_VCMEN));

    /* Update the DAC state */
    hdac->State = HAL_DAC_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hdac);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* DAC1 */

#endif /* HAL_DAC_MODULE_ENABLED */

/**
  * @}
  */
