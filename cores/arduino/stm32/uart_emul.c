/**
  ******************************************************************************
  * @file    uart_emul.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    25-April-2017
  * @brief   provide the UART Emulation interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "hw_config.h"
#include "uart_emul.h"
#include "digital_io.h"
#include "interrupt.h"
#include "variant.h"

#if defined(TIM1_BASE) && defined(UART_EMUL_RX) && defined(UART_EMUL_TX)
#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

/// @brief number of received characters
#define EMUL_TIMER_PERIOD 100

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

/// @brief defines the global attributes of the UART
typedef struct {
  UART_Emul_TypeDef uartEmul_typedef;
  PinName pin_tx;
  PinName pin_rx;
  void (*uart_rx_irqHandle)(void);
  uint8_t rxpData[UART_RCV_SIZE];
  volatile uint32_t data_available;
  volatile uint8_t begin;
  volatile uint8_t end;
  uart_option_e uart_option;
  stimer_t *_timer;
}uart_emul_conf_t;

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Variables
  * @{
  */
/// @brief uart caracteristics
static UART_Emul_HandleTypeDef g_UartEmulHandle[NB_UART_EMUL_MANAGED];

static uart_emul_conf_t g_uartEmul_config[NB_UART_EMUL_MANAGED] = {
  {
    .uartEmul_typedef = {UART1_EMUL_E},
	.pin_tx = UART_EMUL_TX, .pin_rx = UART_EMUL_RX,
    .uart_rx_irqHandle = NULL,
    .data_available = 0,
    .begin = 0,
    .end = 0,
    .uart_option = EMULATED_UART_E,
    ._timer = NULL
  }
};

//@brief just a simple buffer for the uart reception
uint8_t g_rx_data[1];

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */
static void uart_emul_timer_irq(stimer_t *obj) {UNUSED(obj); g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle();}

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Functions
  * @{
  */

/******************************* EMULATED UART ********************************/
/**
  * @brief  Initializes the UART Emulation MSP.
  * @param  huart: UART Emulation Handle
  * @retval None
  */
void HAL_UART_Emul_MspInit(UART_Emul_HandleTypeDef *huart)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  GPIO_TypeDef *port_rx;
  GPIO_TypeDef *port_tx;
  UNUSED(huart);

  // Enable GPIO clock
  port_rx = set_GPIO_Port_Clock(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_rx));
  port_tx = set_GPIO_Port_Clock(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_tx));

  // Enable GPIO TX/RX clock
  __UART_EMUL_CLK_ENABLE();

  // Enable GPIO TX/RX clock
  GPIO_InitStruct.Pin = STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_tx);
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  // UART TX GPIO pin configuration
  HAL_GPIO_Init(port_tx, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_rx);
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;

  // UART RX GPIO pin configuration
  HAL_GPIO_Init(port_rx, &GPIO_InitStruct);
  stm32_interrupt_enable(port_rx, STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_rx),
                          UART_EMUL_EXTI_RX, GPIO_MODE_IT_FALLING);
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
  GPIO_TypeDef *port_rx = get_GPIO_Port(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_rx));
  GPIO_TypeDef *port_tx = get_GPIO_Port(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_tx));
  UNUSED(huart);

  __UART_EMUL_CLK_DISABLE();

  HAL_GPIO_DeInit(port_tx, STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_tx));
  HAL_GPIO_DeInit(port_rx, STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_rx));

  stm32_interrupt_disable(port_rx, STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_rx));
}

/**
  * @brief  Function called to initialize the emulated uart interface
  * @param  serial_id : one of the defined serial interface
  * @param  baudRate : baudrate to apply to the uart : 4800 or 9600 //TODO bug if baud rate > 9600
  * @retval None
  */
void uart_emul_init(uart_emul_id_e uart_id, uint32_t baudRate)
{
  GPIO_TypeDef *port_tx = get_GPIO_Port(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_tx));
  if(uart_id>=NB_UART_EMUL_MANAGED) {
    return;
  }

  g_UartEmulHandle[uart_id].Init.Mode         = UART_EMUL_MODE_TX_RX;
  g_UartEmulHandle[uart_id].Init.BaudRate     = baudRate;
  g_UartEmulHandle[uart_id].Init.WordLength   = UART_EMUL_WORDLENGTH_8B;
  g_UartEmulHandle[uart_id].Init.StopBits     = UART_EMUL_STOPBITS_1;
  g_UartEmulHandle[uart_id].Init.Parity       = UART_EMUL_PARITY_NONE;
  g_UartEmulHandle[uart_id].Init.RxPinNumber  = STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_rx);
  g_UartEmulHandle[uart_id].Init.TxPinNumber  = STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_tx);
  g_UartEmulHandle[uart_id].RxPortName        = get_GPIO_Port(STM_PORT(g_uartEmul_config[UART1_EMUL_E].pin_rx));
  g_UartEmulHandle[uart_id].TxPortName        = port_tx;

  if(HAL_UART_Emul_Init(&g_UartEmulHandle[uart_id])!= HAL_OK) {
    return;
  }

  if (HAL_UART_Emul_Receive_DMA(&g_UartEmulHandle[uart_id], g_rx_data, 1) != HAL_OK) {
    return;
  }

  uart_emul_flush(uart_id);

  HAL_GPIO_WritePin(port_tx, STM_GPIO_PIN(g_uartEmul_config[UART1_EMUL_E].pin_tx), GPIO_PIN_SET);
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
void uart_emul_attached_handler(stimer_t *obj, void (*irqHandle)(void))
{
  obj->timer = TIMER_UART_EMULATED;
  TimerHandleInit(obj, EMUL_TIMER_PERIOD - 1, (uint16_t)(HAL_RCC_GetHCLKFreq() / 1000) - 1); //50ms
  g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle = irqHandle;
  g_uartEmul_config[UART1_EMUL_E]._timer = obj;
  attachIntHandle(obj, uart_emul_timer_irq);
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
      setTimerCounter((stimer_t *)g_uartEmul_config[UART1_EMUL_E]._timer->timer, 0);
    }
    else if(uart_emul_available(UART1_EMUL_E) < (UART_RCV_SIZE/4*3)) {
      setTimerCounter((stimer_t *)g_uartEmul_config[UART1_EMUL_E]._timer->timer, EMUL_TIMER_PERIOD - 1);
    }
    else {
      g_uartEmul_config[UART1_EMUL_E].uart_rx_irqHandle();
    }
  }
}

/*void HAL_UART_Emul_ErrorCallback(UART_Emul_HandleTypeDef *huart)
{
  printf("UART EMUL RX ERROR\n");
}*/

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
#endif //TIM1_BASE && UART_EMUL_RX && UART_EMUL_TX
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
