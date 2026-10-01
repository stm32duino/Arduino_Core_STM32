# Pin naming

STM32 GPIO pins are identified by a port letter and a pin number. For example, `PA_0` means pin 0 on GPIO port A. This `PinName` is distinct from an Arduino digital pin number, a board connector label, and the MCU package pin number. The generic `PY_n` notation means port `Y`, pin `n`; for example, `PB_1` is port B, pin 1.

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

### Example: ordinary GPIO code

Use the board-defined Arduino names for code that should follow the selected board variant:

```cpp
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
delay(100);
digitalWrite(LED_BUILTIN, LOW);
```

Use `A0` with Arduino APIs when you mean the analog pin exposed by the selected variant:

```cpp
int value = analogRead(A0);
```

The physical GPIO represented by `LED_BUILTIN` or `A0` depends on the selected board.

### Which pin form should I use?

| Situation | Recommended form |
| --- | --- |
| Sketch code that follows the selected board | `LED_BUILTIN`, `A0`, or another board-defined alias |
| `pinMode()`, `digitalWrite()`, or another Arduino digital API | An Arduino digital number or board-defined alias |
| A constructor or function explicitly typed as `PinName` | `PA_9`, `PB_6`, or another physical `PinName` |
| An alternate peripheral route | `PA2_ALT1` or another route defined and supported by the selected variant |
| An internal ADC resource | `ATEMP`, `AVREF`, or `AVBAT`, when defined for the selected target |

## Pin conversion helpers

The core provides helpers for converting between board pin numbers and physical STM32 pin names:

- `digitalPinToPinName(pin)` converts an Arduino digital pin value, including an analog alias such as `A0`, to its physical `PinName`, such as `PA_5`.
- `pinNametoDigitalPin(pin)` converts a physical `PinName` back to the first matching Arduino digital pin number defined by the selected variant.
- `analogInputToDigitalPin(pin)` converts an analog input index, such as `0` for `A0`, to the corresponding Arduino digital pin number.
- `analogInputToPinName(pin)` converts an external analog input index to its GPIO `PinName`. It also returns special ADC resource names for internal channels when they are defined; these are not physical GPIO pins.

These helpers use the selected board variant's pin tables. They do not discover pins from the MCU at runtime, and the result can differ between boards.

```cpp
pin_size_t digitalPin = A0;
PinName physicalPin = digitalPinToPinName(digitalPin);
pin_size_t sameDigitalPin = pinNametoDigitalPin(physicalPin);

// Analog input index 0 corresponds to A0.
pin_size_t analogPin = analogInputToDigitalPin(0);
```

For invalid or unavailable pins, `digitalPinToPinName()` returns `NC`, while `pinNametoDigitalPin()` returns `NUM_DIGITAL_PINS`. When analog inputs are defined, an invalid `analogInputToDigitalPin()` result is `NC`; on a target with no analog inputs, its fallback is `NUM_DIGITAL_PINS`. Check conversion results before passing them to another API. `analogInputToPinName()` returns `NC` when no physical or internal ADC mapping exists.

### Equivalence example

On a board where digital pin 3 is connected to physical STM32 pin `PA_4`, the same pin can be represented in several ways:

| Name | Meaning |
| --- | --- |
| `3` | Arduino digital pin number |
| `D3` | Board or connector notation for digital pin 3, when used by the board documentation |
| `PA_4` | Physical STM32 `PinName` (`PY_n` notation) |
| `digitalPinToPinName(3)` | Converts digital pin 3 to `PA_4` |
| `pinNametoDigitalPin(PA_4)` | Converts `PA_4` back to digital pin 3 |

```cpp
// Illustrative mapping only; check the selected variant first.
pin_size_t digitalPin = 3; // D3 in board documentation
PinName physicalPin = digitalPinToPinName(digitalPin); // PA_4
pin_size_t sameDigitalPin = pinNametoDigitalPin(PA_4); // 3
```

In this example, `3`, `D3`, and `PA_4` refer to the same physical connection, but they are not interchangeable in every API. `3` is a digital pin number, `D3` is usually a board-documentation label rather than a C++ symbol, and `PA_4` is a `PinName`. The mapping and numeric values are defined by the selected board variant and may differ on another board. A physical pin can have more than one Arduino representation, so converting to a digital number and back does not necessarily preserve the original alias.

### Analog pin equivalence

For analog APIs, `A0` is the Arduino constant for the first analog input; it does not mean digital pin `0`. The conversion helpers use analog index `0` to retrieve the selected variant's corresponding digital pin number and physical `PinName`:

| Name | Meaning |
| --- | --- |
| `A0` | Arduino constant for the first analog input used with APIs such as `analogRead()` |
| `0` | Analog input index used by `analogInputToDigitalPin()` and `analogInputToPinName()` |
| `analogInputToDigitalPin(0)` | Digital pin number assigned to `A0` by the variant |
| `analogInputToPinName(0)` | Physical `PinName` assigned to `A0`, for example `PA_0` |
| `PY_n` | Generic notation for a physical pin, where `Y` is the port letter and `n` is the pin number |

```cpp
int value = analogRead(A0); // A0 is analog input index 0

pin_size_t digitalPin = analogInputToDigitalPin(0);
PinName physicalPin = analogInputToPinName(0); // For example, PA_0
```

The physical pin might instead be `PB_1`, `PC_0`, or another `PY_n` value on a different board. Always use the selected variant and board documentation to determine the actual mapping.

Internal ADC channels are different from external analog inputs. When supported by the target, names such as `ATEMP`, `AVREF`, and `AVBAT` select the MCU temperature sensor, internal voltage reference, or battery-voltage channel. They are not GPIO pins or board connector pins, and `analogInputToDigitalPin()` returns no GPIO mapping for them.

### Example: APIs that require `PinName`

Use the underscore form when a constructor or function expects a `PinName`. For example, these peripheral instances use the physical STM32 pins directly:

```cpp
HardwareSerial Serial3(PA_10, PA_9); // RX, TX
TwoWire Wire2(PB_9, PB_8);           // SDA, SCL
```

Do not replace `PA_10` with `PA10` in these calls. `PA_10` is the canonical `PinName` form; a no-underscore alias such as `PA10` only works when the selected variant explicitly defines it as a compatible alias.

## Alternate pin routes

Some board variants define names such as `PA2_ALT1` in addition to the default route. These select an alternate pin mapping supported by the core's peripheral pin maps. The suffix is a core/variant route selector; it is not necessarily the STM32 alternate-function number shown in a datasheet. Use an alternate name only when it is defined by the selected variant and supported for the requested peripheral.

For example, an alternate pin can be passed to a peripheral constructor when the variant provides that route:

```cpp
HardwareSerial Serial2(PA2_ALT1, PA3_ALT1); // Only if defined by the variant
```

Check `PeripheralPins.c` before using an `_ALT1` or similar name; the name alone does not guarantee that the requested peripheral supports that route. An unsupported route can prevent the peripheral from being configured correctly.

## Finding the right pin

For a specific board, consult its pinout or schematic, the selected variant's [`variant.h`](development/Add-a-new-variant/overview.md#generated-variant-files), and its `PeripheralPins.c` definitions. These identify the Arduino aliases and which GPIO pins support each peripheral function. A GPIO pin can support different peripheral functions on different STM32 families, and a peripheral instance may have multiple valid pin routes. The [API reference](API.md) contains further examples of constructors that accept `PinName` values.
