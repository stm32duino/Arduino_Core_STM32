/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2018 MCCI Corporation
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
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
 *****************************************************************************/

/**
 * @brief USB virtual serial terminal
 */

#if defined(NO_HWSERIAL) && ! defined(USBCON)

#include <string.h>

#include "wiring.h"

NullSerial SerialNull;


/* NullSerial is always available and instantiated in main.cpp */
void NullSerial::begin(void)
	{
	}

void NullSerial::end(void)
	{
	}

int NullSerial::availableForWrite(void)
	{
	return 1024;
	}

size_t NullSerial::write(uint8_t ch)
	{
	return 1;
	}

size_t NullSerial::write(const uint8_t *buffer, size_t size)
	{
	return size;
	}

int NullSerial::available(void)
	{
	return 0;
	}

int NullSerial::read(void)
	{
	return -1;
	}

int NullSerial::peek(void)
	{
	return -1;
	}

void NullSerial::flush(void)
	{
	}

#endif /* NO_HWSERIAL && ! USBCON */
