# Pin naming

STM32 GPIO pins are identified by a port letter and a pin number. For example, `PA_0` means pin 0 on GPIO port A. This hardware name is distinct from an Arduino digital pin number, a board connector label, and the MCU package pin number.

## `PinName` constants

The core defines hardware pin names such as `PA_0`, `PB_10`, and `PG_9` in `PinNames.h`. Use this underscore form when an API parameter is explicitly typed as `PinName`:

```cpp
Serial.setRx(PG_9);
Serial.begin(9600);
```

`NC` represents an unconnected pin in APIs that accept a `PinName`. A pin name can exist in the core definitions but still be unavailable on a particular MCU package or board; check the MCU datasheet and board schematic.

## Arduino pin numbers and variant aliases

Arduino functions such as `pinMode()` and `digitalWrite()` normally use the digital pin numbering defined by the selected board variant. The variant may also define aliases such as `PA0`, `PB7`, `A0`, or `LED_BUILTIN`. These aliases are board-specific and can map to Arduino digital numbers; they are not interchangeable with the `PinName` constant `PA_0`.

For example, a variant may map `PA0` to `PIN_A0`, while another maps a port-pin alias to a different digital pin number. Use the aliases and labels documented for the selected board:

```cpp
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
```

Do not assume that `PA0` means Arduino digital pin 0, or that `A0` is always the same physical pin across boards.

## Alternate pin routes

Some board variants define names such as `PA2_ALT1` in addition to the default route. These select an alternate pin mapping supported by the core's peripheral pin maps. The suffix is a core/variant route selector; it is not necessarily the STM32 alternate-function number shown in a datasheet. Use an alternate name only when it is defined by the selected variant and supported for the requested peripheral.

## Finding the right pin

For a specific board, consult its pinout or schematic, the selected variant's `variant.h`, and its `PeripheralPins.c` definitions. These identify the Arduino aliases and which GPIO pins support each peripheral function. A GPIO pin can support different peripheral functions on different STM32 families, and a peripheral instance may have multiple valid pin routes.
