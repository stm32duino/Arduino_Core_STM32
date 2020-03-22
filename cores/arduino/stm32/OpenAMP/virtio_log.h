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
#ifndef __OPENAMP_VIRTIO_LOG_H
#define __OPENAMP_VIRTIO_LOG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write data to the OpenAMP trace buffer
 * @note  By writing OpenAMP trace (log) buffer here, the Linux host can access
 *        to the content by the following command:
 *          $ cat /sys/kernel/debug/remoteproc/remoteproc0/trace0
 * @note  When the buffer overflows (2kb by default, configurable.),
 *        the buffer is cleaned by a null character. Consider increasing
 *        VIRTIO_LOG_BUFFER_SIZE if a larger log buffer is needed.
 * @param data: Data to send
 * @param size: size of data
 */
void virtio_log(uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // __OPENAMP_VIRTIO_LOG_H
