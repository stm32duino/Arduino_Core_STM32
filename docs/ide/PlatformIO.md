# [PlatformIO]

> [!WARNING]
> The [STM32duino GitHub organization] does not support issue met using [PlatformIO]. Only the Arduino IDE is supported. Below information are provided "as it" based on this PR [#1413] from [@brianredbeard]. Do not hesitate to correct them.


In your project, set your environment to use the `platform` setting `ststm32` and the `framework` setting `arduino`, e.g:

```dosini
[env]
platform  = ststm32
framework = arduino
```

Behind the scenes this will create a dependency on the [ST STM32: development platform] for [PlatformIO] ([`ststm32`]) and the framework package `framework-arduinoststm32` (the [PlatformIO]name of this library as noted in [`/package.json`]).

This repository should not be confused with the [ST STM32: development platform] which is located at https://github.com/platformio/platform-ststm32.


[STM32duino GitHub organization]: https://github.com/stm32duino
[PlatformIO]: https://platformio.org/
[ST STM32: development platform]: https://github.com/platformio/platform-ststm32
[`/package.json`]: https://github.com/stm32duino/Arduino_Core_STM32/blob/main/package.json
[`ststm32`]: https://docs.platformio.org/en/latest/platforms/ststm32.html
[@brianredbeard]: https://github.com/brianredbeard
[#1413]: https://github.com/stm32duino/Arduino_Core_STM32/pull/1413