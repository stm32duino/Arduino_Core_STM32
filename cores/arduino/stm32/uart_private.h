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
 * @file uart_private.h
 * @brief Definitions shared by uart.c and uart_serial.c, not part of the API.
 */
#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_

#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)

/* @brief uart characteristics */
typedef enum {
#if defined(USART1_BASE)
  UART1_INDEX,
#endif
#if defined(USART2_BASE)
  UART2_INDEX,
#endif
#if defined(USART3_BASE)
  UART3_INDEX,
#endif
#if defined(UART4_BASE) || defined(USART4_BASE)
  UART4_INDEX,
#endif
#if defined(UART5_BASE) || defined(USART5_BASE)
  UART5_INDEX,
#endif
#if defined(USART6_BASE)
  UART6_INDEX,
#endif
#if defined(UART7_BASE) || defined(USART7_BASE)
  UART7_INDEX,
#endif
#if defined(UART8_BASE) || defined(USART8_BASE)
  UART8_INDEX,
#endif
#if defined(UART9_BASE)
  UART9_INDEX,
#endif
#if defined(UART10_BASE) || defined(USART10_BASE)
  UART10_INDEX,
#endif
#if defined(USART11_BASE)
  UART11_INDEX,
#endif
#if defined(UART12_BASE)
  UART12_INDEX,
#endif
#if defined(LPUART1_BASE)
  LPUART1_INDEX,
#endif
#if defined(LPUART2_BASE)
  LPUART2_INDEX,
#endif
#if defined(LPUART3_BASE)
  LPUART3_INDEX,
#endif
  UART_NUM
} uart_index_t;

/* HAL handles of the initialized U(S)ART, indexed by uart_index_t */
#if defined(USE_HALV2_DRIVER)
extern hal_uart_handle_t *uart_handlers[UART_NUM];
#else
extern UART_HandleTypeDef *uart_handlers[UART_NUM];
#endif

/* Get the serial_t object from its HAL UART handle, defined in uart.c */
#if defined(USE_HALV2_DRIVER)
serial_t *get_serial_obj(hal_uart_handle_t *huart);
#else
serial_t *get_serial_obj(UART_HandleTypeDef *huart);
#endif

#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* _UART_PRIVATE_H_ */
