#include <dma.h>
#include <DMATransfer.h>

/**
  * @brief  Prepares for DMA Transfer by enabling clocks
  *         and storing the settings in the slots
  * @param  settings : dma transfer settings
  * @retval None
  */
void DMATransferClass::prepare(DMA_HandleTypeDef *settings)
{
  if (!_prepared) {
    // TODO - figure out which DMA to enable the clock for.
    __HAL_RCC_DMA1_CLK_ENABLE();

    memcpy(&_dma, settings, sizeof(DMA_HandleTypeDef));
    /*
    _transfer_settings.dma_settings.Init.Direction = _transfer_settings.transfer_direction;
    _transfer_settings.dma_settings.Init.PeriphInc = DMA_PINC_DISABLE;
    _transfer_settings.dma_settings.Init.MemInc = DMA_MINC_DISABLE;
    _transfer_settings.dma_settings.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    _transfer_settings.dma_settings.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    _transfer_settings.dma_settings.Init.Mode = _transfer_settings.circular ? DMA_CIRCULAR : DMA_NORMAL;
    _transfer_settings.dma_settings.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    _transfer_settings.dma_settings.Instance = _transfer_settings.channel_stream;
    // TODO - intialize the callbacks.
    */

    // Perform HAL Initialization first.
    HAL_DMA_Init(&_dma);
    _dma.XferCpltCallback = settings->XferCpltCallback;
    _dma.XferHalfCpltCallback = settings->XferHalfCpltCallback;
    _dma.XferErrorCallback = settings->XferErrorCallback;
    _dma.XferAbortCallback = settings->XferAbortCallback;

    // Call dma prepare
    prepare_dma(&_dma);

    _prepared = true;
  }
}

/**
  * @brief  Begin the DMA transfer
  * @retval None
  */
void DMATransferClass::begin(uint32_t source, uint32_t destination, int bytes_to_transfer, bool use_interrupt)
{
  if (!_prepared) {
    // call dma prepare
    prepare_dma(&_dma);
  }

  // Reset flags so it starts over
  __HAL_DMA_CLEAR_FLAG(&_dma, DMA_FLAG_TC2 | DMA_FLAG_HT2 | DMA_FLAG_TE2);

  // Set size to transfer
  _dma.Instance->CNDTR = bytes_to_transfer;

  // and enable it
  __HAL_DMA_ENABLE(&_dma);

  if (use_interrupt) {
    IRQn_Type interrupt_number = get_dma_interrupt(_dma.Instance);
    HAL_NVIC_SetPriority(interrupt_number, 0, 0);
    HAL_NVIC_EnableIRQ(interrupt_number);
    HAL_DMA_Start_IT(&_dma, source, destination, bytes_to_transfer);
  }
  else {
    HAL_DMA_Start(&_dma, source, destination, bytes_to_transfer);
  }
}

/**
  * @brief  End the DMA transfer
  * @retval None
  */
void DMATransferClass::end()
{

  __HAL_DMA_DISABLE(&_dma);

  if (_prepared) {
    end_dma(&_dma);
    _prepared = false;
  }
}
