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

#include "stm32_def.h"

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef DMA2_BASE
#define DMA_NUMBER  (2)
#else
#define DMA_NUMBER  (1)
#endif

#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#define CHANNEL_NUMBER  (8)
#else
// +1 to compensate missing 0 index
#if defined(DMA1_Channel7_BASE)
#define CHANNEL_NUMBER  (7 + 1)
#elif defined(DMA1_Channel6_BASE)
#define CHANNEL_NUMBER  (6 + 1)
#else
#define CHANNEL_NUMBER  (5 + 1)
#endif
#endif

#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#define DMA_INSTANCE_OFFSET(n) ((n) == 0 ? 0 : (DMA1_Stream1_BASE - DMA1_Stream0_BASE))
#define DMA_CHANNEL(n)  ((n) == 0 ? DMA_CHANNEL_0 : (DMA_CHANNEL_0 + (0x02000000U * (n))))
#else
#define DMA_INSTANCE_OFFSET(n) ((n) == 1 ? 0 : (DMA1_Channel2_BASE - DMA1_Channel1_BASE))
#if defined(STM32L0xx) || defined(STM32L4xx)
#define DMA_CHANNEL(n)  ((n) == 0 ? DMA_REQUEST_0 : (DMA_REQUEST_0 + (0x01 * (n))))
#endif
#endif


#if defined(STM32F0xx) || defined(STM32L0xx)
#define DMA1_Channel2_IRQHandler DMA1_Channel2_3_IRQHandler
#define DMA1_Channel4_IRQHandler DMA1_Channel4_5_6_7_IRQHandler
#endif //STM32F0xx || STM32L0xx


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

typedef struct {
    void* peripheral;
    int8_t dmaNumber;
    int8_t channelNumber;
    int8_t requestNumber;
    IRQn_Type irq;
} DMAMap_t;

void DMA_init(void *periph, void *instance, DMA_HandleTypeDef **handle, const DMAMap_t *map);
void DMA_deinit(void *instance, const DMAMap_t *map);

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H */

/************************ (C) COPYRIGHT Wi6labs ***************END OF FILE****/
