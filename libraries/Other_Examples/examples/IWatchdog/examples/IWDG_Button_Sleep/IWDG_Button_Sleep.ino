/*

  The code demonstrates the use of a independent watchdog timer with board sleeping activities.
  The watchdog timer is initialized with timeout of 10 seconds.
  Every time the button is pressed, the watchdog timer is reset on button release.
  If left unattended the system would reset itself about every 10 seconds.

  You would have to keep pressing the button frequently (< 10 seconds apart)
  to prevent the system from resetting itself.

  You would recognize the reset condition when the LED blinks few times quickly.
*/

#include "STM32LowPower.h"
#include <STM32RTC.h>
#include <IWatchdog.h>

#define USING_SLEEP_MODE

#ifdef USER_BTN
const int buttonPin = USER_BTN;
#endif

#ifdef LED_BUILTIN
const int ledPin = LED_BUILTIN;
#endif

#define BUTTON_DEBOUNCE_TIME_MS 50 // 50 milliseconds
volatile uint32_t button_release_last_evt_timestamp;
volatile bool button_release_flag;

STM32RTC &rtc = STM32RTC::getInstance();
static uint32_t atime = 600;

void setup() {
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, LOW);
  digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
  digitalWrite(GNSS_V_BCKP_PIN, LOW);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  mcu_sleep_init();

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), button_release_isr, RISING);

  // Check if the current reset cause by IWatchdog
  if (IWatchdog.isReset(true)) {
    // LED blinks to indicate reset
    for (uint8_t idx = 0; idx < 5; idx++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }

  // Init the watchdog timer with 10 seconds timeout
  IWatchdog.begin(10000000);

  // Check IWDG init status
  if (!IWatchdog.isEnabled()) {
    // LED blinks indefinitely
    while (1) {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
    }
  }
}

void loop() {
  if (button_release_flag) {
    // Blink LED to indicate IWDG reloading
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);

    // Reload the IWDG
    IWatchdog.reload();

    // Clear button flag
    button_release_flag = false;
  }
  else {
    mcu_sleep(5);
  }
}

void button_release_isr(void)
{
  if (millis() - button_release_last_evt_timestamp > BUTTON_DEBOUNCE_TIME_MS)
  {
    button_release_last_evt_timestamp = millis();
    button_release_flag = true;
  }
}

void mcu_sleep_init(void)
{
  // Low-power library initialization
  rtc.begin();
  LowPower.begin();
  LowPower.enableWakeupFrom(&rtc, alarmMatch, &atime);
}

void mcu_sleep(uint32_t sleep_duration_s)
{
#ifndef USING_SLEEP_MODE
  delay(sleep_duration_s * 1000); // DEBUG
#else
  rtc.setAlarmEpoch(rtc.getEpoch() + sleep_duration_s);
  LowPower.deepSleep();
#endif
}

void alarmMatch(void *data)
{
}
