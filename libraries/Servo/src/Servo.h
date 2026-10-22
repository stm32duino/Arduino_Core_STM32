/*
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
  Copyright (c) 2009 Michael Margolis.  All right reserved.

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
*/

/*
  A servo is activated by creating an instance of the Servo class passing
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two
  timers, 48 servos will use four.
  The sequence used to seize timers is defined in timers.h

  The methods are:

    Servo - Class for manipulating servo motors connected to Arduino pins.

    attach(pin )  - Attaches a servo motor to an i/o pin.
    attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
    default min is 544, max is 2400

    write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
    writeMicroseconds() - Sets the servo pulse width in microseconds
    read()      - Gets the last written servo pulse width as an angle between 0 and 180.
    readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
    attached()  - Returns true if there is a servo attached.
    detach()    - Stops an attached servos from pulsing its i/o pin.
 */

#ifndef Servo_h
#define Servo_h

#include "api/Common.h"
#include <inttypes.h>

/*
 * Defines for 16 bit timers used with  Servo library
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the current board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 */

#include "stm32/ServoTimers.h"

#define Servo_VERSION           2     // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index


typedef struct  {
  uint8_t nbr;            // a pin number from 0 to 255
  uint8_t isActive;       // true if this channel is enabled, pin not pulsed if false
} ServoPin_t   ;

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;

/**
 * @brief Servo motor controller. Each instance drives one servo on a pin, using a shared 16 bit timer.
 */
class Servo {
  public:
    /**
     * @brief Create a servo instance and assign it a channel index. If no channel is left, the instance is invalid.
     */
    Servo();
    /**
     * @brief Attach the servo to a pin, using the default min and max pulse widths.
     * @param pin Pin number to attach the servo to.
     * @param value Initial value, as an angle in degrees or a pulse width in microseconds. Default: DEFAULT_PULSE_WIDTH.
     * @return Index of the channel used, or INVALID_SERVO if no channel is available.
     */
    uint8_t attach(pin_size_t pin, int value = DEFAULT_PULSE_WIDTH);
    /**
     * @brief Attach the servo to a pin, with custom min and max pulse widths.
     * @param pin Pin number to attach the servo to.
     * @param min Pulse width in microseconds for 0 degrees. Default: MIN_PULSE_WIDTH.
     * @param max Pulse width in microseconds for 180 degrees. Default: MAX_PULSE_WIDTH.
     * @param value Initial value, as an angle in degrees or a pulse width in microseconds. Default: DEFAULT_PULSE_WIDTH.
     * @return Index of the channel used, or INVALID_SERVO if no channel is available.
     */
    uint8_t attach(pin_size_t pin, int min, int max, int value = DEFAULT_PULSE_WIDTH);
    /**
     * @brief Stop the servo from pulsing its pin. The timer is paused when no servo is active.
     */
    void detach();
    /**
     * @brief Set the servo position.
     * @param value Angle in degrees (0 to 180) if less than MIN_PULSE_WIDTH, otherwise a pulse width in microseconds.
     */
    void write(int value);
    /**
     * @brief Set the servo pulse width. The value is clamped to the min and max pulse widths of this servo.
     * @param value Pulse width in microseconds.
     */
    void writeMicroseconds(int value);
    /**
     * @brief Get the last written position.
     * @return Current position as an angle between 0 and 180 degrees.
     */
    int read();
    /**
     * @brief Get the last written pulse width.
     * @return Current pulse width in microseconds.
     */
    int readMicroseconds();
    /**
     * @brief Check if the servo is attached.
     * @return true if the servo is attached, false otherwise.
     */
    bool attached();
  private:
    uint8_t servoIndex;               // index into the channel data for this servo
    int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
    int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
};

#endif
