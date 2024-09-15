#include "Adafruit_Sensor.h"

/**************************************************************************/
/*!
    @brief  Prints sensor information to serial console
*/
/**************************************************************************/
void Adafruit_Sensor::printSensorDetails(void) {
  sensor_t sensor;
  getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print(F("Sensor:       "));
  Serial.println(sensor.name);
  Serial.print(F("Type:         "));
  switch ((sensors_type_t)sensor.type) {
  case SENSOR_TYPE_ACCELEROMETER:
    Serial.print(F("Acceleration (m/s2)"));
    break;
  case SENSOR_TYPE_MAGNETIC_FIELD:
    Serial.print(F("Magnetic (uT)"));
    break;
  case SENSOR_TYPE_ORIENTATION:
    Serial.print(F("Orientation (degrees)"));
    break;
  case SENSOR_TYPE_GYROSCOPE:
    Serial.print(F("Gyroscopic (rad/s)"));
    break;
  case SENSOR_TYPE_LIGHT:
    Serial.print(F("Light (lux)"));
    break;
  case SENSOR_TYPE_PRESSURE:
    Serial.print(F("Pressure (hPa)"));
    break;
  case SENSOR_TYPE_PROXIMITY:
    Serial.print(F("Distance (cm)"));
    break;
  case SENSOR_TYPE_GRAVITY:
    Serial.print(F("Gravity (m/s2)"));
    break;
  case SENSOR_TYPE_LINEAR_ACCELERATION:
    Serial.print(F("Linear Acceleration (m/s2)"));
    break;
  case SENSOR_TYPE_ROTATION_VECTOR:
    Serial.print(F("Rotation vector"));
    break;
  case SENSOR_TYPE_RELATIVE_HUMIDITY:
    Serial.print(F("Relative Humidity (%)"));
    break;
  case SENSOR_TYPE_AMBIENT_TEMPERATURE:
    Serial.print(F("Ambient Temp (C)"));
    break;
  case SENSOR_TYPE_OBJECT_TEMPERATURE:
    Serial.print(F("Object Temp (C)"));
    break;
  case SENSOR_TYPE_VOLTAGE:
    Serial.print(F("Voltage (V)"));
    break;
  case SENSOR_TYPE_CURRENT:
    Serial.print(F("Current (mA)"));
    break;
  case SENSOR_TYPE_COLOR:
    Serial.print(F("Color (RGBA)"));
    break;
  case SENSOR_TYPE_TVOC:
    Serial.print(F("Total Volatile Organic Compounds (ppb)"));
    break;
  case SENSOR_TYPE_VOC_INDEX:
    Serial.print(F("Volatile Organic Compounds (Index)"));
    break;
  case SENSOR_TYPE_NOX_INDEX:
    Serial.print(F("Nitrogen Oxides (Index)"));
    break;
  case SENSOR_TYPE_CO2:
    Serial.print(F("Carbon Dioxide (ppm)"));
    break;
  case SENSOR_TYPE_ECO2:
    Serial.print(F("Equivalent/estimated CO2 (ppm)"));
    break;
  case SENSOR_TYPE_PM10_STD:
    Serial.print(F("Standard Particulate Matter 1.0 (ppm)"));
    break;
  case SENSOR_TYPE_PM25_STD:
    Serial.print(F("Standard Particulate Matter 2.5 (ppm)"));
    break;
  case SENSOR_TYPE_PM100_STD:
    Serial.print(F("Standard Particulate Matter 10.0 (ppm)"));
    break;
  case SENSOR_TYPE_PM10_ENV:
    Serial.print(F("Environmental Particulate Matter 1.0 (ppm)"));
    break;
  case SENSOR_TYPE_PM25_ENV:
    Serial.print(F("Environmental Particulate Matter 2.5 (ppm)"));
    break;
  case SENSOR_TYPE_PM100_ENV:
    Serial.print(F("Environmental Particulate Matter 10.0 (ppm)"));
    break;
  case SENSOR_TYPE_GAS_RESISTANCE:
    Serial.print(F("Gas Resistance (ohms)"));
    break;
  case SENSOR_TYPE_UNITLESS_PERCENT:
    Serial.print(F("Unitless Percent (%)"));
    break;
  case SENSOR_TYPE_ALTITUDE:
    Serial.print(F("Altitude (m)"));
    break;
  }

  Serial.println();
  Serial.print(F("Driver Ver:   "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:    "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Min Value:    "));
  Serial.println(sensor.min_value);
  Serial.print(F("Max Value:    "));
  Serial.println(sensor.max_value);
  Serial.print(F("Resolution:   "));
  Serial.println(sensor.resolution);
  Serial.println(F("------------------------------------\n"));
}
