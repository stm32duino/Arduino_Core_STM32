/**
  ******************************************************************************
  * @file    dma.c
  * @author  MCD Application Team, Wi6labs
  * @brief   dma service.
  ******************************************************************************

Copyright (c) <2017>, <Wi6labs>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the wi6labs nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL WI6LABS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  ******************************************************************************
  */

#include "stm32_def.h"
#include "dma.h"
#include "analog.h"

const DmaMap DmaMap_DMA[] = {
  #if defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32F3xx) || \
      defined(STM32L0xx) || defined(STM32L1xx) || defined(STM32L4xx)
  {ADC1, 1, DMA1_Channel1, DMA1_Channel1_IRQn        , 1},
  #if defined(STM32F0xx)
  {ADC1, 1, DMA1_Channel2, DMA1_Ch2_3_DMA2_Ch1_2_IRQn, 2},
  #if defined(STM32F091xC) || defined(STM32F098xx)
  {ADC1, 2, DMA2_Channel5, DMA1_Ch4_7_DMA2_Ch3_5_IRQn, 5},
  #endif
  #endif
  #if defined(STM32F303xC) || defined(STM32F303xE) || defined(STM32F358xx) || \
      defined(STM32F398xx)
  {ADC2, 2, DMA2_Channel1, DMA2_Channel1_IRQn, 1},
  {ADC2, 2, DMA2_Channel3, DMA2_Channel3_IRQn, 3},
  {ADC3, 2, DMA2_Channel5, DMA2_Channel5_IRQn, 5},
  {ADC4, 2, DMA2_Channel2, DMA2_Channel2_IRQn, 2},
  {ADC4, 2, DMA2_Channel4, DMA2_Channel4_IRQn, 4},
  #endif
  #if defined(STM32F328xx) || defined(STM32F303x8) || defined(STM32F334x8)
  {ADC2, 1, DMA1_Channel2, DMA1_Channel2_IRQn, 2},
  {ADC2, 1, DMA1_Channel4, DMA1_Channel4_IRQn, 4},
  #endif
  #if defined(STM32L0xx)
  {ADC1, 1, DMA1_Channel2, DMA1_Channel2_3_IRQn, 2},
  #endif
  #if defined(STM32L4xx)
  {ADC1, 2, DMA2_Channel3, DMA2_Channel3_IRQn, 3},
  #if defined(STM32L476xx) || defined(STM32L476xx)
  {ADC2, 1, DMA1_Channel2, DMA1_Channel2_IRQn, 2},
  {ADC3, 1, DMA1_Channel3, DMA1_Channel3_IRQn, 3},
  {ADC2, 2, DMA2_Channel4, DMA2_Channel4_IRQn, 4},
  {ADC3, 2, DMA2_Channel5, DMA2_Channel5_IRQn, 5},
  #endif
  #endif
  #endif
  #if defined(STM32F2xx) || defined(STM32F4xx)
  {ADC1, 2, DMA2_Stream0, DMA2_Stream0_IRQn, 0},
  {ADC1, 2, DMA2_Stream4, DMA2_Stream4_IRQn, 4},
  #if defined(STM32F2xx) || defined(STM32F429xx) || defined(STM32F407xx)
  {ADC2, 2, DMA2_Stream2, DMA2_Stream2_IRQn, 2},
  {ADC2, 2, DMA2_Stream3, DMA2_Stream3_IRQn, 3},
  {ADC3, 2, DMA2_Stream0, DMA2_Stream0_IRQn, 0},
  {ADC3, 2, DMA2_Stream1, DMA2_Stream1_IRQn, 1},
  {NP,   0, NP,            NP,               0}
  #endif
  #endif
};

#ifdef __cplusplus
 extern "C" {
#endif

extern AdcContext context[ADC_NUM];
static bool dmaTab[DMA_NUMBER][CHANNEL_NUMBER];

/**
  * @brief  This function will find the DMA number associate to the peripheral 
  * @param  peripheral : pointer to the peripheral
  * @param  dma        : DMA table into look to it
  * @retval the DMA number
  */
uint8_t dma_find_dma(void* peripheral, const DmaMap* dma) {
  while (dma->peripheral != NP) {
    if (dma->peripheral == peripheral)
      return dma->dmaNumber;
    dma++;
  }
  return NP;
}

/**
  * @brief  This function will find the DMA IrqHandler associate to the peripheral 
  * @param  peripheral : pointer to the peripheral
  * @param  dma        : DMA table into look to it
  * @retval the DMA IrqHandler
  */
IRQn_Type dma_find_dmaIrqHandler(void* peripheral, const DmaMap* dma) {
  while (dma->peripheral != NP) {
    if (dma->peripheral == peripheral)
      return dma->irqHandler;
    dma++;
  }
  return NP;
}

/**
  * @brief  This function will find the DMA channel number associate to the peripheral 
  * @param  peripheral : pointer to the peripheral
  * @param  dma        : DMA table into look to it
  * @retval the DMA channel number
  */
int8_t dma_find_dmaChannelNumber(void* peripheral, const DmaMap* dma) {
  while (dma->peripheral != NP) {
    if (dma->peripheral == peripheral)
      return dma->channelNumber;
    dma++;
  }
  return NP;
}

/**
  * @brief  This function will find the DMA channel associate to the peripheral 
  * @param  peripheral : pointer to the peripheral
  * @param  dma        : DMA table into look to it
  * @retval the DMA channel
  */
void* dma_find_dmaChannel(void* peripheral, const DmaMap* dma) {
  while (dma->peripheral != NP) {
    if (dma->peripheral == peripheral)
      return dma->channel;
    dma++;
  }
  return NP;
}

/**
  * @brief  For a particular instance give the associate channel and irqHandler
  * @param  instance   : pointer to the peripheral to link to DMA
  * @param  channel    : DMA channel associate with the peripheral
  * @param  irqHandler : DMA IrqHandler associate with the peripheral
  * @retval true is dma can be allocate, false otherwise
  */
bool dma_allocate(void *instance, void **channel, IRQn_Type *irqHandler)
{
  int8_t    channelNumber = 0;
  int8_t    dmaNumber     = 0;
  
  /* Get channel                                                              */
  *channel = dma_find_dmaChannel(instance, DmaMap_DMA);
  if (*channel == NP)
  {
    return false;
  }
  
  /* Get channel number                                                       */
  channelNumber = dma_find_dmaChannelNumber(instance, DmaMap_DMA);
  if (channelNumber == NP)
  {
    return false;
  }
  
  /* Get dma                                                                  */
  dmaNumber = dma_find_dma(instance, DmaMap_DMA);
  if (dmaNumber == NP)
  {
    return false;
  }
  
  /* Set clock as active                                                      */
  dmaTab[dmaNumber-1][channelNumber] = true;
  
  /* NVIC configuration for DMA Input data interrupt                          */
  *irqHandler = dma_find_dmaIrqHandler(instance, DmaMap_DMA);
  
#ifdef __HAL_RCC_DMA1_CLK_ENABLE
  __HAL_RCC_DMA1_CLK_ENABLE();
#endif

#ifdef __HAL_RCC_DMA2_CLK_ENABLE
  __HAL_RCC_DMA2_CLK_ENABLE();
#endif

return true;
}

/**
  * @brief  This function will deinit the dma irqHandler and clock corresponding 
  *         to the wanted peripheral
  * @param  instance      : pointer to the peripheral
  * @retval none
  */
void dma_free(void *instance)
{
  IRQn_Type irqHandler    = 0;
  int8_t    channelNumber = 0;
  int8_t    dmaNumber     = 0;
  irqHandler    = dma_find_dmaIrqHandler(instance, DmaMap_DMA);
  channelNumber = dma_find_dmaChannelNumber(instance, DmaMap_DMA);
  dmaNumber     = dma_find_dma(instance, DmaMap_DMA);

  HAL_NVIC_DisableIRQ(irqHandler);
  
  // Disable the clock only if not another channel of the dma is use
  dmaTab[dmaNumber-1][channelNumber] = false;
  
  for (int i=0; i<CHANNEL_NUMBER; i++)
  {
    if (dmaTab[dmaNumber][i] == true)
    {
      break;
    }
    if (i == CHANNEL_NUMBER-1)
    {
      // All dma channel are inactive
      if (dmaNumber == 1)
      {
      #ifdef __HAL_RCC_DMA1_CLK_ENABLE
        __HAL_RCC_DMA1_CLK_DISABLE();
      #endif
      }
      else if (dmaNumber == 2)
      {
        #ifdef __HAL_RCC_DMA2_CLK_ENABLE
        __HAL_RCC_DMA2_CLK_DISABLE();
        #endif
      }
    }
  }
}

/**
  * @brief  DMA IRQ Handle 
  * @param  None
  * @retval None
  */

#ifdef ADC1_BASE
void DMA2_Stream0_IRQHandler(void)
{
  #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
  if (context[0].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[0].AdcHandle.DMA_Handle); // ADC1
  }
  else if (context[2].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[2].AdcHandle.DMA_Handle); // ADC3
  }
  #else
  if (context[0].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[0].AdcHandle.DMA_Handle);
  }
  #endif
}

#if defined(STM32L4xx) || defined(STM32L0xx) || defined(STM32F0xx) \
 || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream4_IRQHandler(void)
{
  if (context[0].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[0].AdcHandle.DMA_Handle);
  }
}
#endif

#if defined(STM32L011xx) || defined(STM32L021xx) || defined(STM32L031xx) || \
    defined(STM32L041xx) || defined(STM32L051xx) || defined(STM32L061xx) || \
    defined(STM32L071xx) || defined(STM32L081xx) || defined(STM32F091xC) || \
    defined(STM32F098xx)
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  if (context[0].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[0].AdcHandle.DMA_Handle);
  }
}
#endif
#endif

#ifdef ADC2_BASE
void DMA2_Stream2_IRQHandler(void)
{
  if (context[1].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[1].AdcHandle.DMA_Handle);
  }
}

void DMA2_Stream3_IRQHandler(void)
{
  if (context[1].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[1].AdcHandle.DMA_Handle);
  }
}
#endif

#ifdef ADC3_BASE
void DMA2_Stream1_IRQHandler(void)
{
  if (context[2].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[2].AdcHandle.DMA_Handle);
  }
}

#if defined(STM32L4xx)
void DMA2_Channel5_IRQHandler(void)
{
  if (context[2].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[2].AdcHandle.DMA_Handle);
  }
}
#endif
#endif

#ifdef ADC4_BASE
void DMA2_Channel2_IRQHandler(void)
{
  if (context[3].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[3].AdcHandle.DMA_Handle);
  }
}

void DMA2_Channel4_IRQHandler(void)
{
  if (context[3].AdcHandle.DMA_Handle != NULL)
  {
    HAL_DMA_IRQHandler(context[3].AdcHandle.DMA_Handle);
  }
}
#endif


#ifdef __cplusplus
}
#endif


