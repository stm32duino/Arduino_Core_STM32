# LPS22HB

Arduino library to support the LPS22HB 260-1260 hPa absolute digital output barometer.

## API

* **LPS22HBSensor(TwoWire\*, uint8_t)**: class constructor  
_Params_ pointer to the I2C instance  
_Params_ (optional) address of the component's instance  

* **Enable**: enable sensor  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **Disable**: disable sensor  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **ReadID(uint8_t\*)**: read ID address  
_Params_ pointer where store the ID of the device  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **Reset**: reboot memory content  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **GetPressure(float\*)**: read output register and calculate the pressure in mbar
_Params_ pointer where to store data  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **GetTemperature(float\*)**: read output register and calculate the temperature
_Params_ pointer where to store data  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **GetODR(float\*)**: get the output data rate mode  
_Params_ pointer where to store data  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **SetODR(float)**: set the output data rate mode  
_Params_ data rate to be set  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **ReadReg(uint8_t, uint8_t\*)**: read data from register  
_Params_ register address  
_Params_ pointer to register data  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

* **WriteReg(uint8_t, uint8_t)**: write data to register  
_Params_ register address  
_Params_ register data  
_Returns_ LPS22HB_STATUS_OK in case of success, an error code otherwise  

> [!NOTE]
> This library uses the Wire library presents in the STM32 core by default.

## Examples

* DISCO_IOT_LPS22HB_DataLog_Terminal: reads pressure and temperature values and prints them.

## Source

You can find the source files at  
https://github.com/stm32duino/LPS22HB

## Documentation

The LPS22HB datasheet is available at  
http://www.st.com/content/st_com/en/products/mems-and-sensors/pressure-sensors/lps22hb.html
