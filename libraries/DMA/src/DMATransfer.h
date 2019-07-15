#ifndef __DMATRANSFER_H__
#define __DMATRANSFER_H__

#include "Arduino.h"

typedef struct dmatransfer_s dmatransfer_t;

#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
  typedef DMA_Stream_TypeDef DMA_CS_Selection;
#else
  typedef DMA_Channel_TypeDef DMA_CS_Selection;
#endif


struct dmatransfer_s {
    /*  Keep this the first member so casting back and forth is easy
     */
  DMA_HandleTypeDef *dma_settings;
  DMA_CS_Selection channel_stream;
  boolean circular;
  void (*transferComplete)(DMA_HandleTypeDef *);
  void (*transferHalfComplete)(DMA_HandleTypeDef *);
  void (*transferError)(DMA_HandleTypeDef *);
};

class DMATransferClass {

  public:
    void prepare(dmatransfer_t *settings);
    void begin(int bytes_to_transfer);
    void end();
  private:
    bool _prepared;
    dmatransfer_t _transfer_settings;
};


#endif /* __DMATRANSFER_H__ */
