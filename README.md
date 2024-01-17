# LEAT-EchoStar-Terminal-BSP

This reposistory contains the Arduino Core for LEAT EchoStar Terminals.

<img src="https://nguyenmanhthao996tn.github.io/other_resource/Echo_term_6.jpg" width="350">

### Supported boards:

- **EchoStar-term-6**
  - Microcontroller: STM32WB5MMGH6TR
  - Radio: EchoStar EM2050
  - GNSS: Quectel LC76F
  - Sensors:
    - Accelerometers KX023-1025
    - Humidity, Pressure and Temperature Sensor BME280


# How to install this Core?

1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software) (at least version v1.8.13)
2. Start the Arduino IDE
3. Go to Preferences
4. Copy & Add the following JSON URL to your "**Additional Board Manager URL**"
```
https://fabienferrero.github.io/ArduinoBoardManagerJSON/package_leat-echostar-terminal_index.json
``` 
5. Open the Boards Manager from the **Tools** -> **Board menu** and install "_LEAT EchoStar Terminals_"
6. Select your board from the **Tools** -> **Board menu**
7. Config the approriate settings in **Tools** menu, and upload your source code.

# Integrated example

Since [version 2.8.0-dev1](https://github.com/nguyenmanhthao996tn/LEAT-EchoStar-Terminal-BSP/releases/tag/2.8.0-dev1), there are integrated examples dedicated for **LEAT EchoStar Terminals** in **File** &rightarrow; **Examples** &rightarrow; **EchoStar_Term_Examples**. The list of currently available examples:
- 0_LED_n_Button
- 1_USB_Serial_ByPass_for_GNSS
- 2_USB_Serial_ByPass_for_EM2050
- 3_Sensors_I2C_Scanner
- 4_Sensors_BME280
- 5_Sensors_KX023
- 6_GNSS_MicroNMEA

There are external libraries used in these example. They could be found & installed from this list:
- [adafruit/Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library)
- [adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [nguyenmanhthao996tn/Kionix_KX023](https://github.com/nguyenmanhthao996tn/Kionix_KX023)
- [stevemarple/MicroNMEA](https://github.com/stevemarple/MicroNMEA)

# Pre-define for Pin Name/Number & others

The variant in this core includes pre-define for MCU pins connected to on-boards peripherals / modules. Details are listed as follows:

### EchoStar-term-6

```
// On-board LED pin number
#define LED_BUILTIN PA13

// On-board user button
#define USER_BTN PC2

// EchoStar EM2050 Module
#define ECHOSTAR_TXD_PIN PC0
#define ECHOSTAR_RXD_PIN PC1
#define ECHOSTAR_SWCTRL_PIN PB4
#define DPDT_CTRL_PIN PB8

// GNSS
#define GNSS_TXD_PIN PB7
#define GNSS_RXD_PIN PA9
#define GNSS_WAKEUP_PIN PB5
#define GNSS_ENABLE_PIN PA1
#define GNSS_V_BCKP_PIN PC3

// Sensors
#define SENSORS_ENABLE_PIN PA14
#define SENSORS_I2C_SDA_PIN PA10
#define SENSORS_I2C_SCL_PIN PB6

#define SENSORS_BME280_ADDRESS 0x76
#define SENSORS_KX023_ADDRESS 0x1F
```

# To-do

- [ ] Verify the installation & functionalites on different environments

|                          |      Windows       |      Linux      |      MacOS      |
| ------------------------ | :----------------: | :-------------: | :-------------: |
| ArduinoIDE 2             |  :grey_question:   | :grey_question: | :grey_question: |
| Arduino IDE Legacy 1.8.x | :heavy_check_mark: | :grey_question: | :grey_question: |

# Known issues

- Need to install [stm32duino/Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)

# Credit

- [stm32duino/Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)

---
#### *Maintained by Prof. Fabien Ferrero & mtnguyen at Laboratoire d’Electronique, Antennes et Télécommunications (LEAT)*
