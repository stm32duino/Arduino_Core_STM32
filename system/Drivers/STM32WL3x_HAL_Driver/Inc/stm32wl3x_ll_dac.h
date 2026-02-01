/**
  ******************************************************************************
  * @file    stm32wl3x_ll_dac.h
  * @author  MCD Application Team
  * @brief   Header file of DAC LL module.
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
#ifndef STM32WL3x_LL_DAC_H
#define STM32WL3x_LL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x.h"

/** @addtogroup STM32WL3x_LL_Driver
  * @{
  */

#if defined(DAC1)

/** @defgroup DAC_LL DAC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup DAC_LL_Private_Constants DAC Private Constants
  * @{
  */

/* Internal masks for DAC channels definition */
/* To select into literal LL_DAC_CHANNEL_x the relevant bits for:             */
/* - channel bits position into registers CR, MCR, CCR, SHHR, SHRR            */
/* - channel bits position into register SWTRIG                               */
/* - channel register offset of data holding register DHRx                    */
/* - channel register offset of data output register DORx                     */
#define DAC_CR_CH1_BITOFFSET           0UL   /* Position of channel bits into registers
                                                CR, MCR, CCR, SHHR, SHRR of channel 1 */
#define DAC_CR_CHX_BITOFFSET_MASK      (DAC_CR_CH1_BITOFFSET)

#define DAC_SWTR_CH1                   (DAC_SWTRIGR_SWTRIG)  /* Channel bit into register SWTRIGR of channel 1. */
#define DAC_SWTR_CHX_MASK              (DAC_SWTR_CH1)


/* Miscellaneous data */
#define DAC_DIGITAL_SCALE_12BITS                  63UL     /* Full-scale digital value with a resolution of 6
                                                              bits (voltage range determined by analog voltage
                                                              references Vref+ and Vref-, refer to reference manual) */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup DAC_LL_Private_Macros DAC Private Macros
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
#define __DAC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup DAC_LL_ES_INIT DAC Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of DAC instance.
  */
typedef struct
{
  uint32_t TriggerSource;               /*!< Set the conversion trigger source for the selected DAC channel:
                                             internal (SW start) or from external peripheral
                                             (timer event, external interrupt line).
                                             This parameter can be a value of @ref DAC_LL_EC_TRIGGER_SOURCE

                                             This feature can be modified afterwards using unitary
                                             function @ref LL_DAC_SetTriggerSource(). */

  uint32_t WaveAutoGeneration;          /*!< Set the waveform automatic generation mode for the selected DAC channel.
                                             This parameter can be a value of @ref DAC_LL_EC_WAVE_AUTO_GENERATION_MODE

                                             This feature can be modified afterwards using unitary
                                             function @ref LL_DAC_SetWaveAutoGeneration(). */

  uint32_t WaveAutoGenerationConfig;    /*!< Set the waveform automatic generation mode for the selected DAC channel.
                                             If waveform automatic generation mode is set to noise, this parameter
                                             can be a value of @ref DAC_LL_EC_WAVE_NOISE_LFSR_UNMASK_BITS
                                             If waveform automatic generation mode is set to triangle,
                                             this parameter can be a value of @ref DAC_LL_EC_WAVE_TRIANGLE_AMPLITUDE
                                             @note If waveform automatic generation mode is disabled,
                                              this parameter is discarded.

                                             This feature can be modified afterwards using unitary
                                             function @ref LL_DAC_SetWaveNoiseLFSR(),
                                             @ref LL_DAC_SetWaveTriangleAmplitude()
                                             depending on the wave automatic generation selected. */

  uint32_t OutputBuffer;                /*!< Set the output buffer for the selected DAC channel.
                                             This parameter can be a value of @ref DAC_LL_EC_OUTPUT_BUFFER

                                             This feature can be modified afterwards using unitary
                                             function @ref LL_DAC_SetOutputBuffer(). */

  uint32_t OutputConnection;            /*!< Set the output connection for the selected DAC channel.
                                             This parameter can be a value of @ref DAC_LL_EC_OUTPUT_CONNECTION

                                             This feature can be modified afterwards using unitary
                                             function @ref LL_DAC_SetOutputConnection(). */

} LL_DAC_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Constants DAC Exported Constants
  * @{
  */

/** @defgroup DAC_LL_EC_GET_FLAG DAC flags
  * @brief    Flags defines which can be used with LL_DAC_ReadReg function
  * @{
  */
/* DAC channel 1 flags */
#define LL_DAC_FLAG_DMAUDR                 (DAC_SR_DMAUDR)    /*!< DAC channel 1 flag DMA underrun */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_IT DAC interruptions
  * @brief    IT defines which can be used with LL_DAC_ReadReg and  LL_DAC_WriteReg functions
  * @{
  */
#define LL_DAC_IT_DMAUDRIE                 (DAC_CR_DMAUDRIE) /*!< DAC channel 1 interruption DMA underrun */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_CHANNEL DAC channels
  * @{
  */
#define LL_DAC_CHANNEL_1                   (DAC_CR_CH1_BITOFFSET | DAC_SWTR_CH1) /*!< DAC channel 1 */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_TRIGGER_SOURCE DAC trigger source
  * @{
  */
#define LL_DAC_TRIG_SOFTWARE               (DAC_CR_TSEL_2 | DAC_CR_TSEL_1 | DAC_CR_TSEL_0) /*!< DAC channel conversion trigger internal (SW start) */
#define LL_DAC_TRIG_EXT_TIM16_TRGO         (                                        0x0UL) /*!< DAC channel conversion trigger from external peripheral: TIM16 TRGO. */
#define LL_DAC_TRIG_EXT_EXTI_LINE8         (                                DAC_CR_TSEL_0) /*!< DAC channel conversion trigger from external peripheral: external interrupt line 8. */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_WAVE_AUTO_GENERATION_MODE DAC waveform automatic generation mode
  * @{
  */
#define LL_DAC_WAVE_AUTO_GENERATION_NONE     0x00000000UL                   /*!< DAC channel wave auto generation mode disabled. */
#define LL_DAC_WAVE_AUTO_GENERATION_NOISE    (               DAC_CR_WAVE_0) /*!< DAC channel wave auto generation mode enabled, set generated noise waveform. */
#define LL_DAC_WAVE_AUTO_GENERATION_TRIANGLE (DAC_CR_WAVE_1               ) /*!< DAC channel wave auto generation mode enabled, set generated triangle waveform. */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_WAVE_NOISE_LFSR_UNMASK_BITS DAC wave generation - Noise LFSR unmask bits
  * @{
  */
#define LL_DAC_NOISE_LFSR_UNMASK_BIT0      0x00000000UL                                                      /*!< Noise wave generation, unmask LFSR bit0, for the selected DAC channel */
#define LL_DAC_NOISE_LFSR_UNMASK_BITS1_0   (                                                  DAC_CR_MAMP_0) /*!< Noise wave generation, unmask LFSR bits[1:0], for the selected DAC channel */
#define LL_DAC_NOISE_LFSR_UNMASK_BITS2_0   (                                  DAC_CR_MAMP_1                ) /*!< Noise wave generation, unmask LFSR bits[2:0], for the selected DAC channel */
#define LL_DAC_NOISE_LFSR_UNMASK_BITS3_0   (                                  DAC_CR_MAMP_1 | DAC_CR_MAMP_0) /*!< Noise wave generation, unmask LFSR bits[3:0], for the selected DAC channel */
#define LL_DAC_NOISE_LFSR_UNMASK_BITS4_0   (                  DAC_CR_MAMP_2                                ) /*!< Noise wave generation, unmask LFSR bits[4:0], for the selected DAC channel */
#define LL_DAC_NOISE_LFSR_UNMASK_BITS5_0   (                  DAC_CR_MAMP_2                 | DAC_CR_MAMP_0) /*!< Noise wave generation, unmask LFSR bits[5:0], for the selected DAC channel */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_WAVE_TRIANGLE_AMPLITUDE DAC wave generation - Triangle amplitude
  * @{
  */
#define LL_DAC_TRIANGLE_AMPLITUDE_1        0x00000000UL                                                     /*!< Triangle wave generation, amplitude of 1 LSB of DAC output range, for the selected DAC channel */
#define LL_DAC_TRIANGLE_AMPLITUDE_3        (                                                 DAC_CR_MAMP_0) /*!< Triangle wave generation, amplitude of 3 LSB of DAC output range, for the selected DAC channel */
#define LL_DAC_TRIANGLE_AMPLITUDE_7        (                                 DAC_CR_MAMP_1                ) /*!< Triangle wave generation, amplitude of 7 LSB of DAC output range, for the selected DAC channel */
#define LL_DAC_TRIANGLE_AMPLITUDE_15       (                                 DAC_CR_MAMP_1 | DAC_CR_MAMP_0) /*!< Triangle wave generation, amplitude of 15 LSB of DAC output range, for the selected DAC channel */
#define LL_DAC_TRIANGLE_AMPLITUDE_31       (                 DAC_CR_MAMP_2                                ) /*!< Triangle wave generation, amplitude of 31 LSB of DAC output range, for the selected DAC channel */
#define LL_DAC_TRIANGLE_AMPLITUDE_63       (                 DAC_CR_MAMP_2                 | DAC_CR_MAMP_0) /*!< Triangle wave generation, amplitude of 63 LSB of DAC output range, for the selected DAC channel */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_OUTPUT_BUFFER DAC channel output buffer
  * @{
  */
#define LL_DAC_OUTPUT_BUFFER_ENABLE        (DAC_CR_BON)            /*!< The selected DAC channel output is buffered: higher drive current capability, but also higher current consumption */
#define LL_DAC_OUTPUT_BUFFER_DISABLE       0x00000000UL            /*!< The selected DAC channel output is not buffered: lower drive current capability, but also lower current consumption */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_OUTPUT_CONNECTION DAC channel output connection
  * @{
  */
#define LL_DAC_OUTPUT_CONNECT_GPIO         0x00000000UL            /*!< The selected DAC channel output is connected to external pin */
#define LL_DAC_OUTPUT_CONNECT_INTERNAL     (DAC_CR_CMPEN)          /*!< The selected DAC channel output is connected to on-chip peripherals via internal paths. On this STM32 series, output connection depends on output mode (normal or sample and hold) and output buffer state. Refer to comments of function @ref LL_DAC_SetOutputConnection(). */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_RESOLUTION  DAC channel output resolution
  * @{
  */
#define LL_DAC_RESOLUTION_6B               0x00000000UL            /*!< DAC channel resolution 6 bits */
/**
  * @}
  */

/** @defgroup DAC_LL_EC_HW_DELAYS  Definitions of DAC hardware constraints delays
  * @note   Only DAC peripheral HW delays are defined in DAC LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for DAC channel voltage settling time from DAC channel startup       */
/* (transition from disable to enable).                                       */
/* Note: DAC channel startup time depends on board application environment:   */
/*       impedance connected to DAC channel output.                           */
/*       The delay below is specified under conditions:                       */
/*        - voltage maximum transition (lowest to highest value)              */
/*        - until voltage reaches final value +-1LSB                          */
/*        - DAC channel output buffer enabled                                 */
/*        - load impedance of 5kOhm (min), 50pF (max)                         */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tWAKEUP").                                                      */
/* Unit: us                                                                   */
#define LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US             15UL /*!< Delay for DAC channel voltage settling time from DAC channel startup (transition from disable to enable) */

/* Delay for DAC channel voltage settling time.                               */
/* Note: DAC channel startup time depends on board application environment:   */
/*       impedance connected to DAC channel output.                           */
/*       The delay below is specified under conditions:                       */
/*        - voltage maximum transition (lowest to highest value)              */
/*        - until voltage reaches final value +-1LSB                          */
/*        - DAC channel output buffer enabled                                 */
/*        - load impedance of 5kOhm min, 50pF max                             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSETTLING").                                                    */
/* Unit: us                                                                   */
#define LL_DAC_DELAY_VOLTAGE_SETTLING_US                    12UL /*!< Delay for DAC channel voltage settling time */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Macros DAC Exported Macros
  * @{
  */

/** @defgroup DAC_LL_EM_WRITE_READ Common write and read registers macros
  * @{
  */

/**
  * @brief  Write a value in DAC register
  * @param  __INSTANCE__ DAC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DAC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DAC register
  * @param  __INSTANCE__ DAC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DAC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**
  * @}
  */

/** @defgroup DAC_LL_EM_HELPER_MACRO DAC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get DAC channel number in decimal format
  *         from literals LL_DAC_CHANNEL_x.
  *         Example:
  *            __LL_DAC_CHANNEL_TO_DECIMAL_NB(LL_DAC_CHANNEL_1)
  *            will return decimal number "1".
  * @note   The input can be a value from functions where a channel
  *         number is returned.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval 1
  */
#define __LL_DAC_CHANNEL_TO_DECIMAL_NB(__CHANNEL__)                            \
  ((__CHANNEL__) & DAC_SWTR_CHX_MASK)

/**
  * @brief  Helper macro to get DAC channel in literal format LL_DAC_CHANNEL_x
  *         from number in decimal format.
  *         Example:
  *           __LL_DAC_DECIMAL_NB_TO_CHANNEL(1)
  *           will return a data equivalent to "LL_DAC_CHANNEL_1".
  * @note  If the input parameter does not correspond to a DAC channel,
  *        this macro returns value '0'.
  * @param  __DECIMAL_NB__ 1...2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  */
#define __LL_DAC_DECIMAL_NB_TO_CHANNEL(__DECIMAL_NB__) \
  (((__DECIMAL_NB__) == 1UL)                           \
   ? (LL_DAC_CHANNEL_1)                                \
   :                                                   \
   (0UL)                                               \
  )

/**
  * @brief  Helper macro to define the DAC conversion data full-scale digital
  *         value corresponding to the selected DAC resolution.
  * @note   DAC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref-
  *         (refer to reference manual).
  * @param  __DAC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_DAC_RESOLUTION_12B
  *         @arg @ref LL_DAC_RESOLUTION_8B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_DAC_DIGITAL_SCALE(__DAC_RESOLUTION__)                             \
  ((0x0000003FUL) >> ((__DAC_RESOLUTION__) << 1UL))

/**
  * @brief  Helper macro to calculate the DAC conversion data (unit: digital
  *         value) corresponding to a voltage (unit: mVolt).
  * @note   This helper macro is intended to provide input data in voltage
  *         rather than digital value,
  *         to be used with LL DAC functions such as
  *         @ref LL_DAC_ConvertData12RightAligned().
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __DAC_VOLTAGE__ Voltage to be generated by DAC channel
  *                         (unit: mVolt).
  * @param  __DAC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_DAC_RESOLUTION_12B
  *         @arg @ref LL_DAC_RESOLUTION_8B
  * @retval DAC conversion data (unit: digital value)
  */
#define __LL_DAC_CALC_VOLTAGE_TO_DATA(__VREFANALOG_VOLTAGE__, __DAC_VOLTAGE__, __DAC_RESOLUTION__)     \
  ((__DAC_VOLTAGE__) * __LL_DAC_DIGITAL_SCALE(__DAC_RESOLUTION__)                                      \
   / (__VREFANALOG_VOLTAGE__)                                                                          \
  )

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Functions DAC Exported Functions
  * @{
  */

/**
  * @brief  Set the conversion trigger source for the selected DAC channel.
  * @note   For conversion trigger source to be effective, DAC trigger
  *         must be enabled using function @ref LL_DAC_EnableTrigger().
  * @note   To set conversion trigger source, DAC channel must be disabled.
  *         Otherwise, the setting is discarded.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CR       TSEL           LL_DAC_SetTriggerSource
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_DAC_TRIG_SOFTWARE
  *         @arg @ref LL_DAC_TRIG_EXT_TIM16_TRGO
  *         @arg @ref LL_DAC_TRIG_EXT_EXTI_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetTriggerSource(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t TriggerSource)
{
  MODIFY_REG(DACx->CR,
             DAC_CR_TSEL << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             TriggerSource << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the conversion trigger source for the selected DAC channel.
  * @note   For conversion trigger source to be effective, DAC trigger
  *         must be enabled using function @ref LL_DAC_EnableTrigger().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CR       TSEL           LL_DAC_GetTriggerSource
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_TRIG_SOFTWARE
  *         @arg @ref LL_DAC_TRIG_EXT_TIM16_TRGO
  *         @arg @ref LL_DAC_TRIG_EXT_EXTI_LINE8
  */
__STATIC_INLINE uint32_t LL_DAC_GetTriggerSource(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, DAC_CR_TSEL << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set the waveform automatic generation mode
  *         for the selected DAC channel.
  * @rmtoll CR       WAVE           LL_DAC_SetWaveAutoGeneration
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  WaveAutoGeneration This parameter can be one of the following values:
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_NONE
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_NOISE
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_TRIANGLE
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetWaveAutoGeneration(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t WaveAutoGeneration)
{
  MODIFY_REG(DACx->CR,
             DAC_CR_WAVE << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             WaveAutoGeneration << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the waveform automatic generation mode
  *         for the selected DAC channel.
  * @rmtoll CR       WAVE           LL_DAC_GetWaveAutoGeneration
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_NONE
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_NOISE
  *         @arg @ref LL_DAC_WAVE_AUTO_GENERATION_TRIANGLE
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveAutoGeneration(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, DAC_CR_WAVE << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set the noise waveform generation for the selected DAC channel:
  *         Noise mode and parameters LFSR (linear feedback shift register).
  * @note   For wave generation to be effective, DAC channel
  *         wave generation mode must be enabled using
  *         function @ref LL_DAC_SetWaveAutoGeneration().
  * @note   This setting can be set when the selected DAC channel is disabled
  *         (otherwise, the setting operation is ignored).
  * @rmtoll CR       MAMP           LL_DAC_SetWaveNoiseLFSR
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  NoiseLFSRMask This parameter can be one of the following values:
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BIT0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS1_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS2_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS3_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS4_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS5_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS6_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS7_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS8_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS9_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS10_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS11_0
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetWaveNoiseLFSR(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t NoiseLFSRMask)
{
  MODIFY_REG(DACx->CR,
             DAC_CR_MAMP << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             NoiseLFSRMask << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the noise waveform generation for the selected DAC channel:
  *         Noise mode and parameters LFSR (linear feedback shift register).
  * @rmtoll CR       MAMP           LL_DAC_GetWaveNoiseLFSR
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BIT0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS1_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS2_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS3_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS4_0
  *         @arg @ref LL_DAC_NOISE_LFSR_UNMASK_BITS5_0
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveNoiseLFSR(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, DAC_CR_MAMP << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set the triangle waveform generation for the selected DAC channel:
  *         triangle mode and amplitude.
  * @note   For wave generation to be effective, DAC channel
  *         wave generation mode must be enabled using
  *         function @ref LL_DAC_SetWaveAutoGeneration().
  * @note   This setting can be set when the selected DAC channel is disabled
  *         (otherwise, the setting operation is ignored).
  * @rmtoll CR       MAMP           LL_DAC_SetWaveTriangleAmplitude
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  TriangleAmplitude This parameter can be one of the following values:
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_1
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_3
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_7
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_15
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_31
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_63
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_127
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_255
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_511
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_1023
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_2047
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_4095
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetWaveTriangleAmplitude(DAC_TypeDef *DACx, uint32_t DAC_Channel,
                                                     uint32_t TriangleAmplitude)
{
  MODIFY_REG(DACx->CR,
             DAC_CR_MAMP << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             TriangleAmplitude << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the triangle waveform generation for the selected DAC channel:
  *         triangle mode and amplitude.
  * @rmtoll CR       MAMP           LL_DAC_GetWaveTriangleAmplitude
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_1
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_3
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_7
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_15
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_31
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_63
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_127
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_255
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_511
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_1023
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_2047
  *         @arg @ref LL_DAC_TRIANGLE_AMPLITUDE_4095
  */
__STATIC_INLINE uint32_t LL_DAC_GetWaveTriangleAmplitude(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, DAC_CR_MAMP << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set the output buffer for the selected DAC channel.
  * @rmtoll CR       BON            LL_DAC_SetOutputBuffer
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  OutputBuffer This parameter can be one of the following values:
  *         @arg @ref LL_DAC_OUTPUT_BUFFER_ENABLE
  *         @arg @ref LL_DAC_OUTPUT_BUFFER_DISABLE
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetOutputBuffer(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t OutputBuffer)
{
  MODIFY_REG(DACx->CR,
             DAC_CR_BON << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             OutputBuffer << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the output buffer state for the selected DAC channel.
  * @rmtoll CR       BON            LL_DAC_GetOutputBuffer
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_OUTPUT_BUFFER_ENABLE
  *         @arg @ref LL_DAC_OUTPUT_BUFFER_DISABLE
  */
__STATIC_INLINE uint32_t LL_DAC_GetOutputBuffer(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, DAC_CR_BON << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set the output connection for the selected DAC channel.
  * @note   On this STM32 series, output connection depends on output mode (normal or
  *         sample and hold) and output buffer state.
  *         - if output connection is set to internal path and output buffer
  *           is enabled (whatever output mode):
  *           output connection is also connected to GPIO pin
  *           (both connections to GPIO pin and internal path).
  *         - if output connection is set to GPIO pin, output buffer
  *           is disabled, output mode set to sample and hold:
  *           output connection is also connected to internal path
  *           (both connections to GPIO pin and internal path).
  * @rmtoll CR       CMPEN          LL_DAC_SetOutputConnection
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  OutputConnection This parameter can be one of the following values:
  *         @arg @ref LL_DAC_OUTPUT_CONNECT_GPIO
  *         @arg @ref LL_DAC_OUTPUT_CONNECT_INTERNAL
  * @retval None
  */
__STATIC_INLINE void LL_DAC_SetOutputConnection(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t OutputConnection)
{
  MODIFY_REG(DACx->CR,
             (uint32_t)DAC_CR_CMPEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK),
             OutputConnection << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get the output connection for the selected DAC channel.
  * @note   On this STM32 series, output connection depends on output mode (normal or
  *         sample and hold) and output buffer state.
  *         - if output connection is set to internal path and output buffer
  *           is enabled (whatever output mode):
  *           output connection is also connected to GPIO pin
  *           (both connections to GPIO pin and internal path).
  *         - if output connection is set to GPIO pin, output buffer
  *           is disabled, output mode set to sample and hold:
  *           output connection is also connected to internal path
  *           (both connections to GPIO pin and internal path).
  * @rmtoll CR       CMPEN          LL_DAC_GetOutputConnection
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DAC_OUTPUT_CONNECT_GPIO
  *         @arg @ref LL_DAC_OUTPUT_CONNECT_INTERNAL
  */
__STATIC_INLINE uint32_t LL_DAC_GetOutputConnection(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return (uint32_t)(READ_BIT(DACx->CR, (uint32_t)DAC_CR_CMPEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
                    >> (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                   );
}

/**
  * @}
  */

/** @defgroup DAC_LL_EF_DMA_Management DMA Management
  * @{
  */

/**
  * @brief  Enable DAC DMA transfer request of the selected channel.
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_DAC_DMA_GetRegAddr().
  * @rmtoll CR       DMAEN          LL_DAC_EnableDMAReq
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_EnableDMAReq(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  SET_BIT(DACx->CR,
          DAC_CR_DMAEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Disable DAC DMA transfer request of the selected channel.
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_DAC_DMA_GetRegAddr().
  * @rmtoll CR       DMAEN          LL_DAC_DisableDMAReq
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_DisableDMAReq(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  CLEAR_BIT(DACx->CR,
            DAC_CR_DMAEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get DAC DMA transfer request state of the selected channel.
  *         (0: DAC DMA transfer request is disabled, 1: DAC DMA transfer request is enabled)
  * @rmtoll CR       DMAEN          LL_DAC_IsDMAReqEnabled
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsDMAReqEnabled(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return ((READ_BIT(DACx->CR,
                    DAC_CR_DMAEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
           == (DAC_CR_DMAEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))) ? 1UL : 0UL);
}

/**
  * @brief  Function to help to configure DMA transfer to DAC: retrieve the
  *         DAC register address from DAC instance and a list of DAC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @note   These DAC registers are data holding registers:
  *         when DAC conversion is requested, DAC generates a DMA transfer
  *         request to have data available in DAC data holding registers.
  * @rmtoll DHR      DACDHR         LL_DAC_DMA_GetRegAddr
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval DAC register address
  */
__STATIC_INLINE uint32_t LL_DAC_DMA_GetRegAddr(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  /* DAC channel selected.                                                    */
  return ((uint32_t)(&((DACx)->DHR)));
}
/**
  * @}
  */

/** @defgroup DAC_LL_EF_Operation Operation on DAC channels
  * @{
  */

/**
  * @brief  Enable DAC selected channel.
  * @rmtoll CR       EN             LL_DAC_Enable
  * @note   After enable from off state, DAC channel requires a delay
  *         for output voltage to reach accuracy +/- 1 LSB.
  *         Refer to device datasheet, parameter "tWAKEUP".
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_Enable(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  SET_BIT(DACx->CR,
          DAC_CR_EN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Disable DAC selected channel.
  * @rmtoll CR       EN            LL_DAC_Disable
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_Disable(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  CLEAR_BIT(DACx->CR,
            DAC_CR_EN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get DAC enable state of the selected channel.
  *         (0: DAC channel is disabled, 1: DAC channel is enabled)
  * @rmtoll CR       EN             LL_DAC_IsEnabled
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsEnabled(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return ((READ_BIT(DACx->CR,
                    DAC_CR_EN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
           == (DAC_CR_EN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))) ? 1UL : 0UL);
}

/**
  * @brief  Enable DAC trigger of the selected channel.
  * @note   - If DAC trigger is disabled, DAC conversion is performed
  *           automatically once the data holding register is updated,
  *           using functions "LL_DAC_ConvertData{8; 12}{Right; Left} Aligned()":
  *           @ref LL_DAC_ConvertData12RightAligned(), ...
  *         - If DAC trigger is enabled, DAC conversion is performed
  *           only when a hardware of software trigger event is occurring.
  *           Select trigger source using
  *           function @ref LL_DAC_SetTriggerSource().
  * @rmtoll CR       TEN            LL_DAC_EnableTrigger
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_EnableTrigger(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  SET_BIT(DACx->CR,
          DAC_CR_TEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Disable DAC trigger of the selected channel.
  * @rmtoll CR       TEN            LL_DAC_DisableTrigger
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_DisableTrigger(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  CLEAR_BIT(DACx->CR,
            DAC_CR_TEN  << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK));
}

/**
  * @brief  Get DAC trigger state of the selected channel.
  *         (0: DAC trigger is disabled, 1: DAC trigger is enabled)
  * @rmtoll CR       TEN            LL_DAC_IsTriggerEnabled
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsTriggerEnabled(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  return ((READ_BIT(DACx->CR,
                    DAC_CR_TEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))
           == (DAC_CR_TEN << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK))) ? 1UL : 0UL);
}

/**
  * @brief  Trig DAC conversion by software for the selected DAC channel.
  * @note   Preliminarily, DAC trigger must be set to software trigger
  *         using function
  *           @ref LL_DAC_Init()
  *           @ref LL_DAC_SetTriggerSource()
  *         with parameter "LL_DAC_TRIGGER_SOFTWARE".
  *         and DAC trigger must be enabled using
  *         function @ref LL_DAC_EnableTrigger().
  * @note   For devices featuring DAC with 2 channels: this function
  *         can perform a SW start of both DAC channels simultaneously.
  *         Two channels can be selected as parameter.
  *         Example: (LL_DAC_CHANNEL_1 | LL_DAC_CHANNEL_2)
  * @rmtoll SWTRIGR  SWTRIG        LL_DAC_TrigSWConversion
  * @param  DACx DAC instance
  * @param  DAC_Channel  This parameter can a combination of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval None
  */
__STATIC_INLINE void LL_DAC_TrigSWConversion(DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  SET_BIT(DACx->SWTRIGR,
          (DAC_Channel & DAC_SWTR_CHX_MASK));
}

/**
  * @brief  Set the data to be loaded in the data holding register
  *         in format 6 bits right alignment (LSB aligned on bit 0),
  *         for the selected DAC channel.
  * @rmtoll DHR  DACDHR          LL_DAC_ConvertData6RightAligned
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @param  Data Value between Min_Data=0x00 and Max_Data=0x3F
  * @retval None
  */
__STATIC_INLINE void LL_DAC_ConvertData6RightAligned(DAC_TypeDef *DACx, uint32_t DAC_Channel, uint32_t Data)
{
  (void)(DAC_Channel);

  MODIFY_REG(DACx->DHR, DAC_DHR_DACDHR, Data);
}

/**
  * @brief  Retrieve output data currently generated for the selected DAC channel.
  * @note   Whatever alignment and resolution settings
  *         (using functions "LL_DAC_ConvertData{8; 12}{Right; Left} Aligned()":
  *         @ref LL_DAC_ConvertData12RightAligned(), ...),
  *         output data format is 12 bits right aligned (LSB aligned on bit 0).
  * @rmtoll DOR      DACDOR         LL_DAC_RetrieveOutputData
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_DAC_RetrieveOutputData(const DAC_TypeDef *DACx, uint32_t DAC_Channel)
{
  (void)(DAC_Channel);

  return (uint16_t) READ_BIT(DACx->DOR, DAC_DOR_DACDOR);
}

/**
  * @}
  */

/** @defgroup DAC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Get DAC underrun flag for DAC channel 1
  * @rmtoll SR       DMAUDR        LL_DAC_IsActiveFlag_DMAUDR
  * @param  DACx DAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsActiveFlag_DMAUDR(const DAC_TypeDef *DACx)
{
  return ((READ_BIT(DACx->SR, LL_DAC_FLAG_DMAUDR) == (LL_DAC_FLAG_DMAUDR)) ? 1UL : 0UL);
}

/**
  * @brief  Clear DAC underrun flag for DAC channel 1
  * @rmtoll SR       DMAUDR        LL_DAC_ClearFlag_DMAUDR
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_ClearFlag_DMAUDR(DAC_TypeDef *DACx)
{
  WRITE_REG(DACx->SR, LL_DAC_FLAG_DMAUDR);
}

/**
  * @}
  */

/** @defgroup DAC_LL_EF_IT_Management IT management
  * @{
  */

/**
  * @brief  Enable DMA underrun interrupt for DAC channel 1
  * @rmtoll CR       DMAUDRIE      LL_DAC_EnableIT_DMAUDR
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_EnableIT_DMAUDR(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->CR, LL_DAC_IT_DMAUDRIE);
}

/**
  * @brief  Disable DMA underrun interrupt for DAC channel 1
  * @rmtoll CR       DMAUDRIE      LL_DAC_DisableIT_DMAUDR
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_DisableIT_DMAUDR(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->CR, LL_DAC_IT_DMAUDRIE);
}

/**
  * @brief  Get DMA underrun interrupt for DAC channel 1
  * @rmtoll CR       DMAUDRIE       LL_DAC_IsEnabledIT_DMAUDR
  * @param  DACx DAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsEnabledIT_DMAUDR(const DAC_TypeDef *DACx)
{
  return ((READ_BIT(DACx->CR, LL_DAC_IT_DMAUDRIE) == (LL_DAC_IT_DMAUDRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Power-up the VCM buffer.
  * @rmtoll CR       VCMON           LL_DAC_EnableVCMBuffer
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_EnableVCMBuffer(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->CR, DAC_CR_VCMON);
}

/**
  * @brief  Power-up the VCM buffer.
  * @rmtoll CR       VCMON           LL_DAC_DisableVCMBuffer
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_DisableVCMBuffer(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->CR, DAC_CR_VCMON);
}

/**
  * @brief  Get the VCM buffer state.
  *         (0: DAC VCM buffer is disabled, 1: DAC VCM buffer is enabled)
  * @param  DACx DAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsVCMBufferEnabled(const DAC_TypeDef *DACx)
{
  return ((READ_BIT(DACx->CR, DAC_CR_VCMON) == (DAC_CR_VCMON)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the VCM buffer channel output.
  * @rmtoll CR       VCMEN           LL_DAC_EnableVCMBufferOutput
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_EnableVCMBufferOutput(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->CR, DAC_CR_VCMEN);
}

/**
  * @brief  Disable the VCM buffer channel output.
  * @rmtoll CR       VCMEN           LL_DAC_DisableVCMBufferOutput
  * @param  DACx DAC instance
  * @retval None
  */
__STATIC_INLINE void LL_DAC_DisableVCMBufferOutput(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->CR, DAC_CR_VCMEN);
}

/**
  * @brief  Get the VCM buffer output state.
  *         (0: DAC VCM buffer output is disabled, 1: DAC VCM buffer output is enabled)
  * @param  DACx DAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DAC_IsVCMBufferOutputEnabled(const DAC_TypeDef *DACx)
{
  return ((READ_BIT(DACx->CR, DAC_CR_VCMEN) == (DAC_CR_VCMEN)) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup DAC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_DAC_DeInit(const DAC_TypeDef *DACx);
ErrorStatus LL_DAC_Init(DAC_TypeDef *DACx, uint32_t DAC_Channel, const LL_DAC_InitTypeDef *DAC_InitStruct);
void        LL_DAC_StructInit(LL_DAC_InitTypeDef *DAC_InitStruct);

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

#endif /* DAC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WL3x_LL_DAC_H */
