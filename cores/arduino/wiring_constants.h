/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_CONSTANTS_
#define _WIRING_CONSTANTS_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <stdbool.h>

// Arduino digital pin alias
// GPIO port (A to K) * 16 pins: 176
enum {
  D0,   D1,   D2,   D3,   D4,   D5,   D6,   D7,   D8,   D9,
  D10,  D11,  D12,  D13,  D14,  D15,  D16,  D17,  D18,  D19,
  D20,  D21,  D22,  D23,  D24,  D25,  D26,  D27,  D28,  D29,
  D30,  D31,  D32,  D33,  D34,  D35,  D36,  D37,  D38,  D39,
  D40,  D41,  D42,  D43,  D44,  D45,  D46,  D47,  D48,  D49,
  D50,  D51,  D52,  D53,  D54,  D55,  D56,  D57,  D58,  D59,
  D60,  D61,  D62,  D63,  D64,  D65,  D66,  D67,  D68,  D69,
  D70,  D71,  D72,  D73,  D74,  D75,  D76,  D77,  D78,  D79,
  D80,  D81,  D82,  D83,  D84,  D85,  D86,  D87,  D88,  D89,
  D90,  D91,  D92,  D93,  D94,  D95,  D96,  D97,  D98,  D99,
  D100, D101, D102, D103, D104, D105, D106, D107, D108, D109,
  D110, D111, D112, D113, D114, D115, D116, D117, D118, D119,
  D120, D121, D122, D123, D124, D125, D126, D127, D128, D129,
  D130, D131, D132, D133, D134, D135, D136, D137, D138, D139,
  D140, D141, D142, D143, D144, D145, D146, D147, D148, D149,
  D150, D151, D152, D153, D154, D155, D156, D157, D158, D159,
  D160, D161, D162, D163, D164, D165, D166, D167, D168, D169,
  D170, D171, D172, D173, D174, D175,
  DEND
};

#ifdef STM32F1xx
enum {
    AFIO_NONE,
    AFIO_SPI1_ENABLE,
    AFIO_SPI1_DISABLE,
    AFIO_I2C1_ENABLE,
    AFIO_I2C1_DISABLE,
    AFIO_USART1_ENABLE,
    AFIO_USART1_DISABLE,
    AFIO_USART2_ENABLE,
    AFIO_USART2_DISABLE,
    AFIO_USART3_ENABLE,
    AFIO_USART3_PARTIAL,
    AFIO_USART3_DISABLE,
    AFIO_TIM1_ENABLE,
    AFIO_TIM1_PARTIAL,
    AFIO_TIM1_DISABLE,
    AFIO_TIM2_ENABLE,
    AFIO_TIM2_PARTIAL_2,
    AFIO_TIM2_PARTIAL_1,
    AFIO_TIM2_DISABLE,
    AFIO_TIM3_ENABLE,
    AFIO_TIM3_PARTIAL,
    AFIO_TIM3_DISABLE,
    AFIO_TIM4_ENABLE,
    AFIO_TIM4_DISABLE,
//#if defined(AFIO_MAPR_CAN_REMAP1)
    AFIO_CAN1_1,
    AFIO_CAN1_2,
    AFIO_CAN1_3,
//#endif
    AFIO_PD01_ENABLE,
    AFIO_PD01_DISABLE,
//#if defined(AFIO_MAPR_TIM5CH4_IREMAP)
    AFIO_TIM5CH4_ENABLE,
    AFIO_TIM5CH4_DISABLE,
//#endif
//#if defined(AFIO_MAPR_ETH_REMAP)
    AFIO_ETH_ENABLE,
    AFIO_ETH_DISABLE,
//#endif
//#if defined(AFIO_MAPR_CAN2_REMAP)
    AFIO_CAN2_ENABLE,
    AFIO_CAN2_DISABLE,
//#endif
//#if defined(AFIO_MAPR_MII_RMII_SEL)
    AFIO_ETH_RMII,
    AFIO_ETH_MII,
//#endif
    AFIO_ADC1_ETRGINJ_ENABLE,
    AFIO_ADC1_ETRGINJ_DISABLE,
    AFIO_ADC1_ETRGREG_ENABLE,
    AFIO_ADC1_ETRGREG_DISABLE,
//#if defined(AFIO_MAPR_ADC2_ETRGINJ_REMAP)
    AFIO_ADC2_ETRGINJ_ENABLE,
    AFIO_ADC2_ETRGINJ_DISABLE,
//#endif
//#if defined(AFIO_MAPR_ADC2_ETRGREG_REMAP)
    AFIO_ADC2_ETRGREG_ENABLE,
    AFIO_ADC2_ETRGREG_DISABLE,
//#endif
    AFIO_SWJ_ENABLE,
    AFIO_SWJ_NONJTRST,
    AFIO_SWJ_NOJTAG,
    AFIO_SWJ_DISABLE,
//#if defined(AFIO_MAPR_SPI3_REMAP)
    AFIO_SPI3_ENABLE,
    AFIO_SPI3_DISABLE,
//#endif
//#if defined(AFIO_MAPR_TIM2ITR1_IREMAP)
    AFIO_TIM2ITR1_TO_USB,
    AFIO_TIM2ITR1_TO_ETH,
//#endif
//#if defined(AFIO_MAPR_PTP_PPS_REMAP)
    AFIO_ETH_PTP_PPS_ENABLE,
    AFIO_ETH_PTP_PPS_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM9_REMAP)
    AFIO_TIM9_ENABLE,
    AFIO_TIM9_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM10_REMAP)
    AFIO_TIM10_ENABLE,
    AFIO_TIM10_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM11_REMAP)
    AFIO_TIM11_ENABLE,
    AFIO_TIM11_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM13_REMAP)
    AFIO_TIM13_ENABLE,
    AFIO_TIM13_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM14_REMAP)
    AFIO_TIM14_ENABLE,
    AFIO_TIM14_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_FSMC_NADV_REMAP)
    AFIO_FSMCNADV_DISCONNECTED,
    AFIO_FSMCNADV_CONNECTED,
//#endif
//#if defined(AFIO_MAPR2_TIM15_REMAP)
    AFIO_TIM15_ENABLE,
    AFIO_TIM15_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM16_REMAP)
    AFIO_TIM16_ENABLE,
    AFIO_TIM16_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM17_REMAP)
    AFIO_TIM17_ENABLE,
    AFIO_TIM17_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_CEC_REMAP)
    AFIO_CEC_ENABLE,
    AFIO_CEC_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM1_DMA_REMAP)
    AFIO_TIM1DMA_ENABLE,
    AFIO_TIM1DMA_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM67_DAC_DMA_REMAP)
    AFIO_TIM67DACDMA_ENABLE,
    AFIO_TIM67DACDMA_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_TIM12_REMAP)
    AFIO_TIM12_ENABLE,
    AFIO_TIM12_DISABLE,
//#endif
//#if defined(AFIO_MAPR2_MISC_REMAP)
    AFIO_MISC_ENABLE,
    AFIO_MISC_DISABLE,
//#endif
};
#endif // STM32F1xx

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

//      LOW 0
//      HIGH 1
#define CHANGE 2
#define FALLING 3
#define RISING 4

#define DEFAULT 1
#define EXTERNAL 0

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif // min

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif // max

#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int word;

#define bit(b) (1UL << (b))


typedef bool boolean ;

typedef uint8_t byte ;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _WIRING_CONSTANTS_ */
