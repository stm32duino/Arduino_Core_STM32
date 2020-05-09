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
#include <HardwareTimer.h>

#if defined(HAL_TIM_MODULE_ENABLED) && defined(TIMER_SERVO) && !defined(HAL_TIM_MODULE_ONLY)

static servo_t servos[MAX_SERVOS];                         // static array of servo structures
static volatile int8_t timerChannel[_Nbr_16timers] = {-1}; // counter for the servo being pulsed for each timer (or -1 if refresh interval)

static HardwareTimer TimerServo(TIMER_SERVO);

uint8_t ServoCount = 0;                                    // the total number of attached servos

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)   // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)   // maximum value in uS for this servo

#define TIMER_ID(_timer) ((timer_id_e)(_timer))
#define SERVO_TIMER(_timer_id)  ((timer16_Sequence_t)(_timer_id))

/************ static functions common to all instances ***********************/

volatile uint32_t CumulativeCountSinceRefresh = 0;
static void Servo_PeriodElapsedCallback()
{
  // Only 1 timer used
  timer16_Sequence_t timer_id = _timer1;

  if (timerChannel[timer_id] < 0) {
    // Restart from 1st servo
    CumulativeCountSinceRefresh = 0;
  } else {
    if (timerChannel[timer_id] < ServoCount && servos[timerChannel[timer_id]].Pin.isActive == true) {
      digitalWrite(servos[timerChannel[timer_id]].Pin.nbr, LOW); // pulse this channel low if activated
    }
  }

  timerChannel[timer_id]++;    // increment to the next channel
  if (timerChannel[timer_id] < ServoCount && timerChannel[timer_id] < SERVOS_PER_TIMER) {
    TimerServo.setOverflow(servos[timerChannel[timer_id]].ticks);
    CumulativeCountSinceRefresh += servos[timerChannel[timer_id]].ticks;
    if (servos[timerChannel[timer_id]].Pin.isActive == true) {
      // check if activated
      digitalWrite(servos[timerChannel[timer_id]].Pin.nbr, HIGH); // its an active channel so pulse it high
    }
  } else {
    // finished all channels so wait for the refresh period to expire before starting over
    if (CumulativeCountSinceRefresh + 4 < REFRESH_INTERVAL) {
      // allow a few ticks to ensure the next OCR1A not missed
      TimerServo.setOverflow(REFRESH_INTERVAL - CumulativeCountSinceRefresh);
    } else {
      // generate update to restart immediately from the beginning with the 1st servo
      TimerServo.refresh();
    }
    timerChannel[timer_id] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
  }
}

static void TimerServoInit()
{
  // prescaler is computed so that timer tick correspond to 1 microseconde
  uint32_t prescaler = TimerServo.getTimerClkFreq() / 1000000;

  TimerServo.setMode(1, TIMER_OUTPUT_COMPARE, NC);
  TimerServo.setPrescaleFactor(prescaler);
  TimerServo.setOverflow(REFRESH_INTERVAL); // thanks to prescaler Tick = microsec
  TimerServo.attachInterrupt(Servo_PeriodElapsedCallback);
  TimerServo.setPreloadEnable(false);
  TimerServo.resume();
}


static bool isTimerActive()
{
  // returns true if any servo is active on this timer
  for (uint8_t channel = 0; channel < SERVOS_PER_TIMER; channel++) {
    if (servos[channel].Pin.isActive == true) {
      return true;
    }
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
  if (this->servoIndex < MAX_SERVOS) {
    pinMode(pin, OUTPUT);                                   // set servo pin to output
    servos[this->servoIndex].Pin.nbr = pin;
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    this->min  = (MIN_PULSE_WIDTH - min) / 4; //resolution of min/max is 4 uS
    this->max  = (MAX_PULSE_WIDTH - max) / 4;
    // initialize the timer if it has not already been initialized
    if (isTimerActive() == false) {
      TimerServoInit();
    }
    servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
  }
  return this->servoIndex;
}

void Servo::detach()
{
  servos[this->servoIndex].Pin.isActive = false;

  if (isTimerActive() == false) {
    TimerServo.pause();
  }
}

void Servo::write(int value)
{
  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
  if (value < MIN_PULSE_WIDTH) {
    if (value < 0) {
      value = 0;
    } else if (value > 180) {
      value = 180;
    }

    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
  }
  writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
  // calculate and store the values for the given channel
  byte channel = this->servoIndex;
  if ((channel < MAX_SERVOS)) {  // ensure channel is valid
    if (value < SERVO_MIN()) {        // ensure pulse width is valid
      value = SERVO_MIN();
    } else if (value > SERVO_MAX()) {
      value = SERVO_MAX();
    }

    servos[channel].ticks = value;
  }
}

int Servo::read() // return the value as degrees
{
  return map(readMicroseconds() + 1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

int Servo::readMicroseconds()
{
  unsigned int pulsewidth;
  if (this->servoIndex != INVALID_SERVO) {
    pulsewidth = servos[this->servoIndex].ticks;
  } else {
    pulsewidth  = 0;
  }

  return pulsewidth;
}

bool Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive;
}

#else

#warning "TIMER_TONE or HAL_TIM_MODULE_ENABLED not defined"
Servo::Servo() {}
uint8_t Servo::attach(int pin)
{
  UNUSED(pin);
  return 0;
}
uint8_t Servo::attach(int pin, int min, int max)
{
  UNUSED(pin);
  UNUSED(min);
  UNUSED(max);
  return 0;
}
void Servo::detach() {}
void Servo::write(int value)
{
  UNUSED(value);
}
void Servo::writeMicroseconds(int value)
{
  UNUSED(value);
}
int Servo::read()
{
  return 0;
}
int Servo::readMicroseconds()
{
  return 0;
}
bool Servo::attached() {}

#endif /* HAL_TIM_MODULE_ENABLED && TIMER_SERVO & !HAL_TIM_MODULE_ONLY */

#endif // ARDUINO_ARCH_STM32
