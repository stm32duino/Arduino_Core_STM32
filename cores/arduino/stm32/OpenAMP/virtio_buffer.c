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
#ifdef VIRTIOCON

#include "virtio_config.h"
#include "virtio_buffer.h"
#include <string.h>
#include "wiring.h"

void virtio_buffer_init(virtio_buffer_t *ring)
{
  ring->write_index = 0;
  ring->read_index = 0;
}

uint16_t virtio_buffer_read_available(virtio_buffer_t *ring)
{
  int32_t delta = ring->write_index - ring->read_index;

  if (delta < 0) {
    return (VIRTIO_BUFFER_SIZE + delta);
  }
  return delta;
}

/* WARNING no protection against race codition (on ring->read_index) when used in interruption */
static uint16_t read(virtio_buffer_t *ring, uint8_t *dst, uint16_t size, bool peek)
{
  uint16_t read_index = ring->read_index;
  int32_t delta = ring->write_index - read_index;
  if (delta < 0) {
    delta += VIRTIO_BUFFER_SIZE;
  }

  size = min(size, delta);

  if ((size + read_index) > VIRTIO_BUFFER_SIZE) {
    // Manage ring buffer rollover
    // First, copy ring buffer from read index to end of buffer
    memcpy(dst, ring->buffer + read_index, VIRTIO_BUFFER_SIZE - read_index);
    // then, copy ring buffer from begining of buffer to end of read
    memcpy(dst + VIRTIO_BUFFER_SIZE - read_index, ring->buffer, size - (VIRTIO_BUFFER_SIZE - read_index));
  } else {
    memcpy(dst, ring->buffer + read_index, size);
  }

  // Update read index if not peeked
  if (!peek) {
    ring->read_index += size;

    // Manage ring buffer rollover
    if (ring->read_index >= VIRTIO_BUFFER_SIZE) {
      ring->read_index -= VIRTIO_BUFFER_SIZE;
    }
  }
  return size;
}

uint16_t virtio_buffer_read(virtio_buffer_t *ring, uint8_t *dst, uint16_t size)
{
  return read(ring, dst, size, false);
}


uint16_t virtio_buffer_peek(virtio_buffer_t *ring, uint8_t *dst, uint16_t size)
{
  return read(ring, dst, size, true);
}



uint16_t virtio_buffer_write_available(virtio_buffer_t *ring)
{
  int32_t delta = ring->read_index - ring->write_index - 1;

  if (delta < 0) {
    return (VIRTIO_BUFFER_SIZE + delta);
  }
  return delta;
}

/* WARNING no protection against race codition (on ring->write_index) when used in interruption */
uint16_t virtio_buffer_write(virtio_buffer_t *ring, uint8_t *src, uint16_t size)
{
  uint16_t write_index = ring->write_index;
  int32_t delta = ring->read_index - write_index - 1;
  if (delta < 0) {
    delta += VIRTIO_BUFFER_SIZE;
  }

  size = min(size, delta);

  if ((size + write_index) > VIRTIO_BUFFER_SIZE) {
    // Manage ring buffer rollover
    // First, write ring buffer from write index to end of buffer
    memcpy(ring->buffer + write_index, src, VIRTIO_BUFFER_SIZE - write_index);
    // then,  write ring buffer from beginning of buffer to end of read
    memcpy(ring->buffer, src + VIRTIO_BUFFER_SIZE - write_index, size - (VIRTIO_BUFFER_SIZE - write_index));
  } else {
    memcpy(ring->buffer + write_index, src, size);
  }

  ring->write_index += size;
  if (ring->write_index >= VIRTIO_BUFFER_SIZE) {
    ring->write_index -= VIRTIO_BUFFER_SIZE;
  }
  return size;
}

#endif /* VIRTIOCON */
