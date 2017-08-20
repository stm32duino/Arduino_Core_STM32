/**
  ******************************************************************************
  * @file    uart.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
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

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "hw_config.h"
#include "uart.h"
#include "digital_io.h"
#include "interrupt.h"
#include "variant.h"
#include "PinAF_STM32F1.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

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
#define UART_NUM (8)
static UART_HandleTypeDef *uart_handlers[UART_NUM] = {NULL};
static void (*rx_callback[UART_NUM])(serial_t*);
static serial_t *rx_callback_obj[UART_NUM];
static int (*tx_callback[UART_NUM])(serial_t*);
static serial_t *tx_callback_obj[UART_NUM];

static uint8_t rx_buffer[1] = {0};
/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Function called to initialize the uart interface
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void uart_init(serial_t *obj)
{
  if(obj == NULL) {
    return;
  }

  UART_HandleTypeDef *huart = &(obj->handle);
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_TypeDef *port;

  // Determine the UART to use (UART_1, UART_2, ...)
  USART_TypeDef *uart_tx = pinmap_peripheral(obj->pin_tx, PinMap_UART_TX);
  USART_TypeDef *uart_rx = pinmap_peripheral(obj->pin_rx, PinMap_UART_RX);

  // Get the peripheral name (UART_1, UART_2, ...) from the pin and assign it to the object
  obj->uart = pinmap_merge_peripheral(uart_tx, uart_rx);

  if(obj->uart == NP) {
    printf("ERROR: UART pins mismatch\n");
    return;
  }

  // Enable USART clock
  if(obj->uart == USART1) {
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
    __HAL_RCC_USART1_CLK_ENABLE();
    obj->index = 0;
    obj->irq = USART1_IRQn;
  } else if(obj->uart == USART2) {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
    __HAL_RCC_USART2_CLK_ENABLE();
    obj->index = 1;
    obj->irq = USART2_IRQn;
  }
#if defined(USART3_BASE)
  else if(obj->uart == USART3) {
    __HAL_RCC_USART3_FORCE_RESET();
    __HAL_RCC_USART3_RELEASE_RESET();
    __HAL_RCC_USART3_CLK_ENABLE();
    obj->index = 2;
    obj->irq = USART3_IRQn;
  }
#endif
#if defined(UART4_BASE)
  else if(obj->uart == UART4) {
    __HAL_RCC_UART4_FORCE_RESET();
    __HAL_RCC_UART4_RELEASE_RESET();
    __HAL_RCC_UART4_CLK_ENABLE();
    obj->index = 3;
    obj->irq = UART4_IRQn;
  }
#endif
#if defined(UART5_BASE)
  else if(obj->uart == UART5) {
    __HAL_RCC_UART5_FORCE_RESET();
    __HAL_RCC_UART5_RELEASE_RESET();
    __HAL_RCC_UART5_CLK_ENABLE();
    obj->index = 4;
    obj->irq = UART5_IRQn;
  }
#endif
#if defined(USART6_BASE)
  else if(obj->uart == USART6) {
    __HAL_RCC_USART6_FORCE_RESET();
    __HAL_RCC_USART6_RELEASE_RESET();
    __HAL_RCC_USART6_CLK_ENABLE();
    obj->index = 5;
    obj->irq = USART6_IRQn;
  }
#endif
#if defined(UART7_BASE)
  else if(obj->uart == UART7) {
    __HAL_RCC_UART7_FORCE_RESET();
    __HAL_RCC_UART7_RELEASE_RESET();
    __HAL_RCC_UART7_CLK_ENABLE();
    obj->index = 6;
    obj->irq = UART7_IRQn;
  }
#endif
#if defined(UART8_BASE)
  else if(obj->uart == UART8) {
    __HAL_RCC_UART8_FORCE_RESET();
    __HAL_RCC_UART8_RELEASE_RESET();
    __HAL_RCC_UART8_CLK_ENABLE();
    obj->index = 7;
    obj->irq = UART8_IRQn;
  }
#endif

  //Configure GPIOs
  //RX
  port = set_GPIO_Port_Clock(STM_PORT(obj->pin_rx));
  GPIO_InitStruct.Pin         = STM_GPIO_PIN(obj->pin_rx);
  GPIO_InitStruct.Mode        = STM_PIN_MODE(pinmap_function(obj->pin_rx,PinMap_UART_RX));
  GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull        = STM_PIN_PUPD(pinmap_function(obj->pin_rx,PinMap_UART_RX));
#ifdef STM32F1xx
  pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_rx,PinMap_UART_RX)));
#else
  GPIO_InitStruct.Alternate   = STM_PIN_AFNUM(pinmap_function(obj->pin_rx,PinMap_UART_RX));
#endif /* STM32F1xx */
  HAL_GPIO_Init(port, &GPIO_InitStruct);

  //TX
  port = set_GPIO_Port_Clock(STM_PORT(obj->pin_tx));
  GPIO_InitStruct.Pin         = STM_GPIO_PIN(obj->pin_tx);
  GPIO_InitStruct.Mode        = STM_PIN_MODE(pinmap_function(obj->pin_tx,PinMap_UART_TX));
  GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull        = STM_PIN_PUPD(pinmap_function(obj->pin_tx,PinMap_UART_TX));
#ifdef STM32F1xx
  pin_SetF1AFPin(STM_PIN_AFNUM(pinmap_function(obj->pin_tx,PinMap_UART_TX)));
#else
  GPIO_InitStruct.Alternate   = STM_PIN_AFNUM(pinmap_function(obj->pin_tx,PinMap_UART_TX));
#endif /* STM32F1xx */
  HAL_GPIO_Init(port, &GPIO_InitStruct);

  //Configure uart
  uart_handlers[obj->index] = huart;
  huart->Instance          = (USART_TypeDef *)(obj->uart);
  huart->Init.BaudRate     = obj->baudrate;
  huart->Init.WordLength   = obj->databits;
  huart->Init.StopBits     = obj->stopbits;
  huart->Init.Parity       = obj->parity;
  huart->Init.Mode         = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  // huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

  if(HAL_UART_Init(huart) != HAL_OK) {
    return;
  }
}

/**
  * @brief  Function called to deinitialize the uart interface
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void uart_deinit(serial_t *obj)
{
  // Reset UART and disable clock
  switch (obj->index) {
    case 0:
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        __HAL_RCC_USART1_CLK_DISABLE();
        break;
    case 1:
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
        break;
#if defined(USART3_BASE)
    case 2:
        __HAL_RCC_USART3_FORCE_RESET();
        __HAL_RCC_USART3_RELEASE_RESET();
        __HAL_RCC_USART3_CLK_DISABLE();
        break;
#endif
#if defined(UART4_BASE)
    case 3:
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();
        __HAL_RCC_UART4_CLK_DISABLE();
        break;
#endif
#if defined(UART5_BASE)
    case 4:
        __HAL_RCC_UART5_FORCE_RESET();
        __HAL_RCC_UART5_RELEASE_RESET();
        __HAL_RCC_UART5_CLK_DISABLE();
        break;
#endif
#if defined(USART6_BASE)
    case 5:
        __HAL_RCC_USART6_FORCE_RESET();
        __HAL_RCC_USART6_RELEASE_RESET();
        __HAL_RCC_USART6_CLK_DISABLE();
        break;
#endif
#if defined(UART7_BASE)
    case 6:
        __HAL_RCC_UART7_FORCE_RESET();
        __HAL_RCC_UART7_RELEASE_RESET();
        __HAL_RCC_UART7_CLK_DISABLE();
        break;
#endif
#if defined(UART8_BASE)
    case 7:
        __HAL_RCC_UART8_FORCE_RESET();
        __HAL_RCC_UART8_RELEASE_RESET();
        __HAL_RCC_UART8_CLK_DISABLE();
        break;
#endif
  }

  HAL_UART_DeInit(uart_handlers[obj->index]);
}

/**
  * @brief  write the data on the uart
  * @param  obj : pointer to serial_t structure
  * @param  data : byte to write
  * @param  size : number of data to write
  * @retval The number of bytes written
  */
size_t uart_write(serial_t *obj, uint8_t data, uint16_t size)
{
  if(HAL_UART_Transmit(uart_handlers[obj->index], &data, size, TX_TIMEOUT) == HAL_OK) {
    return size;
  } else {
    return 0;
  }
}

/**
  * @brief  write the data on the uart: used by printf for debug only (syscalls)
  * @param  obj : pointer to serial_t structure
  * @param  data : bytes to write
  * @param  size : number of data to write
  * @retval The number of bytes written
  */
size_t uart_debug_write(uint8_t *data, uint32_t size)
{
  uint8_t index = 0;
  uint32_t tickstart = HAL_GetTick();

  for(index = 0; index < UART_NUM; index++) {
    if(uart_handlers[index] != NULL) {
      if(DEBUG_UART == uart_handlers[index]->Instance) {
        break;
      }
    }
  }

  if(index >= UART_NUM) {
    return 0;
  }

  while(HAL_UART_Transmit(uart_handlers[index], data, size, TX_TIMEOUT) != HAL_OK) {
    if((HAL_GetTick() - tickstart) >=  TX_TIMEOUT) {
      return 0;
    }
  }

  return size;
}

/**
 * Attempts to determine if the serial peripheral is already in use for RX
 *
 * @param obj The serial object
 * @return Non-zero if the RX transaction is ongoing, 0 otherwise
 */
uint8_t serial_rx_active(serial_t *obj)
{
  return ((obj == NULL) ? 1 : (HAL_UART_GetState(uart_handlers[obj->index]) == HAL_UART_STATE_BUSY_RX));
}

/**
 * Attempts to determine if the serial peripheral is already in use for TX
 *
 * @param obj The serial object
 * @return Non-zero if the TX transaction is ongoing, 0 otherwise
 */
uint8_t serial_tx_active(serial_t *obj)
{
  return ((obj == NULL) ? 1 : (HAL_UART_GetState(uart_handlers[obj->index]) == HAL_UART_STATE_BUSY_TX));
}

/**
  * @brief  Read receive byte from uart
  * @param  obj : pointer to serial_t structure
  * @retval last character received
  */
int uart_getc(serial_t *obj)
{
  if(obj == NULL) {
    return -1;
  }

  if (serial_rx_active(obj)) {
      return -1; // transaction ongoing
  }

  // Restart RX irq
  UART_HandleTypeDef *huart = uart_handlers[obj->index];
  HAL_UART_Receive_IT(huart, rx_buffer, 1);

  return rx_buffer[0];
}

/**
 * Begin asynchronous RX transfer (enable interrupt for data collecting)
 *
 * @param obj : pointer to serial_t structure
 * @param callback : function call at the end of reception
 * @retval none
 */
void uart_attach_rx_callback(serial_t *obj, void (*callback)(serial_t*))
{
  if(obj == NULL) {
    return;
  }

  // Exit if a reception is already on-going
  if (serial_rx_active(obj)) {
    return;
  }

  rx_callback[obj->index] = callback;
  rx_callback_obj[obj->index] = obj;

  HAL_NVIC_SetPriority(obj->irq, 0, 1);
  HAL_NVIC_EnableIRQ(obj->irq);

  if(HAL_UART_Receive_IT(uart_handlers[obj->index], rx_buffer, 1) != HAL_OK) {
    return;
  }
}

/**
 * Begin asynchronous TX transfer.
 *
 * @param obj : pointer to serial_t structure
 * @param callback : function call at the end of transmission
 * @retval none
 */
void uart_attach_tx_callback(serial_t *obj, int (*callback)(serial_t*))
{
  if(obj == NULL) {
    return;
  }

  tx_callback[obj->index] = callback;
  tx_callback_obj[obj->index] = obj;

  // Enable interrupt
  HAL_NVIC_SetPriority(obj->irq, 0, 2);
  HAL_NVIC_EnableIRQ(obj->irq);

  // the following function will enable UART_IT_TXE and error interrupts
  if (HAL_UART_Transmit_IT(uart_handlers[obj->index], &obj->tx_buff[obj->tx_tail], 1) != HAL_OK) {
    return;
  }
}

/**
  * @brief  Return index of the serial handler
  * @param  UartHandle pointer on the uart reference
  * @retval index
  */
uint8_t uart_index(UART_HandleTypeDef *huart)
{
  uint8_t i = 0;
  if(huart == NULL) {
    return UART_NUM;
  }

  for(i = 0; i < UART_NUM; i++) {
    if(huart == uart_handlers[i]) {
      break;
    }
  }

  return i;
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  uint8_t index = uart_index(huart);

  if(index < UART_NUM) {
    rx_callback[index](rx_callback_obj[index]);
  }
}

/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  uint8_t index = uart_index(huart);
  serial_t *obj = tx_callback_obj[index];

  if(index < UART_NUM) {
    if(tx_callback[index](obj) != -1) {
      if (HAL_UART_Transmit_IT(uart_handlers[obj->index], &obj->tx_buff[obj->tx_tail], 1) != HAL_OK) {
        return;
      }
    }
  }
}

/**
  * @brief  error callback from UART
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  volatile uint32_t tmpval;
#if defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32L1xx)
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    tmpval = huart->Instance->DR; // Clear PE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->DR; // Clear FE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->DR; // Clear NE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->DR; // Clear ORE flag
  }
#else
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    tmpval = huart->Instance->RDR; // Clear PE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->RDR; // Clear FE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->RDR; // Clear NE flag
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->RDR; // Clear ORE flag
  }
#endif

  UNUSED(tmpval);
}

/**
  * @brief  USART 1 IRQ handler
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
  HAL_UART_IRQHandler(uart_handlers[0]);
}

/**
  * @brief  USART 2 IRQ handler
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
  HAL_UART_IRQHandler(uart_handlers[1]);
}

/**
  * @brief  USART 3 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART3_BASE)
void USART3_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
  HAL_UART_IRQHandler(uart_handlers[2]);
}
#endif

/**
  * @brief  UART 4 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART4_BASE)
void UART4_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART4_IRQn);
  HAL_UART_IRQHandler(uart_handlers[3]);
}
#endif

/**
  * @brief  USART 3 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART5_BASE)
void UART5_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART5_IRQn);
  HAL_UART_IRQHandler(uart_handlers[4]);
}
#endif

/**
  * @brief  USART 6 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART6_BASE)
void USART6_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART6_IRQn);
  HAL_UART_IRQHandler(uart_handlers[5]);
}
#endif

/**
  * @brief  UART 7 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART7_BASE)
void UART7_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART7_IRQn);
  HAL_UART_IRQHandler(uart_handlers[6]);
}
#endif

/**
  * @brief  UART 8 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART8_BASE)
void UART8_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART8_IRQn);
  HAL_UART_IRQHandler(uart_handlers[7]);
}
#endif

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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
