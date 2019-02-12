/**
  ******************************************************************************
  * @file    uart.c
  * @author  WI6LABS, fpistm
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
#include "core_debug.h"
#include "uart.h"
#include "Arduino.h"
#include "PinAF_STM32F1.h"

#ifdef __cplusplus
 extern "C" {
#endif
#if defined(HAL_UART_MODULE_ENABLED)

/* If DEBUG_UART is not defined assume this is the one linked to PIN_SERIAL_TX */
#if !defined(DEBUG_UART)
#if defined(PIN_SERIAL_TX)
#define DEBUG_UART          pinmap_peripheral(digitalPinToPinName(PIN_SERIAL_TX), PinMap_UART_TX)
#define DEBUG_PINNAME_TX    digitalPinToPinName(PIN_SERIAL_TX)
#else
/* No debug UART defined */
#define DEBUG_UART          NP
#define DEBUG_PINNAME_TX    NC
#endif
#endif
#if !defined(DEBUG_UART_BAUDRATE)
#define DEBUG_UART_BAUDRATE 9600
#endif

/* @brief uart caracteristics */
#if defined(STM32F4xx)
#define UART_NUM (10)
#elif defined(STM32F0xx) || defined(STM32F7xx) || defined(STM32H7xx)
#define UART_NUM (8)
#elif defined(STM32F2xx) || defined(STM32L4xx)
#define UART_NUM (6)
#elif defined(STM32F1xx) || defined(STM32F3xx) ||\
	  defined(STM32L0xx) || defined(STM32L1xx)
#define UART_NUM (5)
#else
#error "Unknown Family - unknown UART_NUM"
#endif

static UART_HandleTypeDef *uart_handlers[UART_NUM] = {NULL};
static void (*rx_callback[UART_NUM])(serial_t*);
static serial_t *rx_callback_obj[UART_NUM];
static int (*tx_callback[UART_NUM])(serial_t*);
static serial_t *tx_callback_obj[UART_NUM];

static serial_t serial_debug = { .uart=NP, .index=UART_NUM };

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

  /* Determine the U(S)ART peripheral to use (USART1, USART2, ...) */
  USART_TypeDef *uart_tx = pinmap_peripheral(obj->pin_tx, PinMap_UART_TX);
  USART_TypeDef *uart_rx = pinmap_peripheral(obj->pin_rx, PinMap_UART_RX);

  /* Pins Rx/Tx must not be NP */
  if(uart_rx == NP || uart_tx == NP) {
    core_debug("ERROR: at least one UART pin has no peripheral\n");
    return;
  }

  /*
   * Get the peripheral name (USART1, USART2, ...) from the pin
   * and assign it to the object
   */
  obj->uart = pinmap_merge_peripheral(uart_tx, uart_rx);

  if(obj->uart == NP) {
    core_debug("ERROR: U(S)ART pins mismatch\n");
    return;
  }

  /* Enable USART clock */
#if defined(USART1_BASE)
  else if(obj->uart == USART1) {
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
    __HAL_RCC_USART1_CLK_ENABLE();
    obj->index = 0;
    obj->irq = USART1_IRQn;
  }
#endif
#if defined(USART2_BASE)
  else if(obj->uart == USART2) {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
    __HAL_RCC_USART2_CLK_ENABLE();
    obj->index = 1;
    obj->irq = USART2_IRQn;
  }
#endif
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
#elif defined(USART4_BASE)
  else if(obj->uart == USART4) {
    __HAL_RCC_USART4_FORCE_RESET();
    __HAL_RCC_USART4_RELEASE_RESET();
    __HAL_RCC_USART4_CLK_ENABLE();
    obj->index = 3;
    obj->irq = USART4_IRQn;
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
#elif defined(USART5_BASE)
  else if(obj->uart == USART5) {
    __HAL_RCC_USART5_FORCE_RESET();
    __HAL_RCC_USART5_RELEASE_RESET();
    __HAL_RCC_USART5_CLK_ENABLE();
    obj->index = 4;
    obj->irq = USART5_IRQn;
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
#if defined(LPUART1_BASE)
  else if(obj->uart == LPUART1) {
    __HAL_RCC_LPUART1_FORCE_RESET();
    __HAL_RCC_LPUART1_RELEASE_RESET();
    __HAL_RCC_LPUART1_CLK_ENABLE();
#if !defined(USART3_BASE)
	obj->index = 2;
#else
	obj->index = 5;
#endif
    obj->irq = LPUART1_IRQn;
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
#elif defined(USART7_BASE)
  else if(obj->uart == USART7) {
    __HAL_RCC_USART7_FORCE_RESET();
    __HAL_RCC_USART7_RELEASE_RESET();
    __HAL_RCC_USART7_CLK_ENABLE();
    obj->index = 6;
    obj->irq = USART7_IRQn;
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
#elif defined(USART8_BASE)
  else if(obj->uart == USART8) {
    __HAL_RCC_USART8_FORCE_RESET();
    __HAL_RCC_USART8_RELEASE_RESET();
    __HAL_RCC_USART8_CLK_ENABLE();
    obj->index = 7;
    obj->irq = USART8_IRQn;
  }
#endif
#if defined(UART9_BASE)
  else if(obj->uart == UART9) {
    __HAL_RCC_UART9_FORCE_RESET();
    __HAL_RCC_UART9_RELEASE_RESET();
    __HAL_RCC_UART9_CLK_ENABLE();
    obj->index = 8;
    obj->irq = UART9_IRQn;
  }
#endif
#if defined(UART10_BASE)
  else if(obj->uart == UART10) {
    __HAL_RCC_UART10_FORCE_RESET();
    __HAL_RCC_UART10_RELEASE_RESET();
    __HAL_RCC_UART10_CLK_ENABLE();
    obj->index = 9;
    obj->irq = UART10_IRQn;
  }
#endif

#if defined(STM32F091xC) || defined (STM32F098xx)
  /* Enable SYSCFG Clock */
  /* Required to get SYSCFG interrupt status register */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
#endif

  /* Configure UART GPIO pins */
  pinmap_pinout(obj->pin_tx, PinMap_UART_TX);
  pinmap_pinout(obj->pin_rx, PinMap_UART_RX);

  /* Configure uart */
  uart_handlers[obj->index] = huart;
  huart->Instance          = (USART_TypeDef *)(obj->uart);
  huart->Init.BaudRate     = obj->baudrate;
  huart->Init.WordLength   = obj->databits;
  huart->Init.StopBits     = obj->stopbits;
  huart->Init.Parity       = obj->parity;
  huart->Init.Mode         = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx)\
 && !defined(STM32L1xx)
  huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif
#ifdef UART_ONE_BIT_SAMPLE_DISABLE
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
#endif

#if defined(LPUART1_BASE)
  /*
   * Note that LPUART clock source must be in the range
   * [3 x baud rate, 4096 x baud rate]
   * check Reference Manual
   */
  if(obj->uart == LPUART1) {
    if (obj->baudrate <= 9600) {
#if defined(USART_CR3_UCESM)
      HAL_UARTEx_EnableClockStopMode(huart);
#endif
      HAL_UARTEx_EnableStopMode(huart);
    } else {
#if defined(USART_CR3_UCESM)
      HAL_UARTEx_DisableClockStopMode(huart);
#endif
      HAL_UARTEx_DisableStopMode(huart);
    }
    /* Trying default LPUART clock source */
    if (HAL_UART_Init(huart) == HAL_OK) {
      return;
    }
    /* Trying to change LPUART clock source */
    /* If baudrate is lower than or equal to 9600 try to change to LSE */
    if(obj->baudrate <= 9600) {
      /* Enable the clock if not already set by user */
      enableClock(LSE_CLOCK);

      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_LSE);
      if (HAL_UART_Init(huart) == HAL_OK) {
        return;
      }
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY)) {
      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_HSI);
      if (HAL_UART_Init(huart) == HAL_OK) {
        return;
      }
    }
#ifndef STM32H7xx
    __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_PCLK1);
    if (HAL_UART_Init(huart) == HAL_OK) {
      return;
    }
    __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_SYSCLK);
#else
    __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_CSI);
#endif
  }
#endif

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
  /* Reset UART and disable clock */
  switch (obj->index) {
#if defined(USART1_BASE)
    case 0:
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        __HAL_RCC_USART1_CLK_DISABLE();
        break;
#endif
#if defined(USART2_BASE)
    case 1:
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
        break;
#endif
#if defined(USART3_BASE)
    case 2:
        __HAL_RCC_USART3_FORCE_RESET();
        __HAL_RCC_USART3_RELEASE_RESET();
        __HAL_RCC_USART3_CLK_DISABLE();
        break;
#elif defined(LPUART1_BASE)
    case 2:
        __HAL_RCC_LPUART1_FORCE_RESET();
        __HAL_RCC_LPUART1_RELEASE_RESET();
        __HAL_RCC_LPUART1_CLK_DISABLE();
        break;
#endif
#if defined(UART4_BASE)
    case 3:
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();
        __HAL_RCC_UART4_CLK_DISABLE();
        break;
#elif defined(USART4_BASE)
    case 3:
        __HAL_RCC_USART4_FORCE_RESET();
        __HAL_RCC_USART4_RELEASE_RESET();
        __HAL_RCC_USART4_CLK_DISABLE();
        break;
#endif
#if defined(UART5_BASE)
    case 4:
        __HAL_RCC_UART5_FORCE_RESET();
        __HAL_RCC_UART5_RELEASE_RESET();
        __HAL_RCC_UART5_CLK_DISABLE();
        break;
#elif defined(USART5_BASE)
    case 4:
        __HAL_RCC_USART5_FORCE_RESET();
        __HAL_RCC_USART5_RELEASE_RESET();
        __HAL_RCC_USART5_CLK_DISABLE();
        break;
#endif
#if defined(USART6_BASE)
    case 5:
        __HAL_RCC_USART6_FORCE_RESET();
        __HAL_RCC_USART6_RELEASE_RESET();
        __HAL_RCC_USART6_CLK_DISABLE();
        break;
#elif defined(LPUART1_BASE)
    case 5:
        __HAL_RCC_LPUART1_FORCE_RESET();
        __HAL_RCC_LPUART1_RELEASE_RESET();
        __HAL_RCC_LPUART1_CLK_DISABLE();
        break;
#endif
#if defined(UART7_BASE)
    case 6:
        __HAL_RCC_UART7_FORCE_RESET();
        __HAL_RCC_UART7_RELEASE_RESET();
        __HAL_RCC_UART7_CLK_DISABLE();
        break;
#elif defined(USART7_BASE)
    case 6:
        __HAL_RCC_USART7_FORCE_RESET();
        __HAL_RCC_USART7_RELEASE_RESET();
        __HAL_RCC_USART7_CLK_DISABLE();
        break;
#endif
#if defined(UART8_BASE)
    case 7:
        __HAL_RCC_UART8_FORCE_RESET();
        __HAL_RCC_UART8_RELEASE_RESET();
        __HAL_RCC_UART8_CLK_DISABLE();
        break;
#elif defined(USART8_BASE)
    case 7:
        __HAL_RCC_USART8_FORCE_RESET();
        __HAL_RCC_USART8_RELEASE_RESET();
        __HAL_RCC_USART8_CLK_DISABLE();
        break;
#endif
#if defined(UART9_BASE)
    case 8:
        __HAL_RCC_UART9_FORCE_RESET();
        __HAL_RCC_UART9_RELEASE_RESET();
        __HAL_RCC_UART9_CLK_DISABLE();
        break;
#endif
#if defined(UART10_BASE)
    case 9:
        __HAL_RCC_UART10_FORCE_RESET();
        __HAL_RCC_UART10_RELEASE_RESET();
        __HAL_RCC_UART10_CLK_DISABLE();
        break;
#endif
}

  HAL_UART_DeInit(uart_handlers[obj->index]);
}

#if defined(HAL_PWR_MODULE_ENABLED) && defined(UART_IT_WUF)
/**
  * @brief  Function called to configure the uart interface for low power
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void uart_config_lowpower(serial_t *obj)
{
  if(obj == NULL) {
    return;
  }
  /* Ensure HSI clock is enable */
  enableClock(HSI_CLOCK);

  /* Configure HSI as source clock for low power wakeup clock */
  switch (obj->index) {
#if defined(USART1_BASE)
    case 0:
      if (__HAL_RCC_GET_USART1_SOURCE() != RCC_USART1CLKSOURCE_HSI) {
        __HAL_RCC_USART1_CONFIG(RCC_USART1CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(USART2_BASE) && defined(__HAL_RCC_USART2_CONFIG)
    case 1:
      if (__HAL_RCC_GET_USART2_SOURCE() != RCC_USART2CLKSOURCE_HSI) {
        __HAL_RCC_USART2_CONFIG(RCC_USART2CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(USART3_BASE) && defined(__HAL_RCC_USART3_CONFIG)
    case 2:
      if (__HAL_RCC_GET_USART3_SOURCE() != RCC_USART3CLKSOURCE_HSI) {
        __HAL_RCC_USART3_CONFIG(RCC_USART3CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(UART4_BASE) && defined(__HAL_RCC_UART4_CONFIG)
    case 3:
      if (__HAL_RCC_GET_UART4_SOURCE() != RCC_UART4CLKSOURCE_HSI) {
        __HAL_RCC_UART4_CONFIG(RCC_UART4CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(UART5_BASE) && defined(__HAL_RCC_UART5_CONFIG)
    case 4:
      if (__HAL_RCC_GET_UART5_SOURCE() != RCC_UART5CLKSOURCE_HSI) {
        __HAL_RCC_UART5_CONFIG(RCC_UART5CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(LPUART1_BASE) && defined(__HAL_RCC_LPUART1_CONFIG)
#if !defined(USART3_BASE)
    case 2:
#else
    case 5:
#endif
      if (__HAL_RCC_GET_LPUART1_SOURCE() != RCC_LPUART1CLKSOURCE_HSI) {
        __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_HSI);
      }
      break;
#endif
  }
}
#endif

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
  * @brief  Function called to initialize the debug uart interface
  * @note   Call only if debug U(S)ART peripheral is not already initialized
  *         by a Serial instance
  *         Default config: 8N1
  * @retval None
  */
void uart_debug_init(void)
{
  if ( DEBUG_UART != NP) {
    serial_debug.pin_rx = pinmap_pin(DEBUG_UART, PinMap_UART_RX);
#if defined(DEBUG_PINNAME_TX)
    serial_debug.pin_tx = DEBUG_PINNAME_TX;
#else
    serial_debug.pin_tx = pinmap_pin(DEBUG_UART, PinMap_UART_TX);
#endif
    serial_debug.baudrate = DEBUG_UART_BAUDRATE;
    serial_debug.parity = UART_PARITY_NONE;
    serial_debug.databits = UART_WORDLENGTH_8B;
    serial_debug.stopbits = UART_STOPBITS_1;

    uart_init(&serial_debug);
  }
}

/**
  * @brief  write the data on the uart: used by printf for debug only (syscalls)
  * @param  data : bytes to write
  * @param  size : number of data to write
  * @retval The number of bytes written
  */
size_t uart_debug_write(uint8_t *data, uint32_t size)
{
  uint8_t index = 0;
  uint32_t tickstart = HAL_GetTick();

  if (DEBUG_UART == NP) {
    return 0;
  }
  /* Search if DEBUG_UART already initialized */
  for(index = 0; index < UART_NUM; index++) {
    if(uart_handlers[index] != NULL) {
      if(DEBUG_UART == uart_handlers[index]->Instance) {
        break;
      }
    }
  }

  if(index >= UART_NUM) {
    /* DEBUG_UART not initialized */
    if( serial_debug.index >= UART_NUM ) {
      uart_debug_init();
      if( serial_debug.index >= UART_NUM ) {
        return 0;
      }
    }
    index = serial_debug.index;
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
  return ((HAL_UART_GetState(uart_handlers[obj->index]) & HAL_UART_STATE_BUSY_RX) == HAL_UART_STATE_BUSY_RX);
}

/**
 * Attempts to determine if the serial peripheral is already in use for TX
 *
 * @param obj The serial object
 * @return Non-zero if the TX transaction is ongoing, 0 otherwise
 */
uint8_t serial_tx_active(serial_t *obj)
{
  return ((HAL_UART_GetState(uart_handlers[obj->index]) & HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX);
}

/**
  * @brief  Read receive byte from uart
  * @param  obj : pointer to serial_t structure
  * @retval last character received
  */
int uart_getc(serial_t *obj, unsigned char* c)
{
  if(obj == NULL) {
    return -1;
  }

  if (serial_rx_active(obj)) {
      return -1; /* Transaction ongoing */
  }

  *c = (unsigned char)(obj->recv);
  /* Restart RX irq */
  UART_HandleTypeDef *huart = uart_handlers[obj->index];
  HAL_UART_Receive_IT(huart, &(obj->recv), 1);

  return 0;
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

  /* Exit if a reception is already on-going */
  if (serial_rx_active(obj)) {
    return;
  }

  rx_callback[obj->index] = callback;
  rx_callback_obj[obj->index] = obj;

  HAL_NVIC_SetPriority(obj->irq, 0, 1);
  HAL_NVIC_EnableIRQ(obj->irq);

  if(HAL_UART_Receive_IT(uart_handlers[obj->index], &(obj->recv), 1) != HAL_OK) {
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

  /* Enable interrupt */
  HAL_NVIC_SetPriority(obj->irq, 0, 2);
  HAL_NVIC_EnableIRQ(obj->irq);

  /* The following function will enable UART_IT_TXE and error interrupts */
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
    tmpval = huart->Instance->DR; /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear ORE flag */
  }
#else
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear ORE flag */
  }
#endif

  UNUSED(tmpval);
}

/**
  * @brief  USART 1 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART1_BASE)
void USART1_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
  HAL_UART_IRQHandler(uart_handlers[0]);
}
#endif

/**
  * @brief  USART 2 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART2_BASE)
void USART2_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
  HAL_UART_IRQHandler(uart_handlers[1]);
}
#endif

/**
  * @brief  USART 3 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART3_BASE)
void USART3_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
#if defined(STM32F091xC) || defined (STM32F098xx)
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART3)!= RESET)
  {
    HAL_UART_IRQHandler(uart_handlers[2]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART4)!= RESET)
  {
     HAL_UART_IRQHandler(uart_handlers[3]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART5)!= RESET)
  {
     HAL_UART_IRQHandler(uart_handlers[4]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART6)!= RESET)
  {
     HAL_UART_IRQHandler(uart_handlers[5]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART7)!= RESET)
  {
     HAL_UART_IRQHandler(uart_handlers[6]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART8)!= RESET)
  {
     HAL_UART_IRQHandler(uart_handlers[7]);
  }
#else
  if(uart_handlers[2] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[2]);
  }
#if defined(STM32F0xx)
/* USART3_4_IRQn */
  if(uart_handlers[3] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[3]);
  }
#if defined(STM32F030xC)
  if(uart_handlers[4] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[4]);
  }
  if(uart_handlers[5] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[5]);
  }
#endif /* STM32F030xC */
#endif /* STM32F0xx */
#endif /* STM32F091xC || STM32F098xx */
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
  * @brief  USART 4/5 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(STM32L0xx)
#if defined(USART4_BASE) || defined(USART5_BASE)
void USART4_5_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART4_IRQn);
  if(uart_handlers[3] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[3]);
  }
  if(uart_handlers[4] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[4]);
  }
}
#endif
#endif

/**
  * @brief  USART 5 IRQ handler
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
#if defined(USART6_BASE) && !defined(STM32F0xx)
void USART6_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART6_IRQn);
  HAL_UART_IRQHandler(uart_handlers[5]);
}
#endif

/**
  * @brief  LPUART 1 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(LPUART1_BASE)
void LPUART1_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(LPUART1_IRQn);
#if !defined(USART3_BASE)
  HAL_UART_IRQHandler(uart_handlers[2]);
#else
  HAL_UART_IRQHandler(uart_handlers[5]);
#endif
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
  * @brief  UART 9 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART9_BASE)
void UART9_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART9_IRQn);
  HAL_UART_IRQHandler(uart_handlers[8]);
}
#endif

/**
  * @brief  UART 10 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(UART10_BASE)
void UART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART10_IRQn);
  HAL_UART_IRQHandler(uart_handlers[9]);
}
#endif

/**
  * @brief  HAL UART Call Back
  * @param  UART handler
  * @retval None
  */
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  uint8_t index = uart_index(huart);
  serial_t *obj = rx_callback_obj[index];

  HAL_UART_Receive_IT(huart,  &(obj->recv), 1);
}
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
