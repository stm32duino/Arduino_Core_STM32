# EEPROM emulation

EEPROM emulation is based on Arduino API:
https://docs.arduino.cc/learn/built-in-libraries/eeprom/

Emulation is made in Flash, with all constraints related to Flash operation:

- whole sector/page erased and written for each write operation. This can be very long depending on sector/page size.
- limited Flash life cycle write operation

In addition to Arduino API, to mitigate Flash constraints, it is possible to use buffered API:
Write operations are made in an intermediate RAM buffer, and only at the end (after writing several parameters for example) the buffer is copied in Flash. Thus only 1 write operation for a whole bunch of data.
Example is available here: https://github.com/stm32duino/STM32Examples/tree/main/examples/NonReg/BufferedEEPROM
```C
void eeprom_buffer_fill(); // This function copies the data from flash into the buffer
void eeprom_buffer_flush(); // This function writes the buffer content into the flash
uint8_t eeprom_buffered_read_byte(const uint32_t pos); // Function reads a byte from the eeprom buffer
void eeprom_buffered_write_byte(uint32_t pos, uint8_t value); // Function writes a byte to the eeprom buffer
```
By default, EEPROM emulation storage correspond to the last sector/page of Flash,
and its size correspond to the size of the last sector/page.
Nevertheless it is possible to customize address and size used for EEPROM.
In this case, following switches should be defined (in variant.h or [`build_opt.h`][build_opt.h])

- `FLASH_BASE_ADDRESS`
- `FLASH_DATA_SECTOR` or `FLASH_PAGE_NUMBER` (depending on STM32 family used)

see example of variant implementation: [PR #938](https://github.com/stm32duino/Arduino_Core_STM32/pull/938)

> [!WARNING]
> Single/dual bank configuration:
>
> Default last sector used correspond to default board configuration.
>
> For example, NUCLEO_F767ZI is by default configured in single bank. Last sector correspond to this bank configuration.
> If this configuration is changed, it is then mandatory to customize `FLASH_BASE_ADDRESS`/`FLASH_DATA_SECTOR`,
> even to use last sector of Flash.

[build_opt.h]: ../../customization/Customize-build-options-using-build_opt.h.md
