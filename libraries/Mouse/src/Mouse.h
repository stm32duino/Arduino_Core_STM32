/*
  Mouse.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

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

#ifndef MOUSE_h
#define MOUSE_h

#include <Arduino.h>

#if !defined(USBCON) || !defined(USBD_USE_HID_COMPOSITE)

#error "USB HID not enabled! Select 'HID' in the 'Tools->USB interface' menu."

#else

//================================================================================
//================================================================================
//  Mouse

/** @brief Left mouse button. */
#define MOUSE_LEFT 1
/** @brief Right mouse button. */
#define MOUSE_RIGHT 2
/** @brief Middle mouse button. */
#define MOUSE_MIDDLE 4
/** @brief All the mouse buttons. */
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

/**
 * @brief USB HID mouse, used through the global Mouse object.
 *
 * Requires the 'HID' USB interface selected in the 'Tools->USB interface' menu.
 */
class Mouse_ {
  private:
    uint8_t _buttons;
    /**
     * @brief Set the pressed buttons and send a report if the state changed.
     * @param b Bit mask of the pressed buttons.
     */
    void buttons(uint8_t b);
  public:
    /**
     * @brief Create the mouse instance, not started.
     */
    Mouse_(void);
    /**
     * @brief Start the USB HID mouse interface.
     */
    void begin(void);
    /**
     * @brief Stop the USB HID mouse interface.
     */
    void end(void);
    /**
     * @brief Click a button: press then release it.
     * @param b Button(s) to click: MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE or a
     *        combination. Default: MOUSE_LEFT.
     */
    void click(uint8_t b = MOUSE_LEFT);
    /**
     * @brief Move the cursor and/or the scroll wheel, with the current button state.
     * @param x Relative movement on the horizontal axis.
     * @param y Relative movement on the vertical axis.
     * @param wheel Relative scroll wheel movement. Default: 0.
     */
    void move(signed char x, signed char y, signed char wheel = 0);
    /**
     * @brief Press a button and keep it pressed until release() is called.
     * @param b Button(s) to press: MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE or a
     *        combination. Default: MOUSE_LEFT.
     */
    void press(uint8_t b = MOUSE_LEFT);
    /**
     * @brief Release a pressed button.
     * @param b Button(s) to release: MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE or a
     *        combination. Default: MOUSE_LEFT.
     */
    void release(uint8_t b = MOUSE_LEFT);
    /**
     * @brief Check if a button is pressed.
     * @param b Button(s) to check: MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE or a
     *        combination. Default: MOUSE_LEFT.
     * @return true if at least one of the buttons is pressed, false otherwise.
     */
    bool isPressed(uint8_t b = MOUSE_LEFT);
};
/** @brief Global mouse instance. */
extern Mouse_ Mouse;

#endif
#endif
