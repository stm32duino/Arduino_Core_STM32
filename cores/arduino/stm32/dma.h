/**
  ******************************************************************************
  * @file    dma.h
  * @author  MCD Application Team, Wi6labs
  * @brief   header file for dma service.
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA_H
#define __DMA_H

#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define DMA_NUMBER         2
#define CHANNEL_NUMBER     8


#ifdef STM32L0xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#define DMA2_Stream4_IRQHandler DMA1_Channel2_3_IRQHandler
#endif
#endif //STM32L0xx

#ifdef STM32L1xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#endif
#endif //STM32L1xx

#ifdef STM32L4xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#define DMA2_Stream4_IRQHandler DMA2_Channel3_IRQHandler
#endif
#ifdef ADC2_BASE
#define DMA2_Stream2_IRQHandler DMA1_Channel2_IRQHandler
#define DMA2_Stream3_IRQHandler DMA2_Channel4_IRQHandler
#endif
#ifdef ADC3_BASE
#define DMA2_Stream1_IRQHandler DMA1_Channel3_IRQHandler
#endif
#endif //STM32L4xx

#ifdef STM32F0xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#define DMA2_Stream4_IRQHandler DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler
#if defined(STM32F091xC) || defined(STM32F098xx)
#define DMA1_Channel4_5_6_7_IRQHandler DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler
#endif
#endif
#endif //STM32F0xx

#ifdef STM32F1xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#endif
#ifdef ADC3_BASE
#define DMA2_Stream1_IRQHandler DMA2_Channel4_5_IRQHandler 
#endif
#endif //STM32F1xx

#ifdef STM32F3xx
#ifdef ADC1_BASE
#define DMA2_Stream0_IRQHandler DMA1_Channel1_IRQHandler
#endif
#ifdef ADC2_BASE
#if defined(STM32F303xC) || defined(STM32F303xE) || defined(STM32F358xx) || \
    defined(STM32F398xx)
#define DMA2_Stream2_IRQHandler DMA2_Channel1_IRQHandler
#define DMA2_Stream3_IRQHandler DMA2_Channel3_IRQHandler
#endif
#if defined(STM32F328xx) || defined(STM32F303x8) || defined(STM32F334x8)
#define DMA2_Stream2_IRQHandler DMA1_Channel2_IRQHandler
#define DMA2_Stream3_IRQHandler DMA1_Channel4_IRQHandler
#endif
#endif
#ifdef ADC3_BASE
#define DMA2_Stream1_IRQHandler DMA2_Channel5_IRQHandler
#endif
#endif //STM32F3xx


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

typedef struct {
    void* peripheral;
    int8_t dmaNumber;
    void* channel;
    IRQn_Type irqHandler;
    int8_t channelNumber;
} DmaMap;

bool dma_allocate(void *instance, void **channel, IRQn_Type *irqHandler);
void dma_free(void *instance);

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H */

/************************ (C) COPYRIGHT Wi6labs ***************END OF FILE****/



