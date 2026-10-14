# SPI

STM32 SPI library has been modified with the possibility to manage hardware CS pin linked to the SPI peripheral.
This section documents STM32-specific additions to the [standard SPI API](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/).

There are two ways to manage the CS pin:

- the CS pin is managed directly by the user code before to transfer the data (like the Arduino SPI library)
- the user uses a hardware CS pin linked to the SPI peripheral

## New SPISetting parameter

* `noReceive`: value can be `SPI_TRANSMITRECEIVE` or `SPI_TRANSMITONLY`. It allows to skip receive data after transmitting.

## New API functions

* `SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel)`: alternative class constructor
_Params_ SPI `mosi` pin
_Params_ SPI `miso` pin
_Params_ SPI `sclk` pin
_Params_ (optional) SPI `ssel` pin. This pin must be an hardware CS pin. If you configure this pin, the chip select will be managed by the SPI peripheral.

#### Example

This is an example of the use of the hardware CS pin linked to the SPI peripheral:

```C++
#include <SPI.h>
//            MOSI  MISO  SCLK   SSEL
SPIClass SPI_3(PC12, PC11, PC10, PC9);
SPISettings settings(1000000, MSBFIRST, SPI_MODE0);

void setup() {
  SPI_3.begin(); // Enable the SPI_3 instance with default SPISsettings
  SPI_3.beginTransaction(settings); // Configure the SPI_3 instance
  SPI_3.transfer(0x52); // Transfers data to the first device
  SPI_3.end(); // SPI_3 instance is disabled
}
```

### Change default `SPI` instance pins
It is also possible to change the default pins used by the `SPI` instance using above API:

> [!WARNING]
> Have to be called before `begin()`.

* `void setMISO(uint32_t miso)`
* `void setMOSI(uint32_t mosi)`
* `void setSCLK(uint32_t sclk)`
* `void setSSEL(uint32_t ssel)`
* `void setMISO(PinName miso)`
* `void setMOSI(PinName mosi)`
* `void setSCLK(PinName sclk)`
* `void setSSEL(PinName ssel)`

> [!NOTE]
> Using `setSSEL()` allows to enable hardware CS pin management linked to the SPI peripheral.

#### Example:
```C++
    SPI.setMISO(PC_4); // using pin name PY_n
    SPI.setMOSI(PC2); // using pin number PYn
    SPI.begin(2);
```
