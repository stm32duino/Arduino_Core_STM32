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

#ifdef __cplusplus
 extern "C" {
#endif

#include "dma.h"
#include "PeripheralPins.h"

static DMA_HandleTypeDef DMAHandle[DMA_NUMBER][CHANNEL_NUMBER] = {0};

/**
  * @brief  Find DMA number from DMA mapping information
  * @param  peripheral  : pointer to peripheral instance
  * @param  map         : DMA map specific to the peripheral
  * @retval none
  */
static int8_t DMAMap_find_DMAx(void *peripheral, const DMAMap_t *map) {
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral)
      return map->dmaNumber;
    map++;
  }
  return NC;
}

/**
  * @brief  Find DMA irq from DMA mapping information
  * @param  peripheral  : pointer to peripheral instance
  * @param  map         : DMA map specific to the peripheral
  * @retval none
  */
static IRQn_Type DMA_find_irqn(void *peripheral, const DMAMap_t *map) {
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral)
      return map->irq;
    map++;
  }
  return NP;
}

/**
  * @brief  Find DMA channel from DMA mapping information
  * @param  peripheral  : pointer to peripheral instance
  * @param  map         : DMA map specific to the peripheral
  * @retval none
  */
static int8_t DMAMap_find_channel(void *peripheral, const DMAMap_t *map) {
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral)
      return map->channelNumber;
    map++;
  }
  return NC;
}

/**
  * @brief  Find DMA request from DMA mapping information
  * @param  peripheral  : pointer to peripheral instance
  * @param  map         : DMA map specific to the peripheral
  * @retval none
  */
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx) ||\
    defined(STM32L0xx) || defined(STM32L4xx)
static int8_t DMAMap_find_request(void *peripheral, const DMAMap_t *map) {
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral)
      return map->requestNumber;
    map++;
  }
  return NC;
}
#endif

/**
  * @brief  Find DMA instance from DMA mapping information
  * @param  DMAx    : DMA number (1 or 2)
  * @param  channel : channel number (0 to 7)
  * @retval DMA
  */
static void *DMA_find_instance(int8_t DMAx, int8_t channelx)
{
  void *DMAx_Instance = NULL;

  if((DMAx == NC) || (channelx == NC)) {
    return NULL;
  }

#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
  if(DMAx == 2) {
#ifdef DMA2_BASE
    DMAx_Instance = (void *)(DMA2_Stream0_BASE + DMA_INSTANCE_OFFSET(channelx));
#endif
  } else {
    DMAx_Instance = (void *)(DMA1_Stream0_BASE + DMA_INSTANCE_OFFSET(channelx));
  }
#else
  if(DMAx == 2) {
#ifdef DMA2_BASE
    DMAx_Instance = (void *)(DMA2_Channel1_BASE + DMA_INSTANCE_OFFSET(channelx));
#endif
  } else {
    DMAx_Instance = (void *)(DMA1_Channel1_BASE + DMA_INSTANCE_OFFSET(channelx));
  }
#endif

  return DMAx_Instance;
}

/**
  * @brief  This function initializes DMA for a peripheral
  * @param  handle            : pointer to peripheral DMA Handle
  * @param  peripheral        : pointer to peripheral instance
  * @param  map               : DMA mapping specific to the peripheral
  * @retval none
  */
void DMA_init(void *periph, void *instance, DMA_HandleTypeDef **handle, const DMAMap_t *map)
{
  if((periph == NULL) || (instance == NULL) || (handle == NULL) || (map == NULL)) {
    printf("DMA_init failed: incorrect parameters!\n");
    return;
  }

  int8_t DMAx = DMAMap_find_DMAx(instance, map);
  if(DMAx == NC) {
    printf("DMA_init failed: DMA number not found!\n");
    return;
  }

  int8_t channel = DMAMap_find_channel(instance, map);
  if(channel == NC) {
    printf("DMA_init failed: DMA channel not found!\n");
    return;
  }

  void *DMAx_Instance = DMA_find_instance(DMAx, channel);
  if(DMAx_Instance == NULL) {
    printf("DMA_init failed: DMA instance not found!\n");
    return;
  }

  if(DMAx == 2) {
#ifdef DMA2_BASE
    __HAL_RCC_DMA2_CLK_ENABLE();
#endif
  } else {
    __HAL_RCC_DMA1_CLK_ENABLE();
  }

  // Match with DMAHandle index
  DMAx -= 1;

  // Configure DMA
  DMAHandle[DMAx][channel].Instance                 = DMAx_Instance;
  DMAHandle[DMAx][channel].Init.Direction           = DMA_PERIPH_TO_MEMORY;
  DMAHandle[DMAx][channel].Init.PeriphInc           = DMA_PINC_DISABLE;
  DMAHandle[DMAx][channel].Init.MemInc              = DMA_MINC_ENABLE;
  DMAHandle[DMAx][channel].Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;//DMA_PDATAALIGN_HALFWORD;
  DMAHandle[DMAx][channel].Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  DMAHandle[DMAx][channel].Init.Mode                = DMA_NORMAL;
  DMAHandle[DMAx][channel].Init.Priority            = DMA_PRIORITY_MEDIUM;
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
  DMAHandle[DMAx][channel].Init.Channel             = DMA_CHANNEL(DMAMap_find_request(instance, map));
  DMAHandle[DMAx][channel].Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  DMAHandle[DMAx][channel].Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_HALFFULL;
  DMAHandle[DMAx][channel].Init.MemBurst            = DMA_MBURST_SINGLE;
  DMAHandle[DMAx][channel].Init.PeriphBurst         = DMA_PBURST_SINGLE;
#elif defined(STM32L0xx) || defined(STM32L4xx)
  DMAHandle[DMAx][channel].Init.Request             = DMA_CHANNEL(DMAMap_find_request(instance, map));
#endif //STM32F2xx STM32F4xx STM32F7xx

  /* DeInitialize the DMA */
  HAL_DMA_DeInit(&DMAHandle[DMAx][channel]);
  /* Initialize the DMA */
  HAL_DMA_Init(&DMAHandle[DMAx][channel]);

  /* Associate the DMA handle (can't use __HAL_LINKDMA())*/
  *handle = &DMAHandle[DMAx][channel];
  DMAHandle[DMAx][channel].Parent = periph;

  /* NVIC */
  IRQn_Type irqn = DMA_find_irqn(instance, map);
  HAL_NVIC_SetPriority(irqn, 1, 0);
  HAL_NVIC_EnableIRQ(irqn);
}

/**
  * @brief  This function deinitializes DMA
  * @param  peripheral  : pointer to peripheral instance
  * @param  map               : DMA mapping specific to the peripheral
  * @retval none
  */
void DMA_deinit(void *instance, const DMAMap_t *map)
{
  if((instance == NULL) || (map == NULL)) {
    return;
  }

  int8_t DMAx = DMAMap_find_DMAx(instance, map);
  if(DMAx == NC) {
    return;
  }

  int8_t channel = DMAMap_find_channel(instance, map);
  if(channel == NC) {
    return;
  }

  IRQn_Type irqn = DMA_find_irqn(instance, map);
  HAL_NVIC_DisableIRQ(irqn);

  HAL_DMA_DeInit(&DMAHandle[DMAx-1][channel]);
}

/******************************************************************************/
/*                            DMAx IRQ HANDLER                                */
/******************************************************************************/

#if defined(DMA1_Stream0_BASE)
void DMA1_Stream0_IRQHandler(void)
{
  if(DMAHandle[0][0].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][0]);
  }
}
#endif

#if defined(DMA1_Channel1_BASE) || defined(DMA1_Stream1_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream1_IRQHandler(void)
#else
void DMA1_Channel1_IRQHandler(void)
#endif
{
  if(DMAHandle[0][1].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][1]);
  }
}
#endif

#if defined(DMA1_Channel2_BASE) || defined(DMA1_Stream2_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream2_IRQHandler(void)
#else
void DMA1_Channel2_IRQHandler(void)
#endif
{
  if(DMAHandle[0][2].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][2]);
  }

#if defined(STM32F0xx) || defined(STM32L0xx)
  if(DMAHandle[0][3].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][3]);
  }
#endif
}
#endif

#if defined(DMA1_Channel3_BASE) || defined(DMA1_Stream3_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream3_IRQHandler(void)
#else
void DMA1_Channel3_IRQHandler(void)
#endif
{
  if(DMAHandle[0][3].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][3]);
  }
}
#endif

#if defined(DMA1_Channel4_BASE) || defined(DMA1_Stream4_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream4_IRQHandler(void)
#else
void DMA1_Channel4_IRQHandler(void)
#endif
{
  if(DMAHandle[0][4].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][4]);
  }

#if defined(STM32F0xx) || defined(STM32L0xx)
  if(DMAHandle[0][5].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][5]);
  }

  if(DMAHandle[0][6].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][6]);
  }

  if(DMAHandle[0][7].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][7]);
  }
#endif
}
#endif

#if defined(DMA1_Channel5_BASE) || defined(DMA1_Stream5_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream5_IRQHandler(void)
#else
void DMA1_Channel5_IRQHandler(void)
#endif
{
  if(DMAHandle[0][5].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][5]);
  }
}
#endif

#if defined(DMA1_Channel6_BASE) || defined(DMA1_Stream6_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream6_IRQHandler(void)
#else
void DMA1_Channel6_IRQHandler(void)
#endif
{
  if(DMAHandle[0][6].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][6]);
  }
}
#endif

#if defined(DMA1_Channel7_BASE) || defined(DMA1_Stream7_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA1_Stream7_IRQHandler(void)
#else
void DMA1_Channel7_IRQHandler(void)
#endif
{
  if(DMAHandle[0][7].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[0][7]);
  }
}
#endif

#if defined(DMA2_Stream0_BASE)
void DMA2_Stream0_IRQHandler(void)
{
  if(DMAHandle[1][0].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][0]);
  }
}
#endif

#if defined(DMA2_Channel1_BASE) || defined(DMA2_Stream1_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream1_IRQHandler(void)
#else
void DMA2_Channel1_IRQHandler(void)
#endif
{
  if(DMAHandle[1][1].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][1]);
  }
}
#endif

#if defined(DMA2_Channel2_BASE) || defined(DMA2_Stream2_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream2_IRQHandler(void)
#else
void DMA2_Channel2_IRQHandler(void)
#endif
{
  if(DMAHandle[1][2].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][2]);
  }
}
#endif

#if defined(DMA2_Channel3_BASE) || defined(DMA2_Stream3_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream3_IRQHandler(void)
#else
void DMA2_Channel3_IRQHandler(void)
#endif
{
  if(DMAHandle[1][3].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][3]);
  }
}
#endif

#if defined(DMA2_Channel4_BASE) || defined(DMA2_Stream4_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream4_IRQHandler(void)
#else
void DMA2_Channel4_IRQHandler(void)
#endif
{
  if(DMAHandle[1][4].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][4]);
  }
}
#endif

#if defined(DMA2_Channel5_BASE) || defined(DMA2_Stream5_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream5_IRQHandler(void)
#else
void DMA2_Channel5_IRQHandler(void)
#endif
{
  if(DMAHandle[1][5].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][5]);
  }
}
#endif

#if defined(DMA2_Channel6_BASE) || defined(DMA2_Stream6_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream6_IRQHandler(void)
#else
void DMA2_Channel6_IRQHandler(void)
#endif
{
  if(DMAHandle[1][6].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][6]);
  }
}
#endif

#if defined(DMA2_Channel7_BASE) || defined(DMA2_Stream7_Base)
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
void DMA2_Stream7_IRQHandler(void)
#else
void DMA2_Channel7_IRQHandler(void)
#endif
{
  if(DMAHandle[1][7].Instance != NULL)
  {
    HAL_DMA_IRQHandler(&DMAHandle[1][7]);
  }
}
#endif

#ifdef __cplusplus
}
#endif
