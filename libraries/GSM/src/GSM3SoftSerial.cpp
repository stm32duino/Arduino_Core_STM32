/*
This file is part of the GSM3 communications library for Arduino
-- Multi-transport communications platform
-- Fully asynchronous
-- Includes code for the Arduino-Telefonica GSM/GPRS Shield V1
-- Voice calls
-- SMS
-- TCP/IP connections
-- HTTP basic clients

This library has been developed by Telef�nica Digital - PDI -
- Physical Internet Lab, as part as its collaboration with
Arduino and the Open Hardware Community.

September-December 2012

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
https://github.com/BlueVia/Official-Arduino
*/
#include "GSM3SoftSerial.h"
#include "GSM3IO.h"
#include <avr/pgmspace.h>
#include "pins_arduino.h"
//#include <HardwareSerial.h>

#define __XON__ 0x11
#define __XOFF__ 0x13

#define _GSMSOFTSERIALFLAGS_ESCAPED_ 0x01
#define _GSMSOFTSERIALFLAGS_SENTXOFF_ 0x02

GSM3SoftSerial* GSM3SoftSerial::_activeObject=0;

GSM3SoftSerial::GSM3SoftSerial(): cb(this){}

void GSM3SoftSerial::begin(long speed)
{
  _activeObject=this;
  _flags=0;

  uart_emul_init(UART1_EMUL_E,speed);
  uart_emul_attached_handler(&_timer, this->handle_interrupt);
}

void GSM3SoftSerial::close()
{
  _activeObject=0;
  uart_emul_deinit(UART1_EMUL_E);
}

size_t GSM3SoftSerial::write(uint8_t c)
{
	// Characters to be escaped under XON/XOFF control with Quectel
	if(c==0x11)
	{
		this->finalWrite(0x77);
		return this->finalWrite(0xEE);
	}

	if(c==0x13)
	{
		this->finalWrite(0x77);
		return this->finalWrite(0xEC);
	}

	if(c==0x77)
	{
		this->finalWrite(0x77);
		return this->finalWrite(0x88);
	}

	return this->finalWrite(c);
}

size_t GSM3SoftSerial::finalWrite(uint8_t c)
{
	return uart_emul_write(UART1_EMUL_E, c);
}

void GSM3SoftSerial::tunedDelay(uint16_t delay)
{
  delayInsideIT(delay);
}

void GSM3SoftSerial::handle_interrupt()
{
	if(_activeObject)
		_activeObject->recv();
}

void GSM3SoftSerial::recv()
{
  bool firstByte=true;
  byte thisHead;

  uint8_t d = 0;
  bool morebytes=false;
  bool fullbuffer=false;

  if( ((_flags & _GSMSOFTSERIALFLAGS_SENTXOFF_) == _GSMSOFTSERIALFLAGS_SENTXOFF_)
    && (uart_emul_available(UART1_EMUL_E) < UART_RCV_SIZE)
    && (cb.availableBytes() > 6) )
  {
    finalWrite(__XON__);
    _flags &= ~_GSMSOFTSERIALFLAGS_SENTXOFF_;
  } else {
    if(uart_emul_available(UART1_EMUL_E) >= UART_RCV_SIZE) {
        finalWrite(__XOFF__);
        _flags |= _GSMSOFTSERIALFLAGS_SENTXOFF_;
    }

    if(uart_emul_available(UART1_EMUL_E) > 0)
    {
	    do
	    {
		    if(cb.availableBytes() < 6) {
		      fullbuffer=1;
		      if((_flags & _GSMSOFTSERIALFLAGS_SENTXOFF_) != _GSMSOFTSERIALFLAGS_SENTXOFF_) {
		        finalWrite(__XOFF__);
		        _flags |= _GSMSOFTSERIALFLAGS_SENTXOFF_;
		      }
		    }

		    d = uart_emul_read(UART1_EMUL_E);

		    if(keepThisChar(&d))
		    {
			    cb.write(d);
			    if(firstByte)
			    {
				    firstByte=false;
				    thisHead=cb.getTail();
			    }
		    }

		    morebytes=false;

		    if((uart_emul_available(UART1_EMUL_E) > 0) && (fullbuffer == 0))
		      morebytes=true;

	    }while(morebytes);

	    //Just to be sure that thisHead is initialized!
	    if(firstByte)
		    thisHead=cb.getTail();

	    // If we find a line feed, we are at the end of a paragraph
	    // check!
	    if (fullbuffer)
	    {
		    // And... go handle it!
		    if(mgr)
			    mgr->manageMsg(thisHead, cb.getTail());
	    }
	    else if(d==10)
	    {
		    // And... go handle it!
		    if(mgr)
			    mgr->manageMsg(thisHead, cb.getTail());
	    }
	    else if (d==32)
	    {
		    // And... go handle it!
		    if(mgr)
			    mgr->manageMsg(thisHead, cb.getTail());
	    }
    }
  }
}

bool GSM3SoftSerial::keepThisChar(uint8_t* c)
{
	// Horrible things for Quectel XON/XOFF
	// 255 is the answer to a XOFF
	// It comes just once
	if((*c==255)&&(_flags & _GSMSOFTSERIALFLAGS_SENTXOFF_))
	{
		//_flags ^= _GSMSOFTSERIALFLAGS_SENTXOFF_;
		return false;
	}

	// 0x77, w, is the escape character
	if(*c==0x77)
	{
		_flags |= _GSMSOFTSERIALFLAGS_ESCAPED_;
		return false;
	}

	// and these are the escaped codes
	if(_flags & _GSMSOFTSERIALFLAGS_ESCAPED_)
	{
		if(*c==0xEE)
			*c=0x11;
		else if(*c==0xEC)
			*c=0x13;
		else if(*c==0x88)
			*c=0x77;

		_flags ^= _GSMSOFTSERIALFLAGS_ESCAPED_;
		return true;
	}

	return true;
}

void GSM3SoftSerial::spaceAvailable()
{
	// If there is spaceAvailable in the buffer, lets send a XON
	//finalWrite((byte)__XON__);
}


// This is here to avoid problems with Arduino compiler
void GSM3SoftSerialMgr::manageMsg(byte from, byte to){};
