## LoRa

### [RAK811 LoRa Tracker](https://www.rakwireless.com/en/)

Hereafter some application codes which can be used for RAK811 LoRa board provided by [@RAKWireless](https://github.com/RAKWireless) in [#859](https://github.com/stm32duino/Arduino_Core_STM32/issues/859).

#### Power on for LoRa chip:
```C++
  pinMode(RADIO_XTAL_EN, OUTPUT);  //Power LoRa module
  digitalWrite(RADIO_XTAL_EN, HIGH);
```
#### External antenna receiving and transmitting state switching pin configuration:
##### Receive state:
``` C++
  pinMode(RADIO_RF_CRX_RX, OUTPUT);  
  digitalWrite(RADIO_RF_CRX_RX, HIGH);  //control LoRa work to receive
  pinMode(RADIO_RF_CTX_PA, OUTPUT);  
  digitalWrite(RADIO_RF_CTX_PA, LOW);
```
##### Transmit state:
```
  pinMode(RADIO_RF_CRX_RX, OUTPUT);  
  digitalWrite(RADIO_RF_CRX_RX, LOW);  
  pinMode(RADIO_RF_CTX_PA,OUTPUT);  
  digitalWrite(RADIO_RF_CTX_PA, HIGH);  //control LoRa send by PA_BOOST
``` 
More details can be found here:
https://github.com/RAKWireless/RAK811_LoRaWAN_Arduino