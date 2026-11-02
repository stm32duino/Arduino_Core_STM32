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

/**
 * @brief Driver for an RGB LED controlled by a TLC59731 driver through a
 *        single wire interface.
 */
class RGB_LED_TLC59731 {

  public:
    /**
     * @brief Construct the driver and select the pins used to drive the LED.
     * @param rgb_pin Pin connected to the TLC59731 data input. Default: LED_BUILTIN.
     * @param enable_pin Pin connected to the TLC59731 enable line, NC if not
     *        used. Default: NC.
     */
    RGB_LED_TLC59731(pin_size_t rgb_pin = LED_BUILTIN, pin_size_t enable_pin = NC):
      _rgb_pin(digitalPinToPinName(rgb_pin)), _enable_pin(digitalPinToPinName(enable_pin)) {};
    /**
     * @brief Set the RGB LED color.
     *
     * The pins are configured on the first call.
     * @param rgb Array of red, green and blue values in range [0-255].
     */
    void on(uint8_t rgb[3]);
    /**
     * @brief Set the RGB LED color.
     * @param red Red value in range [0-255].
     * @param green Green value in range [0-255].
     * @param blue Blue value in range [0-255].
     */
    void on(uint8_t red, uint8_t green, uint8_t blue);
    /**
     * @brief Turn the RGB LED off and release its pins.
     */
    void off(void);
    /**
     * @brief Get the current brightness value.
     * @return Brightness value.
     */
    inline uint8_t getBrightness(void)
    {
      return brightness;
    }
    /**
     * @brief Set the brightness value, applied to the predefined colors.
     *
     * The LED is not updated until on() is called with a predefined color.
     * @param value New brightness value in range [0-255].
     */
    void setBrightness(uint8_t value);

    /**
     * @brief Current brightness value, used by the predefined colors.
     */
    static uint8_t brightness;
    /** @brief Predefined color: off (no light). */
    static uint8_t OFF[3];
    /** @brief Predefined color: red. */
    static uint8_t RED[3];
    /** @brief Predefined color: green. */
    static uint8_t GREEN[3];
    /** @brief Predefined color: blue. */
    static uint8_t BLUE[3];
    /** @brief Predefined color: magenta. */
    static uint8_t MAGENTA[3];
    /** @brief Predefined color: cyan. */
    static uint8_t CYAN[3];
    /** @brief Predefined color: yellow. */
    static uint8_t YELLOW[3];
    /** @brief Predefined color: white. */
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

    /**
     * @brief Send one bit to the TLC59731 using its pulse width timing.
     * @param bit Bit value to send (0 or 1).
     */
    void sendBit(uint8_t bit);
    /**
     * @brief Send one byte to the TLC59731, most significant bit first.
     * @param byte Byte value to send.
     */
    void sendByte(uint8_t byte);
};

#endif /* __RGB_LED_TLC59731_H__ */
