/**
  ******************************************************************************
  * @file    cdc_queue.c
  * @author  makarenya
  * @version V1.0.0
  * @date    23-December-2018
  * @brief   Provides methods to manipulate with CDC cyclic buffers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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

#ifdef USBCON
#ifdef USBD_USE_CDC

#include "cdc_queue.h"

// Initialize read and write position of queue
void CDC_TransmitQueue_Init(CDC_TransmitQueue_TypeDef *queue)
{
  queue->read = 0;
  queue->write = 0;
}

// Determine size, available for write in queue
int CDC_TransmitQueue_WriteSize(CDC_TransmitQueue_TypeDef *queue)
{
  return (queue->read + CDC_TRANSMIT_QUEUE_BUFFER_SIZE - queue->write - 1)
         % CDC_TRANSMIT_QUEUE_BUFFER_SIZE;
}

// Determine size of data, stored in queue
int CDC_TransmitQueue_ReadSize(CDC_TransmitQueue_TypeDef *queue)
{
  return (queue->write + CDC_TRANSMIT_QUEUE_BUFFER_SIZE - queue->read)
         % CDC_TRANSMIT_QUEUE_BUFFER_SIZE;
}

// Write provided data into queue.
void CDC_TransmitQueue_Enqueue(CDC_TransmitQueue_TypeDef *queue,
                               const uint8_t *buffer, uint32_t size)
{
  uint32_t sizeToEnd = CDC_TRANSMIT_QUEUE_BUFFER_SIZE - queue->write;
  if (sizeToEnd > size) {
    memcpy(&queue->buffer[queue->write], &buffer[0], size);
  } else {
    memcpy(&queue->buffer[queue->write], &buffer[0], sizeToEnd);
    memcpy(&queue->buffer[0], &buffer[sizeToEnd], size - sizeToEnd);
  }
  queue->write = (uint16_t)((queue->write + size) %
                            CDC_TRANSMIT_QUEUE_BUFFER_SIZE);
}

// Read flat block from queue biggest as possible, but max QUEUE_MAX_PACKET_SIZE
uint8_t *CDC_TransmitQueue_ReadBlock(CDC_TransmitQueue_TypeDef *queue,
                                     uint16_t *size)
{
  if (queue->write >= queue->read) {
    *size = queue->write - queue->read;
  } else {
    *size = CDC_TRANSMIT_QUEUE_BUFFER_SIZE - queue->read;
  }
  queue->reserved = *size;
  return &queue->buffer[queue->read];
}

void CDC_TransmitQueue_CommitRead(CDC_TransmitQueue_TypeDef *queue)
{
  queue->read = (queue->read + queue->reserved) %
                CDC_TRANSMIT_QUEUE_BUFFER_SIZE;
}

// Initialize read and write position of queue.
void CDC_ReceiveQueue_Init(CDC_ReceiveQueue_TypeDef *queue)
{
  queue->read = 0;
  queue->write = 0;
  queue->length = CDC_RECEIVE_QUEUE_BUFFER_SIZE;
}

// Reserve block in queue and return pointer to it.
uint8_t *CDC_ReceiveQueue_ReserveBlock(CDC_ReceiveQueue_TypeDef *queue)
{
  const uint16_t limit =
    CDC_RECEIVE_QUEUE_BUFFER_SIZE - CDC_QUEUE_MAX_PACKET_SIZE;
  volatile uint16_t read = queue->read;

  if (read <= queue->write) {
    // if write is limited only by buffer size.
    if (queue->write < limit || (queue->write == limit && read > 0)) {
      // if size in the rest of buffer is enough for full packet plus 1 byte
      // or if it tight enough and write position can be set to 0
      return queue->buffer + queue->write;
    } else if (read > CDC_QUEUE_MAX_PACKET_SIZE) {
      // if size in the rest is not enough, but enough size in head
      queue->length = queue->write;
      queue->write = 0;
      return queue->buffer + queue->write;
    }
  } else if (queue->write + CDC_QUEUE_MAX_PACKET_SIZE < read) {
    // write position must be less than read position
    // after reading largest possible packet
    return queue->buffer + queue->write;
  }
  return 0;
}

// Commits block in queue and make it available for reading
void CDC_ReceiveQueue_CommitBlock(CDC_ReceiveQueue_TypeDef *queue,
                                  uint16_t size)
{
  queue->write += size;
  if (queue->write >= queue->length) {
    queue->length = CDC_RECEIVE_QUEUE_BUFFER_SIZE;
  }
  if (queue->write >= CDC_RECEIVE_QUEUE_BUFFER_SIZE) {
    queue->write = 0;
  }
}

// Determine size, available for read
int CDC_ReceiveQueue_ReadSize(CDC_ReceiveQueue_TypeDef *queue)
{
  // reading length after write make guarantee, that length >= write
  // and determined reading size will be smaller or equal than real one.
  volatile uint16_t write = queue->write;
  volatile uint16_t length = queue->length;
  if (write >= queue->read) {
    return write - queue->read;
  }
  return length + write - queue->read;
}

// Read one byte from queue.
int CDC_ReceiveQueue_Dequeue(CDC_ReceiveQueue_TypeDef *queue)
{
  volatile uint16_t write = queue->write;
  volatile uint16_t length = queue->length;
  if (queue->read == length) {
    queue->read = 0;
  }
  if (write == queue->read) {
    return -1;
  }
  uint8_t ch = queue->buffer[queue->read++];
  if (queue->read >= length) {
    queue->read = 0;
  }
  return ch;
}

// Peek byte from queue.
int CDC_ReceiveQueue_Peek(CDC_ReceiveQueue_TypeDef *queue)
{
  volatile uint16_t write = queue->write;
  volatile uint16_t length = queue->length;
  if (queue->read >= length) {
    queue->read = 0;
  }
  if (write == queue->read) {
    return -1;
  }
  return queue->buffer[queue->read];
}

uint16_t CDC_ReceiveQueue_Read(CDC_ReceiveQueue_TypeDef *queue,
                               uint8_t *buffer, uint16_t size)
{
  volatile uint16_t write = queue->write;
  volatile uint16_t length = queue->length;
  uint16_t available;

  if (queue->read >= length) {
    queue->read = 0;
  }
  if (write >= queue->read) {
    available = write - queue->read;
  } else {
    available = length - queue->read;
  }
  if (available < size) {
    size = available;
  }

  memcpy(buffer, &queue->buffer[queue->read], size);
  queue->read = queue->read + size;
  if (queue->read >= length) {
    queue->read = 0;
  }
  return size;
}

bool CDC_ReceiveQueue_ReadUntil(CDC_ReceiveQueue_TypeDef *queue,
                                uint8_t terminator, uint8_t *buffer, uint16_t size, uint16_t *fetched)
{
  volatile uint16_t write = queue->write;
  volatile uint16_t length = queue->length;
  uint16_t available;

  if (queue->read >= length) {
    queue->read = 0;
  }
  if (write >= queue->read) {
    available = write - queue->read;
  } else {
    available = length - queue->read;
  }
  if (available < size) {
    size = available;
  }

  uint8_t *start = &queue->buffer[queue->read];
  for (uint16_t i = 0; i < size; i++) {
    uint8_t ch = start[i];
    if (ch == terminator) {
      queue->read += (uint16_t)(i + 1);
      if (queue->read >= length) {
        queue->read = 0;
      }
      *fetched = i;
      return true;
    } else {
      buffer[i] = ch;
    }
  }

  *fetched = size;
  queue->read += size;
  if (queue->read >= length) {
    queue->read = 0;
  }
  return false;
}
#endif /* USBD_USE_CDC */
#endif /* USBCON */
