/*    
 * A library for Grove - 3-Axis Digital Accelerometer ±2g to 16g Ultra-low Power(LIS3DHTR)
 *   
 * Copyright (c) 2019 seeed technology co., ltd.  
 * Author      : Hongtai Liu (lht856@foxmail.com)  
 * Create Time : July 2019
 * Change Log  : 
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software istm
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS INcommInterface
 * THE SOFTWARE.
 */

#include "LIS3DHTR.h"
template <class T>

LIS3DHTR<T>::LIS3DHTR()
{
    
}

template <class T>
void LIS3DHTR<T>::begin(SPIClass &comm, uint8_t sspin)
{
    chipSelectPin = sspin;
    _spi_com = &comm;
    _wire_com = NULL;
    pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH);

    // Maximum SPI frequency is 10MHz, Data is read and written MSb first,
    // Data is captured on rising edge of clock (CPHA = 0)
    // Base value of the clock is HIGH (CPOL = 1)
    // MODE3 for 328p operation
    SPISettings _settings(10000000, MSBFIRST, SPI_MODE3);

    // start the SPI library:
    _spi_com->begin();

    delay(200);

    uint8_t config5 = LIS3DHTR_REG_TEMP_ADC_PD_ENABLED |
                      LIS3DHTR_REG_TEMP_TEMP_EN_DISABLED;

    writeRegister(LIS3DHTR_REG_TEMP_CFG, config5);
    delay(LIS3DHTR_CONVERSIONDELAY);

    uint8_t config1 = LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_NORMAL | // Normal Mode
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AZEN_ENABLE | // Acceleration Z-Axis Enabled
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AYEN_ENABLE | // Acceleration Y-Axis Enabled
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AXEN_ENABLE;

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1, config1);
    delay(LIS3DHTR_CONVERSIONDELAY);

    uint8_t config4 = LIS3DHTR_REG_ACCEL_CTRL_REG4_BDU_NOTUPDATED | // Continuous Update
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_BLE_LSB |        // Data LSB @ lower address
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_DISABLE |      // High Resolution Disable
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_NORMAL |      // Normal Mode
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_SIM_4WIRE;       // 4-Wire Interface

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4, config4);

    delay(LIS3DHTR_CONVERSIONDELAY);

    setFullScaleRange(LIS3DHTR_RANGE_16G);
    setOutputDataRate(LIS3DHTR_DATARATE_400HZ);
}

template <class T>
void LIS3DHTR<T>::begin(TwoWire &wire, uint8_t address)
{
    _wire_com = &wire;
    _wire_com->begin();
    _spi_com = NULL;
    devAddr = address;

    uint8_t config5 = LIS3DHTR_REG_TEMP_ADC_PD_ENABLED |
                      LIS3DHTR_REG_TEMP_TEMP_EN_DISABLED;

    writeRegister(LIS3DHTR_REG_TEMP_CFG, config5);
    delay(LIS3DHTR_CONVERSIONDELAY);

    uint8_t config1 = LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_NORMAL | // Normal Mode
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AZEN_ENABLE | // Acceleration Z-Axis Enabled
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AYEN_ENABLE | // Acceleration Y-Axis Enabled
                      LIS3DHTR_REG_ACCEL_CTRL_REG1_AXEN_ENABLE;

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1, config1);

    delay(LIS3DHTR_CONVERSIONDELAY);

    uint8_t config4 = LIS3DHTR_REG_ACCEL_CTRL_REG4_BDU_NOTUPDATED | // Continuous Update
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_BLE_LSB |        // Data LSB @ lower address
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_DISABLE |     // High Resolution Disable
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_NORMAL |      // Normal Mode
                      LIS3DHTR_REG_ACCEL_CTRL_REG4_SIM_4WIRE;       // 4-Wire Interface

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4, config4);

    delay(LIS3DHTR_CONVERSIONDELAY);

    setFullScaleRange(LIS3DHTR_RANGE_16G);
    setOutputDataRate(LIS3DHTR_DATARATE_400HZ);
}

template<class T>
bool LIS3DHTR<T>::available()
{
    uint8_t status = 0;
    status = readRegister(LIS3DHTR_REG_ACCEL_STATUS2);
    status &= LIS3DHTR_REG_ACCEL_STATUS2_UPDATE_MASK;
    return status;
}

template <class T>
void LIS3DHTR<T>::openTemp()
{
    uint8_t config5 = LIS3DHTR_REG_TEMP_ADC_PD_ENABLED |
                      LIS3DHTR_REG_TEMP_TEMP_EN_ENABLED;

    writeRegister(LIS3DHTR_REG_TEMP_CFG, config5);
    delay(LIS3DHTR_CONVERSIONDELAY);
}

template <class T>
void LIS3DHTR<T>::closeTemp()
{
    uint8_t config5 = LIS3DHTR_REG_TEMP_ADC_PD_ENABLED |
                      LIS3DHTR_REG_TEMP_TEMP_EN_DISABLED;

    writeRegister(LIS3DHTR_REG_TEMP_CFG, config5);
    delay(LIS3DHTR_CONVERSIONDELAY);
}

template <class T>
int16_t LIS3DHTR<T>::getTemperature(void)
{
    int16_t result = ((int16_t)readRegisterInt16(0x0c)) / 256;
    result += 25;
    return result;
}

template <class T>
bool LIS3DHTR<T>::isConnection(void)
{
    return (getDeviceID() == 0x33);
}

template <class T>
uint8_t LIS3DHTR<T>::getDeviceID(void)
{
    return readRegister(LIS3DHTR_REG_ACCEL_WHO_AM_I);
}

template <class T>
void LIS3DHTR<T>::setPowerMode(power_type_t mode)
{
    uint8_t data = 0;

    data = readRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1);

    data &= ~LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_MASK;
    data |= mode;

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1, data);
    delay(LIS3DHTR_CONVERSIONDELAY);
}

template <class T>
void LIS3DHTR<T>::setFullScaleRange(scale_type_t range)
{
    uint8_t data = 0;

    data = readRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4);

    data &= ~LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_MASK;
    data |= range;

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4, data);
    delay(LIS3DHTR_CONVERSIONDELAY);

    switch (range)
    {
    case LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_16G:
        accRange = 1280;
        break;
    case LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_8G:
        accRange = 3968;
        break;
    case LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_4G:
        accRange = 7282;
        break;
    case LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_2G:
        accRange = 16000;
        break;
    default:
        break;
    }
}

template <class T>
void LIS3DHTR<T>::setOutputDataRate(odr_type_t odr)
{
    uint8_t data = 0;

    data = readRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1);

    data &= ~LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_MASK;
    data |= odr;

    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG1, data);
    delay(LIS3DHTR_CONVERSIONDELAY);
}

template <class T>
void LIS3DHTR<T>::getAcceleration(float *x, float *y, float *z)
{
    // Read the Accelerometer
    uint8_t buf[8]={0};

    // Read the Data
    readRegisterRegion(buf,LIS3DHTR_REG_ACCEL_OUT_X_L,6);

    // Conversion of the result
    // 16-bit signed result for X-Axis Acceleration Data of LIS3DHTR
    *x = (float)((int16_t*)buf)[0] / accRange;
    // 16-bit signed result for Y-Axis Acceleration Data of LIS3DHTR
    *y = (float)((int16_t*)buf)[1] / accRange;
    // 16-bit signed result for Z-Axis Acceleration Data of LIS3DHTR
    *z = (float)((int16_t*)buf)[2] / accRange;
}

template <class T>
float LIS3DHTR<T>::getAccelerationX(void)
{
    // Read the Accelerometer
    uint8_t xAccelLo, xAccelHi;
    int16_t x;

    // Read the Data
    // Reading the Low X-Axis Acceleration Data Register
    xAccelLo = readRegister(LIS3DHTR_REG_ACCEL_OUT_X_L);
    // Reading the High X-Axis Acceleration Data Register
    xAccelHi = readRegister(LIS3DHTR_REG_ACCEL_OUT_X_H);
    // Conversion of the result
    // 16-bit signed result for X-Axis Acceleration Data of LIS3DHTR
    x = (int16_t)((xAccelHi << 8) | xAccelLo);

    return (float)x / accRange;
}

template <class T>
float LIS3DHTR<T>::getAccelerationY(void)
{
    // Read the Accelerometer
    uint8_t yAccelLo, yAccelHi;
    int16_t y;

    // Reading the Low Y-Axis Acceleration Data Register
    yAccelLo = readRegister(LIS3DHTR_REG_ACCEL_OUT_Y_L);
    // Reading the High Y-Axis Acceleration Data Register
    yAccelHi = readRegister(LIS3DHTR_REG_ACCEL_OUT_Y_H);
    // Conversion of the result
    // 16-bit signed result for Y-Axis Acceleration Data of LIS3DHTR
    y = (int16_t)((yAccelHi << 8) | yAccelLo);

    return (float)y / accRange;
}

template <class T>
float LIS3DHTR<T>::getAccelerationZ(void)
{
    // Read the Accelerometer
    uint8_t zAccelLo, zAccelHi;
    int16_t z;

    // Reading the Low Z-Axis Acceleration Data Register
    zAccelLo = readRegister(LIS3DHTR_REG_ACCEL_OUT_Z_L);
    // Reading the High Z-Axis Acceleration Data Register
    zAccelHi = readRegister(LIS3DHTR_REG_ACCEL_OUT_Z_H);
    // Conversion of the result
    // 16-bit signed result for Z-Axis Acceleration Data of LIS3DHTR
    z = (int16_t)((zAccelHi << 8) | zAccelLo);

    return (float)z / accRange;
}

template <class T>
void LIS3DHTR<T>::setHighSolution(bool enable)
{
    uint8_t data = 0;
    data = readRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4);
   
    data = enable? data | LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_ENABLE : data & ~LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_ENABLE;
    
    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG4, data);
    return; 
}

template <class T>
uint16_t LIS3DHTR<T>::readbitADC1(void)
{
    uint8_t adc1_l, adc1_h;
    int16_t intTemp;
    uint16_t uintTemp;
    adc1_l = readRegister(0x08);
    adc1_h = readRegister(0x09);

    intTemp = (int16_t)(adc1_h << 8) | adc1_l;
    intTemp = 0 - intTemp;
    uintTemp = intTemp + 32768;
    return uintTemp >> 6;
}
template <class T>
uint16_t LIS3DHTR<T>::readbitADC2(void)
{
    uint8_t adc2_l, adc2_h;
    int16_t intTemp;
    uint16_t uintTemp;
    adc2_l = readRegister(0x0A);
    adc2_h = readRegister(0x0B);
    intTemp = (int16_t)(adc2_h << 8) | adc2_l;
    intTemp = 0 - intTemp;
    uintTemp = intTemp + 32768;
    return uintTemp >> 6;
}

template <class T>
uint16_t LIS3DHTR<T>::readbitADC3(void)
{
    uint8_t adc3_l, adc3_h;
    int16_t intTemp;
    uint16_t uintTemp;
    adc3_l = readRegister(0x0C);
    adc3_h = readRegister(0x0D);

    intTemp = (int16_t)(adc3_h << 8) | adc3_l;
    intTemp = 0 - intTemp;
    uintTemp = intTemp + 32768;
    return uintTemp >> 6;
}

template <class T>
void LIS3DHTR<T>::writeRegister(uint8_t reg, uint8_t val)
{
    if (_spi_com != NULL)
    {
        _spi_com->beginTransaction(_settings);
        digitalWrite(chipSelectPin, LOW);
        _spi_com->transfer(reg);
        _spi_com->transfer(val);
        digitalWrite(chipSelectPin, HIGH);
        _spi_com->endTransaction();
    }
    else
    {
        _wire_com->beginTransmission(devAddr);
        _wire_com->write(reg);
        _wire_com->write(val);
        _wire_com->endTransmission();
    }
}

template <class T>
void LIS3DHTR<T>::readRegisterRegion(uint8_t *outputPointer, uint8_t reg, uint8_t length)
{

    //define pointer that will point to the external space
    uint8_t i = 0;
    uint8_t c = 0;

    if (_spi_com != NULL)
    {
        _spi_com->beginTransaction(_settings);
        digitalWrite(chipSelectPin, LOW);
        _spi_com->transfer(reg | 0x80 | 0x40); //Ored with "read request" bit and "auto increment" bit
        while (i < length)                     // slave may send less than requested
        {
            c = _spi_com->transfer(0x00); // receive a byte as character
            *outputPointer = c;
            outputPointer++;
            i++;
        }
        digitalWrite(chipSelectPin, HIGH);
        _spi_com->endTransaction();        
    }
    else
    {

        _wire_com->beginTransmission(devAddr);
        reg |= 0x80; //turn auto-increment bit on, bit 7 for I2C
        _wire_com->write(reg);
        _wire_com->endTransmission();
        _wire_com->requestFrom(devAddr, length);

        while ((_wire_com->available()) && (i < length)) // slave may send less than requested
        {
            c = _wire_com->read(); // receive a byte as character
            *outputPointer = c;
            outputPointer++;
            i++;
        }
    }
}

template <class T>
uint16_t LIS3DHTR<T>::readRegisterInt16(uint8_t reg)
{

    uint8_t myBuffer[2];
    readRegisterRegion(myBuffer, reg, 2);
    uint16_t output = myBuffer[0] | uint16_t(myBuffer[1] << 8);

    return output;
}

template <class T>
uint8_t LIS3DHTR<T>::readRegister(uint8_t reg)
{
    uint8_t data;

    readRegisterRegion(&data, reg, 1);

    return data;
}

template <class T>
void LIS3DHTR<T>::click(uint8_t c, uint8_t click_thresh, uint8_t limit, uint8_t latency, uint8_t window)
{
    if (!c)
    {
        uint8_t r = readRegister(LIS3DHTR_REG_ACCEL_CTRL_REG3);
        r &= ~(0x80); // turn off I1_CLICK
        writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG3, r);
        writeRegister(LIS3DHTR_REG_ACCEL_CLICK_CFG, 0);
        return;
    }
    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG3, 0x80);
    writeRegister(LIS3DHTR_REG_ACCEL_CTRL_REG5, 0x08);

    if (c == 1)
    {
        writeRegister(LIS3DHTR_REG_ACCEL_CLICK_CFG, 0x15);
    }
    if (c == 2)
    {
        writeRegister(LIS3DHTR_REG_ACCEL_CLICK_CFG, 0x2A);
    }

    writeRegister(LIS3DHTR_REG_ACCEL_CLICK_THS, click_thresh);
    writeRegister(LIS3DHTR_REG_ACCEL_TIME_LIMIT, limit);
    writeRegister(LIS3DHTR_REG_ACCEL_TIME_LATENCY, latency);
    writeRegister(LIS3DHTR_REG_ACCEL_TIME_WINDOW, window);
}

template <class T>
LIS3DHTR<T>::operator bool() { return isConnection(); }

template class LIS3DHTR<SPIClass>;
template class LIS3DHTR<TwoWire>;
