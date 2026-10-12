# LSM6DSL

Arduino library to support the LSM6DSL 3D accelerometer and 3D gyroscope.

## API

* **LSM6DSLSensor(TwoWire\*, uint8_t)**: class constructor  
_Params_ pointer to the I2C instance  
_Params_ (optional) address of the component's instance  

* **Enable_X**: enable accelerometer  
  **Enable_G**: enable gyroscope  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_X**: disable accelerometer  
  **Disable_G**: disable gyroscope  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **ReadID(uint8_t\*)**: read ID address  
_Params_ pointer where store the ID of the device  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_X_Axes(int32_t\*)**: read accelerometer data  
  **Get_G_Axes(int32_t\*)**: read gyroscope data  
_Params_ pointer where store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_X_Sensitivity(float\*)**: read accelerometer sensitivity  
  **Get_G_Sensitivity(float\*)**: read gyroscope sensitivity  
_Params_ pointer where store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_X_AxesRaw(float\*)**: read accelerometer raw data  
  **Get_G_AxesRaw(float\*)**: read gyroscope raw data  
_Params_ pointer where store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_X_ODR(float\*)**: read the accelerometer output data rate  
  **Get_G_ODR(float\*)**: read the gyroscope output data rate  
_Params_ pointer where to store data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_X_ODR(float)**: set the accelerometer output data rate  
  **Set_G_ODR(float)**: set the gyroscope output data rate  
_Params_ data rate to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_X_FS(float\*)**: read the accelerometer full scale  
  **Get_G_FS(float\*)**: read the gyroscope full scale  
_Params_ pointer where to store data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_X_FS(float)**: set the accelerometer full scale  
  **Set_G_FS(float)**: set the gyroscope full scale  
_Params_ full scale to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Free_Fall_Detection(LSM6DSL_Interrupt_Pin_t)**: enable free fall detection. Accelerometer ODR sets to 416Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Free_Fall_Detection**: disable free fall detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Free_Fall_Threshold(uint8_t)**: set the accelerometer free fall detection threshold  
_Params_ the threshold to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Pedometer**: enable the pedometer feature. Accelerometer ODR sets to 26Hz and full scale to 2g.  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Pedometer**: disable the pedometer feature  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_Step_Counter(uint16_t\*)**: read step counter  
_Params_ pointer where to store data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Reset_Step_Counter**: reset step counter  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Pedometer_Threshold(uint8_t)**: set the pedometer threshold  
_Params_ the threshold to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Tilt_Detection(LSM6DSL_Interrupt_Pin_t)**: enable tilt detection. Accelerometer ODR sets to 26Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Tilt_Detection**: disable tilt detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Wake_Up_Detection(LSM6DSL_Interrupt_Pin_t)**: enable wake up detection. Accelerometer ODR sets to 416Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Wake_Up_Detection**: disable wake up detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Wake_Up_Threshold(uint8_t)**: set the wake up threshold  
_Params_ the threshold to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Single_Tap_Detection(LSM6DSL_Interrupt_Pin_t)**: enable the single tap detection. Accelerometer ODR sets to 416Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Single_Tap_Detection**: disable single tap detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_Double_Tap_Detection(LSM6DSL_Interrupt_Pin_t)**: enable the double tap detection. Accelerometer ODR sets to 416Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_Double_Tap_Detection**: disable double tap detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Tap_Threshold(uint8_t)**: set the tap threshold  
_Params_ the threshold to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Tap_Shock_Time(uint8_t)**: set the tap shock time window  
_Params_ the shock time window to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Tap_Quiet_Time(uint8_t)**: set the tap quiet time window  
_Params_ the quiet time window to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Set_Tap_Duration_Time(uint8_t)**: set the tap duration of the time window  
_Params_ the duration of the time window to be set  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Enable_6D_Orientation(LSM6DSL_Interrupt_Pin_t)**: enable the 6D orientation detection. Accelerometer ODR sets to 416Hz and full scale to 2g.  
_Params_ (optional) interrupt pin to be used  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Disable_6D_Orientation**: disable the 6D orientation detection  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_XL(uint8_t\*)**: read the XL axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_XH(uint8_t\*)**: read the XH axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_YL(uint8_t\*)**: read the YL axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_YH(uint8_t\*)**: read the YH axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_ZL(uint8_t\*)**: read the ZL axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_6D_Orientation_ZH(uint8_t\*)**: read the ZH axis data  
_Params_ pointer where to store the data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **Get_Event_Status(LSM6DSL_Event_Status_t\*)**: read the status of all hardware events
_Params_ pointer where to store the event status
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **ReadReg(uint8_t, uint8_t\*)**: read data from register  
_Params_ register address  
_Params_ pointer to register data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

* **WriteReg(uint8_t, uint8_t)**: write data to register  
_Params_ register address  
_Params_ register data  
_Returns_ LSM6DSL_STATUS_OK in case of success, an error code otherwise  

> [!NOTE]
> This library uses the Wire library presents in the STM32 core by default.

## Examples

* DISCO_IOT_6DOrientation: detects and prints 6D orientation event
* DISCO_IOT_DoubleTap: detects and prints double tap event
* DISCO_IOT_FreeFall: detects and prints free fall event
* DISCO_IOT_LS6DSL_DataLog_Terminal: reads accelerometer and gyroscope values and prints them
* DISCO_IOT_MultiEvent: detects and prints free fall, tap, double tap, tilt, wake up, 6D orientation and step events
* DISCO_IOT_Pedometer: detects and prints step event
* DISCO_IOT_Tap: detects and prints single tap event
* DISCO_IOT_Tilt: detects and prints tilt event
* DISCO_IOT_WakeUp: detects and prints wakeup event

## Source

You can find the source files at  
https://github.com/stm32duino/LSM6DSL

## Documentation

The LSM6DSL datasheet is available at  
http://www.st.com/content/st_com/en/products/mems-and-sensors/inemo-inertial-modules/lsm6dsl.html
