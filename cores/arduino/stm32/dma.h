/**
  ******************************************************************************
  * @file    dma.h
  * @author  xC0000005
  * @version V1.0.0
  * @date    12-July-2019
  * @brief   provide dma callbacks for dma
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA_H
#define __DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32_def.h>

/**
  * @brief  This function will get the interrupt number for a DMA
  * @param  dma_handle : dma channel or strea
  * @retval None
  */
IRQn_Type get_dma_interrupt(
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
  DMA_Stream_TypeDef
#else
  DMA_Channel_TypeDef
#endif
  *instance);

/**
  * @brief  This function will store the DMA handle in the appropriate slot
  * @param  dma_handle : dma handle
  * @retval None
  */
void prepare_dma(DMA_HandleTypeDef *dma_handle);

/**
  * @brief  This function will remove the DMA handle from the appropriate slot
  * @param  dma_handle : dma handle
  * @retval None
  */
void end_dma(DMA_HandleTypeDef *dma_handle);

#ifdef __cplusplus
}
#endif

#endif
