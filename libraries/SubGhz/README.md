## SubGhz library

This library gives some low-level control over the SubGhz radio module
present in the STM32WL series of microcontrollers.

This radio module is integrated into the microcontroller chip. It is
essentially a Semtech SX126x radio chip (a combination of the SX1261 and
SX1262 really), connected to a dedicated internal SPI bus.

This library offers an Arduino-style API to access this module on a low
level, where the user is responsible for composing and sending the right
SPI commands to operate the module. It does *not* offer a high-level
interface for sending or receiving data.

### Using this library
This library defines a single class and predefines an instance of that
class called `SubGhz`. To use this library, call methods on this
instance, e.g.:

```
SubGhz.setNssActive(true);
```

#### SPI access
Access to the dedicated SPI bus happens through the `SubGhz.SPI` object.
This behaves just like the normal Arduino SPI object (it is in fact
a customized subclass of the normal SPIClass, provided by the normal SPI
library).

If you use the `beginTransaction()` method, you can pass the
`SubGhz.spi_settings` variable to get the right settings and run at the
maximum supported speed. If not using `beginTransaction()`, the default
settings are also fine, just a bit slower.

#### "GPIO" signals
Some of the signals which are normally (on an actual external SX126x
radio chip) available externally and controlled by GPIO are now
internally connected to registers in the RCC and PWR modules. These
signals (Nss, Reset and Busy) can be controlled and/or read through this
library.

The Nss signal can be written (and read back) using
`SubGhz.setNssActive(bool)` and `SubGhz.isNssActive()`, the Reset signal
using `SubGhz.setResetActive(bool)` and `SubGhz.isResetActive()` and the
busy signal can only be read using `SubGhz.isBusy()`.

There is no need to configure these signals before using them (i.e.
nothing like `pinMode()` is needed).

Note that there is no way to read the DIO signals directly, since they
are not directly available to the MCU anywhere (only through the
interrupt controller, so with some care the DIO signal status could be
derived from the interrupt pending status if needed).

#### Interrupts
In addition, the DIO signals produced by the radio module are connected
together in an "OR" configuration and drive the radio interrupt. This
interrupt can be enabled and configured using various methods in this
library.

The interrupt can be attached (and enabled) using the
`SubGhz.attachInterrupt(callback)` method. You can pass any callable here that
`std::function` accepts (global function, method bound with `std::bind`,
callable object or a lambda). Attaching an interrupt clears any
previously pending interrupts and enables the interrupt.

The `SubGhz.detachInterrupt()` method can be used to disable the
interrupt and clear the handler and the `SubGhz.hasInterrupt()` method
can be used to query if a handler was attached (regardless of whether it
is currently enabled).

The `SubGhz.disableInterrupt()` and `SubGhz.enableInterrupt()` method
can be used to temporarily disable the interrupt. If the interrupt is
triggered while it is disabled, it will become pending (indicated by the
`SubGhz.isInterruptPending()` method) and the interrupt handler will run
directly when the interrupt is enabled again (unless cleared with
`SubGhz.clearPendingInterrupt()`). Note that there is no method to query
whether the interrupt is currently enabled, as the interrupt controller
hardware does allow reading back this value.

Note that there is there is hardly any point in having multiple DIO
signals, since they are all wired together into a single interrupt and
cannot be individually read, but this is just how the original Semtech
radio was designed.

Also note that the DIO lines are directly connected to the MCU interrupt
controller (NVIC), which is level sensitive. When the ISR is triggered,
it should always either clear the interrupt flag in the radio, or
disable the interrupt in the NVIC (using `SubGhz.disableInterrupt()` in
this library) to prevent the ISR from triggering again (and again and
again etc.) after it completes.

### Example

This is a basic example of initializing the radio and SPI bus and
reading a register through an SPI command. See the examples folder for
a full example sketch.

```C++
  // initialize SPI:
  SubGhz.SPI.begin();

  // clear reset to
  SubGhz.setResetActive(false);

  // Start SPI transaction and wait for the radio to wake up (it starts
  // in sleep mode with its busy signal active).
  SubGhz.SPI.beginTransaction(SubGhz.spi_settings);
  SubGhz.setNssActive(true);
  while (SubGhz.isBusy()) /* wait */;

  // Write a command and read the result
  SubGhz.SPI.transfer(0x1D); // Write command: Read_Register()
  SubGhz.SPI.transfer(0x07); // Write MSB of register address: SUBGHZ_LSYNCRH
  SubGhz.SPI.transfer(0x40); // Write LSB of register address: SUBGHZ_LSYNCRH
  uint8_t status = SubGhz.SPI.transfer(0x0);  // Read status
  uint8_t value = SubGhz.SPI.transfer(0x0);  // Read register value

  // End transaction
  SubGhz.setNssActive(false);
  SubGhz.SPI.endTransaction();

  // value now has the register value read
```

### License
Copyright (c) 2022, STMicroelectronics
All rights reserved.

This software component is licensed by ST under BSD 3-Clause license,
the "License"; You may not use this file except in compliance with the
License. You may obtain a copy of the License at:
                       opensource.org/licenses/BSD-3-Clause
