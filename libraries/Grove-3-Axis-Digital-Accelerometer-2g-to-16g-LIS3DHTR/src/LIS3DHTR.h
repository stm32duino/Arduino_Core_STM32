/*
    The MIT License (MIT)

    Author: Hongtai Liu (lht856@foxmail.com)

    Copyright (C) 2019  Seeed Technology Co.,Ltd.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Wire.h>
#include <SPI.h>


#ifndef SEEED_LIS3DHTR_H
#define SEEED_LIS3DHTR_H

/**************************************************************************
    I2C ADDRESS/BITS
**************************************************************************/
#define LIS3DHTR_DEFAULT_ADDRESS (0x18) // 3C >> 1 = 7-bit default
#define LIS3DHTR_ADDRESS_UPDATED (0x19) //

/**************************************************************************
    CONVERSION DELAY (in mS)
**************************************************************************/
#define LIS3DHTR_CONVERSIONDELAY (100)

/**************************************************************************
    ACCELEROMETER REGISTERS
**************************************************************************/
#define LIS3DHTR_REG_ACCEL_STATUS (0x07)        // Status Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC1_L (0x28)    // 1-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC1_H (0x29)    // 1-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC2_L (0x2A)    // 2-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC2_H (0x2B)    // 2-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC3_L (0x2C)    // 3-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_ADC3_H (0x2D)    // 3-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_WHO_AM_I (0x0F)      // Device identification Register
#define LIS3DHTR_REG_TEMP_CFG (0x1F)            // Temperature Sensor Register
#define LIS3DHTR_REG_ACCEL_CTRL_REG1 (0x20)     // Accelerometer Control Register 1
#define LIS3DHTR_REG_ACCEL_CTRL_REG2 (0x21)     // Accelerometer Control Register 2
#define LIS3DHTR_REG_ACCEL_CTRL_REG3 (0x22)     // Accelerometer Control Register 3
#define LIS3DHTR_REG_ACCEL_CTRL_REG4 (0x23)     // Accelerometer Control Register 4
#define LIS3DHTR_REG_ACCEL_CTRL_REG5 (0x24)     // Accelerometer Control Register 5
#define LIS3DHTR_REG_ACCEL_CTRL_REG6 (0x25)     // Accelerometer Control Register 6
#define LIS3DHTR_REG_ACCEL_REFERENCE (0x26)     // Reference/Datacapture Register
#define LIS3DHTR_REG_ACCEL_STATUS2 (0x27)       // Status Register 2
#define LIS3DHTR_REG_ACCEL_OUT_X_L (0x28)       // X-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_X_H (0x29)       // X-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_Y_L (0x2A)       // Y-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_Y_H (0x2B)       // Y-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_Z_L (0x2C)       // Z-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_Z_H (0x2D)       // Z-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_FIFO_CTRL (0x2E)     // FIFO Control Register
#define LIS3DHTR_REG_ACCEL_FIFO_SRC (0x2F)      // FIFO Source Register
#define LIS3DHTR_REG_ACCEL_INT1_CFG (0x30)      // Interrupt Configuration Register
#define LIS3DHTR_REG_ACCEL_INT1_SRC (0x31)      // Interrupt Source Register
#define LIS3DHTR_REG_ACCEL_INT1_THS (0x32)      // Interrupt Threshold Register
#define LIS3DHTR_REG_ACCEL_INT1_DURATION (0x33) // Interrupt Duration Register
#define LIS3DHTR_REG_ACCEL_CLICK_CFG (0x38)     // Interrupt Click Recognition Register
#define LIS3DHTR_REG_ACCEL_CLICK_SRC (0x39)     // Interrupt Click Source Register
#define LIS3DHTR_REG_ACCEL_CLICK_THS (0x3A)     // Interrupt Click Threshold Register
#define LIS3DHTR_REG_ACCEL_TIME_LIMIT (0x3B)    // Click Time Limit Register
#define LIS3DHTR_REG_ACCEL_TIME_LATENCY (0x3C)  // Click Time Latency Register
#define LIS3DHTR_REG_ACCEL_TIME_WINDOW (0x3D)   // Click Time Window Register

/**************************************************************************
    TEMPERATURE REGISTER DESCRIPTION
**************************************************************************/
#define LIS3DHTR_REG_TEMP_ADC_PD_MASK (0x80)     // ADC Power Enable Status
#define LIS3DHTR_REG_TEMP_ADC_PD_DISABLED (0x00) // ADC Disabled
#define LIS3DHTR_REG_TEMP_ADC_PD_ENABLED (0x80)  // ADC Enabled

#define LIS3DHTR_REG_TEMP_TEMP_EN_MASK (0x40)     // Temperature Sensor (T) Enable Status
#define LIS3DHTR_REG_TEMP_TEMP_EN_DISABLED (0x00) // Temperature Sensor (T) Disabled
#define LIS3DHTR_REG_TEMP_TEMP_EN_ENABLED (0x40)  // Temperature Sensor (T) Enabled

/**************************************************************************
    ACCELEROMETER CONTROL REGISTER 1 DESCRIPTION
**************************************************************************/
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_MASK (0xF0) // Acceleration Data Rate Selection
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_PD (0x00)   // Power-Down Mode
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_1 (0x10)    // Normal / Low Power Mode (1 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_10 (0x20)   // Normal / Low Power Mode (10 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_25 (0x30)   // Normal / Low Power Mode (25 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_50 (0x40)   // Normal / Low Power Mode (50 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_100 (0x50)  // Normal / Low Power Mode (100 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_200 (0x60)  // Normal / Low Power Mode (200 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_400 (0x70)  // Normal / Low Power Mode (400 Hz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_1_6K (0x80) // Low Power Mode (1.6 KHz)
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_5K (0x90)   // Normal (1.25 KHz) / Low Power Mode (5 KHz)

#define LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_MASK (0x08)   // Low Power Mode Enable
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_NORMAL (0x00) // Normal Mode
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_LOW (0x08)    // Low Power Mode

#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AZEN_MASK (0x04)    // Acceleration Z-Axis Enable
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AZEN_DISABLE (0x00) // Acceleration Z-Axis Disabled
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AZEN_ENABLE (0x04)  // Acceleration Z-Axis Enabled

#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AYEN_MASK (0x02)    // Acceleration Y-Axis Enable
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AYEN_DISABLE (0x00) // Acceleration Y-Axis Disabled
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AYEN_ENABLE (0x02)  // Acceleration Y-Axis Enabled

#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AXEN_MASK (0x01)    // Acceleration X-Axis Enable
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AXEN_DISABLE (0x00) // Acceleration X-Axis Disabled
#define LIS3DHTR_REG_ACCEL_CTRL_REG1_AXEN_ENABLE (0x01)  // Acceleration X-Axis Enabled

/**************************************************************************
    ACCELEROMETER CONTROL REGISTER 4 DESCRIPTION
**************************************************************************/
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BDU_MASK (0x80)       // Block Data Update
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BDU_CONTINUOUS (0x00) // Continuous Update
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BDU_NOTUPDATED (0x80) // Output Registers Not Updated until MSB and LSB Read

#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BLE_MASK (0x40) // Big/Little Endian Data Selection
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BLE_LSB (0x00)  // Data LSB @ lower address
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_BLE_MSB (0x40)  // Data MSB @ lower address

#define LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_MASK (0x30) // Full-Scale Selection
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_2G (0x00)   // +/- 2G
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_4G (0x10)   // +/- 4G
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_8G (0x20)   // +/- 8G
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_16G (0x30)  // +/- 16G

#define LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_MASK (0x08)    // High Resolution Output Mode
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_DISABLE (0x00) // High Resolution Disable
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_HS_ENABLE (0x08)  // High Resolution Enable

#define LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_MASK (0x06)   // Self-Test Enable
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_NORMAL (0x00) // Normal Mode
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_0 (0x02)      // Self-Test 0
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_ST_1 (0x04)      // Self-Test 1

#define LIS3DHTR_REG_ACCEL_CTRL_REG4_SIM_MASK (0x01)  // SPI Serial Interface Mode Selection
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_SIM_4WIRE (0x00) // 4-Wire Interface
#define LIS3DHTR_REG_ACCEL_CTRL_REG4_SIM_3WIRE (0x01) // 3-Wire Interface

#define LIS3DHTR_REG_ACCEL_STATUS2_UPDATE_MASK (0x08)   // Has New Data Flag Mask

enum power_type_t // power mode
{
    POWER_MODE_NORMAL = LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_NORMAL,
    POWER_MODE_LOW = LIS3DHTR_REG_ACCEL_CTRL_REG1_LPEN_LOW
};

enum scale_type_t // measurement rage
{
    LIS3DHTR_RANGE_2G = LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_2G,   //
    LIS3DHTR_RANGE_4G = LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_4G,   //
    LIS3DHTR_RANGE_8G = LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_8G,   //
    LIS3DHTR_RANGE_16G = LIS3DHTR_REG_ACCEL_CTRL_REG4_FS_16G, //
};

enum odr_type_t // output data rate
{
    LIS3DHTR_DATARATE_POWERDOWN = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_PD,
    LIS3DHTR_DATARATE_1HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_1,
    LIS3DHTR_DATARATE_10HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_10,
    LIS3DHTR_DATARATE_25HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_25,
    LIS3DHTR_DATARATE_50HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_50,
    LIS3DHTR_DATARATE_100HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_100,
    LIS3DHTR_DATARATE_200HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_200,
    LIS3DHTR_DATARATE_400HZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_400,
    LIS3DHTR_DATARATE_1_6KH = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_1_6K,
    LIS3DHTR_DATARATE_5KHZ = LIS3DHTR_REG_ACCEL_CTRL_REG1_AODR_5K
};

template <class T>
class LIS3DHTR
{
public:
    LIS3DHTR();

    bool isConnection(void);

    void begin(SPIClass &comm = SPI, uint8_t sspin = SS); //init
    void begin(TwoWire &comm = Wire, uint8_t address = LIS3DHTR_DEFAULT_ADDRESS); //init
    void begin(uint8_t address) { begin(Wire, address); };


    void setPowerMode(power_type_t mode);
    void setFullScaleRange(scale_type_t range);
    void setOutputDataRate(odr_type_t odr);
    void setHighSolution(bool enable);
    bool available();
    void getAcceleration(float *x, float *y, float *z);
    float getAccelerationX(void);
    float getAccelerationY(void);
    float getAccelerationZ(void);
    void click(uint8_t c, uint8_t click_thresh, uint8_t limit = 10, uint8_t latency = 20, uint8_t window = 255);

    void openTemp();
    void closeTemp();

    uint16_t readbitADC1(void);
    uint16_t readbitADC2(void);
    uint16_t readbitADC3(void);

    int16_t getTemperature(void);

    uint8_t getDeviceID(void);

    void reset(void);
    operator bool();

private:
    void read(uint8_t reg, uint8_t *buf, uint16_t len);
    void readRegisterRegion(uint8_t *outputPointer, uint8_t offset, uint8_t length);
    void writeRegister(uint8_t reg, uint8_t val);
    uint8_t readRegister(uint8_t reg);
    uint16_t readRegisterInt16(uint8_t reg);
    uint8_t devAddr;
    int16_t accRange;
    uint8_t commInterface;
    uint8_t chipSelectPin;
    SPIClass *_spi_com;
    SPISettings _settings;
    TwoWire *_wire_com;
};

#endif /*SEEED_LIS3DHTR_H*/
