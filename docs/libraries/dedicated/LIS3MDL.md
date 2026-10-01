# LIS3MDL

Arduino library to support the LIS3MDL high-performance 3-axis magnetometer.

## API

* **LIS3MDLSensor(TwoWire\*, uint8_t)**: class constructor  
_Params_ pointer to the I2C instance  
_Params_ (optional) address of the component's instance  

* **Enable**: enable sensor  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **Disable**: disable sensor  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **ReadID(uint8_t\*)**: read ID address  
_Params_ pointer where store the ID of the device  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **GetAxes(int32_t\*)**: read magnetometer data  
_Params_ pointer where to store data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **GetSensitivity(float\*)**: read magnetometer sensitivity  
_Params_ pointer where to store data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **GetAxesRaw(int16_t\*)**: read magnetometer raw data  
_Params_ pointer where to store data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **GetODR(float\*)**: get the output data rate mode  
_Params_ pointer where to store data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **SetODR(float)**: set the output data rate mode  
_Params_ data rate to be set  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **GetFS(float\*)**: get the magnetometer full scale  
_Params_ pointer where to store data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **SetFS(float)**: set the magnetometer full scale  
_Params_ full scale to be set  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **ReadReg(uint8_t, uint8_t\*)**: read data from register  
_Params_ register address  
_Params_ pointer to register data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

* **WriteReg(uint8_t, uint8_t)**: write data to register  
_Params_ register address  
_Params_ register data  
_Returns_ LIS3MDL_STATUS_OK in case of success, an error code otherwise  

> [!NOTE]
> This library uses the Wire library presents in the STM32 core by default.

## Examples

* DISCO_IOT_LIS3MDL_DataLog_Terminal: reads magnetometer axes values and prints them.

## Source

You can find the source files at  
https://github.com/stm32duino/LIS3MDL

## Documentation

The LIS3MDL datasheet is available at  
http://www.st.com/content/st_com/en/products/mems-and-sensors/e-compasses/lis3mdl.html
