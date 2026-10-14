# I2C

By default, only one `Wire` instance is available and it uses the Arduino pins D14(SDA) and D15(SCL).
To use a second I2C port, a `TwoWire` object should be declared in the sketch before the `setup()` function:
```C++
#include <Wire.h>
//            SDA  SCL
TwoWire Wire2(PB3, PB10);

void setup() {
  Wire2.begin();
}

void loop() {
  Wire2.beginTransmission(0x71);
  Wire2.write('v');
  Wire2.endTransmission();
  delay(1000);
}
```

See [I2C Timing](../../customization/Custom-definitions.md#i2c-timing) to customize the I2C speed if needed.

## Default I2C pins
**The default I2C interface pins are configured inside the PeripheralPins.c file.**

### Example (for Nucleo-L452RE in file PeripheralPins.c):
```C++
#ifdef HAL_I2C_MODULE_ENABLED
 WEAK const PinMap PinMap_I2C_SDA[] = {
   {PA_10, I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   {PB_4,  I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)},
   {PB_7,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   //  {PB_7,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF5_I2C4)},
   {PB_9,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   {PB_11, I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
   //  {PB_11, I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF3_I2C4)},
   {PB_14, I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
   //  {PC_1,  I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)},
   {PC_1,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF2_I2C4)},
   {NC,    NP,    0}
 };
 #endif

 #ifdef HAL_I2C_MODULE_ENABLED
 WEAK const PinMap PinMap_I2C_SCL[] = {
   {PA_7,  I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)},
   {PA_9,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   //  {PB_6,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   {PB_6,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF5_I2C4)},
   {PB_8,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)},
   {PB_10, I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
   //  {PB_10, I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF3_I2C4)},
   {PB_13, I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
   //  {PC_0,  I2C3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)},
   {PC_0,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF2_I2C4)},
   {NC,    NP,    0}
 };
 #endif
```

## Redefine I2C pins
Because they are defined as WEAK, you can redefine them in your sketch file instead of changing values in the PeripheralPins.c file.
You can also enable/disable the internal pull-ups with the second parameter of STM_PIN_DATA().
#### Example (inside of sketch file):
```C++
const PinMap PinMap_I2C_SDA[] = {
  {PB_9,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULLUP, GPIO_AF4_I2C1)},
  {PC_1,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, GPIO_AF2_I2C4)},
  {NC,    NP,    0}
};
const PinMap PinMap_I2C_SCL[] = {
  {PB_8,  I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULLUP, GPIO_AF4_I2C1)},
  {PC_0,  I2C4, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, GPIO_AF2_I2C4)},
  {NC,    NP,    0}
};
```



## New API functions

### Change default `Wire` instance pins
It is also possible to change the default pins used by the `Wire` instance using above API:

* `void setSCL(uint32_t scl)`
* `void setSDA(uint32_t sda)`
* `void setSCL(PinName scl)`
* `void setSDA(PinName sda)`

> [!WARNING]
> Have to be called before `begin()`.

#### Example:
```C++
    Wire.setSDA(PC_4); // using pin name PY_n
    Wire.setSCL(PC2); // using pin number PYn
    Wire.begin();
```

### Enable general call mode
Available in core version greater than **1.5.0**

Adding `true` as last parameters of the 3 `Wire::begin()` methods will enable the general call mode otherwise `false` per default:

* `void begin(bool generalCall = false)`
* `void begin(uint8_t, bool generalCall = false)`
* `void begin(int, bool generalCall = false)`

#### Example
`Wire.begin(true);` or `Wire.begin(0x70,true);`

## I2C buffer management
By default, I2C buffers are aligned with the Arduino API at **32 bytes**. Transfers of up to **255 bytes** are also possible:

- In master mode: RX and TX buffers will automatically grow when needed, independently one from each other, and independently from other I2C instances. Nothing to do from application point of view. Warning: a bug in STM32 cube HAL (STM32 core v1.8.0) prevents to transfer exactly 255 bytes. (see [PR #853])

- In slave mode: RX and TX buffer size can be statically redefined using [hal_conf_extra.h](../../customization/HAL-configuration.md) or [`build_opt.h`][build_opt.h] (at compilation time) thanks to switch `I2C_TXRX_BUFFER_SIZE` (see [PR #853]). All I2C instances are impacted by change of this compilation switch.

[build_opt.h]: ../../customization/Customize-build-options-using-build_opt.h.md
[PR #853]: https://github.com/stm32duino/Arduino_Core_STM32/pull/853
