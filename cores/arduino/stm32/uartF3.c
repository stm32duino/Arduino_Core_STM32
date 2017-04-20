/**
  ******************************************************************************
  * @file    uart.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    27-July-2016
  * @brief   provide the UART interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f3xx_system
  * @{
  */

/** @addtogroup STM32F3xx_System_Private_Includes
  * @{
  */
#ifdef STM32F3xx
#include "stm32_def.h"
#include "hw_config.h"
#include "uart.h"
#include "uart_emul.h"
#include "timer.h"
#include "digital_io.h"
#include "interrupt.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_Defines
  * @{
  */

/// @brief number of received characters
#define EMUL_TIMER_PERIOD 100

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_TypesDefinitions
  * @{
  */

/// @brief defines the global attributes of the UART
typedef struct {
  USART_TypeDef * usart_typedef;
  IRQn_Type       irqtype;
  GPIO_TypeDef  *tx_port;
  GPIO_InitTypeDef tx_pin;
  GPIO_TypeDef  *rx_port;
  GPIO_InitTypeDef rx_pin;
  void (*uart_clock_init)(void);
  void (*uart_force_reset)(void);
  void (*uart_release_reset)(void);
  void (*gpio_tx_clock_init)(void);
  void (*gpio_rx_clock_init)(void);
  uint8_t rxpData[UART_RCV_SIZE];
  volatile uint32_t data_available;
  volatile uint8_t begin;
  volatile uint8_t end;
  uart_option_e uart_option;
}uart_conf_t;

typedef struct {
  UART_Emul_TypeDef uartEmul_typedef;
  GPIO_TypeDef  *tx_port;
  GPIO_InitTypeDef tx_pin;
  GPIO_TypeDef  *rx_port;
  GPIO_InitTypeDef rx_pin;
  void (*gpio_tx_clock_init)(void);
  void (*gpio_rx_clock_init)(void);
  void (*uart_rx_irqHandle)(void);
  uint8_t rxpData[UART_RCV_SIZE];
  volatile uint32_t data_available;
  volatile uint8_t begin;
  volatile uint8_t end;
  uart_option_e uart_option;
}uart_emul_conf_t;

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_Macros
  * @{
  */
static void usart1_clock_enable(void)   { __USART1_CLK_ENABLE(); }
static void usart1_force_reset(void)    { __USART1_FORCE_RESET(); }
static void usart1_release_reset(void)  { __USART1_RELEASE_RESET(); }
static void usart2_clock_enable(void)   { __USART2_CLK_ENABLE(); }
static void usart2_force_reset(void)    { __USART2_FORCE_RESET(); }
static void usart2_release_reset(void)  { __USART2_RELEASE_RESET(); }
static void gpioa_clock_enable(void)    { __GPIOA_CLK_ENABLE(); }
static void gpiob_clock_enable(void)    { __GPIOB_CLK_ENABLE(); }

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_Variables
  * @{
  */
/// @brief uart caracteristics
static UART_HandleTypeDef g_UartHandle[NB_UART_MANAGED];

static uart_conf_t g_uart_config[NB_UART_MANAGED] = {
  //USART1 (PA9/PA10)
  {
    //UART ID and IRQ
    .usart_typedef = USART1, .irqtype = USART1_IRQn,
    //tx pin configuration
    .tx_port = GPIOA, .tx_pin = {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1},
    //rx pin configuration
    .rx_port = GPIOA, .rx_pin = {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1},
    //uart clock init
    .uart_clock_init = usart1_clock_enable,
    //uart force reset
    .uart_force_reset = usart1_force_reset,
    //uart release reset
    .uart_release_reset = usart1_release_reset,
    //TX gpio clock init
    .gpio_tx_clock_init = gpioa_clock_enable,
    //RX gpio clock init
    .gpio_rx_clock_init = gpioa_clock_enable,
    .data_available = 0,
    .begin = 0,
    .end = 0,
    .uart_option = NATIVE_UART_E
  },
  //USART2 (PA2/PA3)
  {
    .usart_typedef = USART2, .irqtype = USART2_IRQn,
    //tx pin configuration
    .tx_port = GPIOA, .tx_pin = {GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART2},
    //rx pin configuration
    .rx_port = GPIOA, .rx_pin = {GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART2},
    //uart clock init
    .uart_clock_init = usart2_clock_enable,
    //uart force reset
    .uart_force_reset = usart2_force_reset,
    //uart release reset
    .uart_release_reset = usart2_release_reset,
    //TX gpio clock init
    .gpio_tx_clock_init = gpioa_clock_enable,
    //RX gpio clock init
    .gpio_rx_clock_init = gpioa_clock_enable,
    .data_available = 0,
    .begin = 0,
    .end = 0,
    .uart_option = NATIVE_UART_E
  }
};

static UART_Emul_HandleTypeDef g_UartEmulHandle[NB_UART_EMUL_MANAGED];

static uart_emul_conf_t g_uartEmul_config[NB_UART_EMUL_MANAGED] = {
  {
    .uartEmul_typedef = {UART1_EMUL_E},
    .tx_port = GPIOB, .tx_pin = {GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},
    .rx_port = GPIOA, .rx_pin = {GPIO_PIN_10, GPIO_MODE_IT_FALLING, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},
    .gpio_tx_clock_init = gpiob_clock_enable,
    .gpio_rx_clock_init = gpioa_clock_enable,
    .uart_rx_irqHandle = NULL,
    .data_available = 0,
    .begin = 0,
    .end = 0,
    .uart_option = EMULATED_UART_E
  }
};

//@brief just a simple buffer for the uart reception
uint8_t g_rx_data[1];

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_FunctionPrototypes
  * @{
  */
static void uart_emul_timer_irq(timer_id_e timer_id) {g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle();}
uart_id_e get_uart_id_from_handle(UART_HandleTypeDef *huart);

/**
  * @}
  */

/** @addtogroup STM32F3xx_System_Private_Functions
  * @{
  */

/**
  * @brief  This function returns the corresponding uart id function of the
  *         handle
  * @param  huart : one of the defined serial interface
  * @retval the UART id
  */
uart_id_e get_uart_id_from_handle(UART_HandleTypeDef *huart)
{
  uart_id_e uart_id = NB_UART_MANAGED;
  int i;
  for(i = 0; i<NB_UART_MANAGED; i++) {
    if(&g_UartHandle[i] == huart) {
      uart_id = i;
      break;
    }
  }
  return uart_id;
}



/**
  * @brief  UART MSP Initialization - perform IOs and clock init
  * @param  huart : one of the defined serial interface
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  uart_id_e uart_id;

  uart_id = get_uart_id_from_handle(huart);
  if(NB_UART_MANAGED == uart_id) {
    return;
  }

  // Enable GPIO TX/RX clock
  g_uart_config[uart_id].gpio_tx_clock_init();
  g_uart_config[uart_id].gpio_rx_clock_init();

  // Enable USART clock
  g_uart_config[uart_id].uart_clock_init();


  //##-2- Configure peripheral GPIO ##########################################

  // UART TX GPIO pin configuration
  HAL_GPIO_Init(g_uart_config[uart_id].tx_port, &g_uart_config[uart_id].tx_pin);

  // UART RX GPIO pin configuration
  HAL_GPIO_Init(g_uart_config[uart_id].rx_port, &g_uart_config[uart_id].rx_pin);

  HAL_NVIC_SetPriority(g_uart_config[uart_id].irqtype, 0, 1);
  HAL_NVIC_EnableIRQ(g_uart_config[uart_id].irqtype);
}

/**
  * @brief  UART MSP DeInitialization - perform IOs and clock deinit
  * @param  huart : one of the defined serial interface
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  uart_id_e uart_id;

  uart_id = get_uart_id_from_handle(huart);
  if(NB_UART_MANAGED == uart_id) {
    return;
  }

  g_uart_config[uart_id].uart_force_reset();
  g_uart_config[uart_id].uart_release_reset();

  HAL_GPIO_DeInit(g_uart_config[uart_id].tx_port, g_uart_config[uart_id].tx_pin.Pin);
  HAL_GPIO_DeInit(g_uart_config[uart_id].rx_port, g_uart_config[uart_id].rx_pin.Pin);
}

/**
  * @brief  Function called to initialize the uart interface
  * @param  serial_id : one of the defined serial interface
  * @param  baudRate : baudrate to apply to the uart
  * @retval None
  */
void uart_init(uart_id_e uart_id, uint32_t baudRate)
{
  if(uart_id>=NB_UART_MANAGED) {
    return;
  }

  g_UartHandle[uart_id].Instance        = g_uart_config[uart_id].usart_typedef;
  g_UartHandle[uart_id].Init.BaudRate   = baudRate;
  g_UartHandle[uart_id].Init.StopBits   = UART_STOPBITS_1;

  g_UartHandle[uart_id].Init.WordLength = UART_WORDLENGTH_8B;
  g_UartHandle[uart_id].Init.Parity     = UART_PARITY_NONE;
  g_UartHandle[uart_id].Init.Mode       = UART_MODE_TX_RX;
  g_UartHandle[uart_id].Init.HwFlowCtl  = UART_HWCONTROL_NONE;

  // g_UartHandle[uart_id].Init.OverSampling = UART_OVERSAMPLING_16;
  // g_UartHandle[uart_id].Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

  if(HAL_UART_Init(&g_UartHandle[uart_id])!= HAL_OK) {
    return;
  }

#ifdef UART_OPTIMIZED
  UART_MASK_COMPUTATION(&g_UartHandle[uart_id]);

  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(&g_UartHandle[uart_id], UART_IT_RXNE);
#else
  if(HAL_UART_Receive_IT(&g_UartHandle[uart_id], g_rx_data, 1)!= HAL_OK) {
    return;
  }
#endif
}

/**
  * @brief  Function called to deinitialize the uart interface
  * @param  serial_id : one of the defined serial interface
  * @retval None
  */
void uart_deinit(uart_id_e uart_id)
{
  HAL_UART_DeInit(&g_UartHandle[uart_id]);
}

/**
  * @brief  Function returns the amount of data available
  * @param  serial_id : one of the defined serial interface
  * @retval The number of serial data available - int
  */
int uart_available(uart_id_e uart_id)
{
  return g_uart_config[uart_id].data_available;
}

/**
  * @brief  Return the first element of the rx buffer
  * @param  serial_id : one of the defined serial interface
  * @retval The first byte of incoming serial data available (or -1 if no data is available) - int
  */
int8_t uart_read(uart_id_e uart_id)
{
  int8_t data = -1;

  if(g_uart_config[uart_id].data_available > 0) {

    data = g_uart_config[uart_id].rxpData[g_uart_config[uart_id].begin++];

    if(g_uart_config[uart_id].begin >= UART_RCV_SIZE) {
      g_uart_config[uart_id].begin = 0;
    }

    g_uart_config[uart_id].data_available--;
  }

  return data;
}

/**
  * @brief  Return the first element of the rx buffer without removing it from
  *         the buffer
  * @param  serial_id : one of the defined serial interface
  * @retval The first byte of incoming serial data available (or -1 if no data is available) - int
  */
int8_t uart_peek(uart_id_e uart_id)
{
  int8_t data = -1;

  if(g_uart_config[uart_id].data_available > 0) {
    data = g_uart_config[uart_id].rxpData[g_uart_config[uart_id].begin];
  }

  return data;
}

/**
  * @brief  Flush the content of the RX buffer
  * @param  serial_id : one of the defined serial interface
  * @retval None
  */
void uart_flush(uart_id_e uart_id)
{
  g_uart_config[uart_id].data_available = 0;
  g_uart_config[uart_id].end = 0;
  g_uart_config[uart_id].begin = 0;
}

/**
  * @brief  write the data on the uart
  * @param  serial_id : one of the defined serial interface
  * @param  data : byte to write
  * @retval The number of bytes written
  */
size_t uart_write(uart_id_e uart_id, uint8_t data)
{
  HAL_UART_Transmit(&g_UartHandle[uart_id], &data, 1, 5000);
  return 1;
}

/**
  * @brief  error callback from UART
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  uart_id_e uart_id = get_uart_id_from_handle(huart);
  if(NB_UART_MANAGED == uart_id) {
    return;
  }

  uart_deinit(uart_id);
  uart_init(uart_id, g_UartHandle[uart_id].Init.BaudRate);
}

/**
  * @brief  Read receive byte from uart
  * @param  UartHandle pointer on the uart reference
  * @param  byte byte to read
  * @retval None
  */
static void uart_getc(uart_id_e uart_id, uint8_t byte)
{
  if((NB_UART_MANAGED == uart_id) ||
      (g_uart_config[uart_id].data_available >= UART_RCV_SIZE)) {
    return;
  }
  g_uart_config[uart_id].rxpData[g_uart_config[uart_id].end++] = byte;
  if(g_uart_config[uart_id].end >= UART_RCV_SIZE) {
    g_uart_config[uart_id].end = 0;
  }
  g_uart_config[uart_id].data_available++;
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  uart_id_e uart_id = get_uart_id_from_handle(huart);

  HAL_UART_Receive_IT(&g_UartHandle[uart_id], g_rx_data, 1);

  uart_getc(uart_id, g_rx_data[0]);
}

/**
  * @brief UART waking up
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
}

/**
  * @brief  USART 1 IRQ handler
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
#ifdef UART_OPTIMIZED
  /* UART in mode Receiver ---------------------------------------------------*/
  if((__HAL_UART_GET_IT(&g_UartHandle[USART1_E], UART_IT_RXNE) != RESET) &&
     (__HAL_UART_GET_IT_SOURCE(&g_UartHandle[USART1_E], UART_IT_RXNE) != RESET))
  {
    uart_getc(USART1_E, (uint8_t)(g_UartHandle[USART1_E].Instance->RDR &
                                                 (uint8_t)g_UartHandle[USART1_E].Mask));

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&g_UartHandle[USART1_E], UART_IT_RXNE);

    /* Clear RXNE interrupt flag */
    __HAL_UART_SEND_REQ(&g_UartHandle[USART1_E], UART_RXDATA_FLUSH_REQUEST);

  }
#else
  HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
  HAL_UART_IRQHandler(&g_UartHandle[USART1_E]);
#endif
}

/**
  * @brief  USART 2 IRQ handler
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
#ifdef UART_OPTIMIZED
  /* UART in mode Receiver ---------------------------------------------------*/
  if((__HAL_UART_GET_IT(&g_UartHandle[USART2_E], UART_IT_RXNE) != RESET) &&
     (__HAL_UART_GET_IT_SOURCE(&g_UartHandle[USART2_E], UART_IT_RXNE) != RESET))
  {
    uart_getc(USART2_E, (uint8_t)(g_UartHandle[USART2_E].Instance->RDR &
                                                  (uint8_t)g_UartHandle[USART2_E].Mask));

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&g_UartHandle[USART2_E], UART_IT_RXNE);

    /* Clear RXNE interrupt flag */
    __HAL_UART_SEND_REQ(&g_UartHandle[USART2_E], UART_RXDATA_FLUSH_REQUEST);

  }
#else
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
  HAL_UART_IRQHandler(&g_UartHandle[USART2_E]);
#endif
}


/******************************* EMULATED UART ********************************/
/**
  * @brief  Initializes the UART Emulation MSP.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
void HAL_UART_Emul_MspInit(UART_Emul_HandleTypeDef *huart)
{
  // Enable GPIO TX/RX clock
  __UART_EMUL_CLK_ENABLE();

  // Enable GPIO TX/RX clock
  g_uartEmul_config[UART1_EMUL_E].gpio_tx_clock_init();
  g_uartEmul_config[UART1_EMUL_E].gpio_rx_clock_init();

  // UART TX GPIO pin configuration
  HAL_GPIO_Init(g_uartEmul_config[UART1_EMUL_E].tx_port, &g_uartEmul_config[UART1_EMUL_E].tx_pin);

  // UART RX GPIO pin configuration
  HAL_GPIO_Init(g_uartEmul_config[UART1_EMUL_E].rx_port, &g_uartEmul_config[UART1_EMUL_E].rx_pin);

  stm32_interrupt_enable(g_uartEmul_config[UART1_EMUL_E].rx_port, g_uartEmul_config[UART1_EMUL_E].rx_pin.Pin,
                          UART_EMUL_EXTI_RX, g_uartEmul_config[UART1_EMUL_E].rx_pin.Mode);
  /*HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);*/
}

/**
 * @brief  UART Emulation MSP DeInit.
 * @param  huart: UART Emulation handle
 * @retval None
 */
void HAL_UART_Emul_MspDeInit(UART_Emul_HandleTypeDef *huart)
{
  __UART_EMUL_CLK_DISABLE();

  HAL_GPIO_DeInit(g_uartEmul_config[UART1_EMUL_E].tx_port, g_uartEmul_config[UART1_EMUL_E].tx_pin.Pin);
  HAL_GPIO_DeInit(g_uartEmul_config[UART1_EMUL_E].rx_port, g_uartEmul_config[UART1_EMUL_E].rx_pin.Pin);

  stm32_interrupt_disable(g_uartEmul_config[UART1_EMUL_E].rx_port, g_uartEmul_config[UART1_EMUL_E].rx_pin.Pin);
}

/**
  * @brief  Function called to initialize the emulated uart interface
  * @param  serial_id : one of the defined serial interface
  * @param  baudRate : baudrate to apply to the uart : 4800 or 9600 //TODO bug if baud rate > 9600
  * @retval None
  */
void uart_emul_init(uart_emul_id_e uart_id, uint32_t baudRate)
{
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return;
  }

  g_UartEmulHandle[uart_id].Init.Mode         = UART_EMUL_MODE_TX_RX;
  g_UartEmulHandle[uart_id].Init.BaudRate     = baudRate;
  g_UartEmulHandle[uart_id].Init.WordLength   = UART_EMUL_WORDLENGTH_8B;
  g_UartEmulHandle[uart_id].Init.StopBits     = UART_EMUL_STOPBITS_1;
  g_UartEmulHandle[uart_id].Init.Parity       = UART_EMUL_PARITY_NONE;
  g_UartEmulHandle[uart_id].Init.RxPinNumber  = g_uartEmul_config[uart_id].rx_pin.Pin;
  g_UartEmulHandle[uart_id].Init.TxPinNumber  = g_uartEmul_config[uart_id].tx_pin.Pin;
  g_UartEmulHandle[uart_id].RxPortName        = g_uartEmul_config[uart_id].rx_port;
  g_UartEmulHandle[uart_id].TxPortName        = g_uartEmul_config[uart_id].tx_port;

  if(HAL_UART_Emul_Init(&g_UartEmulHandle[uart_id])!= HAL_OK) {
    return;
  }

  if (HAL_UART_Emul_Receive_DMA(&g_UartEmulHandle[uart_id], g_rx_data, 1) != HAL_OK) {
    return;
  }

  uart_emul_flush(uart_id);

  HAL_GPIO_WritePin(g_uartEmul_config[uart_id].tx_port, g_uartEmul_config[uart_id].tx_pin.Pin, GPIO_PIN_SET);
}

/**
  * @brief  Function called to deinitialize the emulated uart interface
  * @param  serial_id : one of the defined serial interface
  * @retval None
  */
void uart_emul_deinit(uart_emul_id_e uart_id)
{
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return;
  }

  HAL_UART_Emul_DeInit(&g_UartEmulHandle[uart_id]);
}

/**
  * @brief  Function returns the amount of data available
  * @param  serial_id : one of the defined serial interface
  * @retval The number of serial data available - int
  */
int uart_emul_available(uart_emul_id_e uart_id)
{
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return 0;
  }

  return g_uartEmul_config[uart_id].data_available;
}

/**
  * @brief  Return the first element of the rx buffer
  * @param  serial_id : one of the defined serial interface
  * @retval The first byte of incoming serial data available (or -1 if no data is available) - int
  */
int8_t uart_emul_read(uart_emul_id_e uart_id)
{
  int8_t data = -1;

  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return data;
  }

  if(g_uartEmul_config[uart_id].data_available > 0) {

    data = g_uartEmul_config[uart_id].rxpData[g_uartEmul_config[uart_id].begin++];

    if(g_uartEmul_config[uart_id].begin >= UART_RCV_SIZE) {
      g_uartEmul_config[uart_id].begin = 0;
    }

    g_uartEmul_config[uart_id].data_available--;
  }

  return data;
}

/**
  * @brief  write the data on the uart
  * @param  serial_id : one of the defined serial interface
  * @param  data : byte to write
  * @retval The number of bytes written
  */
size_t uart_emul_write(uart_emul_id_e uart_id, uint8_t data)
{
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return 0;
  }

  while(HAL_UART_Emul_Transmit_DMA(&g_UartEmulHandle[uart_id], &data, 1) != HAL_OK);
  return 1;
}

/**
  * @brief  Return the first element of the rx buffer without removing it from
  *         the buffer
  * @param  serial_id : one of the defined serial interface
  * @retval The first byte of incoming serial data available (or -1 if no data is available) - int
  */
int8_t uart_emul_peek(uart_emul_id_e uart_id)
{
  int8_t data = -1;

  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return data;
  }

  if(g_uartEmul_config[uart_id].data_available > 0) {
    data = g_uartEmul_config[uart_id].rxpData[g_uartEmul_config[uart_id].begin];
  }

  return data;
}

/**
  * @brief  Flush the content of the RX buffer
  * @param  serial_id : one of the defined serial interface
  * @retval None
  */
void uart_emul_flush(uart_emul_id_e uart_id)
{
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return;
  }

  g_uartEmul_config[uart_id].data_available = 0;
  g_uartEmul_config[uart_id].end = 0;
  g_uartEmul_config[uart_id].begin = 0;
}

/**
  * @brief  Read receive byte from uart
  * @param  UartHandle : pointer on the uart reference
  * @param  byte : byte to read
  * @retval None
  */
static void uart_emul_getc(uart_emul_id_e uart_id, uint8_t byte)
{
  if((uart_id >= NB_UART_EMUL_MANAGED) ||
      (g_uartEmul_config[uart_id].data_available >= UART_RCV_SIZE)) {
    return;
  }

  g_uartEmul_config[uart_id].rxpData[g_uartEmul_config[uart_id].end++] = byte;
  if(g_uartEmul_config[uart_id].end >= UART_RCV_SIZE) {
    g_uartEmul_config[uart_id].end = 0;
  }
  g_uartEmul_config[uart_id].data_available++;
}

/**
  * @brief
  * @param  irq : pointer to function to call
  * @retval None
  */
void uart_emul_attached_handler(void (*irqHandle)(void))
{
  TimerHandleInit(TIM20_E, EMUL_TIMER_PERIOD - 1, (uint16_t)(HAL_RCC_GetHCLKFreq() / 1000) - 1); //50ms
  g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle = irqHandle;
  attachIntHandle(TIM20_E, uart_emul_timer_irq);
}

/**
  * @brief  Initializes the UART Emulation Transfer Complete.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
void HAL_UART_Emul_RxCpltCallback(UART_Emul_HandleTypeDef *huart)
{
  uart_emul_getc(UART1_EMUL_E, *huart->pRxBuffPtr);
  HAL_UART_Emul_Receive_DMA(&g_UartEmulHandle[UART1_EMUL_E], g_rx_data, 1);

  if(g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle != NULL) {
    if(uart_emul_available(UART1_EMUL_E) < (UART_RCV_SIZE / 2)) {
      setTimerCounter(TIM20_E, 0);
    }
    else if(uart_emul_available(UART1_EMUL_E) < (UART_RCV_SIZE/4*3)) {
      setTimerCounter(TIM20_E, EMUL_TIMER_PERIOD - 1);
    }
    else {
      g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle();
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
