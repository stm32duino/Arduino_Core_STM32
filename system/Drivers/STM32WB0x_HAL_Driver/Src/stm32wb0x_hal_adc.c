/**
  ******************************************************************************
  * @file    stm32wb0x_hal_adc.c
  * @author  GPM Application Team
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Analog to Digital Converter (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *          Other functions (extended functions) are available in file
  *          "stm32wb0x_hal_adc_ex.c".
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
                     ##### ADC peripheral features #####
  ==============================================================================
  [..]
  (+) Conversion frequency is up to 1 Msps.

  (+) Three input voltage ranges are supported (0V : 1.2V, 0V : 2.4V, 0V : 3.6V).

  (+) Up to eight analog single ended channels or four analog differential inputs or a mix of
both.

  (+) Temperature sensor conversion.

  (+) Battery level conversion up to 3.6V.

  (+) Continuous or single acquisition.

  (+) ADC Down Sampler for multi-purpose applications to improve analog performance
while off-loading the CPU (ratio adjustable from 1 to 128).

  (+) A watchdog feature to inform when data is outside thresholds.

  (+) DMA capability.

  (+) Interrupt sources with flags.

                     ##### How to use this driver #####
  ==============================================================================
    [..]

     *** Configuration of top level parameters related to ADC ***
     ============================================================
     [..]

    (#) Enable the ADC interface
        (++) As prerequisite, ADC clock must be configured at RCC top level.

        (++) Example:
               Into HAL_ADC_MspInit() (recommended code location) or with
               other device clock parameters configuration:
           (+++) __HAL_RCC_ADC_CLK_ENABLE();                  (mandatory)

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_ENABLE()
         (++) Configure these ADC pins in analog mode
              using function HAL_GPIO_Init()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Configure the NVIC for ADC
              using function HAL_NVIC_EnableIRQ(ADCx_IRQn)
         (++) Insert the ADC interruption handler function HAL_ADC_IRQHandler()
              into the function of corresponding ADC interruption vector
              ADC_IRQHandler().

    (#) Optionally, in case of usage of DMA:
         (++) Configure the DMA (DMA channel, mode normal or circular, ...)
              using function HAL_DMA_Init().
         (++) Configure the NVIC for DMA
              using function HAL_NVIC_EnableIRQ(DMAx_Channelx_IRQn)
         (++) Insert the ADC interruption handler function HAL_ADC_IRQHandler()
              into the function of corresponding DMA interruption vector
              DMAx_Channelx_IRQHandler().

     *** Configuration of ADC, channels parameters ***
     ================================================================
     [..]

    (#) Configure the ADC parameters using function HAL_ADC_Init().

    (#) Configure the channels using the function HAL_ADC_ConfigChannel().

    (#) Optionally, configure the analog watchdog parameters (channels
        monitored, thresholds, ...)
        using function HAL_ADC_AWDConfig().

     *** Execution of ADC conversions ***
     ====================================
     [..]

    (#) ADC driver can be used among three modes: polling, interruption,
        transfer by DMA.

        (++) ADC conversion by polling:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start()
          (+++) Wait for ADC conversion completion
                using function HAL_ADC_PollForConversion()
          (+++) Retrieve conversion results
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral
                using function HAL_ADC_Stop()

        (++) ADC conversion by interruption:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start_IT()
          (+++) Wait for ADC conversion completion by call of function
                HAL_ADC_ConvCpltCallback()
                (this function must be implemented in user program)
          (+++) Retrieve conversion results
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral
                using function HAL_ADC_Stop_IT()

        (++) ADC conversion with transfer by DMA:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start_DMA()
          (+++) Wait for ADC conversion completion by call of function
                HAL_ADC_ConvCpltCallback() or HAL_ADC_ConvHalfCpltCallback()
                (these functions must be implemented in user program)
          (+++) Conversion results are automatically transferred by DMA into
                destination variable address.
          (+++) Stop conversion and disable the ADC peripheral
                using function HAL_ADC_Stop_DMA()

     [..]

    (@) Callback functions must be implemented in user program:
      (+@) HAL_ADC_ErrorCallback()
      (+@) LevelOutOfWindowCallback() (callback of analog watchdog)
      (+@) HAL_ADC_ConvCpltCallback()
      (+@) HAL_ADC_ConvHalfCpltCallback

     *** Deinitialization of ADC ***
     ============================================================
     [..]

    (#) Disable the ADC interface
      (++) ADC clock can be hard reset and disabled at RCC top level.
        (++) Hard reset of ADC peripherals
             using macro __HAL_RCC_ADC_FORCE_RESET(), __HAL_RCC_ADC_RELEASE_RESET().
        (++) ADC clock disable
             using the equivalent macro/functions as configuration step.
             (+++) Example:
                   Into HAL_ADC_MspDeInit() (recommended code location).

    (#) ADC pins configuration
         (++) Disable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_DISABLE()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Disable the NVIC for ADC
              using function HAL_NVIC_DisableIRQ(ADCx_IRQn)

    (#) Optionally, in case of usage of DMA:
         (++) Deinitialize the DMA
              using function HAL_DMA_DeInit().
         (++) Disable the NVIC for DMA
              using function HAL_NVIC_DisableIRQ(DMAx_Channelx_IRQn)

    [..]

    *** Callback registration ***
    =============================================
    [..]

     The compilation flag USE_HAL_ADC_REGISTER_CALLBACKS, when set to 1,
     allows the user to configure dynamically the driver callbacks.
     Use Functions @ref HAL_ADC_RegisterCallback() to register an interrupt callback.
    [..]

     Function @ref HAL_ADC_RegisterCallback() allows to register following callbacks:
       (+) ConvCpltCallback               : ADC conversion complete callback
       (+) ConvHalfCpltCallback           : ADC conversion DMA half-transfer callback
       (+) LevelOutOfWindowCallback       : ADC analog watchdog callback
       (+) ErrorCallback                  : ADC error callback
       (+) MspInitCallback                : ADC Msp Init callback
       (+) MspDeInitCallback              : ADC Msp DeInit callback
     This function takes as parameters the HAL peripheral handle, the Callback ID
     and a pointer to the user callback function.
    [..]

     Use function @ref HAL_ADC_UnRegisterCallback to reset a callback to the default
     weak function.
    [..]

     @ref HAL_ADC_UnRegisterCallback takes as parameters the HAL peripheral handle,
     and the Callback ID.
     This function allows to reset following callbacks:
       (+) ConvCpltCallback               : ADC conversion complete callback
       (+) ConvHalfCpltCallback           : ADC conversion DMA half-transfer callback
       (+) LevelOutOfWindowCallback       : ADC analog watchdog callback
       (+) ErrorCallback                  : ADC error callback
       (+) MspInitCallback                : ADC Msp Init callback
       (+) MspDeInitCallback              : ADC Msp DeInit callback
     [..]

     By default, after the @ref HAL_ADC_Init() and when the state is @ref HAL_ADC_STATE_RESET
     all callbacks are set to the corresponding weak functions:
     examples @ref HAL_ADC_ConvCpltCallback(), @ref HAL_ADC_ErrorCallback().
     Exception done for MspInit and MspDeInit functions that are
     reset to the legacy weak functions in the @ref HAL_ADC_Init()/ @ref HAL_ADC_DeInit() only when
     these callbacks are null (not registered beforehand).
    [..]

     If MspInit or MspDeInit are not null, the @ref HAL_ADC_Init()/ @ref HAL_ADC_DeInit()
     keep and use the user MspInit/MspDeInit callbacks (registered beforehand) whatever the state.
     [..]

     Callbacks can be registered/unregistered in @ref HAL_ADC_STATE_READY state only.
     Exception done MspInit/MspDeInit functions that can be registered/unregistered
     in @ref HAL_ADC_STATE_READY or @ref HAL_ADC_STATE_RESET state,
     thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
    [..]

     Then, the user first registers the MspInit/MspDeInit user callbacks
     using @ref HAL_ADC_RegisterCallback() before calling @ref HAL_ADC_DeInit()
     or @ref HAL_ADC_Init() function.
     [..]

     When the compilation flag USE_HAL_ADC_REGISTER_CALLBACKS is set to 0 or
     not defined, the callback registration feature is not available and all callbacks
     are set to the corresponding weak functions.

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x_hal.h"

/** @addtogroup STM32WB0x_HAL_Driver
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define ADC_VBIAS_PRECH_DELAY_PRESC_MAX_VALUE (1020UL) /*!< Used to configure the VBIAS precharge pulse duration.
                                                            With PRECH_DELAY_SEL=0, the maximum delay is 1.02 ms
                                                            (255 x 4 us). */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef *hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);

/* Exported functions --------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    ADC Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC.
      (+) De-initialize the ADC.
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the ADC peripheral according to
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (refer to description of RCC configuration for ADC
  *         in header of this file).
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
  *         coming from ADC state reset. Following calls to this function can
  *         be used to reconfigure some parameters of ADC_InitTypeDef
  *         structure on the fly, without modifying MSP configuration. If ADC
  *         MSP has to be modified again, HAL_ADC_DeInit() must be called
  *         before HAL_ADC_Init().
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure
  *         "ADC_InitTypeDef".
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check ADC handle */
  if (hadc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SAMPLERATE(hadc->Init.SampleRate));
  assert_param(IS_ADC_SAMPLINGMODE(hadc->Init.SamplingMode));
  assert_param(IS_ADC_OVERRUN(hadc->Init.Overrun));
  assert_param(IS_ADC_DATA_INVERT(hadc->Init.InvertOutputMode));
  assert_param(IS_ADC_DATAWIDTH(hadc->Init.DownSamplerConfig.DataWidth));
  assert_param(IS_ADC_DATARATIO(hadc->Init.DownSamplerConfig.DataRatio));
  assert_param(IS_ADC_NB_CONV(hadc->Init.SequenceLength));
  assert_param(IS_ADC_CONVERSIONTYPE(hadc->Init.ConversionType));

  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    /* Init the ADC Callback settings */
    hadc->ConvCpltCallback              = HAL_ADC_ConvCpltCallback;                 /* Legacy weak callback */
    hadc->ConvHalfCpltCallback          = HAL_ADC_ConvHalfCpltCallback;             /* Legacy weak callback */
    hadc->LevelOutOfWindowCallback      = HAL_ADC_LevelOutOfWindowCallback;         /* Legacy weak callback */
    hadc->ErrorCallback                 = HAL_ADC_ErrorCallback;                    /* Legacy weak callback */

    if (hadc->MspInitCallback == NULL)
    {
      hadc->MspInitCallback = HAL_ADC_MspInit; /* Legacy weak MspInit  */
    }

    /* Init the low level hardware */
    hadc->MspInitCallback(hadc);
#else
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);

    /* Initialize Lock */
    hadc->Lock = HAL_UNLOCKED;
  }

#if defined(ADC_CTRL_ADC_LDO_ENA)
  if (LL_ADC_IsInternalRegulatorEnabled(hadc->Instance) == 0UL)
  {
    /* Enable ADC internal voltage regulator */
    LL_ADC_EnableInternalRegulator(hadc->Instance);
  }
#endif /* ADC_CTRL_ADC_LDO_ENA */

  /* Configuration of ADC parameters if there is no conversion on going       */
  /* (ADC may already be enabled at this point if HAL_ADC_Init() is           */
  /* called to update a parameter on the fly).                                */
  if (((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) == 0UL) && (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL))
  {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_DS_BUSY,
                      HAL_ADC_STATE_BUSY_INTERNAL);

    /* Configuration of ADC:                                                  */
    /*  - Sample Rate                              Init.SampleRate            */
    /*  - Sample Rate MSB                          Init.SampleRateMsb         */
    /*  - Sampling Mode                            Init.SamplingMode          */
    /*  - Overrun Mode                             Init.Overrun               */
    /*  - Invert Output Bit Mode                   Init.InvertOutputMode      */
    /*  - Conversion Type                          Init.ConversionType        */

    /* Configure the sample rate */
    LL_ADC_SetSampleRate(hadc->Instance, hadc->Init.SampleRate);

    /* Configure the input sampling mode */
    LL_ADC_SetInputSamplingMode(hadc->Instance, hadc->Init.SamplingMode);

    /* Configure the continuous mode */
    if (hadc->Init.ContinuousConvMode == ENABLE)
    {
      LL_ADC_ContinuousModeEnable(hadc->Instance);
    }
    else
    {
      LL_ADC_ContinuousModeDisable(hadc->Instance);
    }


    /* Configure the overrun mode for the output data */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
    if (hadc->Init.ConversionType == ADC_CONVERSION_WITH_DS)
    {
      LL_ADC_SetOverrunDS(hadc->Instance, hadc->Init.Overrun);
    }
    else
    {
      LL_ADC_SetOverrunDF(hadc->Instance, hadc->Init.Overrun);
    }
#else
    LL_ADC_SetOverrunDS(hadc->Instance, hadc->Init.Overrun);
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

    /* Configure the bit to bit inversion (1' complement) mode */
    if (hadc->Init.InvertOutputMode == ADC_DATA_INVERT_NONE)
    {
      LL_ADC_InvertOutputDiffModeDisable(hadc->Instance);
      LL_ADC_InvertOutputSingleNegModeDisable(hadc->Instance);
    }
    else if (hadc->Init.InvertOutputMode == ADC_DATA_INVERT_DIFF)
    {
      LL_ADC_InvertOutputDiffModeEnable(hadc->Instance);
      LL_ADC_InvertOutputSingleNegModeDisable(hadc->Instance);
    }
    else if (hadc->Init.InvertOutputMode == ADC_DATA_INVERT_SING)
    {
      LL_ADC_InvertOutputDiffModeDisable(hadc->Instance);
      LL_ADC_InvertOutputSingleNegModeEnable(hadc->Instance);
    }
    else
    {
      LL_ADC_InvertOutputDiffModeEnable(hadc->Instance);
      LL_ADC_InvertOutputSingleNegModeEnable(hadc->Instance);
    }

    LL_ADC_ConfigureDSDataOutput(hadc->Instance, hadc->Init.DownSamplerConfig.DataWidth,
                                 hadc->Init.DownSamplerConfig.DataRatio);

    LL_ADC_SetSequenceLength(hadc->Instance, hadc->Init.SequenceLength);

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
    /* Configure the overrun mode for the output data */
    if (hadc->Init.ConversionType == ADC_CONVERSION_WITH_DS)
    {
      /* Configure the operation mode as ADC mode (static/low frequency signal) through the Down Sampler (DS) */
      LL_ADC_SetADCMode(hadc->Instance, LL_ADC_OP_MODE_ADC);
    }
    else
    {
      /* Configure the operation mode as Full ADC mode through the Decimation Filter (DF) */
      LL_ADC_SetADCMode(hadc->Instance, LL_ADC_OP_MODE_FULL);
    }
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

    /* Initialize the ADC state */
    /* Clear HAL_ADC_STATE_BUSY_INTERNAL bit, set HAL_ADC_STATE_READY bit */
    ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL, HAL_ADC_STATE_READY);
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);

    tmp_hal_status = HAL_ERROR;
  }

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check ADC handle */
  if (hadc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL);

  /* Stop potential conversion on going */
  tmp_hal_status = ADC_ConversionStop(hadc);

  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK)
  {
    /* Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);

    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }

  /* Note: HAL ADC deInit is done independently of ADC conversion stop        */
  /*       and disable return status. In case of status fail, attempt to      */
  /*       perform deinitialization anyway and it is up user code in          */
  /*       in HAL_ADC_MspDeInit() to reset the ADC peripheral using           */
  /*       system RCC hard reset.                                             */

  /* ========== Reset ADC registers ========== */
#if defined(ADC_IRQ_EN_MASK)
  /* Reset register IER */
  __HAL_ADC_DISABLE_IT(hadc, ADC_IRQ_EN_MASK);
#endif /* ADC_IRQ_EN_MASK */
#if defined(ADC_IRQ_FLAGS_MASK)
  /* Reset register ISR */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAGS_MASK);
#endif /* ADC_IRQ_FLAGS_MASK */

  /* Reset all the registers */
  CLEAR_BIT(hadc->Instance->CONF, (ADC_CONF_BIT_INVERT_DIFF
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

  SET_BIT(hadc->Instance->CONF, (ADC_CONF_ADC_CONT_1V2 | ADC_CONF_BIT_INVERT_SN | ADC_CONF_SEQUENCE));

  CLEAR_BIT(hadc->Instance->CTRL, (ADC_CTRL_ADC_LDO_ENA
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                                   | ADC_CTRL_DIG_AUD_MODE
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                                   | ADC_CTRL_STOP_OP_MODE | ADC_CTRL_START_CONV
                                   | ADC_CTRL_ADC_ON_OFF));

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  CLEAR_BIT(hadc->Instance->OCM_CTRL, (ADC_OCM_CTRL_OCM_ENA | ADC_OCM_CTRL_OCM_SRC));

  CLEAR_BIT(hadc->Instance->PGA_CONF, (ADC_PGA_CONF_PGA_BIAS | ADC_PGA_CONF_PGA_GAIN));
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

  CLEAR_BIT(hadc->Instance->SWITCH, (ADC_SWITCH_SE_VIN_7 | ADC_SWITCH_SE_VIN_6
                                     | ADC_SWITCH_SE_VIN_5 | ADC_SWITCH_SE_VIN_4
                                     | ADC_SWITCH_SE_VIN_3 | ADC_SWITCH_SE_VIN_2
                                     | ADC_SWITCH_SE_VIN_1 | ADC_SWITCH_SE_VIN_0));

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  CLEAR_BIT(hadc->Instance->DF_CONF, (ADC_DF_CONF_DF_HALF_D_EN
                                      | ADC_DF_CONF_DF_HPF_EN | ADC_DF_CONF_DF_MICROL_RN
                                      | ADC_DF_CONF_PDM_RATE
                                      | ADC_DF_CONF_DF_O_S2U
                                      | ADC_DF_CONF_DF_I_U2S  | ADC_DF_CONF_DF_ITP1P2
                                      | ADC_DF_CONF_DF_CIC_DHF | ADC_DF_CONF_DF_CIC_DEC_FACTOR));

  SET_BIT(hadc->Instance->DF_CONF, (ADC_DF_CONF_PDM_RATE_1 | ADC_DF_CONF_PDM_RATE_2));
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

  CLEAR_BIT(hadc->Instance->DS_CONF, (ADC_DS_CONF_DS_WIDTH | ADC_DS_CONF_DS_RATIO));

  CLEAR_BIT(hadc->Instance->SEQ_1, (ADC_SEQ_1_SEQ7 | ADC_SEQ_1_SEQ6
                                    | ADC_SEQ_1_SEQ5 | ADC_SEQ_1_SEQ4
                                    | ADC_SEQ_1_SEQ3 | ADC_SEQ_1_SEQ2
                                    | ADC_SEQ_1_SEQ1 | ADC_SEQ_1_SEQ0));

  CLEAR_BIT(hadc->Instance->SEQ_2, (ADC_SEQ_2_SEQ15 | ADC_SEQ_2_SEQ14
                                    | ADC_SEQ_2_SEQ13 | ADC_SEQ_2_SEQ12
                                    | ADC_SEQ_2_SEQ11 | ADC_SEQ_2_SEQ10
                                    | ADC_SEQ_2_SEQ9  | ADC_SEQ_2_SEQ8));

  MODIFY_REG(hadc->Instance->COMP_1, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(hadc->Instance->COMP_2, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(hadc->Instance->COMP_3, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);
  MODIFY_REG(hadc->Instance->COMP_4, (ADC_COMP_1_OFFSET1 | ADC_COMP_1_GAIN1), 0x555UL);

  CLEAR_BIT(hadc->Instance->COMP_SEL, (ADC_COMP_SEL_OFFSET_GAIN8 | ADC_COMP_SEL_OFFSET_GAIN7
                                       | ADC_COMP_SEL_OFFSET_GAIN6 | ADC_COMP_SEL_OFFSET_GAIN5
                                       | ADC_COMP_SEL_OFFSET_GAIN4 | ADC_COMP_SEL_OFFSET_GAIN3
                                       | ADC_COMP_SEL_OFFSET_GAIN2 | ADC_COMP_SEL_OFFSET_GAIN1
                                       | ADC_COMP_SEL_OFFSET_GAIN0));

  MODIFY_REG(hadc->Instance->WD_TH, (ADC_WD_TH_WD_HT | ADC_WD_TH_WD_LT), ADC_WD_TH_WD_HT);

  CLEAR_BIT(hadc->Instance->WD_CONF, (ADC_WD_CONF_AWD_CHX));

  CLEAR_BIT(hadc->Instance->IRQ_STATUS, (ADC_IRQ_STATUS_OVR_DS_IRQ
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

  CLEAR_BIT(hadc->Instance->IRQ_ENABLE, (ADC_IRQ_ENABLE_OVR_DS_IRQ_ENA
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

  CLEAR_BIT(hadc->Instance->TIMER_CONF, (ADC_TIMER_CONF_ADC_LDO_DELAY
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
                                         | ADC_TIMER_CONF_PRECH_DELAY_SEL
                                         | ADC_TIMER_CONF_VBIAS_PRECH_DELAY
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
                                        ));
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
  LL_ADC_SetVbiasPrechargeDelay(hadc->Instance, ADC_DEFAULT_VBIAS_PRECH_DELAY_US / 4UL);
#endif /* ADC_SUPPORT_AUDIO_FEATURES */
  LL_ADC_SetADCLDODelay(hadc->Instance, ADC_DEFAULT_LDO_DELAY_US / 4UL);

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  if (hadc->MspDeInitCallback == NULL)
  {
    hadc->MspDeInitCallback = HAL_ADC_MspDeInit; /* Legacy weak MspDeInit  */
  }

  /* DeInit the low level hardware: RCC clock, NVIC */
  hadc->MspDeInitCallback(hadc);
#else
  /* DeInit the low level hardware: RCC clock, NVIC */
  HAL_ADC_MspDeInit(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

  /* Set ADC error code to none */
  ADC_CLEAR_ERRORCODE(hadc);

  /* Set ADC state */
  hadc->State = HAL_ADC_STATE_RESET;

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Initialize the ADC MSP.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspInit must be implemented in the user file.
   */
}

/**
  * @brief  DeInitialize the ADC MSP.
  * @param hadc ADC handle
  * @note   All ADC instances use the same core clock at RCC level, disabling
  *         the core clock reset all ADC instances).
  * @retval None
  */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspDeInit must be implemented in the user file.
   */
}

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User ADC Callback
  *         To be used instead of the weak predefined callback
  * @param  hadc Pointer to a ADC_HandleTypeDef structure that contains
  *                the configuration information for the specified ADC.
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_ADC_CONVERSION_COMPLETE_CB_ID      ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_CONVERSION_HALF_CB_ID          ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID    ADC watchdog callback ID
  *          @arg @ref HAL_ADC_ERROR_CB_ID                    ADC error callback ID
  *          @arg @ref HAL_ADC_MSPINIT_CB_ID                  ADC Msp Init callback ID
  *          @arg @ref HAL_ADC_MSPDEINIT_CB_ID                ADC Msp DeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID,
                                           pADC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  if ((hadc->State & HAL_ADC_STATE_READY) != 0UL)
  {
    switch (CallbackID)
    {
      case HAL_ADC_CONVERSION_COMPLETE_CB_ID :
        hadc->ConvCpltCallback = pCallback;
        break;

      case HAL_ADC_CONVERSION_HALF_CB_ID :
        hadc->ConvHalfCpltCallback = pCallback;
        break;

      case HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID :
        hadc->LevelOutOfWindowCallback = pCallback;
        break;

      case HAL_ADC_ERROR_CB_ID :
        hadc->ErrorCallback = pCallback;
        break;

      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = pCallback;
        break;

      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else if (HAL_ADC_STATE_RESET == hadc->State)
  {
    switch (CallbackID)
    {
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = pCallback;
        break;

      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister a ADC Callback
  *         ADC callback is redirected to the weak predefined callback
  * @param  hadc Pointer to a ADC_HandleTypeDef structure that contains
  *                the configuration information for the specified ADC.
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_ADC_CONVERSION_COMPLETE_CB_ID      ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_CONVERSION_HALF_CB_ID          ADC conversion complete callback ID
  *          @arg @ref HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID    ADC watchdog callback ID
  *          @arg @ref HAL_ADC_ERROR_CB_ID                    ADC error callback ID
  *          @arg @ref HAL_ADC_MSPINIT_CB_ID                  ADC Msp Init callback ID
  *          @arg @ref HAL_ADC_MSPDEINIT_CB_ID                ADC Msp DeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if ((hadc->State & HAL_ADC_STATE_READY) != 0UL)
  {
    switch (CallbackID)
    {
      case HAL_ADC_CONVERSION_COMPLETE_CB_ID :
        hadc->ConvCpltCallback = HAL_ADC_ConvCpltCallback;
        break;

      case HAL_ADC_CONVERSION_HALF_CB_ID :
        hadc->ConvHalfCpltCallback = HAL_ADC_ConvHalfCpltCallback;
        break;

      case HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID  :
        hadc->LevelOutOfWindowCallback = HAL_ADC_LevelOutOfWindowCallback;
        break;

      case HAL_ADC_ERROR_CB_ID :
        hadc->ErrorCallback = HAL_ADC_ErrorCallback;
        break;

      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = HAL_ADC_MspInit; /* Legacy weak MspInit       */
        break;

      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = HAL_ADC_MspDeInit; /* Legacy weak MspDeInit */
        break;

      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_ADC_STATE_RESET == hadc->State)
  {
    switch (CallbackID)
    {
      case HAL_ADC_MSPINIT_CB_ID :
        hadc->MspInitCallback = HAL_ADC_MspInit;                   /* Legacy weak MspInit              */
        break;

      case HAL_ADC_MSPDEINIT_CB_ID :
        hadc->MspDeInitCallback = HAL_ADC_MspDeInit;               /* Legacy weak MspDeInit            */
        break;

      default :
        /* Update the error code */
        hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hadc->ErrorCode |= HAL_ADC_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2 ADC Input and Output operation functions
  * @brief    ADC IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Poll for conversion complete.
      (+) Poll for conversion event.
      (+) Get result of channel conversion.
      (+) Start conversion and enable interruptions.
      (+) Stop conversion and disable interruptions.
      (+) Handle ADC interrupt request
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable ADC DMA transfer.
@endverbatim
  * @{
  */

/**
  * @brief  Enable ADC, start conversion.
  * @note   Interruptions enabled in this function: None.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);

  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                        */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_DS_EOC | HAL_ADC_STATE_DS_OVR,
                      HAL_ADC_STATE_DS_BUSY);

    /* Reset all ADC error code fields */
    ADC_CLEAR_ERRORCODE(hadc);
  }

  /* Clear ADC conversion flag and overrun flag               */
  /* (To ensure of no unknown state from potential previous ADC operations) */
  __HAL_ADC_CLEAR_FLAG(hadc, (ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_OVRDS));

  /* Process unlocked */
  /* Unlock before starting ADC conversions: in case of potential         */
  /* interruption, to let the process to ADC IRQ Handler.                 */
  __HAL_UNLOCK(hadc);

  /* Start ADC conversion */
  LL_ADC_StartConversion(hadc->Instance);

  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion and disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential conversion.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Stop potential conversion on going*/
  tmp_hal_status = ADC_ConversionStop(hadc);

  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK)
  {
    /* Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);

    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_DS_BUSY, HAL_ADC_STATE_READY);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Wait for a conversion to be completed.
  * @note   ADC conversion flags EOS (end of sequence) and EOC (end of
  *         conversion) are cleared by this function.
  * @note   This function cannot be used in a particular setup: ADC configured
  *         in DMA mode and polling for end of each conversion.
  *         In this case, DMA resets the flag EOC and polling cannot be
  *         performed on each conversion. Nevertheless, polling can still
  *         be performed on the complete sequence.
  * @param hadc ADC handle
  * @param Timeout Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Wait until End of unitary conversion or sequence conversions flag is raised */
  while (__HAL_ADC_GET_FLAG(hadc, ADC_IRQ_FLAG_EODS) == 0UL)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0UL))
      {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);

        /* Process unlocked */
        __HAL_UNLOCK(hadc);

        return HAL_TIMEOUT;
      }
    }
  }

  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_DS_EOC);

  /* Check whether end of sequence is reached */
  if (__HAL_ADC_GET_FLAG(hadc, ADC_IRQ_FLAG_EOS))
  {
    /* Set ADC state */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_DS_BUSY);
  }

  /* Clear polled flag */
  __HAL_ADC_CLEAR_FLAG(hadc, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Poll for ADC event.
  * @param hadc ADC handle
  * @param EventType the ADC event type.
  *          This parameter can be one of the following values:
  *          ADC_IRQ_FLAG_OVRFL   ADC decimation filter saturated event (1)
  *          ADC_IRQ_FLAG_OVRDF   ADC decimation filter overrun event (1)
  *          ADC_IRQ_FLAG_EODF    ADC decimation filter conversion completed event (1)
  *          ADC_IRQ_FLAG_OVRDS   ADC Down Sampler overrun event
  *          ADC_IRQ_FLAG_AWD1     ADC analog watchdog event
  *          ADC_IRQ_FLAG_EOS     ADC sequence of conversion completed event
  *          ADC_IRQ_FLAG_EODS    ADC Down Sampler conversion completed Event
  *         (1) todo: Only available on STM32WB0x
  * @param Timeout Timeout value in millisecond.
  * @note   The relevant flag is cleared if found to be set, except for
  *         ADC_IRQ_FLAG_OVRDS.
  *         Indeed, the latter is reset only if hadc->Init.Overrun field is set
  *         to ADC_NEW_DATA_IS_KEPT. Otherwise, data register may be
  *         potentially overwritten by a new converted data as soon as OVR is
  *         cleared.
  *         To reset OVR flag once the preserved data is retrieved, the user can
  *         resort to macro __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRDS);
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Check selected event flag */
  while (__HAL_ADC_GET_FLAG(hadc, EventType) == 0UL)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0UL))
      {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);

        /* Process unlocked */
        __HAL_UNLOCK(hadc);

        return HAL_TIMEOUT;
      }
    }
  }

  switch (EventType)
  {
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
    /* Check decimation filter saturated flag */
    case ADC_IRQ_FLAG_OVRFL:
      /* If overrun is set to overwrite previous data, overrun event is not     */
      /* considered as an error.                                                */
      if (hadc->Init.Overrun == ADC_NEW_DATA_IS_KEPT)
      {
        /* Set ADC state */
        SET_BIT(hadc->State, HAL_ADC_STATE_DF_OVR);

        /* Set ADC error code to overrun */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);
      }
      else
      {
        /* Clear ADC Overrun flag only if Overrun is set to ADC_NEW_DATA_IS_KEPT
          otherwise, data register is potentially overwritten by new converted data as soon
          as OVR is cleared. */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRFL);
      }

      break;

    /* Check decimation filter overrun flag */
    case ADC_IRQ_FLAG_OVRDF:
      /* If overrun is set to overwrite previous data, overrun event is not     */
      /* considered as an error.                                                */
      if (hadc->Init.Overrun == ADC_NEW_DATA_IS_KEPT)
      {
        /* Set ADC state */
        SET_BIT(hadc->State, HAL_ADC_STATE_DF_OVR);

        /* Set ADC error code to overrun */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);
      }
      else
      {
        /* Clear ADC Overrun flag only if Overrun is set to ADC_NEW_DATA_IS_KEPT
          otherwise, data register is potentially overwritten by new converted data as soon
          as OVR is cleared. */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRDF);
      }
      break;

    /* Check decimation filter conversion completed flag */
    case ADC_IRQ_FLAG_EODF:
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_DF_EOC);

      /* Clear ADC decimation filter conversion completed flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_EODF);

      break;
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

    /* Check analog watchdog flag */
    case ADC_IRQ_FLAG_AWD1:
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_AWD1);

      /* Clear ADC analog watchdog flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_AWD1);

      break;

    /* Check sequence of conversion completed flag */
    case ADC_IRQ_FLAG_EOS:
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_DS_EOC);

      /* Clear ADC sequence of conversion completed flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_EOS);

      break;

    /* Check Down Sampler conversion completed flag */
    case ADC_IRQ_FLAG_EODS:
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_DS_EOC);

      /* Clear ADC Down Sampler conversion completed flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_EODS);

      break;

    /* Overrun event */
    default: /* Case ADC_OVR_EVENT */
      /* If overrun is set to overwrite previous data, overrun event is not     */
      /* considered as an error.                                                */
      if (hadc->Init.Overrun == ADC_NEW_DATA_IS_LOST)
      {
        /* Set ADC state */
        SET_BIT(hadc->State, HAL_ADC_STATE_DS_OVR);

        /* Set ADC error code to overrun */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);
      }
      else
      {
        /* Clear ADC Overrun flag only if Overrun is set to ADC_NEW_DATA_IS_KEPT
          otherwise, data register is potentially overwritten by new converted data as soon
          as OVR is cleared. */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRDS);
      }
      break;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enable ADC and start conversion with interruption.
  * @note   Interruptions enabled in this function according to initialization
  *         setting : EOC (end of conversion), EOS (end of sequence),
  *         OVR overrun.
  *         Each of these interruptions has its dedicated callback function.
  * @note   To guarantee a proper reset of all interruptions once all the needed
  *         conversions are obtained, HAL_ADC_Stop_IT() must be called to ensure
  *         a correct stop of the IT-based conversions.
  * @param hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);

  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                        */
    /* - Clear state bitfield related to conversion results   */
    /* - Set state bitfield related to operation                    */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_DS_EOC | HAL_ADC_STATE_DS_OVR,
                      HAL_ADC_STATE_DS_BUSY);

    /* Reset all ADC error code fields */
    ADC_CLEAR_ERRORCODE(hadc);

    /* Clear ADC conversion flag and overrun flag               */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_OVRDS));

    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential         */
    /* interruption, to let the process to ADC IRQ Handler.                 */
    __HAL_UNLOCK(hadc);

    /* Disable all interruptions before enabling the desired ones */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS | ADC_IRQ_EN_OVRDS));

    /* Enable ADC end of conversion interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IRQ_EN_EOS);

    /* Enable ADC overrun interrupt */
    /* If hadc->Init.Overrun is set to ADC_NEW_DATA_IS_LOST, only then is */
    /* ADC_IRQ_EN_OVRDS enabled; otherwise data overwrite is considered as  */
    /* normal behavior and no CPU time is lost for a non-processed          */
    /* interruption.                                                        */
    if (hadc->Init.Overrun == ADC_NEW_DATA_IS_LOST)
    {
      __HAL_ADC_ENABLE_IT(hadc, ADC_IRQ_EN_OVRDS);
    }

    /* Enable conversion.                                                   */
    /* If software start has been selected, conversion starts immediately.  */
    /* If external trigger has been selected, conversion will start at next */
    /* trigger event.                                                       */
    /* Start ADC conversion */
    LL_ADC_StartConversion(hadc->Instance);

  }
  else
  {
    tmp_hal_status = HAL_BUSY;
  }

  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion, disable interrution of
  *         end-of-conversion, disable ADC peripheral.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* 1. Stop potential conversion on going*/
  tmp_hal_status = ADC_ConversionStop(hadc);

  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK)
  {
    /* Disable ADC end of conversion interrupt */
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS | ADC_IRQ_EN_OVRDS));

    /* 2. Disable the ADC peripheral */
    tmp_hal_status = ADC_Disable(hadc);

    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_DS_BUSY, HAL_ADC_STATE_READY);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Enable ADC, start conversion and transfer result through DMA.
  * @note   Interruptions enabled in this function:
  *         overrun (if applicable), DMA half transfer, DMA transfer complete.
  *         Each of these interruptions has its dedicated callback function.
  *         The ADC continuous mode is enabled in this DMA acquisition mode.
  * @param hadc ADC handle
  * @param pData Destination Buffer address.
  * @param Length Number of data to be transferred from ADC peripheral to memory
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, const uint32_t *pData, uint32_t Length)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);

  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                      */
    /* - Clear state bitfield related to conversion results               */
    /* - Set state bitfield related to operation                          */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_DS_EOC | HAL_ADC_STATE_DS_OVR,
                      HAL_ADC_STATE_DS_BUSY);

    /* Reset all ADC error code fields */
    ADC_CLEAR_ERRORCODE(hadc);

    /* Set the DMA transfer complete callback */
    hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;

    /* Set the DMA half transfer complete callback */
    hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;

    /* Set the DMA error callback */
    hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;

    /* Manage ADC and DMA start: ADC overrun interruption, DMA start,     */
    /* ADC start (in case of SW start):                                   */

    /* Clear conversion flag and overrun flag                             */
    /* (To ensure of no unknown state from potential previous ADC         */
    /* operations)                                                        */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_OVRDS));

    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential       */
    /* interruption, to let the process to ADC IRQ Handler.               */
    __HAL_UNLOCK(hadc);

    /* With DMA, overrun event is always considered as an error even if
        hadc->Init. Overrun is set to ADC_NEW_DATA_IS_KEPT. Therefore,
        ADC_IRQ_EN_OVRDS is enabled. */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IRQ_EN_OVRDS);

    /* Enable ADC DMA mode */
    LL_ADC_DMAModeDSEnable(hadc->Instance);

    /* Start the DMA channel */
    tmp_hal_status = HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DS_DATAOUT, (uint32_t)pData,
                                      Length);

    if (tmp_hal_status != HAL_ERROR)
    {
      /* Enable conversion.                                                   */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      /* Start ADC group conversion */
      LL_ADC_StartConversion(hadc->Instance);
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }

  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Stop ADC conversion, disable ADC DMA transfer, disable
  *         ADC peripheral.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* 1. Stop potential ADC conversion on going */
  LL_ADC_ContinuousModeDisable(hadc->Instance);
  tmp_hal_status = ADC_ConversionStop(hadc);

  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmp_hal_status == HAL_OK)
  {

    /* Abort the ADC DMA channel */
    if (hadc->DMA_Handle != NULL)
    {
      /* Disable ADC DMA (ADC DMA configuration of continuous requests is kept) */
      LL_ADC_DMAModeDSDisable(hadc->Instance);

      if (HAL_DMA_Abort_IT(hadc->DMA_Handle) != HAL_OK)
      {
        if (HAL_DMA_GetError(hadc->DMA_Handle) == HAL_DMA_ERROR_TIMEOUT)
        {
          /* Set error code to DMA */
          hadc->ErrorCode = HAL_ADC_ERROR_DMA;

          /* Process Unlocked */
          __HAL_UNLOCK(hadc);

          return HAL_TIMEOUT;
        }
      }
    }

    /* Disable the DMA channel (in case of DMA in circular mode or stop       */
    /* while DMA transfer is on going)                                        */
    if (hadc->DMA_Handle->State == HAL_DMA_STATE_BUSY)
    {
      tmp_hal_status = HAL_DMA_Abort(hadc->DMA_Handle);

      /* Check if DMA channel effectively disabled */
      if (tmp_hal_status != HAL_OK)
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_DMA);
      }
    }

    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IRQ_EN_OVRDS);

    /* 2. Disable the ADC peripheral */
    /* Update "tmp_hal_status" only if DMA channel disabling passed,          */
    /* to keep in memory a potential failing status.                          */
    if (tmp_hal_status == HAL_OK)
    {
      tmp_hal_status = ADC_Disable(hadc);
    }
    else
    {
      (void)ADC_Disable(hadc);
    }

    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_DS_BUSY, HAL_ADC_STATE_READY);
    }

  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Get ADC conversion result (raw value).
  * @note   Occurrence of flag EOS rising:
  *          - If sequencer is composed of 1 rank, flag EOS is equivalent
  *            to flag EOC.
  *          - If sequencer is composed of several ranks, during the scan
  *            sequence flag EOC only is raised, at the end of the scan sequence
  *            both flags EOC and EOS are raised.
  *         The flag EODS is rising when the Down Sampler conversion is
  *         completed.
  *         To clear those flags, either use function:
  *         in programming model IT: @ref HAL_ADC_IRQHandler(), in programming
  *         model polling: @ref HAL_ADC_PollForConversion()
  *         or @ref __HAL_ADC_CLEAR_FLAG(&hadc, ADC_IRQ_FLAG_EOS).
  * @param hadc ADC handle
  * @retval ADC conversion data
  */
uint32_t HAL_ADC_GetValue(const ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Return ADC converted value */
  return LL_ADC_DSGetOutputData(hadc->Instance);
}

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief  Get ADC conversion result from decimation filter(raw value).
  * @note   Flag EODF is rising when decimation filter conversion is
  *         completed.
  *         To clear this flag, either use function:
  *         in programming model IT: @ref HAL_ADC_IRQHandler(), in programming
  *         model polling: @ref HAL_ADC_PollForConversion()
  *         or @ref __HAL_ADC_CLEAR_FLAG(&hadc, ADC_IRQ_FLAG_EOS).
  * @param hadc ADC handle
  * @retval ADC conversion data
  */
uint32_t HAL_ADC_GetValue_DF(const ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Return ADC converted value */
  return LL_ADC_DFGetOutputData(hadc->Instance);
}
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/**
  * @brief  Handle ADC interrupt request.
  * @param hadc ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc)
{
  uint32_t overrun_error = 0UL; /* flag set if overrun occurrence has to be considered as an error */
  uint32_t tmp_ier = hadc->Instance->IRQ_ENABLE;
  uint32_t tmp_isr = LL_ADC_GetActiveFlags(hadc->Instance);

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* ====== Check ADC end of unitary conversion sequence conversions ===== */
  if ((((tmp_isr & ADC_IRQ_FLAG_EODS) == ADC_IRQ_FLAG_EODS) && ((tmp_ier & ADC_IRQ_EN_EODS) == ADC_IRQ_EN_EODS)) ||
      (((tmp_isr & ADC_IRQ_FLAG_EOS)  == ADC_IRQ_FLAG_EOS)  && ((tmp_ier & ADC_IRQ_EN_EOS)  == ADC_IRQ_EN_EOS))  ||
      (((tmp_isr & ADC_IRQ_FLAG_EOC)  == ADC_IRQ_FLAG_EOC)  && ((tmp_ier & ADC_IRQ_EN_EOC)  == ADC_IRQ_EN_EOC)))
  {
    /* Update state machine on conversion status if not in error state */
    if ((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) == 0UL)
    {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_DS_EOC);
    }

    /* Carry on if continuous mode is disabled */
    if (!LL_ADC_IsContinuousModeEnabled(hadc->Instance))
    {
      /* If End of Sequence is reached, disable interrupts */
      if (__HAL_ADC_GET_FLAG(hadc, ADC_IRQ_FLAG_EOS))
      {
        /* Disable ADC end of sequence conversion interrupt */
        /* Note: Overrun interrupt was enabled with EOC interrupt in      */
        /* HAL_Start_IT(), but is not disabled here because can be used   */
        /* by overrun IRQ process below.                                  */
        __HAL_ADC_DISABLE_IT(hadc, ADC_IRQ_EN_EODS | ADC_IRQ_EN_EOS | ADC_IRQ_EN_EOC);

        /* Set ADC state */
        CLEAR_BIT(hadc->State, HAL_ADC_STATE_DS_BUSY);

        SET_BIT(hadc->State, HAL_ADC_STATE_READY);
      }
    }

    /* Conversion complete callback */
    /* Note: Into callback function "HAL_ADC_ConvCpltCallback()",             */
    /*       to determine if conversion has been triggered from EOC or EOS,   */
    /*       possibility to use:                                              */
    /*        " if (__HAL_ADC_GET_FLAG(&hadc, ADC_IRQ_FLAG_EOS)) "                */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->ConvCpltCallback(hadc);
#else
    HAL_ADC_ConvCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

    /* Clear conversion flag */
    /* Note: in case of overrun set to ADC_NEW_DATA_IS_LOST, end of         */
    /*       conversion flags clear induces the release of the preserved data.*/
    /*       Therefore, if the preserved data value is needed, it must be     */
    /*       read preliminarily into HAL_ADC_ConvCpltCallback().              */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_IRQ_FLAG_EODS | ADC_IRQ_FLAG_EOS | ADC_IRQ_FLAG_EOC));
  }

  /* ========== Check Analog watchdog 1 flag ========== */
  if (((tmp_isr & ADC_IRQ_FLAG_AWD1) == ADC_IRQ_FLAG_AWD1) && ((tmp_ier & ADC_IRQ_FLAG_AWD1) == ADC_IRQ_FLAG_AWD1))
  {
    /* Set ADC state */
    SET_BIT(hadc->State, HAL_ADC_STATE_AWD1);

    /* Level out of window 1 callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->LevelOutOfWindowCallback(hadc);
#else
    HAL_ADC_LevelOutOfWindowCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */

    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_AWD1);
  }

  /* ========== Check Overrun flag ========== */
  if (((tmp_isr & ADC_IRQ_FLAG_OVRDS) == ADC_IRQ_FLAG_OVRDS) && ((tmp_ier & ADC_IRQ_EN_OVRDS) == ADC_IRQ_EN_OVRDS))
  {
    /* If overrun is set to overwrite previous data (default setting),        */
    /* overrun event is not considered as an error.                           */
    /* Exception for usage with DMA overrun event always considered as an     */
    /* error.                                                                 */
    if (hadc->Init.Overrun == ADC_NEW_DATA_IS_LOST)
    {
      overrun_error = 1UL;
    }
    else
    {
      /* Check DMA configuration */
      if (LL_ADC_IsDMAModeDSEnabled(hadc->Instance))
      {
        overrun_error = 1UL;
      }
    }

    if (overrun_error == 1UL)
    {
      /* Change ADC state to error state */
      SET_BIT(hadc->State, HAL_ADC_STATE_DS_OVR);

      /* Set ADC error code to overrun */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_OVR);

      /* Error callback */
      /* Note: In case of overrun, ADC conversion data is preserved until     */
      /*       flag OVR is reset.                                             */
      /*       Therefore, old ADC conversion data can be retrieved in         */
      /*       function "HAL_ADC_ErrorCallback()".                            */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
      hadc->ErrorCallback(hadc);
#else
      HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    }

    /* Clear ADC overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_IRQ_FLAG_OVRDS);
  }

}


/**
  * @brief  Conversion complete callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Conversion DMA half-transfer callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvHalfCpltCallback must be implemented in the user file.
  */
}


/**
  * @brief  Analog watchdog callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOutOfWindowCallback must be implemented in the user file.
  */
}


/**
  * @brief  ADC error callback in non-blocking mode
  *         (ADC conversion with interruption or transfer by DMA).
  * @note   In case of error due to overrun when using ADC with DMA transfer
  *         (HAL ADC handle parameter "ErrorCode" to state "HAL_ADC_ERROR_OVR"):
  *         - Reinitialize the DMA using function "HAL_ADC_Stop_DMA()".
  *         - If needed, restart a new ADC conversion using function
  *           "HAL_ADC_Start_DMA()"
  *           (this function is also clearing overrun flag)
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ErrorCallback must be implemented in the user file.
  */
}


/**
  * @}
  */
#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_Exported_Functions_Group4 Microphone Interface Control functions
  * @brief Configure and start Microphone Interface (analog and digital)
  *
@verbatim
 ===============================================================================
             ##### Microphone Interface Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the analog microphone interface (Gain & VoltageBias)
      (+) Configure the digital microphone interface (Clock rate)
      (+) Start the ADC digital microphone mode

@endverbatim
  * @{
  */

/**
  * @brief  Select the left/right channel on digital microphone mode.
  * @param hadc ADC handle
  * @param MicrophoneChannel This parameter can be one of the following values:
  * @arg @ref ADC_DF_MIC_CH_LEFT
  * @arg @ref ADC_DF_MIC_CH_RIGHT
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_SetMicrophoneChannel(ADC_HandleTypeDef *hadc, uint32_t MicrophoneChannel)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_DF_MICROPHONE_CHANNEL(MicrophoneChannel));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SetMicrophoneChannel(hadc->Instance, MicrophoneChannel);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Configure the PDM clock rate.
  *         The PDM clock rate is : SYSTEM_CLOCK / (Divider).
  * @param hadc ADC handle
  * @param ConfigPDM Structure of PDM Interface configuration
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_PDMConfig(ADC_HandleTypeDef *hadc, const ADC_PDMConfTypeDef *ConfigPDM)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_PDM_CLOCK_DIVIDER(ConfigPDM->ClockDivider));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SetPDMRate(hadc->Instance, ConfigPDM->ClockDivider);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief Enable the digital audio mode.
  * @param hadc ADC handle
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_PDMStart(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_AudioModeEnable(hadc->Instance);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Disable the digital audio mode.
  * @param hadc ADC handle
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_PDMStop(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_AudioModeDisable(hadc->Instance);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief Configure PGA used in the ADC analog microphone mode.
  * @note The PGA voltage bias value is expressed as a ratio of the battery
  *       voltage VBAT, between 0.5 and 0.9.
  * @note The PGA gain value is expressed in DB
  * @param hadc ADC handle
  * @param ConfigPGA Structure of PGA parameters.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_PGAConfig(ADC_HandleTypeDef *hadc, const ADC_PGAConfTypeDef *ConfigPGA)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_PGA_BIAS(ConfigPGA->Bias));
  assert_param(IS_ADC_PGA_GAIN(ConfigPGA->Gain));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_ConfigureMicrophonePGA(hadc->Instance, ConfigPGA->Bias, ConfigPGA->Gain);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}
/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/** @defgroup ADC_Exported_Functions_Group5 Occasional Mode Control functions
  * @brief Configure and start occasional mode
  *
@verbatim
 ===============================================================================
             ##### Occasional Mode Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the channel converted in occasional mode
      (+) Start an occasional conversion

@endverbatim
  * @{
  */

/**
  * @brief  Set the ADC occasional conversion source.
  * @param hadc ADC handle
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref ADC_OCM_SRC_VBAT
  *         @arg @ref ADC_OCM_SRC_TEMP
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_SetOccasionalSource(ADC_HandleTypeDef *hadc, uint32_t Source)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_OCM_SOURCE(Source));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SetOccasionalConversionSource(hadc->Instance, Source);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief Start an ADC occasional conversion during an analog audio conversion
  *        or during an ADC full mode.
  * @param hadc ADC handle
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_StartOccasionalMode(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_StartOccasionalConversionMode(hadc->Instance);

  /* Process locked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @}
  */
#endif /* ADC_SUPPORT_AUDIO_FEATURES */

/** @defgroup ADC_Exported_Functions_Group6 Analog Timing Control functions
  * @brief Configure analog related timing parameters
@verbatim
 ===============================================================================
             ##### Analog Timing Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the synchronisation between SMPS and ADC start of conversion
      (+) Configure the ADC PGA VBias precharge duration
      (+) Configure the ADC LDO delay

@endverbatim
  * @{
  */

/**
  * @brief  Enable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   The synchronization should only be enabled when using the SMPS with
  *         an ADC clock different from 32 MHz.
  * @param hadc ADC handle
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_SMPSSyncEnable(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SMPSSyncEnable(hadc->Instance);

  /* Process locked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Disable the synchronization of the ADC start conversion with
  *         a pulse generated by the SMPS.
  * @note   The synchronization should only be enabled when using the SMPS with
  *         an ADC clock different from 32 MHz.
  * @param hadc ADC handle
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_SMPSSyncDisable(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SMPSSyncDisable(hadc->Instance);

  /* Process locked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief Configure the Vbias precharge time of the Programmable Gain Amplifier.
  * @note The delay in microseconds corresponding to the duration of a waiting
  *       time starting at rising edge of PGA_EN signal. This duration is the
  *       VBIAS precharge pulse duration.
  * @note The delay value should be an increment of 4us between 0us and 1020.
  *       Then the value should be an increment of 4096us between 4096us and
  *       1044480us. If these requirements are not met the function configure
  *       an approximate available value close to the input value.
  * @note This value is configured at reset to a default value. This value can be
  *       reconfigured using @arg @ref ADC_DEFAULT_VBIAS_PRECH_DELAY_US.
  * @param hadc ADC handle
  * @param Delay_us delay in us. This parameter must be a number between
  *                 Min_Data = 4 and Max_Data = 1'044'480.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_VBiasPrechargeDelayConfig(ADC_HandleTypeDef *hadc, uint32_t Delay_us)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_PGA_VBIAS_PRECHARGE_DELAY(Delay_us));

  /* Process locked */
  __HAL_LOCK(hadc);

  if (Delay_us <= ADC_VBIAS_PRECH_DELAY_PRESC_MAX_VALUE)
  {
    LL_ADC_VbiasPrechargeDelayPrescalerDisable(hadc->Instance);
    LL_ADC_SetVbiasPrechargeDelay(hadc->Instance, (Delay_us) / (4UL));
  }
  else
  {
    LL_ADC_VbiasPrechargeDelayPrescalerEnable(hadc->Instance);
    LL_ADC_SetVbiasPrechargeDelay(hadc->Instance, (Delay_us) / (4096UL));
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

#endif /* ADC_SUPPORT_AUDIO_FEATURES */
/**
  * @brief Configure the LDO stabilization time
  * @note The delay in microseconds corresponding to the duration of a waiting
  *       time to be inserted between the ADC_LDO enable and the ADC ON to let
  *       the LDO stabilize before starting a conversion.
  * @note The delay value should be an increment of 4us. Otherwise the function
  *       configure an approximate available value close to the input value.
  * @note This value is configured at reset to a default value. This value can be
  *       reconfigured using @arg @ref ADC_DEFAULT_LDO_DELAY_US.
  * @param hadc ADC handle
  * @param Delay_us delay in us. This parameter must be a number between
  *                 Min_Data = 4 and Max_Data = 1020.
  * @return HAL status
  */
HAL_StatusTypeDef HAL_ADC_LDODelayConfig(ADC_HandleTypeDef *hadc, uint32_t Delay_us)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_LDO_DELAY(Delay_us));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SetADCLDODelay(hadc->Instance, (Delay_us) / 0xFFUL);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}
/**
  * @}
  */


/** @defgroup ADC_Exported_Functions_Group3 Peripheral Control functions
  * @brief    Peripheral Control functions
  *
@verbatim
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure channels on a conversion sequence
      (+) Configure the analog watchdog

@endverbatim
  * @{
  */

/**
  * @brief Configure a channel to be assigned to ADC conversion sequence.
  * @param hadc ADC handle
  * @param sConfigChannel Structure of ADC channel configuration and position in
  *                       ADC conversion sequence.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, const ADC_ChannelConfTypeDef *sConfigChannel)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tmp_gain;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_RANK(sConfigChannel->Rank));
  assert_param(IS_ADC_VOLTAGE_RANGE(sConfigChannel->VoltRange));
  assert_param(IS_ADC_CHANNEL(sConfigChannel->Channel));

  assert_param(IS_ADC_CALIBRATION_POINT(sConfigChannel->CalibrationPoint.Number));
  assert_param(IS_ADC_CALIBRATION_GAIN(sConfigChannel->CalibrationPoint.Gain));
  assert_param(IS_ADC_CALIBRATION_OFFSET(sConfigChannel->CalibrationPoint.Offset));

  /* Process locked */
  __HAL_LOCK(hadc);

  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL)
  {
    LL_ADC_SetSequencerRanks(hadc->Instance, sConfigChannel->Rank, sConfigChannel->Channel);
    if ((sConfigChannel->Channel != ADC_CHANNEL_TEMPSENSOR)
        && (sConfigChannel->Channel != ADC_CHANNEL_VBAT))
    {
      LL_ADC_SetChannelVoltageRange(hadc->Instance, sConfigChannel->Channel, sConfigChannel->VoltRange);
    }
  }
  /* If a conversion is on going no update could be done on                   */
  /* neither of the channel configuration structure parameters.               */
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

    tmp_hal_status = HAL_ERROR;
  }

  if (sConfigChannel->CalibrationPoint.Number != ADC_CALIB_NONE)
  {
    if (sConfigChannel->CalibrationPoint.Gain != 0UL)
    {
      tmp_gain = sConfigChannel->CalibrationPoint.Gain;
    }
    else if ((sConfigChannel->VoltRange == ADC_VIN_RANGE_1V2)
             || (sConfigChannel->Channel == ADC_CHANNEL_TEMPSENSOR))
    {
      /* 1.2V mode: [calibrated gain = 0.96, gain clamped at 1] */
      tmp_gain = 0xFFFUL;
    }
    else if (sConfigChannel->VoltRange == ADC_VIN_RANGE_2V4)
    {
      /* 2.4V mode: [calibrated gain = 1/2] */
      tmp_gain = 0x7FFUL;
    }
    else /* ADC_VIN_RANGE_3V6 */
    {
      /* 3.6V mode: [calibrated gain = 1/3] */
      tmp_gain = 0x555UL;
    }
    LL_ADC_ConfigureCalibPoint(hadc->Instance, sConfigChannel->CalibrationPoint.Number,
                               tmp_gain, sConfigChannel->CalibrationPoint.Offset);

    switch (sConfigChannel->Channel)
    {
      case ADC_CHANNEL_VINM0:
      case ADC_CHANNEL_VINM1:
      case ADC_CHANNEL_VINM2:
      case ADC_CHANNEL_VINM3:
      {
        LL_ADC_SetCalibPointForSingleNeg(hadc->Instance, sConfigChannel->CalibrationPoint.Number,
                                         sConfigChannel->VoltRange);
        break;
      }
      case ADC_CHANNEL_VINP0:
      case ADC_CHANNEL_VINP1:
      case ADC_CHANNEL_VINP2:
      case ADC_CHANNEL_VINP3:
      {
        LL_ADC_SetCalibPointForSinglePos(hadc->Instance, sConfigChannel->CalibrationPoint.Number,
                                         sConfigChannel->VoltRange);
        break;
      }
      case ADC_CHANNEL_VINP0_VINM0:
      case ADC_CHANNEL_VINP1_VINM1:
      case ADC_CHANNEL_VINP2_VINM2:
      case ADC_CHANNEL_VINP3_VINM3:
      {
        LL_ADC_SetCalibPointForDiff(hadc->Instance, sConfigChannel->CalibrationPoint.Number, sConfigChannel->VoltRange);
        break;
      }
      case ADC_CHANNEL_VBAT:
      {
        LL_ADC_SetCalibPointForSingleNeg(hadc->Instance, sConfigChannel->CalibrationPoint.Number,
                                         LL_ADC_VIN_RANGE_3V6);
        break;
      }
      case ADC_CHANNEL_TEMPSENSOR:
      {
        LL_ADC_SetCalibPointForSinglePos(hadc->Instance, sConfigChannel->CalibrationPoint.Number,
                                         LL_ADC_VIN_RANGE_1V2);
        break;
      }
      default:
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

        tmp_hal_status = HAL_ERROR;
        break;
      }
    }
  }
  else
  {
    /* Nothing to do */
    __NOP();
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Configure the watchdog.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the watchdog, successive
  *         calls to this function can be used to reconfigure some parameters
  *         of structure "ADC_AnalogWDGConfTypeDef" on the fly, without
  *         resetting the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  * @param hadc ADC handle
  * @param ConfigWatchdog Structure of ADC watchdog configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, const ADC_AnalogWDGConfTypeDef *ConfigWatchdog)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_AWD_CHANNEL(ConfigWatchdog->ChannelMask));
  assert_param(IS_ADC_AWD_EVENT_TYPE(ConfigWatchdog->EventType));

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Check if there is a conversion on going */
  if (LL_ADC_IsConversionOngoing(hadc->Instance) == 0UL)
  {
    /* Configure the thresholds */
    LL_ADC_ConfigureAWDThresholds(hadc->Instance, ConfigWatchdog->LowThreshold, ConfigWatchdog->HighThreshold);

    /* Set the channels mask */
    LL_ADC_SetAWDInputChannels(hadc->Instance, ConfigWatchdog->ChannelMask);

    /* Update state, clear previous result related to watchdog */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_AWD1);

    /* Clear flag ADC analog watchdog */
    /* Note: Flag cleared Clear the ADC Analog watchdog flag to be ready  */
    /* to use for HAL_ADC_IRQHandler() or HAL_ADC_PollForEvent()          */
    /* (in case left enabled by previous ADC operations).                 */
    LL_ADC_ClearFlag_AWD(hadc->Instance);

    /* Configure ADC analog watchdog interrupt */
    if (ConfigWatchdog->EventType == ADC_AWD_EVENT_INTERRUPT)
    {
      LL_ADC_EnableIT_AWD(hadc->Instance);
    }
    else
    {
      LL_ADC_DisableIT_AWD(hadc->Instance);
    }
  }
  /* If a conversion is on going , no update could be done */
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

    tmp_hal_status = HAL_ERROR;
  }
  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

#if defined(ADC_SUPPORT_AUDIO_FEATURES)
/**
  * @brief Configure the decimation filter
  *
  * @param hadc ADC handle
  * @param ConfigDF Structure of decimation filter configuration
  * @return status HAL
  */
HAL_StatusTypeDef HAL_ADC_DFConfig(ADC_HandleTypeDef *hadc, const ADC_DFConfTypeDef *ConfigDF)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_DF_DYNAMIC_RANGE(ConfigDF->DynamicMode));
  assert_param(IS_FUNCTIONAL_STATE(ConfigDF->HighPassFilter));
  assert_param(IS_ADC_DF_DATA_FORMAT(ConfigDF->OutputDataFormatMode));
  assert_param(IS_ADC_DF_DATA_FORMAT(ConfigDF->InputDataFormatMode));
  assert_param(IS_FUNCTIONAL_STATE(ConfigDF->FractionalInterpolator));
  assert_param(IS_ADC_DF_CIC_DECIMATOR_HALF_FACTOR(ConfigDF->CICFilterDecimatorHalfFactor));
  assert_param(IS_ADC_DF_CIC_DECIMATOR_FACTOR(ConfigDF->MCICOutputFrequency));

  /* Process locked */
  __HAL_LOCK(hadc);

  LL_ADC_SetDFInputDynamic(hadc->Instance, ConfigDF->DynamicMode);
  if (ConfigDF->HighPassFilter == ENABLE)
  {
    LL_ADC_DFHighPassFilterEnable(hadc->Instance);
  }
  else
  {
    LL_ADC_DFHighPassFilterDisable(hadc->Instance);
  }

  LL_ADC_SetDataOutputFormat(hadc->Instance, ConfigDF->OutputDataFormatMode);
  LL_ADC_SetDataInputFormat(hadc->Instance, ConfigDF->InputDataFormatMode);
  if (ConfigDF->FractionalInterpolator == ENABLE)
  {
    LL_ADC_FractionalInterpolatorEnable(hadc->Instance);
  }
  else
  {
    LL_ADC_FractionalInterpolatorDisable(hadc->Instance);
  }
  LL_ADC_SetCICDecimatorFactor(hadc->Instance, ConfigDF->CICFilterDecimatorHalfFactor);
  LL_ADC_SetMicrophoneOutputDatarate(hadc->Instance, ConfigDF->MCICOutputFrequency);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

#endif /* ADC_SUPPORT_AUDIO_FEATURES */
/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group7 Peripheral State functions
  * @brief    ADC Peripheral State functions
  *
@verbatim
 ===============================================================================
            ##### Peripheral state and errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions to get in run-time the status of the
    peripheral.
      (+) Check the ADC state
      (+) Check the ADC error code

@endverbatim
  * @{
  */

/**
  * @brief  Return the ADC handle state.
  * @note   ADC state machine is managed by bitfields, ADC status must be
  *         compared with states bits.
  *         For example:
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_DS_BUSY) != 0UL) "
  *           " if ((HAL_ADC_GetState(hadc) & HAL_ADC_STATE_AWD1) != 0UL) "
  * @param hadc ADC handle
  * @retval ADC handle state (bitfield on 32 bits)
  */
uint32_t HAL_ADC_GetState(const ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Return ADC handle state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code.
  * @param hadc ADC handle
  * @retval ADC error code (bitfield on 32 bits)
  */
uint32_t HAL_ADC_GetError(const ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  return hadc->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/**
  * @brief Stop ADC conversion.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef *hadc)
{
  uint32_t is_conversion_on;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Verification if ADC is not already stopped to bypass this function if    */
  /* not needed.                                                              */
  is_conversion_on = LL_ADC_IsConversionOngoing(hadc->Instance);
  if (is_conversion_on != 0UL)
  {
    /* Stop ADC conversion */
    LL_ADC_StopConversion(hadc->Instance);
  }

  /* Return HAL status */
  return HAL_OK;
}


/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef *hadc)
{
  /* ADC enable  */
  if (LL_ADC_IsEnabled(hadc->Instance) == 0UL)
  {
    /* Enable the ADC peripheral */
    LL_ADC_Enable(hadc->Instance);
  }

  /* Return HAL status */
  return HAL_OK;
}


/**
  * @brief  Disable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped.
  * @param hadc ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef *hadc)
{
  /* Verification if ADC is not already disabled: */
  if ((LL_ADC_IsEnabled(hadc->Instance) != 0UL))
  {
    /* Disable the ADC peripheral */
    LL_ADC_Disable(hadc->Instance);
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  DMA transfer complete callback.
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Update state machine on conversion status if not in error state */
  if ((hadc->State & (HAL_ADC_STATE_ERROR_INTERNAL | HAL_ADC_STATE_ERROR_DMA)) == 0UL)
  {
    /* Set ADC state */
    SET_BIT(hadc->State, HAL_ADC_STATE_DS_EOC);

    /* Is it the end of the sequence ? */
    if ((hadc->Instance->IRQ_STATUS & ADC_IRQ_FLAG_EOS) != 0UL)
    {
      /* Is it in continuous mode */
      if (LL_ADC_IsContinuousModeEnabled(hadc->Instance) == 0UL)
      {
        /* It is not  bit is not set, no more conversions expected */
        CLEAR_BIT(hadc->State, HAL_ADC_STATE_DS_BUSY);
      }
    }
    else
    {
      /* DMA End of Transfer interrupt was triggered but conversions sequence
         is not over. If DMA_DS_ENA is set to 0, conversions are stopped. */
      if (LL_ADC_IsDMAModeDSEnabled(hadc->Instance) == 0UL)
      {
        /* DMA_DS_ENA bit is not set, conversions are stopped. */
        CLEAR_BIT(hadc->State, HAL_ADC_STATE_DS_BUSY);
      }
    }

    /* Conversion complete callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
    hadc->ConvCpltCallback(hadc);
#else
    HAL_ADC_ConvCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
  }
  else /* DMA and-or internal error occurred */
  {
    if ((hadc->State & HAL_ADC_STATE_ERROR_INTERNAL) != 0UL)
    {
      /* Call HAL ADC Error Callback function */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
      hadc->ErrorCallback(hadc);
#else
      HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
    }
    else
    {
      /* Call ADC DMA error callback */
      hadc->DMA_Handle->XferErrorCallback(hdma);
    }
  }
}

/**
  * @brief  DMA half transfer complete callback.
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Half conversion callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  hadc->ConvHalfCpltCallback(hadc);
#else
  HAL_ADC_ConvHalfCpltCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA error callback.
  * @param hdma pointer to DMA handle.
  * @retval None
  */
void ADC_DMAError(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_DMA);

  /* Set ADC error code to DMA error */
  SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_DMA);

  /* Error callback */
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  hadc->ErrorCallback(hadc);
#else
  HAL_ADC_ErrorCallback(hadc);
#endif /* USE_HAL_ADC_REGISTER_CALLBACKS */
}


/**
  * @}
  */

#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
