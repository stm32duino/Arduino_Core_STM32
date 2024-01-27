# LEAT EchoStar Terminal BSP

###### This document is applied to core version 12.7.1-0

This reposistory contains the Arduino Core for LEAT EchoStar Terminals.

### EchoLab-6
 * This example demonstrates how to use use the GNSS and Echostar network for tracking application
 * This code can also be used to test Echostar AT commands, GNSS UART and I2C sensors (BME280 and KX025)
 * The terminal try to get a GNSS fix and send to Echo network its position + sensing information

### Supported boards: 

- **EchoStar-term-6**
  - Microcontroller: STM32WB5MMGH6TR
  - Radio: EchoStar EM2050
  - GNSS: Quectel LC76F
  - Sensors:
    - Accelerometers KX023-1025
    - Humidity, Pressure and Temperature Sensor BME280

# External libraries

There are external libraries used in these example. They could be found & installed from this list:
- [adafruit/Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library)
- [adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [nguyenmanhthao996tn/Kionix_KX023](https://github.com/nguyenmanhthao996tn/Kionix_KX023)
- [stevemarple/MicroNMEA](https://github.com/stevemarple/MicroNMEA)

# Credit

- [stm32duino/Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)

---
#### *Maintained by Prof. Fabien Ferrero & mtnguyen at Laboratoire d’Electronique, Antennes et Télécommunications (LEAT)*
🇫🇷 🇻🇳
