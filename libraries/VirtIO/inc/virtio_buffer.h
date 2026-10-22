/**
 * MIT License:
 * Copyright (c) 2019 Bumsik kim <k.bumsik@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __OPENAMP_VIRTIO_BUFFER_H
#define __OPENAMP_VIRTIO_BUFFER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Size of virtio ring buffer
 * @note  See virtio_config.h for the size decision. (7937 bytes by default)
 *        The multiplier should be at least 1. As a result, the minimum
 *        required size of the initial virtio_buffer_write_available()
 *        must be RPMSG_VRING_TOTAL_PAYLOAD_SIZE.
 * @note  If VIRTIO_BUFFER_SIZE is still too big, RPMSG_VRING_TOTAL_PAYLOAD_SIZE
 *        can be reduced by reducing the number of VRING_NUM_BUFFS in
 *        virtio_config.h.
 */
#ifndef VIRTIO_BUFFER_SIZE
#define VIRTIO_BUFFER_SIZE (RPMSG_VRING_TOTAL_PAYLOAD_SIZE * 1 + 1)
#endif

typedef struct {
  uint8_t buffer[VIRTIO_BUFFER_SIZE];
  volatile uint16_t write_index;
  volatile uint16_t read_index;
} virtio_buffer_t;

/**
 * @brief Initialize a virtio ring buffer to empty.
 * @param ring Pointer to the ring buffer to initialize.
 */
void virtio_buffer_init(virtio_buffer_t *ring);

/**
 * @brief Get the number of bytes available to read.
 * @param ring Pointer to the ring buffer.
 * @return Number of bytes that virtio_buffer_read() can return.
 */
uint16_t virtio_buffer_read_available(virtio_buffer_t *ring);

/**
 * @brief Read and remove bytes from the ring buffer.
 * @param ring Pointer to the ring buffer.
 * @param dst Destination buffer.
 * @param size Maximum number of bytes to read.
 * @return Number of bytes actually read, at most size.
 * @note Not protected against race conditions on read_index. Do not use
 *       concurrently from an interrupt and the main loop.
 */
uint16_t virtio_buffer_read(virtio_buffer_t *ring, uint8_t *dst, uint16_t size);

/**
 * @brief Copy bytes from the ring buffer without removing them.
 * @param ring Pointer to the ring buffer.
 * @param dst Destination buffer.
 * @param size Maximum number of bytes to copy.
 * @return Number of bytes actually copied, at most size.
 */
uint16_t virtio_buffer_peek(virtio_buffer_t *ring, uint8_t *dst, uint16_t size);

/**
 * @brief Get the number of bytes that can be written.
 * @param ring Pointer to the ring buffer.
 * @return Number of free bytes. One byte is always kept unused to tell a
 *         full buffer from an empty one.
 */
uint16_t virtio_buffer_write_available(virtio_buffer_t *ring);

/**
 * @brief Write bytes into the ring buffer.
 * @param ring Pointer to the ring buffer.
 * @param src Source data.
 * @param size Maximum number of bytes to write.
 * @return Number of bytes actually written, at most size.
 * @note Not protected against race conditions on write_index. Do not use
 *       concurrently from an interrupt and the main loop.
 */
uint16_t virtio_buffer_write(virtio_buffer_t *ring, uint8_t *src, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif // __OPENAMP_VIRTIO_BUFFER_H
