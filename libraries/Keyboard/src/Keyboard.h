/*
  Keyboard.h

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

#ifndef KEYBOARD_h
#define KEYBOARD_h

#include <Arduino.h>

#if !defined(USBCON) || !defined(USBD_USE_HID_COMPOSITE)

#error "USB HID not enabled! Select 'HID' in the 'Tools->USB interface' menu."

#else

//================================================================================
//================================================================================
//  Keyboard

/**
 * @name Modifier keys
 * @brief Key codes of the modifier keys, usable with Keyboard.press(),
 *        Keyboard.release() and Keyboard.write().
 * @{
 */
#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_RIGHT_GUI   0x87
/** @} */

/**
 * @name Non-printing keys
 * @brief Key codes of the non-printing keys, usable with Keyboard.press(),
 *        Keyboard.release() and Keyboard.write().
 * @{
 */

#define KEY_UP_ARROW    0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_BACKSPACE   0xB2
#define KEY_TAB       0xB3
#define KEY_RETURN      0xB0
#define KEY_ESC       0xB1
#define KEY_INSERT      0xD1
#define KEY_DELETE      0xD4
#define KEY_PAGE_UP     0xD3
#define KEY_PAGE_DOWN   0xD6
#define KEY_HOME      0xD2
#define KEY_END       0xD5
#define KEY_CAPS_LOCK   0xC1
#define KEY_F1        0xC2
#define KEY_F2        0xC3
#define KEY_F3        0xC4
#define KEY_F4        0xC5
#define KEY_F5        0xC6
#define KEY_F6        0xC7
#define KEY_F7        0xC8
#define KEY_F8        0xC9
#define KEY_F9        0xCA
#define KEY_F10       0xCB
#define KEY_F11       0xCC
#define KEY_F12       0xCD
#define KEY_F13       0xF0
#define KEY_F14       0xF1
#define KEY_F15       0xF2
#define KEY_F16       0xF3
#define KEY_F17       0xF4
#define KEY_F18       0xF5
#define KEY_F19       0xF6
#define KEY_F20       0xF7
#define KEY_F21       0xF8
#define KEY_F22       0xF9
#define KEY_F23       0xFA
#define KEY_F24       0xFB  // Keyboard F24
/** @} */

/**
 * @brief Low level key report: up to 6 keys and shift, ctrl etc at once.
 */
typedef struct {
  uint8_t modifiers;  /**< Bit mask of the pressed modifier keys. */
  uint8_t reserved;   /**< Reserved, always 0. */
  /** HID usage codes of the pressed keys, 0 for an empty slot. */
  uint8_t keys[6];
} KeyReport;

/**
 * @brief USB HID keyboard, used through the global Keyboard object.
 *
 * Requires the 'HID' USB interface selected in the 'Tools->USB interface' menu.
 */
class Keyboard_ : public Print {
  private:
    KeyReport _keyReport;
    /**
     * @brief Send a key report to the host.
     * @param keys Key report to send.
     */
    void sendReport(KeyReport *keys);
  public:
    /**
     * @brief Create the keyboard instance, not started.
     */
    Keyboard_(void);
    /**
     * @brief Start the USB HID keyboard interface.
     */
    void begin(void);
    /**
     * @brief Stop the USB HID keyboard interface.
     */
    void end(void);
    /**
     * @brief Press then release a key: send a key stroke.
     * @param k ASCII character, modifier or non-printing key code (KEY_xxx).
     * @return 1 if the key was pressed, 0 otherwise (e.g. unsupported character).
     */
    size_t write(uint8_t k);
    /**
     * @brief Add a key (printing, non-printing or modifier) to the persistent
     *        key report and send the report.
     *
     * Because of the way USB HID works, the host acts like the key remains
     * pressed until release(), releaseAll() or write() is called.
     * Up to 6 keys can be pressed at the same time.
     * @param k ASCII character, modifier or non-printing key code (KEY_xxx).
     * @return 1 if the key was added to the report, 0 otherwise (unsupported
     *         character or no free slot).
     */
    size_t press(uint8_t k);
    /**
     * @brief Remove a key from the persistent key report and send the report.
     *
     * This tells the host the key is no longer pressed and that it shouldn't be
     * repeated any more.
     * @param k ASCII character, modifier or non-printing key code (KEY_xxx).
     * @return 1 if the report was sent, 0 if the character is not supported.
     */
    size_t release(uint8_t k);
    /**
     * @brief Release all the pressed keys and modifiers and send the report.
     */
    void releaseAll(void);
};
/** @brief Global keyboard instance. */
extern Keyboard_ Keyboard;

#endif
#endif
