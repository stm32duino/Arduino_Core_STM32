# Discovery L072CZ-LRWAN1 support
## Board [B-L072Z-LRWAN1](http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)
## MCU [STM32L072CZ](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-ultra-low-power-mcus/stm32l0-series/stm32l0x2/stm32l072cz.html)
## Restrictions
Some of the _STM32L072CZY6_ pins are used by the LoRa module, so fewer  GPIOs are available on this board.

These pins are not available on the board: `PA6-7,15`; `PB0-1,3-4,10-11`; `PC0,13-15`

These pins are available, but dedicated to the LoRa module: `PA1, PC1-2`

By default, `A1`, `A3`, `A4`, and `A5` are not connected pins.

`A1` and `A3` can be connected to the same GPIOs as `A0` and `A2` by closing
solder bridges **SB7** and **SB8**.

`A4` and `A5` can be connected to `PB9` and `PB8` using solder bridges
**SB11** and **SB12** (note that `PB9` and `PB8` do not have any analog/ADC
capabilities though).

A third analog/ADC input is available as `A6` on the `PA5` pin.

There is no PWM on Arduino `D5` (`PB7`), `D6` (`PB2`) and `D9` (`PB12`) unlike Arduino Uno.

For further information, please refers to the [UM2115: Discovery kit for LoRaWAN (TM) and LPWAN protocols with STM32L0](http://www.st.com/resource/en/user_manual/dm00329995.pdf)
