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
 * @brief Wirish virtual serial port
 */

#ifndef _NULL_SERIAL_H_
#define _NULL_SERIAL_H_

#if defined(NO_HWSERIAL) && ! defined(USBCON)

#include "Stream.h"

/**
 * @brief Virtual serial terminal.
 */
class NullSerial : public Stream
	{
public:
	NullSerial(void) {};

	void begin(void);
	void begin(unsigned long baud) { begin(); }
	void end(void);

	virtual int available(void);
	virtual int peek(void);
	virtual void flush(void);
	virtual int read(void);

	int availableForWrite(void);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buffer, size_t size);
	inline size_t write(unsigned long n) { return write((uint8_t)n); }
	inline size_t write(long n) { return write((uint8_t)n); }
	inline size_t write(unsigned int n) { return write((uint8_t)n); }
	inline size_t write(int n) { return write((uint8_t)n); }
	using Print::write;

	operator bool() { return true; }
	bool dtr(void) { return true; }
	};

extern NullSerial SerialNull;

#define Serial SerialNull

#endif /* NO_HWSERIAL && ! USBCON */

#endif /* _NULL_SERIAL_H_ */
