# SPBTLE-RF

Arduino library to support the Bluetooth (V4.1 compliant) SPBTLE-RF module.

## API

### BLE module

* **SPBTLERFClass(SPIClass\*, uint8_t, uint8_t, uint8_t, uint8_t)**: class constructor  
_Params_ pointer to SPI interface  
_Params_ BLE module CS pin  
_Params_ BLE module IRQ pin  
_Params_ BLE module reset pin  
_Params_ (optional) BLE module led pin  

* **begin**: enable the BLE module  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **end**: disable the BLE module  

* **update**: update the BLE stack. Must be call as soon as possible.

### Beacon service

* **begin(uint8_t\*, char\*)**: enable the Beacon service in URL mode  
_Params_ pointer to the address of the module to be set  
_Params_ URL to be set  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **begin(uint8_t\*, uint8_t\*, uint8_t\*)**: enable the Beacon service in UID mode  
_Params_ pointer to the address of the module to be set  
_Params_ pointer to ID to be set  
_Params_ pointer to name space to be set  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

### Sensor service

* **begin(const char\*, uint8_t\*)**: enable the Sensor service  
_Params_ pointer to name space to be set  
_Params_ pointer to the address of the module to be set  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **setConnectable**: put the device in connectable mode  

* **isConnected**: check if the device is connected  
_Return_ true if connected or false otherwise  

* **Add_Acc_Service**: add accelerometer service  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Free_Fall_Notify**: send a notification for a free fall detection  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Acc_Update(AxesRaw_t\*)**: update accelerometer values  
_Params_ pointer to structure containing accelerometer values in mg  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Add_Environmental_Sensor_Service**: add environmental service  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Temp_Update(int16_t)**: update temperature value  
_Params_ new temperature value  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Press_Update(uint32_t)**: update pressure value  
_Params_ new pressure value  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Humidity_Update(uint16_t)**: update humidity value  
_Params_ new humidity value  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Add_Time_Service**: add time service  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Update_Time_Characteristics**: update seconds and minutes values  

* **Seconds_Update**: update seconds value  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Minutes_Notify**: send a notification for a minute  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **Add_LED_Service**: add LED service  
_Return_ SPBTLERF_OK in case of success, an error code otherwise  

* **LED_State**: read the LED state  
_Return_ led state (true or false)  

> [!NOTE]
> This library provides a basic BLE class to enable or disable the Bluetooth Low Energy module
> and 2 profiles as examples. You can use the BLE stack to create your own profile.

## Examples

* DISCO_IOT_BeaconDemo: enable a Beacon service (UID or URL)  
* DISCO_IOT_SensorDemo: enable an environmental sensor service (accelerometer, temperature, humidity, pressure and time)  

## Source

You can find the source files at  
https://github.com/stm32duino/SPBTLE-RF

## Documentation

The SPBTLE-RF module datasheet is available at  
http://www.st.com/content/st_com/en/products/wireless-connectivity/bluetooth-bluetooth-low-energy/spbtle-rf.html
