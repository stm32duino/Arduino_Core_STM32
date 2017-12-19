/**
  ******************************************************************************
  * @file    analog.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide analog services (ADC + PWM)
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "stm32_def.h"
#include "analog.h"
#include "timer.h"
#include "PinAF_STM32F1.h"
#include "dma.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

// Use smalled sample time decreases ADC conversion time
#if defined(ADC_SAMPLETIME_1CYCLE_5)
#define SAMPLINGTIME        ADC_SAMPLETIME_1CYCLE_5;
#elif defined(ADC_SAMPLETIME_2CYCLES_5)
#define SAMPLINGTIME        ADC_SAMPLETIME_2CYCLES_5;
#elif defined(ADC_SAMPLETIME_3CYCLES)
#define SAMPLINGTIME        ADC_SAMPLETIME_3CYCLES;
#elif defined(ADC_SAMPLETIME_4CYCLES)
#define SAMPLINGTIME        ADC_SAMPLETIME_4CYCLES;
#else
#error "ADC SAMPLINGTIME could not be defined"
#endif

// Use smaller clock prescaler to keep ADC conversion time as short as possible
#ifndef STM32F1xx
#ifdef ADC_CLOCK_SYNC_PCLK_DIV1
#define ADC_CLOCK_DIV       ADC_CLOCK_SYNC_PCLK_DIV1
#elif defined(ADC_CLOCK_ASYNC_DIV1)
#define ADC_CLOCK_DIV       ADC_CLOCK_ASYNC_DIV1
#elif defined(ADC_CLOCK_SYNC_PCLK_DIV2)
#define ADC_CLOCK_DIV       ADC_CLOCK_SYNC_PCLK_DIV2
#else
#error "ADC_CLOCK_DIV could not be defined"
#endif
#endif /* STM32F1xx */

#ifndef ADC_REGULAR_RANK_1
#define ADC_REGULAR_RANK_1  1
#endif
/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/* Adc context                                                                */
AdcContext context[ADC_NUM];

/* GPIO pin use for DAC                                                       */
static PinName g_current_pin = NC;


/**
  * @brief get indice for fulfill DMA table
  * @param instance : pointer to the instance
  * @retval         : indice for the corresponding peripheral
  */
uint8_t get_indice(void *instance)
{
  uint8_t indice = 255;
  
  #ifdef ADC1_BASE
  if (instance == ADC1)
  {
    indice = 0;
  }
  #endif
  #ifdef ADC2_BASE
  if (instance == ADC2)
  {
     indice = 1;
  }
  #endif
  #ifdef ADC3_BASE
  if (instance == ADC3)
  {
    indice = 2;
  }
  #endif
  #ifdef ADC4_BASE
  if (instance == ADC4)
  {
    indice = 3;
  }
  #endif
  return indice;
}

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */
static uint32_t get_adc_channel(PinName pin)
{
  uint32_t function = pinmap_function(pin, PinMap_ADC);
  uint32_t channel = 0;
  switch(STM_PIN_CHANNEL(function)) {
#ifdef ADC_CHANNEL_0
    case 0:
      channel = ADC_CHANNEL_0;
      break;
#endif
    case 1:
      channel = ADC_CHANNEL_1;
    break;
    case 2:
      channel = ADC_CHANNEL_2;
    break;
    case 3:
      channel = ADC_CHANNEL_3;
    break;
    case 4:
      channel = ADC_CHANNEL_4;
    break;
    case 5:
      channel = ADC_CHANNEL_5;
    break;
    case 6:
      channel = ADC_CHANNEL_6;
    break;
    case 7:
      channel = ADC_CHANNEL_7;
    break;
    case 8:
      channel = ADC_CHANNEL_8;
    break;
    case 9:
      channel = ADC_CHANNEL_9;
    break;
    case 10:
      channel = ADC_CHANNEL_10;
    break;
    case 11:
      channel = ADC_CHANNEL_11;
    break;
    case 12:
      channel = ADC_CHANNEL_12;
    break;
    case 13:
      channel = ADC_CHANNEL_13;
    break;
    case 14:
      channel = ADC_CHANNEL_14;
    break;
    case 15:
      channel = ADC_CHANNEL_15;
    break;
    case 16:
      channel = ADC_CHANNEL_TEMPSENSOR;
    break;
    case 17:
      channel = ADC_CHANNEL_VREFINT;
    break;
#ifdef ADC_CHANNEL_VBAT
	case 18:
      channel = ADC_CHANNEL_VBAT;
    break;
#endif
    default:
      channel = 0;
    break;
   }
  return channel;
}

static uint32_t get_pwm_channel(PinName pin)
{
  uint32_t function = pinmap_function(pin, PinMap_PWM);
  uint32_t channel = 0;
  switch(STM_PIN_CHANNEL(function)) {
    case 1:
      channel = TIM_CHANNEL_1;
      break;
    case 2:
      channel = TIM_CHANNEL_2;
      break;
    case 3:
      channel = TIM_CHANNEL_3;
      break;
    case 4:
      channel = TIM_CHANNEL_4;
      break;
    default:
      channel = 0;
    break;
   }
  return channel;
}

#ifdef HAL_DAC_MODULE_ENABLED
static uint32_t get_dac_channel(PinName pin)
{
  uint32_t function = pinmap_function(pin, PinMap_DAC);
  uint32_t channel = 0;
  switch(STM_PIN_CHANNEL(function)) {
#ifdef DAC_CHANNEL_0
    case 0:
      channel = DAC_CHANNEL_0;
      break;
#endif
    case 1:
      channel = DAC_CHANNEL_1;
    break;
#ifdef DAC_CHANNEL_2
    case 2:
      channel = DAC_CHANNEL_2;
    break;
#endif
    default:
      channel = 0;
    break;
   }
  return channel;
}

////////////////////////// DAC INTERFACE FUNCTIONS /////////////////////////////

/**
  * @brief DAC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hdac: DAC handle pointer
  * @retval None
  */
void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  GPIO_TypeDef *port;
  UNUSED(hdac);

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clock ****************************************/
  port = set_GPIO_Port_Clock(STM_PORT(g_current_pin));

  /* DAC Periph clock enable */
#ifdef __HAL_RCC_DAC1_CLK_ENABLE
  __HAL_RCC_DAC1_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_DAC_CLK_ENABLE
  __HAL_RCC_DAC_CLK_ENABLE();
#endif
  /*##-2- Configure peripheral GPIO ##########################################*/
  /* DAC Channel1 GPIO pin configuration */
  GPIO_InitStruct.Pin = STM_GPIO_PIN(g_current_pin);
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}


/**
  * @brief  This function will set the DAC to the required value
  * @param  port : the gpio port to use
  * @param  pin : the gpio pin to use
  * @param  value : the value to push on the adc output
  * @param  do_init : if set to 1 the initialization of the adc is done
  * @retval None
  */
void dac_write_value(PinName pin, uint32_t value, uint8_t do_init)
{
  DAC_HandleTypeDef DacHandle = {};
  DAC_ChannelConfTypeDef dacChannelConf = {};
  uint32_t dacChannel;

  DacHandle.Instance = pinmap_peripheral(pin, PinMap_DAC);
  if (DacHandle.Instance == NP) return;
  dacChannel = get_dac_channel(pin);
  if (!IS_DAC_CHANNEL(dacChannel)) return;
  if(do_init == 1) {

    if (HAL_DAC_DeInit(&DacHandle) != HAL_OK)
    {
      /* DeInitialization Error */
      return;
    }

    /*##-1- Configure the DAC peripheral #######################################*/
    g_current_pin = pin;
    if (HAL_DAC_Init(&DacHandle) != HAL_OK)
    {
      /* Initialization Error */
      return;
    }

	dacChannelConf.DAC_Trigger = DAC_TRIGGER_NONE;
	dacChannelConf.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;
    /*##-2- Configure DAC channel1 #############################################*/
    if (HAL_DAC_ConfigChannel(&DacHandle, &dacChannelConf, dacChannel) != HAL_OK)
    {
      /* Channel configuration Error */
      return;
    }
  }

  /*##-3- Set DAC Channel1 DHR register ######################################*/
  if (HAL_DAC_SetValue(&DacHandle, dacChannel, DAC_ALIGN_12B_R, value) != HAL_OK)
  {
    /* Setting value Error */
    return;
  }

  /*##-4- Enable DAC Channel1 ################################################*/
  HAL_DAC_Start(&DacHandle, dacChannel);
}

/**
  * @brief  DeInitialize the DAC MSP.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  UNUSED(hdac);
  /* DAC Periph clock disable */
#ifdef __HAL_RCC_DAC1_CLK_DISABLE
  __HAL_RCC_DAC1_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_DAC_CLK_DISABLE
  __HAL_RCC_DAC_CLK_DISABLE();
#endif
}

/**
  * @brief  This function will stop the DAC
  * @param  port : the gpio port to use
  * @param  pin : the gpio pin to use
  * @retval None
  */
void dac_stop(PinName pin)
{
  DAC_HandleTypeDef DacHandle;
  uint32_t dacChannel;

  DacHandle.Instance = pinmap_peripheral(pin, PinMap_DAC);
  if (DacHandle.Instance == NP) return;
  dacChannel = get_dac_channel(pin);
  if (!IS_DAC_CHANNEL(dacChannel)) return;

  HAL_DAC_Stop(&DacHandle, dacChannel);

  if (HAL_DAC_DeInit(&DacHandle) != HAL_OK)
  {
    /* DeInitialization Error */
    return;
  }
}
#endif //HAL_DAC_MODULE_ENABLED


////////////////////////// ADC INTERFACE FUNCTIONS /////////////////////////////

/**
  * @brief ADC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - Peripheral's DMA
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_TypeDef *port = NULL;
  uint8_t indice = 255;
  void *channel = NULL;
  IRQn_Type irqHandler;
  
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* ADC Periph clock enable */
  if(hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_CLK_ENABLE
	__HAL_RCC_ADC1_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_ENABLE
	__HAL_RCC_ADC12_CLK_ENABLE();
#endif
  }
#ifdef ADC2
  else if(hadc->Instance == ADC2) {
#ifdef __HAL_RCC_ADC2_CLK_ENABLE
	__HAL_RCC_ADC2_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_ENABLE
	__HAL_RCC_ADC12_CLK_ENABLE();
#endif
  }
#endif
#ifdef ADC3
  else if(hadc->Instance == ADC3) {
#ifdef __HAL_RCC_ADC3_CLK_ENABLE
    __HAL_RCC_ADC3_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC34_CLK_ENABLE
    __HAL_RCC_ADC34_CLK_ENABLE();
#endif
  }
#endif
#ifdef ADC4
  else if(hadc->Instance == ADC4) {
    __HAL_RCC_ADC34_CLK_ENABLE();
  }
#endif

#ifdef __HAL_RCC_ADC_CLK_ENABLE
  __HAL_RCC_ADC_CLK_ENABLE();
#endif

/* For STM32F1xx, ADC prescaler is confgured in SystemClock_Config (variant.cpp) */
#if defined(__HAL_RCC_ADC_CONFIG) && !defined(STM32F1xx)
  /* ADC Periph interface clock configuration */
  __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);
#endif

  /*##-2- Configure peripheral GPIO ##########################################*/
#ifdef ADC1_BASE
  if (hadc->Instance == ADC1)
  {
    port = set_GPIO_Port_Clock(STM_PORT(context[0].current_pin));
    GPIO_InitStruct.Pin = STM_GPIO_PIN(context[0].current_pin);
  }
#endif
  
#ifdef ADC2_BASE
  if (hadc->Instance == ADC2)
  {
    port = set_GPIO_Port_Clock(STM_PORT(context[1].current_pin));
    GPIO_InitStruct.Pin = STM_GPIO_PIN(context[1].current_pin);
  }
 #endif
  
#ifdef ADC3_BASE
  if (hadc->Instance == ADC3)
  {
    port = set_GPIO_Port_Clock(STM_PORT(context[2].current_pin));
    GPIO_InitStruct.Pin = STM_GPIO_PIN(context[2].current_pin);
  }
#endif
  
#ifdef ADC4_BASE
  if (hadc->Instance == ADC4)
  {
    port = set_GPIO_Port_Clock(STM_PORT(context[3].current_pin));
    GPIO_InitStruct.Pin = STM_GPIO_PIN(context[3].current_pin);
  }
#endif

  /* ADC Channel GPIO pin configuration */
#ifdef GPIO_MODE_ANALOG_ADC_CONTROL
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
#else
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
#endif
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
  
  indice = get_indice(hadc->Instance);
  
  if (context[indice].use_dma)
  {
    /*##-3- Ask DMA informations ###############################################*/
    if (dma_allocate(hadc->Instance, &channel, &irqHandler))
    {
      /*##-4- Configure the DMA ##################################################*/
          
      #if defined(STM32L0xx) || defined(STM32L4xx)
      context[indice].DmaHandle.Init.Request             = DMA_REQUEST_0;
      #endif

      #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
      #ifdef ADC1_BASE
      if (hadc->Instance == ADC1)
      {
        context[indice].DmaHandle.Init.Channel           = DMA_CHANNEL_0;
      }
      #endif
      #ifdef ADC2_BASE
      if (hadc->Instance == ADC2)
      {
        context[indice].DmaHandle.Init.Channel           = DMA_CHANNEL_1;
      }
      #endif
      #ifdef ADC3_BASE
      if (hadc->Instance == ADC3)
      {
        context[indice].DmaHandle.Init.Channel           = DMA_CHANNEL_2;
      }
      #endif
      #endif //STM32F2xx STM32F4xx STM32F7xx

      context[indice].DmaHandle.Instance                 = channel;
      context[indice].DmaHandle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
      context[indice].DmaHandle.Init.PeriphInc           = DMA_PINC_DISABLE;
      context[indice].DmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
      context[indice].DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      context[indice].DmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
      context[indice].DmaHandle.Init.Mode                = DMA_NORMAL;
      context[indice].DmaHandle.Init.Priority            = DMA_PRIORITY_MEDIUM;

      #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
      context[indice].DmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
      context[indice].DmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_HALFFULL;
      context[indice].DmaHandle.Init.MemBurst            = DMA_MBURST_SINGLE;
      context[indice].DmaHandle.Init.PeriphBurst         = DMA_PBURST_SINGLE;
      #endif //STM32F2xx STM32F4xx STM32F7xx
          
      /* Deinitialize  & Initialize the DMA for new transfer */
      HAL_DMA_DeInit(&context[indice].DmaHandle);
      HAL_DMA_Init(&context[indice].DmaHandle);

      /* Associate the DMA handle */
      __HAL_LINKDMA(hadc, DMA_Handle, context[indice].DmaHandle);

      /* NVIC */
      HAL_NVIC_SetPriority(irqHandler, 1, 0);
      HAL_NVIC_EnableIRQ(irqHandler);
    }
  }
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  uint8_t indice = 255;

#ifdef __HAL_RCC_ADC_FORCE_RESET
  __HAL_RCC_ADC_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC_RELEASE_RESET
  __HAL_RCC_ADC_RELEASE_RESET();
#endif

  if(hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_FORCE_RESET
	__HAL_RCC_ADC1_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_RELEASE_RESET
    __HAL_RCC_ADC1_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
	__HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_CLK_DISABLE
	__HAL_RCC_ADC1_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_DISABLE
	__HAL_RCC_ADC12_CLK_DISABLE();
#endif
  }
#ifdef ADC2
  else if(hadc->Instance == ADC2) {
#ifdef __HAL_RCC_ADC2_FORCE_RESET
	__HAL_RCC_ADC2_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_RELEASE_RESET
    __HAL_RCC_ADC2_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
	__HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
	__HAL_RCC_ADC2_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
	__HAL_RCC_ADC2_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC3
  else if(hadc->Instance == ADC3) {
#ifdef __HAL_RCC_ADC3_FORCE_RESET
	__HAL_RCC_ADC3_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_RELEASE_RESET
    __HAL_RCC_ADC3_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_FORCE_RESET
	__HAL_RCC_ADC34_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_CLK_DISABLE
    __HAL_RCC_ADC3_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC4
  else if(hadc->Instance == ADC4) {
	__HAL_RCC_ADC34_FORCE_RESET();
    __HAL_RCC_ADC34_RELEASE_RESET();
    __HAL_RCC_ADC34_CLK_DISABLE();
  }
#endif
#ifdef __HAL_RCC_ADC_CLK_DISABLE
  __HAL_RCC_ADC_CLK_DISABLE();
#endif

  indice = get_indice(hadc->Instance);

  if (context[indice].use_dma)
  {
    dma_free(hadc->Instance);
    HAL_DMA_DeInit(hadc->DMA_Handle);
  }
}

/**
  * @brief  This function will set the ADC to the required value
  * @param  pin : the pin to use
  * @retval the value of the adc
  */
uint16_t adc_read_value(PinName pin)
{
  ADC_ChannelConfTypeDef  AdcChannelConf = {};
  __IO uint16_t uhADCxConvertedValue = 0;
  void *peripheral;
  uint8_t indice = 255;

  peripheral                         = pinmap_peripheral(pin, PinMap_ADC);
  indice                             = get_indice(peripheral);
  context[indice].current_pin        = pin;                                           /* Needed for HAL_ADC_MspInit */
  context[indice].AdcHandle.Instance = peripheral;


  if (context[indice].AdcHandle.Instance == NP) return 0;

#ifndef STM32F1xx
  context[indice].AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_DIV;                /* Asynchronous clock mode, input ADC clock divided */
  context[indice].AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;            /* 12-bit resolution for converted data */
  context[indice].AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;           /* EOC flag picked-up to indicate conversion end */
  context[indice].AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because software trigger chosen */
  context[indice].AdcHandle.Init.DMAContinuousRequests = DISABLE;                       /* DMA one-shot mode selected (not applied to this example) */
#endif
  context[indice].AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;           /* Right-alignment for converted data */
  context[indice].AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  context[indice].AdcHandle.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  context[indice].AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  context[indice].AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
  context[indice].AdcHandle.State = HAL_ADC_STATE_RESET;
#if defined (STM32F0xx) || defined (STM32L0xx)
  context[indice].AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
  context[indice].AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;                       /* ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered */
  context[indice].AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      /* DR register is overwritten with the last conversion result in case of overrun */
#ifdef STM32F0xx
  context[indice].AdcHandle.Init.SamplingTimeCommon    = SAMPLINGTIME;
#else // STM32L0
  //LowPowerFrequencyMode to enable if clk freq < 2.8Mhz
  context[indice].AdcHandle.Init.SamplingTime          = SAMPLINGTIME;
#endif
#else
#ifdef STM32F3xx
  context[indice].AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
#endif
  context[indice].AdcHandle.Init.NbrOfConversion       = 1;                             /* Specifies the number of ranks that will be converted within the regular group sequencer. */
  context[indice].AdcHandle.Init.NbrOfDiscConversion   = 0;                             /* Parameter discarded because sequencer is disabled */
#endif

  context[indice].use_dma = false;

  if (HAL_ADC_Init(&context[indice].AdcHandle) != HAL_OK) {
    return 0;
  }

  AdcChannelConf.Channel      = get_adc_channel(pin);             /* Specifies the channel to configure into ADC */
#ifdef STM32L4xx
  if (!IS_ADC_CHANNEL(&context[indice].AdcHandle, AdcChannelConf.Channel)) return 0;
#else
  if (!IS_ADC_CHANNEL(AdcChannelConf.Channel)) return 0;
#endif
  AdcChannelConf.Rank         = ADC_REGULAR_RANK_1;               /* Specifies the rank in the regular group sequencer */
#ifndef STM32L0xx
  AdcChannelConf.SamplingTime = SAMPLINGTIME;                     /* Sampling time value to be set for the selected channel */
#endif
  /*##-2- Configure ADC regular channel ######################################*/
  if (HAL_ADC_ConfigChannel(&context[indice].AdcHandle, &AdcChannelConf) != HAL_OK)
  {
    /* Channel Configuration Error */
    return 0;
  }

#if defined (STM32F0xx) || defined (STM32F1xx) || defined (STM32F3xx) || defined (STM32L0xx) || defined (STM32L4xx)
  /*##-2.1- Calibrate ADC then Start the conversion process ####################*/
#if defined (STM32F0xx) || defined (STM32F1xx)
  if (HAL_ADCEx_Calibration_Start(&context[indice].AdcHandle) !=  HAL_OK)
#else
  if (HAL_ADCEx_Calibration_Start(&context[indice].AdcHandle, ADC_SINGLE_ENDED) !=  HAL_OK)
#endif
  {
    /* ADC Calibration Error */
    return 0;
  }
#endif

  /*##-3- Start the conversion process ####################*/
  if (HAL_ADC_Start(&context[indice].AdcHandle) != HAL_OK)
  {
    /* Start Conversation Error */
    return 0;
  }

  /*##-4- Wait for the end of conversion #####################################*/
  /*  For simplicity reasons, this example is just waiting till the end of the
      conversion, but application may perform other tasks while conversion
      operation is ongoing. */
  if (HAL_ADC_PollForConversion(&context[indice].AdcHandle, 10) != HAL_OK)
  {
    /* End Of Conversion flag not set on time */
    return 0;
  }

  /* Check if the continous conversion of regular channel is finished */
  if ((HAL_ADC_GetState(&context[indice].AdcHandle) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
  {
    /*##-5- Get the converted value of regular channel  ########################*/
    uhADCxConvertedValue = HAL_ADC_GetValue(&context[indice].AdcHandle);
  }

  if (HAL_ADC_Stop(&context[indice].AdcHandle) != HAL_OK)
  {
    /* Stop Conversation Error */
    return 0;
  }

  if(HAL_ADC_DeInit(&context[indice].AdcHandle) != HAL_OK) {
    return 0;
  }

  return uhADCxConvertedValue;
}

/**
  * @brief  This function will use DMA for ADC conversion
  * @param  pin               : the pin to use
  * @param  pData             : pointer to buffer where write data
  * @param  lData             : Number of sample
  * @param  callback          : Callback function to execute when conversion is done
  * @param  functionParameter : Callback function parameter
  * @retval 1 is success, 0 if fail.
  */
uint16_t adc_read_value_dma(PinName pin, uint32_t *pData, uint32_t lData,
                            void (*callback)(void *user_data), void *functionParameter)
{
  void *peripheral;
  ADC_ChannelConfTypeDef        sConfig;
  uint8_t indice = 255;
  
  /* ### - 1 - Initialize ADC peripheral #################################### */
  peripheral                         = pinmap_peripheral(pin, PinMap_ADC);
  indice                             = get_indice(peripheral);
  context[indice].current_pin        = pin;                                             /* Needed for HAL_ADC_MspInit     */
  context[indice].cb                 = callback;                                        /* Register the callback function */
  context[indice].user_data          = functionParameter;
  context[indice].AdcHandle.Instance = peripheral;
  
  if (context[indice].AdcHandle.Instance == NP) return 0;

  if (HAL_ADC_DeInit(&context[indice].AdcHandle) != HAL_OK)
  {
    return 0;
  }

#ifndef STM32F1xx
  context[indice].AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_DIV;                 /* Synchronous clock mode, input ADC clock divided by 1*/
  context[indice].AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;            /* 12-bit resolution for converted data */
  context[indice].AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;           /* EOC flag picked-up to indicate conversion end */
  context[indice].AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because software trigger chosen */
  context[indice].AdcHandle.Init.DMAContinuousRequests = DISABLE;                        /* ADC DMA to match with DMA normal mode */
#endif
  context[indice].AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;           /* Right-alignment for converted data */
  context[indice].AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  context[indice].AdcHandle.Init.ContinuousConvMode    = ENABLE;                        /* Continuous mode enabled (automatic conversion restart after each conversion) */
  context[indice].AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  context[indice].AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
  context[indice].AdcHandle.State = HAL_ADC_STATE_RESET;
#if defined (STM32F0xx) ||defined (STM32L0xx)
  context[indice].AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
  context[indice].AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;
  context[indice].AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      /* DR register is overwritten with the last conversion result in case of overrun */
#ifdef STM32F0xx
  context[indice].AdcHandle.Init.SamplingTimeCommon    = SAMPLINGTIME;
#else // STM32L0
  //LowPowerFrequencyMode to enable if clk freq < 2.8Mhz
  context[indice].AdcHandle.Init.SamplingTime          = SAMPLINGTIME;
#endif
#else
#ifdef STM32F3xx
  context[indice].AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
  context[indice].AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      /* DR register is overwritten with the last conversion result in case of overrun */
#endif
  context[indice].AdcHandle.Init.NbrOfConversion       = 1;                             /* Parameter discarded because sequencer is disabled */
  context[indice].AdcHandle.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
#endif

  context[indice].use_dma = true;
  
  /* Initialize ADC peripheral according to the passed parameters */
  if (HAL_ADC_Init(&context[indice].AdcHandle) != HAL_OK)
  {
    return 0;
  }

#if defined (STM32F0xx) || defined (STM32F1xx) || defined (STM32F3xx) || defined (STM32L0xx) || defined (STM32L4xx)
  /* ### - 2 - Start calibration ############################################ */
#if defined (STM32F0xx) || defined (STM32F1xx)
  if (HAL_ADCEx_Calibration_Start(&context[indice].AdcHandle) !=  HAL_OK)
#else //defined (STM32F0xx) || defined (STM32F1xx)
  if (HAL_ADCEx_Calibration_Start(&context[indice].AdcHandle, ADC_SINGLE_ENDED) !=  HAL_OK)
#endif
  {
    return 0;
  }
#endif //defined (STM32F0xx) || defined (STM32F1xx) || defined (STM32F3xx) || defined (STM32L0xx) || defined (STM32L4xx)

  /* ### - 3 - Channel configuration ######################################## */
  sConfig.Channel      = get_adc_channel(pin);        /* Sampled channel number */
#ifdef STM32L4xx
  if (!IS_ADC_CHANNEL(&context[indice].AdcHandle, sConfig.Channel)) return 0;
#else //STM32L4xx
  if (!IS_ADC_CHANNEL(sConfig.Channel)) return 0;
#endif
  sConfig.Rank         = ADC_REGULAR_RANK_1;          /* Rank of sampled channel number ADCx_CHANNEL */
#ifndef STM32L0xx
  sConfig.SamplingTime = SAMPLINGTIME;                /* Sampling time (number of clock cycles unit) */
#endif //STM32L0xx

  if (HAL_ADC_ConfigChannel(&context[indice].AdcHandle, &sConfig) != HAL_OK)
  {
    return 0;
  }
  
  /* ### - 4 - Start conversion in DMA mode ################################# */
  if (HAL_ADC_Start_DMA(&context[indice].AdcHandle, (uint32_t*)pData, lData) != HAL_OK)
  {
    return 0;
  }
  return 1;
}


////////////////////////// PWM INTERFACE FUNCTIONS /////////////////////////////


/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  GPIO_TypeDef *port;
  uint32_t function = pinmap_function(g_current_pin, PinMap_PWM);
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  timer_enable_clock(htim);

  /* Enable GPIO Channels Clock */
  /* Enable GPIO clock ****************************************/
  port = set_GPIO_Port_Clock(STM_PORT(g_current_pin));

  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
#ifdef STM32F1xx
  pin_SetF1AFPin(STM_PIN_AFNUM(function));
#else
  GPIO_InitStruct.Alternate = STM_PIN_AFNUM(function);
#endif /* STM32F1xx */
  GPIO_InitStruct.Pin = STM_GPIO_PIN(g_current_pin);

  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

/**
  * @brief  DeInitializes TIM PWM MSP.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
  timer_disable_clock(htim);
}

/**
  * @brief  This function will set the PWM to the required value
  * @param  port : the gpio port to use
  * @param  pin : the gpio pin to use
  * @param  clock_freq : frequency of the tim clock
  * @param  period : period of the tim counter
  * @param  value : the value to push on the PWM output
  * @param  do_init : if set to 1 the initialization of the PWM is done
  * @retval None
  */
void pwm_start(PinName pin, uint32_t clock_freq,
                uint32_t period, uint32_t value, uint8_t do_init)
{
  TIM_HandleTypeDef timHandle = {};
  TIM_OC_InitTypeDef timConfig = {};
  uint32_t timChannel;

  /* Compute the prescaler value to have TIM counter clock equal to clock_freq Hz */
  timHandle.Instance               = pinmap_peripheral(pin, PinMap_PWM);
  if (timHandle.Instance == NP) return;
  timHandle.Init.Prescaler         = (uint32_t)(getTimerClkFreq(timHandle.Instance) / clock_freq) - 1;
  timHandle.Init.Period            = period -1;
  timHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  timHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
#if !defined(STM32L0xx) && !defined(STM32L1xx)
  timHandle.Init.RepetitionCounter = 0;
#endif
  timHandle.State= HAL_TIM_STATE_RESET;
  // TBC: is timHandle.State field should be saved ?

  if (do_init == 1) {
    g_current_pin = pin;
    if (HAL_TIM_PWM_Init(&timHandle) != HAL_OK) {
      return;
    }
  }
  timChannel = get_pwm_channel(pin);
  if (!IS_TIM_CHANNELS(timChannel)) return;
  //HAL_TIM_PWM_Stop(&timHandle, timChannel);

  /*##-2- Configure the PWM channels #########################################*/
  /* Common configuration for all channels */
  timConfig.OCMode       = TIM_OCMODE_PWM1;
  timConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  timConfig.OCFastMode   = TIM_OCFAST_DISABLE;
#if !defined(STM32L0xx) && !defined(STM32L1xx)
  timConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  timConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  timConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
#endif
  timConfig.Pulse = value;

  if (HAL_TIM_PWM_ConfigChannel(&timHandle, &timConfig, timChannel) != HAL_OK)
  {
    /*##-2- Configure the PWM channels #########################################*/
    return;
  }

#if !defined(STM32L0xx) && !defined(STM32L1xx)
  if(STM_PIN_INVERTED(pinmap_function(pin, PinMap_PWM))) {
    HAL_TIMEx_PWMN_Start(&timHandle, timChannel);
  } else
#endif
  {
    HAL_TIM_PWM_Start(&timHandle, timChannel);
  }
}

/**
  * @brief  This function will disable the PWM
  * @param  port : the gpio port to use
  * @param  pin : the gpio pin to use
  * @retval None
  */
void pwm_stop(PinName pin)
{
  TIM_HandleTypeDef timHandle;
  uint32_t timChannel;

  timHandle.Instance = pinmap_peripheral(pin, PinMap_PWM);
  if (timHandle.Instance == NP) return;
  timChannel = get_pwm_channel(pin);
  if (!IS_TIM_CHANNELS(timChannel)) return;

#if !defined(STM32L0xx) && !defined(STM32L1xx)
  if (STM_PIN_INVERTED(pinmap_function(pin, PinMap_PWM))) {
    HAL_TIMEx_PWMN_Stop(&timHandle, timChannel);
  } else
#endif
  {
    HAL_TIM_PWM_Stop(&timHandle, timChannel);
  }

  HAL_TIM_PWM_DeInit(&timHandle);
}


/**
  * @brief  Conversion DMA transfer callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
  /* Report to main program that ADC sequencer has reached its end */
  AdcContext *contextls = (AdcContext*) AdcHandle;
  if (contextls->cb != NULL)
  {
    contextls->cb(contextls->user_data);
  }
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

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
