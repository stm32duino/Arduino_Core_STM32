#ifndef __DMATRANSFER_H__
#define __DMATRANSFER_H__

#include "Arduino.h"

typedef struct dmatransfer_s dmatransfer_t;

#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
typedef DMA_Stream_TypeDef DMA_CS_Selection;
#else
typedef DMA_Channel_TypeDef DMA_CS_Selection;
#endif

typedef class DMATransferClass {

  public:
    /*
    DMATransferClass(uint32_t transfer_direction, boolean circular, uint32_t source, uint32_t destination){
      this->dma.Init.
    }*/

    void prepare(DMA_HandleTypeDef *settings);
    void begin(uint32_t source, uint32_t destination, int bytes_to_transfer, bool use_interrupt = false);
    void end();
  private:
    bool _prepared;
    DMA_HandleTypeDef _dma;
} DMATransfer;


#endif /* __DMATRANSFER_H__ */
