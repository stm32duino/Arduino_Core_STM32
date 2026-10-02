# VL53L0X

Arduino library to support the VL53L0X Time-of-Flight and gesture-detection sensor.

## API

The API provides simple distance measure, single swipe gesture detection,
directional (left/right) swipe gesture detection and single tap gesture detection.

### VL53L0X class

* **VL53L0X(TwoWire\*, int, int, uint8_t)**: class constructor

_Params_ pointer to I2C instance  
_Params_ sensor shutdown pin  
_Params_ sensor interrupt pin  
_Params_ (optional) device address (0x29 by default)  

* **VL53L0X_On**: power on the sensor

* **VL53L0X_Off**: power off the sensor

* **InitSensor**: initialize the sensor with default values

_Return_ 0 on Success, error code otherwise  

* **StartMeasurementSimplified(OperatingMode, void(*)(void))**: Start the measure indicated by operating mode

_Params_ specifies requested measure (range_single_shot_polling,
   range_continuous_polling,
   range_continuous_interrupt,
   range_continuous_polling_low_threshold,
   range_continuous_polling_high_threshold,
   range_continuous_polling_out_of_window,
   range_continuous_interrupt_low_threshold,
   range_continuous_interrupt_high_threshold,
   range_continuous_interrupt_out_of_window)  
_Params_ pointer to callback function. Must be not NULL in case of interrupt measure  
_Return_ 0 on Success, error code otherwise  

* **GetMeasurementSimplified(OperatingMode, VL53L0X_RangingMeasurementData_t\*)**: Get results for the measure indicated by operating mode

_Params_ specifies requested measure (range_single_shot_polling,
   range_continuous_polling,
   range_continuous_interrupt,
   range_continuous_polling_low_threshold,
   range_continuous_polling_high_threshold,
   range_continuous_polling_out_of_window,
   range_continuous_interrupt_low_threshold,
   range_continuous_interrupt_high_threshold,
   range_continuous_interrupt_out_of_window)  
_Params_ Data pointer to the MeasureData_t structure to read data in to  
_Return_ 0 on Success, error code otherwise  

* **StopMeasurementSimplified(OperatingMode)**: Stop the currently running measure indicate by operating_mode

_Params_ specifies requested measure (range_single_shot_polling,
   range_continuous_polling,
   range_continuous_interrupt,
   range_continuous_polling_low_threshold,
   range_continuous_polling_high_threshold,
   range_continuous_polling_out_of_window,
   range_continuous_interrupt_low_threshold,
   range_continuous_interrupt_high_threshold,
   range_continuous_interrupt_out_of_window)  
_Return_ 0 on Success, error code otherwise  

* **WaitDeviceBooted**: Wait for device booted after chip enable (hardware standby)

_Return_ 0 on Success, error code otherwise  

* **Prepare**: Prepare device for operation. Does static initialization and reprogram common default setting.

_Return_ 0 on Success, error code otherwise  

* **GetDistance(uint32_t\*)**: Get ranging result and only that

_Params_ pointer to range distance (value in millimeter)  
_Return_ 0 on Success, error code otherwise  

* **SetDeviceAddress(int)**: Set new device i2c address

_Params_ The new i2c address (7bit)  
_Return_ 0 on Success, error code otherwise  

_You can find a complete description of the following functions in the API user manual (UM2039)_
* **Init**
* **StaticInit**
* **PerformRefCalibration(uint8_t\*, uint8_t\*)**
* **PerformRefSpadManagement(uint32_t\*, uint8_t\*)**
* **SetDeviceMode(VL53L0X_DeviceModes)**
* **SetMeasurementTimingBudgetMicroSeconds(uint32_t)**
* **StartMeasurement**
* **StopMeasurement**
* **GetMeasurementDataReady(uint8_t\*)**
* **GetRangingMeasurementData(VL53L0X_RangingMeasurementData_t\*)**
* **ClearInterruptMask(uint32_t)**

### ToF gestures

* **tof_gestures_initDIRSWIPE_1(int32_t, long, long, Gesture_DIRSWIPE_1_Data_t\*)**: Initialize directional (left/right) gesture detection

_Params_ swipe threshold  
_Params_ Minimum duration of a swipe to be detected  
_Params_ Maximum duration of a swipe to be detected  
_Params_ pointer to Gesture_DIRSWIPE_1_Data_t structure  
_Return_ 0 on Success, error code otherwise  

* **tof_gestures_detectDIRSWIPE_1(int32_t, int32_t, Gesture_DIRSWIPE_1_Data_t\*)**: Detect directional (left/right) gesture

_Params_ left range value in millimeter    
_Params_ right range value in millimeter    
_Params_ pointer to Gesture_DIRSWIPE_1_Data_t structure  
_Return_ One of these gestures code: GESTURES_SWIPE_LEFT_RIGHT, GESTURES_SWIPE_RIGHT_LEFT, GESTURES_NULL, GESTURES_DISCARDED_TOO_SLOW or GESTURES_DISCARDED_TOO_FAST  

* **tof_gestures_initSWIPE_1(Gesture_SWIPE_1_Data_t\*)**: Initialize single swipe gesture detection

_Params_ pointer to Gesture_SWIPE_1_Data_t structure  
_Return_ 0 on Success, error code otherwise  

* **tof_gestures_detectSWIPE_1(int32_t, Gesture_SWIPE_1_Data_t\*)**: Detect single swipe gesture

_Params_ range value in millimeter  
_Params_ pointer to Gesture_SWIPE_1_Data_t structure  
_Return_ One of these gestures code: GESTURES_HAND_ENTERING, GESTURES_HAND_LEAVING, GESTURES_SINGLE_SWIPE or GESTURES_NULL, GESTURES_DISCARDED, GESTURES_DISCARDED_TOO_SLOW  

* **tof_gestures_initTAP_1(Gesture_TAP_1_Data_t\*)**: Initialize single tap gesture detection

_Params_ pointer to Gesture_TAP_1_Data_t structure  
_Return_ 0 on Success, error code otherwise  

* **tof_gestures_detectTAP_1(int32_t, Gesture_TAP_1_Data_t\*)**: Detect single tap gesture

_Params_ range value in millimeter  
_Params_ pointer to Gesture_TAP_1_Data_t structure  
_Return_ One of these gestures code: GESTURES_SINGLE_TAP or GESTURES_NULL  

* **tof_initMotion(int, MotionData_t\*)**: Initialize motion detector

_Params_ range threshold  
_Params_ pointer to MotionData_t structure  
_Return_ 0 on Success, error code otherwise  

* **tof_getMotion(int32_t, MotionData_t\*)**: return current motion state

_Params_ range value in millimeter  
_Params_ pointer to MotionData_t structure  
_Return_ One of these gestures code: GESTURES_MOTION_NULL, GESTURES_MOTION_DOWN_STATE, GESTURES_MOTION_UP_STATE, GESTURES_MOTION_RAISE_UP or GESTURES_MOTION_DROP_DOWN  

> [!NOTE]
> The maximum detection distance is influenced by the color of the target and the
> indoor or outdoor situation due to absence or presence of external infrared.
> The detection range is between ~40cm and ~120cm. (see chapter 5 of the VL53L0X
> datasheet).
> If you need an higher accuracy (up to +200cm), you should implement your own function.

## Examples

* DISCO_IOT_53L0A1_DataLogTerminal: gets proximity value and prints it  
* DISCO_IOT_53L0A1_Gesture_Swipe1: detects a simple swipe gesture.
* DISCO_IOT_53L0A1_Gesture_Tap1: detects a simple tap gesture.

## Source

You can find the source files at  
https://github.com/stm32duino/VL53L0X

## Documentation

The VL53L0X datasheet is available at  
http://www.st.com/content/st_com/en/products/imaging-and-photonics-solutions/proximity-sensors/vl53l0x.html
