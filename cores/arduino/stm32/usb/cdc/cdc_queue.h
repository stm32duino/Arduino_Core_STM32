/**
  ******************************************************************************
  * @file    cdc_queue.h
  * @author  makarenya
  * @version V1.0.0
  * @date    23-December-2018
  * @brief   Header for cdc_queue.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#ifndef __CDC_QUEUE_H
#define __CDC_QUEUE_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "usbd_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#if USE_USB_HS
#define CDC_QUEUE_MAX_PACKET_SIZE USB_HS_MAX_PACKET_SIZE
#else
#define CDC_QUEUE_MAX_PACKET_SIZE USB_FS_MAX_PACKET_SIZE
#endif
#define CDC_TRANSMIT_QUEUE_BUFFER_SIZE ((uint16_t)(CDC_QUEUE_MAX_PACKET_SIZE * 2))
#define CDC_RECEIVE_QUEUE_BUFFER_SIZE ((uint16_t)(CDC_QUEUE_MAX_PACKET_SIZE * 3))

typedef struct {
  uint8_t buffer[CDC_TRANSMIT_QUEUE_BUFFER_SIZE];
  volatile uint16_t write;
  volatile uint16_t read;
  volatile uint16_t reserved;
} CDC_TransmitQueue_TypeDef;

typedef struct {
  uint8_t buffer[CDC_RECEIVE_QUEUE_BUFFER_SIZE];
  volatile uint16_t write;
  volatile uint16_t read;
  volatile uint16_t length;
} CDC_ReceiveQueue_TypeDef;

void CDC_TransmitQueue_Init(CDC_TransmitQueue_TypeDef *queue);
int CDC_TransmitQueue_WriteSize(CDC_TransmitQueue_TypeDef *queue);
int CDC_TransmitQueue_ReadSize(CDC_TransmitQueue_TypeDef *queue);
void CDC_TransmitQueue_Enqueue(CDC_TransmitQueue_TypeDef *queue, const uint8_t *buffer, uint32_t size);
uint8_t *CDC_TransmitQueue_ReadBlock(CDC_TransmitQueue_TypeDef *queue, uint16_t *size);
void CDC_TransmitQueue_CommitRead(CDC_TransmitQueue_TypeDef *queue);

void CDC_ReceiveQueue_Init(CDC_ReceiveQueue_TypeDef *queue);
int CDC_ReceiveQueue_ReadSize(CDC_ReceiveQueue_TypeDef *queue);
int CDC_ReceiveQueue_Dequeue(CDC_ReceiveQueue_TypeDef *queue);
int CDC_ReceiveQueue_Peek(CDC_ReceiveQueue_TypeDef *queue);
uint16_t CDC_ReceiveQueue_Read(CDC_ReceiveQueue_TypeDef *queue, uint8_t *buffer, uint16_t size);
bool CDC_ReceiveQueue_ReadUntil(CDC_ReceiveQueue_TypeDef *queue, uint8_t terminator, uint8_t *buffer,
                                uint16_t size, uint16_t *fetched);
uint8_t *CDC_ReceiveQueue_ReserveBlock(CDC_ReceiveQueue_TypeDef *queue);
void CDC_ReceiveQueue_CommitBlock(CDC_ReceiveQueue_TypeDef *queue, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif // __CDC_QUEUE_H