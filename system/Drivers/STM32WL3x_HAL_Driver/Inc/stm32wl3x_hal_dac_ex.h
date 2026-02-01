/**
  ******************************************************************************
  * @file    stm32wl3x_hal_dac_ex.h
  * @author  MCD Application Team
  * @brief   Header file of DAC HAL Extended module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WL3x_HAL_DAC_EX_H
#define STM32WL3x_HAL_DAC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

#if defined(DAC1)

/** @addtogroup DACEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  HAL State structures definition
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DACEx_Exported_Constants DACEx Exported Constants
  * @{
  */

/** @defgroup DACEx_lfsrunmask_triangleamplitude DACEx lfsrunmask triangle amplitude
  * @{
  */

#define DAC_LFSRUNMASK_BIT0                0x00000000UL                                                    /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUNMASK_BITS1_0             (                                                DAC_CR_MAMP_0) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS2_0             (                                DAC_CR_MAMP_1                ) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS3_0             (                                DAC_CR_MAMP_1 | DAC_CR_MAMP_0) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS4_0             (                DAC_CR_MAMP_2                                ) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS5_0             (                DAC_CR_MAMP_2                 | DAC_CR_MAMP_0) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */

#define DAC_TRIANGLEAMPLITUDE_1            0x00000000UL                                                    /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLEAMPLITUDE_3            (                                                DAC_CR_MAMP_0) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLEAMPLITUDE_7            (                                DAC_CR_MAMP_1                ) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLEAMPLITUDE_15           (                                DAC_CR_MAMP_1 | DAC_CR_MAMP_0) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLEAMPLITUDE_31           (                DAC_CR_MAMP_2                                ) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLEAMPLITUDE_63           (                DAC_CR_MAMP_2                 | DAC_CR_MAMP_0) /*!< Select max triangle amplitude of 63 */

/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/** @defgroup DACEx_Private_Macros DACEx Private Macros
  * @{
  */
#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_TRIGGER_NONE)       || \
                                 ((TRIGGER) == DAC_TRIGGER_SOFTWARE)   || \
                                 ((TRIGGER) == DAC_TRIGGER_T16_TRGO)   || \
                                 ((TRIGGER) == DAC_TRIGGER_EXT_IT8))

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUNMASK_BIT0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS1_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS2_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS3_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS4_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS5_0) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_1) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_3) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_15) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_31) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_63))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/* Extended features functions ************************************************/

/** @addtogroup DACEx_Exported_Functions
  * @{
  */

/** @addtogroup DACEx_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/

HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);


/**
  * @}
  */

/* VCM Buffer Control functions  **********************************************/
HAL_StatusTypeDef HAL_DACEx_EnableVCMBuffer(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_DisableVCMBuffer(DAC_HandleTypeDef *hdac);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* DAC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_HAL_DAC_EX_H */
