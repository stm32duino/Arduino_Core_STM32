/*
  Copyright (c) 2017 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>
#include <Servo.h>

static servo_t servos[MAX_SERVOS];                         // static array of servo structures
static volatile int8_t timerChannel[_Nbr_16timers ];       // counter for the servo being pulsed for each timer (or -1 if refresh interval)

uint8_t ServoCount = 0;                                    // the total number of attached servos
stimer_t _timer;

// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER))   // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)                       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)                     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])                           // macro to access servo class by timer and channel

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)   // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)   // maximum value in uS for this servo

#define TIMER_ID(_timer) ((timer_id_e)(_timer))
#define SERVO_TIMER(_timer_id)  ((timer16_Sequence_t)(_timer_id))

/************ static functions common to all instances ***********************/
static void ServoIrqHandle(stimer_t *obj, uint32_t channel)
{
  uint8_t timer_id = obj->idx;

  if( timerChannel[SERVO_TIMER(timer_id)] < 0 ) {
    setTimerCounter(obj, 0); // channel set to -1 indicated that refresh interval completed so reset the timer
  }
  else{
    if(SERVO_INDEX(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]) < ServoCount &&
       SERVO(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]).Pin.isActive == true)
    {
      digitalWrite(SERVO(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]).Pin.nbr,LOW); // pulse this channel low if activated
    }
  }

  timerChannel[SERVO_TIMER(timer_id)]++;    // increment to the next channel
  if( SERVO_INDEX(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]) < ServoCount &&
      timerChannel[SERVO_TIMER(timer_id)] < SERVOS_PER_TIMER ) {
    if(SERVO(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]).Pin.isActive == true) {     // check if activated
      digitalWrite( SERVO(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]).Pin.nbr,HIGH); // its an active channel so pulse it high
    }
    setCCRRegister(obj, channel, getTimerCounter(obj) + SERVO(SERVO_TIMER(timer_id),timerChannel[SERVO_TIMER(timer_id)]).ticks);
  }
  else {
    // finished all channels so wait for the refresh period to expire before starting over
    if( getTimerCounter(obj) + 4 < REFRESH_INTERVAL ) {  // allow a few ticks to ensure the next OCR1A not missed
      setCCRRegister(obj, channel, (unsigned int)REFRESH_INTERVAL);
    } else {
      setCCRRegister(obj, channel, getTimerCounter(obj) + 4);  // at least REFRESH_INTERVAL has elapsed
    }
    timerChannel[SERVO_TIMER(timer_id)] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
  }
}

static void initISR(stimer_t *obj)
{
  /*
   * Timer clock set by default at 1us.
   * Period set to REFRESH_INTERVAL*3
   * Default pulse width set to DEFAULT_PULSE_WIDTH
   */
  TimerPulseInit(obj, REFRESH_INTERVAL*3, DEFAULT_PULSE_WIDTH, ServoIrqHandle);
}

static void finISR(stimer_t *obj)
{
  TimerPulseDeinit(obj);
}

static boolean isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
  for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++) {
    if(SERVO(timer,channel).Pin.isActive == true)
      return true;
  }
  return false;
}

/****************** end of static functions ******************************/

Servo::Servo()
{
  if (ServoCount < MAX_SERVOS) {
    this->servoIndex = ServoCount++;                    // assign a servo index to this instance
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;   // store default values
  } else {
    this->servoIndex = INVALID_SERVO;  // too many servos
  }
}

uint8_t Servo::attach(int pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max)
{
  timer16_Sequence_t timer;

  if (this->servoIndex < MAX_SERVOS) {
    pinMode(pin, OUTPUT);                                   // set servo pin to output
    servos[this->servoIndex].Pin.nbr = pin;
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    this->min  = (MIN_PULSE_WIDTH - min)/4; //resolution of min/max is 4 uS
    this->max  = (MAX_PULSE_WIDTH - max)/4;
    // initialize the timer if it has not already been initialized
    timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if (isTimerActive(timer) == false) {
      _timer.idx = timer;
      initISR(&_timer);
    }
    servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
  }
  return this->servoIndex;
}

void Servo::detach()
{
  timer16_Sequence_t timer;

  servos[this->servoIndex].Pin.isActive = false;
  timer = SERVO_INDEX_TO_TIMER(servoIndex);
  if(isTimerActive(timer) == false) {
    finISR(&_timer);
  }
}

void Servo::write(int value)
{
  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
  if (value < MIN_PULSE_WIDTH)
  {
    if (value < 0)
      value = 0;
    else if (value > 180)
      value = 180;

    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
  }
  writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
  // calculate and store the values for the given channel
  byte channel = this->servoIndex;
  if( (channel < MAX_SERVOS) )   // ensure channel is valid
  {
    if (value < SERVO_MIN())          // ensure pulse width is valid
      value = SERVO_MIN();
    else if (value > SERVO_MAX())
      value = SERVO_MAX();

    servos[channel].ticks = value;
  }
}

int Servo::read() // return the value as degrees
{
  return map(readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

int Servo::readMicroseconds()
{
  unsigned int pulsewidth;
  if (this->servoIndex != INVALID_SERVO)
    pulsewidth = servos[this->servoIndex].ticks;
  else
    pulsewidth  = 0;

  return pulsewidth;
}

bool Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive;
}

#endif // ARDUINO_ARCH_STM32
