/**
  ******************************************************************************
  * @file    stm32h7xx_hal_i2s.h
  * @author  MCD Application Team
  * @brief   Header file of I2S HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_I2S_H
#define STM32H7xx_HAL_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup I2S
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup I2S_Exported_Types I2S Exported Types
  * @{
  */

/**
  * @brief I2S Init structure definition
  */
typedef struct
{
  uint32_t Mode;                            /*!< Specifies the I2S operating mode.
                                                 This parameter can be a value of @ref I2S_Mode                    */

  uint32_t Standard;                        /*!< Specifies the standard used for the I2S communication.
                                                 This parameter can be a value of @ref I2S_Standard                */

  uint32_t DataFormat;                      /*!< Specifies the data format for the I2S communication.
                                                 This parameter can be a value of @ref I2S_Data_Format             */

  uint32_t MCLKOutput;                      /*!< Specifies whether the I2S MCLK output is enabled or not.
                                                 This parameter can be a value of @ref I2S_MCLK_Output             */

  uint32_t AudioFreq;                       /*!< Specifies the frequency selected for the I2S communication.
                                                 This parameter can be a value of @ref I2S_Audio_Frequency         */

  uint32_t CPOL;                            /*!< Specifies the idle state of the I2S clock.
                                                 This parameter can be a value of @ref I2S_Clock_Polarity          */

  uint32_t FirstBit;                        /*!< Specifies whether data transfers start from MSB or LSB bit.
                                                 This parameter can be a value of @ref I2S_MSB_LSB_transmission    */

  uint32_t WSInversion;                     /*!< Control the Word Select Inversion.
                                                 This parameter can be a value of @ref I2S_WSInversion             */

  uint32_t IOSwap;                          /*!< Invert MISO/MOSI alternate functions
                                                 This parameter can be a value of @ref I2S_IO_Swap                 */

  uint32_t Data24BitAlignment;              /*!< Specifies the Data Padding for 24 bits data lenght
                                                 This parameter can be a value of @ref I2S_Data_24Bit_Alignment    */

  uint32_t FifoThreshold;                   /*!< Specifies the FIFO threshold level.
                                                 This parameter can be a value of @ref I2S_Fifo_Threshold          */

  uint32_t MasterKeepIOState;               /*!< Control of Alternate function GPIOs state
                                                 This parameter can be a value of @ref I2S_Master_Keep_IO_State    */

  uint32_t SlaveExtendFREDetection;         /*!< Control the channel length in SLAVE.
                                                 This parameter can be a value of @ref I2S_SlaveExtendFREDetection */


} I2S_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_I2S_STATE_RESET      = 0x00U,         /*!< I2S not yet initialized or disabled                */
  HAL_I2S_STATE_READY      = 0x01U,         /*!< I2S initialized and ready for use                  */
  HAL_I2S_STATE_BUSY       = 0x02U,         /*!< I2S internal process is ongoing                    */
  HAL_I2S_STATE_BUSY_TX    = 0x03U,         /*!< Data Transmission process is ongoing               */
  HAL_I2S_STATE_BUSY_RX    = 0x04U,         /*!< Data Reception process is ongoing                  */
  HAL_I2S_STATE_BUSY_TX_RX = 0x05U,         /*!< Data Transmission and Reception process is ongoing */
  HAL_I2S_STATE_TIMEOUT    = 0x06U,         /*!< I2S timeout state                                  */
  HAL_I2S_STATE_ERROR      = 0x07U          /*!< I2S error state                                    */
} HAL_I2S_StateTypeDef;

/**
  * @brief I2S handle Structure definition
  */
typedef struct __I2S_HandleTypeDef
{
  SPI_TypeDef               *Instance;                 /*!< I2S registers base address              */

  I2S_InitTypeDef            Init;                     /*!< I2S communication parameters            */

  uint16_t                  *pTxBuffPtr;               /*!< Pointer to I2S Tx transfer buffer       */

  __IO uint16_t              TxXferSize;               /*!< I2S Tx transfer size                    */

  __IO uint16_t              TxXferCount;              /*!< I2S Tx transfer Counter                 */

  uint16_t                  *pRxBuffPtr;               /*!< Pointer to I2S Rx transfer buffer       */

  __IO uint16_t              RxXferSize;               /*!< I2S Rx transfer size                    */

  __IO uint16_t              RxXferCount;              /*!< I2S Rx transfer counter                 */

  void (*RxISR)(struct __I2S_HandleTypeDef *hi2s);     /*!< function pointer on Rx ISR              */

  void (*TxISR)(struct __I2S_HandleTypeDef *hi2s);     /*!< function pointer on Tx ISR              */

  DMA_HandleTypeDef         *hdmatx;                   /*!< I2S Tx DMA handle parameters            */

  DMA_HandleTypeDef         *hdmarx;                   /*!< I2S Rx DMA handle parameters            */

  __IO HAL_LockTypeDef       Lock;                     /*!< I2S locking object                      */

  __IO HAL_I2S_StateTypeDef  State;                    /*!< I2S communication state                 */

  __IO uint32_t              ErrorCode;                /*!< I2S Error code                          */

#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  void (* TxCpltCallback)(struct __I2S_HandleTypeDef *hi2s);       /*!< I2S Tx Completed callback        */
  void (* RxCpltCallback)(struct __I2S_HandleTypeDef *hi2s);       /*!< I2S Rx Completed callback        */
  void (* TxRxCpltCallback)(struct __I2S_HandleTypeDef *hi2s);     /*!< I2S TxRx Completed callback      */
  void (* TxHalfCpltCallback)(struct __I2S_HandleTypeDef *hi2s);   /*!< I2S Tx Half Completed callback   */
  void (* RxHalfCpltCallback)(struct __I2S_HandleTypeDef *hi2s);   /*!< I2S Rx Half Completed callback   */
  void (* TxRxHalfCpltCallback)(struct __I2S_HandleTypeDef *hi2s); /*!< I2S TxRx Half Completed callback */
  void (* ErrorCallback)(struct __I2S_HandleTypeDef *hi2s);        /*!< I2S Error callback               */
  void (* MspInitCallback)(struct __I2S_HandleTypeDef *hi2s);      /*!< I2S Msp Init callback            */
  void (* MspDeInitCallback)(struct __I2S_HandleTypeDef *hi2s);    /*!< I2S Msp DeInit callback          */

#endif  /* USE_HAL_I2S_REGISTER_CALLBACKS */
} I2S_HandleTypeDef;

#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL I2S Callback ID enumeration definition
  */
typedef enum
{
  HAL_I2S_TX_COMPLETE_CB_ID             = 0x00U,    /*!< I2S Tx Completed callback ID        */
  HAL_I2S_RX_COMPLETE_CB_ID             = 0x01U,    /*!< I2S Rx Completed callback ID        */
  HAL_I2S_TX_RX_COMPLETE_CB_ID          = 0x02U,    /*!< I2S TxRx Completed callback ID      */
  HAL_I2S_TX_HALF_COMPLETE_CB_ID        = 0x03U,    /*!< I2S Tx Half Completed callback ID   */
  HAL_I2S_RX_HALF_COMPLETE_CB_ID        = 0x04U,    /*!< I2S Rx Half Completed callback ID   */
  HAL_I2S_TX_RX_HALF_COMPLETE_CB_ID     = 0x05U,    /*!< I2S TxRx Half Completed callback ID */
  HAL_I2S_ERROR_CB_ID                   = 0x06U,    /*!< I2S Error callback ID               */
  HAL_I2S_MSPINIT_CB_ID                 = 0x07U,    /*!< I2S Msp Init callback ID            */
  HAL_I2S_MSPDEINIT_CB_ID               = 0x08U     /*!< I2S Msp DeInit callback ID          */

} HAL_I2S_CallbackIDTypeDef;

/**
  * @brief  HAL I2S Callback pointer definition
  */
typedef  void (*pI2S_CallbackTypeDef)(I2S_HandleTypeDef *hi2s); /*!< pointer to an I2S callback function */

#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup I2S_Exported_Constants I2S Exported Constants
  * @{
  */

/**
  * @defgroup  I2S_Error_Defintion I2S Error Defintion
  * @brief     I2S Error Code
  * @{
  */
#define HAL_I2S_ERROR_NONE                       (0x00000000U)    /*!< No error                          */
#define HAL_I2S_ERROR_UDR                        (0x00000001U)    /*!< I2S Underrun error                */
#define HAL_I2S_ERROR_OVR                        (0x00000002U)    /*!< I2S Overrun error                 */
#define HAL_I2S_ERROR_FRE                        (0x00000004U)    /*!< I2S Frame format error            */
#define HAL_I2S_ERROR_DMA                        (0x00000008U)    /*!< DMA transfer error                */
#define HAL_I2S_ERROR_TIMEOUT                    (0x00000010U)    /*!< Timeout error                     */
#define HAL_I2S_ERROR_PRESCALER                  (0x00000020U)    /*!< Prescaler error                   */
#define HAL_I2S_ERROR_NOT_SUPPORTED              (0x00000040U)    /*!< Requested operation not supported */
#define HAL_I2S_ERROR_NO_TRANSFER                (0x00000080U)    /*!< No on going transfert             */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
#define HAL_I2S_ERROR_INVALID_CALLBACK           (0x00000100U)    /*!< Invalid Callback error            */
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup I2S_Mode I2S Mode
  * @{
  */
#define I2S_MODE_SLAVE_TX                        (0x00000000U)
#define I2S_MODE_SLAVE_RX                        (0x00000002U)
#define I2S_MODE_MASTER_TX                       (0x00000004U)
#define I2S_MODE_MASTER_RX                       (0x00000006U)
#define I2S_MODE_SLAVE_FD                        (0x00000008U)
#define I2S_MODE_MASTER_FD                       (0x0000000AU)
/**
  * @}
  */

/** @defgroup I2S_Standard I2S Standard
  * @{
  */
#define I2S_STANDARD_PHILIPS                     (0x00000000U)
#define I2S_STANDARD_MSB                         (0x00000010U)
#define I2S_STANDARD_LSB                         (0x00000020U)
#define I2S_STANDARD_PCM_SHORT                   (0x00000030U)
#define I2S_STANDARD_PCM_LONG                    (0x000000B0U)
/**
  * @}
  */

/** @defgroup I2S_Data_Format I2S Data Format
  * @{
  */
#define I2S_DATAFORMAT_16B                       (0x00000000U)
#define I2S_DATAFORMAT_16B_EXTENDED              (0x00000400U)
#define I2S_DATAFORMAT_24B                       (0x00000500U)
#define I2S_DATAFORMAT_32B                       (0x00000600U)
/**
  * @}
  */

/** @defgroup I2S_MCLK_Output I2S MCLK Output
  * @{
  */
#define I2S_MCLKOUTPUT_ENABLE                    SPI_I2SCFGR_MCKOE
#define I2S_MCLKOUTPUT_DISABLE                   (0x00000000U)
/**
  * @}
  */

/** @defgroup I2S_Audio_Frequency I2S Audio Frequency
  * @{
  */
#define I2S_AUDIOFREQ_192K                       (192000U)
#define I2S_AUDIOFREQ_96K                        (96000U)
#define I2S_AUDIOFREQ_48K                        (48000U)
#define I2S_AUDIOFREQ_44K                        (44100U)
#define I2S_AUDIOFREQ_32K                        (32000U)
#define I2S_AUDIOFREQ_22K                        (22050U)
#define I2S_AUDIOFREQ_16K                        (16000U)
#define I2S_AUDIOFREQ_11K                        (11025U)
#define I2S_AUDIOFREQ_8K                         (8000U)
#define I2S_AUDIOFREQ_DEFAULT                    (2U)
/**
  * @}
  */

/** @defgroup I2S_Clock_Polarity I2S Clock Polarity
  * @{
  */
#define I2S_CPOL_LOW                            (0x00000000U)
#define I2S_CPOL_HIGH                           SPI_I2SCFGR_CKPOL
/**
  * @}
  */

/** @defgroup I2S_MSB_LSB_transmission I2S MSB LSB Transmission
  * @{
  */
#define I2S_FIRSTBIT_MSB                        (0x00000000U)
#define I2S_FIRSTBIT_LSB                        SPI_CFG2_LSBFRST
/**
  * @}
  */

/** @defgroup I2S_WSInversion I2S Word Select Inversion
  * @{
  */
#define I2S_WS_INVERSION_DISABLE                (0x00000000U)
#define I2S_WS_INVERSION_ENABLE                 SPI_I2SCFGR_WSINV
/**
  * @}
  */

/** @defgroup I2S_IO_Swap Control I2S IO Swap
  * @{
  */
#define I2S_IO_SWAP_DISABLE                     (0x00000000U)
#define I2S_IO_SWAP_ENABLE                      SPI_CFG2_IOSWP
/**
  * @}
  */

/** @defgroup I2S_Data_24Bit_Alignment Data Padding 24Bit
  * @{
  */
#define I2S_DATA_24BIT_ALIGNMENT_RIGHT         (0x00000000U)
#define I2S_DATA_24BIT_ALIGNMENT_LEFT          SPI_I2SCFGR_DATFMT
/**
  * @}
  */

/** @defgroup I2S_Fifo_Threshold I2S Fifo Threshold
  * @{
  */
#define I2S_FIFO_THRESHOLD_01DATA              (0x00000000U)
#define I2S_FIFO_THRESHOLD_02DATA              (0x00000020U)
#define I2S_FIFO_THRESHOLD_03DATA              (0x00000040U)
#define I2S_FIFO_THRESHOLD_04DATA              (0x00000060U)
#define I2S_FIFO_THRESHOLD_05DATA              (0x00000080U)
#define I2S_FIFO_THRESHOLD_06DATA              (0x000000A0U)
#define I2S_FIFO_THRESHOLD_07DATA              (0x000000C0U)
#define I2S_FIFO_THRESHOLD_08DATA              (0x000000E0U)
#define I2S_FIFO_THRESHOLD_09DATA              (0x00000100U)
#define I2S_FIFO_THRESHOLD_10DATA              (0x00000120U)
#define I2S_FIFO_THRESHOLD_11DATA              (0x00000140U)
#define I2S_FIFO_THRESHOLD_12DATA              (0x00000160U)
#define I2S_FIFO_THRESHOLD_13DATA              (0x00000180U)
#define I2S_FIFO_THRESHOLD_14DATA              (0x000001A0U)
#define I2S_FIFO_THRESHOLD_15DATA              (0x000001C0U)
#define I2S_FIFO_THRESHOLD_16DATA              (0x000001E0U)
/**
  * @}
  */

/** @defgroup I2S_Master_Keep_IO_State Keep IO State
  * @{
  */
#define I2S_MASTER_KEEP_IO_STATE_DISABLE       (0x00000000U)
#define I2S_MASTER_KEEP_IO_STATE_ENABLE        SPI_CFG2_AFCNTR
/**
  * @}
  */

/** @defgroup I2S_SlaveExtendFREDetection Slave Extend FRE Detection
  * @{
  */
#define I2S_SLAVE_EXTEND_FRE_DETECTION_DISABLE (0x00000000U)
#define I2S_SLAVE_EXTEND_FRE_DETECTION_ENABLE  SPI_I2SCFGR_FIXCH
/**
  * @}
  */

/** @defgroup I2S_Interrupt_definition I2S Interrupt definition
  * @{
  */
#define I2S_IT_TXP                             SPI_IER_TXPIE
#define I2S_IT_RXP                             SPI_IER_RXPIE
#define I2S_IT_OVR                             SPI_IER_OVRIE
#define I2S_IT_UDR                             SPI_IER_UDRIE
#define I2S_IT_TIFRE                           SPI_IER_TIFREIE
#define I2S_IT_ERR                             (SPI_IER_OVRIE | SPI_IER_UDRIE | SPI_IER_TIFREIE)

/**
  * @}
  */

/** @defgroup I2S_Flag_definition I2S Flag definition
  * @{
  */
#define I2S_FLAG_TXP                           SPI_SR_TXP     /* I2S status flag: Tx-Packet space available      */
#define I2S_FLAG_RXP                           SPI_SR_RXP     /* I2S status flag: Rx-Packet available            */
#define I2S_FLAG_UDR                           SPI_SR_UDR     /* I2S Error flag: Underrun flag                   */
#define I2S_FLAG_RXWNE                         SPI_SR_RXWNE   /* I2S RxFIFO Word Not Empty                       */
#define I2S_FLAG_OVR                           SPI_SR_OVR     /* I2S Error flag: Overrun flag                    */
#define I2S_FLAG_TIFRE                         SPI_SR_TIFRE   /* I2S Error flag: TI mode frame format error flag */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/** @defgroup I2S_Exported_Macros I2S Exported Macros
  * @{
  */

/** @brief  Reset I2S handle state
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
#define __HAL_I2S_RESET_HANDLE_STATE(__HANDLE__) do{                                                  \
                                                     (__HANDLE__)->State = HAL_I2S_STATE_RESET;       \
                                                     (__HANDLE__)->MspInitCallback = NULL;            \
                                                     (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                   } while(0)
#else
#define __HAL_I2S_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_I2S_STATE_RESET)
#endif

/** @brief  Enable the specified SPI peripheral (in I2S mode).
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_ENABLE(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)

/** @brief  Disable the specified SPI peripheral (in I2S mode).
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_DISABLE(__HANDLE__) CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)

/** @brief  Enable the specified I2S interrupts.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @param  __INTERRUPT__: specifies the interrupt source to enable.
  *         This parameter can be one of the following values:
  *            @arg I2S_IT_TXP  : Tx-Packet space available interrupt
  *            @arg I2S_IT_RXP  : Rx-Packet available interrupt
  *            @arg I2S_IT_OVR  : Overrun interrupt
  *            @arg I2S_IT_UDR  : Underrun interrupt
  *            @arg I2S_IT_TIFRE: TI mode frame format error interrupt
  *            @arg I2S_IT_ERR: Error interrupt
  * @retval None
  */
#define __HAL_I2S_ENABLE_IT(__HANDLE__, __INTERRUPT__)    (SET_BIT((__HANDLE__)->Instance->IER,(__INTERRUPT__)))

/** @brief  Disable the specified I2S interrupts.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @param  __INTERRUPT__: specifies the interrupt source to disable.
  *         This parameter can be one of the following values:
  *            @arg I2S_IT_TXP  : Tx-Packet space available interrupt
  *            @arg I2S_IT_RXP  : Rx-Packet available interrupt
  *            @arg I2S_IT_OVR  : Overrun interrupt
  *            @arg I2S_IT_UDR  : Underrun interrupt
  *            @arg I2S_IT_TIFRE: TI mode frame format error interrupt
  *            @arg I2S_IT_ERR  : Error interrupt
  * @retval None
  */
#define __HAL_I2S_DISABLE_IT(__HANDLE__, __INTERRUPT__) (CLEAR_BIT((__HANDLE__)->Instance->IER,(__INTERRUPT__)))

/** @brief  Checks if the specified I2S interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the I2S Handle.
  *         This parameter can be I2S where x: 1, 2, or 3 to select the I2S peripheral.
  * @param  __INTERRUPT__: specifies the I2S interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg I2S_IT_TXP  : Tx-Packet space available interrupt
  *            @arg I2S_IT_RXP  : Rx-Packet available interrupt
  *            @arg I2S_IT_OVR  : Overrun interrupt
  *            @arg I2S_IT_UDR  : Underrun interrupt
  *            @arg I2S_IT_TIFRE: TI mode frame format error interrupt
  *            @arg I2S_IT_ERR  : Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_I2S_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified I2S flag is set or not.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg I2S_FLAG_TXP  : Tx-Packet space available flag
  *            @arg I2S_FLAG_RXP  : Rx-Packet available flag
  *            @arg I2S_FLAG_UDR  : Underrun flag
  *            @arg I2S_FLAG_RXWNE: RxFIFO Word Not Empty flag
  *            @arg I2S_FLAG_OVR  : Overrun flag
  *            @arg I2S_FLAG_TIFRE: TI mode frame format error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_I2S_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/** @brief Clears the I2S UDR pending flag.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_CLEAR_UDRFLAG(__HANDLE__)   SET_BIT((__HANDLE__)->Instance->IFCR , SPI_IFCR_UDRC)

/** @brief Clears the I2S OVR pending flag.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_CLEAR_OVRFLAG(__HANDLE__)   SET_BIT((__HANDLE__)->Instance->IFCR , SPI_IFCR_OVRC)

/** @brief  Clear the I2S TIFRE pending flag.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_CLEAR_TIFREFLAG(__HANDLE__) SET_BIT((__HANDLE__)->Instance->IFCR , SPI_IFCR_TIFREC)

/** @brief  Clear the I2S SUSP pending flag.
  * @param  __HANDLE__: specifies the I2S Handle.
  * @retval None
  */
#define __HAL_I2S_CLEAR_SUSPFLAG(__HANDLE__) SET_BIT((__HANDLE__)->Instance->IFCR , SPI_IFCR_SUSPC)

/* Include I2S HAL Extended module */
#include "stm32h7xx_hal_i2s_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup I2S_Exported_Functions I2S Exported Functions
  * @{
  */

/** @defgroup I2S_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s);
void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s);
void HAL_I2S_MspDeInit(I2S_HandleTypeDef *hi2s);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
HAL_StatusTypeDef HAL_I2S_RegisterCallback(I2S_HandleTypeDef *hspi, HAL_I2S_CallbackIDTypeDef CallbackID, pI2S_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2S_UnRegisterCallback(I2S_HandleTypeDef *hspi, HAL_I2S_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup I2S_Exported_Functions_Group2 IO operation functions
  * @{
  */
/* I/O operation functions  ***************************************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size, uint32_t Timeout);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size);

void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s);

/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2S_DMAPause(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_DMAResume(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_DMAStop(I2S_HandleTypeDef *hi2s);

/* Callbacks used in non blocking modes (Interrupt and DMA) *******************/
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s);
/**
  * @}
  */

/** @addtogroup I2S_Exported_Functions_Group3 Peripheral State and Errors functions
  * @{
  */
/* Peripheral Control and State functions  ************************************/
HAL_I2S_StateTypeDef HAL_I2S_GetState(I2S_HandleTypeDef *hi2s);
uint32_t HAL_I2S_GetError(I2S_HandleTypeDef *hi2s);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2S_Private I2S Private
  * @{
  */
#define IS_I2S_MODE(MODE)         (((MODE) == I2S_MODE_SLAVE_TX)  || \
                                   ((MODE) == I2S_MODE_SLAVE_RX)  || \
                                   ((MODE) == I2S_MODE_MASTER_TX) || \
                                   ((MODE) == I2S_MODE_MASTER_RX) || \
                                   ((MODE) == I2S_MODE_SLAVE_FD)  || \
                                   ((MODE) == I2S_MODE_MASTER_FD))

#define IS_I2S_FD_MODE(MODE)      (((MODE) == I2S_MODE_SLAVE_FD)  || \
                                   ((MODE) == I2S_MODE_MASTER_FD))

#define IS_I2S_MASTER(MODE)       (((MODE) == I2S_MODE_MASTER_TX)  || \
                                   ((MODE) == I2S_MODE_MASTER_RX) || \
                                   ((MODE) == I2S_MODE_MASTER_FD))

#define IS_I2S_TX_MODE(MODE)      (((MODE) == I2S_MODE_SLAVE_TX)  || \
                                   ((MODE) == I2S_MODE_MASTER_TX) || \
                                   ((MODE) == I2S_MODE_SLAVE_FD)  || \
                                   ((MODE) == I2S_MODE_MASTER_FD))

#define IS_I2S_RX_MODE(MODE)      (((MODE) == I2S_MODE_SLAVE_RX)  || \
                                   ((MODE) == I2S_MODE_MASTER_RX) || \
                                   ((MODE) == I2S_MODE_SLAVE_FD)  || \
                                   ((MODE) == I2S_MODE_MASTER_FD))

#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_STANDARD_PHILIPS)   || \
                                   ((STANDARD) == I2S_STANDARD_MSB)       || \
                                   ((STANDARD) == I2S_STANDARD_LSB)       || \
                                   ((STANDARD) == I2S_STANDARD_PCM_SHORT) || \
                                   ((STANDARD) == I2S_STANDARD_PCM_LONG))

#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DATAFORMAT_16B)          || \
                                    ((FORMAT) == I2S_DATAFORMAT_16B_EXTENDED) || \
                                    ((FORMAT) == I2S_DATAFORMAT_24B)          || \
                                    ((FORMAT) == I2S_DATAFORMAT_32B))

#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOUTPUT_ENABLE) || \
                                    ((OUTPUT) == I2S_MCLKOUTPUT_DISABLE))

#define IS_I2S_AUDIO_FREQ(FREQ)   ((((FREQ) >= I2S_AUDIOFREQ_8K)    && \
                                    ((FREQ) <= I2S_AUDIOFREQ_192K)) || \
                                    ((FREQ) == I2S_AUDIOFREQ_DEFAULT))

#define IS_I2S_CPOL(CPOL)          (((CPOL) == I2S_CPOL_LOW) || \
                                    ((CPOL) == I2S_CPOL_HIGH))

#define IS_I2S_FIRST_BIT(FIRSTBIT) (((FIRSTBIT) == I2S_FIRSTBIT_MSB) || \
                                    ((FIRSTBIT) == I2S_FIRSTBIT_LSB))

#define IS_I2S_WS_INVERSION(WSINV) (((WSINV) == I2S_WS_INVERSION_DISABLE) || \
                                    ((WSINV) == I2S_WS_INVERSION_ENABLE))

#define IS_I2S_IO_SWAP(IOSWAP)     (((IOSWAP) == I2S_IO_SWAP_DISABLE) || \
                                    ((IOSWAP) == I2S_IO_SWAP_ENABLE))

#define IS_I2S_DATA_24BIT_ALIGNMENT(ALIGNMENT)  (((ALIGNMENT) == I2S_DATA_24BIT_ALIGNMENT_RIGHT) || \
                                                 ((ALIGNMENT) == I2S_DATA_24BIT_ALIGNMENT_LEFT))

#define IS_I2S_FIFO_THRESHOLD(FTHLV) (((FTHLV) == I2S_FIFO_THRESHOLD_01DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_02DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_03DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_04DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_05DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_06DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_07DATA) || \
                                      ((FTHLV) == I2S_FIFO_THRESHOLD_08DATA))

#define IS_I2S_MASTER_KEEP_IO_STATE(AFCNTR)      (((AFCNTR) == I2S_MASTER_KEEP_IO_STATE_DISABLE) || \
                                                  ((AFCNTR) == I2S_MASTER_KEEP_IO_STATE_ENABLE))

#define IS_I2S_SLAVE_EXTEND_FRE_DETECTION(FIXCH) (((FIXCH) == I2S_SLAVE_EXTEND_FRE_DETECTION_DISABLE) || \
                                                  ((FIXCH) == I2S_SLAVE_EXTEND_FRE_DETECTION_ENABLE))

/**
  * @}
  */

/* Define the private group ***************************************************/
/******************************************************************************/
/** @defgroup I2S_Private I2S Private
  * @{
  */
/**
  * @}
  */
/******************************************************************************/
/**
  * @}
  */

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



#endif /* STM32H7xx_HAL_I2S_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
