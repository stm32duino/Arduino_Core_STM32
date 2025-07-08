/**
  ******************************************************************************
  * @file    stm32wb0x_hal_adc.h
  * @author  GPM Application Team
  * @brief   Header file of ADC HAL module.
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
#ifndef STM32WB0x_HAL_ADC_H
#define STM32WB0x_HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Include low level driver */
#include "stm32wb0x_ll_adc.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief  Structure definition for the configuration of the ADC watchdog.
  */
typedef struct
{
  uint32_t LowThreshold;              /*!< Set the lower threshold for the watchdog.
                                           This parameter is a 12-bit value.  */

  uint32_t HighThreshold;             /*!< Set the higher threshold for the watchdog.
                                           This parameter is a 12-bit value.  */

  uint32_t ChannelMask;               /*!< Select the input channels the watchdog has to use.
                                           This parameter can be a value of @ref ADC_AWD_CHANNEL.  */

  uint32_t EventType;                 /*!< Select the event type used for the watchdog.
                                           This parameter can be a value of @ref ADC_AWD_EVENTTYPE.  */

} ADC_AnalogWDGConfTypeDef;

/**
  * @brief Structure definition with the setting for the Calibration Point().
  */
typedef struct
{
  uint32_t Number;                    /*!< Select the calibration point number
                                           This parameter can be a value of @ref ADC_HAL_CALIB_POINT
                                           Caution: Only one offset is allowed per input mode (Single positive, single
                                                    negative and differential) and voltage range. This parameter
                                                    overwrites the last setting.
                                           Note: Use the ADC_CALIB_NONE to skip calibration parameter for this channel
                                                 and leave offset and gain untouched. */

  uint32_t Offset;                    /*!< Define the offset to be subtracted from the raw converted data.
                                           Offset value must be a positive number.
                                           This parameter must be a number between Min_Data = 0x00 and
                                           Max_Data = 0xFF.  */

  uint32_t Gain;                      /*!< Specify the ADC gain compensation coefficient to be applied to ADC raw
                                           conversion data, based on following formula:
                                           DATA = DATA(raw) * (gain compensation coef) / 4096
                                           This parameter value can be:
                                            - value "0": Gain will be set to default parameters
                                            - value in range [0x001; 0xFFF]: Gain compensation will be set to specified
                                           value */

} ADC_CalibrationPointTypeDef;

/**
  * @brief  Structure definition for the configuration of the ADC watchdog.
  */
typedef struct
{
  uint32_t Channel;                              /*!< Specify the channel type the channel number code for the 1st
                                                      conversion of the sequence.
                                                      This parameter can be a value of @ref ADC_HAL_CH_NUM_CODE. */

  uint32_t Rank;                                 /*!< Assign a specific sequence number to the channel.
                                                      This parameter can be a value of @ref ADC_HAL_EC_SEQ_RANKS. */

  uint32_t VoltRange;                            /*!< Specify the voltage range for the selected channel.
                                                      This parameter can be a value of
                                                      @ref ADC_HAL_INPUT_VOLTAGE_RANGE. */

  ADC_CalibrationPointTypeDef CalibrationPoint;  /*!< Specify the calibration parameter for the selected channel. */

} ADC_ChannelConfTypeDef;

/**
  * @brief Structure definition with the setting for the Down Sampler (DS).
  */
typedef struct
{
  uint32_t    DataWidth;              /*!< Specify the width of the output data from the Down Sampler (DS).
                                           This parameter can be a value of @ref ADC_HAL_DS_DATA_WIDTH. */

  uint32_t    DataRatio;              /*!< Specify the ratio of the output data from the Down Sampler (DS).
                                           This parameter can be a value of @ref ADC_HAL_DS_RATIO. */

} ADC_DSConfTypeDef;

/**
  * @brief Structure definition with the setting for the Decimation Filter (DF).
  */
typedef struct
{
  uint32_t    DynamicMode;                    /*!< Specify the input dynamic range for the Decimation Filter (DF).
                                                   This parameter can be a value of @ref ADC_HAL_DF_DYN_RANGE. */

  uint32_t    HighPassFilter;                 /*!< Specify whether the high pass filter feature is enabled or disabled.
                                                   This parameter can be set to ENABLE or DISABLE. */

  uint32_t    OutputDataFormatMode;           /*!< Specify the signed/unsigned output data format.
                                                   This parameter can be a value of @ref ADC_HAL_DF_DATA_FORMAT. */

  uint32_t    InputDataFormatMode;            /*!< Specify the signed/unsigned input data format.
                                                   This parameter can be a value of @ref ADC_HAL_DF_DATA_FORMAT. */

  uint32_t    FractionalInterpolator;         /*!< Specify whether fractional interpolator is enabled or disabled.
                                                   This parameter can be set to ENABLE or DISABLE. */

  uint32_t    CICFilterDecimatorHalfFactor;   /*!< Specify if the decimator factor of the CIC filter is using integer or
                                                   half.
                                                   Note: this bit must be set only for the generation of a data rate at
                                                   44.1 kps from ADC data at 1 MHz. Unpredictable result may happen if
                                                   set for other configuration.
                                                   This parameter can be a value of
                                                   @ref ADC_HAL_CIC_DECIMATOR_HALF_FACTOR. */

  uint32_t    MCICOutputFrequency;            /*!< Specify the output frequency of the CIC filter.
                                                   This parameter can be a value of @ref ADC_HAL_MICROPHONE_OUT_FREQ. */

} ADC_DFConfTypeDef;

/**
  * @brief Structure definition with the setting for the Pulse Density Modulation (PDM)
  */
typedef struct
{
  uint32_t ClockDivider;              /*!< Specify the clock divider for the (PDM) Interface.
                                           This parameter can be a value of @ref ADC_HAL_PDM_CLK_DIVIDER. */
} ADC_PDMConfTypeDef;

/**
  * @brief Structure definition with the setting for the Pulse Density Modulation (PDM)
  */
typedef struct
{
  uint32_t Bias;                      /*!< Specify the bias voltage (offset) for the Programmable Gain Amplifier (PGA).
                                           This parameter can be a value of @ref ADC_HAL_PGA_BIAS. */

  uint32_t Gain;                      /*!< Specify the gain for the Programmable Gain Amplifier (PGA).
                                           This parameter can be a value of @ref ADC_HAL_PGA_GAIN. */

} ADC_PGAConfTypeDef;

/**
  * @brief Structure definition with common setting for the ADC.
  */
typedef struct
{
  uint32_t    ConversionType;          /*!< Specifies the conversion type: through the Down Sampler (DS) or
                                            through the Decimation Filter (DF).
                                            This parameter can be a value of @ref ADC_HAL_CONVERSION_TYPE. */

  FunctionalState ContinuousConvMode;  /*!< Specify whether the conversion is performed in single mode (one conversion)
                                            or continuous mode for ADC group regular, after the first ADC conversion
                                            start trigger occurred (software start or external trigger). This parameter
                                            can be set to ENABLE or DISABLE. */

  uint32_t    SequenceLength;          /*!< Specify the length of the conversion sequence.
                                            This parameter must be a number between Min_Data = 1 and
                                            Max_Data = 16. */

  uint32_t    SamplingMode;            /*!< Specifies the input sampling mode.
                                            This parameter can be a value of @ref ADC_HAL_SAMPLING_METHOD. */

  uint32_t    SampleRate;              /*!< Specify the ADC sample rate.
                                            This parameter can be a value of @ref ADC_HAL_SAMPLE_RATE.     */

  ADC_DSConfTypeDef DownSamplerConfig; /*!< Specifies the Down Sampler parameters. */

  uint32_t    InvertOutputMode;        /*!< Specifies the bit to bit inversion (1' complement) for
                                            differential input and/or single negative input.
                                            This parameter can be a value of @ref ADC_HAL_DATA_INVERT.   */

  uint32_t    Overrun;                 /*!< Specifies the overrung policy applied to the data.
                                            This parameter can be a value of @ref ADC_HAL_OVERRUN_CONFIG.  */


} ADC_InitTypeDef;

/**
  * @brief  ADC handle Structure definition
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
typedef struct __ADC_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
{
  ADC_TypeDef        *Instance;    /*!< Register base address */
  ADC_InitTypeDef    Init;         /*!< Parameters for ADC initialization */

  DMA_HandleTypeDef  *DMA_Handle;  /*!< Pointer DMA Handler */

  HAL_LockTypeDef    Lock;         /*!< ADC locking object */
  __IO uint32_t      State;        /*!< ADC communication state (bitmap of ADC states) */
  __IO uint32_t      ErrorCode;    /*!< ADC Error code */

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  void (* ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);         /*!< ADC conversion complete callback */
  void (* ConvHalfCpltCallback)(struct __ADC_HandleTypeDef *hadc);     /*!< ADC conversion DMA half-transfer callback */
  void (* LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc); /*!< ADC analog watchdog 1 callback */
  void (* ErrorCallback)(struct __ADC_HandleTypeDef *hadc);            /*!< ADC error callback */
  void (* MspInitCallback)(struct __ADC_HandleTypeDef *hadc);          /*!< ADC Msp Init callback */
  void (* MspDeInitCallback)(struct __ADC_HandleTypeDef *hadc);        /*!< ADC Msp DeInit callback */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

} ADC_HandleTypeDef;


#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL ADC Callback ID enumeration definition
  */
typedef enum
{
  HAL_ADC_CONVERSION_COMPLETE_CB_ID     = 0x00U,  /*!< ADC conversion complete callback ID          */
  HAL_ADC_CONVERSION_HALF_CB_ID         = 0x01U,  /*!< ADC conversion DMA half-transfer callback ID */
  HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID   = 0x02U,  /*!< ADC watchdog callback ID                 */
  HAL_ADC_ERROR_CB_ID                   = 0x03U,  /*!< ADC error callback ID                        */
  HAL_ADC_MSPINIT_CB_ID                 = 0x09U,  /*!< ADC Msp Init callback ID                     */
  HAL_ADC_MSPDEINIT_CB_ID               = 0x0AU   /*!< ADC Msp DeInit callback ID                   */
} HAL_ADC_CallbackIDTypeDef;

/**
  * @brief  HAL ADC Callback pointer definition
  */
typedef  void (*pADC_CallbackTypeDef)(ADC_HandleTypeDef *hadc); /*!< pointer to a ADC callback function */

#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_States ADC States
  * @{
  */

/**
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  * @note   ADC state machine is managed by bitfields, state must be compared
  *         with bit by bit.
  *         For example:
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATEBUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_AWD1) != 0UL) "
  */
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET           (0x00000000UL)   /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY           (0x00000001UL)   /*!< ADC peripheral ready to use         */
#define HAL_ADC_STATE_BUSY_INTERNAL   (0x00000002UL)   /*!< ADC is busy due to an internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT         (0x00000004UL)   /*!< TimeOut occurrence                  */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL  (0x00000010UL)   /*!< Internal error occurrence      */
#define HAL_ADC_STATE_ERROR_CONFIG    (0x00000020UL)   /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA       (0x00000040UL)   /*!< DMA error occurrence           */

/* States of ADC conversion */
#define HAL_ADC_STATE_DS_BUSY         (0x00000100UL)   /*!< A conversion on down sampler data path is ongoing or can
                                                            occur */
#define HAL_ADC_STATE_DS_EOC          (0x00000200UL)   /*!< Converted data available in downsampler data register     */
#define HAL_ADC_STATE_DS_OVR          (0x00000400UL)   /*!< Overrun on down sampler data path occurrence              */

#define HAL_ADC_STATE_DF_BUSY         (0x00001000UL)   /*!< A conversion on decimation filter path is ongoing or can
                                                            occur */
#define HAL_ADC_STATE_DF_EOC          (0x00002000UL)   /*!< Converted data available in decimation filter data
                                                            register */
#define HAL_ADC_STATE_DF_OVR          (0x00000400UL)   /*!< Overrun occurrence in decimation filter data              */

/* States of ADC analog watchdog */
#define HAL_ADC_STATE_AWD1            (0x00010000UL)   /*!< Out-of-window occurrence of ADC analog watchdog */

/**
  * @}
  */


/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */

#define HAL_ADC_ERROR_NONE            (0x00U)   /*!< No error               */
#define HAL_ADC_ERROR_INTERNAL        (0x01U)   /*!< Internal error         */
#define HAL_ADC_ERROR_OVR             (0x02U)   /*!< Data overrun error     */
#define HAL_ADC_ERROR_DMA             (0x04U)   /*!< DMA transfer error     */

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define HAL_ADC_ERROR_INVALID_CALLBACK  (0x10U) /*!< Invalid Callback error */
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */

#define ADC_DEFAULT_LDO_DELAY_US         (160UL)      /*!< Default delay for LDO stabilization (uS)*/
#define ADC_DEFAULT_VBIAS_PRECH_DELAY_US (600UL)      /*!< Default delay for the VBIAS precharge pulse duration (uS)*/

/** @defgroup ADC_HAL_CH_NUM_CODE ADC channel number code for conversion definitions
  * @{
  */

#define ADC_CHANNEL_VINM0            (LL_ADC_CHANNEL_VINM0)        /*!< ADC channel for VINM0 to single negative input */
#define ADC_CHANNEL_VINM1            (LL_ADC_CHANNEL_VINM1)        /*!< ADC channel for VINM1 to single negative input */
#define ADC_CHANNEL_VINM2            (LL_ADC_CHANNEL_VINM2)        /*!< ADC channel for VINM2 to single negative input */
#define ADC_CHANNEL_VINM3            (LL_ADC_CHANNEL_VINM3)        /*!< ADC channel for VINM3 to single negative input */
#define ADC_CHANNEL_VINP0            (LL_ADC_CHANNEL_VINP0)        /*!< ADC channel for VINP0 to single positive input */
#define ADC_CHANNEL_VINP1            (LL_ADC_CHANNEL_VINP1)        /*!< ADC channel for VINP1 to single positive input */
#define ADC_CHANNEL_VINP2            (LL_ADC_CHANNEL_VINP2)        /*!< ADC channel for VINP2 to single positive input */
#define ADC_CHANNEL_VINP3            (LL_ADC_CHANNEL_VINP3)        /*!< ADC channel for VINP3 to single positive input */
#define ADC_CHANNEL_VINP0_VINM0      (LL_ADC_CHANNEL_VINP0_VINM0)  /*!< ADC channel for VINP0 - VINM0 to differential input */
#define ADC_CHANNEL_VINP1_VINM1      (LL_ADC_CHANNEL_VINP1_VINM1)  /*!< ADC channel for VINP1 - VINM1 to differential input */
#define ADC_CHANNEL_VINP2_VINM2      (LL_ADC_CHANNEL_VINP2_VINM2)  /*!< ADC channel for VINP2 - VINM2 to differential input */
#define ADC_CHANNEL_VINP3_VINM3      (LL_ADC_CHANNEL_VINP3_VINM3)  /*!< ADC channel for VINP3 - VINM3 to differential input */
#define ADC_CHANNEL_VBAT             (LL_ADC_CHANNEL_VBAT)         /*!< ADC channel for VBAT, battery level detector        */
#define ADC_CHANNEL_TEMPSENSOR       (LL_ADC_CHANNEL_TEMPSENSOR)   /*!< ADC channel for temperature sensor                  */

/**
  * @}
  */

/** @defgroup ADC_HAL_SAMPLING_METHOD  ADC input sampling method definitions
  * @{
  */

#define ADC_SAMPLING_AT_START    (LL_ADC_SAMPLING_AT_START)  /*!< Sampling only at conversion start (default) */
#define ADC_SAMPLING_AT_END      (LL_ADC_SAMPLING_AT_END)    /*!< Sampling sampling phase starts after end of
                                                                  conversion, and stops upon trigger event
                                                                  (Also known as Bulb sampling mode). */

/**
  * @}
  */


/** @defgroup ADC_HAL_OVERRUN_CONFIG ADC overrun configuration definitions
  * @{
  */
#define ADC_NEW_DATA_IS_LOST    (LL_ADC_NEW_DATA_IS_LOST)        /*!< Previous data is preserved, new data is lost.   */
#define ADC_NEW_DATA_IS_KEPT    (LL_ADC_NEW_DATA_IS_KEPT)        /*!< Previous data is overwritten, new data is kept. */

/**
  * @}
  */


/** @defgroup ADC_HAL_DATA_INVERT ADC invert bit to bit data output for differential or
  *           single negative input (1' complement) definitions
  * @{
  */

#define ADC_DATA_INVERT_NONE  (0x00UL)    /*!< No inversion                             */
#define ADC_DATA_INVERT_DIFF  (0x01UL)    /*!< Inversion only for differential input    */
#define ADC_DATA_INVERT_SING  (0x02UL)    /*!< Inversion only for single negative input */
#define ADC_DATA_INVERT_BOTH  (0x03UL)    /*!< Inversion for both input type            */

/**
  * @}
  */

/** @defgroup ADC_HAL_CONVERSION_TYPE ADC conversion type definitions
  * @{
  */

#define ADC_CONVERSION_WITH_DS  (0x00UL)    /*!< ADC conversion through the Down Sampler (DS)      */
#define ADC_CONVERSION_WITH_DF  (0x01UL)    /*!< ADC conversion through the Decimation Filter (DF) */

/**
  * @}
  */

/** @defgroup ADC_HAL_SAMPLE_RATE ADC sample rate definitions
  * @{
  */
#define ADC_SAMPLE_RATE_16    (LL_ADC_SAMPLE_RATE_16)                     /*!< ADC conversion rate at F_ADC_CLK /  16 */
#define ADC_SAMPLE_RATE_20    (LL_ADC_SAMPLE_RATE_20)                     /*!< ADC conversion rate at F_ADC_CLK /  20 */
#define ADC_SAMPLE_RATE_24    (LL_ADC_SAMPLE_RATE_24)                     /*!< ADC conversion rate at F_ADC_CLK /  24 */
#define ADC_SAMPLE_RATE_28    (LL_ADC_SAMPLE_RATE_28)                     /*!< ADC conversion rate at F_ADC_CLK /  28 */
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
#define ADC_SAMPLE_RATE_32    (LL_ADC_SAMPLE_RATE_32)                     /*!< ADC conversion rate at F_ADC_CLK /  32 */
#define ADC_SAMPLE_RATE_36    (LL_ADC_SAMPLE_RATE_36)                     /*!< ADC conversion rate at F_ADC_CLK /  36 */
#define ADC_SAMPLE_RATE_40    (LL_ADC_SAMPLE_RATE_40)                     /*!< ADC conversion rate at F_ADC_CLK /  40 */
#define ADC_SAMPLE_RATE_44    (LL_ADC_SAMPLE_RATE_44)                     /*!< ADC conversion rate at F_ADC_CLK /  44 */
#define ADC_SAMPLE_RATE_48    (LL_ADC_SAMPLE_RATE_48)                     /*!< ADC conversion rate at F_ADC_CLK /  48 */
#define ADC_SAMPLE_RATE_52    (LL_ADC_SAMPLE_RATE_52)                     /*!< ADC conversion rate at F_ADC_CLK /  52 */
#define ADC_SAMPLE_RATE_56    (LL_ADC_SAMPLE_RATE_56)                     /*!< ADC conversion rate at F_ADC_CLK /  56 */
#define ADC_SAMPLE_RATE_60    (LL_ADC_SAMPLE_RATE_60)                     /*!< ADC conversion rate at F_ADC_CLK /  60 */
#define ADC_SAMPLE_RATE_64    (LL_ADC_SAMPLE_RATE_64)                     /*!< ADC conversion rate at F_ADC_CLK /  64 */
#define ADC_SAMPLE_RATE_68    (LL_ADC_SAMPLE_RATE_68)                     /*!< ADC conversion rate at F_ADC_CLK /  68 */
#define ADC_SAMPLE_RATE_72    (LL_ADC_SAMPLE_RATE_72)                     /*!< ADC conversion rate at F_ADC_CLK /  72 */
#define ADC_SAMPLE_RATE_76    (LL_ADC_SAMPLE_RATE_76)                     /*!< ADC conversion rate at F_ADC_CLK /  76 */
#define ADC_SAMPLE_RATE_80    (LL_ADC_SAMPLE_RATE_80)                     /*!< ADC conversion rate at F_ADC_CLK /  80 */
#define ADC_SAMPLE_RATE_84    (LL_ADC_SAMPLE_RATE_84)                     /*!< ADC conversion rate at F_ADC_CLK /  84 */
#define ADC_SAMPLE_RATE_88    (LL_ADC_SAMPLE_RATE_88)                     /*!< ADC conversion rate at F_ADC_CLK /  88 */
#define ADC_SAMPLE_RATE_92    (LL_ADC_SAMPLE_RATE_92)                     /*!< ADC conversion rate at F_ADC_CLK /  92 */
#define ADC_SAMPLE_RATE_96    (LL_ADC_SAMPLE_RATE_96)                     /*!< ADC conversion rate at F_ADC_CLK /  96 */
#define ADC_SAMPLE_RATE_100   (LL_ADC_SAMPLE_RATE_100)                    /*!< ADC conversion rate at F_ADC_CLK / 100 */
#define ADC_SAMPLE_RATE_104   (LL_ADC_SAMPLE_RATE_104)                    /*!< ADC conversion rate at F_ADC_CLK / 104 */
#define ADC_SAMPLE_RATE_108   (LL_ADC_SAMPLE_RATE_108)                    /*!< ADC conversion rate at F_ADC_CLK / 108 */
#define ADC_SAMPLE_RATE_112   (LL_ADC_SAMPLE_RATE_112)                    /*!< ADC conversion rate at F_ADC_CLK / 112 */
#define ADC_SAMPLE_RATE_116   (LL_ADC_SAMPLE_RATE_116)                    /*!< ADC conversion rate at F_ADC_CLK / 116 */
#define ADC_SAMPLE_RATE_120   (LL_ADC_SAMPLE_RATE_120)                    /*!< ADC conversion rate at F_ADC_CLK / 120 */
#define ADC_SAMPLE_RATE_124   (LL_ADC_SAMPLE_RATE_124)                    /*!< ADC conversion rate at F_ADC_CLK / 124 */
#define ADC_SAMPLE_RATE_128   (LL_ADC_SAMPLE_RATE_128)                    /*!< ADC conversion rate at F_ADC_CLK / 128 */
#define ADC_SAMPLE_RATE_132   (LL_ADC_SAMPLE_RATE_132)                    /*!< ADC conversion rate at F_ADC_CLK / 132 */
#define ADC_SAMPLE_RATE_136   (LL_ADC_SAMPLE_RATE_136)                    /*!< ADC conversion rate at F_ADC_CLK / 136 */
#define ADC_SAMPLE_RATE_140   (LL_ADC_SAMPLE_RATE_140)                    /*!< ADC conversion rate at F_ADC_CLK / 140 */

#endif /* ADC_CONF_SAMPLE_RATE_MSB */
/**
  * @}
  */


/** @defgroup ADC_HAL_OP_MODE ADC operation modes definitions
  * @{
  */

#define ADC_OP_MODE_ADC      (LL_ADC_OP_MODE_ADC)    /*!< ADC operation mode ADC   */
#define ADC_OP_MODE_AUDIO    (LL_ADC_OP_MODE_AUDIO)  /*!< ADC operation mode AUDIO */
#define ADC_OP_MODE_FULL     (LL_ADC_OP_MODE_FULL)   /*!< ADC operation Full mode  */

/**
  * @}
  */

/** @defgroup ADC_HAL_EC_SEQ_RANKS  ADC Sequencer ranks
  * @{
  */

#define ADC_RANK_1                (LL_ADC_RANK_1)  /*!< ADC sequencer rank  1 */
#define ADC_RANK_2                (LL_ADC_RANK_2)  /*!< ADC sequencer rank  2 */
#define ADC_RANK_3                (LL_ADC_RANK_3)  /*!< ADC sequencer rank  3 */
#define ADC_RANK_4                (LL_ADC_RANK_4)  /*!< ADC sequencer rank  4 */
#define ADC_RANK_5                (LL_ADC_RANK_5)  /*!< ADC sequencer rank  5 */
#define ADC_RANK_6                (LL_ADC_RANK_6)  /*!< ADC sequencer rank  6 */
#define ADC_RANK_7                (LL_ADC_RANK_7)  /*!< ADC sequencer rank  7 */
#define ADC_RANK_8                (LL_ADC_RANK_8)  /*!< ADC sequencer rank  8 */
#define ADC_RANK_9                (LL_ADC_RANK_9)  /*!< ADC sequencer rank  9 */
#define ADC_RANK_10               (LL_ADC_RANK_10) /*!< ADC sequencer rank 10 */
#define ADC_RANK_11               (LL_ADC_RANK_11) /*!< ADC sequencer rank 11 */
#define ADC_RANK_12               (LL_ADC_RANK_12) /*!< ADC sequencer rank 12 */
#define ADC_RANK_13               (LL_ADC_RANK_13) /*!< ADC sequencer rank 13 */
#define ADC_RANK_14               (LL_ADC_RANK_14) /*!< ADC sequencer rank 14 */
#define ADC_RANK_15               (LL_ADC_RANK_15) /*!< ADC sequencer rank 15 */
#define ADC_RANK_16               (LL_ADC_RANK_16) /*!< ADC sequencer rank 16 */

/**
  * @}
  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_HAL_OCM_SOURCE ADC occasional mode source definitions
  * @{
  */

#define ADC_OCM_SRC_VBAT    (LL_ADC_OCM_SRC_VBAT)  /*!< ADC occasional mode source VBAT */
#define ADC_OCM_SRC_TEMP    (LL_ADC_OCM_SRC_TEMP)  /*!< ADC occasional mode source temperature sensor */

/**
  * @}
  */


/** @defgroup ADC_HAL_PGA_BIAS ADC microphone bias voltage definitions
  * @{
  */

#define ADC_PGA_BIAS_050_BAT   (LL_ADC_PGA_BIAS_050_BAT)  /*!< Set the microphone bias voltage at 0.50 V */
#define ADC_PGA_BIAS_055_BAT   (LL_ADC_PGA_BIAS_055_BAT)  /*!< Set the microphone bias voltage at 0.55 V */
#define ADC_PGA_BIAS_060_BAT   (LL_ADC_PGA_BIAS_060_BAT)  /*!< Set the microphone bias voltage at 0.60 V */
#define ADC_PGA_BIAS_065_BAT   (LL_ADC_PGA_BIAS_065_BAT)  /*!< Set the microphone bias voltage at 0.65 V */
#define ADC_PGA_BIAS_070_BAT   (LL_ADC_PGA_BIAS_070_BAT)  /*!< Set the microphone bias voltage at 0.70 V */
#define ADC_PGA_BIAS_075_BAT   (LL_ADC_PGA_BIAS_075_BAT)  /*!< Set the microphone bias voltage at 0.75 V */
#define ADC_PGA_BIAS_080_BAT   (LL_ADC_PGA_BIAS_080_BAT)  /*!< Set the microphone bias voltage at 0.80 V */
#define ADC_PGA_BIAS_090_BAT   (LL_ADC_PGA_BIAS_090_BAT)  /*!< Set the microphone bias voltage at 0.90 V */

/**
  * @}
  */


/** @defgroup ADC_HAL_PGA_GAIN ADC microphone gain definitions
  * @{
  */

#define ADC_PGA_GAIN_06_DB   (LL_ADC_PGA_GAIN_06_DB)  /*!< Set the microphone gain at 6 dB  */
#define ADC_PGA_GAIN_09_DB   (LL_ADC_PGA_GAIN_09_DB)  /*!< Set the microphone gain at 9 dB  */
#define ADC_PGA_GAIN_12_DB   (LL_ADC_PGA_GAIN_12_DB)  /*!< Set the microphone gain at 12 dB */
#define ADC_PGA_GAIN_15_DB   (LL_ADC_PGA_GAIN_15_DB)  /*!< Set the microphone gain at 15 dB */
#define ADC_PGA_GAIN_18_DB   (LL_ADC_PGA_GAIN_18_DB)  /*!< Set the microphone gain at 18 dB */
#define ADC_PGA_GAIN_21_DB   (LL_ADC_PGA_GAIN_21_DB)  /*!< Set the microphone gain at 21 dB */
#define ADC_PGA_GAIN_24_DB   (LL_ADC_PGA_GAIN_24_DB)  /*!< Set the microphone gain at 24 dB */
#define ADC_PGA_GAIN_27_DB   (LL_ADC_PGA_GAIN_27_DB)  /*!< Set the microphone gain at 27 dB */
#define ADC_PGA_GAIN_30_DB   (LL_ADC_PGA_GAIN_30_DB)  /*!< Set the microphone gain at 30 dB */
/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_HAL_INPUT_VOLTAGE_RANGE ADC input voltage range definitions
  * @{
  */

#define ADC_VIN_RANGE_1V2    (LL_ADC_VIN_RANGE_1V2)  /*!< ADC input voltage range up to 1.2 V */
#define ADC_VIN_RANGE_2V4    (LL_ADC_VIN_RANGE_2V4)  /*!< ADC input voltage range up to 2.4 V */
#define ADC_VIN_RANGE_3V6    (LL_ADC_VIN_RANGE_3V6)  /*!< ADC input voltage range up to 3.6 V */

/**
  * @}
  */


#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_HAL_DF_DYN_RANGE ADC Decimation Filter dynamic range definitions
  * @{
  */

#define ADC_DF_DYN_RANGE_FULL    (LL_ADC_DF_DYN_RANGE_FULL)  /*!< ADC Decimation Filter dynamic full range */
#define ADC_DF_DYN_RANGE_HALF    (LL_ADC_DF_DYN_RANGE_HALF)  /*!< ADC Decimation Filter dynamic half range */

/**
  * @}
  */

/** @defgroup ADC_HAL_MIC_CHANNEL ADC microphone channel definitions
  * @{
  */

#define ADC_DF_MIC_CH_RIGHT    (LL_ADC_DF_MIC_CH_RIGHT) /*!< ADC microphone channel right */
#define ADC_DF_MIC_CH_LEFT     (LL_ADC_DF_MIC_CH_LEFT)  /*!< ADC microphone channel left  */

/**
  * @}
  */

/** @defgroup ADC_HAL_DF_DATA_FORMAT ADC data format definitions
  * @{
  */

#define ADC_DF_DATA_FORMAT_SIGNED    (LL_ADC_DF_DATA_FORMAT_SIGNED)    /*!< ADC data format signed   */
#define ADC_DF_DATA_FORMAT_UNSIGNED  (LL_ADC_DF_DATA_FORMAT_UNSIGNED)  /*!< ADC data format unsigned */

/**
  * @}
  */

/** @defgroup ADC_HAL_CIC_DECIMATOR_HALF_FACTOR ADC CIC decimator half factor definitions
  * @{
  */

#define ADC_DF_CIC_DECIMATOR_FACTOR_HALF     (LL_ADC_DF_CIC_DECIMATOR_FACTOR_HALF)    /*!< ADC DF CIC decimator factor half    */
#define ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER  (LL_ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER) /*!< ADC DF CIC decimator factor integer */

/**
  * @}
  */

/** @defgroup ADC_HAL_PDM_CLK_DIVIDER ADC PDM clock divider definitions
  * @{
  */

#define ADC_PDM_DIV_10   (LL_ADC_PDM_DIV_10)  /*!< ADC PDM clock divider 10 */
#define ADC_PDM_DIV_11   (LL_ADC_PDM_DIV_11)  /*!< ADC PDM clock divider 11 */
#define ADC_PDM_DIV_12   (LL_ADC_PDM_DIV_12)  /*!< ADC PDM clock divider 12 */
#define ADC_PDM_DIV_13   (LL_ADC_PDM_DIV_13)  /*!< ADC PDM clock divider 13 */
#define ADC_PDM_DIV_14   (LL_ADC_PDM_DIV_14)  /*!< ADC PDM clock divider 14 */
#define ADC_PDM_DIV_15   (LL_ADC_PDM_DIV_15)  /*!< ADC PDM clock divider 15 */
#define ADC_PDM_DIV_16   (LL_ADC_PDM_DIV_16)  /*!< ADC PDM clock divider 16 */
#define ADC_PDM_DIV_17   (LL_ADC_PDM_DIV_17)  /*!< ADC PDM clock divider 17 */
#define ADC_PDM_DIV_18   (LL_ADC_PDM_DIV_18)  /*!< ADC PDM clock divider 18 */
#define ADC_PDM_DIV_19   (LL_ADC_PDM_DIV_19)  /*!< ADC PDM clock divider 19 */
#define ADC_PDM_DIV_20   (LL_ADC_PDM_DIV_20)  /*!< ADC PDM clock divider 20 */
#define ADC_PDM_DIV_21   (LL_ADC_PDM_DIV_21)  /*!< ADC PDM clock divider 21 */
#define ADC_PDM_DIV_22   (LL_ADC_PDM_DIV_22)  /*!< ADC PDM clock divider 22 */
#define ADC_PDM_DIV_23   (LL_ADC_PDM_DIV_23)  /*!< ADC PDM clock divider 23 */
#define ADC_PDM_DIV_24   (LL_ADC_PDM_DIV_24)  /*!< ADC PDM clock divider 24 */
#define ADC_PDM_DIV_25   (LL_ADC_PDM_DIV_25)  /*!< ADC PDM clock divider 25 */

/**
  * @}
  */

/** @defgroup ADC_HAL_MICROPHONE_OUT_FREQ ADC microphone output frequency definitions
  * @{
  */
#define ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ)  /*!< ADC digital microphone output frequency 47.619 kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ)  /*!< ADC digital microphone output frequency 44.44  kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ)  /*!< ADC digital microphone output frequency 22.22  kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ)  /*!< ADC digital microphone output frequency 15.873 kHz */
#define ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ)   /*!< ADC digital microphone output frequency 7.936  kHz */

#define ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ (LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ)  /*!< ADC analog microphone output frequency 200.00 kHz */
#define ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ  (LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ)   /*!< ADC analog microphone output frequency 15.873 kHz */
#define ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ   (LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ)    /*!< ADC analog microphone output frequency 7.936  kHz */

/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_HAL_DS_DATA_WIDTH ADC Down Sampler data width definitions
  * @{
  */

#define ADC_DS_DATA_WIDTH_12_BIT  (LL_ADC_DS_DATA_WIDTH_12_BIT)  /*!< ADC Down Sampler data width 12 bits */
#define ADC_DS_DATA_WIDTH_13_BIT  (LL_ADC_DS_DATA_WIDTH_13_BIT)  /*!< ADC Down Sampler data width 13 bits */
#define ADC_DS_DATA_WIDTH_14_BIT  (LL_ADC_DS_DATA_WIDTH_14_BIT)  /*!< ADC Down Sampler data width 14 bits */
#define ADC_DS_DATA_WIDTH_15_BIT  (LL_ADC_DS_DATA_WIDTH_15_BIT)  /*!< ADC Down Sampler data width 15 bits */
#define ADC_DS_DATA_WIDTH_16_BIT  (LL_ADC_DS_DATA_WIDTH_16_BIT)  /*!< ADC Down Sampler data width 16 bits */

/**
  * @}
  */


/** @defgroup ADC_HAL_DS_RATIO ADC Down Sampler ratio definitions
  * @{
  */

#define ADC_DS_RATIO_1    (LL_ADC_DS_RATIO_1)       /*!< ADC Down Sampler ratio 1, no down sampling (default) */
#define ADC_DS_RATIO_2    (LL_ADC_DS_RATIO_2)       /*!< ADC Down Sampler ratio 2                             */
#define ADC_DS_RATIO_4    (LL_ADC_DS_RATIO_4)       /*!< ADC Down Sampler ratio 4                             */
#define ADC_DS_RATIO_8    (LL_ADC_DS_RATIO_8)       /*!< ADC Down Sampler ratio 8                             */
#define ADC_DS_RATIO_16   (LL_ADC_DS_RATIO_16)      /*!< ADC Down Sampler ratio 16                            */
#define ADC_DS_RATIO_32   (LL_ADC_DS_RATIO_32)      /*!< ADC Down Sampler ratio 32                            */
#define ADC_DS_RATIO_64   (LL_ADC_DS_RATIO_64)      /*!< ADC Down Sampler ratio 64                            */
#define ADC_DS_RATIO_128  (LL_ADC_DS_RATIO_128)     /*!< ADC Down Sampler ratio 128                           */

/**
  * @}
  */


/** @defgroup ADC_HAL_CALIB_POINT ADC calibration points definitions
  * @{
  */

#define ADC_CALIB_POINT_1  (LL_ADC_CALIB_POINT_1)  /*!< ADC calibration point 1 */
#define ADC_CALIB_POINT_2  (LL_ADC_CALIB_POINT_2)  /*!< ADC calibration point 2 */
#define ADC_CALIB_POINT_3  (LL_ADC_CALIB_POINT_3)  /*!< ADC calibration point 3 */
#define ADC_CALIB_POINT_4  (LL_ADC_CALIB_POINT_4)  /*!< ADC calibration point 4 */
#define ADC_CALIB_NONE     (LL_ADC_CALIB_POINT_1   \
                            | LL_ADC_CALIB_POINT_2 \
                            | LL_ADC_CALIB_POINT_3 \
                            | LL_ADC_CALIB_POINT_4) /*!< ADC calibration point disabled: correction are left untouched
                                                       for the selected channel */

/**
  * @}
  */


/** @defgroup ADC_AWD_CHANNEL ADC watchdog channel selection for bit mask definitions
  * @{
  */

#define ADC_AWD_CH_VINM0      (LL_ADC_AWD_CH_VINM0)      /*!< ADC watchdog channel selection: VINM0 to ADC negative input  */
#define ADC_AWD_CH_VINM1      (LL_ADC_AWD_CH_VINM1)      /*!< ADC watchdog channel selection: VINM1 to ADC negative input  */
#define ADC_AWD_CH_VINM2      (LL_ADC_AWD_CH_VINM2)      /*!< ADC watchdog channel selection: VINM2 to ADC negative input  */
#define ADC_AWD_CH_VINM3      (LL_ADC_AWD_CH_VINM3)      /*!< ADC watchdog channel selection: VINM3 to ADC negative input  */
#define ADC_AWD_CH_VINP0      (LL_ADC_AWD_CH_VINP0)      /*!< ADC watchdog channel selection: VINP0 to ADC positive input  */
#define ADC_AWD_CH_VINP1      (LL_ADC_AWD_CH_VINP1)      /*!< ADC watchdog channel selection: VINP1 to ADC positive input  */
#define ADC_AWD_CH_VINP2      (LL_ADC_AWD_CH_VINP2)      /*!< ADC watchdog channel selection: VINP2 to ADC positive input  */
#define ADC_AWD_CH_VINP3      (LL_ADC_AWD_CH_VINP3)      /*!< ADC watchdog channel selection: VINP3 to ADC positive input  */
#define ADC_AWD_CH_MICROM     (LL_ADC_AWD_CH_MICROM)     /*!< ADC watchdog channel selection: MICROM to ADC negative input */
#define ADC_AWD_CH_MICROP     (LL_ADC_AWD_CH_MICROP)     /*!< ADC watchdog channel selection: MICROP to ADC positive input */
#define ADC_AWD_CH_VBAT       (LL_ADC_AWD_CH_VBAT)       /*!< ADC watchdog channel selection: VBAT to ADC negative input   */
#define ADC_AWD_CH_TEMPSENSOR (LL_ADC_AWD_CH_TEMPSENSOR) /*!< ADC watchdog channel selection: TEMPSENSOR to ADC positive input   */
#define ADC_AWD_CH_GND_NEG    (LL_ADC_AWD_CH_GND_NEG)    /*!< ADC watchdog channel selection: GND to ADC negative input    */
#define ADC_AWD_CH_GND_POS    (LL_ADC_AWD_CH_GND_POS)    /*!< ADC watchdog channel selection: GND to ADC positive input    */
#define ADC_AWD_CH_VDDA_NEG   (LL_ADC_AWD_CH_VDDA_NEG)   /*!< ADC watchdog channel selection: VDDA to ADC negative input   */
#define ADC_AWD_CH_VDDA_POS   (LL_ADC_AWD_CH_VDDA_POS)   /*!< ADC watchdog channel selection: VDDA to ADC positive input   */

/**
  * @}
  */

/** @defgroup ADC_AWD_EVENTTYPE ADC watchdog event type definitions
  * @{
  */

#define ADC_AWD_EVENT_POLLING       (0x00U)  /*!< ADC watchdog event type polling   */
#define ADC_AWD_EVENT_INTERRUPT     (0x01U)  /*!< ADC watchdog event type interrupt */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @{
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define ADC_IRQ_FLAG_OVRFL   (LL_ADC_IRQ_FLAG_OVRFL) /*!< ADC IRQ flag OVRFL Decimation Filter Saturated */
#define ADC_IRQ_FLAG_OVRDF   (LL_ADC_IRQ_FLAG_OVRDF) /*!< ADC IRQ flag OVRDF Decimation Filter Overrun */
#define ADC_IRQ_FLAG_EODF    (LL_ADC_IRQ_FLAG_EODF)  /*!< ADC IRQ flag EODF  End of Decimation Filter conversion */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
#define ADC_IRQ_FLAG_OVRDS   (LL_ADC_IRQ_FLAG_OVRDS) /*!< ADC IRQ flag OVRDS Down Sampler overrun */
#define ADC_IRQ_FLAG_AWD1    (LL_ADC_IRQ_FLAG_AWD1)  /*!< ADC IRQ flag AWD1 Analog watchdog event */
#define ADC_IRQ_FLAG_EOS     (LL_ADC_IRQ_FLAG_EOS)   /*!< ADC IRQ flag EOS  End of conversion Sequence */
#define ADC_IRQ_FLAG_EOC     (LL_ADC_IRQ_FLAG_EOC)   /*!< ADC IRQ flag EOC  End of conversion */
#define ADC_IRQ_FLAG_EODS    (LL_ADC_IRQ_FLAG_EODS)  /*!< ADC IRQ flag EODS End of Down Sampler conversion */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @{
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define ADC_IRQ_FLAGS_MASK      (ADC_IRQ_FLAG_OVRFL | \
                                 ADC_IRQ_FLAG_OVRDF | \
                                 ADC_IRQ_FLAG_OVRDS | \
                                 ADC_IRQ_FLAG_AWD1  | \
                                 ADC_IRQ_FLAG_EOS   | \
                                 ADC_IRQ_FLAG_EOC   | \
                                 ADC_IRQ_FLAG_EODF  | \
                                 ADC_IRQ_FLAG_EODS)

#else
#define ADC_IRQ_FLAGS_MASK      (ADC_IRQ_FLAG_OVRDS | \
                                 ADC_IRQ_FLAG_AWD1  | \
                                 ADC_IRQ_FLAG_EOS   | \
                                 ADC_IRQ_FLAG_EOC   | \
                                 ADC_IRQ_FLAG_EODS)
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE ADC interrupts enable definitions
  * @{
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define ADC_IRQ_EN_OVRFL   (LL_ADC_IRQ_EN_OVRFL)    /*!< ADC IRQ enable OVRFL */
#define ADC_IRQ_EN_OVRDF   (LL_ADC_IRQ_EN_OVRDF)    /*!< ADC IRQ enable OVRDF */
#define ADC_IRQ_EN_EODF    (LL_ADC_IRQ_EN_EODF)     /*!< ADC IRQ enable EODF  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
#define ADC_IRQ_EN_OVRDS   (LL_ADC_IRQ_EN_OVRDS)    /*!< ADC IRQ enable OVRDS */
#define ADC_IRQ_EN_AWD1    (LL_ADC_IRQ_EN_AWD1)     /*!< ADC IRQ enable AWD1   */
#define ADC_IRQ_EN_EOS     (LL_ADC_IRQ_EN_EOS)      /*!< ADC IRQ enable EOS   */
#define ADC_IRQ_EN_EOC     (LL_ADC_IRQ_EN_EOC)      /*!< ADC IRQ enable EOC   */
#define ADC_IRQ_EN_EODS    (LL_ADC_IRQ_EN_EODS)     /*!< ADC IRQ enable EODS  */

/**
  * @}
  */


/** @defgroup ADC_HAL_IRQ_ENABLE_MASK ADC IRQ_ENABLE register mask definitions
  * @{
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define ADC_IRQ_EN_MASK      (ADC_IRQ_EN_OVRFL | \
                              ADC_IRQ_EN_OVRDF | \
                              ADC_IRQ_EN_OVRDS | \
                              ADC_IRQ_EN_AWD1  | \
                              ADC_IRQ_EN_EOS   | \
                              ADC_IRQ_EN_EOC   | \
                              ADC_IRQ_EN_EODF  | \
                              ADC_IRQ_EN_EODS)
#else
#define ADC_IRQ_EN_MASK      (ADC_IRQ_EN_OVRDS | \
                              ADC_IRQ_EN_AWD1  | \
                              ADC_IRQ_EN_EOS   | \
                              ADC_IRQ_EN_EOC   | \
                              ADC_IRQ_EN_EODS)
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
/**
  * @}
  */


/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Clear ADC error code (set it to no error code "HAL_ADC_ERROR_NONE").
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)

/**
  * @brief Simultaneously clear and set specific bits of the handle State.
  * @note  ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set.
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG

/**
  * @brief Verify the length of the scheduled conversions group.
  * @param __LENGTH__ number of programmed conversions.
  * @retval SET (__LENGTH__ is within the maximum number of possible programmable conversions)
  *         or RESET (__LENGTH__ is null or too large)
  */
#define IS_ADC_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1UL)) && ((__LENGTH__) <= (16UL)))

/**
  * @brief Verify the ADC data width setting.
  * @param __DATA_WIDTH__ programmed ADC resolution.
  * @retval SET (__DATA_WIDTH__ is a valid value) or RESET (__DATA_WIDTH__ is invalid)
  */
#define IS_ADC_DATAWIDTH(__DATA_WIDTH__) (((__DATA_WIDTH__) == ADC_DS_DATA_WIDTH_12_BIT) || \
                                          ((__DATA_WIDTH__) == ADC_DS_DATA_WIDTH_13_BIT) || \
                                          ((__DATA_WIDTH__) == ADC_DS_DATA_WIDTH_14_BIT) || \
                                          ((__DATA_WIDTH__) == ADC_DS_DATA_WIDTH_15_BIT) || \
                                          ((__DATA_WIDTH__) == ADC_DS_DATA_WIDTH_16_BIT)   )
/**
  * @brief Verify the ADC downsampler ratio setting.
  * @param __DATA_RATIO__ programmed ADC downsampler ratio.
  * @retval SET (__DATA_RATIO__ is a valid value) or RESET (__DATA_RATIO__ is invalid)
  */
#define IS_ADC_DATARATIO(__DATA_RATIO__) (((__DATA_RATIO__) == ADC_DS_RATIO_1)  || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_2)  || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_4)  || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_8)  || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_16) || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_32) || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_64) || \
                                          ((__DATA_RATIO__) == ADC_DS_RATIO_128)   )

/**
  * @brief Verify the ADC conversion type setting.
  * @param __CONVERSION_TYPE__ ADC conversion type.
  * @retval SET (__CONVERSION_TYPE__ is a valid value) or RESET (__CONVERSION_TYPE__ is invalid)
  */
#define IS_ADC_CONVERSIONTYPE(__CONVERSION_TYPE__) (((__CONVERSION_TYPE__) == ADC_CONVERSION_WITH_DS)  || \
                                                    ((__CONVERSION_TYPE__) == ADC_CONVERSION_WITH_DF)    )

/**
  * @brief Verify the ADC conversions overrun handling.
  * @param __OVR__ ADC conversions overrun handling.
  * @retval SET (__OVR__ is a valid value) or RESET (__OVR__ is invalid)
  */
#define IS_ADC_OVERRUN(__OVR__) (((__OVR__) == ADC_NEW_DATA_IS_LOST)  || \
                                 ((__OVR__) == ADC_NEW_DATA_IS_KEPT)    )

/**
  * @brief Verify the ADC sampling mode setting.
  * @param __SAMPLING_MODE__ programmed ADC sampling mode.
  * @retval SET (__SAMPLING_MODE__ is a valid value) or RESET (__SAMPLING_MODE__ is invalid)
  */
#define IS_ADC_SAMPLINGMODE(__SAMPLING_MODE__) (((__SAMPLING_MODE__) == ADC_SAMPLING_AT_START) || \
                                                ((__SAMPLING_MODE__) == ADC_SAMPLING_AT_END)     )

/**
  * @brief Verify the ADC calibration calibration point setting.
  * @param __POINT_NUMBER__ selected ADC calibration point number
  * @retval SET (__POINT_NUMBER__ is a valid value) or RESET (__POINT_NUMBER__ is invalid)
  */
#define IS_ADC_CALIBRATION_POINT(__POINT_NUMBER__) (((__POINT_NUMBER__) == ADC_CALIB_POINT_1) || \
                                                    ((__POINT_NUMBER__) == ADC_CALIB_POINT_2) || \
                                                    ((__POINT_NUMBER__) == ADC_CALIB_POINT_3) || \
                                                    ((__POINT_NUMBER__) == ADC_CALIB_POINT_4) || \
                                                    ((__POINT_NUMBER__) == ADC_CALIB_NONE)      )

/**
  * @brief Verify the ADC calibration calibration gain setting.
  * @param __GAIN__ selected ADC calibration gain
  * @retval SET (__GAIN__ is a valid value) or RESET (__GAIN__ is invalid)
  */
#define IS_ADC_CALIBRATION_GAIN(__GAIN__) ((__GAIN__ <= 0xFFFUL))

/**
  * @brief Verify the ADC calibration calibration offset setting.
  * @param __OFFSET__ selected ADC calibration offset
  * @retval SET (__OFFSET__ is a valid value) or RESET (__OFFSET__ is invalid)
  */
#define IS_ADC_CALIBRATION_OFFSET(__OFFSET__) ((__OFFSET__ <= 0xFFUL))

/**
  * @brief Verify the ADC conversions sampling time.
  * @param __SAMPLERATE__ ADC conversions sampling time.
  * @retval SET (__SAMPLING_TIME__ is a valid value) or RESET (__SAMPLING_TIME__ is invalid)
  */
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
#define IS_ADC_SAMPLERATE(__SAMPLERATE__)    (((__SAMPLERATE__) == ADC_SAMPLE_RATE_16)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_20)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_24)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_28)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_32)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_36)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_40)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_44)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_48)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_52)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_56)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_60)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_64)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_68)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_72)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_76)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_80)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_84)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_88)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_92)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_96)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_100) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_104) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_108) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_112) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_116) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_120) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_124) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_128) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_132) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_136) || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_140)  )
#else
#define IS_ADC_SAMPLERATE(__SAMPLERATE__)    (((__SAMPLERATE__) == ADC_SAMPLE_RATE_16)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_20)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_24)  || \
                                              ((__SAMPLERATE__) == ADC_SAMPLE_RATE_28)   )
#endif /* ADC_CONF_SAMPLE_RATE_MSB */

/**
  * @brief Verify the ADC bit inversion mode
  * @param  __OUTBIT_MODE__ ADC invert bit to bit data output.
  * @retval SET (__OUTBIT_MODE__ is valid) or RESET (__OUTBIT_MODE__ is invalid)
  */
#define IS_ADC_DATA_INVERT(__OUTBIT_MODE__)   (((__OUTBIT_MODE__) == ADC_DATA_INVERT_NONE) || \
                                               ((__OUTBIT_MODE__) == ADC_DATA_INVERT_DIFF) || \
                                               ((__OUTBIT_MODE__) == ADC_DATA_INVERT_SING) || \
                                               ((__OUTBIT_MODE__) == ADC_DATA_INVERT_BOTH)  )

/**
  * @brief Verify the ADC sequencer rank setting.
  * @param  __RANK__ selected position in sequencer.
  * @retval SET (__RANK__ is valid) or RESET (__RANK__ is invalid)
  */
#define IS_ADC_RANK(__RANK__) (((__RANK__) == ADC_RANK_1 ) || \
                               ((__RANK__) == ADC_RANK_2 ) || \
                               ((__RANK__) == ADC_RANK_3 ) || \
                               ((__RANK__) == ADC_RANK_4 ) || \
                               ((__RANK__) == ADC_RANK_5 ) || \
                               ((__RANK__) == ADC_RANK_6 ) || \
                               ((__RANK__) == ADC_RANK_7 ) || \
                               ((__RANK__) == ADC_RANK_8 ) || \
                               ((__RANK__) == ADC_RANK_9 ) || \
                               ((__RANK__) == ADC_RANK_10) || \
                               ((__RANK__) == ADC_RANK_11) || \
                               ((__RANK__) == ADC_RANK_12) || \
                               ((__RANK__) == ADC_RANK_13) || \
                               ((__RANK__) == ADC_RANK_14) || \
                               ((__RANK__) == ADC_RANK_15) || \
                               ((__RANK__) == ADC_RANK_16)   )

/**
  * @brief Verify the ADC channel voltage range setting.
  * @param  __VOLTAGE_RANGE__ selected voltage range.
  * @retval SET (__VOLTAGE_RANGE_ is valid) or RESET (__VOLTAGE_RANGE_ is invalid)
  */
#define IS_ADC_VOLTAGE_RANGE(__VOLTAGE_RANGE__) (((__VOLTAGE_RANGE__) == ADC_VIN_RANGE_1V2) || \
                                                 ((__VOLTAGE_RANGE__) == ADC_VIN_RANGE_2V4) || \
                                                 ((__VOLTAGE_RANGE__) == ADC_VIN_RANGE_3V6)   )

/**
  * @brief Verify the ADC channel setting.
  * @param  __CHANNEL__ selected ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_VINM0)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINM1)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINM2)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINM3)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP0)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP1)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP2)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP3)       || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP0_VINM0) || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP1_VINM1) || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP2_VINM2) || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VINP3_VINM3) || \
                                     ((__CHANNEL__) == ADC_CHANNEL_VBAT)        || \
                                     ((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)    )

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief Verify the ADC event setting.
  * @param  __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_IRQ_FLAG_OVRFL) || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_OVRDF) || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_OVRDS) || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_AWD1)  || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_EOS)   || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_EODF)  || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_EODS)    )
#else
/**
  * @brief Verify the ADC event setting.
  * @param  __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_IRQ_FLAG_OVRDS) || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_AWD1)  || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_EOS)   || \
                                      ((__EVENT__) == ADC_IRQ_FLAG_EODS)    )
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @brief Verify the ADC watchdog channel setting.
  * @param  __CHANNEL__ ADC channel selection monitored by watchdog.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_AWD_CHANNEL(__CHANNEL__) \
  (((__CHANNEL__) != 0UL)  \
   && (((__CHANNEL__) & ~(ADC_AWD_CH_VINM0   | ADC_AWD_CH_VINM1   | ADC_AWD_CH_VINM2    | ADC_AWD_CH_VINM3      | \
                          ADC_AWD_CH_VINP0   | ADC_AWD_CH_VINP1   | ADC_AWD_CH_VINP2    | ADC_AWD_CH_VINP3      | \
                          ADC_AWD_CH_MICROM  | ADC_AWD_CH_MICROP  | ADC_AWD_CH_VBAT     | ADC_AWD_CH_TEMPSENSOR | \
                          ADC_AWD_CH_GND_NEG | ADC_AWD_CH_GND_POS | ADC_AWD_CH_VDDA_NEG | ADC_AWD_CH_VDDA_POS ))  \
       == 0UL))

/**
  * @brief Verify the ADC watchdog event setting.
  * @param  __EVENT__ ADC watchdog event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_AWD_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_AWD_EVENT_POLLING) || \
                                          ((__EVENT__) == ADC_AWD_EVENT_INTERRUPT) )

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief Verify the ADC Decimation filter dynamic range setting.
  * @param  __RANGE__ Decimation filter selected dynamic range.
  * @retval SET (__RANGE__ is valid) or RESET (__RANGE__ is invalid)
  */
#define IS_ADC_DF_DYNAMIC_RANGE(__RANGE__) (((__RANGE__) == ADC_DF_DYN_RANGE_FULL) || \
                                            ((__RANGE__) == ADC_DF_DYN_RANGE_HALF) )

/**
  * @brief Verify the ADC Decimation filter data format setting.
  * @param  __SIGN__ Selected data sign.
  * @retval SET (__SIGN__ is valid) or RESET (__SIGN__ is invalid)
  */
#define IS_ADC_DF_DATA_FORMAT(__SIGN__) (((__SIGN__) == ADC_DF_DATA_FORMAT_SIGNED) || \
                                         ((__SIGN__) == ADC_DF_DATA_FORMAT_UNSIGNED) )

/**
  * @brief Verify the ADC Decimation filter CIC Filter factor format setting.
  * @param  __FACTOR__ Selected Decimation filter CIC Filter factor format.
  * @retval SET (__FACTOR__ is valid) or RESET (__FACTOR__ is invalid)
  */
#define IS_ADC_DF_CIC_DECIMATOR_HALF_FACTOR(__FACTOR__) (((__FACTOR__) == ADC_DF_CIC_DECIMATOR_FACTOR_HALF) || \
                                                         ((__FACTOR__) == ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER) )

/**
  * @brief Verify the ADC Decimation filter CIC Filter factor setting.
  * @param  __FACTOR__ Selected CIC Filter factor.
  * @retval SET (__FACTOR__ is valid) or RESET (__FACTOR__ is invalid)
  */
#define IS_ADC_DF_CIC_DECIMATOR_FACTOR(__FACTOR__) ((__FACTOR__) <= 0x3FUL)

/**
  * @brief Verify the ADC Decimation filter microphone channel setting.
  * @param  __CHANNEL__ ADC microphone channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_DF_MICROPHONE_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_DF_MIC_CH_LEFT) || \
                                                   ((__CHANNEL__) == ADC_DF_MIC_CH_RIGHT)  )

/**
  * @brief Verify the ADC PDM clock divider setting.
  * @param  __CLOCK_DIV__  ADC PDM clock divider.
  * @retval SET (__CLOCK_DIV__ is valid) or RESET (__CLOCK_DIV__ is invalid)
  */
#define IS_ADC_PDM_CLOCK_DIVIDER(__CLOCK_DIV__) (((__CLOCK_DIV__) == ADC_PDM_DIV_10) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_11) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_12) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_13) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_14) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_15) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_16) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_17) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_18) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_19) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_20) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_21) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_22) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_23) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_24) || \
                                                 ((__CLOCK_DIV__) == ADC_PDM_DIV_25)   )

/**
  * @brief Verify the ADC Programmable Gain Amplifier voltage bias setting.
  * @param  __BIAS__  ADC PGA voltage bias.
  * @retval SET (__BIAS__ is valid) or RESET (__BIAS__ is invalid)
  */
#define IS_ADC_PGA_BIAS(__BIAS__) (((__BIAS__) == ADC_PGA_BIAS_050_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_055_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_060_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_065_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_070_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_075_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_080_BAT) || \
                                   ((__BIAS__) == ADC_PGA_BIAS_090_BAT)   )

/**
  * @brief Verify the ADC Programmable Gain Amplifier gain setting.
  * @param  __GAIN__  ADC PGA gain.
  * @retval SET (__GAIN__ is valid) or RESET (__GAIN__ is invalid)
  */
#define IS_ADC_PGA_GAIN(__GAIN__) (((__GAIN__) == ADC_PGA_GAIN_06_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_09_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_12_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_15_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_18_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_21_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_24_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_27_DB) || \
                                   ((__GAIN__) == ADC_PGA_GAIN_30_DB)   )

/**
  * @brief Verify the ADC Occasional mode source channel setting.
  * @param  __CHANNEL__  selected ADC Occasional mode source channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_OCM_SOURCE(__CHANNEL__) (((__CHANNEL__) == ADC_OCM_SRC_VBAT) || \
                                        ((__CHANNEL__) == ADC_OCM_SRC_TEMP)   )

/**
  * @brief Verify the Programmable Gain Amplifier voltage bias precharge delay.
  * @param  __DELAY__  ADC PGA voltage bias precharge delay (microseconds).
  * @retval SET (__DELAY__ is valid) or RESET (__DELAY__ is invalid)
  */
#define IS_ADC_PGA_VBIAS_PRECHARGE_DELAY(__DELAY__) ((__DELAY__) <= 1044480UL)
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @brief Verify the LDO stabilization delay.
  * @param  __DELAY__  LDO stabilization delay (microseconds).
  * @retval SET (__DELAY__ is valid) or RESET (__DELAY__ is invalid)
  */
#define IS_ADC_LDO_DELAY(__DELAY__) ((__DELAY__) <= 1020UL)

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_HAL_EM_HANDLE_IT_FLAG HAL ADC macro to manage HAL ADC handle,
  *           IT and flags.
  * @{
  */

/** @brief  Reset ADC handle state.
  * @param __HANDLE__ ADC handle
  * @retval None
  */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)     \
  do                                                 \
  {                                                  \
    (__HANDLE__)->State = HAL_ADC_STATE_RESET;       \
    (__HANDLE__)->MspInitCallback = NULL;            \
    (__HANDLE__)->MspDeInitCallback = NULL;          \
  } while(0)
#else
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)     \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */


/**
  * @brief Enable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturated interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD1   ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOC    ADC End of conversion interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)     LL_ADC_EnableIT((__HANDLE__)->Instance, __INTERRUPT__)


/**
  * @brief Disable ADC interrupt.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC Interrupt
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturated interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD1   ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOC    ADC End of conversion interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)    LL_ADC_DisableIT((__HANDLE__)->Instance, __INTERRUPT__)


/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__ ADC handle
  * @param __INTERRUPT__ ADC interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg @ref ADC_IRQ_EN_OVRFL  ADC Decimation Filter saturated interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_EN_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_EN_AWD1   ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_EN_EOC    ADC End of conversion interrupt source
  *            @arg @ref ADC_IRQ_EN_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_EN_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_EN_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    LL_ADC_IsEnabledIT((__HANDLE__)->Instance, __INTERRUPT__)


/**
  * @brief Check whether the specified ADC flag is set or not.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be one of the following values:
  *            @arg @ref ADC_IRQ_FLAG_OVRFL  ADC Decimation Filter saturated interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_FLAG_AWD1   ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOC    ADC End of conversion interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval State of flag (TRUE or FALSE).
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)    LL_ADC_IsActiveFlag((__HANDLE__)->Instance, __FLAG__)


/**
  * @brief Clear the specified ADC flag.
  * @param __HANDLE__ ADC handle
  * @param __FLAG__ ADC flag
  *        This parameter can be a combination of the following values:
  *            @arg @ref ADC_IRQ_FLAG_OVRFL  ADC Decimation Filter saturated interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDF  ADC Decimation Filter overrung interrupt source
  *            @arg @ref ADC_IRQ_FLAG_OVRDS  ADC Down Sampler overrun interrupt source
  *            @arg @ref ADC_IRQ_FLAG_AWD1   ADC Watchdog alert interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOC    ADC End of conversion interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EOS    ADC End of conversion of a sequence interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODF   ADC End of conversion from Decimation Filter interrupt source
  *            @arg @ref ADC_IRQ_FLAG_EODS   ADC End of conversion from Down Sampler interrupt source
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)    LL_ADC_ClearActiveFlags((__HANDLE__)->Instance, __FLAG__)


/**
  * @}
  */

/** @defgroup ADC_HAL_EM_HELPER_MACRO HAL ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_VINM0
  *         @arg @ref ADC_CHANNEL_VINM1
  *         @arg @ref ADC_CHANNEL_VINM2
  *         @arg @ref ADC_CHANNEL_VINM3
  *         @arg @ref ADC_CHANNEL_VINP0
  *         @arg @ref ADC_CHANNEL_VINP1
  *         @arg @ref ADC_CHANNEL_VINP2
  *         @arg @ref ADC_CHANNEL_VINP3
  *         @arg @ref ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref ADC_CHANNEL_VINP3_VINM3
  *         @arg @ref ADC_CHANNEL_VBAT
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel
  *         (channel connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define __HAL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                             \
  __LL_ADC_IS_CHANNEL_INTERNAL((__CHANNEL__))

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_WIDTH_CURRENT__ Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @param  __ADC_WIDTH_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data to the requested resolution
  */
#define __HAL_ADC_CONVERT_DATA_RESOLUTION(__DATA__,\
                                          __ADC_WIDTH_CURRENT__,\
                                          __ADC_WIDTH_TARGET__)\
__LL_ADC_CONVERT_DATA_RESOLUTION((__DATA__),                                   \
                                 (__ADC_WIDTH_CURRENT__),                      \
                                 (__ADC_WIDTH_TARGET__))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref ADC_VIN_RANGE_3V6
  *         @arg @ref ADC_VIN_RANGE_2V4
  *         @arg @ref ADC_VIN_RANGE_1V2
  * @param  __ADC_DATA__ ADC conversion data (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __HAL_ADC_CALC_DATA_TO_VOLTAGE(__INPUT_VOLTAGE_RANGE__,\
                                       __ADC_DATA__,\
                                       __ADC_WIDTH__)\
__LL_ADC_CALC_DATA_TO_VOLTAGE((__INPUT_VOLTAGE_RANGE__),                       \
                              (__ADC_DATA__),                                  \
                              (__ADC_WIDTH__))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value)
  *         in differential ended mode.
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref ADC_VIN_RANGE_3V6
  *         @arg @ref ADC_VIN_RANGE_2V4
  *         @arg @ref ADC_VIN_RANGE_1V2
  * @param  __ADC_DATA__ ADC conversion data (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __HAL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(__INPUT_VOLTAGE_RANGE__,\
                                            __ADC_DATA__,\
                                            __ADC_WIDTH__)\
__LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE((__INPUT_VOLTAGE_RANGE__),                  \
                                   (__ADC_DATA__),                             \
                                   (__ADC_WIDTH__))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data of internal
  *                                 temperature sensor (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @retval Temperature (unit: degree Celsius)
  */
#define __HAL_ADC_CALC_TEMPERATURE(__TEMPSENSOR_ADC_DATA__,\
                                   __ADC_WIDTH__)\
__LL_ADC_CALC_TEMPERATURE((__TEMPSENSOR_ADC_DATA__),                           \
                          (__ADC_WIDTH__))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor typical values
  *         (refer to device datasheet).
  * @param  __TEMPSENSOR_ADC_DATA__      ADC conversion data of internal temperature sensor (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref ADC_DS_DATA_WIDTH_16_BIT
  * @retval Temperature (unit: degree Celsius)
  */
#define __HAL_ADC_CALC_TEMPERATURE_TYP_PARAMS(__TEMPSENSOR_ADC_DATA__,\
                                              __ADC_WIDTH__)\
__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS((__TEMPSENSOR_ADC_DATA__),                \
                                     (__ADC_WIDTH__))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @brief    Initialization and Configuration functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void              HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void              HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID,
                                           pADC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group2
  * @brief    IO operation functions
  * @{
  */

/* IO operation functions  *****************************************************/

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, const uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t HAL_ADC_GetValue(const ADC_HandleTypeDef *hadc);
uint32_t HAL_ADC_GetValue_DF(const ADC_HandleTypeDef *hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, const ADC_ChannelConfTypeDef *ConfigChannel);
HAL_StatusTypeDef HAL_ADC_DFConfig(ADC_HandleTypeDef *hadc, const ADC_DFConfTypeDef *ConfigDF);
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, const ADC_AnalogWDGConfTypeDef *ConfigWatchdog);

/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group4 Microphone Interface Control functions
  * @{
  */
HAL_StatusTypeDef HAL_ADC_SetMicrophoneChannel(ADC_HandleTypeDef *hadc, uint32_t MicrophoneChannel);

HAL_StatusTypeDef HAL_ADC_PDMConfig(ADC_HandleTypeDef *hadc, const ADC_PDMConfTypeDef *ConfigPDM);
HAL_StatusTypeDef HAL_ADC_PDMStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PDMStop(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_PGAConfig(ADC_HandleTypeDef *hadc, const ADC_PGAConfTypeDef *ConfigPGA);
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group5 Occasional Mode Control functions
  * @{
  */
HAL_StatusTypeDef HAL_ADC_SetOccasionalSource(ADC_HandleTypeDef *hadc, uint32_t Source);

HAL_StatusTypeDef HAL_ADC_StartOccasionalMode(ADC_HandleTypeDef *hadc);
/**
  * @}
  */

/**
  * @addtogroup ADC_Exported_Functions_Group6 Analog Timing Control functions
  * @{
  */
HAL_StatusTypeDef HAL_ADC_SMPSSyncEnable(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_SMPSSyncDisable(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_VBiasPrechargeDelayConfig(ADC_HandleTypeDef *hadc, uint32_t Delay_us);
HAL_StatusTypeDef HAL_ADC_LDODelayConfig(ADC_HandleTypeDef *hadc, uint32_t Delay_us);
/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group7
  * @{
  */

uint32_t HAL_ADC_GetState(const ADC_HandleTypeDef *hadc);
uint32_t HAL_ADC_GetError(const ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup ADC_Private_Functions ADC Private Functions
  * @{
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


#endif /* STM32WB0x_HAL_ADC_H */
