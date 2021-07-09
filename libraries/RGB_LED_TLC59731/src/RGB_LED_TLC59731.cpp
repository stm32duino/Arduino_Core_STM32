/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#include "RGB_LED_TLC59731.h"

#define WRITE_COMMAND      0x3A
#ifndef DEFAULT_BRIGHTNESS
  #define DEFAULT_BRIGHTNESS 0x41
#endif
uint8_t RGB_LED_TLC59731::brightness = DEFAULT_BRIGHTNESS;
uint8_t RGB_LED_TLC59731::OFF[3]     = {0,                  0,                  0                 };
uint8_t RGB_LED_TLC59731::RED[3]     = {DEFAULT_BRIGHTNESS, 0,                  0                 };
uint8_t RGB_LED_TLC59731::GREEN[3]   = {0,                  DEFAULT_BRIGHTNESS, 0                 };
uint8_t RGB_LED_TLC59731::BLUE[3]    = {0,                  0,                  DEFAULT_BRIGHTNESS};
uint8_t RGB_LED_TLC59731::MAGENTA[3] = {DEFAULT_BRIGHTNESS, 0,                  DEFAULT_BRIGHTNESS};
uint8_t RGB_LED_TLC59731::CYAN[3]    = {0,                  DEFAULT_BRIGHTNESS, DEFAULT_BRIGHTNESS};
uint8_t RGB_LED_TLC59731::YELLOW[3]  = {DEFAULT_BRIGHTNESS, DEFAULT_BRIGHTNESS, 0                 };
uint8_t RGB_LED_TLC59731::WHITE[3]   = {DEFAULT_BRIGHTNESS, DEFAULT_BRIGHTNESS, DEFAULT_BRIGHTNESS};

/**
  * @brief  Set RGB LED color
  * @param  rgb[3]: red,green, blue value in range [0-255]
  * @retval None
  */
void RGB_LED_TLC59731::on(uint8_t rgb[3])
{
  on(rgb[0], rgb[1], rgb[2]);
}

/**
  * @brief  Set RGB LED color
  * @param  red: red value in range [0-255]
  * @param  green: green value in range [0-255]
  * @param  blue: blue value in range [0-255]
  * @retval None
  */
void RGB_LED_TLC59731::on(uint8_t red, uint8_t green, uint8_t blue)
{
  if (!_enabled) {
    if (_enable_pin != NC) {
      pinMode(pinNametoDigitalPin(_enable_pin), OUTPUT);
      digitalWriteFast(_enable_pin, HIGH);
    }

    pinMode(pinNametoDigitalPin(_rgb_pin), OUTPUT);
    _enabled = true;
  }
  /* Data Transfer Rate (T_CYCLE) Measurement Sequence */
  digitalWriteFast(_rgb_pin, HIGH);
  delayMicroseconds(_T_Rise);
  digitalWriteFast(_rgb_pin, LOW);
  delayMicroseconds(_T_Cycle0);
  /* Write command */
  senByte(WRITE_COMMAND);
  /* Write the GS data */
  senByte(red);
  senByte(green);
  senByte(blue);
  /* GS Latch */
  delayMicroseconds(_T_GS_Lat);
}

/**
  * @brief  Set RGB LED Off
  * @param  None
  * @retval None
  */
void RGB_LED_TLC59731::off(void)
{
  /* Set RGB LED off value */
  on(RGB_LED_TLC59731::OFF);
  pinMode(pinNametoDigitalPin(_rgb_pin), INPUT_ANALOG);

  if (_enable_pin != NC) {
    digitalWriteFast(_enable_pin, LOW);
    pinMode(pinNametoDigitalPin(_enable_pin), INPUT_ANALOG);
    _enabled = false;
  }
}

/**
  * @brief  Set brightness value
  * @param  value: new brightness value
  * @retval None
  */
void RGB_LED_TLC59731::setBrightness(uint8_t value)
{
  RGB_LED_TLC59731::brightness = value;
  RGB_LED_TLC59731::RED[0]     = value;
  RGB_LED_TLC59731::GREEN[1]   = value;
  RGB_LED_TLC59731::BLUE[2]    = value;
  RGB_LED_TLC59731::MAGENTA[0] = value;
  RGB_LED_TLC59731::MAGENTA[2] = value;
  RGB_LED_TLC59731::CYAN[1]    = value;
  RGB_LED_TLC59731::CYAN[2]    = value;
  RGB_LED_TLC59731::YELLOW[0]  = value;
  RGB_LED_TLC59731::YELLOW[1]  = value;
  RGB_LED_TLC59731::WHITE[0]   = value;
  RGB_LED_TLC59731::WHITE[1]   = value;
  RGB_LED_TLC59731::WHITE[2]   = value;
}

/* Private */
void RGB_LED_TLC59731::sendBit(uint8_t bit)
{
  /* Start next cycle */
  digitalWriteFast(_rgb_pin, HIGH);
  delayMicroseconds(_T_Rise);
  digitalWriteFast(_rgb_pin, LOW);
  delayMicroseconds(_T_Rise);

  if (bit) {
    digitalWriteFast(_rgb_pin, HIGH);
    delayMicroseconds(_T_Rise);
    digitalWriteFast(_rgb_pin, LOW);
    delayMicroseconds(_T_Cycle1);
  } else {
    delayMicroseconds(_T_Cycle0);
  }
}


void RGB_LED_TLC59731::senByte(uint8_t byte)
{
  sendBit(byte & (1 << 7));
  sendBit(byte & (1 << 6));
  sendBit(byte & (1 << 5));
  sendBit(byte & (1 << 4));
  sendBit(byte & (1 << 3));
  sendBit(byte & (1 << 2));
  sendBit(byte & (1 << 1));
  sendBit(byte & (1 << 0));
}
