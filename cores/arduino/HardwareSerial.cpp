/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "Arduino.h"
#include "HardwareSerial.h"

#if !defined(NO_HWSERIAL)
#if defined(HAVE_HWSERIAL1) || defined(HAVE_HWSERIAL2) || defined(HAVE_HWSERIAL3) ||\
    defined(HAVE_HWSERIAL4) || defined(HAVE_HWSERIAL5) || defined(HAVE_HWSERIAL6) ||\
    defined(HAVE_HWSERIAL7) || defined(HAVE_HWSERIAL8) || defined(HAVE_HWSERIAL8) ||\
    defined(HAVE_HWSERIAL10)
// SerialEvent functions are weak, so when the user doesn't define them,
// the linker just sets their address to 0 (which is checked below).
#if defined(HAVE_HWSERIAL1)
  HardwareSerial Serial1(USART1);
  void serialEvent1() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL2)
  HardwareSerial Serial2(USART2);
  void serialEvent2() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL3)
  HardwareSerial Serial3(USART3);
  void serialEvent3() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL4)
#if defined(USART4)
  HardwareSerial Serial4(USART4);
#else
  HardwareSerial Serial4(UART4);
#endif
  void serialEvent4() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL5)
#if defined(USART5)
  HardwareSerial Serial5(USART5);
#else
  HardwareSerial Serial5(UART5);
#endif
  void serialEvent5() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL6)
  HardwareSerial Serial6(USART6);
  void serialEvent6() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL7)
#if defined(USART7)
  HardwareSerial Serial7(USART7);
#else
  HardwareSerial Serial7(UART7);
#endif
  void serialEvent7() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL8)
#if defined(USART8)
  HardwareSerial Serial8(USART8);
#else
  HardwareSerial Serial8(UART8);
#endif
  void serialEvent8() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL9)
  HardwareSerial Serial9(UART9);
  void serialEvent9() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL10)
  HardwareSerial Serial10(UART10);
  void serialEvent10() __attribute__((weak));
#endif

void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL1)
  if (serialEvent1 && Serial1.available()) serialEvent1();
#endif
#if defined(HAVE_HWSERIAL2)
  if (serialEvent2 && Serial2.available()) serialEvent2();
#endif
#if defined(HAVE_HWSERIAL3)
  if (serialEvent3 && Serial3.available()) serialEvent3();
#endif
#if defined(HAVE_HWSERIAL4)
  if (serialEvent4 && Serial4.available()) serialEvent4();
#endif
#if defined(HAVE_HWSERIAL5)
  if (serialEvent5 && Serial5.available()) serialEvent5();
#endif
#if defined(HAVE_HWSERIAL6)
  if (serialEvent6 && Serial6.available()) serialEvent6();
#endif
#if defined(HAVE_HWSERIAL7)
  if (serialEvent7 && Serial7.available()) serialEvent7();
#endif
#if defined(HAVE_HWSERIAL8)
  if (serialEvent8 && Serial8.available()) serialEvent8();
#endif
#if defined(HAVE_HWSERIAL9)
  if (serialEvent9 && Serial9.available()) serialEvent9();
#endif
#if defined(HAVE_HWSERIAL10)
  if (serialEventl10 && Serial10.available()) serialEvent10();
#endif
}

// Constructors ////////////////////////////////////////////////////////////////
HardwareSerial::HardwareSerial(PinName _rx, PinName _tx)
{
  _serial.pin_rx = _rx;
  _serial.pin_tx = _tx;
  init();
}

HardwareSerial::HardwareSerial(void* peripheral)
{
// If Serial is defined in variant set
// the Rx/Tx pins for com port if defined
#if defined(Serial) && defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
  if (this == &Serial)
  {
    setRx(PIN_SERIAL_RX);
    setTx(PIN_SERIAL_TX);
  }
  else
#endif
// else get the pins of the first peripheral occurence in PinMap
  {
    _serial.pin_rx = pinmap_pin(peripheral, PinMap_UART_RX);
    _serial.pin_tx = pinmap_pin(peripheral, PinMap_UART_TX);
  }
  init();
}

void HardwareSerial::init(void)
{
  _serial.rx_buff = _rx_buffer;
  _serial.rx_head = 0;
  _serial.rx_tail = 0;
  _serial.tx_buff = _tx_buffer;
  _serial.tx_head = 0;
  _serial.tx_tail = 0;
}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void HardwareSerial::_rx_complete_irq(serial_t* obj)
{
  // No Parity error, read byte and store it in the buffer if there is room
  unsigned char c;

  if (uart_getc(obj, &c) == 0) {

    rx_buffer_index_t i = (unsigned int)(obj->rx_head + 1) % SERIAL_RX_BUFFER_SIZE;

    // if we should be storing the received character into the location
    // just before the tail (meaning that the head would advance to the
    // current location of the tail), we're about to overflow the buffer
    // and so we don't write the character or advance the head.
    if (i != obj->rx_tail) {
      obj->rx_buff[obj->rx_head] = c;
      obj->rx_head = i;
    }
  }
}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

int HardwareSerial::_tx_complete_irq(serial_t* obj)
{
  // If interrupts are enabled, there must be more data in the output
  // buffer. Send the next byte
  obj->tx_tail = (obj->tx_tail + 1) % SERIAL_TX_BUFFER_SIZE;

  if (obj->tx_head == obj->tx_tail) {
    return -1;
  }

  return 0;
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud, byte config)
{
  uint32_t databits = 0;

  _serial.baudrate = (uint32_t)baud;

  // Manage databits
  switch(config & 0x07) {
    case 0x02:
      databits = 6;
      break;
    case 0x04:
      databits = 7;
      break;
    case 0x06:
      databits = 8;
      break;
    default:
      databits = 0;
      break;
  }

  if((config & 0x30) == 0x30) {
    _serial.parity = UART_PARITY_ODD;
    databits++;
  } else if((config & 0x20) == 0x20) {
    _serial.parity = UART_PARITY_EVEN;
    databits++;
  } else {
    _serial.parity = UART_PARITY_NONE;
  }

  if((config & 0x08) == 0x08) {
    _serial.stopbits = UART_STOPBITS_2;
  } else {
    _serial.stopbits = UART_STOPBITS_1;
  }

  switch(databits) {
#ifdef UART_WORDLENGTH_7B
    case 7:
      _serial.databits = UART_WORDLENGTH_7B;
      break;
#endif
    case 8:
      _serial.databits = UART_WORDLENGTH_8B;
      break;
    case 9:
      _serial.databits = UART_WORDLENGTH_9B;
      break;
    default:
	case 0:
      databits = 0;
      break;
  }
  assert(databits!=0);

  uart_init(&_serial);
  uart_attach_rx_callback(&_serial, _rx_complete_irq);
}

void HardwareSerial::end()
{
  // wait for transmission of outgoing data
  flush();

  uart_deinit(&_serial);

  // clear any received data
  _serial.rx_head = _serial.rx_tail;
}

int HardwareSerial::available(void)
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _serial.rx_head - _serial.rx_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int HardwareSerial::peek(void)
{
  if (_serial.rx_head == _serial.rx_tail) {
    return -1;
  } else {
    return _serial.rx_buff[_serial.rx_tail];
  }
}

int HardwareSerial::read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (_serial.rx_head == _serial.rx_tail) {
    return -1;
  } else {
    unsigned char c = _serial.rx_buff[_serial.rx_tail];
    _serial.rx_tail = (rx_buffer_index_t)(_serial.rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

int HardwareSerial::availableForWrite(void)
{
  tx_buffer_index_t head = _serial.tx_head;
  tx_buffer_index_t tail = _serial.tx_tail;

  if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

void HardwareSerial::flush()
{
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (!_written)
    return;

  while((_serial.tx_head != _serial.tx_tail)) {
    // nop, the interrupt handler will free up space for us
  }
  // If we get here, nothing is queued anymore (DRIE is disabled) and
  // the hardware finished tranmission (TXC is set).
}

size_t HardwareSerial::write(uint8_t c)
{
  _written = true;

  tx_buffer_index_t i = (_serial.tx_head + 1) % SERIAL_TX_BUFFER_SIZE;

  // If the output buffer is full, there's nothing for it other than to
  // wait for the interrupt handler to empty it a bit
  while (i == _serial.tx_tail) {
    // nop, the interrupt handler will free up space for us
  }

  _serial.tx_buff[_serial.tx_head] = c;
  _serial.tx_head = i;

  if(!serial_tx_active(&_serial)) {
    uart_attach_tx_callback(&_serial, _tx_complete_irq);
  }

  return 1;
}

void HardwareSerial::setRx(uint32_t _rx) {
  _serial.pin_rx = digitalPinToPinName(_rx);
}

void HardwareSerial::setTx(uint32_t _tx) {
  _serial.pin_tx = digitalPinToPinName(_tx);
}

void HardwareSerial::setRx(PinName _rx) {
  _serial.pin_rx = _rx;
}

void HardwareSerial::setTx(PinName _tx){
  _serial.pin_tx = _tx;
}
#endif // HAVE_HWSERIALx
#endif // !NO_HWSERIAL
