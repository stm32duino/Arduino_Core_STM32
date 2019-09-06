/*
 * SoftwareSerial.cpp (formerly NewSoftSerial.cpp)
 *
 * Multi-instance software serial library for Arduino/Wiring
 * -- Interrupt-driven receive and other improvements by ladyada
 *    (http://ladyada.net)
 * -- Tuning, circular buffer, derivation from class Print/Stream,
 *    multi-instance support, porting to 8MHz processors,
 *    various optimizations, PROGMEM delay tables, inverse logic and
 *    direct port writing by Mikal Hart (http://www.arduiniana.org)
 * -- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
 * -- 20MHz processor support by Garrett Mace (http://www.macetech.com)
 * -- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)
 * -- STM32 support by Armin van der Togt
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * The latest version of this library can always be found at
 * http://arduiniana.org.
 */

//
// Includes
//
#include <stdint.h>
#include <stdarg.h>

#include <wiring_digital.h>
#include <time.h>

#include <Arduino.h>
#include "SoftwareSerial.h"
#include <HardwareTimer.h>
#include <stm32_def.h>
#include <digital_io.h>

#define OVERSAMPLE 3
// defined in bit-periods
#define HALFDUPLEX_SWITCH_DELAY 5
// It's best to define TIMER_SERIAL in variant.h. If not defined, we choose one here
// The order is based on (lack of) features and compare channels, we choose the simplest available
// because we only need an update interrupt
#if !defined(TIMER_SERIAL)
#if defined (TIM18_BASE)
#define TIMER_SERIAL TIM18
#elif defined (TIM7_BASE)
#define TIMER_SERIAL TIM7
#elif defined (TIM6_BASE)
#define TIMER_SERIAL TIM6
#elif defined (TIM22_BASE)
#define TIMER_SERIAL TIM22
#elif defined (TIM21_BASE)
#define TIMER_SERIAL TIM21
#elif defined (TIM17_BASE)
#define TIMER_SERIAL TIM17
#elif defined (TIM16_BASE)
#define TIMER_SERIAL TIM16
#elif defined (TIM15_BASE)
#define TIMER_SERIAL TIM15
#elif defined (TIM14_BASE)
#define TIMER_SERIAL TIM14
#elif defined (TIM13_BASE)
#define TIMER_SERIAL TIM13
#elif defined (TIM11_BASE)
#define TIMER_SERIAL TIM11
#elif defined (TIM10_BASE)
#define TIMER_SERIAL TIM10
#elif defined (TIM12_BASE)
#define TIMER_SERIAL TIM12
#elif defined (TIM19_BASE)
#define TIMER_SERIAL TIM19
#elif defined (TIM9_BASE)
#define TIMER_SERIAL TIM9
#elif defined (TIM5_BASE)
#define TIMER_SERIAL TIM5
#elif defined (TIM4_BASE)
#define TIMER_SERIAL TIM4
#elif defined (TIM3_BASE)
#define TIMER_SERIAL TIM3
#elif defined (TIM2_BASE)
#define TIMER_SERIAL TIM2
#elif defined (TIM20_BASE)
#define TIMER_SERIAL TIM20
#elif defined (TIM8_BASE)
#define TIMER_SERIAL TIM8
#elif defined (TIM1_BASE)
#define TIMER_SERIAL TIM1
#else
#error No suitable timer found for SoftwareSerial, define TIMER_SERIAL in variant.h
#endif
#endif
//
// Statics
//
HardwareTimer SoftwareSerial::timer(TIMER_SERIAL);
SoftwareSerial *SoftwareSerial::active_listener = nullptr;
SoftwareSerial *volatile SoftwareSerial::active_out = nullptr;
SoftwareSerial *volatile SoftwareSerial::active_in = nullptr;
int32_t SoftwareSerial::tx_tick_cnt = 0;
int32_t volatile SoftwareSerial::rx_tick_cnt = 0;
uint32_t SoftwareSerial::tx_buffer = 0;
int32_t SoftwareSerial::tx_bit_cnt = 0;
uint32_t SoftwareSerial::rx_buffer = 0;
int32_t SoftwareSerial::rx_bit_cnt = -1;
uint32_t SoftwareSerial::cur_speed = 0;
uint8_t SoftwareSerial::rx_high_count = 0;
uint8_t SoftwareSerial::rx_low_count = 0;

//
// Private methods
//

void SoftwareSerial::setSpeed(uint32_t speed)
{
  if (speed != cur_speed) {
    timer.pause();
    if (speed != 0) {
      // Disable the timer
      uint32_t clock_rate, cmp_value;
      // Get timer clock
      clock_rate = timer.getTimerClkFreq();
      int pre = 1;
      // Calculate prescale an compare value
      do {
        cmp_value = clock_rate / (speed * OVERSAMPLE);
        if (cmp_value >= UINT16_MAX) {
          clock_rate = clock_rate / 2;
          pre *= 2;
        }
      } while (cmp_value >= UINT16_MAX);
      timer.setPrescaleFactor(pre);
      timer.setOverflow(cmp_value);
      timer.setCount(0);
      timer.attachInterrupt(&handleInterrupt);
      timer.resume();
    } else {
      timer.detachInterrupt();
    }
    cur_speed = speed;
  }
}

// This function sets the current object as the "listening"
// one and returns true if it replaces another
bool SoftwareSerial::listen()
{
  if (_receivePin >= 0) {
    // wait for any transmit to complete as we may change speed
    while (active_out)
      ;
    if (active_listener) {
      active_listener->stopListening();
    }
    rx_tick_cnt = 0;
    rx_bit_cnt = -1;
    setSpeed(_speed);
    active_listener = this;
    if (!_half_duplex) {
      active_in = this;
    }
    return true;
  }
  return false;
}

// Stop listening. Returns true if we were actually listening.
bool SoftwareSerial::stopListening()
{
  if (active_listener == this) {
    // wait for any output to complete
    while (active_out)
      ;
    if (_half_duplex) {
      setRXTX(false);
    }
    active_listener = nullptr;
    active_in = nullptr;
    // turn off ints
    setSpeed(0);
    return true;
  }
  return false;
}

inline void SoftwareSerial::setTX()
{
  if (_inverse_logic) {
    LL_GPIO_ResetOutputPin(_transmitPinPort, _transmitPinNumber);
  } else {
    LL_GPIO_SetOutputPin(_transmitPinPort, _transmitPinNumber);
  }
  pinMode(_transmitPin, OUTPUT);
}

inline void SoftwareSerial::setRX()
{
  if (_receivePin > 0) {
    pinMode(_receivePin, _inverse_logic ? INPUT_PULLDOWN : INPUT_PULLUP); // pullup for normal logic!
  }
}

inline void SoftwareSerial::setRXTX(bool input)
{
  if (_half_duplex) {
    if (input) {
      if (active_in != this) {
        setRX();
        rx_bit_cnt = -1;
        rx_tick_cnt = 1;
        active_in = this;
      }
    } else {
      if (active_in == this) {
        setTX();
        active_in = nullptr;
      }
    }
  }
}

inline void SoftwareSerial::send()
{
  if (--tx_tick_cnt < 0) {
    if (tx_bit_cnt++ < 10) {
      // send data (including start and stop bits)
      if (tx_buffer & 1) {
        LL_GPIO_SetOutputPin(_transmitPinPort, _transmitPinNumber);
      } else {
        LL_GPIO_ResetOutputPin(_transmitPinPort, _transmitPinNumber);

      }
      tx_buffer >>= 1;
      tx_tick_cnt = OVERSAMPLE - 1; // first sample sent, OVERSAMPLE - 1 more samples to go
    } else {
      tx_tick_cnt = 0;
      if (_output_pending || !(_half_duplex && active_listener == this)) {
        active_out = nullptr;
        // When in half-duplex mode, we wait for HALFDUPLEX_SWITCH_DELAY bit-periods after the byte has
        // been transmitted before allowing the switch to RX mode
      } else if (tx_bit_cnt > 10 + HALFDUPLEX_SWITCH_DELAY * OVERSAMPLE) {
        pinMode(_receivePin, _inverse_logic ? INPUT_PULLDOWN : INPUT_PULLUP); // pullup for normal logic!
        rx_bit_cnt = -1;
        rx_tick_cnt = 1;
        active_in = this;
        active_out = nullptr;
      }
    }
  }
}

//
// The receive routine called by the interrupt handler
//
inline void SoftwareSerial::recv()
{
  if (LL_GPIO_IsInputPinSet(_receivePinPort, _receivePinNumber)) {
	  rx_high_count++;
  }
  else {
	  rx_low_count++;
  }
  if (--rx_tick_cnt < 0) {
    bool inbit = (rx_high_count > rx_low_count) ^ _inverse_logic;
    rx_high_count = 0;
    rx_low_count = 0;
    if (rx_bit_cnt == -1) {
      // waiting for start bit
      if (!inbit) {
        // got start bit
        rx_bit_cnt = 0;
        rx_tick_cnt = OVERSAMPLE - 1; // First sample taken, we will take OVERSAMPLE - 1 more samples
        rx_buffer = 0;
      } else {
        rx_tick_cnt = 0;
      }
    } else if (rx_bit_cnt >= 8) {
      if (inbit) {
        // stop bit read complete add to buffer
        uint8_t next = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
        if (next != _receive_buffer_head) {
          // save new data in buffer: tail points to where byte goes
          _receive_buffer[_receive_buffer_tail] = rx_buffer; // save new byte
          _receive_buffer_tail = next;
        } else {
          _buffer_overflow = true;
        }
      }
      rx_tick_cnt = 0;
      rx_bit_cnt = -1;
    } else {
      // data bits
      rx_buffer >>= 1;
      if (inbit) {
        rx_buffer |= 0x80;
      }
      rx_bit_cnt++;
      rx_tick_cnt = OVERSAMPLE - 1; // First sample taken, we will take OVERSAMPLE - 1 more samples
    }
  }
}

//
// Interrupt handling
//

/* static */
inline void SoftwareSerial::handleInterrupt(HardwareTimer *timer)
{
  if (active_in) {
    active_in->recv();
  }
  if (active_out) {
    active_out->send();
  }
}
//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint16_t receivePin, uint16_t transmitPin, bool inverse_logic /* = false */) :
  _receivePin(receivePin),
  _transmitPin(transmitPin),
  _receivePinPort(digitalPinToPort(receivePin)),
  _receivePinNumber(STM_LL_GPIO_PIN(digitalPinToPinName(receivePin))),
  _transmitPinPort(digitalPinToPort(transmitPin)),
  _transmitPinNumber(STM_LL_GPIO_PIN(digitalPinToPinName(transmitPin))),
  _speed(0),
  _buffer_overflow(false),
  _inverse_logic(inverse_logic),
  _half_duplex(receivePin == transmitPin),
  _output_pending(0),
  _receive_buffer_tail(0),
  _receive_buffer_head(0)
{
  /* Enable GPIO clock for tx and rx pin*/
  set_GPIO_Port_Clock(STM_PORT(digitalPinToPinName(transmitPin)));
  set_GPIO_Port_Clock(STM_PORT(digitalPinToPinName(receivePin)));
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
  end();
}

//
// Public methods
//

void SoftwareSerial::begin(long speed)
{
#ifdef FORCE_BAUD_RATE
  speed = FORCE_BAUD_RATE;
#endif
  _speed = speed;
  if (!_half_duplex) {
    setTX();
    setRX();
  } else {
    setTX();
  }

  listen();
}

void SoftwareSerial::end()
{
  stopListening();
}

// Read data from buffer
int SoftwareSerial::read()
{
  // Empty buffer?
  if (_receive_buffer_head == _receive_buffer_tail) {
    return -1;
  }

  // Read from "head"
  uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
  _receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
  return d;
}

int SoftwareSerial::available()
{
  return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
}

size_t SoftwareSerial::write(uint8_t b)
{
  // wait for previous transmit to complete
  _output_pending = 1;
  while (active_out)
    ;
  // add start and stop bits.
  tx_buffer = b << 1 | 0x200;
  if (_inverse_logic) {
    tx_buffer = ~tx_buffer;
  }
  tx_bit_cnt = 0;
  tx_tick_cnt = OVERSAMPLE;
  setSpeed(_speed);
  if (_half_duplex) {
    setRXTX(false);
  }
  _output_pending = 0;
  // make us active
  active_out = this;
  return 1;
}

void SoftwareSerial::flush()
{
  noInterrupts();
  _receive_buffer_head = _receive_buffer_tail = 0;
  interrupts();
}

int SoftwareSerial::peek()
{
  // Empty buffer?
  if (_receive_buffer_head == _receive_buffer_tail) {
    return -1;
  }

  // Read from "head"
  return _receive_buffer[_receive_buffer_head];
}
