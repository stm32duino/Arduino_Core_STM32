STM32F051K6 TIM Resources

TIM1 : Advanced Control Timer, 16 Bit, 4 Channel
TIM2 : General Timer, 32 Bit, 4 Channel
TIM3 : General Timer, 16 Bit, 4 Channel
TIM14 : General Timer, 16 Bit, 1 Channel
TIM15 : General Timer, 16 Bit, 2 Channel
TIM16 : General Timer, 16 Bit, 1 Channel
TIM17 : General Timer, 16 Bit, 1 Channel
TIM6 : Basic Timer, 16 Bit

// --------------------------------------------------------------------------

TIM1 : Motor Control Timer
TIM14 : Motor Commutation Timer
TIM15 : RC Input Measurement
TIM16 : System Millisecond Timer

Input : PA2, TIM15_CH1

LED_RED : PA15
LED_GREEN : PB3
LED_BLUE : PB4

A_FET_HI : PA10
A_FET_LO : PA9
B_FET_HI : PA8
B_FET_LO : PB1
C_FET_HI : PB0
C_FET_LO : PA7

COMP1_INP : PA1
COMP1_INM : PA0
COMP1_INM : PA4
COMP1_INM : PA5

ADC_IN3 : PA3
ADC_IN6 : PA6

USART1_TX : PB6 

// --------------------------------------------------------------------------

// input
#define INPUT_GPIO      GPIOA
#define INPUT_PIN       GPIO_PIN_2

#define INPUT_TIMER     TIM15
#define INPUT_TIMER_CH  TIM_CHANNEL_1

// LEDs
#define LED_RED_GPIO    GPIOA
#define LED_RED_PIN     GPIO_PIN_15
#define LED_GREEN_GPIO  GPIOB
#define LED_GREEN_PIN   GPIO_PIN_3
#define LED_BLUE_GPIO   GPIOB
#define LED_BLUE_PIN    GPIO_PIN_4
#define LED_MASK        LL_AHB1_GRP1_PERIPH_GPIOA | LL_AHB1_GRP1_PERIPH_GPIOB

// H_BRIDGE
#define FD6288
#define A_FET_HI_GPIO   GPIOA
#define A_FET_HI_PIN    GPIO_PIN_10
#define B_FET_HI_GPIO   GPIOA
#define B_FET_HI_PIN    GPIO_PIN_9
#define C_FET_HI_GPIO   GPIOA
#define C_FET_HI_PIN    GPIO_PIN_8
#define A_FET_LO_GPIO   GPIOB
#define A_FET_LO_PIN    GPIO_PIN_1
#define B_FET_LO_GPIO   GPIOB
#define B_FET_LO_PIN    GPIO_PIN_0
#define C_FET_LO_GPIO   GPIOA
#define C_FET_LO_PIN    GPIO_PIN_7

// comparator ,Ok
#define COMPARATOR_OPTIMIZE
#define COMPARATOR              COMP1
#define COMPARATOR_PHASE_A      COMP_INVERTINGINPUT_IO1
#define COMPARATOR_PHASE_A_CSR  0b1100001
#define COMPARATOR_PHASE_B      COMP_INVERTINGINPUT_DAC1
#define COMPARATOR_PHASE_B_CSR  0b1000001
#define COMPARATOR_PHASE_C      COMP_INVERTINGINPUT_DAC2
#define COMPARATOR_PHASE_C_CSR  0b1010001
#define COMPARATOR_COMMON       COMP_NONINVERTINGINPUT_IO1
#define COMPARATOR_MASK         GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5

// adc ,Ok
#define ADC_VOLTAGE             ADC_CHANNEL_3
#define ADC_CURRENT             ADC_CHANNEL_6
#define ADC_TEMPERATURE         ADC_CHANNEL_TEMPSENSOR
#define ADC_MASK                GPIO_PIN_3 | GPIO_PIN_6

// adc calibration ,Ok
#define ADC_VOLTAGE_OFFSET      1.0
#define ADC_VOLTAGE_FACTOR      0.6
#define ADC_CURRENT_OFFSET      0  // 0 -> auto offset
#define ADC_CURRENT_FACTOR      2.13
#define ADC_CONSUMPTION_FACTOR  0.00028
#define ADC_TEMPERATURE_OFFSET  95.05
#define ADC_TEMPERATURE_FACTOR  -0.04

// telemetry
#define USART                   USART1
#define USART_IRQn              USART1_IRQn
#define USART_IRQHandler        USART1_IRQHandler
#define USART_TX_PIN            LL_GPIO_PIN_6
#define USART_TX_GPIO_PORT      GPIOB
#define USART_TX_GPIO_CLK       LL_AHB1_GRP1_PERIPH_GPIOB
#define USART_TX_AF             LL_GPIO_AF_0
#define USART_TDR_ADDRESS       0x40013828
#define USART_TX_DMA_CHANNEL    LL_DMA_CHANNEL_2
