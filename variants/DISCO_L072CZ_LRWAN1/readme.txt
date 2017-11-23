Discovery L072CZ-LRWAN1 support.

Board: http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html
MCU: http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-ultra-low-power-mcus/stm32l0-series/stm32l0x2/stm32l072cz.html

Restrictions:

Some of the STM32L072CZY6 pins are used by the LoRa module, so fewer
GPIOs are available on this board.

These pins are not available on the board: PA6-7,15; PB0-1,3-4,10-11; PC0,13-15

These pins are available, but dedicated to the LoRa module: PA1, PC1-2

By default, A1, A3, A4, and A5 are no-connect pins.

A1 and A3 can be connected to the same GPIOs as A0 and A2 by closing
solder bridges SB7 and SB8.

A4 and A5 can be connected to PB9 and PB8 using solder bridges SB11
and SB12 (note that PB9 and PB8 do not have any analog/ADC
capabilities though).

An third analog/ADC input is available as A6 on the PA5 pin.

SPI MOSI and MISO are available on digital pins D11 and D12, but the
SCK pin is D3 (unlike Arduino Uno where it is on D13).
