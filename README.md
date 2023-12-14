# LEAT-EchoStar-Terminal-BSP

This reposistory contains the Arduino Core for LEAT EchoStar Terminals.

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

# To-do

- [ ] Verify the installation & functionalites on different environments

|                          |      Windows       |      Linux      |      MacOS      |
| ------------------------ | :----------------: | :-------------: | :-------------: |
| ArduinoIDE 2             |  :grey_question:   | :grey_question: | :grey_question: |
| Arduino IDE Legacy 1.8.x | :heavy_check_mark: | :grey_question: | :grey_question: |

# Credit

- [stm32duino/Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)

---
#### *Maintained by Prof. Fabien Ferrero & mtnguyen at Laboratoire d’Electronique, Antennes et Télécommunications (LEAT)*