# LEAT EchoStar Terminal BSP

This reposistory contains the Arduino Core for LEAT EchoStar Terminals.

<img src="https://nguyenmanhthao996tn.github.io/other_resource/Echo_term_6.jpg" width="350">

### Supported boards:


- **EchoStar-term-7**
  - Microcontroller: STM32U585CIT6
  - Radio: EchoStar EM2050
  - GNSS: Quectel LC29H
  - Sensors:
    - Accelerometers KX023-1025
    - Humidity, Pressure and Temperature Sensor BME280
    - Gas sensor BME680/688
  - External IO Headers for ADC, SPI, USART, I2C, etc. 

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

|  No.  |         Define          | Term 6 Pin | Term 7 Pin | Description                                              |
| :---: | :---------------------: | :--------: | :--------: | -------------------------------------------------------- |
|   1   |       LED_BUILTIN       |    PA13    |    PA15    | Integrated LED pin                                       |
|   2   |        USER_BTN         |    PC2     |    PA14    | Integrated button pin                                    |
|   3   | SENSORS_BATERY_ADC_PIN  |    PA2     |    PB1     | ADC pin that connected to resistor voltage divider       |
|   4   | ECHOSTAR_PWR_ENABLE_PIN |     -1     |    PH1     | EchoStar EM2050 LDO enable pin                           |
|   5   |    ECHOSTAR_TXD_PIN     |    PC0     |    PA10    | EchoStar EM2050 Serial TxD pin (assigned to MCU RxD pin) |
|   6   |    ECHOSTAR_RXD_PIN     |    PC1     |    PA9     | EchoStar EM2050 Serial RxD pin (assigned to MCU TxD pin) |
|   7   |   ECHOSTAR_SWCTRL_PIN   |    PB4     |    PB0     | EchoStar EM2050 SWCTRL pin (MCU should read only)        |
|   8   |    ECHOSTAR_RTS_PIN     |    PC12    |    PB15    | EchoStar EM2050 RTS pin                                  |
|   9   |    ECHOSTAR_BOOT_PIN    |    PC11    |    PA5     | EchoStar EM2050 Bootloader enable pin                    |
|  10   |    ECHOSTAR_nRST_PIN    |    PC10    |    PA6     | EchoStar EM2050 nRST pin                                 |
|  11   |   DPDT_PWR_ENABLE_PIN   |     -1     |    PA7     | Sband RF Switch power supply pin                         |
|  12   |      DPDT_CTRL_PIN      |    PB8     |    PA4     | Sband RF Switch control pin                              |
|  13   |      GNSS_TXD_PIN       |    PB7     |    PA1     | GNSS Serial TxD pin (assigned to MCU RxD pin)            |
|  14   |      GNSS_RXD_PIN       |    PA9     |    PA0     | GNSS Serial RxD pin (assigned to MCU TxD pin)            |
|  15   |     GNSS_WAKEUP_PIN     |    PB5     |     -1     | GNSS Wakeup pin                                          |
|  16   |   GNSS_PWR_ENABLE_PIN   |    PA1     |    PC13    | GNSS LDO enable pin                                      |
|  17   |      GNSS_1PPS_PIN      |    PA0     |     -1     | GNSS 1PPS pin                                            |
|  18   |     GNSS_V_BCKP_PIN     |    PC3     |    PH0     | GNSS V_BCKP pin                                          |
|  19   | SENSORS_PWR_ENABLE_PIN  |    PA14    |    PA13    | Sensors LDO enable pin                                   |
|  20   |   SENSORS_I2C_SDA_PIN   |    PA10    |    PB7     | I2C SDA pin for sensor communication                     |
|  21   |   SENSORS_I2C_SCL_PIN   |    PB6     |    PB8     | I2C SCL pin for sensor communication                     |
|  22   |  SENSORS_ACC_INT_1_PIN  |    PB11    |    PA8     | KX023 INT1 pin                                           |
|  23   |  SENSORS_ACC_INT_2_PIN  |    PB10    |     -1     | KX023 INT2 pin                                           |
|  24   |  SENSORS_ACC_TRIG_PIN   |    PB12    |     -1     | KX023 TRIG pin                                           |
|  25   | SENSORS_BME280_ADDRESS  |    0x76    |    0x76    | I2C Address of BME280                                    |
|  25   | SENSORS_BME680_ADDRESS  |    0x76    |    0x76    | I2C Address of BME680/688                                |
|  26   |  SENSORS_KX023_ADDRESS  |    0x1F    |    0x1F    | I2C Address of KX023                                     |

*<u>Note</u>: `-1` implies that the function is **NOT AVAILABLE** on that board version. Please consider not to use it.*

# To-do

- [ ] Verify the installation & functionalites on different environments

|                          |      Windows       |       Linux        |      MacOS      |
| ------------------------ | :----------------: | :----------------: | :-------------: |
| ArduinoIDE 2             | :heavy_check_mark: | :heavy_check_mark: | :grey_question: |
| Arduino IDE Legacy 1.8.x | :heavy_check_mark: | :heavy_check_mark: | :grey_question: |

# Credit

- [stm32duino/Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)

---
#### *Maintained by Prof. Fabien Ferrero & mtnguyen at Laboratoire d’Electronique, Antennes et Télécommunications (LEAT)*
