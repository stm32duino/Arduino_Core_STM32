# RGB_LED_TLC59731

## Introduction

The RGB_LED_TLC59731 library drives an RGB LED controlled by a TLC59731 driver
through its single wire interface. For example, the STM32WB5MM-DK board has
such a LED.

## Usage

```Arduino
#include <RGB_LED_TLC59731.h>

RGB_LED_TLC59731 myLED;

void setup() {
  myLED.setBrightness(0x10);
}

void loop() {
  myLED.on(RGB_LED_TLC59731::RED);
  delay(500);
  myLED.off();
  delay(500);
}
```

On the STM32WB5MM-DK, the LED data pin is `RGB_LED` and the enable pin is
`LED_SELECT`: `RGB_LED_TLC59731 myLED(RGB_LED, LED_SELECT);`.
It also requires JP5 on and JP4 off. See the `RGB_LED_TLC59731` example of the
library.

## API

| Method | Description |
| ------ | ----------- |
| `RGB_LED_TLC59731(pin_size_t rgb_pin = LED_BUILTIN, pin_size_t enable_pin = NC)` | Creates the driver. `rgb_pin` is connected to the TLC59731 data input and `enable_pin` to its enable line, `NC` if not used. |
| `void on(uint8_t rgb[3])` | Sets the LED color from an array of red, green and blue values in `[0-255]`. The pins are configured on the first call. |
| `void on(uint8_t red, uint8_t green, uint8_t blue)` | Sets the LED color from the red, green and blue values in `[0-255]`. |
| `void off()` | Turns the LED off and releases its pins. |
| `void setBrightness(uint8_t value)` | Sets the brightness in `[0-255]`, applied to the predefined colors. The LED is only updated by a following call to `on()` with a predefined color. |
| `uint8_t getBrightness()` | Returns the current brightness value. |

### Predefined colors

`RGB_LED_TLC59731::OFF`, `RED`, `GREEN`, `BLUE`, `MAGENTA`, `CYAN`, `YELLOW`
and `WHITE`. They are `uint8_t[3]` arrays whose active channels use the
brightness value (default `0x41`, can be changed with `DEFAULT_BRIGHTNESS` or
`setBrightness()`).
