/**
  ******************************************************************************
  * @file    stm32wb0x_ll_adc.h
  * @author  GPM Application Team
  * @brief   Header file of ADC LL module.
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
#ifndef STM32WB0x_LL_ADC_H
#define STM32WB0x_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cpluplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (ADC1)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Internal mask for ADC sequencer:                                           */
/* To select into literal LL_ADC_RANK_x the relevant bits for:                */
/* - sequencer register offset                                                */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC sequencer configuration */
/* (offset placed into a spare area of literal definition)  */
#define ADC_SEQ_1_REGOFFSET                 (0x00000000UL)
#define ADC_SEQ_2_REGOFFSET                 (0x00000100UL)

#define ADC_SEQ_X_REGOFFSET_MASK        (ADC_SEQ_1_REGOFFSET | ADC_SEQ_2_REGOFFSET)
#define ADC_SEQ_X_REGOFFSET_POS         (8UL) /* Position of bits ADC_SEQ_x_REGOFFSET in ADC_REG_SEQ_X_REGOFFSET_MASK*/
#define ADC_RANK_ID_SEQ_X_MASK          (0xFFUL)

/* Definition of ADC sequencer bits information to be inserted  */
/* into ADC sequencer ranks literals definition.                */
#define ADC_RANK_1_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ0_Pos)
#define ADC_RANK_2_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ1_Pos)
#define ADC_RANK_3_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ2_Pos)
#define ADC_RANK_4_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ3_Pos)
#define ADC_RANK_5_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ4_Pos)
#define ADC_RANK_6_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ5_Pos)
#define ADC_RANK_7_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ6_Pos)
#define ADC_RANK_8_SEQ_X_BITOFFSET_POS   (ADC_SEQ_1_SEQ7_Pos)
#define ADC_RANK_9_SEQ_X_BITOFFSET_POS   (ADC_SEQ_2_SEQ8_Pos)
#define ADC_RANK_10_SEQ_X_BITOFFSET_POS   (ADC_SEQ_2_SEQ9_Pos)
#define ADC_RANK_11_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ10_Pos)
#define ADC_RANK_12_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ11_Pos)
#define ADC_RANK_13_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ12_Pos)
#define ADC_RANK_14_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ13_Pos)
#define ADC_RANK_15_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ14_Pos)
#define ADC_RANK_16_SEQ_X_BITOFFSET_POS  (ADC_SEQ_2_SEQ15_Pos)

static const uint8_t ADC_CHANNEL_SWITCH_POS_LUT[12] =
{
  (uint8_t)(ADC_SWITCH_SE_VIN_0_Pos),      /*!< ADC_SWITCH_SE_VIN_0 Channel ADC_INM0 */
  (uint8_t)(ADC_SWITCH_SE_VIN_1_Pos),      /*!< ADC_SWITCH_SE_VIN_1 Channel ADC_INM1 */
  (uint8_t)(ADC_SWITCH_SE_VIN_2_Pos),      /*!< ADC_SWITCH_SE_VIN_2 Channel ADC_INM2 */
  (uint8_t)(ADC_SWITCH_SE_VIN_3_Pos),      /*!< ADC_SWITCH_SE_VIN_3 Channel ADC_INM3 */
  (uint8_t)(ADC_SWITCH_SE_VIN_4_Pos),      /*!< ADC_SWITCH_SE_VIN_4 Channel ADC_INP1 */
  (uint8_t)(ADC_SWITCH_SE_VIN_5_Pos),      /*!< ADC_SWITCH_SE_VIN_5 Channel ADC_INP2 */
  (uint8_t)(ADC_SWITCH_SE_VIN_6_Pos),      /*!< ADC_SWITCH_SE_VIN_6 Channel ADC_INP3 */
  (uint8_t)(ADC_SWITCH_SE_VIN_7_Pos),      /*!< ADC_SWITCH_SE_VIN_7 Channel ADC_INP4 */
  (uint8_t)(ADC_SWITCH_SE_VIN_0_Pos),      /*!< ADC_SWITCH_SE_VIN_0 Channel ADC_INP1 - ADC_INM1 */
  (uint8_t)(ADC_SWITCH_SE_VIN_1_Pos),      /*!< ADC_SWITCH_SE_VIN_1 Channel ADC_INP2 - ADC_INM2 */
  (uint8_t)(ADC_SWITCH_SE_VIN_2_Pos),      /*!< ADC_SWITCH_SE_VIN_2 Channel ADC_INP3 - ADC_INM3 */
  (uint8_t)(ADC_SWITCH_SE_VIN_3_Pos),      /*!< ADC_SWITCH_SE_VIN_3 Channel ADC_INP4 - ADC_INM4 */
};

#if defined(STM32WB09) || defined(STM32WB05)
#define TEMPSENSOR_TCK_ADDR               ((uint32_t*) (0x10001E5CUL)) /* Internal temperature sensor, address of
                                           parameter TCK: TCK is the chuck temperature in 0.1DegC (e.g. 30DegC = 300)*/
#else
#define TEMPSENSOR_C85_ADDR               ((uint32_t*) (0x10001E68UL)) /* Internal temperature sensor, address of
                                           parameter C85: On this STM32 series, temperature sensor ADC raw data
                                           acquired at temperature 85 DegC. */
#define TEMPSENSOR_C85_TEMP                (85UL)                      /* Internal temperature sensor, temperature
                                           at which temperature sensor has been calibrated in production for data
                                           into TEMPSENSOR_C85_ADDR (tolerance: +-5 DegC) (unit: DegC). */
#endif /* defined(STM32WB09) || defined(STM32WB05) */
#define TEMPSENSOR_C30_ADDR               ((uint32_t*) (0x10001E60UL)) /* Internal temperature sensor, address of
                                           parameter C30: On this STM32 series, temperature sensor ADC raw data
                                           acquired at temperature 30 DegC. */

#define TEMPSENSOR_C30_TEMP                (30UL)                      /* Internal temperature sensor, temperature
                                           at which temperature sensor has been calibrated in production for data
                                           into TEMPSENSOR_C30_ADDR (tolerance: +-5 DegC) (unit: DegC). */

/** @defgroup ADC_LL_CALIB_ADDRESS ADC calibration points location
  * @brief    Defines the memory address of the calibration points.
  * @{
  */
#define ADC_LAYOUT_ID                    (0x10001EFCUL)
#define ADC_CALIB_ADDRESS_VINPX_3V6      (0x10001E20UL)
#define ADC_CALIB_ADDRESS_VINMX_3V6      (0x10001E1CUL)
#define ADC_CALIB_ADDRESS_VINDIFF_3V6    (0x10001E18UL)
#define ADC_CALIB_ADDRESS_VINPX_2V4      (0x10001E14UL)
#define ADC_CALIB_ADDRESS_VINMX_2V4      (0x10001E10UL)
#define ADC_CALIB_ADDRESS_VINDIFF_2V4    (0x10001E0CUL)
#define ADC_CALIB_ADDRESS_VINPX_1V2      (0x10001E08UL)
#define ADC_CALIB_ADDRESS_VINMX_1V2      (0x10001E04UL)
#define ADC_CALIB_ADDRESS_VINDIFF_1V2    (0x10001E00UL)

/**
  * @}
  */

/* Uncomment this symbol to use the version with floating point of the conversion functions */
#define BLE_ADC_OUTPUT_FLOAT

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */


/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_ES_INIT ADC Exported Init structure
  * @{
  */

/**
  * @brief Structure definition with common setting for the ADC.
  */
typedef struct
{
  FunctionalState ContinuousConvMode;  /*!< Specify whether the conversion is performed in single mode (one conversion)
                                            or continuous mode for ADC group regular, after the first ADC conversion
                                            start trigger occurred (software start or external trigger). This parameter
                                            can be set to ENABLE or DISABLE.
                                            This feature can be modified afterwards using unitary function
                                            @ref LL_ADC_ContinuousModeEnable() or @ref LL_ADC_ContinuousModeDisable().*/

  uint32_t    SequenceLength;          /*!< Specify the length of the conversion sequence.
                                            This parameter must be a number between Min_Data = 1 and Max_Data = 16.
                                            This feature can be modified afterwards using unitary function
                                            @ref LL_ADC_SetSequenceLength(). */

  uint32_t    SamplingMode;            /*!< Specifies the input sampling mode.
                                            This parameter can be a value of @ref ADC_LL_SAMPLING_METHOD.
                                            This feature can be modified afterwards using unitary function
                                            @ref LL_ADC_SetInputSamplingMode(). */

  uint32_t    SampleRate;              /*!< Specify the ADC sample rate.
                                            This parameter can be a value of @ref ADC_LL_SAMPLE_RATE.
                                            This feature can be modified afterwards using unitary function
                                            @ref LL_ADC_SetSampleRate(). */

  uint32_t    Overrun;                 /*!< Specifies the overrung policy applied to the data.
                                            This parameter can be a value of @ref ADC_LL_OVERRUN_CONFIG.
                                            This feature can be modified afterwards using unitary function
                                            @ref LL_ADC_SetOverrunDS(). */
} LL_ADC_InitTypeDef;


/**
  * @brief  Structure definition containing the input voltage range
  *         for each type of ADC input channel.
  */
typedef struct
{
  uint32_t InputVinm0_Vinp0Vinm0;     /*!< Set the input voltage range for single VINM0 or differential (VINP0 - VINM0).
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinm1_Vinp1Vinm1;     /*!< Set the input voltage range for single VINM1 or differential (VINP1 - VINM1).
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange().  */

  uint32_t InputVinm2_Vinp2Vinm2;     /*!< Set the input voltage range for single VINM2 or differential (VINP2 - VINM2).
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinm3_Vinp3Vinm3;     /*!< Set the input voltage range for single VINM3 or differential (VINP3 - VINM3).
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinp0;                /*!< Set the input voltage range for single VINP0.
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinp1;                /*!< Set the input voltage range for single VINP1.
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinp2;                /*!< Set the input voltage range for single VINP2.
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

  uint32_t InputVinp3;                /*!< Set the input voltage range for single VINP3.
                                           This parameter can be a value of @ref ADC_LL_INPUT_VOLTAGE_RANGE
                                           This feature can be modified afterwards using unitary function
                                           @ref LL_ADC_SetChannelVoltageRange(). */

} LL_ADC_VoltRangeInitTypeDef;


/**
  * @brief  Structure definition with the input channel entry
  *         for each element of the conversion sequence.
  */
typedef struct
{
  uint32_t ChannelForSeq0;              /*!< Set the channel number code for the 1st conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq1;              /*!< Set the channel number code for the 2nd conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq2;              /*!< Set the channel number code for the 3rd conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq3;              /*!< Set the channel number code for the 4th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq4;              /*!< Set the channel number code for the 5th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq5;              /*!< Set the channel number code for the 6th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq6;              /*!< Set the channel number code for the 7th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq7;              /*!< Set the channel number code for the 8th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq8;              /*!< Set the channel number code for the 9th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq9;              /*!< Set the channel number code for the 10th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq10;             /*!< Set the channel number code for the 11th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq11;             /*!< Set the channel number code for the 12th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq12;             /*!< Set the channel number code for the 13th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq13;             /*!< Set the channel number code for the 14th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq14;             /*!< Set the channel number code for the 15th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

  uint32_t ChannelForSeq15;             /*!< Set the channel number code for the 16th conversion of the sequence.
                                             This parameter can be a value of @ref ADC_LL_CHANNEL
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_SetSequencerRanks(). */

} LL_ADC_SequenceInitTypeDef;

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/


/** @defgroup ADC_LL_Exported_Constants ADC Exported Constants
  * @{
  */


/** @defgroup ADC_LL_SAMPLING_METHOD  ADC input sampling method definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetInputSamplingMode()
  *           and @ref LL_ADC_GetInputSamplingMode()
  * @{
  */

#define LL_ADC_SAMPLING_AT_START    (0x00000000UL)             /*!< Sampling phase starts only at conversion start and
                                                                    sampling time is 125ns regardless of the sampling
                                                                    period (default). */
#define LL_ADC_SAMPLING_AT_END      (ADC_CONF_ADC_CONT_1V2)    /*!< Sampling phase starts after end of
                                                                    conversion, and stops upon trigger event (Also known
                                                                    as Bulb sampling mode).
                                                                    Sampling time is a function of the sampling period
                                                                    (Sample rate). */

/**
  * @}
  */


/** @defgroup ADC_LL_OVERRUN_CONFIG ADC overrun configuration definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetOverrunDF(), @ref LL_ADC_GetOverrunDF(),
  *           @ref LL_ADC_SetOverrunDS(), and @ref LL_ADC_GetOverrunDS()
  * @{
  */

#define LL_ADC_NEW_DATA_IS_LOST    (0x00000000UL)                /*!< Previous data is preserved, new data is lost.   */
#define LL_ADC_NEW_DATA_IS_KEPT    (ADC_CONF_OVR_DS_CFG)         /*!< Previous data is overwritten, new data is kept. */

/**
  * @}
  */

/** @defgroup ADC_LL_SAMPLE_RATE ADC sample rate definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetSampleRate()
  *           and @ref LL_ADC_GetSampleRate()
  *           The  ADC conversion rate is: System clock / (16 + 16*SAMPLE_RATE_MSB + 4*SAMPLE_RATE)
  * @{
  */
#define LL_ADC_SAMPLE_RATE_16  (0x0UL)                                     /*!< ADC conversion rate at F_ADC_CLK / 16 */
#define LL_ADC_SAMPLE_RATE_20  (0x1UL << ADC_CONF_SAMPLE_RATE_Pos)         /*!< ADC conversion rate at F_ADC_CLK / 20 */
#define LL_ADC_SAMPLE_RATE_24  (0x2UL << ADC_CONF_SAMPLE_RATE_Pos)         /*!< ADC conversion rate at F_ADC_CLK / 24 */
#define LL_ADC_SAMPLE_RATE_28  (0x3UL << ADC_CONF_SAMPLE_RATE_Pos)         /*!< ADC conversion rate at F_ADC_CLK / 28 */

#if defined(ADC_CONF_SAMPLE_RATE_MSB)
#define LL_ADC_SAMPLE_RATE_32       (0x1UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 32 */
#define LL_ADC_SAMPLE_RATE_36       (0x1UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 36 */
#define LL_ADC_SAMPLE_RATE_40       (0x1UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 40 */
#define LL_ADC_SAMPLE_RATE_44       (0x1UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 44 */
#define LL_ADC_SAMPLE_RATE_48       (0x2UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 48 */
#define LL_ADC_SAMPLE_RATE_52       (0x2UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 52 */
#define LL_ADC_SAMPLE_RATE_56       (0x2UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 56 */
#define LL_ADC_SAMPLE_RATE_60       (0x2UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 60 */
#define LL_ADC_SAMPLE_RATE_64       (0x3UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 64 */
#define LL_ADC_SAMPLE_RATE_68       (0x3UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 68 */
#define LL_ADC_SAMPLE_RATE_72       (0x3UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 72 */
#define LL_ADC_SAMPLE_RATE_76       (0x3UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 76 */
#define LL_ADC_SAMPLE_RATE_80       (0x4UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 80 */
#define LL_ADC_SAMPLE_RATE_84       (0x4UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 84 */
#define LL_ADC_SAMPLE_RATE_88       (0x4UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 88 */
#define LL_ADC_SAMPLE_RATE_92       (0x4UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 92 */
#define LL_ADC_SAMPLE_RATE_96       (0x5UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 96  */
#define LL_ADC_SAMPLE_RATE_100      (0x5UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 100 */
#define LL_ADC_SAMPLE_RATE_104      (0x5UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 104 */
#define LL_ADC_SAMPLE_RATE_108      (0x5UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 108 */
#define LL_ADC_SAMPLE_RATE_112      (0x6UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 112 */
#define LL_ADC_SAMPLE_RATE_116      (0x6UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 116 */
#define LL_ADC_SAMPLE_RATE_120      (0x6UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 120 */
#define LL_ADC_SAMPLE_RATE_124      (0x6UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 124 */
#define LL_ADC_SAMPLE_RATE_128      (0x7UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x0UL)                             /*!< ADC
                                    conversion rate at F_ADC_CLK / 128 */
#define LL_ADC_SAMPLE_RATE_132      (0x7UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x1UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 132 */
#define LL_ADC_SAMPLE_RATE_136      (0x7UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x2UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 136 */
#define LL_ADC_SAMPLE_RATE_140      (0x7UL << ADC_CONF_SAMPLE_RATE_MSB_Pos | 0x3UL << ADC_CONF_SAMPLE_RATE_Pos) /*!< ADC
                                    conversion rate at F_ADC_CLK / 140 */
#endif /* ADC_CONF_SAMPLE_RATE_MSB */
/**
  * @}
  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_LL_OP_MODE ADC operation modes definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetADCMode() and @ref LL_ADC_GetADCMode()
  * @{
  */

#define LL_ADC_OP_MODE_AUDIO    (0x1UL << ADC_CONF_OP_MODE_Pos)  /*!< ADC operation mode AUDIO */
#define LL_ADC_OP_MODE_ADC      (0x2UL << ADC_CONF_OP_MODE_Pos)  /*!< ADC operation mode ADC   */
#define LL_ADC_OP_MODE_FULL     (0x3UL << ADC_CONF_OP_MODE_Pos)  /*!< ADC operation Full mode  */

/**
  * @}
  */

/** @defgroup ADC_LL_OCM_SOURCE ADC occasional mode source definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetOccasionalConversionSource()
  *           and @ref LL_ADC_GetOccasionalConversionSource()
  * @{
  */

#define LL_ADC_OCM_SRC_VBAT    (0UL)  /*!< ADC occasional mode source VBAT               */
#define LL_ADC_OCM_SRC_TEMP    (1UL)  /*!< ADC occasional mode source temperature sensor */

/**
  * @}
  */

/** @defgroup ADC_LL_PGA_BIAS ADC microphone bias voltage definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetMicrophonePGABias()
  *           and @ref LL_ADC_GetMicrophonePGABias()
  * @{
  */

#define LL_ADC_PGA_BIAS_050_BAT   (0x00000000UL)                       /*!< Set the microphone bias voltage at 0.50 V */
#define LL_ADC_PGA_BIAS_055_BAT   (0x1UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.55 V */
#define LL_ADC_PGA_BIAS_060_BAT   (0x2UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.60 V */
#define LL_ADC_PGA_BIAS_065_BAT   (0x3UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.65 V */
#define LL_ADC_PGA_BIAS_070_BAT   (0x4UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.70 V */
#define LL_ADC_PGA_BIAS_075_BAT   (0x5UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.75 V */
#define LL_ADC_PGA_BIAS_080_BAT   (0x6UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.80 V */
#define LL_ADC_PGA_BIAS_090_BAT   (0x7UL << ADC_PGA_CONF_PGA_BIAS_Pos) /*!< Set the microphone bias voltage at 0.90 V */

/**
  * @}
  */


/** @defgroup ADC_LL_PGA_GAIN ADC microphone gain definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetMicrophonePGAGain()
  *           and @ref LL_ADC_GetMicrophonePGAGain()
  * @{
  */

#define LL_ADC_PGA_GAIN_00_DB   (0x00000000UL)  /*!< Set the microphone gain at 0 dB  */
#define LL_ADC_PGA_GAIN_03_DB   (0x00000001UL)  /*!< Set the microphone gain at 3 dB  */
#define LL_ADC_PGA_GAIN_06_DB   (0x00000002UL)  /*!< Set the microphone gain at 6 dB */
#define LL_ADC_PGA_GAIN_09_DB   (0x00000003UL)  /*!< Set the microphone gain at 9 dB */
#define LL_ADC_PGA_GAIN_12_DB   (0x00000004UL)  /*!< Set the microphone gain at 12 dB */
#define LL_ADC_PGA_GAIN_15_DB   (0x00000005UL)  /*!< Set the microphone gain at 15 dB */
#define LL_ADC_PGA_GAIN_18_DB   (0x00000006UL)  /*!< Set the microphone gain at 18 dB */
#define LL_ADC_PGA_GAIN_21_DB   (0x00000007UL)  /*!< Set the microphone gain at 21 dB */
#define LL_ADC_PGA_GAIN_24_DB   (0x00000008UL)  /*!< Set the microphone gain at 24 dB */
#define LL_ADC_PGA_GAIN_27_DB   (0x00000009UL)  /*!< Set the microphone gain at 27 dB */
#define LL_ADC_PGA_GAIN_30_DB   (0x0000000AUL)  /*!< Set the microphone gain at 30 dB */

/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_LL_INPUT_VOLTAGE_RANGE ADC input voltage range definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetChannelVoltageRange()
  *           and @ref LL_ADC_GetChannelVoltageRange()
  * @{
  */

#define LL_ADC_VIN_RANGE_1V2    (0UL)  /*!< ADC input voltage range up to 1.2 V */
#define LL_ADC_VIN_RANGE_2V4    (2UL)  /*!< ADC input voltage range up to 2.4 V */
#define LL_ADC_VIN_RANGE_3V6    (3UL)  /*!< ADC input voltage range up to 3.6 V */

/**
  * @}
  */


/** @defgroup ADC_LL_DEFAULT_RANGE_VALUE ADC default range value definitions
  * @brief    It defines the parameters used as default range value
  * @{
  */

#define LL_ADC_DEFAULT_RANGE_VALUE_1V2    (0xFFFUL)  /*!< ADC default range value up to 1.2 V */
#define LL_ADC_DEFAULT_RANGE_VALUE_2V4    (0x7FFUL)  /*!< ADC default range value up to 2.4 V */
#define LL_ADC_DEFAULT_RANGE_VALUE_3V6    (0x555UL)  /*!< ADC default range value up to 3.6 V */

/**
  * @}
  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_LL_DF_DYN_RANGE ADC Decimation Filter dynamic range definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetDFInputDynamic()
  *           and @ref LL_ADC_GetDFInputDynamic()
  * @{
  */

#define LL_ADC_DF_DYN_RANGE_FULL    (0x00000000UL)                              /*!< ADC Decimation Filter dynamic
                                                                                     full range */
#define LL_ADC_DF_DYN_RANGE_HALF    (0x1UL << ADC_DF_CONF_DF_HALF_D_EN_Pos)     /*!< ADC Decimation Filter dynamic
                                                                                     half range */

/**
  * @}
  */


/** @defgroup ADC_LL_MIC_CHANNEL ADC microphone channel definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetMicrophoneChannel()
  *           and @ref LL_ADC_GetMicrophoneChannel()
  * @{
  */

#define LL_ADC_DF_MIC_CH_RIGHT    (0x00000000UL)                           /*!< ADC microphone channel right */
#define LL_ADC_DF_MIC_CH_LEFT     (0x1UL << ADC_DF_CONF_DF_MICROL_RN_Pos)  /*!< ADC microphone channel left  */

/**
  * @}
  */


/** @defgroup ADC_LL_PDM_CLK_DIVIDER ADC PDM clock divider definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetPDMRate() and @ref LL_ADC_GetPDMRate()
  * @{
  */

#define LL_ADC_PDM_DIV_10   (0x00000000UL)                       /*!< ADC PDM clock divider 10 */
#define LL_ADC_PDM_DIV_11   (0x1UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 11 */
#define LL_ADC_PDM_DIV_12   (0x2UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 12 */
#define LL_ADC_PDM_DIV_13   (0x3UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 13 */
#define LL_ADC_PDM_DIV_14   (0x4UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 14 */
#define LL_ADC_PDM_DIV_15   (0x5UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 15 */
#define LL_ADC_PDM_DIV_16   (0x6UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 16 */
#define LL_ADC_PDM_DIV_17   (0x7UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 17 */
#define LL_ADC_PDM_DIV_18   (0x8UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 18 */
#define LL_ADC_PDM_DIV_19   (0x9UL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 19 */
#define LL_ADC_PDM_DIV_20   (0xAUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 20 */
#define LL_ADC_PDM_DIV_21   (0xBUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 21 */
#define LL_ADC_PDM_DIV_22   (0xCUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 22 */
#define LL_ADC_PDM_DIV_23   (0xDUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 23 */
#define LL_ADC_PDM_DIV_24   (0xEUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 24 */
#define LL_ADC_PDM_DIV_25   (0xFUL << ADC_DF_CONF_PDM_RATE_Pos)  /*!< ADC PDM clock divider 25 */

/**
  * @}
  */


/** @defgroup ADC_LL_DATA_FORMAT ADC data format definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetDataOutputFormat(),
  *           @ref LL_ADC_GetDataOutputFormat(), @ref LL_ADC_SetDataInputFormat() and @ref LL_ADC_GetDataInputFormat()
  * @{
  */

#define LL_ADC_DF_DATA_FORMAT_SIGNED    (0UL)  /*!< ADC data format signed   */
#define LL_ADC_DF_DATA_FORMAT_UNSIGNED  (1UL)  /*!< ADC data format unsigned */

/**
  * @}
  */


/** @defgroup ADC_LL_CIC_DECIMATOR_FACTOR ADC CIC decimator factor definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetCICDecimatorFactor()
  *           and @ref LL_ADC_GetCICDecimatorFactor()
  * @{
  */

#define LL_ADC_DF_CIC_DECIMATOR_FACTOR_HALF     (ADC_DF_CONF_DF_CIC_DHF)  /*!< ADC CIC decimator factor half    */
#define LL_ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER  (0x00000000UL)            /*!< ADC CIC decimator factor integer */

/**
  * @}
  */


/** @defgroup ADC_LL_MICROPHONE_OUT_FREQ ADC microphone output frequency definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetMicrophoneOutputDatarate()
  *           and @ref LL_ADC_GetMicrophoneOutputDatarate()
  * @{
  */

#define LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ  (0x0EUL)  /*!< ADC digital microphone output frequency 47.619 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ  (0x0FUL)  /*!< ADC digital microphone output frequency 44.44  kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ  (0x1EUL)  /*!< ADC digital microphone output frequency 22.22  kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ  (0x2AUL)  /*!< ADC digital microphone output frequency 15.873 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ   (0x54UL)  /*!< ADC digital microphone output frequency  7.936 kHz */

#define LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ (0x02UL)  /*!< ADC analog microphone output frequency 200.00 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ  (0x15UL)  /*!< ADC analog microphone output frequency 15.873 kHz */
#define LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ   (0x2AUL)  /*!< ADC analog microphone output frequency  7.936 kHz */

/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_LL_DS_DATA_WIDTH ADC Down Sampler data width definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetDSDataOutputWidth()
  *           and @ref LL_ADC_GetDSDataOutputWidth()
  * @{
  */

#define LL_ADC_DS_DATA_WIDTH_12_BIT  (0UL)  /*!< ADC Down Sampler data width 12 bits */
#define LL_ADC_DS_DATA_WIDTH_13_BIT  (1UL)  /*!< ADC Down Sampler data width 13 bits */
#define LL_ADC_DS_DATA_WIDTH_14_BIT  (2UL)  /*!< ADC Down Sampler data width 14 bits */
#define LL_ADC_DS_DATA_WIDTH_15_BIT  (3UL)  /*!< ADC Down Sampler data width 15 bits */
#define LL_ADC_DS_DATA_WIDTH_16_BIT  (4UL)  /*!< ADC Down Sampler data width 16 bits */

/**
  * @}
  */


/** @defgroup ADC_LL_DS_RATIO ADC Down Sampler ratio definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetDSDataOutputRatio()
  *           and @ref LL_ADC_GetDSDataOutputRatio()
  * @{
  */

#define LL_ADC_DS_RATIO_1    (0UL)          /*!< ADC Down Sampler ratio 1, no down sampling (default) */
#define LL_ADC_DS_RATIO_2    (1UL)          /*!< ADC Down Sampler ratio 2                             */
#define LL_ADC_DS_RATIO_4    (2UL)          /*!< ADC Down Sampler ratio 4                             */
#define LL_ADC_DS_RATIO_8    (3UL)          /*!< ADC Down Sampler ratio 8                             */
#define LL_ADC_DS_RATIO_16   (4UL)          /*!< ADC Down Sampler ratio 16                            */
#define LL_ADC_DS_RATIO_32   (5UL)          /*!< ADC Down Sampler ratio 32                            */
#define LL_ADC_DS_RATIO_64   (6UL)          /*!< ADC Down Sampler ratio 64                            */
#define LL_ADC_DS_RATIO_128  (7UL)          /*!< ADC Down Sampler ratio 128                           */

/**
  * @}
  */


/** @defgroup ADC_LL_CHANNEL ADC channel number code for conversion definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetSequencerRanks()
  * @{
  */

#define LL_ADC_CHANNEL_VINM0             (0x00UL)  /*!< ADC channel for VINM0 to single negative input */
#define LL_ADC_CHANNEL_VINM1             (0x01UL)  /*!< ADC channel for VINM1 to single negative input */
#define LL_ADC_CHANNEL_VINM2             (0x02UL)  /*!< ADC channel for VINM2 to single negative input */
#define LL_ADC_CHANNEL_VINM3             (0x03UL)  /*!< ADC channel for VINM3 to single negative input */
#define LL_ADC_CHANNEL_VINP0             (0x04UL)  /*!< ADC channel for VINP0 to single positive input */
#define LL_ADC_CHANNEL_VINP1             (0x05UL)  /*!< ADC channel for VINP1 to single positive input */
#define LL_ADC_CHANNEL_VINP2             (0x06UL)  /*!< ADC channel for VINP2 to single positive input */
#define LL_ADC_CHANNEL_VINP3             (0x07UL)  /*!< ADC channel for VINP3 to single positive input */
#define LL_ADC_CHANNEL_VINP0_VINM0       (0x08UL)  /*!< ADC channel for VINP0 - VINM0 to differential input */
#define LL_ADC_CHANNEL_VINP1_VINM1       (0x09UL)  /*!< ADC channel for VINP1 - VINM1 to differential input */
#define LL_ADC_CHANNEL_VINP2_VINM2       (0x0AUL)  /*!< ADC channel for VINP2 - VINM2 to differential input */
#define LL_ADC_CHANNEL_VINP3_VINM3       (0x0BUL)  /*!< ADC channel for VINP3 - VINM3 to differential input */
#define LL_ADC_CHANNEL_VBAT              (0x0CUL)  /*!< ADC channel for VBAT, battery level detector */
#define LL_ADC_CHANNEL_TEMPSENSOR        (0x0DUL)  /*!< ADC channel for temperature sensor */

/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_RANKS  ADC - Sequencer ranks
  * @{
  */
#define LL_ADC_RANK_1  (ADC_SEQ_1_REGOFFSET | ADC_RANK_1_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  1 */
#define LL_ADC_RANK_2  (ADC_SEQ_1_REGOFFSET | ADC_RANK_2_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  2 */
#define LL_ADC_RANK_3  (ADC_SEQ_1_REGOFFSET | ADC_RANK_3_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  3 */
#define LL_ADC_RANK_4  (ADC_SEQ_1_REGOFFSET | ADC_RANK_4_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  4 */
#define LL_ADC_RANK_5  (ADC_SEQ_1_REGOFFSET | ADC_RANK_5_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  5 */
#define LL_ADC_RANK_6  (ADC_SEQ_1_REGOFFSET | ADC_RANK_6_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  6 */
#define LL_ADC_RANK_7  (ADC_SEQ_1_REGOFFSET | ADC_RANK_7_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  7 */
#define LL_ADC_RANK_8  (ADC_SEQ_1_REGOFFSET | ADC_RANK_8_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  8 */
#define LL_ADC_RANK_9  (ADC_SEQ_2_REGOFFSET | ADC_RANK_9_SEQ_X_BITOFFSET_POS)   /*!< ADC rank  9 */
#define LL_ADC_RANK_10 (ADC_SEQ_2_REGOFFSET | ADC_RANK_10_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 10 */
#define LL_ADC_RANK_11 (ADC_SEQ_2_REGOFFSET | ADC_RANK_11_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 11 */
#define LL_ADC_RANK_12 (ADC_SEQ_2_REGOFFSET | ADC_RANK_12_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 12 */
#define LL_ADC_RANK_13 (ADC_SEQ_2_REGOFFSET | ADC_RANK_13_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 13 */
#define LL_ADC_RANK_14 (ADC_SEQ_2_REGOFFSET | ADC_RANK_14_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 14 */
#define LL_ADC_RANK_15 (ADC_SEQ_2_REGOFFSET | ADC_RANK_15_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 15 */
#define LL_ADC_RANK_16 (ADC_SEQ_2_REGOFFSET | ADC_RANK_16_SEQ_X_BITOFFSET_POS)  /*!< ADC rank 16 */
/**
  * @}
  */

/** @defgroup ADC_LL_CALIB_POINT ADC calibration points definitions
  * @brief    It defines the parameters used for the functions
  *           @ref LL_ADC_SetCalibPointForDiff(), @ref LL_ADC_GetCalibPointForDiff(),
  *           @ref LL_ADC_SetCalibPointForSinglePos(), @ref LL_ADC_GetCalibPointForSinglePos(),
  *           @ref LL_ADC_SetCalibPointForSingleNeg(), @ref LL_ADC_GetCalibPointForSingleNeg(),
  * @{
  */

#define LL_ADC_CALIB_POINT_1  (0x00UL)  /*!< ADC calibration point 1 */
#define LL_ADC_CALIB_POINT_2  (0x01UL)  /*!< ADC calibration point 2 */
#define LL_ADC_CALIB_POINT_3  (0x02UL)  /*!< ADC calibration point 3 */
#define LL_ADC_CALIB_POINT_4  (0x03UL)  /*!< ADC calibration point 4 */

/**
  * @}
  */

/** @defgroup ADC_LL_AWD_CHANNEL ADC watchdog channel selection for bit mask definitions
  * @brief    It defines the parameters used for the functions @ref LL_ADC_SetAWDInputChannels()
  *           and @ref LL_ADC_GetAWDInputChannels()
  * @{
  */

#define LL_ADC_AWD_CH_VINM0      (ADC_WD_CONF_AWD_CHX_0 ) /*!< ADC watchdog channel selection: VINM0 to negative input  */
#define LL_ADC_AWD_CH_VINM1      (ADC_WD_CONF_AWD_CHX_1 ) /*!< ADC watchdog channel selection: VINM1 to negative input  */
#define LL_ADC_AWD_CH_VINM2      (ADC_WD_CONF_AWD_CHX_2 ) /*!< ADC watchdog channel selection: VINM2 to negative input  */
#define LL_ADC_AWD_CH_VINM3      (ADC_WD_CONF_AWD_CHX_3 ) /*!< ADC watchdog channel selection: VINM3 to negative input  */
#define LL_ADC_AWD_CH_VINP0      (ADC_WD_CONF_AWD_CHX_8 ) /*!< ADC watchdog channel selection: VINP0 to positive input  */
#define LL_ADC_AWD_CH_VINP1      (ADC_WD_CONF_AWD_CHX_9 ) /*!< ADC watchdog channel selection: VINP1 to positive input  */
#define LL_ADC_AWD_CH_VINP2      (ADC_WD_CONF_AWD_CHX_10) /*!< ADC watchdog channel selection: VINP2 to positive input  */
#define LL_ADC_AWD_CH_VINP3      (ADC_WD_CONF_AWD_CHX_11) /*!< ADC watchdog channel selection: VINP3 to positive input  */
#define LL_ADC_AWD_CH_MICROM     (ADC_WD_CONF_AWD_CHX_4 ) /*!< ADC watchdog channel selection: MICROM to negative input */
#define LL_ADC_AWD_CH_MICROP     (ADC_WD_CONF_AWD_CHX_12) /*!< ADC watchdog channel selection: MICROP to positive input */
#define LL_ADC_AWD_CH_VBAT       (ADC_WD_CONF_AWD_CHX_5 ) /*!< ADC watchdog channel selection: VBAT to negative input   */
#define LL_ADC_AWD_CH_TEMPSENSOR (ADC_WD_CONF_AWD_CHX_13) /*!< ADC watchdog channel selection: TEMP to positive input   */
#define LL_ADC_AWD_CH_VDDA_NEG   (ADC_WD_CONF_AWD_CHX_7 ) /*!< ADC watchdog channel selection: VDDA to negative input   */
#define LL_ADC_AWD_CH_VDDA_POS   (ADC_WD_CONF_AWD_CHX_15) /*!< ADC watchdog channel selection: VDDA to positive input   */
#define LL_ADC_AWD_CH_GND_NEG    (ADC_WD_CONF_AWD_CHX_6 ) /*!< ADC watchdog channel selection: GND to negative input    */
#define LL_ADC_AWD_CH_GND_POS    (ADC_WD_CONF_AWD_CHX_14) /*!< ADC watchdog channel selection: GND to positive input    */

/**
  * @}
  */


/** @defgroup ADC_LL_IRQ_STATUS_MASK ADC IRQ_STATUS register mask definitions
  * @brief    It defines the IRQ flags used for the functions @ref LL_ADC_ClearActiveFlags()
  *           and @ref LL_ADC_GetActiveFlags().
  * @{
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define LL_ADC_IRQ_FLAG_OVRFL   (ADC_IRQ_STATUS_DF_OVRFL_IRQ) /*!< ADC IRQ flag OVRFL */
#define LL_ADC_IRQ_FLAG_OVRDF   (ADC_IRQ_STATUS_OVR_DF_IRQ)   /*!< ADC IRQ flag OVRDF */
#define LL_ADC_IRQ_FLAG_EODF    (ADC_IRQ_STATUS_EODF_IRQ)     /*!< ADC IRQ flag EODF  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
#define LL_ADC_IRQ_FLAG_OVRDS   (ADC_IRQ_STATUS_OVR_DS_IRQ)   /*!< ADC IRQ flag OVRDS */
#define LL_ADC_IRQ_FLAG_AWD1    (ADC_IRQ_STATUS_AWD_IRQ)      /*!< ADC IRQ flag AWD1  */
#define LL_ADC_IRQ_FLAG_EOC     (ADC_IRQ_STATUS_EOC_IRQ)      /*!< ADC IRQ flag EOC   */
#define LL_ADC_IRQ_FLAG_EOS     (ADC_IRQ_STATUS_EOS_IRQ)      /*!< ADC IRQ flag EOS   */
#define LL_ADC_IRQ_FLAG_EODS    (ADC_IRQ_STATUS_EODS_IRQ)     /*!< ADC IRQ flag EODS  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define LL_ADC_IRQ_FLAGS_MASK   (LL_ADC_IRQ_FLAG_OVRFL | \
                                 LL_ADC_IRQ_FLAG_OVRDF | \
                                 LL_ADC_IRQ_FLAG_OVRDS | \
                                 LL_ADC_IRQ_FLAG_AWD1  | \
                                 LL_ADC_IRQ_FLAG_EOC   | \
                                 LL_ADC_IRQ_FLAG_EOS   | \
                                 LL_ADC_IRQ_FLAG_EODF  | \
                                 LL_ADC_IRQ_FLAG_EODS)
#else
#define LL_ADC_IRQ_FLAGS_MASK   (LL_ADC_IRQ_FLAG_OVRDS | \
                                 LL_ADC_IRQ_FLAG_AWD1  | \
                                 LL_ADC_IRQ_FLAG_EOC   | \
                                 LL_ADC_IRQ_FLAG_EOS   | \
                                 LL_ADC_IRQ_FLAG_EODS)
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @}
  */


/** @defgroup ADC_LL_IRQ_ENABLE ADC interrupts enable definitions
  * @brief    It defines the IRQ interrupt enable used for the functions @ref LL_ADC_ClearActiveFlags()
  *           and @ref LL_ADC_GetActiveFlags().
  * @{
  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
#define LL_ADC_IRQ_EN_OVRFL   (ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA) /*!< ADC IRQ enable OVRFL */
#define LL_ADC_IRQ_EN_OVRDF   (ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)   /*!< ADC IRQ enable OVRDF */
#define LL_ADC_IRQ_EN_EODF    (ADC_IRQ_ENABLE_EODF_IRQ_ENA)     /*!< ADC IRQ enable EODF  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
#define LL_ADC_IRQ_EN_OVRDS   (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA)   /*!< ADC IRQ enable OVRDS */
#define LL_ADC_IRQ_EN_AWD1    (ADC_IRQ_ENABLE_AWD_IRQ_ENA)      /*!< ADC IRQ enable AWD1  */
#define LL_ADC_IRQ_EN_EOC     (ADC_IRQ_ENABLE_EOC_IRQ_ENA)      /*!< ADC IRQ enable EOC   */
#define LL_ADC_IRQ_EN_EOS     (ADC_IRQ_ENABLE_EOS_IRQ_ENA)      /*!< ADC IRQ enable EOS   */
#define LL_ADC_IRQ_EN_EODS    (ADC_IRQ_ENABLE_EODS_IRQ_ENA)     /*!< ADC IRQ enable EODS  */

/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @}
  */

/** @defgroup ADC_LL_EM_HELPER_MACRO ADC helper macro
  * @{
  */

#define LL_ADC_TEMPERATURE_CALC_ERROR      ((int16_t)0x7FFF)  /* Temperature calculation error using helper macro
                                                                 @ref __LL_ADC_CALC_TEMPERATURE(), due to issue on
                                                                 calibration parameters. This value is coded on 16 bits
                                                                 (to fit on signed word or double word) and corresponds
                                                                 to an inconsistent temperature value. */
/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref-
  *         (refer to reference manual).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
  */
#define __LL_ADC_DIGITAL_SCALE(__ADC_WIDTH__) (0xFFFFUL >> ((LL_ADC_DS_DATA_WIDTH_16_BIT) - (__ADC_WIDTH__)))

/**
  * @brief  Helper macro to define the ADC conversion data full-scale analog
  *         voltage value corresponding to the selected ADC input range.
  * @param  __INPUT_VOLTAGE_RANGE__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
  */
#define __LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__) \
  (((__INPUT_VOLTAGE_RANGE__) == LL_ADC_VIN_RANGE_1V2) ? 1250UL : ((__INPUT_VOLTAGE_RANGE__) * 1200UL))

/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VINP0
  *         @arg @ref LL_ADC_CHANNEL_VINP1
  *         @arg @ref LL_ADC_CHANNEL_VINP2
  *         @arg @ref LL_ADC_CHANNEL_VINP3
  *         @arg @ref LL_ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINP3_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel
  *         (channel connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define __LL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__) ((__CHANNEL__) == (LL_ADC_CHANNEL_VBAT)          \
                                                   || (__CHANNEL__) == (LL_ADC_CHANNEL_TEMPSENSOR) \
                                                  )

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_WIDTH_CURRENT__ Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @param  __ADC_WIDTH_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data to the requested resolution
  */
#define __LL_ADC_CONVERT_DATA_RESOLUTION(__DATA__,\
                                         __ADC_WIDTH_CURRENT__,\
                                         __ADC_WIDTH_TARGET__)                \
(((__DATA__)                                                                  \
  << ((LL_ADC_DS_DATA_WIDTH_16_BIT) - (__ADC_WIDTH_CURRENT__)))               \
 >> ((LL_ADC_DS_DATA_WIDTH_16_BIT) - (__ADC_WIDTH_TARGET__))                  \
)

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  * @param  __ADC_DATA__ ADC conversion data (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DATA_TO_VOLTAGE(__INPUT_VOLTAGE_RANGE__,\
                                      __ADC_DATA__,\
                                      __ADC_WIDTH__)                            \
((__ADC_DATA__) * (int32_t)(__LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__))\
 / (int32_t)(__LL_ADC_DIGITAL_SCALE(__ADC_WIDTH__))                             \
)

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value) in
  *         differential ended mode.
  * @note   ADC data from ADC data register is unsigned and centered around
  *         middle code in. Converted voltage can be positive or negative
  *         depending on differential input voltages.
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  * @param  __ADC_DATA__ ADC conversion data (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(__INPUT_VOLTAGE_RANGE__,\
                                           __ADC_DATA__,\
                                           __ADC_WIDTH__)                                   \
((int32_t)((__ADC_DATA__)) * (int32_t)(__LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__)) \
 / (int32_t)(__LL_ADC_DIGITAL_SCALE(__ADC_WIDTH__))                                         \
 - (int32_t)(__LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__) / 2 )                      \
)


/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  * @note   Calculation formula:
  *           Temperature = (55 / (C85 - C30)) * (TS_ADC_DATA - C30) + 30
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                C85    = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL1 (calibrated in factory)
  *                C30    = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL2 (calibrated in factory)
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data of internal
  *                                 temperature sensor (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Temperature (unit: degree Celsius)
  *         In case or error, value LL_ADC_TEMPERATURE_CALC_ERROR is returned (inconsistent temperature value)
  */
#if defined(TEMPSENSOR_TCK_ADDR)
#define __LL_ADC_CALC_TEMPERATURE(__TEMPSENSOR_ADC_DATA__,\
                                  __ADC_WIDTH__)                                                                       \
(((__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__),(__ADC_WIDTH__), LL_ADC_DS_DATA_WIDTH_12_BIT)            \
   - (int32_t)*TEMPSENSOR_C30_ADDR + (int32_t)*TEMPSENSOR_TCK_ADDR)                                                    \
  / (10UL))                                                                                                            \
)
#else
#define __LL_ADC_CALC_TEMPERATURE(__TEMPSENSOR_ADC_DATA__,\
                                  __ADC_WIDTH__)                                                                       \
((((int32_t)*TEMPSENSOR_C85_ADDR - (int32_t)*TEMPSENSOR_C30_ADDR) != 0)                                                \
 ? (((int32_t)(((__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__),                                           \
                                                  (__ADC_WIDTH__),                                                     \
                                                  LL_ADC_DS_DATA_WIDTH_12_BIT)                                         \
                 - (int32_t)*TEMPSENSOR_C30_ADDR)) * 55L)                                                              \
     / ((int32_t)*TEMPSENSOR_C85_ADDR - (int32_t)*TEMPSENSOR_C30_ADDR))                                                \
    + TEMPSENSOR_C30_TEMP)                                                                                             \
 :                                                                                                                     \
 ((int32_t)LL_ADC_TEMPERATURE_CALC_ERROR)                                                                              \
)
#endif /* TEMPSENSOR_TCK_ADDR */

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor typical values
  *         (refer to device datasheet).
  * @note   Calculation formula:
  *           Temperature = (Avg_Slope * (TS_ADC_DATA - VMIN) + TEMP_MIN
  *
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                Avg_Slope = (TEMP_MAX - TEMP_MIN) / (VMAX - VMIN))
  *                TEMP_MIN  = maximal temperature range of the sensor (unit: degC)
  *                TEMP_MAX  = maximal temperature range of the sensor (unit: degC)
  *                VMIN      = temperature sensor digital value at TEMP_MIN (unit: mV)
  *                VMAX      = temperature sensor digital value at TEMP_MAX (unit: mV)
  *         Caution: Calculation relevancy under reserve the temperature sensor
  *                  of the current device has characteristics in line with
  *                  datasheet typical values.
  *                  If temperature sensor calibration values are available on
  *                  on this device (presence of macro __LL_ADC_CALC_TEMPERATURE()),
  *                  temperature calculation will be more accurate using
  *                  helper macro @ref __LL_ADC_CALC_TEMPERATURE().
  * @param  __TEMPSENSOR_ADC_DATA__       ADC conversion data of internal temperature sensor (unit: digital value).
  * @param  __ADC_WIDTH__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval Temperature (unit: degree Celsius)
  */
#if defined(TEMPSENSOR_TCK_ADDR)
#define __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(__TEMPSENSOR_ADC_DATA__,\
                                             __ADC_WIDTH__)                                                            \
(((__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__),(__ADC_WIDTH__), LL_ADC_DS_DATA_WIDTH_12_BIT)            \
   - 2500 + 300)                                                                                                       \
  / (10UL))                                                                                                            \
)
#else
#define __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(__TEMPSENSOR_ADC_DATA__,\
                                             __ADC_WIDTH__)                                                            \
(((((int32_t)(__LL_ADC_CONVERT_DATA_RESOLUTION(__TEMPSENSOR_ADC_DATA__,                                                \
                                               __ADC_WIDTH__,                                                          \
                                               LL_ADC_DS_DATA_WIDTH_12_BIT)) - 2530L)                                  \
   * 55L) / (2980L - 2530L)) + 30UL                                                                                    \
)
#endif /* TEMPSENSOR_TCK_ADDR */

/**
  * @brief   Helper macro to convert the threshold value from mV to code for
  *          single conversion or battery sensor.
  * @param  __VOLTAGE_MV__ The voltage threshold for the ADC watchdog in mV.
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  * @retval Returned 12-bit value to be used as ADC watchdog threshold.
  */
#define LL_ADC_CONVERT_VOLTAGE_TO_DATA_AWD_THRESHOLD_SINGLE(__VOLTAGE_MV__,\
                                                            __INPUT_VOLTAGE_RANGE__)                                   \
((uint32_t)(((__VOLTAGE_MV__) * __LL_ADC_DIGITAL_SCALE(ADC_DS_DATA_WIDTH_12_BIT))                                      \
            / (__LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__))))

/**
  * @brief  Helper macro to convert the threshold value from mV to code for
  *         differential conversion.
  * @param  __VOLTAGE_MV__ The voltage threshold for the ADC watchdog in mV.
  * @param  __INPUT_VOLTAGE_RANGE__ Analog reference voltage (unit: mV)
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  * @retval Returned 12-bit value to be used as ADC watchdog threshold.
  */
#define LL_ADC_CONVERT_VOLTAGE_TO_DATA_AWD_THRESHOLD_DIFF(__VOLTAGE_MV__,\
                                                          __INPUT_VOLTAGE_RANGE__)                                     \
((uint32_t)((((__VOLTAGE_MV__) * __LL_ADC_DIGITAL_SCALE(ADC_DS_DATA_WIDTH_12_BIT))                                    \
             / (2UL * __LL_ADC_REFERENCE_VOLTAGE(__INPUT_VOLTAGE_RANGE__)))                                            \
            + (__LL_ADC_DIGITAL_SCALE(ADC_DS_DATA_WIDTH_12_BIT) / 2UL)))

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_LL_EF_Configuration_ADC ADC Configuration functions
  * @{
  */

/**
  * @brief  Select the input sampling method.
  *         Sampling only at conversion start (default).
  *         Sampling starts at the end of conversion.
  * @rmtoll CONF     ADC_CONT_1V2       LL_ADC_SetInputSamplingMode
  * @param  ADCx ADC instance
  * @param  SamplingMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_AT_START
  *         @arg @ref LL_ADC_SAMPLING_AT_END
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetInputSamplingMode(ADC_TypeDef *ADCx, uint32_t SamplingMode)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_ADC_CONT_1V2, SamplingMode);
}

/**
  * @brief  Get input sampling mode.
  * @rmtoll CONF     ADC_CONT_1V2       LL_ADC_GetInputSamplingMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_AT_START
  *         @arg @ref LL_ADC_SAMPLING_AT_END
  */
__STATIC_INLINE uint32_t LL_ADC_GetInputSamplingMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_ADC_CONT_1V2));
}

/**
  * @brief  Enable the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_InvertOutputDiffModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputDiffModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF);
}

/**
  * @brief  Disable the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_InvertOutputDiffModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputDiffModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF);
}

/**
  * @brief  Check if the inversion of the ADC data output bits (1's complement)
  *         when a differential input is connected to the ADC is enabled.
  * @rmtoll CONF     BIT_INVERT_DIFF     LL_ADC_IsInvertOutputDiffModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: inversion is not enabled, 1: inversion is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInvertOutputDiffModeEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_DIFF) == (ADC_CONF_BIT_INVERT_DIFF)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_InvertOutputSingleNegModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputSingleNegModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN);
}

/**
  * @brief  Disable the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_InvertOutputSingleNegModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_InvertOutputSingleNegModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN);
}

/**
  * @brief  Check if the inversion of the ADC data output bits (1's complement)
  *         when a single negative input is connected to the ADC is enabled.
  * @rmtoll CONF     BIT_INVERT_SN     LL_ADC_IsInvertOutputSingleNegModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: inversion is not enabled, 1: inversion is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInvertOutputSingleNegModeEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_BIT_INVERT_SN) == (ADC_CONF_BIT_INVERT_SN)) ? 1UL : 0UL);
}

#if defined(ADC_CONF_OVR_DF_CFG)
/**
  * @brief  Select the overrun configuration for the output data of
  *         the Decimation Filter (DF).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DF_CFG       LL_ADC_SetOverrunDF
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverrunDF(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_OVR_DF_CFG, Overrun);
}

/**
  * @brief  Get the overrun configuration for the output data of
  *         the Decimation Filter (DF).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DF_CFG       LL_ADC_GetOverrunDF
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverrunDF(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OVR_DF_CFG));
}
#endif /* ADC_CONF_OVR_DF_CFG */

/**
  * @brief  Select the overrun configuration for the output data of
  *         the Down Sampler (DS).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DS_CFG       LL_ADC_SetOverrunDS
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverrunDS(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_OVR_DS_CFG, Overrun);
}

/**
  * @brief  Get the overrun configuration for the output data of
  *         the Down Sampler (DS).
  *         Previous data is kept, the new one is lost.
  *         Previous data is lost, the new one is kept.
  * @rmtoll CONF     OVR_DS_CFG       LL_ADC_GetOverrunDS
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_NEW_DATA_IS_LOST
  *         @arg @ref LL_ADC_NEW_DATA_IS_KEPT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverrunDS(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OVR_DS_CFG));
}

#if defined(ADC_CONF_DMA_DF_ENA)
/**
  * @brief  Enable the DMA mode for the Decimation Filter (DF) data path.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_DMAModeDFEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDFEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA);
}

/**
  * @brief  Disable the DMA mode for the Decimation Filter (DF) data path.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_DMAModeDFDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDFDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA);
}


/**
  * @brief  Check if the DMA mode for the Decimation Filter (DF) data path is enabled.
  * @rmtoll CONF     DMA_DF_ENA     LL_ADC_IsDMAModeDFEnabled
  * @param  ADCx ADC instance
  * @retval 0: DMA mode is not enabled, 1: DMA mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDMAModeDFEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_DMA_DF_ENA) == (ADC_CONF_DMA_DF_ENA)) ? 1UL : 0UL);
}
#endif /* ADC_CONF_DMA_DF_ENA */

/**
  * @brief  Enable the DMA mode for the Down Sampler (DS) data path.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_DMAModeDSEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDSEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA);
}


/**
  * @brief  Disable the DMA mode for the Down Sampler (DS) data path.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_DMAModeDSDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DMAModeDSDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA);
}


/**
  * @brief  Check if the DMA mode for the Down Sampler (DS) data path is enabled.
  * @rmtoll CONF     DMA_DS_ENA     LL_ADC_IsDMAModeDSEnabled
  * @param  ADCx ADC instance
  * @retval 0: DMA mode is not enabled, 1: DMA mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDMAModeDSEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_DMA_DS_ENA) == (ADC_CONF_DMA_DS_ENA)) ? 1UL : 0UL);
}

/**
  * @brief  Select the ADC conversion rate.
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_SetSampleRate
  * @param  ADCx ADC instance
  * @param  SampleRate This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_16
  *         @arg @ref LL_ADC_SAMPLE_RATE_20
  *         @arg @ref LL_ADC_SAMPLE_RATE_24
  *         @arg @ref LL_ADC_SAMPLE_RATE_28
  *         @arg @ref LL_ADC_SAMPLE_RATE_32  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_36  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_40  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_44  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_48  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_52  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_56  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_60  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_64  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_68  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_72  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_76  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_80  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_84  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_88  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_92  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_96  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_100 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_104 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_108 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_112 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_116 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_120 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_124 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_128 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_132 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_136 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_140 (1)
  *
  *         (1) Parameter only available on STM32WB09 and STM32WB05
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSampleRate(ADC_TypeDef *ADCx, uint32_t SampleRate)
{
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
  MODIFY_REG(ADCx->CONF, ADC_CONF_SAMPLE_RATE | ADC_CONF_SAMPLE_RATE_MSB, SampleRate);
#else
  MODIFY_REG(ADCx->CONF, ADC_CONF_SAMPLE_RATE, SampleRate);
#endif /* ADC_CONF_SAMPLE_RATE_MSB */
}


/**
  * @brief  Get the ADC conversion rate.
  * @rmtoll CONF     SAMPLE_RATE       LL_ADC_GetSampleRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLE_RATE_16
  *         @arg @ref LL_ADC_SAMPLE_RATE_20
  *         @arg @ref LL_ADC_SAMPLE_RATE_24
  *         @arg @ref LL_ADC_SAMPLE_RATE_28
  *         @arg @ref LL_ADC_SAMPLE_RATE_32  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_36  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_40  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_44  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_48  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_52  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_56  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_60  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_64  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_68  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_72  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_76  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_80  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_84  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_88  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_92  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_96  (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_100 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_104 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_108 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_112 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_116 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_120 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_124 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_128 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_132 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_136 (1)
  *         @arg @ref LL_ADC_SAMPLE_RATE_140 (1)
  *
  *         (1) Parameter only available on STM32WB09 and STM32WB05
  */
__STATIC_INLINE uint32_t LL_ADC_GetSampleRate(const ADC_TypeDef *ADCx)
{
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SAMPLE_RATE | ADC_CONF_SAMPLE_RATE_MSB));
#else
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SAMPLE_RATE));
#endif /* ADC_CONF_SAMPLE_RATE_MSB */
}

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief  Select the ADC operation mode.
  * @rmtoll CONF     OP_MODE       LL_ADC_SetADCMode
  * @param  ADCx ADC instance
  * @param  OperationMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OP_MODE_AUDIO
  *         @arg @ref LL_ADC_OP_MODE_ADC
  *         @arg @ref LL_ADC_OP_MODE_FULL
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetADCMode(ADC_TypeDef *ADCx, uint32_t OperationMode)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_OP_MODE, OperationMode);
}


/**
  * @brief  Get the ADC operation mode.
  * @rmtoll CONF     OP_MODE       LL_ADC_GetADCMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OP_MODE_AUDIO
  *         @arg @ref LL_ADC_OP_MODE_ADC
  *         @arg @ref LL_ADC_OP_MODE_FULL
  */
__STATIC_INLINE uint32_t LL_ADC_GetADCMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_OP_MODE));
}
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @brief  Enable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_SMPSSyncEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SMPSSyncEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA);
}

/**
  * @brief  Disable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_SMPSSyncDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SMPSSyncDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA);
}


/**
  * @brief  Check if the the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS is enabled.
  * @note   This bitfield must be 0 when the ADC clock is 32 MHz or
  *         when the SMPS is not used.
  * @rmtoll CONF     SMPS_SYNCHRO_ENA     LL_ADC_IsSMPSSyncEnabled
  * @param  ADCx ADC instance
  * @retval 0: Synchronization with SMPS is not enabled, 1: Synchronization with SMPS is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsSMPSSyncEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_SMPS_SYNCHRO_ENA) == (ADC_CONF_SMPS_SYNCHRO_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Set the number of conversion in a sequence starting from SEQ0.
  * @rmtoll CONF     SEQ_LEN       LL_ADC_SetSequenceLength
  * @param  ADCx ADC instance
  * @param  SequenceLength This parameter must be a number between Min_Data = 1 and Max_Data = 16.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSequenceLength(ADC_TypeDef *ADCx, uint32_t SequenceLength)
{
  MODIFY_REG(ADCx->CONF, ADC_CONF_SEQ_LEN, (SequenceLength - 1UL) << ADC_CONF_SEQ_LEN_Pos);
}


/**
  * @brief  Get the number of conversion in a sequence starting from SEQ0.
  * @rmtoll CONF     SEQ_LEN       LL_ADC_GetSequenceLength
  * @param  ADCx ADC instance
  * @retval Returned value is a number between Min_Data = 1 and Max_Data = 16.
  */
__STATIC_INLINE uint32_t LL_ADC_GetSequenceLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CONF, ADC_CONF_SEQ_LEN) >> ADC_CONF_SEQ_LEN_Pos) + 1UL;
}


/**
  * @brief  Enable the ADC conversion in sequence mode.
  * @rmtoll CONF     SEQUENCE     LL_ADC_SequenceModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SequenceModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_SEQUENCE);
}


/**
  * @brief  Disable the ADC conversion in sequence mode.
  * @rmtoll CONF     SEQUENCE     LL_ADC_SequenceModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SequenceModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_SEQUENCE);
}


/**
  * @brief  Check if the ADC conversion in sequence mode is enabled.
  * @rmtoll CONF     SEQUENCE     LL_ADC_IsSequenceModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: Sequence mode is not enabled, 1: Sequence mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsSequenceModeEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_SEQUENCE) == (ADC_CONF_SEQUENCE)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the ADC continuous conversion mode.
  *         When a sequence is over, the conversion starts again.
  * @note   Stop the conversion can be made by sets the STOP_OP_MODE bit.
  *         Call the API @ref LL_ADC_StopConversion().
  * @rmtoll CONF     CONT     LL_ADC_ContinuousModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ContinuousModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CONF, ADC_CONF_CONT);
}


/**
  * @brief  Disable the ADC continuous conversion mode.
  *         When a sequence is over, the conversion stops (single conversion mode).
  * @rmtoll CONF     CONT     LL_ADC_ContinuousModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ContinuousModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CONF, ADC_CONF_CONT);
}


/**
  * @brief  Check if the ADC continuous conversion mode is enabled.
  * @rmtoll CONF     CONT     LL_ADC_IsContinuousModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: Continuous mode is not enabled, 1: Continuous mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsContinuousModeEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CONF, ADC_CONF_CONT) == (ADC_CONF_CONT)) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Control_ADC ADC Control functions
  * @{
  */

#if defined(ADC_CTRL_ADC_LDO_ENA)
/**
  * @brief  Enable the LDO associated to the ADC block.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_EnableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableInternalRegulator(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA);
}


/**
  * @brief  Disable the LDO associated to the ADC block.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_DisableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableInternalRegulator(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA);
}


/**
  * @brief  Check if the LDO associated to the ADC block is enabled.
  * @note   This bit must not be set on QFN32 package.
  * @rmtoll CTRL     ADC_LDO_ENA     LL_ADC_IsInternalRegulatorEnabled
  * @param  ADCx ADC instance
  * @retval 0: LDO is not enabled, 1: LDO is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInternalRegulatorEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_ADC_LDO_ENA) == (ADC_CTRL_ADC_LDO_ENA)) ? 1UL : 0UL);
}
#endif /* ADC_CTRL_ADC_LDO_ENA */

#if defined(ADC_CTRL_DIG_AUD_MODE)
/**
  * @brief  Enable the digital audio mode.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_AudioModeEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_AudioModeEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE);
}


/**
  * @brief  Disable the digital audio mode.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_AudioModeDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_AudioModeDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE);
}

/**
  * @brief  Check if the digital audio mode is enabled.
  * @rmtoll CTRL     DIG_AUD_MODE     LL_ADC_IsAudioModeEnabled
  * @param  ADCx ADC instance
  * @retval 0: audio mode is not enabled, 1: audio mode is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsAudioModeEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_DIG_AUD_MODE) == (ADC_CTRL_DIG_AUD_MODE)) ? 1UL : 0UL);
}
#endif /* ADC_CTRL_DIG_AUD_MODE */

/**
  * @brief  Stop the ongoing ADC conversion.
  * @note   This bit is set by software and cleared by hardware.
  * @note   When the STOP_MODE_OP is set, the user has to wait around 10 us before
  *         to start a new ADC conversion (set START_CONV bit).
  * @rmtoll CTRL     STOP_OP_MODE     LL_ADC_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StopConversion(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_STOP_OP_MODE);
}


/**
  * @brief  Check if the stop conversion is ongoing.
  * @rmtoll CTRL     STOP_OP_MODE     LL_ADC_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: stop conversion is not ongoing, 1: stop conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsStopConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_STOP_OP_MODE) == (ADC_CTRL_STOP_OP_MODE)) ? 1UL : 0UL);
}


/**
  * @brief  Start an ADC conversion.
  * @note   This bit is set by software and cleared by hardware.
  * @rmtoll CTRL     START_CONV     LL_ADC_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartConversion(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_START_CONV);
}


/**
  * @brief  Check if the ADC conversion is ongoing.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: ADC conversion is not ongoing, 1: ADC conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsConversionOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF) == (ADC_CTRL_ADC_ON_OFF)) ? 1UL : 0UL);
}


/**
  * @brief  Power on the ADC.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_Enable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF);
}


/**
  * @brief  Power off the ADC.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_Disable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF);
}


/**
  * @brief  Check if the ADC is on.
  * @rmtoll CTRL     ADC_ON_OFF     LL_ADC_IsEnabled
  * @param  ADCx ADC instance
  * @retval 0: ADC is off, 1: ADC is on.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CTRL, ADC_CTRL_ADC_ON_OFF) == (ADC_CTRL_ADC_ON_OFF)) ? 1UL : 0UL);
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Occasional_Mode ADC Occasional Mode Control functions
  * @{
  */

#if defined(ADC_OCM_CTRL_OCM_ENA)
/**
  * @brief  Start an ADC occasional conversion during an analog audio conversion or
  *         during an ADC full mode.
  * @note   This bit is set by software and cleared by hardware.
  * @rmtoll OCM_CTRL     OCM_ENA     LL_ADC_StartOccasionalConversionMode
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartOccasionalConversionMode(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_ENA);
}


/**
  * @brief  Check if the ADC occasional conversion is ongoing.
  * @rmtoll OCM_CTRL     OCM_ENA     LL_ADC_IsOccasionalConversionModeOngoing
  * @param  ADCx ADC instance
  * @retval 0: ADC occasional conversion is not ongoing, 1: ADC occasional conversion is ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsOccasionalConversionModeOngoing(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_ENA) == (ADC_OCM_CTRL_OCM_ENA)) ? 1UL : 0UL);
}
#endif

#if defined(ADC_OCM_CTRL_OCM_SRC)
/**
  * @brief  Set the ADC occasional conversion source.
  *         ADC conversion from internal VBAT.
  *         ADC conversion from temperature sensor.
  * @rmtoll OCM_CTRL     OCM_SRC       LL_ADC_SetOccasionalConversionSource
  * @param  ADCx ADC instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OCM_SRC_VBAT
  *         @arg @ref LL_ADC_OCM_SRC_TEMP
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOccasionalConversionSource(ADC_TypeDef *ADCx, uint32_t Source)
{
  MODIFY_REG(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_SRC, Source);
}


/**
  * @brief  Get the ADC occasional conversion source.
  *         ADC conversion from internal VBAT.
  *         ADC conversion from temperature sensor.
  * @rmtoll OCM_CTRL     OCM_SRC       LL_ADC_GetOccasionalConversionSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OCM_SRC_VBAT
  *         @arg @ref LL_ADC_OCM_SRC_TEMP
  */
__STATIC_INLINE uint32_t LL_ADC_GetOccasionalConversionSource(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->OCM_CTRL, ADC_OCM_CTRL_OCM_SRC));
}
#endif /* ADC_OCM_CTRL_OCM_SRC */

/**
  * @}
  */


/** @defgroup ADC_LL_EF_PGA_Configuration ADC PGA Configuration functions
  * @{
  */

#if defined(ADC_PGA_CONF_PGA_BIAS) && defined(ADC_PGA_CONF_PGA_GAIN)
/**
  * @brief  Configure the voltage bias and the gain for the PGA used in the ADC microphone mode.
  * @param  ADCx ADC instance
  * @param  Bias This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  * @param  Gain This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureMicrophonePGA(ADC_TypeDef *ADCx, uint32_t Bias, uint32_t Gain)
{
  MODIFY_REG(ADCx->PGA_CONF, (ADC_PGA_CONF_PGA_BIAS | ADC_PGA_CONF_PGA_GAIN), (Bias | Gain));
}


/**
  * @brief  Set the voltage bias for the PGA used in the ADC microphone mode.
  * @rmtoll PGA_CONF     PGA_BIAS       LL_ADC_SetMicrophonePGABias
  * @param  ADCx ADC instance
  * @param  Bias This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophonePGABias(ADC_TypeDef *ADCx, uint32_t Bias)
{
  MODIFY_REG(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_BIAS, Bias);
}


/**
  * @brief  Get the voltage bias for the PGA used in the ADC microphone mode.
  * @rmtoll PGA_CONF     PGA_BIAS       LL_ADC_GetMicrophonePGABias
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PGA_BIAS_050_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_055_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_060_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_065_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_070_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_075_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_080_BAT
  *         @arg @ref LL_ADC_PGA_BIAS_090_BAT
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophonePGABias(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_BIAS));
}

/**
  * @brief  Set the gain for the PGA used in the ADC microphone mode.
  * @note   PGA gain of 6 dB is equivalent to the 2.4 V ADC full scale.
  * @rmtoll PGA_CONF     PGA_GAIN       LL_ADC_SetMicrophonePGAGain
  * @param  ADCx ADC instance
  * @param  Gain This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophonePGAGain(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_GAIN, Gain);
}


/**
  * @brief  Get the gain for the PGA used in the ADC microphone mode.
  * @note   PGA gain of 6 dB is equivalent to the 2.4 V ADC full scale.
  * @rmtoll PGA_CONF     PGA_GAIN       LL_ADC_GetMicrophonePGAGain
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PGA_GAIN_06_DB
  *         @arg @ref LL_ADC_PGA_GAIN_09_DB
  *         @arg @ref LL_ADC_PGA_GAIN_12_DB
  *         @arg @ref LL_ADC_PGA_GAIN_15_DB
  *         @arg @ref LL_ADC_PGA_GAIN_18_DB
  *         @arg @ref LL_ADC_PGA_GAIN_21_DB
  *         @arg @ref LL_ADC_PGA_GAIN_24_DB
  *         @arg @ref LL_ADC_PGA_GAIN_27_DB
  *         @arg @ref LL_ADC_PGA_GAIN_30_DB
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophonePGAGain(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PGA_CONF, ADC_PGA_CONF_PGA_GAIN));
}
#endif /* ADC_PGA_CONF_PGA_BIAS && ADC_PGA_CONF_PGA_GAIN */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Input_Switch_Selection ADC Input Switch Selection functions
  * @{
  */

/**
  * @brief  Set the input voltage range for selected channel.
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_1       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_2       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_3       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_4       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_5       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_6       LL_ADC_SetChannelVoltageRange\n
  *         SWITCH     SE_VIN_7       LL_ADC_SetChannelVoltageRange
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VINP0
  *         @arg @ref LL_ADC_CHANNEL_VINP1
  *         @arg @ref LL_ADC_CHANNEL_VINP2
  *         @arg @ref LL_ADC_CHANNEL_VINP3
  *         @arg @ref LL_ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINP3_VINM3
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelVoltageRange(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t Range)
{
  MODIFY_REG(ADCx->SWITCH, (ADC_SWITCH_SE_VIN_0 << ADC_CHANNEL_SWITCH_POS_LUT[Channel]),
             (Range << ADC_CHANNEL_SWITCH_POS_LUT[Channel]));
}

/**
  * @brief  Get the input voltage range for selected channel.
  * @rmtoll SWITCH     SE_VIN_0       LL_ADC_GetChannelVoltageRange
  *         SWITCH     SE_VIN_1       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_2       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_3       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_4       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_5       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_6       LL_ADC_GetChannelVoltageRange\n
  *         SWITCH     SE_VIN_7       LL_ADC_GetChannelVoltageRange
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VINP0
  *         @arg @ref LL_ADC_CHANNEL_VINP1
  *         @arg @ref LL_ADC_CHANNEL_VINP2
  *         @arg @ref LL_ADC_CHANNEL_VINP3
  *         @arg @ref LL_ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINP3_VINM3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelVoltageRange(const ADC_TypeDef *ADCx, uint32_t Channel)
{
  return ((uint32_t)(READ_BIT(ADCx->SWITCH, ADC_SWITCH_SE_VIN_0 << ADC_CHANNEL_SWITCH_POS_LUT[Channel]))
          >> ADC_CHANNEL_SWITCH_POS_LUT[Channel]);
}

/**
  * @}
  */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_LL_EF_DF_Configuration ADC Decimation Filter Configuration functions
  * @{
  */

/**
  * @brief  Set the input dynamic range for Decimation Filter (DF).
  *         It can be full dynamic or half dynamic.
  * @rmtoll DF_CONF     DF_HALF_D_EN       LL_ADC_SetDFInputDynamic
  * @param  ADCx ADC instance
  * @param  Dynamic This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_DYN_RANGE_FULL
  *         @arg @ref LL_ADC_DF_DYN_RANGE_HALF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDFInputDynamic(ADC_TypeDef *ADCx, uint32_t Dynamic)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_HALF_D_EN, Dynamic);
}


/**
  * @brief  Get the input dynamic ragne for Decimation Filter (DF).
  *         It can be full dynamic or half dynamic.
  * @rmtoll DF_CONF     DF_HALF_D_EN       LL_ADC_GetDFInputDynamic
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_DYN_RANGE_FULL
  *         @arg @ref LL_ADC_DF_DYN_RANGE_HALF
  */
__STATIC_INLINE uint32_t LL_ADC_GetDFInputDynamic(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HALF_D_EN));
}

/**
  * @brief  Enable the High Pass Filter (HPF) of the Decimation Filter (DF).
  *         The HPF cut off frequency is 40 Hz.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_DFHighPassFilterEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DFHighPassFilterEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN);
}


/**
  * @brief  Disable the High Pass Filter (HPF) of the Decimation Filter (DF).
  *         The HPF cut off frequency is 40 Hz.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_DFHighPassFilterDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DFHighPassFilterDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN);
}

/**
  * @brief  Check if the High Pass Filter (HPF) of the Decimation Filter (DF) is enabled.
  * @rmtoll DF_CONF     DF_HPF_EN     LL_ADC_IsDFHighPassFilterEnabled
  * @param  ADCx ADC instance
  * @retval 0: HPF is not enabled, 1: HPF is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDFHighPassFilterEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_HPF_EN) == (ADC_DF_CONF_DF_HPF_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Select the left/right channel on digital microphone mode.
  * @rmtoll DF_CONF     DF_MICROL_RN       LL_ADC_SetMicrophoneChannel
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_MIC_CH_LEFT
  *         @arg @ref LL_ADC_DF_MIC_CH_RIGHT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophoneChannel(ADC_TypeDef *ADCx, uint32_t Channel)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_MICROL_RN, Channel);
}

/**
  * @brief  Get the left/right channel on digital microphone mode.
  * @rmtoll DF_CONF     DF_MICROL_RN       LL_ADC_GetMicrophoneChannel
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_MIC_CH_LEFT
  *         @arg @ref LL_ADC_DF_MIC_CH_RIGHT
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophoneChannel(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_MICROL_RN));
}

/**
  * @brief  Set the PDM clock rate.
  *         The PDM clock rate is : SYSTEM_CLOCK / (Divider).
  * @note   With a SYSTEM_CLOCK of 32 MHz, the PDM clock rate is:
  *         3.2  MHz with Divider = 10.
  *         1.28 MHz with Divider = 25.
  * @rmtoll DF_CONF     PDM_RATE       LL_ADC_SetPDMRate
  * @param  ADCx ADC instance
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PDM_DIV_10
  *         @arg @ref LL_ADC_PDM_DIV_11
  *         @arg @ref LL_ADC_PDM_DIV_12
  *         @arg @ref LL_ADC_PDM_DIV_13
  *         @arg @ref LL_ADC_PDM_DIV_14
  *         @arg @ref LL_ADC_PDM_DIV_15
  *         @arg @ref LL_ADC_PDM_DIV_16
  *         @arg @ref LL_ADC_PDM_DIV_17
  *         @arg @ref LL_ADC_PDM_DIV_18
  *         @arg @ref LL_ADC_PDM_DIV_19
  *         @arg @ref LL_ADC_PDM_DIV_20
  *         @arg @ref LL_ADC_PDM_DIV_21
  *         @arg @ref LL_ADC_PDM_DIV_22
  *         @arg @ref LL_ADC_PDM_DIV_23
  *         @arg @ref LL_ADC_PDM_DIV_24
  *         @arg @ref LL_ADC_PDM_DIV_25
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetPDMRate(ADC_TypeDef *ADCx, uint32_t Divider)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_PDM_RATE, Divider);
}


/**
  * @brief  Get the PDM clock rate.
  *         The PDM clock rate is : SYSTEM_CLOCK / (Divider).
  * @note   With a SYSTEM_CLOCK of 32 MHz, the PDM clock rate is:
  *         3.2  MHz with Divider = 10.
  *         1.28 MHz with Divider = 25.
  * @rmtoll DF_CONF     PDM_RATE       LL_ADC_GetPDMRate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PDM_DIV_10
  *         @arg @ref LL_ADC_PDM_DIV_11
  *         @arg @ref LL_ADC_PDM_DIV_12
  *         @arg @ref LL_ADC_PDM_DIV_13
  *         @arg @ref LL_ADC_PDM_DIV_14
  *         @arg @ref LL_ADC_PDM_DIV_15
  *         @arg @ref LL_ADC_PDM_DIV_16
  *         @arg @ref LL_ADC_PDM_DIV_17
  *         @arg @ref LL_ADC_PDM_DIV_18
  *         @arg @ref LL_ADC_PDM_DIV_19
  *         @arg @ref LL_ADC_PDM_DIV_20
  *         @arg @ref LL_ADC_PDM_DIV_21
  *         @arg @ref LL_ADC_PDM_DIV_22
  *         @arg @ref LL_ADC_PDM_DIV_23
  *         @arg @ref LL_ADC_PDM_DIV_24
  *         @arg @ref LL_ADC_PDM_DIV_25
  */
__STATIC_INLINE uint32_t LL_ADC_GetPDMRate(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_PDM_RATE) + 10UL);
}

/**
  * @brief  Set the signed/unsigned output data format.
  * @rmtoll DF_CONF     DF_O_S2U       LL_ADC_SetDataOutputFormat
  * @param  ADCx ADC instance
  * @param  Format This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_SIGNED
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_UNSIGNED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataOutputFormat(ADC_TypeDef *ADCx, uint32_t Format)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_O_S2U, (Format << ADC_DF_CONF_DF_O_S2U_Pos));
}


/**
  * @brief  Get the signed/unsigned output data format.
  * @rmtoll DF_CONF     DF_O_S2U       LL_ADC_GetDataOutputFormat
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_SIGNED
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_UNSIGNED
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataOutputFormat(const ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_O_S2U)) >> ADC_DF_CONF_DF_O_S2U_Pos);
}

/**
  * @brief  Set the signed/unsigned input data format.
  * @rmtoll DF_CONF     DF_I_S2U       LL_ADC_SetDataInputFormat
  * @param  ADCx ADC instance
  * @param  Format This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_SIGNED
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_UNSIGNED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataInputFormat(ADC_TypeDef *ADCx, uint32_t Format)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_I_U2S, ~((Format) << ADC_DF_CONF_DF_I_U2S_Pos) & ADC_DF_CONF_DF_I_U2S);
}


/**
  * @brief  Get the signed/unsigned input data format.
  * @rmtoll DF_CONF     DF_I_S2U       LL_ADC_GetDataInputFormat
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_SIGNED
  *         @arg @ref LL_ADC_DF_DATA_FORMAT_UNSIGNED
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataInputFormat(const ADC_TypeDef *ADCx)
{
  return ((uint32_t)((READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_I_U2S)) == ADC_DF_CONF_DF_I_U2S) ?
          LL_ADC_DF_DATA_FORMAT_SIGNED : LL_ADC_DF_DATA_FORMAT_UNSIGNED);
}

/**
  * @brief  Enable the fractional interpolator.
  * @note   This bit must be set only for the generation of a data rate
  *         at 200 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_FractionalInterpolatorEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_FractionalInterpolatorEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2);
}


/**
  * @brief  Disable the fractional interpolator.
  * @note   This bit must be set only for the generation of a data rate
  *         at 200 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_FractionalInterpolatorDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_FractionalInterpolatorDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2);
}

/**
  * @brief  Check if the fractional interpolator is enabled.
  * @rmtoll DF_CONF     DF_ITP1P2     LL_ADC_IsFractionalInterpolatorEnabled
  * @param  ADCx ADC instance
  * @retval 0: Interpolator is not enabled, 1: Interpolator is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsFractionalInterpolatorEnabled(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_ITP1P2) == (ADC_DF_CONF_DF_ITP1P2)) ? 1UL : 0UL);
}

/**
  * @brief  Set the decimator factor of the CIC filter.
  * @note   This bit must be set (LL_ADC_DF_CIC_DECIMATOR_FACTOR_HALF)
  *         only for the generation of a data rate
  *         at 44.1 kps from ADC data at 1 MHz.
  * @rmtoll DF_CONF     DF_CIC_DHF       LL_ADC_SetCICDecimatorFactor
  * @param  ADCx ADC instance
  * @param  Factor This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DF_CIC_DECIMATOR_FACTOR_HALF
  *         @arg @ref LL_ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCICDecimatorFactor(ADC_TypeDef *ADCx, uint32_t Factor)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DHF, Factor);
}


/**
  * @brief  Get the decimator factor of the CIC filter.
  * @rmtoll DF_CONF     DF_CIC_DHF       LL_ADC_GetCICDecimatorFactor
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DF_CIC_DECIMATOR_FACTOR_HALF
  *         @arg @ref LL_ADC_DF_CIC_DECIMATOR_FACTOR_INTEGER
  */
__STATIC_INLINE uint32_t LL_ADC_GetCICDecimatorFactor(const ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DHF)));
}

/**
  * @brief  Set the output frequency for the microphone mode.
  * @rmtoll DF_CONF     DF_CIC_DEC_FACTOR       LL_ADC_SetMicrophoneOutputDatarate
  * @note   Different parameters for digital microphone and analog microphone.
  * @param  ADCx ADC instance
  * @param  Frequency This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ
  *
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMicrophoneOutputDatarate(ADC_TypeDef *ADCx, uint32_t Frequency)
{
  MODIFY_REG(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DEC_FACTOR, Frequency);
}


/**
  * @brief  Get the output frequency for the microphone mode.
  * @rmtoll DF_CONF     DF_CIC_DEC_FACTOR       LL_ADC_GetMicrophoneOutputDatarate
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_47619_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_44440_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_22220_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_DIG_7936_HZ
  *
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_200000_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_15873_HZ
  *         @arg @ref LL_ADC_OUTPUT_FREQ_MIC_ANA_7936_HZ
  */
__STATIC_INLINE uint32_t LL_ADC_GetMicrophoneOutputDatarate(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_CONF, ADC_DF_CONF_DF_CIC_DEC_FACTOR));
}
/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_LL_EF_DS_Configuration ADC Down Sampler Configuration functions
  * @{
  */

/**
  * @brief  Configure the width (in bit) and the ratio of the output data from the Down Sampler.
  * @param  ADCx ADC instance
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_1 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_2
  *         @arg @ref LL_ADC_DS_RATIO_4
  *         @arg @ref LL_ADC_DS_RATIO_8
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureDSDataOutput(ADC_TypeDef *ADCx, uint32_t Width, uint32_t Ratio)
{
  MODIFY_REG(ADCx->DS_CONF, (ADC_DS_CONF_DS_WIDTH | ADC_DS_CONF_DS_RATIO),
             ((Width << ADC_DS_CONF_DS_WIDTH_Pos) | Ratio));
}

/**
  * @brief  Set the width (in bit) of the output data from the Down Sampler.
  * @rmtoll DS_CONF     DS_WIDTH       LL_ADC_SetDSDataOutputWidth
  * @param  ADCx ADC instance
  * @param  Width This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDSDataOutputWidth(ADC_TypeDef *ADCx, uint32_t Width)
{
  MODIFY_REG(ADCx->DS_CONF, ADC_DS_CONF_DS_WIDTH, (Width << ADC_DS_CONF_DS_WIDTH_Pos));
}


/**
  * @brief  Get the width (in bit) of the output data from the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_WIDTH       LL_ADC_GetDSDataOutputWidth
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_12_BIT (default)
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_13_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_14_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_15_BIT
  *         @arg @ref LL_ADC_DS_DATA_WIDTH_16_BIT
  */
__STATIC_INLINE uint32_t LL_ADC_GetDSDataOutputWidth(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_CONF, ADC_DS_CONF_DS_WIDTH) >> ADC_DS_CONF_DS_WIDTH_Pos);
}


/**
  * @brief  Set the ratio of the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_RATIO       LL_ADC_SetDSDataOutputRatio
  * @param  ADCx ADC instance
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_1 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_2
  *         @arg @ref LL_ADC_DS_RATIO_4
  *         @arg @ref LL_ADC_DS_RATIO_8
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDSDataOutputRatio(ADC_TypeDef *ADCx, uint32_t Ratio)
{
  MODIFY_REG(ADCx->DS_CONF, ADC_DS_CONF_DS_RATIO, Ratio);
}


/**
  * @brief  Get the ratio of the Down Sampler (DS).
  * @rmtoll DS_CONF     DS_RATIO       LL_ADC_GetDSDataOutputRatio
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DS_RATIO_1 (no down sampling, default)
  *         @arg @ref LL_ADC_DS_RATIO_2
  *         @arg @ref LL_ADC_DS_RATIO_4
  *         @arg @ref LL_ADC_DS_RATIO_8
  *         @arg @ref LL_ADC_DS_RATIO_16
  *         @arg @ref LL_ADC_DS_RATIO_32
  *         @arg @ref LL_ADC_DS_RATIO_64
  *         @arg @ref LL_ADC_DS_RATIO_128
  */
__STATIC_INLINE uint32_t LL_ADC_GetDSDataOutputRatio(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_CONF, ADC_DS_CONF_DS_RATIO));
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Sequence_Configuration ADC Sequence Configuration functions
  * @{
  */

/**
  * @brief  Set ADC sequence: channel on the selected
  *         scan sequence rank.
  * @note   This function performs configuration of:
  *         - Channels ordering into each rank of scan sequence:
  *           whatever channel can be placed into whatever rank.
  * @note   On this STM32 series, ADCsequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @rmtoll SEQ_1     SEQ1            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ1            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ2            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ3            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ4            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ5            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ6            LL_ADC_SetSequencerRanks\n
  *         SEQ_1     SEQ7            LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ8            LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ9            LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ10           LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ11           LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ12           LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ13           LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ14           LL_ADC_SetSequencerRanks\n
  *         SEQ_2     SEQ15           LL_ADC_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RANK_1
  *         @arg @ref LL_ADC_RANK_2
  *         @arg @ref LL_ADC_RANK_3
  *         @arg @ref LL_ADC_RANK_4
  *         @arg @ref LL_ADC_RANK_5
  *         @arg @ref LL_ADC_RANK_6
  *         @arg @ref LL_ADC_RANK_7
  *         @arg @ref LL_ADC_RANK_8
  *         @arg @ref LL_ADC_RANK_9
  *         @arg @ref LL_ADC_RANK_10
  *         @arg @ref LL_ADC_RANK_11
  *         @arg @ref LL_ADC_RANK_12
  *         @arg @ref LL_ADC_RANK_13
  *         @arg @ref LL_ADC_RANK_14
  *         @arg @ref LL_ADC_RANK_15
  *         @arg @ref LL_ADC_RANK_16
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VINP0
  *         @arg @ref LL_ADC_CHANNEL_VINP1
  *         @arg @ref LL_ADC_CHANNEL_VINP2
  *         @arg @ref LL_ADC_CHANNEL_VINP3
  *         @arg @ref LL_ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINP3_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register and register position depending on parameter "Rank".         */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SEQ_1,
                                             ((Rank & ADC_SEQ_X_REGOFFSET_MASK) >> ADC_SEQ_X_REGOFFSET_POS));

  MODIFY_REG(*preg,
             ADC_SEQ_1_SEQ0 << (Rank & ADC_RANK_ID_SEQ_X_MASK),
             (Channel) << (Rank & ADC_RANK_ID_SEQ_X_MASK));
}


/**
  * @brief  Get ADC sequence: channel on the selected
  *         scan sequence rank.
  * @note   On this STM32 series, ADC sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @rmtoll SEQ_1     SEQ0            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ1            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ2            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ3            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ4            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ5            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ6            LL_ADC_GetSequencerRanks\n
  *         SEQ_1     SEQ7            LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ8            LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ9            LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ10           LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ11           LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ12           LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ13           LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ14           LL_ADC_GetSequencerRanks\n
  *         SEQ_2     SEQ15           LL_ADC_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RANK_1
  *         @arg @ref LL_ADC_RANK_2
  *         @arg @ref LL_ADC_RANK_3
  *         @arg @ref LL_ADC_RANK_4
  *         @arg @ref LL_ADC_RANK_5
  *         @arg @ref LL_ADC_RANK_6
  *         @arg @ref LL_ADC_RANK_7
  *         @arg @ref LL_ADC_RANK_8
  *         @arg @ref LL_ADC_RANK_9
  *         @arg @ref LL_ADC_RANK_10
  *         @arg @ref LL_ADC_RANK_11
  *         @arg @ref LL_ADC_RANK_12
  *         @arg @ref LL_ADC_RANK_13
  *         @arg @ref LL_ADC_RANK_14
  *         @arg @ref LL_ADC_RANK_15
  *         @arg @ref LL_ADC_RANK_16
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VINP0
  *         @arg @ref LL_ADC_CHANNEL_VINP1
  *         @arg @ref LL_ADC_CHANNEL_VINP2
  *         @arg @ref LL_ADC_CHANNEL_VINP3
  *         @arg @ref LL_ADC_CHANNEL_VINP0_VINM0
  *         @arg @ref LL_ADC_CHANNEL_VINP1_VINM1
  *         @arg @ref LL_ADC_CHANNEL_VINP2_VINM2
  *         @arg @ref LL_ADC_CHANNEL_VINP3_VINM3
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  */
__STATIC_INLINE uint32_t LL_ADC_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SEQ_1,
                                                   ((Rank & ADC_SEQ_X_REGOFFSET_MASK) >> ADC_SEQ_X_REGOFFSET_POS));

  return (uint32_t)((READ_BIT(*preg,
                              ADC_SEQ_1_SEQ0 << (Rank & ADC_RANK_ID_SEQ_X_MASK))
                     >> (Rank & ADC_RANK_ID_SEQ_X_MASK))
                   );
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Calibration_Points_Configuration ADC Calibration Points Configuration functions
  * @{
  */

/**
  * @brief  Configure the gain and the offset of the calibration point 1.
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Offset the signed offset of the first calibration point.
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureCalibPoint(ADC_TypeDef *ADCx, uint32_t Point, uint32_t Gain, uint32_t Offset)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->COMP_1, Point);

  MODIFY_REG(*preg, (ADC_COMP_1_GAIN1 | ADC_COMP_1_OFFSET1),
             ((Gain & ADC_COMP_1_GAIN1) | ((Offset << ADC_COMP_1_OFFSET1_Pos) & ADC_COMP_1_OFFSET1)));
}

/**
  * @brief  Set the gain of the calibration point 1.
  * @rmtoll COMP_1     GAIN1       LL_ADC_SetCalibPointGain
  * @param  ADCx ADC instance
  * @param  Gain the gain of the first calibration point.
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointGain(ADC_TypeDef *ADCx, uint32_t Point, uint32_t Gain)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->COMP_1, Point);

  MODIFY_REG(*preg, ADC_COMP_1_GAIN1, Gain);
}


/**
  * @brief  Get the gain of the calibration point 1.
  * @rmtoll COMP_1     GAIN1       LL_ADC_GetCalibPointGain
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval Return the gain of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointGain(const ADC_TypeDef *ADCx, uint32_t Point)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->COMP_1, Point);

  return (uint32_t)(READ_BIT(*preg, ADC_COMP_1_GAIN1));
}


/**
  * @brief  Set the offset of the calibration point 1.
  * @rmtoll COMP_1     OFFSET1       LL_ADC_SetCalibPointOffset
  * @param  ADCx ADC instance
  * @param  Offset the signed offset of the first calibration point.
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointOffset(ADC_TypeDef *ADCx, uint32_t Point, uint8_t Offset)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->COMP_1, Point);

  MODIFY_REG(*preg, ADC_COMP_1_OFFSET1, (Offset << ADC_COMP_1_OFFSET1_Pos));
}


/**
  * @brief  Get the offset of the calibration point 1.
  * @rmtoll COMP_1     OFFSET1       LL_ADC_GetCalibPointOffset
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @retval Return the signed offset of the first calibration point.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointOffset(const ADC_TypeDef *ADCx, uint32_t Point)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->COMP_1, Point);

  return (uint32_t)(READ_BIT(*preg, ADC_COMP_1_OFFSET1) >> ADC_COMP_1_OFFSET1_Pos);
}

/**
  * @brief  Set the use of a specific calibration point for ADC differential mode
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN8       LL_ADC_SetCalibPointForDiff
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForDiff(ADC_TypeDef *ADCx, uint32_t Point, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN2 << ADC_COMP_SEL_OFFSET_GAIN0_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN2_Pos + ADC_COMP_SEL_OFFSET_GAIN0_Pos)));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN2 << ADC_COMP_SEL_OFFSET_GAIN3_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN2_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN2 << ADC_COMP_SEL_OFFSET_GAIN6_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN2_Pos + ADC_COMP_SEL_OFFSET_GAIN6_Pos)));
  }
}


/**
  * @brief  Get what calibration point is used for ADC differential mode.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN8       LL_ADC_GetCalibPointForDiff
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForDiff(const ADC_TypeDef *ADCx, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN2)
                       >> ADC_COMP_SEL_OFFSET_GAIN2_Pos));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN2 << ADC_COMP_SEL_OFFSET_GAIN3_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN2_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN2 << ADC_COMP_SEL_OFFSET_GAIN6_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN2_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single positive mode
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN7       LL_ADC_SetCalibPointForSinglePos
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSinglePos(ADC_TypeDef *ADCx, uint32_t Point, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN1 << ADC_COMP_SEL_OFFSET_GAIN0_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN1_Pos + ADC_COMP_SEL_OFFSET_GAIN0_Pos)));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN1 << ADC_COMP_SEL_OFFSET_GAIN3_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN1_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN1 << ADC_COMP_SEL_OFFSET_GAIN6_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN1_Pos + ADC_COMP_SEL_OFFSET_GAIN6_Pos)));
  }
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single positive mode
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN7       LL_ADC_GetCalibPointForSinglePos
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSinglePos(const ADC_TypeDef *ADCx, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN1) >> ADC_COMP_SEL_OFFSET_GAIN1_Pos));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN1 << ADC_COMP_SEL_OFFSET_GAIN3_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN1_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN1 << ADC_COMP_SEL_OFFSET_GAIN6_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN1_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
}

/**
  * @brief  Set the use of a specific calibration point for
  *         ADC single negative mode
  *         and battery level detector.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN6       LL_ADC_SetCalibPointForSingleNeg
  * @param  ADCx ADC instance
  * @param  Point This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibPointForSingleNeg(ADC_TypeDef *ADCx, uint32_t Point, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN0 << ADC_COMP_SEL_OFFSET_GAIN0_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN0_Pos + ADC_COMP_SEL_OFFSET_GAIN0_Pos)));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN0 << ADC_COMP_SEL_OFFSET_GAIN3_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN0_Pos + ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    MODIFY_REG(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN0 << ADC_COMP_SEL_OFFSET_GAIN6_Pos),
               (Point << (ADC_COMP_SEL_OFFSET_GAIN0_Pos + ADC_COMP_SEL_OFFSET_GAIN6_Pos)));
  }
}


/**
  * @brief  Get what calibration point is used for
  *         ADC single negative mode
  *         and battery level detector.
  * @rmtoll COMP_SEL     ADC_COMP_SEL_OFFSET_GAIN6       LL_ADC_GetCalibPointForSingleNeg
  * @param  ADCx ADC instance
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_ADC_VIN_RANGE_1V2
  *         @arg @ref LL_ADC_VIN_RANGE_2V4
  *         @arg @ref LL_ADC_VIN_RANGE_3V6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_POINT_1
  *         @arg @ref LL_ADC_CALIB_POINT_2
  *         @arg @ref LL_ADC_CALIB_POINT_3
  *         @arg @ref LL_ADC_CALIB_POINT_4
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibPointForSingleNeg(const ADC_TypeDef *ADCx, uint32_t Range)
{
  if (Range == LL_ADC_VIN_RANGE_1V2)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN0) >> ADC_COMP_SEL_OFFSET_GAIN0_Pos));
  }
  else if (Range == LL_ADC_VIN_RANGE_2V4)
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN0 << ADC_COMP_SEL_OFFSET_GAIN3_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
  else
  {
    return ((uint32_t)(READ_BIT(ADCx->COMP_SEL, ADC_COMP_SEL_OFFSET_GAIN0 << ADC_COMP_SEL_OFFSET_GAIN6_Pos)
                       >> (ADC_COMP_SEL_OFFSET_GAIN3_Pos)));
  }
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_AWD_TH_Configuration ADC Watchdog Thresholds Configuration functions
  * @{
  */

/**
  * @brief  Configure the WatchDoG threshold low and high.
  * @rmtoll WD_TH     ADC_WD_TH_WD_LT       LL_ADC_ConfigureAWDThresholds\n
  *         WD_TH     ADC_WD_TH_WD_HT       LL_ADC_ConfigureAWDThresholds
  * @param  ADCx ADC instance
  * @param  LowThreshold This parameter is a 12-bit value.
  * @param  HighThreshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigureAWDThresholds(ADC_TypeDef *ADCx, uint32_t LowThreshold, uint32_t HighThreshold)
{
  MODIFY_REG(ADCx->WD_TH, (ADC_WD_TH_WD_LT | ADC_WD_TH_WD_HT), (LowThreshold | (HighThreshold << ADC_WD_TH_WD_HT_Pos)));
}


/**
  * @brief  Set the WatchDoG threshold low.
  * @rmtoll WD_TH     ADC_WD_TH_WD_LT     LL_ADC_SetAWDThresholdLow
  * @param  ADCx ADC instance
  * @param  Threshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAWDThresholdLow(ADC_TypeDef *ADCx, uint32_t Threshold)
{
  MODIFY_REG(ADCx->WD_TH, ADC_WD_TH_WD_LT, Threshold);
}


/**
  * @brief  Get the WatchDoG threshold low.
  * @rmtoll WD_TH     ADC_WD_TH_WD_LT     LL_ADC_GetAWDThresholdLow
  * @param  ADCx ADC instance
  * @retval Returned value of the low threshold.
  */
__STATIC_INLINE uint32_t LL_ADC_GetAWDThresholdLow(const ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->WD_TH, ADC_WD_TH_WD_LT)));
}

/**
  * @brief  Set the WatchDoG threshold high.
  * @rmtoll WD_TH     ADC_WD_TH_WD_HT     LL_ADC_SetAWDThresholdHigh
  * @param  ADCx ADC instance
  * @param  Threshold This parameter is a 12-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAWDThresholdHigh(ADC_TypeDef *ADCx, uint32_t Threshold)
{
  MODIFY_REG(ADCx->WD_TH, ADC_WD_TH_WD_HT, (Threshold << ADC_WD_TH_WD_HT_Pos));
}


/**
  * @brief  Get the WatchDoG threshold high.
  * @rmtoll WD_TH     ADC_WD_TH_WD_HT     LL_ADC_GetAWDThresholdHigh
  * @param  ADCx ADC instance
  * @retval Returned value of the high threshold.
  */
__STATIC_INLINE uint32_t LL_ADC_GetAWDThresholdHigh(const ADC_TypeDef *ADCx)
{
  return ((uint32_t)(READ_BIT(ADCx->WD_TH, ADC_WD_TH_WD_HT) >> ADC_WD_TH_WD_HT_Pos));
}


/**
  * @brief  Set the input channels the watchdog must check.
  * @note   ChannelMask can be an OR of the listed parameters.
  * @rmtoll WD_CONF     AWD_CHX       LL_ADC_SetAWDInputChannels
  * @param  ADCx ADC instance
  * @param  ChannelMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_AWD_CH_VINM0
  *         @arg @ref LL_ADC_AWD_CH_VINM1
  *         @arg @ref LL_ADC_AWD_CH_VINM2
  *         @arg @ref LL_ADC_AWD_CH_VINM3
  *         @arg @ref LL_ADC_AWD_CH_MICROM
  *         @arg @ref LL_ADC_AWD_CH_VBAT
  *         @arg @ref LL_ADC_AWD_CH_GND_NEG
  *         @arg @ref LL_ADC_AWD_CH_VDDA_NEG
  *         @arg @ref LL_ADC_AWD_CH_VINP0
  *         @arg @ref LL_ADC_AWD_CH_VINP1
  *         @arg @ref LL_ADC_AWD_CH_VINP2
  *         @arg @ref LL_ADC_AWD_CH_VINP3
  *         @arg @ref LL_ADC_AWD_CH_MICROP
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR
  *         @arg @ref LL_ADC_AWD_CH_GND_POS
  *         @arg @ref LL_ADC_AWD_CH_VDDA_POS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAWDInputChannels(ADC_TypeDef *ADCx, uint32_t ChannelMask)
{
  MODIFY_REG(ADCx->WD_CONF, ADC_WD_CONF_AWD_CHX, ChannelMask);
}


/**
  * @brief  Get the input channels the watchdog must check.
  * @note   The returned value can be an OR of the listed parameters.
  * @rmtoll WD_CONF     AWD_CHX       LL_ADC_GetAWDInputChannels
  * @param  ADCx ADC instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_AWD_CH_VINM0
  *         @arg @ref LL_ADC_AWD_CH_VINM1
  *         @arg @ref LL_ADC_AWD_CH_VINM2
  *         @arg @ref LL_ADC_AWD_CH_VINM3
  *         @arg @ref LL_ADC_AWD_CH_MICROM
  *         @arg @ref LL_ADC_AWD_CH_VBAT
  *         @arg @ref LL_ADC_AWD_CH_GND_NEG
  *         @arg @ref LL_ADC_AWD_CH_VDDA_NEG
  *         @arg @ref LL_ADC_AWD_CH_VINP0
  *         @arg @ref LL_ADC_AWD_CH_VINP1
  *         @arg @ref LL_ADC_AWD_CH_VINP2
  *         @arg @ref LL_ADC_AWD_CH_VINP3
  *         @arg @ref LL_ADC_AWD_CH_MICROP
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR
  *         @arg @ref LL_ADC_AWD_CH_GND_POS
  *         @arg @ref LL_ADC_AWD_CH_VDDA_POS
  */
__STATIC_INLINE uint32_t LL_ADC_GetAWDInputChannels(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->WD_CONF, ADC_WD_CONF_AWD_CHX));
}


/**
  * @}
  */


/** @defgroup ADC_LL_EF_Output_Data ADC Output Data functions
  * @{
  */


/**
  * @brief  Get the 16-bit output data from the Down Sampler (DS).
  * @rmtoll DS_DATAOUT       DS_DATA          LL_ADC_DSGetOutputData
  * @param  ADCx ADC instance
  * @retval The output data from DS.
  */
__STATIC_INLINE uint32_t LL_ADC_DSGetOutputData(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DS_DATAOUT, ADC_DS_DATAOUT_DS_DATA));
}

#if defined(ADC_DF_DATAOUT_DF_DATA)
/**
  * @brief  Get the 16-bit output data from the Decimation Filter (DF).
  * @rmtoll DF_DATAOUT       DF_DATA          LL_ADC_DFGetOutputData
  * @param  ADCx ADC instance
  * @retval The output data from DF.
  */
__STATIC_INLINE uint32_t LL_ADC_DFGetOutputData(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DF_DATAOUT, ADC_DF_DATAOUT_DF_DATA));
}
#endif /* DF_DATAOUT */

/**
  * @}
  */


/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */

/**
  * @brief  Get all the flags status.
  * @param  ADCx ADC instance
  * @retval All the status flags of the register IRQ_STATUS.
  *         The value is a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD1
  *         @arg @ref LL_ADC_IRQ_FLAG_EOC
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  */
__STATIC_INLINE uint32_t LL_ADC_GetActiveFlags(ADC_TypeDef *ADCx)
{
#if defined(LL_ADC_IRQ_FLAGS_MASK)
  return (uint32_t)(READ_BIT(ADCx->IRQ_STATUS, LL_ADC_IRQ_FLAGS_MASK));
#else
  return 0;
#endif /* LL_ADC_IRQ_FLAGS_MASK */
}

/**
  * @brief  Clear all the flags status.
  * @param  ADCx ADC instance
  * @param  FlagsMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD1
  *         @arg @ref LL_ADC_IRQ_FLAG_EOC
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_ClearActiveFlags(ADC_TypeDef *ADCx, uint32_t FlagsMask)
{
  WRITE_REG(ADCx->IRQ_STATUS, FlagsMask);
}

/**
  * @brief  Get if the flags status is set.
  * @param  ADCx ADC instance
  * @param  FlagsMask This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD1
  *         @arg @ref LL_ADC_IRQ_FLAG_EOC
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag(const ADC_TypeDef *ADCx, uint32_t FlagsMask)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, FlagsMask) == (FlagsMask)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_STATUS_DF_OVRFL_IRQ)
/**
  * @brief  Get the status of the flag DF_OVRFL.
  *         The flag indicates, if set, the Decimation Filter output is saturated.
  * @rmtoll IRQ_STATUS      DF_OVRFL_IRQ     LL_ADC_IsActiveFlag_DFOVRFL
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_DFOVRFL(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_DF_OVRFL_IRQ) == (ADC_IRQ_STATUS_DF_OVRFL_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag DF_OVRFL.
  * @rmtoll IRQ_STATUS      DF_OVRFL_IRQ     LL_ADC_ClearFlag_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_DFOVRFL(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_DF_OVRFL_IRQ);
}
#endif /* ADC_IRQ_STATUS_DF_OVRFL_IRQ */

#if defined(ADC_IRQ_STATUS_OVR_DF_IRQ)
/**
  * @brief  Get the status of the flag OVR_DF.
  *         The flag indicates, if set, the Decimation Filter output is overran (at least one data is lost).
  * @rmtoll IRQ_STATUS      OVR_DF_IRQ     LL_ADC_IsActiveFlag_OVRDF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVRDF(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DF_IRQ) == (ADC_IRQ_STATUS_OVR_DF_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag OVR_DF.
  * @rmtoll IRQ_STATUS      OVR_DF_IRQ     LL_ADC_ClearFlag_OVRDF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVRDF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DF_IRQ);
}
#endif /* ADC_IRQ_STATUS_OVR_DF_IRQ */

/**
  * @brief  Get the status of the flag OVR_DS.
  *         The flag indicates, if set, the Down Sampler output is overran (at least one data is lost).
  * @rmtoll IRQ_STATUS      OVR_DS_IRQ     LL_ADC_IsActiveFlag_OVRDS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVRDS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DS_IRQ) == (ADC_IRQ_STATUS_OVR_DS_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag OVR_DS.
  * @rmtoll IRQ_STATUS      OVR_DS_IRQ     LL_ADC_ClearFlag_OVRDS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVRDS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_OVR_DS_IRQ);
}

/**
  * @brief  Get the status of the flag AWD.
  *         The flag indicates, if set, an event of the watchdog has occurred.
  * @rmtoll IRQ_STATUS      AWD_IRQ     LL_ADC_IsActiveFlag_AWD
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_AWD_IRQ) == (ADC_IRQ_STATUS_AWD_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag AWD.
  * @rmtoll IRQ_STATUS      AWD_IRQ     LL_ADC_ClearFlag_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_AWD_IRQ);
}

/**
  * @brief  Get the status of the flag EOS.
  *         The flag indicates, if set, the End Of a Sequence of conversion.
  * @rmtoll IRQ_STATUS      EOS_IRQ     LL_ADC_IsActiveFlag_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOS_IRQ) == (ADC_IRQ_STATUS_EOS_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag EOS.
  * @rmtoll IRQ_STATUS      EOS_IRQ     LL_ADC_ClearFlag_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOS_IRQ);
}

#if defined(ADC_IRQ_STATUS_EODF_IRQ)
/**
  * @brief  Get the status of the flag EODF.
  *         The flag indicates, if set, the End Of a Decimation Filter conversion.
  * @rmtoll IRQ_STATUS      EODF_IRQ     LL_ADC_IsActiveFlag_EODF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EODF(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODF_IRQ) == (ADC_IRQ_STATUS_EODF_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag EODF.
  * @rmtoll IRQ_STATUS      EODF_IRQ     LL_ADC_ClearFlag_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EODF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODF_IRQ);
}
#endif /* ADC_IRQ_STATUS_EODF_IRQ */

/**
  * @brief  Get the status of the flag EODS.
  *         The flag indicates, if set, the End Of a Down Sampler conversion.
  * @rmtoll IRQ_STATUS      EODS_IRQ     LL_ADC_IsActiveFlag_EODS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EODS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODS_IRQ) == (ADC_IRQ_STATUS_EODS_IRQ)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flag EODS.
  * @rmtoll IRQ_STATUS      EODS_IRQ     LL_ADC_ClearFlag_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EODS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EODS_IRQ);
}

/**
  * @brief  Get the status of the flag EOC.
  *         The flag indicates, if set, the End Of Conversion.
  * @rmtoll IRQ_STATUS      EOC_IRQ     LL_ADC_IsActiveFlag_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOC_IRQ) == (ADC_IRQ_STATUS_EOC_IRQ)) ? 1UL : 0UL);
}


/**
  * @brief  Clear the flag EOC.
  * @rmtoll IRQ_STATUS      EOC_IRQ     LL_ADC_ClearFlag_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->IRQ_STATUS, ADC_IRQ_STATUS_EOC_IRQ);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable the interrupts according to the interrupt mask passed as parameter.
  * @param  ADCx ADC instance
  * @param  IrqMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_EN_OVRFL
  *         @arg @ref LL_ADC_IRQ_EN_OVRDF
  *         @arg @ref LL_ADC_IRQ_EN_EODF
  *         @arg @ref LL_ADC_IRQ_EN_OVRDS
  *         @arg @ref LL_ADC_IRQ_EN_AWD1
  *         @arg @ref LL_ADC_IRQ_EN_EOS
  *         @arg @ref LL_ADC_IRQ_EN_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_EnableIT(ADC_TypeDef *ADCx, uint32_t IrqMask)
{
  SET_BIT(ADCx->IRQ_ENABLE, IrqMask);
}


/**
  * @brief  Disable the interrupts according to the interrupt mask passed as parameter.
  * @param  ADCx ADC instance
  * @param  IrqMask This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IRQ_EN_OVRFL
  *         @arg @ref LL_ADC_IRQ_EN_OVRDF
  *         @arg @ref LL_ADC_IRQ_EN_EODF
  *         @arg @ref LL_ADC_IRQ_EN_OVRDS
  *         @arg @ref LL_ADC_IRQ_EN_AWD1
  *         @arg @ref LL_ADC_IRQ_EN_EOS
  *         @arg @ref LL_ADC_IRQ_EN_EODS
  * @retval None.
  */
__STATIC_INLINE void LL_ADC_DisableIT(ADC_TypeDef *ADCx, uint32_t IrqMask)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, IrqMask);
}


/**
  * @brief  Get if the specific flag is enabled or not.
  * @param  ADCx ADC instance
  * @param  IrqMask This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRFL
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDF
  *         @arg @ref LL_ADC_IRQ_FLAG_EODF
  *         @arg @ref LL_ADC_IRQ_FLAG_OVRDS
  *         @arg @ref LL_ADC_IRQ_FLAG_AWD1
  *         @arg @ref LL_ADC_IRQ_FLAG_EOC
  *         @arg @ref LL_ADC_IRQ_FLAG_EOS
  *         @arg @ref LL_ADC_IRQ_FLAG_EODS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT(const ADC_TypeDef *ADCx, uint32_t IrqMask)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, IrqMask) == (IrqMask)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA)
/**
  * @brief  Enable the Decimation Filter saturated interrupt.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_EnableIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DFOVRFL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA);
}


/**
  * @brief  Disable the Decimation Filter saturated interrupt.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_DisableIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DFOVRFL(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA);
}

/**
  * @brief  Check if the Decimation Filter saturated interrupt is enabled.
  * @rmtoll IRQ_ENABLE     DF_OVRFL_IRQ_ENA     LL_ADC_IsEnabledIT_DFOVRFL
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DFOVRFL(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA) == (ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA))
          ? 1UL : 0UL);
}
#endif /* ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA */

#if defined(ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)
/**
  * @brief  Enable the Decimation Filter overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_EnableIT_DFOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DFOVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA);
}


/**
  * @brief  Disable the Decimation Filter overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_DisableIT_DFOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DFOVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA);
}


/**
  * @brief  Check if the Decimation Filter overrun interrupt is enabled.
  * @rmtoll IRQ_ENABLE     OVR_DF_IRQ_ENA     LL_ADC_IsEnabledIT_DFOVR
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DFOVR(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA) == (ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA)) ? 1UL : 0UL);
}
#endif /* ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA */

/**
  * @brief  Enable the Down Sampler overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_EnableIT_DSOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_DSOVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA);
}


/**
  * @brief  Disable the Down Sampler overrun interrupt.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_DisableIT_DSOVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_DSOVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA);
}


/**
  * @brief  Check if the Down Sampler overrun interrupt is enabled.
  * @rmtoll IRQ_ENABLE     OVR_DS_IRQ_ENA     LL_ADC_IsEnabledIT_DSOVR
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_DSOVR(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA) == (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the watchdog event interrupt.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_EnableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA);
}


/**
  * @brief  Disable the watchdog event interrupt.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_DisableIT_AWD
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA);
}


/**
  * @brief  Check if the watchdog event interrupt is enabled.
  * @rmtoll IRQ_ENABLE     AWD_IRQ_ENA     LL_ADC_IsEnabledIT_AWD
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_AWD_IRQ_ENA) == (ADC_IRQ_ENABLE_AWD_IRQ_ENA)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the End Of a Sequence of conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_EnableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Sequence of conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_DisableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Sequence of conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EOS_IRQ_ENA     LL_ADC_IsEnabledIT_EOS
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOS_IRQ_ENA) == (ADC_IRQ_ENABLE_EOS_IRQ_ENA)) ? 1UL : 0UL);
}

#if defined(ADC_IRQ_ENABLE_EODF_IRQ_ENA)
/**
  * @brief  Enable the End Of a Decimation Filter conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_EnableIT_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EODF(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Decimation Filter conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_DisableIT_EODF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EODF(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Decimation Filter conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EODF_IRQ_ENA     LL_ADC_IsEnabledIT_EODF
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EODF(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODF_IRQ_ENA) == (ADC_IRQ_ENABLE_EODF_IRQ_ENA)) ? 1UL : 0UL);
}
#endif /* ADC_IRQ_ENABLE_EODF_IRQ_ENA */

/**
  * @brief  Enable the End Of a Down Sampler conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_EnableIT_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EODS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA);
}


/**
  * @brief  Disable the End Of a Down Sampler conversion interrupt.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_DisableIT_EODS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EODS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA);
}


/**
  * @brief  Check if the End Of a Down Sampler conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EODS_IRQ_ENA     LL_ADC_IsEnabledIT_EODS
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EODS(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EODS_IRQ_ENA) == (ADC_IRQ_ENABLE_EODS_IRQ_ENA)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the End Of Conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOC_IRQ_ENA     LL_ADC_EnableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOC_IRQ_ENA);
}


/**
  * @brief  Disable the End Of Conversion interrupt.
  * @rmtoll IRQ_ENABLE     EOC_IRQ_ENA     LL_ADC_DisableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOC_IRQ_ENA);
}


/**
  * @brief  Check if the End Of Conversion interrupt is enabled.
  * @rmtoll IRQ_ENABLE     EOC_IRQ_ENA     LL_ADC_IsEnabledIT_EOC
  * @param  ADCx ADC instance
  * @retval 0: The interrupt is not enabled, 1: The interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOC(const ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IRQ_ENABLE, ADC_IRQ_ENABLE_EOC_IRQ_ENA) == (ADC_IRQ_ENABLE_EOC_IRQ_ENA)) ? 1UL : 0UL);
}

/**
  * @}
  */


/** @defgroup ADC_LL_EF_Delay_Setting ADC Dealy Setting
  * @{
  */

#if defined(ADC_TIMER_CONF_VBIAS_PRECH_DELAY)
/**
  * @brief  Set the duration of a waiting time starting at rising edge of
  *         PGA_EN signal and corresponding to the VBIAS precharge duration.
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 128 us.
  * @note   The minimum recommended value for this bitfield is 150 to have 600 us.
  * @rmtoll TIMER_CONF     VBIAS_PRECH_DELAY       LL_ADC_SetVbiasPrechargeDelay
  * @param  ADCx ADC instance
  * @param  Delay This parameter is a 8-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetVbiasPrechargeDelay(ADC_TypeDef *ADCx, uint32_t Delay)
{
  MODIFY_REG(ADCx->TIMER_CONF, ADC_TIMER_CONF_VBIAS_PRECH_DELAY, Delay << ADC_TIMER_CONF_VBIAS_PRECH_DELAY_Pos);
}


/**
  * @brief  Get the duration of a waiting time starting at rising edge of
  *         PGA_EN signal and corresponding to the VBIAS precharge duration.
  *         The time unit is 4 us. Max delay is 1.02 ms.
  * @note   The minimum recommended value for this bitfield is 150 to have 600 us.
  * @rmtoll TIMER_CONF     VBIAS_PRECH_DELAY       LL_ADC_GetVbiasPrechargeDelay
  * @param  ADCx ADC instance
  * @retval Returned value is a 8-bit value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetVbiasPrechargeDelay(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_VBIAS_PRECH_DELAY));
}

/**
  * @brief  Enable the 1024x prescaler used to compute the duration of VBIAS
  *         precharge duration
  * @note   The time unit is 4 us with prescaler disabled.
  *         The time unit is 4096 us with prescaler enabled.
  * @rmtoll TIMER_CONF     PRECH_DELAY_SEL       LL_ADC_VbiasPrechargeDelayPrescalerEnable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_VbiasPrechargeDelayPrescalerEnable(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_PRECH_DELAY_SEL);
}

/**
  * @brief  Enable the 1024x prescaler used to compute the duration of VBIAS
  *         precharge duration
  * @note   The time unit is 4 us with prescaler disabled.
  *         The time unit is 4096 us with prescaler enabled.
  * @rmtoll TIMER_CONF     PRECH_DELAY_SEL       LL_ADC_VbiasPrechargeDelayPrescalerDisable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_VbiasPrechargeDelayPrescalerDisable(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_PRECH_DELAY_SEL);
}

#endif /* ADC_TIMER_CONF_VBIAS_PRECH_DELAY */

#if defined (ADC_TIMER_CONF_ADC_LDO_DELAY)
/**
  * @brief  Set the duration of the waiting time between the ADC_LDO enable and
  *         the ADC_ON, to let time to the LDO to stabilize itself before
  *         starting a conversion
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 160 us.
  * @rmtoll TIMER_CONF     ADC_LDO_DELAY       LL_ADC_SetADCLDODelay
  * @param  ADCx ADC instance
  * @param  Delay This parameter is a 8-bit value.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetADCLDODelay(ADC_TypeDef *ADCx, uint32_t Delay)
{
  MODIFY_REG(ADCx->TIMER_CONF, ADC_TIMER_CONF_ADC_LDO_DELAY, Delay);
}


/**
  * @brief  Get the duration of the waiting time between the ADC_LDO enable and
  *         the ADC_ON, to let time to the LDO to stabilize itself before
  *         starting a conversion
  *         The time unit is 4 us. Max delay is 1.02 ms, default value is 160 us.
  * @rmtoll TIMER_CONF     ADC_LDO_DELAY       LL_ADC_GetADCLDODelay
  * @param  ADCx ADC instance
  * @retval Returned value is a 8-bit value.
  */
__STATIC_INLINE uint32_t LL_ADC_GetADCLDODelay(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->TIMER_CONF, ADC_TIMER_CONF_ADC_LDO_DELAY));
}
#endif /* ADC_TIMER_CONF_ADC_LDO_DELAY */


/**
  * @}
  */


/** @defgroup ADC_LL_CALIB_CONVERSION ADC Calibration and Conversion functions
  * @{
  */


/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_3V6) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended positive input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_3V6(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_3V6) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return (int8_t)calibration_offset;
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_2V4(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_2V4) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended positive input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_2V4(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_2V4) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return (int8_t)calibration_offset;
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended positive input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINPX_1V2(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_1V2) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended positive input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_1V2(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINPX_1V2) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return (int8_t)calibration_offset;
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_3V6(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_3V6) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended negative input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_3V6(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_3V6) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return - (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return - (int8_t)calibration_offset;
}

/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_2V4(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_2V4) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended negative input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_2V4(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_2V4) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return - (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return - (int8_t)calibration_offset;
}


/**
  * @brief  Return the calibration value for the gain of
  *         single ended negative input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINMX_1V2(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_1V2) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         single ended negative input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINMX_1V2(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINMX_1V2) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return - (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return - (int8_t)calibration_offset;
}


/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_3V6(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_3V6) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         differential input at range 3.6 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_3V6(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_3V6) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return ((int8_t)calibration_offset);
}

/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_2V4(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_2V4) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         differential input at range 2.4 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_2V4(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_2V4) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return ((int8_t)calibration_offset);
}


/**
  * @brief  Return the calibration value for the gain of
  *         differential input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE uint16_t LL_ADC_GET_CALIB_GAIN_FOR_VINDIFF_1V2(void)
{
  return (uint16_t)((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_1V2) & 0xFFFUL);
}


/**
  * @brief  Return the calibration value for the offset of
  *         differential input at range 1.2 V.
  *         Use the function LL_ADC_ConfigureCalibPointX() with X = 1, 2, 3 or 4.
  * @retval Returned value to be put in COMP_X register if 0xFFFFFFFF means no calibration point.
  */
__STATIC_INLINE int8_t LL_ADC_GET_CALIB_OFFSET_FOR_VINDIFF_1V2(void)
{
  int8_t calibration_offset = ((*(uint32_t *)ADC_CALIB_ADDRESS_VINDIFF_1V2) >> 12UL);

#if defined(STM32WB07) || defined(STM32WB06)
  if (*(uint32_t *)ADC_LAYOUT_ID == 0UL)  /* Memory version 1 */
  {
    /* Negative number on 7-bit */
    if ((calibration_offset & 0x40U) == 0x40U)
    {
      return (int8_t)(calibration_offset | 0x80U);
    }
  }
#endif /* defined(STM32WB07) || defined(STM32WB06) */

  return ((int8_t)calibration_offset);
}

/**
  * @}
  */


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/* De-initialization of ADC instance */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *ADCx);

/* Initialization of ADC instance */
ErrorStatus LL_ADC_Init(ADC_TypeDef *ADCx, const LL_ADC_InitTypeDef *pADC_InitStruct);

/* Initialization of some features of ADC instance */
ErrorStatus LL_ADC_VoltageRangeInit(ADC_TypeDef *ADCx, const LL_ADC_VoltRangeInitTypeDef *pVoltRange_InitStruct);
ErrorStatus LL_ADC_SequenceInit(ADC_TypeDef *ADCx, const LL_ADC_SequenceInitTypeDef *pSequence_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32WB0x_LL_ADC_H */
