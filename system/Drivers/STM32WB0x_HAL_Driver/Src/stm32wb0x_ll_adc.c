/**
  ******************************************************************************
  * @file    stm32wb0x_ll_adc.c
  * @author  GPM Application Team
  * @brief   ADC LL module driver
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_ll_adc.h"
#include "stm32wb0x_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0UL)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (ADC1)

/** @addtogroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup ADC_LL_Private_Constants
  * @{
  */

#define ADC_SWITCH_SE_VIN_ALL                       (ADC_SWITCH_SE_VIN_0 | ADC_SWITCH_SE_VIN_1 | \
                                                     ADC_SWITCH_SE_VIN_2 | ADC_SWITCH_SE_VIN_3 | \
                                                     ADC_SWITCH_SE_VIN_4 | ADC_SWITCH_SE_VIN_5 | \
                                                     ADC_SWITCH_SE_VIN_6 | ADC_SWITCH_SE_VIN_7)

#define ADC_SEQ_1_SEQ_ALL                           (ADC_SEQ_1_SEQ0 | ADC_SEQ_1_SEQ1 | \
                                                     ADC_SEQ_1_SEQ2 | ADC_SEQ_1_SEQ3 | \
                                                     ADC_SEQ_1_SEQ4 | ADC_SEQ_1_SEQ5 | \
                                                     ADC_SEQ_1_SEQ6 | ADC_SEQ_1_SEQ7)

#define ADC_SEQ_2_SEQ_ALL                           (ADC_SEQ_2_SEQ8  | ADC_SEQ_2_SEQ9  | \
                                                     ADC_SEQ_2_SEQ10 | ADC_SEQ_2_SEQ11 | \
                                                     ADC_SEQ_2_SEQ12 | ADC_SEQ_2_SEQ13 | \
                                                     ADC_SEQ_2_SEQ14 | ADC_SEQ_2_SEQ15)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup ADC_LL_Private_Macros
  * @{
  */
/* Check of parameters for configuration of ADC hierarchical scope:           */
/* ADC instance.                                                              */
#define IS_LL_ADC_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1UL)) && ((__LENGTH__) <= (16UL)))

#define IS_LL_ADC_DATAWIDTH(__DATA_WIDTH__) (((__DATA_WIDTH__) == LL_ADC_DS_DATA_WIDTH_12_BIT) || \
                                             ((__DATA_WIDTH__) == LL_ADC_DS_DATA_WIDTH_13_BIT) || \
                                             ((__DATA_WIDTH__) == LL_ADC_DS_DATA_WIDTH_14_BIT) || \
                                             ((__DATA_WIDTH__) == LL_ADC_DS_DATA_WIDTH_15_BIT) || \
                                             ((__DATA_WIDTH__) == LL_ADC_DS_DATA_WIDTH_16_BIT)   )

#define IS_LL_ADC_DATARATIO(__DATA_RATIO__) (((__DATA_RATIO__) == LL_ADC_DS_RATIO_1) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_2) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_4) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_8) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_16) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_32) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_64) || \
                                             ((__DATA_RATIO__) == LL_ADC_DS_RATIO_128)   )

#define IS_LL_ADC_OVERRUN(__OVR__) (((__OVR__) == LL_ADC_NEW_DATA_IS_LOST)  || \
                                    ((__OVR__) == LL_ADC_NEW_DATA_IS_KEPT)    )

#define IS_LL_ADC_SAMPLINGMODE(__SAMPLING_MODE__) (((__SAMPLING_MODE__) == LL_ADC_SAMPLING_AT_START) || \
                                                   ((__SAMPLING_MODE__) == LL_ADC_SAMPLING_AT_END)     )

#if defined(ADC_CONF_SAMPLE_RATE_MSB)
#define IS_LL_ADC_SAMPLERATE(__SAMPLERATE__) (((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_16)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_20)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_24)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_28)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_32)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_36)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_40)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_44)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_48)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_52)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_56)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_60)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_64)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_68)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_72)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_76)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_80)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_84)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_88)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_92)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_96)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_100) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_104) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_108) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_112) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_116) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_120) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_124) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_128) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_132) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_136) || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_140)  )
#else
#define IS_LL_ADC_SAMPLERATE(__SAMPLERATE__) (((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_16)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_20)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_24)  || \
                                              ((__SAMPLERATE__) == LL_ADC_SAMPLE_RATE_28)   )
#endif /* ADC_CONF_SAMPLE_RATE_MSB */

#define IS_LL_ADC_RANK(__RANK__) (((__RANK__) == LL_ADC_RANK_1 ) || \
                                  ((__RANK__) == LL_ADC_RANK_2 ) || \
                                  ((__RANK__) == LL_ADC_RANK_3 ) || \
                                  ((__RANK__) == LL_ADC_RANK_4 ) || \
                                  ((__RANK__) == LL_ADC_RANK_5 ) || \
                                  ((__RANK__) == LL_ADC_RANK_6 ) || \
                                  ((__RANK__) == LL_ADC_RANK_7 ) || \
                                  ((__RANK__) == LL_ADC_RANK_8 ) || \
                                  ((__RANK__) == LL_ADC_RANK_9 ) || \
                                  ((__RANK__) == LL_ADC_RANK_10) || \
                                  ((__RANK__) == LL_ADC_RANK_11) || \
                                  ((__RANK__) == LL_ADC_RANK_12) || \
                                  ((__RANK__) == LL_ADC_RANK_13) || \
                                  ((__RANK__) == LL_ADC_RANK_14) || \
                                  ((__RANK__) == LL_ADC_RANK_15) || \
                                  ((__RANK__) == LL_ADC_RANK_16)   )

#define IS_LL_ADC_VOLTAGE_RANGE(__VOLTAGE_RANGE__) (((__VOLTAGE_RANGE__) == LL_ADC_VIN_RANGE_1V2) || \
                                                    ((__VOLTAGE_RANGE__) == LL_ADC_VIN_RANGE_2V4) || \
                                                    ((__VOLTAGE_RANGE__) == LL_ADC_VIN_RANGE_3V6)   )

#define IS_LL_ADC_CHANNEL(__CHANNEL__) (((__CHANNEL__) == LL_ADC_CHANNEL_VINM0)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINM1)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINM2)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINM3)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP0)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP1)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP2)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP3)       || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP0_VINM0) || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP1_VINM1) || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP2_VINM2) || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VINP3_VINM3) || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)        || \
                                        ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR)    )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_LL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_LL_EF_Init
  * @{
  */

/**
  * @brief  Initialize some features of ADC instance.
  * @note   These parameters have an impact on ADC scope: ADC instance.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC.
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all STM32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @param  ADCx ADC instance
  * @param  pADC_InitStruct Pointer to a @ref LL_ADC_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus LL_ADC_Init(ADC_TypeDef *ADCx, const LL_ADC_InitTypeDef *pADC_InitStruct)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(ADCx));

  assert_param(IS_LL_ADC_NB_CONV(pADC_InitStruct->SequenceLength));
  assert_param(IS_LL_ADC_SAMPLINGMODE(pADC_InitStruct->SamplingMode));
  assert_param(IS_LL_ADC_SAMPLERATE(pADC_InitStruct->SampleRate));
  assert_param(IS_LL_ADC_OVERRUN(pADC_InitStruct->Overrun));

  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if (LL_ADC_IsEnabled(ADCx) == 0UL)
  {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC instance                                                        */
    /*    - Set ADC continuous mode                                           */
    /*    - Set ADC sequence length                                           */
    /*    - Set ADC sampling mode                                             */
    /*    - Set ADC sample rate                                               */
    /*    - Set ADC overrun                                                   */
    MODIFY_REG(ADCx->CONF, (ADC_CONF_SAMPLE_RATE
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
                            | ADC_CONF_SAMPLE_RATE_MSB
#endif /* ADC_CONF_SAMPLE_RATE_MSB */
                            | ADC_CONF_ADC_CONT_1V2
                            | ADC_CONF_OVR_DS_CFG
                            | ADC_CONF_SEQ_LEN
                            | ADC_CONF_CONT),
               (pADC_InitStruct->SampleRate
                | pADC_InitStruct->SamplingMode
                | pADC_InitStruct->Overrun
                | ((pADC_InitStruct->SequenceLength - 1UL) << ADC_CONF_SEQ_LEN_Pos)
                | pADC_InitStruct->ContinuousConvMode));
  }
  else
  {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  De-initialize registers of the selected ADC instance
  *         to their default reset values.
  * @note   If this functions returns error status, it means that ADC instance
  *         is in an unknown state.
  *         In this case, perform a hard reset using high level
  *         clock source RCC ADC reset.
  * @param  ADCx ADC instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are de-initialized
  *          - ERROR: ADC registers are not de-initialized
  */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *ADCx)
{
  ErrorStatus status = SUCCESS;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));

  /* ========== Reset ADC registers ========== */
  /* Reset register IER */
  LL_ADC_DisableIT(ADCx, (LL_ADC_IRQ_EN_OVRDS
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                          | LL_ADC_IRQ_EN_OVRFL
                          | LL_ADC_IRQ_EN_EODF
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                          | LL_ADC_IRQ_EN_AWD1
                          | LL_ADC_IRQ_EN_EOS
                          | LL_ADC_IRQ_EN_EODS));

  /* Reset register ISR */
  LL_ADC_ClearActiveFlags(ADCx, (LL_ADC_IRQ_FLAG_OVRDS
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                                 | LL_ADC_IRQ_FLAG_OVRFL
                                 | LL_ADC_IRQ_FLAG_OVRDF
                                 | LL_ADC_IRQ_FLAG_EODF
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                                 | LL_ADC_IRQ_FLAG_AWD1
                                 | LL_ADC_IRQ_FLAG_EOC
                                 | LL_ADC_IRQ_FLAG_EOS
                                 | LL_ADC_IRQ_FLAG_EODS));

  /* Reset all the registers */
  CLEAR_BIT(ADCx->CONF, (ADC_CONF_BIT_INVERT_DIFF
#if defined(ADC_CONF_SAMPLE_RATE_MSB)
                         | ADC_CONF_SAMPLE_RATE_MSB
#endif /* ADC_CONF_SAMPLE_RATE_MSB */
                         | ADC_CONF_OVR_DS_CFG | ADC_CONF_DMA_DS_ENA
                         | ADC_CONF_SAMPLE_RATE
                         | ADC_CONF_SMPS_SYNCHRO_ENA
                         | ADC_CONF_SEQ_LEN
                         | ADC_CONF_CONT
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                         | ADC_CONF_VBIAS_PRECH_FORCE
                         | ADC_CONF_OVR_DF_CFG | ADC_CONF_DMA_DF_ENA
                         | ADC_CONF_OP_MODE
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                        ));

  SET_BIT(ADCx->CONF, (ADC_CONF_ADC_CONT_1V2 | ADC_CONF_BIT_INVERT_SN | ADC_CONF_SEQUENCE));

  CLEAR_BIT(ADCx->CTRL, (ADC_CTRL_ADC_LDO_ENA
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                         | ADC_CTRL_DIG_AUD_MODE
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                         | ADC_CTRL_STOP_OP_MODE | ADC_CTRL_START_CONV
                         | ADC_CTRL_ADC_ON_OFF));

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  CLEAR_BIT(ADCx->OCM_CTRL, (ADC_OCM_CTRL_OCM_ENA | ADC_OCM_CTRL_OCM_SRC));

  CLEAR_BIT(ADCx->PGA_CONF, (ADC_PGA_CONF_PGA_BIAS | ADC_PGA_CONF_PGA_GAIN));
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

  CLEAR_BIT(ADCx->SWITCH, (ADC_SWITCH_SE_VIN_7 | ADC_SWITCH_SE_VIN_6
                           | ADC_SWITCH_SE_VIN_5 | ADC_SWITCH_SE_VIN_4
                           | ADC_SWITCH_SE_VIN_3 | ADC_SWITCH_SE_VIN_2
                           | ADC_SWITCH_SE_VIN_1 | ADC_SWITCH_SE_VIN_0));

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  CLEAR_BIT(ADCx->DF_CONF, (ADC_DF_CONF_DF_HALF_D_EN
                            | ADC_DF_CONF_DF_HPF_EN | ADC_DF_CONF_DF_MICROL_RN
                            | ADC_DF_CONF_PDM_RATE
                            | ADC_DF_CONF_DF_O_S2U
                            | ADC_DF_CONF_DF_I_U2S  | ADC_DF_CONF_DF_ITP1P2
                            | ADC_DF_CONF_DF_CIC_DHF | ADC_DF_CONF_DF_CIC_DEC_FACTOR));

  SET_BIT(ADCx->DF_CONF, (ADC_DF_CONF_PDM_RATE_1 | ADC_DF_CONF_PDM_RATE_2));
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

  CLEAR_BIT(ADCx->DS_CONF, (ADC_DS_CONF_DS_WIDTH | ADC_DS_CONF_DS_RATIO));

  CLEAR_BIT(ADCx->SEQ_1, (ADC_SEQ_1_SEQ7 | ADC_SEQ_1_SEQ6
                          | ADC_SEQ_1_SEQ5 | ADC_SEQ_1_SEQ4
                          | ADC_SEQ_1_SEQ3 | ADC_SEQ_1_SEQ2
                          | ADC_SEQ_1_SEQ1 | ADC_SEQ_1_SEQ0));

  CLEAR_BIT(ADCx->SEQ_2, (ADC_SEQ_2_SEQ15 | ADC_SEQ_2_SEQ14
                          | ADC_SEQ_2_SEQ13 | ADC_SEQ_2_SEQ12
                          | ADC_SEQ_2_SEQ11 | ADC_SEQ_2_SEQ10
                          | ADC_SEQ_2_SEQ9  | ADC_SEQ_2_SEQ8));

  MODIFY_REG(ADCx->COMP_1, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(ADCx->COMP_2, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(ADCx->COMP_3, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(ADCx->COMP_4, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);

  CLEAR_BIT(ADCx->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN8 | ADC_COMP_SEL_OFFSET_GAIN7
                             | ADC_COMP_SEL_OFFSET_GAIN6 | ADC_COMP_SEL_OFFSET_GAIN5
                             | ADC_COMP_SEL_OFFSET_GAIN4 | ADC_COMP_SEL_OFFSET_GAIN3
                             | ADC_COMP_SEL_OFFSET_GAIN2 | ADC_COMP_SEL_OFFSET_GAIN1
                             | ADC_COMP_SEL_OFFSET_GAIN0));

  MODIFY_REG(ADCx->WD_TH, (ADC_WD_TH_WD_HT | ADC_WD_TH_WD_LT), ADC_WD_TH_WD_HT);

  CLEAR_BIT(ADCx->WD_CONF, (ADC_WD_CONF_AWD_CHX));

  CLEAR_BIT(ADCx->IRQ_STATUS, (ADC_IRQ_STATUS_OVR_DS_IRQ
                               | ADC_IRQ_STATUS_AWD_IRQ
                               | ADC_IRQ_STATUS_EOS_IRQ
                               | ADC_IRQ_STATUS_EODS_IRQ
                               | ADC_IRQ_STATUS_EOC_IRQ
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                               | ADC_IRQ_STATUS_DF_OVRFL_IRQ
                               | ADC_IRQ_STATUS_OVR_DF_IRQ
                               | ADC_IRQ_STATUS_EODF_IRQ
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                              ));

  CLEAR_BIT(ADCx->IRQ_ENABLE, (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA
                               | ADC_IRQ_ENABLE_AWD_IRQ_ENA
                               | ADC_IRQ_ENABLE_EOS_IRQ_ENA
                               | ADC_IRQ_ENABLE_EODS_IRQ_ENA
                               | ADC_IRQ_ENABLE_EOC_IRQ_ENA
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                               | ADC_IRQ_ENABLE_DF_OVRFL_IRQ_ENA
                               | ADC_IRQ_ENABLE_OVR_DF_IRQ_ENA
                               | ADC_IRQ_ENABLE_EODF_IRQ_ENA
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                              ));

  CLEAR_BIT(ADCx->TIMER_CONF, (ADC_TIMER_CONF_ADC_LDO_DELAY
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                               | ADC_TIMER_CONF_PRECH_DELAY_SEL
                               | ADC_TIMER_CONF_VBIAS_PRECH_DELAY
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                              ));
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  LL_ADC_SetVbiasPrechargeDelay(ADCx, 0x96UL);
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
  LL_ADC_SetADCLDODelay(ADCx, 0x28UL);

  return status;
}


/**
  * @brief  Configure the input voltage range for all the inputs.
  * @param  ADCx ADC instance
  * @param  pVoltRange_InitStruct pointer to a @ref LL_ADC_VoltRangeInitTypeDef structure
  *         that contains the voltage range for all the inputs.
  * @retval None
  */
ErrorStatus LL_ADC_VoltageRangeInit(ADC_TypeDef *ADCx, const LL_ADC_VoltRangeInitTypeDef *pVoltRange_InitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinm0_Vinp0Vinm0));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinm1_Vinp1Vinm1));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinm2_Vinp2Vinm2));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinm3_Vinp3Vinm3));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinp0));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinp1));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinp2));
  assert_param(IS_LL_ADC_VOLTAGE_RANGE(pVoltRange_InitStruct->InputVinp3));

  tmpval |= (pVoltRange_InitStruct->InputVinm0_Vinp0Vinm0);
  tmpval |= (pVoltRange_InitStruct->InputVinm1_Vinp1Vinm1) << ADC_SWITCH_SE_VIN_1_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinm2_Vinp2Vinm2) << ADC_SWITCH_SE_VIN_2_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinm3_Vinp3Vinm3) << ADC_SWITCH_SE_VIN_3_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinp0) << ADC_SWITCH_SE_VIN_4_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinp1) << ADC_SWITCH_SE_VIN_5_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinp2) << ADC_SWITCH_SE_VIN_6_Pos;
  tmpval |= (pVoltRange_InitStruct->InputVinp3) << ADC_SWITCH_SE_VIN_7_Pos;

  MODIFY_REG(ADCx->SWITCH, ADC_SWITCH_SE_VIN_ALL, tmpval);

  return (status);
}

/**
  * @brief  Configure the channels for the conversion sequence.
  * @param  ADCx ADC instance
  * @param  pSequence_InitStruct pointer to a @ref LL_ADC_SequenceInitTypeDef structure
  *         that contains the channel codes for the conversion sequence.
  * @retval ErrorStatus
  */
ErrorStatus LL_ADC_SequenceInit(ADC_TypeDef *ADCx, const LL_ADC_SequenceInitTypeDef *pSequence_InitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t tmpval = 0;

  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq0));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq1));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq2));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq3));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq4));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq5));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq6));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq7));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq8));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq9));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq10));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq11));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq12));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq13));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq14));
  assert_param(IS_LL_ADC_CHANNEL(pSequence_InitStruct->ChannelForSeq15));

  tmpval |= (pSequence_InitStruct->ChannelForSeq0) << ADC_SEQ_1_SEQ0_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq1) << ADC_SEQ_1_SEQ1_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq2) << ADC_SEQ_1_SEQ2_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq3) << ADC_SEQ_1_SEQ3_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq4) << ADC_SEQ_1_SEQ4_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq5) << ADC_SEQ_1_SEQ5_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq6) << ADC_SEQ_1_SEQ6_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq7) << ADC_SEQ_1_SEQ7_Pos;

  MODIFY_REG(ADCx->SEQ_1, ADC_SEQ_1_SEQ_ALL, tmpval);

  tmpval = 0;

  tmpval |= (pSequence_InitStruct->ChannelForSeq8)  << ADC_SEQ_2_SEQ8_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq9)  << ADC_SEQ_2_SEQ9_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq10) << ADC_SEQ_2_SEQ10_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq11) << ADC_SEQ_2_SEQ11_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq12) << ADC_SEQ_2_SEQ12_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq13) << ADC_SEQ_2_SEQ13_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq14) << ADC_SEQ_2_SEQ14_Pos;
  tmpval |= (pSequence_InitStruct->ChannelForSeq15) << ADC_SEQ_2_SEQ15_Pos;

  MODIFY_REG(ADCx->SEQ_2, ADC_SEQ_2_SEQ_ALL, tmpval);

  return (status);
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

#endif /* ADC1 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
