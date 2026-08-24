#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PA15                    15
#define PB0                     PIN_A8
#define PB1                     PIN_A9
#define PB2                     PIN_A10
#define PB3                     19
#define PB4                     20
#define PB5                     21
#define PB6                     22
#define PB7                     23
#define PB8                     24
#define PB9                     25
#define PB10                    26
#define PB11                    PIN_A11
#define PB12                    PIN_A12
#define PB13                    29
#define PB14                    PIN_A13
#define PB15                    PIN_A14
#define PC0                     PIN_A15
#define PC1                     PIN_A16
#define PC2                     PIN_A17
#define PC3                     PIN_A18
#define PC4                     PIN_A19
#define PC5                     PIN_A20
#define PC6                     38
#define PC7                     39
#define PC8                     40
#define PC9                     41
#define PC10                    42
#define PC11                    43
#define PC12                    44
#define PC13                    45
#define PC14                    46
#define PC15                    47
#define PD0                     48
#define PD1                     49
#define PD2                     50
#define PD3                     51
#define PD4                     52
#define PD5                     53
#define PD6                     54
#define PD7                     55
#define PD8                     56
#define PD9                     57
#define PD10                    58
#define PD11                    59
#define PD12                    60
#define PD13                    61
#define PD14                    62
#define PD15                    63
#define PE0                     64
#define PE1                     65
#define PE2                     66
#define PE3                     67
#define PE4                     68
#define PE5                     69
#define PE6                     70
#define PE7                     71
#define PE8                     72
#define PE9                     73
#define PE10                    74
#define PE11                    75
#define PE12                    76
#define PE13                    77
#define PE14                    78
#define PE15                    79
#define PF0                     PIN_A21
#define PF1                     PIN_A22
#define PF2                     82
#define PF9                     83
#define PF10                    84
#define PG10                    85

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA11_ALT2               (PA11 | ALT2)
#define PA12_ALT1               (PA12 | ALT1)
#define PA12_ALT2               (PA12 | ALT2)
#define PA13_ALT1               (PA13 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB7_ALT2                (PB7  | ALT2)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB9_ALT3                (PB9  | ALT3)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PC13_ALT1               (PC13 | ALT1)

#define NUM_DIGITAL_PINS        86
#define NUM_ANALOG_INPUTS       23



/* Alias */
#define A_PHASE_UL        PE8
#define A_PHASE_UH        PE9
#define A_PHASE_VL        PE10
#define A_PHASE_VH        PE11
#define A_PHASE_WL        PE12
#define A_PHASE_WH        PE13

#define PIN_READY       PE14  //Gate driver ready pin
#define PIN_NFAULT        PE15  //Gate driver fault pin
#define PIN_I2C_GD_SCL      PC8   //I2C3 connected to Gate driver
#define PIN_I2C_GD_SDA      PC9   //I2C3 connected to Gate driver

#define A_VBUS          PC1   //Pin to sense supply voltage. Also input of COMP3
#define BRAKE_RESISTOR      PC2   //Brake resistor. Also output of COMP3
#define BRAKE_AF        3   //Alternate function 3
#define BRAKE_DAC       DAC1  //DAC 1 or 3
#define BRAKE_DAC_CHAN      DAC_CHANNEL_1   //DAC Channel 1
#define BRAKE_COMP        COMP3   //Use comparator 3
#define BRAKE_COMP_PLUS     COMP_INPUT_PLUS_IO2
#define BRAKE_COMP_MINUS    COMP_INPUT_MINUS_DAC1_CH1

#define VBUS_MUL_FACTOR     23    //Multiply the adc voltage read by this value to get the supply voltage

#define A_GPIO_BEMF       PA10  //Pin to pull Back-emf high or low

#define A_CURRW_H       PA1   //phase W and opamp 1
#define A_CURRW_L       PA3
#define A_BEMFW         PA2

#define A_CURRU_H       PA7   //phase U and opamp 2
#define A_CURRU_L       PA5
#define A_BEMFU         PA0

#define A_CURRV_H       PB0   //phase V and opamp 3
#define A_CURRV_L       PB2
#define A_BEMFV         PC4

#define A_POTENTIOMETER     PC0
#define A_TEMPERATURE     PC5

#ifndef NTC_B_CONSTANT
  #define NTC_B_CONSTANT      4250  //B = ln(R/R0)/(1/T-1/T0)
#endif
#ifndef NTC_T0
  #define NTC_T0          (273.15f+25)//Kelvin
#endif
#ifndef NTC_DIVIDER_BALANCE
  #define NTC_DIVIDER_BALANCE   (22.f/100.f) //R1 (value of the other resistance in the voltage divider) over R0 (resistance of NTC at T0)
#endif

#define CAN_RX          PB8
#define CAN_TX          PB9
#define CAN_PWR         PC13 //Take pin high to power on CAN transceiver

#define SWDIO         PA13 //Serial wire debug I/O
#define SWCLK         PA14 //Serial wire debug clock

#define I2C2_SCL        PA9 //I2C clock on the QWIIC connector
#define I2C2_SDA        PA8 //I2C data on the QWIIC connector

#define USART_TX        PB6
#define USART_RX        PB7

#define ENCODER_A       PA6
#define ENCODER_B       PA4
#define ENCODER_Z       PC3

#define HALL1         ENCODER_A
#define HALL2         ENCODER_B
#define HALL3         ENCODER_Z


// On-board LED pin number
#define LED_RED         PA15
#ifndef LED_BUILTIN
  #define LED_BUILTIN       LED_RED
#endif

#define PIN_PWM_MAG_ANGLE
#define PIN_SS_MAG_ANGLE    PD2

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS        PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1       PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2       PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3       PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI      PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO      PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK       PB3
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA      I2C2_SDA
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL      I2C2_SCL
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE      TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO     TIM7
#endif

// UART Definitions
#define SERIAL_UART_INSTANCE  1 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX     USART_RX
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX     USART_TX
#endif

/* HAL configuration */
#define HSE_VALUE       (8000000UL)

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_FDCAN_MODULE_DISABLED)
  #define HAL_FDCAN_MODULE_ENABLED
#endif