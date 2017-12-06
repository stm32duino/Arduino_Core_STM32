## SPI

STM32 SPI library has been modified with the possibility to manage several CS pins without to stop the SPI interface.  
_We do not describe here the [SPI Arduino API](https://www.arduino.cc/en/Reference/SPI) but the functionalities added._  

We give to the user 3 possiblities about the management of the CS pin:  
1. the CS pin is managed directly by the user code before to transfer the data (like the Arduino SPI library)  
2. the user gives the CS pin number to the library API and the library manages itself the CS pin (see example below)  
3. the user uses a hardware CS pin linked to the SPI peripheral  

### New API functions

* **`SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel)`**: alternative class constructor  
_Params_ SPI mosi pin  
_Params_ SPI miso pin  
_Params_ SPI sclk pin  
_Params_ (optional) SPI ssel pin. This pin must be an hardware CS pin. If you configure this pin, the chip select will be managed by the SPI peripheral. Do not use API functions with CS pin in parameter.  

* **`void SPIClass::begin(uint8_t _pin)`**: initialize the SPI interface and add a CS pin  
_Params_ spi CS pin to be managed by the SPI library  

* **`void beginTransaction(uint8_t pin, SPISettings settings)`**: allows to configure the SPI with other parameter. These new parameter are saved this an associated CS pin.  
_Params_ SPI CS pin to be managed by the SPI library  
_Params_ SPI settings  

* **`void endTransaction(uint8_t pin)`**: removes a CS pin and the SPI settings associated  
_Params_ SPI CS pin managed by the SPI library  

**_Note 1_** The following functions must be called after initialization of the SPI instance with `begin()` or `beginTransaction()`.  
If you have several device to manage, you can call `beginTransaction()` several time with different CS pin in parameter.  
Then you can call the following functions with different CS pin without call again `beginTransaction()` (until you call `end()` or `endTransaction()`).  

**_Note 2_** If the mode is set to `SPI_CONTINUE`, the CS pin is kept enabled. Be careful in case you use several CS pin.  

* **`byte transfer(uint8_t pin, uint8_t _data, SPITransferMode _mode = SPI_LAST)`**: write/read one byte  
_Params_ SPI CS pin managed by the SPI library  
_Params_ data to write  
_Params_ (optional) if `SPI_LAST` CS pin is reset, `SPI_CONTINUE` the CS pin is kept enabled.  
_Return_ byte received  

* **`uint16_t transfer16(uint8_t pin, uint16_t _data, SPITransferMode _mode = SPI_LAST)`**: write/read half-word  
_Params_ SPI CS pin managed by the SPI library  
_Params_ 16bits data to write  
_Params_ (optional) if `SPI_LAST` CS pin is reset, `SPI_CONTINUE` the CS pin is kept enabled.  
_Return_ 16bits data received  

* **`void transfer(uint8_t pin, void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST)`**: write/read several bytes. Only one buffer used to write and read the data  
_Params_ SPI CS pin managed by the SPI library  
_Params_ pointer to data to write. The data will be replaced by the data read.  
_Params_ number of data to write/read.
_Params_ (optional) if `SPI_LAST` CS pin is reset, `SPI_CONTINUE` the CS pin is kept enabled.  

* **`void transfer(byte _pin, void *_bufout, void *_bufin, size_t _count, SPITransferMode _mode = SPI_LAST)`**: write/read several bytes. One buffer for the output data and one for the input data  
_Params_ SPI CS pin managed by the SPI library  
_Params_ pointer to data to write.  
_Params_ pointer where to store the data read.  
_Params_ number of data to write/read.  
_Params_ (optional) if `SPI_LAST` CS pin is reset, `SPI_CONTINUE` the CS pin is kept enabled.  

### Example

This is an example of the use of the CS pin management:  

```C++
SPI.begin(2); //Enables the SPI instance with default settings and attachs the CS pin  
SPI.beginTransaction(1, settings); //Attachs another CS pin and configure the SPI instance with other settings  
SPI.transfer(1, 0x52); //Transfers data to the first device
SPI.transfer(2, 0xA4); //Transfers data to the second device. The SPI instance is configured with the right settings  
SPI.end() //SPI instance is disabled
```
