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
#ifndef __RGB_LED_TLC59731_H__
#define __RGB_LED_TLC59731_H__

#include "Arduino.h"

#ifndef LED_BUILTIN
  #define LED_BUILTIN PNUM_NOT_DEFINED
  #warning "LED_BUILTIN is not defined."
#endif

class RGB_LED_TLC59731 {

  public:
    RGB_LED_TLC59731(uint32_t rgb_pin = LED_BUILTIN, uint32_t enable_pin = NC):
      _rgb_pin(digitalPinToPinName(rgb_pin)), _enable_pin(digitalPinToPinName(enable_pin)) {};
    void on(uint8_t rgb[3]);
    void on(uint8_t red, uint8_t green, uint8_t blue);
    void off(void);
    inline uint8_t getBrightness(void)
    {
      return brightness;
    }
    void setBrightness(uint8_t value);

    static uint8_t brightness;
    static uint8_t OFF[3];
    static uint8_t RED[3];
    static uint8_t GREEN[3];
    static uint8_t BLUE[3];
    static uint8_t MAGENTA[3];
    static uint8_t CYAN[3];
    static uint8_t YELLOW[3];
    static uint8_t WHITE[3];

  private:
    PinName _rgb_pin;
    PinName _enable_pin;

    bool _enabled{false};
    const uint32_t _T_Rise{1};
    const uint32_t _T_Cycle0{4};
    const uint32_t _T_Cycle1{1};
    // GS Data Latch (GSLAT) Sequence delay
    const uint32_t _T_GS_Lat{_T_Cycle0 * 8};

    void sendBit(uint8_t bit);
    void senByte(uint8_t byte);
};

#endif /* __RGB_LED_TLC59731_H__ */
