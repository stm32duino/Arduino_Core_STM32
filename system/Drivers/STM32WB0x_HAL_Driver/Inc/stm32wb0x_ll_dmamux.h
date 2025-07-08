/**
  ******************************************************************************
  * @file    stm32wb0x_ll_dmamux.h
  * @author  MCD Application Team
  * @brief   Header file of DMAMUX LL module.
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
#ifndef STM32WB0x_LL_DMAMUX_H
#define STM32WB0x_LL_DMAMUX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (DMAMUX1)

/** @defgroup DMAMUX_LL DMAMUX
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DMAMUX_LL_Private_Constants DMAMUX Private Constants
  * @{
  */
/* Define used to get DMAMUX CCR register size */
#define DMAMUX_CCR_SIZE                   0x00000004UL
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup DMAMUX_LL_Exported_Constants DMAMUX Exported Constants
  * @{
  */

/** @defgroup DMAMUX_LL_EC_REQUEST Transfer request
  * @{
  */
#define LL_DMAMUX_REQ_MEM2MEM            0x00000000U  /*!< Memory to Memory transfer    */
#ifdef SPI3
#define LL_DMAMUX_REQ_SPI3_RX            0x00000002U  /*!< DMAMUX SPI3 RX request       */
#define LL_DMAMUX_REQ_SPI3_TX            0x00000003U  /*!< DMAMUX SPI3 TX request       */
#endif /* SPI3 */
#ifdef SPI1
#define LL_DMAMUX_REQ_SPI1_RX            0x00000004U  /*!< DMAMUX SPI1 RX request       */
#define LL_DMAMUX_REQ_SPI1_TX            0x00000005U  /*!< DMAMUX SPI1 TX request       */
#endif /* SPI1 */
#ifdef SPI2
#define LL_DMAMUX_REQ_SPI2_RX            0x00000006U  /*!< DMAMUX SPI2 RX request       */
#define LL_DMAMUX_REQ_SPI2_TX            0x00000007U  /*!< DMAMUX SPI2 TX request       */
#endif /* SPI2 */
#ifdef I2C1
#define LL_DMAMUX_REQ_I2C1_RX            0x00000008U  /*!< DMAMUX I2C1 RX request       */
#define LL_DMAMUX_REQ_I2C1_TX            0x00000009U  /*!< DMAMUX I2C1 TX request       */
#endif /* I2C1 */
#ifdef I2C2
#define LL_DMAMUX_REQ_I2C2_RX            0x0000000AU  /*!< DMAMUX I2C2 RX request       */
#define LL_DMAMUX_REQ_I2C2_TX            0x0000000BU  /*!< DMAMUX I2C2 TX request       */
#endif /* I2C2 */
#define LL_DMAMUX_REQ_USART1_RX          0x0000000CU  /*!< DMAMUX USART1 RX request     */
#define LL_DMAMUX_REQ_USART1_TX          0x0000000DU  /*!< DMAMUX USART1 TX request     */
#define LL_DMAMUX_REQ_LPUART1_RX         0x0000000EU  /*!< DMAMUX LPUART1 RX request    */
#define LL_DMAMUX_REQ_LPUART1_TX         0x0000000FU  /*!< DMAMUX LPUART1 TX request    */
#define LL_DMAMUX_REQ_ADC1_DS             0x00000010U  /*!< DMAMUX ADC DS output request */
#ifdef ADC_DF_DATAOUT_DF_DATA
#define LL_DMAMUX_REQ_ADC1_DF             0x00000011U  /*!< DMAMUX ADC DF output request */
#endif /* ADC_DF_DATAOUT_DF_DATA */
#ifdef TIM2
#define LL_DMAMUX_REQ_TIM2_CH1           0x00000012U  /*!< DMAMUX TIM2 CH1 request */
#define LL_DMAMUX_REQ_TIM2_CH2           0x00000013U  /*!< DMAMUX TIM2 CH3 request */
#define LL_DMAMUX_REQ_TIM2_CH3           0x00000014U  /*!< DMAMUX TIM2 CH3 request */
#define LL_DMAMUX_REQ_TIM2_CH4           0x00000015U  /*!< DMAMUX TIM2 CH4 request */
#define LL_DMAMUX_REQ_TIM2_UP            0x00000016U  /*!< DMAMUX TIM2 UP request */
#endif /* TIM2 */
#ifdef TIM16
#define LL_DMAMUX_REQ_TIM16_CH1          0x00000017U  /*!< DMAMUX TIM16 CH1 request */
#define LL_DMAMUX_REQ_TIM16_UP           0x00000018U  /*!< DMAMUX TIM16 UP request */
#endif /* TIM16 */
#ifdef TIM17
#define LL_DMAMUX_REQ_TIM17_CH1          0x00000019U  /*!< DMAMUX TIM17 CH1 request */
#define LL_DMAMUX_REQ_TIM17_UP           0x0000001AU  /*!< DMAMUX TIM17 UP request */
#endif /* TIM17 */


#if defined(STM32WB06) || defined(STM32WB07)
#define LL_DMAMUX_MAX_REQ                 LL_DMAMUX_REQ_ADC1_DF
#endif
#if defined (STM32WB05) || defined(STM32WB09)
#define LL_DMAMUX_MAX_REQ                 LL_DMAMUX_REQ_TIM17_UP
#endif
/**
  * @}
  */

/** @defgroup DMAMUX_LL_EC_CHANNEL DMAMUX Channel
  * @{
  */
#define LL_DMAMUX_CHANNEL_0               0x00000000U               /*!< DMAMUX Channel 0 connected to DMA1 Channel 1  */
#define LL_DMAMUX_CHANNEL_1               0x00000001U               /*!< DMAMUX Channel 1 connected to DMA1 Channel 2  */
#define LL_DMAMUX_CHANNEL_2               0x00000002U               /*!< DMAMUX Channel 2 connected to DMA1 Channel 3  */
#define LL_DMAMUX_CHANNEL_3               0x00000003U               /*!< DMAMUX Channel 3 connected to DMA1 Channel 4  */
#define LL_DMAMUX_CHANNEL_4               0x00000004U               /*!< DMAMUX Channel 4 connected to DMA1 Channel 5  */
#define LL_DMAMUX_CHANNEL_5               0x00000005U               /*!< DMAMUX Channel 5 connected to DMA1 Channel 6  */
#define LL_DMAMUX_CHANNEL_6               0x00000006U               /*!< DMAMUX Channel 6 connected to DMA1 Channel 7  */
#define LL_DMAMUX_CHANNEL_7               0x00000007U               /*!< DMAMUX Channel 7 connected to DMA1 Channel 8  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMAMUX_LL_Exported_Macros DMAMUX Exported Macros
  * @{
  */

/** @defgroup DMAMUX_LL_EM_WRITE_READ Common Write and read registers macros
  * @{
  */
/**
  * @brief  Write a value in DMAMUX register
  * @param  __INSTANCE__ DMAMUX Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DMAMUX_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DMAMUX register
  * @param  __INSTANCE__ DMAMUX Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DMAMUX_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DMAMUX_LL_Exported_Functions DMAMUX Exported Functions
 * @{
 */

/** @defgroup DMAMUX_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief  Set DMAMUX request ID for DMAMUX Channel x.
  * @note   DMAMUX channel 0 to 7 are mapped to DMA1 channel 1 to 8.
  * @rmtoll CxCR         DMAREQ_ID     LL_DMAMUX_SetRequestID
  * @param  DMAMUXx DMAMUXx Instance
  * @param  Channel This parameter can be one of the following values:
  * @arg LL_DMAMUX_CHANNEL_0
  * @arg LL_DMAMUX_CHANNEL_1
  * @arg LL_DMAMUX_CHANNEL_2
  * @arg LL_DMAMUX_CHANNEL_3
  * @arg LL_DMAMUX_CHANNEL_4
  * @arg LL_DMAMUX_CHANNEL_5
  * @arg LL_DMAMUX_CHANNEL_6
  * @arg LL_DMAMUX_CHANNEL_7
  * @param  Request This parameter can be one of the following values:
  * @arg LL_DMAMUX_REQ_MEM2MEM
  * @arg LL_DMAMUX_REQ_SPI3_RX
  * @arg LL_DMAMUX_REQ_SPI3_TX
  * @arg LL_DMAMUX_REQ_SPI1_RX
  * @arg LL_DMAMUX_REQ_SPI1_TX
  * @arg LL_DMAMUX_REQ_SPI2_RX
  * @arg LL_DMAMUX_REQ_SPI2_TX
  * @arg LL_DMAMUX_REQ_I2C1_RX
  * @arg LL_DMAMUX_REQ_I2C1_TX
  * @arg LL_DMAMUX_REQ_I2C2_RX
  * @arg LL_DMAMUX_REQ_I2C2_TX
  * @arg LL_DMAMUX_REQ_USART1_RX
  * @arg LL_DMAMUX_REQ_USART1_TX
  * @arg LL_DMAMUX_REQ_LPUART1_RX
  * @arg LL_DMAMUX_REQ_LPUART1_TX
  * @arg LL_DMAMUX_REQ_ADC1_DS
  * @arg LL_DMAMUX_REQ_ADC1_DF
  * @retval None
  */
__STATIC_INLINE void LL_DMAMUX_SetRequestID(DMAMUX_Channel_TypeDef* DMAMUXx, uint32_t Channel, uint32_t Request)
{
  (void)(DMAMUXx);
  MODIFY_REG((DMAMUX1_Channel0 + Channel)->CxCR, DMAMUX_CxCR_DMAREQ_ID, Request);
}

/**
  * @brief  Get DMAMUX request ID for DMAMUX Channel x.
  * @note   DMAMUX channel 0 to 7 are mapped to DMA1 channel 1 to 8.
  * @rmtoll CxCR         DMAREQ_ID     LL_DMAMUX_GetRequestID
  * @param  DMAMUXx DMAMUXx Instance
  * @param  Channel This parameter can be one of the following values:
  * @arg LL_DMAMUX_CHANNEL_0
  * @arg LL_DMAMUX_CHANNEL_1
  * @arg LL_DMAMUX_CHANNEL_2
  * @arg LL_DMAMUX_CHANNEL_3
  * @arg LL_DMAMUX_CHANNEL_4
  * @arg LL_DMAMUX_CHANNEL_5
  * @arg LL_DMAMUX_CHANNEL_6
  * @arg LL_DMAMUX_CHANNEL_7
  * @retval Returned value can be one of the following values:
  * @arg LL_DMAMUX_REQ_MEM2MEM
  * @arg LL_DMAMUX_REQ_SPI3_RX
  * @arg LL_DMAMUX_REQ_SPI3_TX
  * @arg LL_DMAMUX_REQ_SPI1_RX
  * @arg LL_DMAMUX_REQ_SPI1_TX
  * @arg LL_DMAMUX_REQ_SPI2_RX
  * @arg LL_DMAMUX_REQ_SPI2_TX
  * @arg LL_DMAMUX_REQ_I2C1_RX
  * @arg LL_DMAMUX_REQ_I2C1_TX
  * @arg LL_DMAMUX_REQ_I2C2_RX
  * @arg LL_DMAMUX_REQ_I2C2_TX
  * @arg LL_DMAMUX_REQ_USART1_RX
  * @arg LL_DMAMUX_REQ_USART1_TX
  * @arg LL_DMAMUX_REQ_LPUART1_RX
  * @arg LL_DMAMUX_REQ_LPUART1_TX
  * @arg LL_DMAMUX_REQ_ADC1_DS
  * @arg LL_DMAMUX_REQ_ADC1_DF
  */
__STATIC_INLINE uint32_t LL_DMAMUX_GetRequestID(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t Channel)
{
  (void)(DMAMUXx);
  return (uint32_t)(READ_BIT((DMAMUX1_Channel0 + Channel)->CxCR, DMAMUX_CxCR_DMAREQ_ID));
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

#endif /* DMAMUX1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WB0x_LL_DMAMUX_H */
