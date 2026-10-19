# Additional Libraries and Compatibility

This page lists Arduino libraries known to work with the STM32 core and
community-reported library tests. Compatibility can vary by library version,
board, STM32 device, and connected hardware; check the linked project
documentation for details. Contributions with additional tested combinations
are welcome.

## Official Arduino libraries

- [TFT](https://github.com/arduino-libraries/TFT/): use release [1.0.6](https://github.com/arduino-libraries/TFT/releases/tag/1.0.6) or later; otherwise use [Ucglib_Arduino](https://github.com/olikraus/Ucglib_Arduino)
- [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal)
- [Ethernet](https://github.com/arduino-libraries/Ethernet)
- [WiFi](https://github.com/arduino-libraries/WiFi)

## Community-tested libraries

| Library | Reported test |
| --- | --- |
| [arduino-LoRa](https://github.com/sandeepmistry/arduino-LoRa) | Tested with B-L072Z-LRWAN1 |
| [Firmata](https://github.com/firmata/arduino) | Supported since release 2.5.7 |
| [OneWire](https://github.com/PaulStoffregen/OneWire) | Library for Dallas/Maxim 1-Wire chips |
| [PubSubClient](https://github.com/knolleary/PubSubClient) | Tested on L475 Discovery IoT using Wi-Fi |
| [RTClib](https://github.com/adafruit/RTClib) | Tested with Adafruit module 3296 |
| [Ucglib_Arduino](https://github.com/olikraus/Ucglib_Arduino) | Tested with ST7735 |
| [UIPEthernet](https://github.com/UIPEthernet/UIPEthernet) | Tested with ENC28J60 module |

## Library compatibility

When a library needs to distinguish STM32duino from other Arduino cores, use
the `ARDUINO_ARCH_STM32` preprocessor macro. The core defines it when compiling
for STM32duino. For example:

```cpp
#if defined(ARDUINO_ARCH_STM32)
// STM32duino-specific code
#endif
```

See the [FAQ example](../FAQ.md#how-do-i-know-which-stm32duinolibmaple-core-am-i-running-on)
for how this macro distinguishes STM32duino from the legacy libmaple core.
