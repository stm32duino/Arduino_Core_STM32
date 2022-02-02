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
#include "core_debug.h"
#include "lock_resource.h"
#include "uart.h"
#include "Arduino.h"
#include "PinAF_STM32F1.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)

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
#if defined(LPUART1_BASE)
  LPUART1_INDEX,
#endif
#if defined(LPUART2_BASE)
  LPUART2_INDEX,
#endif
  UART_NUM
} uart_index_t;

static UART_HandleTypeDef *uart_handlers[UART_NUM] = {NULL};

static serial_t serial_debug = { .uart = NP, .index = UART_NUM };

/* Aim of the function is to get serial_s pointer using huart pointer */
/* Highly inspired from magical linux kernel's "container_of" */
serial_t *get_serial_obj(UART_HandleTypeDef *huart)
{
  struct serial_s *obj_s;
  serial_t *obj;

  obj_s = (struct serial_s *)((char *)huart - offsetof(struct serial_s, handle));
  obj = (serial_t *)((char *)obj_s - offsetof(serial_t, uart));

  return (obj);
}

/**
  * @brief  Function called to initialize the uart interface
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void uart_init(serial_t *obj, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopbits)
{
  if (obj == NULL) {
    return;
  }

  UART_HandleTypeDef *huart = &(obj->handle);

  /* Determine the U(S)ART peripheral to use (USART1, USART2, ...) */
  USART_TypeDef *uart_tx = pinmap_peripheral(obj->pin_tx, PinMap_UART_TX);
  USART_TypeDef *uart_rx = pinmap_peripheral(obj->pin_rx, PinMap_UART_RX);
  USART_TypeDef *uart_rts = pinmap_peripheral(obj->pin_rts, PinMap_UART_RTS);
  USART_TypeDef *uart_cts = pinmap_peripheral(obj->pin_cts, PinMap_UART_CTS);

  /* Pin Tx must not be NP */
  if (uart_tx == NP) {
    core_debug("ERROR: [U(S)ART] Tx pin has no peripheral!\n");
    return;
  }
  /* Pin Rx must not be NP if not half-duplex */
  if ((obj->pin_rx != NC) && (uart_rx == NP)) {
    core_debug("ERROR: [U(S)ART] Rx pin has no peripheral!\n");
    return;
  }
  /* Pin RTS must not be NP if flow control is enabled */
  if ((obj->pin_rts != NC) && (uart_rts == NP)) {
    core_debug("ERROR: [U(S)ART] RTS pin has no peripheral!\n");
    return;
  }
  /* Pin CTS must not be NP if flow control is enabled */
  if ((obj->pin_cts != NC) && (uart_cts == NP)) {
    core_debug("ERROR: [U(S)ART] CTS pin has no peripheral!\n");
    return;
  }

  /*
   * Get the peripheral name (USART1, USART2, ...) from the pin
   * and assign it to the object
   */
  obj->uart = pinmap_merge_peripheral(uart_tx, uart_rx);
  /* We also merge RTS/CTS and assert all pins belong to the same instance */
  obj->uart = pinmap_merge_peripheral(obj->uart, uart_rts);
  obj->uart = pinmap_merge_peripheral(obj->uart, uart_cts);

  if (obj->uart == NP) {
    core_debug("ERROR: [U(S)ART] Rx/Tx/RTS/CTS pins peripherals mismatch!\n");
    return;
  }

  /* Enable USART clock */
#if defined(USART1_BASE)
  else if (obj->uart == USART1) {
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
    __HAL_RCC_USART1_CLK_ENABLE();
    obj->index = UART1_INDEX;
    obj->irq = USART1_IRQn;
  }
#endif
#if defined(USART2_BASE)
  else if (obj->uart == USART2) {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
    __HAL_RCC_USART2_CLK_ENABLE();
    obj->index = UART2_INDEX;
    obj->irq = USART2_IRQn;
  }
#endif
#if defined(USART3_BASE)
  else if (obj->uart == USART3) {
    __HAL_RCC_USART3_FORCE_RESET();
    __HAL_RCC_USART3_RELEASE_RESET();
    __HAL_RCC_USART3_CLK_ENABLE();
    obj->index = UART3_INDEX;
    obj->irq = USART3_IRQn;
  }
#endif
#if defined(UART4_BASE)
  else if (obj->uart == UART4) {
    __HAL_RCC_UART4_FORCE_RESET();
    __HAL_RCC_UART4_RELEASE_RESET();
    __HAL_RCC_UART4_CLK_ENABLE();
    obj->index = UART4_INDEX;
    obj->irq = UART4_IRQn;
  }
#elif defined(USART4_BASE)
  else if (obj->uart == USART4) {
    __HAL_RCC_USART4_FORCE_RESET();
    __HAL_RCC_USART4_RELEASE_RESET();
    __HAL_RCC_USART4_CLK_ENABLE();
    obj->index = UART4_INDEX;
    obj->irq = USART4_IRQn;
  }
#endif
#if defined(UART5_BASE)
  else if (obj->uart == UART5) {
    __HAL_RCC_UART5_FORCE_RESET();
    __HAL_RCC_UART5_RELEASE_RESET();
    __HAL_RCC_UART5_CLK_ENABLE();
    obj->index = UART5_INDEX;
    obj->irq = UART5_IRQn;
  }
#elif defined(USART5_BASE)
  else if (obj->uart == USART5) {
    __HAL_RCC_USART5_FORCE_RESET();
    __HAL_RCC_USART5_RELEASE_RESET();
    __HAL_RCC_USART5_CLK_ENABLE();
    obj->index = UART5_INDEX;
    obj->irq = USART5_IRQn;
  }
#endif
#if defined(USART6_BASE)
  else if (obj->uart == USART6) {
    __HAL_RCC_USART6_FORCE_RESET();
    __HAL_RCC_USART6_RELEASE_RESET();
    __HAL_RCC_USART6_CLK_ENABLE();
    obj->index = UART6_INDEX;
    obj->irq = USART6_IRQn;
  }
#endif
#if defined(LPUART1_BASE)
  else if (obj->uart == LPUART1) {
    __HAL_RCC_LPUART1_FORCE_RESET();
    __HAL_RCC_LPUART1_RELEASE_RESET();
    __HAL_RCC_LPUART1_CLK_ENABLE();
    obj->index = LPUART1_INDEX;
    obj->irq = LPUART1_IRQn;
  }
#endif
#if defined(LPUART2_BASE)
  else if (obj->uart == LPUART2) {
    __HAL_RCC_LPUART2_FORCE_RESET();
    __HAL_RCC_LPUART2_RELEASE_RESET();
    __HAL_RCC_LPUART2_CLK_ENABLE();
    obj->index = LPUART2_INDEX;
    obj->irq = LPUART2_IRQn;
  }
#endif
#if defined(UART7_BASE)
  else if (obj->uart == UART7) {
    __HAL_RCC_UART7_FORCE_RESET();
    __HAL_RCC_UART7_RELEASE_RESET();
    __HAL_RCC_UART7_CLK_ENABLE();
    obj->index = UART7_INDEX;
    obj->irq = UART7_IRQn;
  }
#elif defined(USART7_BASE)
  else if (obj->uart == USART7) {
    __HAL_RCC_USART7_FORCE_RESET();
    __HAL_RCC_USART7_RELEASE_RESET();
    __HAL_RCC_USART7_CLK_ENABLE();
    obj->index = UART7_INDEX;
    obj->irq = USART7_IRQn;
  }
#endif
#if defined(UART8_BASE)
  else if (obj->uart == UART8) {
    __HAL_RCC_UART8_FORCE_RESET();
    __HAL_RCC_UART8_RELEASE_RESET();
    __HAL_RCC_UART8_CLK_ENABLE();
    obj->index = UART8_INDEX;
    obj->irq = UART8_IRQn;
  }
#elif defined(USART8_BASE)
  else if (obj->uart == USART8) {
    __HAL_RCC_USART8_FORCE_RESET();
    __HAL_RCC_USART8_RELEASE_RESET();
    __HAL_RCC_USART8_CLK_ENABLE();
    obj->index = UART8_INDEX;
    obj->irq = USART8_IRQn;
  }
#endif
#if defined(UART9_BASE)
  else if (obj->uart == UART9) {
    __HAL_RCC_UART9_FORCE_RESET();
    __HAL_RCC_UART9_RELEASE_RESET();
    __HAL_RCC_UART9_CLK_ENABLE();
    obj->index = UART9_INDEX;
    obj->irq = UART9_IRQn;
  }
#endif
#if defined(UART10_BASE)
  else if (obj->uart == UART10) {
    __HAL_RCC_UART10_FORCE_RESET();
    __HAL_RCC_UART10_RELEASE_RESET();
    __HAL_RCC_UART10_CLK_ENABLE();
    obj->index = UART10_INDEX;
    obj->irq = UART10_IRQn;
  }
#endif
#if defined(USART10_BASE)
  else if (obj->uart == USART10) {
    __HAL_RCC_USART10_FORCE_RESET();
    __HAL_RCC_USART10_RELEASE_RESET();
    __HAL_RCC_USART10_CLK_ENABLE();
    obj->index = UART10_INDEX;
    obj->irq = USART10_IRQn;
  }
#endif

  /* Configure UART GPIO pins */
  pinmap_pinout(obj->pin_tx, PinMap_UART_TX);
  if (uart_rx != NP) {
    pinmap_pinout(obj->pin_rx, PinMap_UART_RX);
  }

  /* Configure flow control */
  uint32_t flow_control = UART_HWCONTROL_NONE;
  if (uart_rts != NP) {
    flow_control |= UART_HWCONTROL_RTS;
    pinmap_pinout(obj->pin_rts, PinMap_UART_RTS);
  }
  if (uart_cts != NP) {
    flow_control |= UART_HWCONTROL_CTS;
    pinmap_pinout(obj->pin_cts, PinMap_UART_CTS);
  }

  /* Configure uart */
  uart_handlers[obj->index] = huart;
  huart->Instance          = (USART_TypeDef *)(obj->uart);
  huart->Init.BaudRate     = baudrate;
  huart->Init.WordLength   = databits;
  huart->Init.StopBits     = stopbits;
  huart->Init.Parity       = parity;
  huart->Init.Mode         = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl    = flow_control;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx)\
 && !defined(STM32L1xx)
  huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif
#ifdef UART_ONE_BIT_SAMPLE_DISABLE
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
#endif

  /* Set the NVIC priority for future interrupts */
  HAL_NVIC_SetPriority(obj->irq, UART_IRQ_PRIO, UART_IRQ_SUBPRIO);

#if defined(LPUART1_BASE) || defined(LPUART2_BASE)
  /*
   * Note that LPUART clock source must be in the range
   * [3 x baud rate, 4096 x baud rate]
   * check Reference Manual
   */
  if ((obj->uart == LPUART1)
#if defined(LPUART2_BASE)
      || (obj->uart == LPUART2)
#endif
     ) {
    if (baudrate <= 9600) {
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
    if (uart_rx == NP) {
      if (HAL_HalfDuplex_Init(huart) == HAL_OK) {
        return;
      }
    } else if (HAL_UART_Init(huart) == HAL_OK) {
      return;
    }
    /* Trying to change LPUART clock source */
    /* If baudrate is lower than or equal to 9600 try to change to LSE */
    if (baudrate <= 9600) {
      /* Enable the clock if not already set by user */
      enableClock(LSE_CLOCK);
      if (obj->uart == LPUART1) {
        __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_LSE);
      }
#if defined(LPUART2_BASE)
      if (obj->uart == LPUART2) {
        __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_LSE);
      }
#endif
      if (uart_rx == NP) {
        if (HAL_HalfDuplex_Init(huart) == HAL_OK) {
          return;
        }
      } else if (HAL_UART_Init(huart) == HAL_OK) {
        return;
      }
    }
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY)) {
      if (obj->uart == LPUART1) {
        __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_HSI);
      }
#if defined(LPUART2_BASE)
      if (obj->uart == LPUART2) {
        __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_HSI);
      }
#endif
      if (uart_rx == NP) {
        if (HAL_HalfDuplex_Init(huart) == HAL_OK) {
          return;
        }
      } else if (HAL_UART_Init(huart) == HAL_OK) {
        return;
      }
    }
    if (obj->uart == LPUART1) {
#if defined(RCC_LPUART1CLKSOURCE_CSI)
      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_CSI);
#elif defined(RCC_LPUART1CLKSOURCE_PCLK1)
      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_PCLK1);
#elif defined(RCC_LPUART1CLKSOURCE_PCLK3)
      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_PCLK3);
#endif
    }
#if defined(LPUART2_BASE)
    if (obj->uart == LPUART2) {
      __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_PCLK1);
    }
#endif
    if (uart_rx == NP) {
      if (HAL_HalfDuplex_Init(huart) == HAL_OK) {
        return;
      }
    } else if (HAL_UART_Init(huart) == HAL_OK) {
      return;
    }
#if defined(RCC_LPUART1CLKSOURCE_SYSCLK)
    if (obj->uart == LPUART1) {
      __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_SYSCLK);
    }
#endif
#if defined(LPUART2_BASE)
    if (obj->uart == LPUART2) {
      __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_SYSCLK);
    }
#endif
  }
#endif

  if (uart_rx == NP) {
    if (HAL_HalfDuplex_Init(huart) != HAL_OK) {
      return;
    }
  } else if (HAL_UART_Init(huart) != HAL_OK) {
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
    case UART1_INDEX:
      __HAL_RCC_USART1_FORCE_RESET();
      __HAL_RCC_USART1_RELEASE_RESET();
      __HAL_RCC_USART1_CLK_DISABLE();
      break;
#endif
#if defined(USART2_BASE)
    case UART2_INDEX:
      __HAL_RCC_USART2_FORCE_RESET();
      __HAL_RCC_USART2_RELEASE_RESET();
      __HAL_RCC_USART2_CLK_DISABLE();
      break;
#endif
#if defined(USART3_BASE)
    case UART3_INDEX:
      __HAL_RCC_USART3_FORCE_RESET();
      __HAL_RCC_USART3_RELEASE_RESET();
      __HAL_RCC_USART3_CLK_DISABLE();
      break;
#endif
#if defined(UART4_BASE)
    case UART4_INDEX:
      __HAL_RCC_UART4_FORCE_RESET();
      __HAL_RCC_UART4_RELEASE_RESET();
      __HAL_RCC_UART4_CLK_DISABLE();
      break;
#elif defined(USART4_BASE)
    case UART4_INDEX:
      __HAL_RCC_USART4_FORCE_RESET();
      __HAL_RCC_USART4_RELEASE_RESET();
      __HAL_RCC_USART4_CLK_DISABLE();
      break;
#endif
#if defined(UART5_BASE)
    case UART5_INDEX:
      __HAL_RCC_UART5_FORCE_RESET();
      __HAL_RCC_UART5_RELEASE_RESET();
      __HAL_RCC_UART5_CLK_DISABLE();
      break;
#elif defined(USART5_BASE)
    case UART5_INDEX:
      __HAL_RCC_USART5_FORCE_RESET();
      __HAL_RCC_USART5_RELEASE_RESET();
      __HAL_RCC_USART5_CLK_DISABLE();
      break;
#endif
#if defined(USART6_BASE)
    case UART6_INDEX:
      __HAL_RCC_USART6_FORCE_RESET();
      __HAL_RCC_USART6_RELEASE_RESET();
      __HAL_RCC_USART6_CLK_DISABLE();
      break;
#endif
#if defined(LPUART1_BASE)
    case LPUART1_INDEX:
      __HAL_RCC_LPUART1_FORCE_RESET();
      __HAL_RCC_LPUART1_RELEASE_RESET();
      __HAL_RCC_LPUART1_CLK_DISABLE();
      break;
#endif
#if defined(LPUART2_BASE)
    case LPUART2_INDEX:
      __HAL_RCC_LPUART2_FORCE_RESET();
      __HAL_RCC_LPUART2_RELEASE_RESET();
      __HAL_RCC_LPUART2_CLK_DISABLE();
      break;
#endif
#if defined(UART7_BASE)
    case UART7_INDEX:
      __HAL_RCC_UART7_FORCE_RESET();
      __HAL_RCC_UART7_RELEASE_RESET();
      __HAL_RCC_UART7_CLK_DISABLE();
      break;
#elif defined(USART7_BASE)
    case UART7_INDEX:
      __HAL_RCC_USART7_FORCE_RESET();
      __HAL_RCC_USART7_RELEASE_RESET();
      __HAL_RCC_USART7_CLK_DISABLE();
      break;
#endif
#if defined(UART8_BASE)
    case UART8_INDEX:
      __HAL_RCC_UART8_FORCE_RESET();
      __HAL_RCC_UART8_RELEASE_RESET();
      __HAL_RCC_UART8_CLK_DISABLE();
      break;
#elif defined(USART8_BASE)
    case UART8_INDEX:
      __HAL_RCC_USART8_FORCE_RESET();
      __HAL_RCC_USART8_RELEASE_RESET();
      __HAL_RCC_USART8_CLK_DISABLE();
      break;
#endif
#if defined(UART9_BASE)
    case UART9_INDEX:
      __HAL_RCC_UART9_FORCE_RESET();
      __HAL_RCC_UART9_RELEASE_RESET();
      __HAL_RCC_UART9_CLK_DISABLE();
      break;
#endif
#if defined(UART10_BASE)
    case UART10_INDEX:
      __HAL_RCC_UART10_FORCE_RESET();
      __HAL_RCC_UART10_RELEASE_RESET();
      __HAL_RCC_UART10_CLK_DISABLE();
      break;
#endif
#if defined(USART10_BASE)
    case UART10_INDEX:
      __HAL_RCC_USART10_FORCE_RESET();
      __HAL_RCC_USART10_RELEASE_RESET();
      __HAL_RCC_USART10_CLK_DISABLE();
      break;
#endif
  }

  HAL_UART_DeInit(uart_handlers[obj->index]);

  /* Release uart debug to ensure init */
  if (serial_debug.index == obj->index) {
    serial_debug.index = UART_NUM;
  }
}

#if defined(HAL_PWR_MODULE_ENABLED) && (defined(UART_IT_WUF) || defined(LPUART1_BASE))
/**
  * @brief  Function called to configure the uart interface for low power
  * @param  obj : pointer to serial_t structure
  * @retval None
  */
void uart_config_lowpower(serial_t *obj)
{
  if (obj == NULL) {
    return;
  }
  /* Ensure HSI clock is enable */
  enableClock(HSI_CLOCK);

  hsem_lock(CFG_HW_RCC_CRRCR_CCIPR_SEMID, HSEM_LOCK_DEFAULT_RETRY);
  /* Configure HSI as source clock for low power wakeup clock */
  switch (obj->index) {
#if defined(USART1_BASE)
    case UART1_INDEX:
      if (__HAL_RCC_GET_USART1_SOURCE() != RCC_USART1CLKSOURCE_HSI) {
        __HAL_RCC_USART1_CONFIG(RCC_USART1CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(USART2_BASE) && defined(__HAL_RCC_USART2_CONFIG)
    case UART2_INDEX:
      if (__HAL_RCC_GET_USART2_SOURCE() != RCC_USART2CLKSOURCE_HSI) {
        __HAL_RCC_USART2_CONFIG(RCC_USART2CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(USART3_BASE) && defined(__HAL_RCC_USART3_CONFIG)
    case UART3_INDEX:
      if (__HAL_RCC_GET_USART3_SOURCE() != RCC_USART3CLKSOURCE_HSI) {
        __HAL_RCC_USART3_CONFIG(RCC_USART3CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(UART4_BASE) && defined(__HAL_RCC_UART4_CONFIG)
    case UART4_INDEX:
      if (__HAL_RCC_GET_UART4_SOURCE() != RCC_UART4CLKSOURCE_HSI) {
        __HAL_RCC_UART4_CONFIG(RCC_UART4CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(UART5_BASE) && defined(__HAL_RCC_UART5_CONFIG)
    case UART5_INDEX:
      if (__HAL_RCC_GET_UART5_SOURCE() != RCC_UART5CLKSOURCE_HSI) {
        __HAL_RCC_UART5_CONFIG(RCC_UART5CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(LPUART1_BASE) && defined(__HAL_RCC_LPUART1_CONFIG)
    case LPUART1_INDEX:
#ifdef __HAL_RCC_LPUART1_CLKAM_ENABLE
      __HAL_RCC_LPUART1_CLKAM_ENABLE();
#endif
      if (__HAL_RCC_GET_LPUART1_SOURCE() != RCC_LPUART1CLKSOURCE_HSI) {
        __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(LPUART2_BASE) && defined(__HAL_RCC_LPUART2_CONFIG)
    case LPUART2_INDEX:
      if (__HAL_RCC_GET_LPUART2_SOURCE() != RCC_LPUART2CLKSOURCE_HSI) {
        __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_HSI);
      }
      break;
#endif
  }
#if defined(UART_WAKEUP_EXTI_LINE)
  /* Enable EXTI wakeup interrupt if defined */
  LL_EXTI_EnableIT_0_31(UART_WAKEUP_EXTI_LINE);
#endif
  hsem_unlock(CFG_HW_RCC_CRRCR_CCIPR_SEMID);
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
  if (HAL_UART_Transmit(uart_handlers[obj->index], &data, size, TX_TIMEOUT) == HAL_OK) {
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
  if (DEBUG_UART != NP) {
    serial_debug.pin_rx = pinmap_pin(DEBUG_UART, PinMap_UART_RX);
#if defined(DEBUG_PINNAME_TX)
    serial_debug.pin_tx = DEBUG_PINNAME_TX;
#else
    serial_debug.pin_tx = pinmap_pin(DEBUG_UART, PinMap_UART_TX);
#endif

    uart_init(&serial_debug, DEBUG_UART_BAUDRATE, UART_WORDLENGTH_8B, UART_PARITY_NONE, UART_STOPBITS_1);
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
  uint32_t tickstart = HAL_GetTick();

  if (DEBUG_UART == NP) {
    return 0;
  }
  if (serial_debug.index >= UART_NUM) {
    /* Search if DEBUG_UART already initialized */
    for (serial_debug.index = 0; serial_debug.index < UART_NUM; serial_debug.index++) {
      if (uart_handlers[serial_debug.index] != NULL) {
        if (DEBUG_UART == uart_handlers[serial_debug.index]->Instance) {
          break;
        }
      }
    }

    if (serial_debug.index >= UART_NUM) {
      /* DEBUG_UART not initialized */
      uart_debug_init();
      if (serial_debug.index >= UART_NUM) {
        return 0;
      }
    } else {
      serial_t *obj = get_serial_obj(uart_handlers[serial_debug.index]);
      if (obj) {
        serial_debug.irq = obj->irq;
      }
    }
  }

  HAL_NVIC_DisableIRQ(serial_debug.irq);

  while (HAL_UART_Transmit(uart_handlers[serial_debug.index], data, size, TX_TIMEOUT) != HAL_OK) {
    if ((HAL_GetTick() - tickstart) >=  TX_TIMEOUT) {
      size = 0;
      break;
    }
  }

  HAL_NVIC_EnableIRQ(serial_debug.irq);

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

/**
 * Begin asynchronous RX transfer (enable interrupt for data collecting)
 *
 * @param obj : pointer to serial_t structure
 * @param callback : function call at the end of reception
 * @retval none
 */
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
  HAL_NVIC_DisableIRQ(obj->irq);

  HAL_UART_Receive_IT(uart_handlers[obj->index], &(obj->recv), 1);

  /* Enable interrupt */
  HAL_NVIC_EnableIRQ(obj->irq);
}

/**
 * Begin asynchronous TX transfer.
 *
 * @param obj : pointer to serial_t structure
 * @param callback : function call at the end of transmission
 * @retval none
 */
void uart_attach_tx_callback(serial_t *obj, int (*callback)(serial_t *), size_t size)
{
  if (obj == NULL) {
    return;
  }
  obj->tx_callback = callback;

  /* Must disable interrupt to prevent handle lock contention */
  HAL_NVIC_DisableIRQ(obj->irq);

  /* The following function will enable UART_IT_TXE and error interrupts */
  HAL_UART_Transmit_IT(uart_handlers[obj->index], &obj->tx_buff[obj->tx_tail], size);

  /* Enable interrupt */
  HAL_NVIC_EnableIRQ(obj->irq);
}

/**
 * Enable transmitter for half-duplex mode. NOOP in full-fuplex mode
 *
 * @param obj : pointer to serial_t structure
 * @retval none
 */
void uart_enable_tx(serial_t *obj)
{
  if (obj != NULL && obj->pin_rx == NC) {
    HAL_HalfDuplex_EnableTransmitter(uart_handlers[obj->index]);
  }
}

/**
 * Enable receiver for half-duplex mode. NOOP in full-fuplex mode
 *
 * @param obj : pointer to serial_t structure
 * @retval none
 */
void uart_enable_rx(serial_t *obj)
{
  if (obj != NULL && obj->pin_rx == NC) {
    HAL_HalfDuplex_EnableReceiver(uart_handlers[obj->index]);
  }
}

/**
  * @brief  Return index of the serial handler
  * @param  UartHandle pointer on the uart reference
  * @retval index
  */
/*
uint8_t uart_index(UART_HandleTypeDef *huart)
{
  uint8_t i = 0;
  if (huart == NULL) {
    return UART_NUM;
  }

  for (i = 0; i < UART_NUM; i++) {
    if (huart == uart_handlers[i]) {
      break;
    }
  }

  return i;
}
*/

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  serial_t *obj = get_serial_obj(huart);
  if (obj) {
    obj->rx_callback(obj);
  }
}

/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  serial_t *obj = get_serial_obj(huart);
  if (obj) {
    obj->tx_callback(obj);
  }
}

/**
  * @brief  error callback from UART
  * @param  UartHandle pointer on the uart reference
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
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
  /* Restart receive interrupt after any error */
  serial_t *obj = get_serial_obj(huart);
  if (obj && !serial_rx_active(obj)) {
    HAL_UART_Receive_IT(huart, &(obj->recv), 1);
  }
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
  HAL_UART_IRQHandler(uart_handlers[UART1_INDEX]);
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
  if (uart_handlers[UART2_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART2_INDEX]);
  }
#if defined(STM32G0xx) && defined(LPUART2_BASE)
  if (uart_handlers[LPUART2_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[LPUART2_INDEX]);
  }
#endif
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
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART3) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART3_INDEX]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART4) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART5) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART6) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART6_INDEX]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART7) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART7_INDEX]);
  }
  if (__HAL_GET_PENDING_IT(HAL_ITLINE_USART8) != RESET) {
    HAL_UART_IRQHandler(uart_handlers[UART8_INDEX]);
  }
#else
  if (uart_handlers[UART3_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART3_INDEX]);
  }
#if defined(STM32F0xx) || defined(STM32G0xx)
  /* USART3_4_IRQn */
  if (uart_handlers[UART4_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
  }
#if defined(STM32F030xC) || defined(STM32G0xx) && defined(LPUART2_BASE)
  if (uart_handlers[UART5_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
  }
  if (uart_handlers[UART6_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART6_INDEX]);
  }
#endif /* STM32F030xC */
#if defined(STM32G0xx) && defined(LPUART1_BASE)
  if (uart_handlers[LPUART1_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[LPUART1_INDEX]);
  }
#endif /* STM32G0xx && LPUART1_BASE */
#endif /* STM32F0xx || STM32G0xx */
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
  HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
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
  if (uart_handlers[UART4_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
  }
  if (uart_handlers[UART5_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART6_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[LPUART1_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART7_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART8_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART9_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART10_INDEX]);
}
#endif

/**
  * @brief  USART 10 IRQ handler
  * @param  None
  * @retval None
  */
#if defined(USART10_BASE)
void USART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART10_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART10_INDEX]);
}
#endif

/**
  * @brief  HAL UART Call Back
  * @param  UART handler
  * @retval None
  */
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  serial_t *obj = get_serial_obj(huart);
  HAL_UART_Receive_IT(huart,  &(obj->recv), 1);
}
#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

#ifdef __cplusplus
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
