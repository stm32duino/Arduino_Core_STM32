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

#include <stdio.h>
#include "Arduino.h"
#include "HardwareSerial.h"

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
#if defined(HAVE_HWSERIAL1) || defined(HAVE_HWSERIAL2) || defined(HAVE_HWSERIAL3) ||\
  defined(HAVE_HWSERIAL4) || defined(HAVE_HWSERIAL5) || defined(HAVE_HWSERIAL6) ||\
  defined(HAVE_HWSERIAL7) || defined(HAVE_HWSERIAL8) || defined(HAVE_HWSERIAL9) ||\
  defined(HAVE_HWSERIAL10) || defined(HAVE_HWSERIALLP1)
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

  #if defined(HAVE_HWSERIALLP1)
    HardwareSerial SerialLP1(LPUART1);
    void serialEventLP1() __attribute__((weak));
  #endif
#endif // HAVE_HWSERIALx

// Constructors ////////////////////////////////////////////////////////////////
HardwareSerial::HardwareSerial(uint32_t _rx, uint32_t _tx)
{
  init(digitalPinToPinName(_rx), digitalPinToPinName(_tx));
}

HardwareSerial::HardwareSerial(PinName _rx, PinName _tx)
{
  init(_rx, _tx);
}

HardwareSerial::HardwareSerial(void *peripheral, HalfDuplexMode_t halfDuplex)
{
  // If PIN_SERIALy_RX is not defined assume half-duplex
  _serial.pin_rx = NC;
  // If Serial is defined in variant set
  // the Rx/Tx pins for com port if defined
#if defined(Serial) && defined(PIN_SERIAL_TX)
  if ((void *)this == (void *)&Serial) {
#if defined(PIN_SERIAL_RX)
    setRx(PIN_SERIAL_RX);
#endif
    setTx(PIN_SERIAL_TX);
  } else
#endif
#if defined(PIN_SERIAL1_TX) && defined(USART1_BASE)
    if (peripheral == USART1) {
#if defined(PIN_SERIAL1_RX)
      setRx(PIN_SERIAL1_RX);
#endif
      setTx(PIN_SERIAL1_TX);
    } else
#endif
#if defined(PIN_SERIAL2_TX) && defined(USART2_BASE)
      if (peripheral == USART2) {
#if defined(PIN_SERIAL2_RX)
        setRx(PIN_SERIAL2_RX);
#endif
        setTx(PIN_SERIAL2_TX);
      } else
#endif
#if defined(PIN_SERIAL3_TX) && defined(USART3_BASE)
        if (peripheral == USART3) {
#if defined(PIN_SERIAL3_RX)
          setRx(PIN_SERIAL3_RX);
#endif
          setTx(PIN_SERIAL3_TX);
        } else
#endif
#if defined(PIN_SERIAL4_TX) &&\
   (defined(USART4_BASE) || defined(UART4_BASE))
#if defined(USART4_BASE)
          if (peripheral == USART4)
#elif defined(UART4_BASE)
          if (peripheral == UART4)
#endif
          {
#if defined(PIN_SERIAL4_RX)
            setRx(PIN_SERIAL4_RX);
#endif
            setTx(PIN_SERIAL4_TX);
          } else
#endif
#if defined(PIN_SERIAL5_TX) &&\
   (defined(USART5_BASE) || defined(UART5_BASE))
#if defined(USART5_BASE)
            if (peripheral == USART5)
#elif defined(UART5_BASE)
            if (peripheral == UART5)
#endif
            {
#if defined(PIN_SERIAL5_RX)
              setRx(PIN_SERIAL5_RX);
#endif
              setTx(PIN_SERIAL5_TX);
            } else
#endif
#if defined(PIN_SERIAL6_TX) && defined(USART6_BASE)
              if (peripheral == USART6) {
#if defined(PIN_SERIAL6_RX)
                setRx(PIN_SERIAL6_RX);
#endif
                setTx(PIN_SERIAL6_TX);
              } else
#endif
#if defined(PIN_SERIAL7_TX) &&\
   (defined(USART7_BASE) || defined(UART7_BASE))
#if defined(USART7_BASE)
                if (peripheral == USART7)
#elif defined(UART7_BASE)
                if (peripheral == UART7)
#endif
                {
#if defined(PIN_SERIAL7_RX)
                  setRx(PIN_SERIAL7_RX);
#endif
                  setTx(PIN_SERIAL7_TX);
                } else
#endif
#if defined(PIN_SERIAL8_TX) &&\
   (defined(USART8_BASE) || defined(UART8_BASE))
#if defined(USART8_BASE)
                  if (peripheral == USART8)
#elif defined(UART8_BASE)
                  if (peripheral == UART8)
#endif
                  {
#if defined(PIN_SERIAL8_RX)
                    setRx(PIN_SERIAL8_RX);
#endif
                    setTx(PIN_SERIAL8_TX);
                  } else
#endif
#if defined(PIN_SERIAL9_TX) && defined(UART9)
                    if (peripheral == UART9) {
#if defined(PIN_SERIAL9_RX)
                      setRx(PIN_SERIAL9_RX);
#endif
                      setTx(PIN_SERIAL9_TX);
                    } else
#endif
#if defined(PIN_SERIAL10_TX) && defined(UART10)
                      if (peripheral == UART10) {
#if defined(PIN_SERIAL10_RX)
                        setRx(PIN_SERIAL10_RX);
#endif
                        setTx(PIN_SERIAL10_TX);
                      } else
#endif
#if defined(PIN_SERIALLP1_TX) && defined(LPUART1_BASE)
                        if (peripheral == LPUART1) {
#if defined(PIN_SERIALLP1_RX)
                          setRx(PIN_SERIALLP1_RX);
#endif
                          setTx(PIN_SERIALLP1_TX);
                        } else
#endif
                          // else get the pins of the first peripheral occurence in PinMap
                        {
                          _serial.pin_rx = pinmap_pin(peripheral, PinMap_UART_RX);
                          _serial.pin_tx = pinmap_pin(peripheral, PinMap_UART_TX);
                        }
  if (halfDuplex == HALF_DUPLEX_ENABLED) {
    _serial.pin_rx = NC;
  }
  init(_serial.pin_rx, _serial.pin_tx);
}

HardwareSerial::HardwareSerial(uint32_t _rxtx)
{
  init(NC, digitalPinToPinName(_rxtx));
}

HardwareSerial::HardwareSerial(PinName _rxtx)
{
  init(NC, _rxtx);
}

void HardwareSerial::init(PinName _rx, PinName _tx)
{
  if (_rx == _tx) {
    _serial.pin_rx = NC;
  } else {
    _serial.pin_rx = _rx;
  }
  _serial.pin_tx = _tx;
  _serial.rx_buff = _rx_buffer;
  _serial.rx_head = 0;
  _serial.rx_tail = 0;
  _serial.tx_buff = _tx_buffer;
  _serial.tx_head = 0;
  _serial.tx_tail = 0;
}

void HardwareSerial::configForLowPower(void)
{
#if defined(HAL_PWR_MODULE_ENABLED) && defined(UART_IT_WUF)
  // Reconfigure properly Serial instance to use HSI as clock source
  end();
  uart_config_lowpower(&_serial);
  begin(_baud, _config);
#endif
}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void HardwareSerial::_rx_complete_irq(serial_t *obj)
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

int HardwareSerial::_tx_complete_irq(serial_t *obj)
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
  uint32_t stopbits = 0;
  uint32_t parity = 0;

  _baud = baud;
  _config = config;

  // Manage databits
  switch (config & 0x07) {
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

  if ((config & 0x30) == 0x30) {
    parity = UART_PARITY_ODD;
    databits++;
  } else if ((config & 0x20) == 0x20) {
    parity = UART_PARITY_EVEN;
    databits++;
  } else {
    parity = UART_PARITY_NONE;
  }

  if ((config & 0x08) == 0x08) {
    stopbits = UART_STOPBITS_2;
  } else {
    stopbits = UART_STOPBITS_1;
  }

  switch (databits) {
#ifdef UART_WORDLENGTH_7B
    case 7:
      databits = UART_WORDLENGTH_7B;
      break;
#endif
    case 8:
      databits = UART_WORDLENGTH_8B;
      break;
    case 9:
      databits = UART_WORDLENGTH_9B;
      break;
    default:
    case 0:
      Error_Handler();
      break;
  }

  uart_init(&_serial, (uint32_t)baud, databits, parity, stopbits);
  enableHalfDuplexRx();
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
  enableHalfDuplexRx();
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

  if (head >= tail) {
    return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  }
  return tail - head - 1;
}

void HardwareSerial::flush()
{
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (!_written) {
    return;
  }

  while ((_serial.tx_head != _serial.tx_tail)) {
    // nop, the interrupt handler will free up space for us
  }
  // If we get here, nothing is queued anymore (DRIE is disabled) and
  // the hardware finished tranmission (TXC is set).
}

size_t HardwareSerial::write(uint8_t c)
{
  _written = true;
  if (isHalfDuplex()) {
    if (_rx_enabled) {
      _rx_enabled = false;
      uart_enable_tx(&_serial);
    }
  }

  tx_buffer_index_t i = (_serial.tx_head + 1) % SERIAL_TX_BUFFER_SIZE;

  // If the output buffer is full, there's nothing for it other than to
  // wait for the interrupt handler to empty it a bit
  while (i == _serial.tx_tail) {
    // nop, the interrupt handler will free up space for us
  }

  _serial.tx_buff[_serial.tx_head] = c;
  _serial.tx_head = i;

  if (!serial_tx_active(&_serial)) {
    uart_attach_tx_callback(&_serial, _tx_complete_irq);
  }

  return 1;
}

void HardwareSerial::setRx(uint32_t _rx)
{
  _serial.pin_rx = digitalPinToPinName(_rx);
}

void HardwareSerial::setTx(uint32_t _tx)
{
  _serial.pin_tx = digitalPinToPinName(_tx);
}

void HardwareSerial::setRx(PinName _rx)
{
  _serial.pin_rx = _rx;
}

void HardwareSerial::setTx(PinName _tx)
{
  _serial.pin_tx = _tx;
}

void HardwareSerial::setHalfDuplex(void)
{
  _serial.pin_rx = NC;
}

bool HardwareSerial::isHalfDuplex(void) const
{
  return _serial.pin_rx == NC;
}

void HardwareSerial::enableHalfDuplexRx(void)
{
  if (isHalfDuplex()) {
    // In half-duplex mode we have to wait for all TX characters to
    // be transmitted before we can receive data.
    flush();
    if (!_rx_enabled) {
      _rx_enabled = true;
      uart_enable_rx(&_serial);
    }
  }
}

#endif // HAL_UART_MODULE_ENABLED && !HAL_UART_MODULE_ONLY
