/**
  ******************************************************************************
  * @file    dma.c
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
#include <stddef.h>
#include "dma.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined(HAL_DMA_MODULE_ENABLED)

#define NC -1

typedef enum
{
#ifdef DMA1_Channel1
    DMA1_CHANNEL1_INDEX,
#endif
#ifdef DMA1_Channel2
    DMA1_CHANNEL2_INDEX,
#endif
#ifdef DMA1_Channel3
    DMA1_CHANNEL3_INDEX,
#endif
#ifdef DMA1_Channel4
    DMA1_CHANNEL4_INDEX,
#endif
#ifdef DMA1_Channel5
    DMA1_CHANNEL5_INDEX,
#endif
#ifdef DMA1_Channel6
    DMA1_CHANNEL6_INDEX,
#endif
#ifdef DMA1_Channel7
    DMA1_CHANNEL7_INDEX,
#endif
#ifdef DMA2_Channel1
    DMA2_CHANNEL1_INDEX,
#endif
#ifdef DMA2_Channel2
    DMA2_CHANNEL2_INDEX,
#endif
#ifdef DMA2_Channel3
    DMA2_CHANNEL3_INDEX,
#endif
#ifdef DMA2_Channel4
    DMA2_CHANNEL4_INDEX,
#endif
#ifdef DMA2_Channel5
    DMA2_CHANNEL5_INDEX,
#endif
#ifdef DMA2_Channel6
    DMA2_CHANNEL6_INDEX,
#endif
#ifdef DMA2_Channel7
    DMA2_CHANNEL7_INDEX,
#endif
#ifdef DMA2_Channel8
    DMA2_CHANNEL8_INDEX,
#endif
    DMA_CHANNEL_NUM
} dma_index_t;

static DMA_HandleTypeDef *dma_handles[DMA_CHANNEL_NUM] = {NULL};

/**
  * @brief  This function determines the dma index
  * @param  instance : dma instance
  * @retval None
  */
static dma_index_t get_dma_index(DMA_Channel_TypeDef *instance) {
    switch ((uint32_t)instance) {
#ifdef DMA1_Channel1
    case (uint32_t)DMA1_Channel1:
        return DMA1_CHANNEL1_INDEX;
#endif
#ifdef DMA1_Channel2
    case (uint32_t)DMA1_Channel2:
        return DMA1_CHANNEL2_INDEX;
#endif
#ifdef DMA1_Channel3
    case (uint32_t)DMA1_Channel3:
        return DMA1_CHANNEL3_INDEX;
#endif
#ifdef DMA1_Channel4
    case (uint32_t)DMA1_Channel4:
        return DMA1_CHANNEL4_INDEX;
#endif
#ifdef DMA1_Channel5
    case (uint32_t)DMA1_Channel5:
        return DMA1_CHANNEL5_INDEX;
#endif
#ifdef DMA1_Channel6
    case (uint32_t)DMA1_Channel6:
        return DMA1_CHANNEL6_INDEX;
#endif
#ifdef DMA1_Channel7
    case (uint32_t)DMA1_Channel7:
        return DMA1_CHANNEL7_INDEX;
#endif
#ifdef DMA2_Channel1
    case (uint32_t)DMA2_Channel1:
        return DMA2_CHANNEL1_INDEX;
#endif
#ifdef DMA2_Channel2
    case (uint32_t)DMA2_Channel2:
        return DMA2_CHANNEL2_INDEX;
#endif
#ifdef DMA2_Channel3
    case (uint32_t)DMA2_Channel3:
        return DMA2_CHANNEL3_INDEX;
#endif
#ifdef DMA2_Channel4
    case (uint32_t)DMA2_Channel4:
        return DMA2_CHANNEL4_INDEX;
#endif
#ifdef DMA2_Channel5
    case (uint32_t)DMA2_Channel5:
        return DMA2_CHANNEL5_INDEX;
#endif
#ifdef DMA2_Channel6
    case (uint32_t)DMA2_Channel6:
        return DMA2_CHANNEL6_INDEX;
#endif
#ifdef DMA2_Channel7
    case (uint32_t)DMA2_Channel7:
        return DMA2_CHANNEL7_INDEX;
#endif
#ifdef DMA2_Channel8
    case (uint32_t)DMA2_Channel8:
        return DMA2_CHANNEL8_INDEX;
#endif
    default:
        return NC;
    }
}

/**
  * @brief  This function will store the DMA handle in the appropriate slot
  * @param  dma_handle : dma handle
  * @retval None
  */
void prepare_dma(DMA_HandleTypeDef *dma_handle) {
    dma_index_t dma_index = get_dma_index(dma_handle->Instance);
    if (dma_index == NC) {
        return;
    }
    dma_handles[dma_index] = dma_handle;
}

/**
  * @brief  This function will remove the DMA handle from the appropriate slot
  * @param  dma_handle : dma handle
  * @retval None
  */
void end_dma(DMA_HandleTypeDef *dma_handle) {
    dma_index_t dma_index = get_dma_index(dma_handle->Instance);
    if (dma_index == NC) {
        return;
    }
    dma_handles[dma_index] = NULL;
}

#ifdef DMA1_Channel1
/**
  * @brief  DMA1 Channel1 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL1_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL1_INDEX]);
}
#endif

#ifdef DMA1_Channel2
/**
  * @brief  DMA1 Channel2 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel2_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL2_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL2_INDEX]);
}
#endif

#ifdef DMA1_Channel3
/**
  * @brief  DMA1 Channel3 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel3_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL3_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL3_INDEX]);
}
#endif

#ifdef DMA1_Channel4
/**
  * @brief  DMA1 Channel4 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL4_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL4_INDEX]);
}
#endif

#ifdef DMA1_Channel5
/**
  * @brief  DMA1 Channel5 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL5_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL5_INDEX]);
}
#endif

#ifdef DMA1_Channel6/**
  * @brief  DMA1 Channel6 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL6_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL6_INDEX]);
}
#endif

#ifdef DMA1_Channel7
/**
  * @brief  DMA1 Channel3 IRQHandler
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler() {
    if (dma_handles[DMA1_CHANNEL7_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA1_CHANNEL7_INDEX]);
}
#endif

#ifdef DMA2_Channel1
/**
  * @brief  DMA2 Channel1 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel1_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL1_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL1_INDEX]);
}
#endif

#ifdef DMA2_Channel2
/**
  * @brief  DMA2 Channel2 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel1_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL2_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL2_INDEX]);
}
#endif

#ifdef DMA2_Channel3
/**
  * @brief  DMA2 Channel3 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel3_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL3_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL3_INDEX]);
}
#endif

#ifdef DMA2_Channel4
/**
  * @brief  DMA2 Channel4 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel4_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL4_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL4_INDEX]);
}
#endif

#ifdef DMA2_Channel5
/**
  * @brief  DMA2 Channel5 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel5_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL5_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL5_INDEX]);
}
#endif

#ifdef DMA2_Channel6
/**
  * @brief  DMA2 Channel6 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel6_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL6_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL6_INDEX]);
}
#endif

#ifdef DMA2_Channel7
/**
  * @brief  DMA2 Channel7 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel7_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL7_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL7_INDEX]);
}
#endif

#ifdef DMA2_Channel8
/**
  * @brief  DMA2 Channel8 IRQHandler
  * @param  None
  * @retval None
  */
void DMA2_Channel8_IRQHandler() {
    if (dma_handles[DMA2_CHANNEL8_INDEX] != NULL)
        HAL_DMA_IRQHandler(dma_handles[DMA2_CHANNEL8_INDEX]);
}
#endif

#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif
