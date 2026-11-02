# SubGhz

## Introduction

The SubGhz library gives low-level control of the sub-GHz radio module of the
STM32WL series. The radio is a Semtech SX126x (SX1261 and SX1262 combined)
integrated in the microcontroller and connected to a dedicated internal SPI bus.

The library offers an Arduino-style API to access the module: the user composes
and sends the SPI commands. It does **not** provide a high-level interface to
send or receive data. For LoRaWAN, see [STM32LoRaWAN](../Hosted-library-documentation.md).

It defines a single class and a predefined instance named `SubGhz`.

## SPI access

The dedicated SPI bus is available through `SubGhz.SPI`. It behaves like the
Arduino [SPI](SPI-library.md) object. Pass `SubGhz.spi_settings` to
`beginTransaction()` to run at the maximum supported speed (16 MHz, mode 0).

## Internal signals

The Nss, Reset and Busy signals are internally connected to the RCC and PWR
registers. No `pinMode()` is needed.

| Method | Description |
| ------ | ----------- |
| `void setNssActive(bool value)` | Activates NSS (drives it LOW) when `true`. |
| `bool isNssActive()` | Reads back the NSS value. |
| `void setResetActive(bool value)` | Puts the module in reset when `true`. |
| `bool isResetActive()` | Reads back the reset value. |
| `bool isBusy()` | Returns the radio busy signal. |

The DIO signals cannot be read directly. They are only available through the
radio interrupt.

## Interrupt

The DIO signals are connected together in an OR configuration and drive a single
**level sensitive** radio interrupt.

| Method | Description |
| ------ | ----------- |
| `void attachInterrupt(callback_function_t callback)` | Attaches and enables the handler, clearing any pending interrupt. Accepts any callable that `std::function<void(void)>` accepts. |
| `void detachInterrupt()` | Disables the interrupt and removes the handler. |
| `bool hasInterrupt()` | Returns `true` if a handler is attached, even when disabled. |
| `void enableInterrupt()` | Enables the interrupt again. If it triggered while disabled, the handler runs immediately. |
| `void disableInterrupt()` | Temporarily disables the interrupt. |
| `bool isInterruptPending()` | Returns `true` if the interrupt is pending. |
| `void clearPendingInterrupt()` | Clears the pending flag. |

> [!WARNING]
> The handler must clear the interrupt flags in the radio or call
> `disableInterrupt()`. Otherwise the interrupt triggers again as soon as the
> handler returns.

## Example

Initialize the radio and read a register with an SPI command:

```C++
#include <SubGhz.h>

void setup() {
  SubGhz.SPI.begin();
  SubGhz.setResetActive(false);

  // The radio starts in sleep mode with its busy signal active.
  SubGhz.SPI.beginTransaction(SubGhz.spi_settings);
  SubGhz.setNssActive(true);
  while (SubGhz.isBusy()) { /* wait */ }

  SubGhz.SPI.transfer(0x1D);                 // Read_Register() command
  SubGhz.SPI.transfer(0x07);                 // Register address MSB
  SubGhz.SPI.transfer(0x40);                 // Register address LSB
  uint8_t status = SubGhz.SPI.transfer(0x0); // Status
  uint8_t value = SubGhz.SPI.transfer(0x0);  // Register value

  SubGhz.setNssActive(false);
  SubGhz.SPI.endTransaction();
}
```

See the `ReadRegister` example of the library.
