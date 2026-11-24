/*
 *******************************************************************************
 * Copyright (c) 2016-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
/**
 * @file uart_serial.c
 * @brief Interrupt driven part of the U(S)ART driver, used by HardwareSerial:
 *        reception and transmission, HAL callbacks and IRQ handlers.
 *
 * Kept apart from uart.c, so a sketch which only uses the debug UART
 * (core logs, printf()) does not link the strong USARTx_IRQHandler() and can
 * define its own. This file is a member of core.a, it is extracted when
 * HardwareSerial references one of its functions.
 */
#include "Arduino.h"
#include "uart.h"
#include "uart_private.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)

/* Handlers registered with uart_attach_irq_handler(), by instance index */
static void (*uart_irq_hooks[UART_NUM])(void) = {NULL};

/**
  * @brief Index of a U(S)ART instance in the internal handlers table
  * @param instance U(S)ART instance
  * @return The index, UART_NUM if the instance is not supported
  */
static uint8_t uart_instance_index(USART_TypeDef *instance)
{
#if defined(USART1_BASE)
  if (instance == USART1) {
    return UART1_INDEX;
  }
#endif
#if defined(USART2_BASE)
  if (instance == USART2) {
    return UART2_INDEX;
  }
#endif
#if defined(USART3_BASE)
  if (instance == USART3) {
    return UART3_INDEX;
  }
#endif
#if defined(UART4_BASE)
  if (instance == UART4) {
    return UART4_INDEX;
  }
#elif defined(USART4_BASE)
  if (instance == USART4) {
    return UART4_INDEX;
  }
#endif
#if defined(UART5_BASE)
  if (instance == UART5) {
    return UART5_INDEX;
  }
#elif defined(USART5_BASE)
  if (instance == USART5) {
    return UART5_INDEX;
  }
#endif
#if defined(USART6_BASE)
  if (instance == USART6) {
    return UART6_INDEX;
  }
#endif
#if defined(UART7_BASE)
  if (instance == UART7) {
    return UART7_INDEX;
  }
#elif defined(USART7_BASE)
  if (instance == USART7) {
    return UART7_INDEX;
  }
#endif
#if defined(UART8_BASE)
  if (instance == UART8) {
    return UART8_INDEX;
  }
#elif defined(USART8_BASE)
  if (instance == USART8) {
    return UART8_INDEX;
  }
#endif
#if defined(UART9_BASE)
  if (instance == UART9) {
    return UART9_INDEX;
  }
#endif
#if defined(UART10_BASE)
  if (instance == UART10) {
    return UART10_INDEX;
  }
#elif defined(USART10_BASE)
  if (instance == USART10) {
    return UART10_INDEX;
  }
#endif
#if defined(USART11_BASE)
  if (instance == USART11) {
    return UART11_INDEX;
  }
#endif
#if defined(UART12_BASE)
  if (instance == UART12) {
    return UART12_INDEX;
  }
#endif
#if defined(LPUART1_BASE)
  if (instance == LPUART1) {
    return LPUART1_INDEX;
  }
#endif
#if defined(LPUART2_BASE)
  if (instance == LPUART2) {
    return LPUART2_INDEX;
  }
#endif
#if defined(LPUART3_BASE)
  if (instance == LPUART3) {
    return LPUART3_INDEX;
  }
#endif
  return UART_NUM;
}

bool uart_attach_irq_handler(USART_TypeDef *instance, void (*handler)(void))
{
  uint8_t index = uart_instance_index(instance);
  if (index >= UART_NUM) {
    return false;
  }
  uart_irq_hooks[index] = handler;
  return true;
}

/**
  * @brief Serve the interrupt of a U(S)ART: the handler registered with
  *        uart_attach_irq_handler() if any, otherwise the HAL handler if the
  *        instance is used by a HardwareSerial
  * @param index Index of the instance in the internal handlers table
  */
static void uart_irq_dispatch(uint8_t index)
{
  if (uart_irq_hooks[index] != NULL) {
    uart_irq_hooks[index]();
  } else if (uart_handlers[index] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[index]);
  }
}

uint8_t serial_rx_active(serial_t *obj)
{
#if defined(USE_HALV2_DRIVER)
  return ((HAL_UART_GetRxState(uart_handlers[obj->index]) & HAL_UART_RX_STATE_ACTIVE) == HAL_UART_RX_STATE_ACTIVE);
#else
  return ((HAL_UART_GetState(uart_handlers[obj->index]) & HAL_UART_STATE_BUSY_RX) == HAL_UART_STATE_BUSY_RX);
#endif
}

int uart_getc(serial_t *obj, unsigned char *c)
{
  if (obj == NULL) {
    return -1;
  }

  if (serial_rx_active(obj)) {
    return -1; /* Transaction ongoing */
  }

  *c = (unsigned char)(obj->recv);
  /* Restart RX irq */
  HAL_UART_Receive_IT(uart_handlers[obj->index], &(obj->recv), 1);

  return 0;
}

void uart_attach_rx_callback(serial_t *obj, void (*callback)(serial_t *))
{
  if (obj == NULL) {
    return;
  }

  /* Exit if a reception is already on-going */
  if (serial_rx_active(obj)) {
    return;
  }
  obj->rx_callback = callback;

  /* Must disable interrupt to prevent handle lock contention */
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_DisableIRQ(obj->irq);
#else
  HAL_NVIC_DisableIRQ(obj->irq);
#endif

  HAL_UART_Receive_IT(uart_handlers[obj->index], &(obj->recv), 1);

  /* Enable interrupt */
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_EnableIRQ(obj->irq);
#else
  HAL_NVIC_EnableIRQ(obj->irq);
#endif
}

void uart_attach_tx_callback(serial_t *obj, int (*callback)(serial_t *), size_t size)
{
  if (obj == NULL) {
    return;
  }
  obj->tx_callback = callback;

  /* Must disable interrupt to prevent handle lock contention */
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_DisableIRQ(obj->irq);
#else
  HAL_NVIC_DisableIRQ(obj->irq);
#endif

  /* The following function will enable UART_IT_TXE and error interrupts */
  HAL_UART_Transmit_IT(uart_handlers[obj->index], &obj->tx_buff[obj->tx_tail], size);

  /* Enable interrupt */
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_EnableIRQ(obj->irq);
#else
  HAL_NVIC_EnableIRQ(obj->irq);
#endif
}

void uart_enable_tx(serial_t *obj)
{
  if (obj != NULL && obj->pin_rx == NC) {
#if defined(USE_HALV2_DRIVER)
    HAL_UART_EnableTransmitter(uart_handlers[obj->index]);
#else
    HAL_HalfDuplex_EnableTransmitter(uart_handlers[obj->index]);
#endif
  }
}

void uart_enable_rx(serial_t *obj)
{
  if (obj != NULL && obj->pin_rx == NC) {
#if defined(USE_HALV2_DRIVER)
    HAL_UART_EnableReceiver(uart_handlers[obj->index]);
#else
    HAL_HalfDuplex_EnableReceiver(uart_handlers[obj->index]);
#endif
  }
}

/**
  * @brief Rx Transfer completed callback: call the RX callback of the serial object
  * @param huart Pointer on the uart reference
  * @param size_byte Number of received bytes (HALv2 driver only, unused)
  * @param rx_event Reception event type (HALv2 driver only, unused)
  */
#if defined(USE_HALV2_DRIVER)
void HAL_UART_RxCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte, hal_uart_rx_event_types_t rx_event)
#else
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
#endif
{
  serial_t *obj = get_serial_obj(huart);
  if (obj) {
#if defined(USE_HALV2_DRIVER)
    (void)size_byte;
    (void)rx_event;
#endif
    obj->rx_callback(obj);
  }
}

/**
  * @brief Tx Transfer completed callback: call the TX callback of the serial object
  * @param huart Pointer on the uart reference
  */
#if defined(USE_HALV2_DRIVER)
void HAL_UART_TxCpltCallback(hal_uart_handle_t *huart)
#else
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
#endif
{
  serial_t *obj = get_serial_obj(huart);
  if (obj) {
    obj->tx_callback(obj);
  }
}

/**
  * @brief Error callback from UART: clear the error flag and restart the reception
  * @param huart Pointer on the uart reference
  */
#if defined(USE_HALV2_DRIVER)
void HAL_UART_ErrorCallback(hal_uart_handle_t *huart)
#else
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
#endif
{
#if defined(USE_HALV2_DRIVER)
  USART_TypeDef *p_uartx = ((USART_TypeDef *)((uint32_t)(huart)->instance));
  if (LL_USART_IsActiveFlag_PE(p_uartx)) {
    LL_USART_ClearFlag_PE(p_uartx); /* Clear PE flag */
  } else if (LL_USART_IsActiveFlag_FE(p_uartx)) {
    LL_USART_ClearFlag_FE(p_uartx); /* Clear FE flag */
  } else if (LL_USART_IsActiveFlag_NE(p_uartx)) {
    LL_USART_ClearFlag_NE(p_uartx); /* Clear NE flag */
  } else if (LL_USART_IsActiveFlag_ORE(p_uartx)) {
    LL_USART_ClearFlag_ORE(p_uartx); /* Clear ORE flag */
  }
#else
#if defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32L1xx)
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    __HAL_UART_CLEAR_PEFLAG(huart); /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    __HAL_UART_CLEAR_FEFLAG(huart); /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    __HAL_UART_CLEAR_NEFLAG(huart); /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    __HAL_UART_CLEAR_OREFLAG(huart); /* Clear ORE flag */
  }
#else
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_PEF); /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_FEF); /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_NEF); /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_OREF); /* Clear ORE flag */
  }
#endif
#endif /* USE_HALV2_DRIVER */
  /* Restart receive interrupt after any error */
  serial_t *obj = get_serial_obj(huart);
  if (obj && !serial_rx_active(obj)) {
    HAL_UART_Receive_IT(huart, &(obj->recv), 1);
  }
}

/**
  * @brief HAL UART wakeup callback: restart the reception
  * @param huart UART handle
  */
#if defined(USE_HALV2_DRIVER)
void HAL_UARTEx_WakeupCallback(hal_uart_handle_t *huart)
#else
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
#endif
{
  serial_t *obj = get_serial_obj(huart);
  HAL_UART_Receive_IT(huart,  &(obj->recv), 1);
}

/**
  * @brief USART 1 IRQ handler
  */
#if defined(USART1_BASE)
void USART1_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(USART1_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
#endif
  uart_irq_dispatch(UART1_INDEX);
}
#endif

/**
  * @brief USART 2 IRQ handler
  */
#if defined(USART2_BASE)
void USART2_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(USART2_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
#endif
  uart_irq_dispatch(UART2_INDEX);
#if (defined(STM32G0xx) || defined(STM32U0xx)) && defined(LPUART2_BASE)
  uart_irq_dispatch(LPUART2_INDEX);
#endif
}
#endif

/**
  * @brief USART 3 IRQ handler
  */
#if defined(USART3_BASE)
void USART3_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(USART3_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
#endif
#if defined(STM32F091xC) || defined (STM32F098xx)
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART3) != RESET) {
    uart_irq_dispatch(UART3_INDEX);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART4) != RESET) {
    uart_irq_dispatch(UART4_INDEX);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART5) != RESET) {
    uart_irq_dispatch(UART5_INDEX);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART6) != RESET) {
    uart_irq_dispatch(UART6_INDEX);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART7) != RESET) {
    uart_irq_dispatch(UART7_INDEX);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART8) != RESET) {
    uart_irq_dispatch(UART8_INDEX);
  }
#else
  uart_irq_dispatch(UART3_INDEX);
#if defined(STM32F0xx) || defined(STM32G0xx) || defined(STM32U0xx)
  /* USART3_4_IRQn */
  uart_irq_dispatch(UART4_INDEX);
#if defined(STM32F030xC) || defined(STM32G0xx) && (defined(LPUART2_BASE) || defined(USART5_BASE))
  uart_irq_dispatch(UART5_INDEX);
  uart_irq_dispatch(UART6_INDEX);
#endif /* STM32F030xC */
#if (defined(STM32G0xx) || STM32U0xx) && defined(LPUART1_BASE)
  uart_irq_dispatch(LPUART1_INDEX);
#endif /* (STM32G0xx || STM32U0xx) && LPUART1_BASE */
#endif /* STM32F0xx || STM32G0xx || STM32U0xx */
#endif /* STM32F091xC || STM32F098xx */
}
#endif

/**
  * @brief UART 4 IRQ handler
  */
#if defined(UART4_BASE)
void UART4_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(UART4_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(UART4_IRQn);
#endif
  uart_irq_dispatch(UART4_INDEX);
}
#endif

/**
  * @brief USART 4/5 IRQ handler
  */
#if defined(STM32L0xx)
#if defined(USART4_BASE) || defined(USART5_BASE)
void USART4_5_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART4_IRQn);
  uart_irq_dispatch(UART4_INDEX);
  uart_irq_dispatch(UART5_INDEX);
}
#endif
#endif

/**
  * @brief USART 4 IRQ handler
  */
#if defined(STM32U0xx)
#if defined(USART4_BASE)
void USART4_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART4_IRQn);
  uart_irq_dispatch(UART4_INDEX);
#if defined(LPUART3_BASE)
  uart_irq_dispatch(LPUART3_INDEX);
#endif
}
#endif
#endif

/**
  * @brief USART 5 IRQ handler
  */
#if defined(UART5_BASE)
void UART5_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(UART5_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(UART5_IRQn);
#endif
  uart_irq_dispatch(UART5_INDEX);
}
#endif

/**
  * @brief USART 6 IRQ handler
  */
#if defined(USART6_BASE) && !defined(STM32F0xx) && !defined(STM32G0xx)
void USART6_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(USART6_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(USART6_IRQn);
#endif
  uart_irq_dispatch(UART6_INDEX);
}
#endif

/**
  * @brief LPUART 1 IRQ handler
  */
#if defined(LPUART1_BASE)
void LPUART1_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(LPUART1_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(LPUART1_IRQn);
#endif
  uart_irq_dispatch(LPUART1_INDEX);
}
#endif

/**
  * @brief UART 7 IRQ handler
  */
#if defined(UART7_BASE)
void UART7_IRQHandler(void)
{
#if defined(USE_HALV2_DRIVER)
  HAL_CORTEX_NVIC_ClearPendingIRQ(UART7_IRQn);
#else
  HAL_NVIC_ClearPendingIRQ(UART7_IRQn);
#endif
  uart_irq_dispatch(UART7_INDEX);
}
#endif

/**
  * @brief UART 8 IRQ handler
  */
#if defined(UART8_BASE)
void UART8_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART8_IRQn);
  uart_irq_dispatch(UART8_INDEX);
}
#endif

/**
  * @brief UART 9 IRQ handler
  */
#if defined(UART9_BASE)
void UART9_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART9_IRQn);
  uart_irq_dispatch(UART9_INDEX);
}
#endif

/**
  * @brief UART 10 IRQ handler
  */
#if defined(UART10_BASE)
void UART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART10_IRQn);
  uart_irq_dispatch(UART10_INDEX);
}
#endif

/**
  * @brief USART 10 IRQ handler
  */
#if defined(USART10_BASE)
void USART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART10_IRQn);
  uart_irq_dispatch(UART10_INDEX);
}
#endif

/**
  * @brief USART 11 IRQ handler
  */
#if defined(USART11_BASE)
void USART11_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART11_IRQn);
  uart_irq_dispatch(UART11_INDEX);
}
#endif

/**
  * @brief UART 12 IRQ handler
  */
#if defined(UART12_BASE)
void UART12_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART12_IRQn);
  uart_irq_dispatch(UART12_INDEX);
}
#endif

#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
