/*
  RGB_LED_TLC59731

  This example code is in the public domain.

  Blink one RGB LED with different default colors:
    RGB_LED_TLC59731::OFF
    RGB_LED_TLC59731::RED
    RGB_LED_TLC59731::GREEN
    RGB_LED_TLC59731::BLUE
    RGB_LED_TLC59731::MAGENTA
    RGB_LED_TLC59731::CYAN
    RGB_LED_TLC59731::YELLOW
    RGB_LED_TLC59731::WHITE
*/

#include <RGB_LED_TLC59731.h>

static uint8_t step = 0;
static uint8_t* sequence[] = { RGB_LED_TLC59731::RED,
                              RGB_LED_TLC59731::GREEN,
                              RGB_LED_TLC59731::BLUE,
                              RGB_LED_TLC59731::MAGENTA,
                              RGB_LED_TLC59731::CYAN,
                              RGB_LED_TLC59731::YELLOW,
                              RGB_LED_TLC59731::WHITE
                            };
/**
    STM32WB5MM-DK have an RGB LED connected to TLC59731
    It requires to enable it thanks LED_SELECT pin
    and to have JP5 on and JP4 off
*/
#if defined(RGB_LED) && defined(LED_SELECT)
RGB_LED_TLC59731 myLED(RGB_LED, LED_SELECT);
#else
RGB_LED_TLC59731 myLED;
#endif

void setup() {
  /* Change Brightness */
  myLED.setBrightness(0x10);
}

void loop() {
  /* Blink */
  myLED.on(sequence[step]);
  delay(500);
  myLED.off();
  delay(500);
  step = (step == 6) ? 0 : step + 1;
}
