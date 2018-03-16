/**
  ******************************************************************************
  * @file    hal_uart_emul.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Adaptation from stm32f4xx_hal_uart_emul.h
  *          Header file of UART Emulation HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_UART_EMUL_H
#define __HAL_UART_EMUL_H

#if defined(TIM1_BASE) && defined(UART_EMUL_RX) && defined(UART_EMUL_TX)
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup UART_EMUL_HAL_Driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief UART Emulation Init Structure definition
  */
typedef struct
{
  uint8_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Emul_Mode */

  uint32_t BaudRate;                 /*!< This member configures the UART communication baud rate.*/


  uint8_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Emul_Word_Length */

  uint8_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Emul_Stop_Bits */


  uint8_t Parity;                   /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Emul_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data*/

  uint16_t RxPinNumber;             /*!< Specifies the number of Receiver Pin.
	                                         This parameter can be a value of @ref GPIO_pins_define */

   uint16_t TxPinNumber;            /*!< Specifies the number of Transmitter Pin.
	                                         his parameter can be a value of @ref GPIO_pins_define */
}UART_Emul_InitTypeDef;

/**
  * @brief HAL UART Emulation State structures definition
  */
typedef enum
{
  HAL_UART_EMUL_STATE_RESET             = 0x00,    /*!< Peripheral is not yet Initialized                  */
  HAL_UART_EMUL_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use           */
  HAL_UART_EMUL_STATE_BUSY              = 0x02,    /*!< An internal process is ongoing                     */
  HAL_UART_EMUL_STATE_BUSY_TX           = 0x04,    /*!< Data Transmission process is ongoing               */
  HAL_UART_EMUL_STATE_BUSY_RX           = 0x08,    /*!< Data Reception process is ongoing                  */
  HAL_UART_EMUL_STATE_BUSY_TX_RX        = 0x10,    /*!< Data Transmission and Reception process is ongoing */
  HAL_UART_EMUL_STATE_ERROR             = 0x20     /*!< Error                                              */

}HAL_UART_Emul_StateTypeDef;

/**
  * @brief  HAL UART Emulation Error Code structure definition
  */
typedef enum
{
  HAL_UART_EMUL_ERROR_NONE      = 0x00,    /*!< No error            */
  HAL_UART_EMUL_ERROR_FE        = 0x01,    /*!< frame error         */
  HAL_UART_EMUL_ERROR_RE        = 0x02,    /*!< receiver error      */
  HAL_UART_EMUL_ERROR_PE        = 0x04     /*!< transfer error      */
}HAL_UART_Emul_ErrorTypeDef;

/**
  * @brief Universal Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint8_t SR;         /*!< UART Emulation Status register software        */

} UART_Emul_TypeDef;

/**
  * @brief  UART Emulation handle Structure definition
  */
typedef struct
{
  UART_Emul_TypeDef                Instance;         /* Instance for UART Emulation register         */

  UART_Emul_InitTypeDef            Init;             /* UART Emulation communication parameters      */

  uint8_t                          *pTxBuffPtr;      /* Pointer to UART Emulation Tx transfer Buffer */

  uint16_t                         TxXferSize;       /* UART Emulation Tx Transfer size              */

  uint16_t                         TxXferCount;      /* UART Emulation Tx Transfer Counter           */

  uint8_t                          *pRxBuffPtr;      /* Pointer to UART Emulation Rx transfer Buffer */

  uint16_t                         RxXferSize;       /* UART Emulation Rx Transfer size              */

  uint16_t                         RxXferCount;      /* UART Emulation Rx Transfer Counter           */

  GPIO_TypeDef                     *RxPortName;      /* UART Emulation Rx port name                  */

  GPIO_TypeDef                     *TxPortName;      /* UART Emulation Tx port name                  */

  __IO HAL_UART_Emul_StateTypeDef  State;            /* UART Emulation communication state           */

  __IO HAL_UART_Emul_ErrorTypeDef  ErrorCode;        /* UART  Emulation Error code                   */

}UART_Emul_HandleTypeDef;



/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Emulation_Exported_Constants
  * @{
  */

/** @defgroup UART_Emul_Word_Length
  * @{
  */

#define UART_EMUL_WORDLENGTH_5B                  ((uint8_t)0x05)
#define UART_EMUL_WORDLENGTH_6B                  ((uint8_t)0x06)
#define UART_EMUL_WORDLENGTH_7B                  ((uint8_t)0x07)
#define UART_EMUL_WORDLENGTH_8B                  ((uint8_t)0x08)
#define UART_EMUL_WORDLENGTH_9B                  ((uint8_t)0x09)
#define IS_UART_EMUL_WORD_LENGTH(LENGTH) (((LENGTH) == UART_EMUL_WORDLENGTH_5B)||\
                                          ((LENGTH) == UART_EMUL_WORDLENGTH_6B)||\
                                          ((LENGTH) == UART_EMUL_WORDLENGTH_7B)||\
                                          ((LENGTH) == UART_EMUL_WORDLENGTH_8B)||\
                                          ((LENGTH) == UART_EMUL_WORDLENGTH_9B))
/**
  * @}
  */

/** @defgroup UART_Emul_Stop_Bits
  * @{
  */
#define UART_EMUL_STOPBITS_1                     ((uint8_t)0x01)
#define UART_EMUL_STOPBITS_2                     ((uint8_t)0x02)
#define IS_UART_EMUL_STOPBITS(STOPBITS) (((STOPBITS) == UART_EMUL_STOPBITS_1)||\
                                         ((STOPBITS) == UART_EMUL_STOPBITS_2))

/**
  * @}
  */

/** @defgroup UART_Emul_Parity
  * @{
  */
#define UART_EMUL_PARITY_NONE                    ((uint8_t)0x00)
#define UART_EMUL_PARITY_EVEN                    ((uint8_t)0x01)
#define UART_EMUL_PARITY_ODD                     ((uint8_t)0x02)
#define IS_UART_EMUL_PARITY(PARITY)       (((PARITY) == UART_EMUL_PARITY_NONE) || \
                                           ((PARITY) == UART_EMUL_PARITY_EVEN) || \
                                           ((PARITY) == UART_EMUL_PARITY_ODD))
/**
  * @}
  */

/** @defgroup UART_Emul_Mode
  * @{
  */
#define UART_EMUL_MODE_RX                        ((uint8_t)0x01)
#define UART_EMUL_MODE_TX                        ((uint8_t)0x02)
#define UART_EMUL_MODE_TX_RX                     ((uint8_t)0x03)
#define IS_UART_EMUL_MODE(MODE)           (((MODE) == UART_EMUL_MODE_RX) || \
																					((MODE) == UART_EMUL_MODE_TX ) || \
																					((MODE) == UART_EMUL_MODE_TX_RX ))
/**
  * @}
  */

/** @defgroup UART_Emul_Flags
  *        Elements values convention: 0xXX
  *           - 0xXX  : Flag mask in the SR register software
  * @{
  */
#define UART_EMUL_FLAG_RC                        ((uint8_t)0x01)
#define UART_EMUL_FLAG_TC                        ((uint8_t)0x02)
#define UART_EMUL_FLAG_FE                        ((uint8_t)0x04)
#define UART_EMUL_FLAG_PE                        ((uint8_t)0x08)

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup Baudrate_Constants
  * @{
  */

/**
  *
  */
#define BAUDRATE_4800                  ((uint32_t)0x12C0)  /* Baudrate Selection 4800   */
#define BAUDRATE_9600                  ((uint32_t)0x2580)  /* Baudrate Selection 9600   */
#define BAUDRATE_14400                 ((uint32_t)0x3840)  /* Baudrate Selection 14400  */
#define BAUDRATE_19200                 ((uint32_t)0x4b00)  /* Baudrate Selection 19200  */
#define BAUDRATE_38400                 ((uint32_t)0x9600)  /* Baudrate Selection 38400  */
#define BAUDRATE_57600                 ((uint32_t)0xE100)  /* Baudrate Selection 57600  */
#define BAUDRATE_115200                ((uint32_t)0x1C200) /* Baudrate Selection 115200 */
#define IS_UART_EMUL_BAUDRATE(BaudRate)     (((BaudRate) == BAUDRATE_4800  )  || \
																						 ((BaudRate) == BAUDRATE_9600  )  || \
																						 ((BaudRate) == BAUDRATE_14400 )  || \
																						 ((BaudRate) == BAUDRATE_19200 )  || \
																						 ((BaudRate) == BAUDRATE_38400 )  || \
																						 ((BaudRate) == BAUDRATE_57600 )  || \
																						 ((BaudRate) == BAUDRATE_115200))
/**
  * @}
  */

 /** @defgroup UART Emulation constant
  * @{
  */

#define FIRST_BYTE        ((uint8_t)0x01)
#define BitMask           ((uint8_t)0x01)
#define RX_BUFFER_SIZE    ((uint8_t)0x0C)
#define TX_BUFFER_SIZE    ((uint8_t)0x0C)

/* Definition Handler for UART Emulation receive mode */

#ifdef STM32F0xx
#define UART_EMUL_TX_DMA_IRQHandler     DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#define UART_EMUL_RX_DMA_IRQHandler     DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler

#define UART_EMUL_TX_DMA_IRQn           DMA1_Ch2_3_DMA2_Ch1_2_IRQn
#define UART_EMUL_RX_DMA_IRQn           DMA1_Ch4_7_DMA2_Ch3_5_IRQn
#elif defined(STM32F3xx)
#define UART_EMUL_TX_DMA_IRQHandler     DMA2_Channel1_IRQHandler
#define UART_EMUL_RX_DMA_IRQHandler     DMA2_Channel3_IRQHandler

#define UART_EMUL_TX_DMA_IRQn           DMA2_Channel1_IRQn
#define UART_EMUL_RX_DMA_IRQn           DMA2_Channel3_IRQn
#elif defined(STM32F4xx)
#define UART_EMUL_TX_DMA_IRQHandler     DMA2_Stream1_IRQHandler
#define UART_EMUL_RX_DMA_IRQHandler     DMA2_Stream2_IRQHandler

#define UART_EMUL_TX_DMA_IRQn           DMA2_Stream1_IRQn
#define UART_EMUL_RX_DMA_IRQn           DMA2_Stream2_IRQn
#endif

/* Defenition of UART Emulation timer */
#define UART_EMUL_TX_TIMER_INSTANCE     TIM1
#define UART_EMUL_RX_TIMER_INSTANCE     TIM1

#define TIM_DMA_Handle_Tx TIM_DMA_ID_CC1
#define TIM_DMA_Handle_Rx TIM_DMA_ID_CC2

#define TIM_Channel_Tx    TIM_CHANNEL_1
#define TIM_Channel_Rx    TIM_CHANNEL_2

#define TIM_DMA_source_Tx TIM_DMA_CC1
#define TIM_DMA_source_Rx TIM_DMA_CC2

#ifdef STM32F4xx
#define DMA_Channel_Tx    DMA_CHANNEL_6
#define DMA_Channel_Rx    DMA_CHANNEL_6
#endif

#ifdef DMA2_Stream1
#define DMA_Stream_Tx     DMA2_Stream1
#define DMA_Stream_Rx     DMA2_Stream2
#else
#define DMA_Stream_Tx     DMA2_Channel1
#define DMA_Stream_Rx     DMA2_Channel3
#endif
/* Exported macro ------------------------------------------------------------*/

/** @brief  Checks whether the specified UART Emulation flag is set or not.
  * @param  __HANDLE__: specifies the UART Emulation Handle.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg UART_EMUL_FLAG_RC:  Receiver Complete flag
  *            @arg UART_EMUL_FLAG_TC:  Transmission Complete flag
  *            @arg UART_EMUL_FLAG_FE:  Framing Error flag
	*            @arg UART_EMUL_FLAG_PE:  Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_UART_EMUL_GET_FLAG(__HANDLE__, __FLAG__)  (((__HANDLE__)->Instance.SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clears the specified UART Emulation  flag.
  * @param  __HANDLE__: specifies the UART Emulation Handle.
  *
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg UART_EMUL_FLAG_RC :  Receiver Complet.
  *            @arg UART_EMUL_FLAG_TC :  Transmitter Complet.
  *            @arg UART_EMUL_FLAG_FE :  Frame Error.
  *            @arg UART_EMUL_FLAG_PE :  Parity Error.
  *
  * @retval None
  */
#define __HAL_UART_EMUL_CLEAR_FLAG(__HANDLE__, __FLAG__)  ((__HANDLE__)->Instance.SR &= ~(__FLAG__))

/** @brief  Set the specified UART Emulation  flag.
  * @param  __HANDLE__: specifies the UART Emulation Handle.
  *
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg UART_EMUL_FLAG_RC :  Receiver Complete.
  *            @arg UART_EMUL_FLAG_TC :  Transmitter Complete.
  *            @arg UART_EMUL_FLAG_FE :  Frame Error.
  *            @arg UART_EMUL_FLAG_PE :  Parity Error.
  *
  * @retval None
  */
#define __HAL_UART_EMUL_SET_FLAG(__HANDLE__, __FLAG__)  ((__HANDLE__)->Instance.SR |= (__FLAG__))

/** @brief  Determinate the length for the frame .
  * @param  __HANDLE__: specifies the UART Emulation Handle.
  * @param  None
  * @retval None
  */
#define __HAL_UART_EMUL_FRAME_LENGTH(__HANDLE__)          (uint16_t)((__HANDLE__)->Init.WordLength + (__HANDLE__)->Init.StopBits + 1)

/** @brief  Enable the clock for UART Emulation.
  *            clock in the peripherique used in this driver Timer and DMA
  * @param  None
  * @retval None
  */
#define __UART_EMUL_CLK_ENABLE()                           __HAL_RCC_TIM1_CLK_ENABLE();\
                                                           __HAL_RCC_DMA2_CLK_ENABLE();

/** @brief  Disable the clock for UART Emulation.
  *            clock in the peripherique used in this emulation Timer and DMA
  * @param  None
  * @retval None
  */
#define __UART_EMUL_CLK_DISABLE()                 __HAL_RCC_TIM1_CLK_DISABLE();\
                                                  __HAL_RCC_DMA2_CLK_DISABLE();


/* Exported functions --------------------------------------------------------*/
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_UART_Emul_Init(UART_Emul_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Emul_DeInit(UART_Emul_HandleTypeDef *huart);
void HAL_UART_Emul_MspInit(UART_Emul_HandleTypeDef *huart);
void HAL_UART_Emul_MspDeInit(UART_Emul_HandleTypeDef *huart);

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_UART_Emul_Transmit_DMA(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Emul_Receive_DMA(UART_Emul_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void HAL_UART_Emul_IRQHandler(UART_Emul_HandleTypeDef *huart);
void HAL_UART_Emul_RxCpltCallback(UART_Emul_HandleTypeDef *huart);
void HAL_UART_Emul_TxCpltCallback(UART_Emul_HandleTypeDef *huart);
void HAL_UART_Emul_ErrorCallback(UART_Emul_HandleTypeDef *huart);
void UART_EMUL_EXTI_RX(void);

/* Peripheral State functions  **************************************************/
HAL_UART_Emul_StateTypeDef HAL_UART_Emul_GetState(UART_Emul_HandleTypeDef *huart);
uint32_t HAL_UART_Emul_GetError(UART_Emul_HandleTypeDef *huart);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
#endif //TIM1_BASE
#endif /* __HAL_UART_EMUL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
