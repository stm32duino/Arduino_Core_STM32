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
#ifndef CDC_TRANSMIT_QUEUE_BUFFER_PACKET_NUMBER
#define CDC_TRANSMIT_QUEUE_BUFFER_PACKET_NUMBER 2
#endif
#ifndef CDC_RECEIVE_QUEUE_BUFFER_PACKET_NUMBER
#define CDC_RECEIVE_QUEUE_BUFFER_PACKET_NUMBER 3
#endif
#define CDC_TRANSMIT_QUEUE_BUFFER_SIZE ((uint16_t)(CDC_QUEUE_MAX_PACKET_SIZE * CDC_TRANSMIT_QUEUE_BUFFER_PACKET_NUMBER))
#define CDC_RECEIVE_QUEUE_BUFFER_SIZE ((uint16_t)(CDC_QUEUE_MAX_PACKET_SIZE * CDC_RECEIVE_QUEUE_BUFFER_PACKET_NUMBER))

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

/**
 * @brief Initialize read and write position of the transmit queue.
 * @param queue transmit queue to initialize.
 */
void CDC_TransmitQueue_Init(CDC_TransmitQueue_TypeDef *queue);

/**
 * @brief Get the free space available for writing into the transmit queue.
 * @note One byte is always kept unused to tell a full queue from an empty one.
 * @param queue transmit queue.
 * @return number of bytes that can be enqueued.
 */
int CDC_TransmitQueue_WriteSize(CDC_TransmitQueue_TypeDef *queue);

/**
 * @brief Get the amount of data stored in the transmit queue.
 * @param queue transmit queue.
 * @return number of bytes waiting to be transmitted.
 */
int CDC_TransmitQueue_ReadSize(CDC_TransmitQueue_TypeDef *queue);

/**
 * @brief Copy data into the transmit queue, wrapping at the end of the buffer.
 * @note The caller must check CDC_TransmitQueue_WriteSize() first. Writing more
 *       than the free space overwrites data not yet transmitted.
 * @param queue transmit queue.
 * @param buffer data to copy.
 * @param size number of bytes to copy.
 */
void CDC_TransmitQueue_Enqueue(CDC_TransmitQueue_TypeDef *queue, const uint8_t *buffer, uint32_t size);

/**
 * @brief Get a contiguous block of queued data to transmit.
 * @note The block may be shorter than the total queued data when it wraps
 *       around the end of the buffer. The block is reserved until
 *       CDC_TransmitQueue_CommitRead() is called.
 * @param queue transmit queue.
 * @param size output: length of the returned block in bytes.
 * @return pointer to the first byte of the block.
 */
uint8_t *CDC_TransmitQueue_ReadBlock(CDC_TransmitQueue_TypeDef *queue, uint16_t *size);

/**
 * @brief Release the block returned by CDC_TransmitQueue_ReadBlock().
 * @param queue transmit queue.
 */
void CDC_TransmitQueue_CommitRead(CDC_TransmitQueue_TypeDef *queue);

/**
 * @brief Initialize read and write position of the receive queue.
 * @param queue receive queue to initialize.
 */
void CDC_ReceiveQueue_Init(CDC_ReceiveQueue_TypeDef *queue);

/**
 * @brief Get the amount of data available for reading from the receive queue.
 * @param queue receive queue.
 * @return number of bytes available to read.
 */
int CDC_ReceiveQueue_ReadSize(CDC_ReceiveQueue_TypeDef *queue);

/**
 * @brief Read and remove one byte from the receive queue.
 * @param queue receive queue.
 * @return byte value (0-255), or -1 if the queue is empty.
 */
int CDC_ReceiveQueue_Dequeue(CDC_ReceiveQueue_TypeDef *queue);

/**
 * @brief Read one byte from the receive queue without removing it.
 * @param queue receive queue.
 * @return byte value (0-255), or -1 if the queue is empty.
 */
int CDC_ReceiveQueue_Peek(CDC_ReceiveQueue_TypeDef *queue);

/**
 * @brief Read and remove up to size bytes from the receive queue.
 * @param queue receive queue.
 * @param buffer destination buffer.
 * @param size maximum number of bytes to read.
 * @return number of bytes copied into buffer.
 */
uint16_t CDC_ReceiveQueue_Read(CDC_ReceiveQueue_TypeDef *queue, uint8_t *buffer, uint16_t size);

/**
 * @brief Read and remove bytes from the receive queue up to a terminator.
 * @note The terminator is consumed but not copied into buffer. If the
 *       terminator is not found, up to size bytes are read and removed.
 * @param queue receive queue.
 * @param terminator byte that ends the read.
 * @param buffer destination buffer.
 * @param size maximum number of bytes to copy into buffer.
 * @param fetched output: number of bytes copied into buffer, excluding the terminator.
 * @return true if the terminator was found, false otherwise.
 */
bool CDC_ReceiveQueue_ReadUntil(CDC_ReceiveQueue_TypeDef *queue, uint8_t terminator, uint8_t *buffer,
                                uint16_t size, uint16_t *fetched);

/**
 * @brief Reserve space in the receive queue for an incoming packet.
 * @note Up to CDC_QUEUE_MAX_PACKET_SIZE bytes may be written to the returned
 *       pointer. Call CDC_ReceiveQueue_CommitBlock() with the number of bytes
 *       actually written.
 * @param queue receive queue.
 * @return pointer where the packet can be written, or NULL if there is no room.
 */
uint8_t *CDC_ReceiveQueue_ReserveBlock(CDC_ReceiveQueue_TypeDef *queue);

/**
 * @brief Commit bytes written to a block returned by CDC_ReceiveQueue_ReserveBlock().
 * @param queue receive queue.
 * @param size number of bytes written into the reserved block.
 */
void CDC_ReceiveQueue_CommitBlock(CDC_ReceiveQueue_TypeDef *queue, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif // __CDC_QUEUE_H
