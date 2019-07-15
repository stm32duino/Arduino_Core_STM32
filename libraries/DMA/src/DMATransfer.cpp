#include <dma.h>
#include <DMATransfer.h>

/**
  * @brief  Prepares for DMA Transfer by enabling clocks
  *         and storing the settings in the slots
  * @param  settings : dma transfer settings
  * @retval None
  */
void DMATransferClass::prepare(dmatransfer_t *settings)
{
  if (!_prepared) {
    // TODO - figure out which DMA to enable the clock for.
    __HAL_RCC_DMA1_CLK_ENABLE();

    memcpy(&_transfer_settings, settings, sizeof(dmatransfer_t));

    _transfer_settings.dma_settings.Init.Direction = _transfer_settings.transfer_direction;
    _transfer_settings.dma_settings.Init.PeriphInc = DMA_PINC_DISABLE;
    _transfer_settings.dma_settings.Init.MemInc = DMA_MINC_DISABLE;
    _transfer_settings.dma_settings.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    _transfer_settings.dma_settings.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    _transfer_settings.dma_settings.Init.Mode = _transfer_settings.circular ? DMA_CIRCULAR : DMA_NORMAL;
    _transfer_settings.dma_settings.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    _transfer_settings.dma_settings.Instance = _transfer_settings.channel_stream;
    // TODO - intialize the callbacks.

    // Perform HAL Initialization first.
    HAL_DMA_Init(&_transfer_settings.dma_settings);

    // Call dma prepare
    prepare_dma(&_transfer_settings.dma_settings);

    _prepared = true;
  }
}

/**
  * @brief  Begin the DMA transfer
  * @retval None
  */
void DMATransferClass::begin(int bytes_to_transfer)
{
  if (!_prepared) {
    // call dma prepare
    prepare_dma(&_transfer_settings.dma_settings);
  }

  // Reset flags so it starts over
  __HAL_DMA_CLEAR_FLAG(&_transfer_settings.dma_settings, DMA_FLAG_TC2 | DMA_FLAG_HT2 | DMA_FLAG_TE2);

  // Set size to transfer
  _transfer_settings.dma_settings.Instance->CNDTR = bytes_to_transfer;

  // and enable it
  __HAL_DMA_ENABLE(&_transfer_settings.dma_settings);

  HAL_DMA_Start(&_transfer_settings.dma_settings, _transfer_settings.source, _transfer_settings.destination, bytes_to_transfer);
}

/**
  * @brief  End the DMA transfer
  * @retval None
  */
void DMATransferClass::end()
{

  __HAL_DMA_DISABLE(&_transfer_settings.dma_settings);

  if (_prepared) {
    end_dma(&_transfer_settings.dma_settings);
    _prepared = false;
  }
}
