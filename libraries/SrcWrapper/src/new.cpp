/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdlib.h>

/**
 * @brief Allocate memory for a single object (C++ new).
 * @param size Number of bytes to allocate.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void *operator new (size_t size)
{
  return malloc(size);
}

/**
 * @brief Allocate memory for an array (C++ new[]).
 * @param size Number of bytes to allocate.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void *operator new[](size_t size)
{
  return malloc(size);
}

/**
 * @brief Free memory allocated by operator new.
 * @param ptr Pointer to the memory to free.
 */
void operator delete (void *ptr)
{
  free(ptr);
}

/**
 * @brief Free memory allocated by operator new[].
 * @param ptr Pointer to the memory to free.
 */
void operator delete[](void *ptr)
{
  free(ptr);
}

/**
 * @brief Free memory allocated by sized operator new.
 * @param ptr Pointer to the memory to free.
 * @param size Size of the allocation (unused).
 */
void operator delete (void *ptr, size_t /*size*/)
{
  free(ptr);
}

/**
 * @brief Free memory allocated by sized operator new[].
 * @param ptr Pointer to the memory to free.
 * @param size Size of the allocation (unused).
 */
void operator delete[](void *ptr, size_t /*size*/)
{
  free(ptr);
}
