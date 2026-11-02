/*
 * SoftwareSerial.h (formerly NewSoftSerial.h)
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

#ifndef SOFTWARESERIAL_H
#define SOFTWARESERIAL_H

#include <Arduino.h>

/******************************************************************************
* Definitions
******************************************************************************/

/**
 * @brief Size of the receive buffer in bytes.
 */
#define _SS_MAX_RX_BUFF 64

/**
 * @brief Software serial (UART) emulation on any pair of GPIO pins, driven by a timer interrupt.
 * @note  When the receive and transmit pins are the same, the instance works in half-duplex mode.
 */
class SoftwareSerial : public Stream {
  private:
    // per object data
    pin_size_t _receivePin;
    pin_size_t _transmitPin;
    GPIO_TypeDef *_receivePinPort;
    uint32_t _receivePinNumber;
    GPIO_TypeDef *_transmitPinPort;
    uint32_t _transmitPinNumber;
    uint32_t _speed;

    uint16_t _buffer_overflow: 1;
    uint16_t _inverse_logic: 1;
    uint16_t _half_duplex: 1;
    uint16_t _output_pending: 1;

    unsigned char _receive_buffer[_SS_MAX_RX_BUFF];
    volatile uint8_t _receive_buffer_tail;
    volatile uint8_t _receive_buffer_head;

    uint32_t delta_start = 0;

    // static data
    static bool initialised;
    static HardwareTimer timer;
    static SoftwareSerial *active_listener;
    static SoftwareSerial *volatile active_out;
    static SoftwareSerial *volatile active_in;
    static int32_t tx_tick_cnt;
    static volatile int32_t rx_tick_cnt;
    static uint32_t tx_buffer;
    static int32_t tx_bit_cnt;
    static uint32_t rx_buffer;
    static int32_t rx_bit_cnt;
    static uint32_t cur_speed;

    /**
     * @brief Timer interrupt handler for the transmit side: send the next TX bit.
     */
    void send();
    /**
     * @brief Timer interrupt handler for the receive side: sample the next RX bit.
     */
    void recv();
    /**
     * @brief Configure the transmit pin as output, idle high (low if inverse
     *        logic is used).
     */
    void setTX();
    /**
     * @brief Configure the receive pin as input with pull-up (pull-down if
     *        inverse logic is used).
     */
    void setRX();
    /**
     * @brief Configure the timer for the given baud rate, or stop it when speed is 0.
     * @param speed Baud rate in bits per second. 0 disables the timer interrupt.
     */
    void setSpeed(uint32_t speed);
    /**
     * @brief Switch the pin between receive and transmit in half-duplex mode.
     * @param input true to switch to receive, false to switch to transmit.
     */
    void setRXTX(bool input);
    /**
     * @brief Timer interrupt handler dispatching to the active receiver and transmitter.
     */
    static void handleInterrupt();

  public:
    /**
     * @brief Create a software serial instance on the given pins.
     * @param receivePin Pin used to receive data (RX).
     * @param transmitPin Pin used to transmit data (TX). Use the same pin as
     *        receivePin for half-duplex mode.
     * @param inverse_logic Optional, true to invert the logic level of the
     *        data. Default: false.
     */
    SoftwareSerial(pin_size_t receivePin, pin_size_t transmitPin, bool inverse_logic = false);
    /**
     * @brief Stop this instance: stop listening and disable its timer interrupt.
     */
    virtual ~SoftwareSerial();
    /**
     * @brief Set the baud rate and initialize the pins. Starts listening unless
     *        the instance is half-duplex.
     * @param speed Baud rate in bits per second. If FORCE_BAUD_RATE is defined,
     *        its value is used instead.
     */
    void begin(long speed);
    /**
     * @brief Set this instance as the listening one. Only one instance can
     *        listen at a time.
     *
     * If another instance was listening, it is stopped and replaced by this one.
     * @return true if this instance became the listening one (replacing another
     *         one if any),
     *         false if it was already listening.
     */
    bool listen();
    /**
     * @brief Stop this instance: stop listening and disable the timer interrupt.
     */
    void end();
    /**
     * @brief Check if this instance is the active listener.
     * @return true if this instance is listening, false otherwise.
     */
    bool isListening()
    {
      return active_listener == this;
    }
    /**
     * @brief Stop listening on this instance. Waits for any pending output to complete.
     * @return true if this instance was actually listening, false otherwise.
     */
    bool stopListening();
    /**
     * @brief Check whether a byte was dropped because the receive buffer was
     *        full. Clears the flag.
     * @return true if an overflow occurred since the last call, false otherwise.
     */
    bool overflow()
    {
      bool ret = _buffer_overflow;
      if (ret) {
        _buffer_overflow = false;
      }
      return ret;
    }
    /**
     * @brief Get the next received byte without removing it from the receive buffer.
     * @return The next byte, or -1 if the receive buffer is empty.
     */
    int peek();

    /**
     * @brief Send one byte. Waits for any previous transmission to complete.
     * @param byte Byte to send.
     * @return Always 1.
     */
    virtual size_t write(uint8_t byte);
    /**
     * @brief Read the next byte from the receive buffer.
     * @return The byte read, or -1 if the receive buffer is empty.
     */
    virtual int read();
    /**
     * @brief Get the number of bytes in the receive buffer.
     * @return Number of bytes available to read.
     */
    virtual int available();
    /**
     * @brief Clear the receive buffer and wait for any pending transmission to complete.
     */
    virtual void flush();
    /**
     * @brief Allow the instance to be used in a boolean context.
     * @return Always true.
     */
    operator bool()
    {
      return true;
    }

    /**
     * @brief Set the priority of the timer interrupt shared by all software serial instances.
     * @param preemptPriority Preemption priority of the interrupt.
     * @param subPriority Sub-priority of the interrupt.
     */
    static void setInterruptPriority(uint32_t preemptPriority, uint32_t subPriority);

    using Print::write;
};

#endif // SOFTWARESERIAL_H
