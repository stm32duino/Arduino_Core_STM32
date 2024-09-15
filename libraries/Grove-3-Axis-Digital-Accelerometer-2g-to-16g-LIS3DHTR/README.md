# Seeed_Arduino_LIS3DHTR  [![Build Status](https://travis-ci.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR.svg?branch=master)](https://travis-ci.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR)
## Introduction 
An Arduino library for 3-Axis Digital Accelerometer ±2g to 16g (LIS3DHTR).Acceleration data can be obtained using IIC interface and SPI interface.
## How to install  Arduino Library
please refer [here](https://wiki.seeedstudio.com/How_to_install_Arduino_Library/).

## Usage

```C++
// This example use I2C.
#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS; //IIC
#define WIRE Wire

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  };
  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);

}
void loop()
{
  if (!LIS)
  {
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }
  //3 axis
   Serial.print("x:"); Serial.print(LIS.getAccelerationX()); Serial.print("  ");
   Serial.print("y:"); Serial.print(LIS.getAccelerationY()); Serial.print("  ");
   Serial.print("z:"); Serial.println(LIS.getAccelerationZ());

}

```

## API Reference

- **begin(*comm\<TwoWire\>, address\<uint8_t\>=0x18*) : void**
```C++
// Init device by IIC
LIS3DHTR<TwoWire> LIS; //IIC
LIS.begin(Wire, 0x19)
```

- **begin(*comm\<SPIClass\>, sspin\<uint8_t\>=SS*) : void** 
```C++
// Init device by SPI
LIS3DHTR<SPIClass> LIS; //SPI
LIS.begin(SPI, 10); //SPI SS/CS
```

- **setPoweMode(*mode\<power_type_t\>*) : void**
```C++
// Set power mode
LIS.setPoweMode(POWER_MODE_NORMAL); // Normal mode
LIS.setPoweMode(POWER_MODE_LOW); // Low power mode
```

- **setFullScaleRange(*range\<scale_type_t\>*) : void**
```C++
// Set Full scale
LIS.setFullScaleRange(LIS3DHTR_RANGE_2G); // 2G
LIS.setFullScaleRange(LIS3DHTR_RANGE_4G); // 4G
LIS.setFullScaleRange(LIS3DHTR_RANGE_8G); // 8G
LIS.setFullScaleRange(LIS3DHTR_RANGE_16G); // 16G
```

- **setOutputDataRate(*odr\<odr_type_t\>*) : void**
```C++
// Set output data rate
LIS.setOutputDataRate(LIS3DHTR_DATARATE_POWERDOWN); // Power down
LIS.setOutputDataRate(LIS3DHTR_DATARATE_1HZ); // 1HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_10HZ); // 10HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); // 25HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ); // 50HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_100HZ); // 100HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_200HZ); // 200HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_400HZ); // 400HZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_1_6KH); // 1.6kHZ
LIS.setOutputDataRate(LIS3DHTR_DATARATE_5KHZ); // 5KHZ
```

- **available(*void*) : bool**
```C++
// if new data
if(LIS.available){
  float x = LIS.getAccelerationX();
}
```

- **getAcceleration(*x\<float \*\>, y\<float \*\>, z\<float \*\>*) : void**
```C++
// get acceleration
float x, y, z;
LIS.getAcceleration(&x, &y, &z);
```

- **getAccelerationX(*void*) : float**
```C++
// get acceleration x
float x = LIS.getAccelerationX();
```

- **getAccelerationY(*void*) : float**
```C++
// get acceleration y
float y = LIS.getAccelerationY();
```

- **getAccelerationY(*void*) : float**
```C++
// get acceleration z
float Z = LIS.getAccelerationZ();
```

- **getTemperature(*void*) : int16_t**
```C++
// get temperature, you need to execute LIS.openTemp() before get temperature
int16_t temp = LIS.getTemperature();
```

- **openTemp(*void*) : void**
```C++
// open temperature enable
LIS.openTemp();
```

- **closeTemp(*void*) : void**
```C++
// close temperature enable
LIS.closeTemp();
```

- **readbitADC1(*void*) : uint16_t**
```C++
// read ADC1
uint16_t adc1 = LIS.readbitADC1();
```

- **readbitADC2(*void*) : uint16_t**
```C++
// read ADC2
uint16_t adc2 = LIS.readbitADC2();
```

- **readbitADC3(*void*) : uint16_t**
```C++
// read ADC3
uint16_t adc3 = LIS.readbitADC3();
```

- **reset(*void*) : void**
```C++
// reset device
LIS.reset();
```


----
## License
This software is written by seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>