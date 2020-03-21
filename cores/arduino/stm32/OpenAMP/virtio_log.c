/**
 * MIT License:
 * Copyright (c) 2020 Bumsik kim <k.bumsik@gmail.com>
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
#if defined(VIRTIOCON) && defined(VIRTIO_LOG)

#include "virtio_config.h"
#include "virtio_log.h"

char virtio_log_buffer[VIRTIO_LOG_BUFFER_SIZE];

void virtio_log(uint8_t *data, uint32_t size)
{
  static int offset = 0;

  for (uint32_t i = 0; i < size; i++) {
    virtio_log_buffer[offset++] = *(data + i);
    if ((offset + 1) >= VIRTIO_LOG_BUFFER_SIZE) {
      offset = 0;
    }
  }
  virtio_log_buffer[offset] = '\0';
}

#endif
