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
#include "stm32yyxx_ll_rcc.h"

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

#if defined(USE_HALV2_DRIVER)
static hal_uart_handle_t *uart_handlers[UART_NUM] = {NULL};
#else
static UART_HandleTypeDef *uart_handlers[UART_NUM] = {NULL};
#endif

static serial_t serial_debug = {
  .uart = NP,
  .pin_tx = NC,
  .pin_rx = NC,
  .pin_rts = NC,
  .pin_cts = NC,
  .index = UART_NUM
};

/* Aim of the function is to get serial_s pointer using huart pointer */
/* Highly inspired from magical linux kernel's "container_of" */
#if defined(USE_HALV2_DRIVER)
serial_t *get_serial_obj(hal_uart_handle_t *huart)
#else
serial_t *get_serial_obj(UART_HandleTypeDef *huart)
#endif
{
  struct serial_s *obj_s;
  serial_t *obj;

  obj_s = (struct serial_s *)((char *)huart - offsetof(struct serial_s, handle));
  obj = (serial_t *)((char *)obj_s - offsetof(serial_t, uart));

  return (obj);
}

bool uart_enable_clock(serial_t *obj)
{
  bool status = true;
  /* Enable USART clock */
  if (obj->uart == NP) {
    status = false;
  }
#if defined(USART1_BASE)
  else if (obj->uart == USART1) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_USART1_Reset();
    HAL_RCC_USART1_EnableClock();
#else
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
    __HAL_RCC_USART1_CLK_ENABLE();
#endif
    obj->index = UART1_INDEX;
    obj->irq = USART1_IRQn;
  }
#endif
#if defined(USART2_BASE)
  else if (obj->uart == USART2) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_USART2_Reset();
    HAL_RCC_USART2_EnableClock();
#else
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
    __HAL_RCC_USART2_CLK_ENABLE();
#endif
    obj->index = UART2_INDEX;
    obj->irq = USART2_IRQn;
  }
#endif
#if defined(USART3_BASE)
  else if (obj->uart == USART3) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_USART3_Reset();
    HAL_RCC_USART3_EnableClock();
#else
    __HAL_RCC_USART3_FORCE_RESET();
    __HAL_RCC_USART3_RELEASE_RESET();
    __HAL_RCC_USART3_CLK_ENABLE();
#endif
    obj->index = UART3_INDEX;
    obj->irq = USART3_IRQn;
  }
#endif
#if defined(UART4_BASE)
  else if (obj->uart == UART4) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_UART4_Reset();
    HAL_RCC_UART4_EnableClock();
#else
    __HAL_RCC_UART4_FORCE_RESET();
    __HAL_RCC_UART4_RELEASE_RESET();
    __HAL_RCC_UART4_CLK_ENABLE();
#endif
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
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_UART5_Reset();
    HAL_RCC_UART5_EnableClock();
#else
    __HAL_RCC_UART5_FORCE_RESET();
    __HAL_RCC_UART5_RELEASE_RESET();
    __HAL_RCC_UART5_CLK_ENABLE();
#endif
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
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_USART6_Reset();
    HAL_RCC_USART6_EnableClock();
#else
    __HAL_RCC_USART6_FORCE_RESET();
    __HAL_RCC_USART6_RELEASE_RESET();
    __HAL_RCC_USART6_CLK_ENABLE();
#endif
    obj->index = UART6_INDEX;
    obj->irq = USART6_IRQn;
  }
#endif
#if defined(LPUART1_BASE)
  else if (obj->uart == LPUART1) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_LPUART1_Reset();
    HAL_RCC_LPUART1_EnableClock();
#else
    __HAL_RCC_LPUART1_FORCE_RESET();
    __HAL_RCC_LPUART1_RELEASE_RESET();
    __HAL_RCC_LPUART1_CLK_ENABLE();
#endif
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
#if defined(LPUART3_BASE)
  else if (obj->uart == LPUART3) {
    __HAL_RCC_LPUART3_FORCE_RESET();
    __HAL_RCC_LPUART3_RELEASE_RESET();
    __HAL_RCC_LPUART3_CLK_ENABLE();
    obj->index = LPUART3_INDEX;
    obj->irq = LPUART3_IRQn;
  }
#endif
#if defined(UART7_BASE)
  else if (obj->uart == UART7) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_UART7_Reset();
    HAL_RCC_UART7_EnableClock();
#else
    __HAL_RCC_UART7_FORCE_RESET();
    __HAL_RCC_UART7_RELEASE_RESET();
    __HAL_RCC_UART7_CLK_ENABLE();
#endif
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
#if defined(USART11_BASE)
  else if (obj->uart == USART11) {
    __HAL_RCC_USART11_FORCE_RESET();
    __HAL_RCC_USART11_RELEASE_RESET();
    __HAL_RCC_USART11_CLK_ENABLE();
    obj->index = UART11_INDEX;
    obj->irq = USART11_IRQn;
  }
#endif
#if defined(UART12_BASE)
  else if (obj->uart == UART12) {
    __HAL_RCC_UART12_FORCE_RESET();
    __HAL_RCC_UART12_RELEASE_RESET();
    __HAL_RCC_UART12_CLK_ENABLE();
    obj->index = UART12_INDEX;
    obj->irq = UART12_IRQn;
  }
#endif
  else {
    if (obj != &serial_debug) {
      core_debug("ERROR: [U(S)ART] Peripheral not supported!\n");
    }
    status = false;
  }
  return status;
}

#if defined(USE_HALV2_DRIVER)
bool uart_init(serial_t *obj, uint32_t baudrate, hal_uart_word_length_t databits, hal_uart_parity_t parity, hal_uart_stop_bits_t stopbits, bool rx_invert, bool tx_invert, bool data_invert)
#else
bool uart_init(serial_t *obj, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopbits, bool rx_invert, bool tx_invert, bool data_invert)
#endif
{
  bool status = true;
  if (obj == NULL) {
    status = false;
  } else {
    /* Determine the U(S)ART peripheral to use (USART1, USART2, ...) */
    USART_TypeDef *uart_tx = pinmap_peripheral(obj->pin_tx, PinMap_UART_TX);
    USART_TypeDef *uart_rx = pinmap_peripheral(obj->pin_rx, PinMap_UART_RX);
    USART_TypeDef *uart_rts = pinmap_peripheral(obj->pin_rts, PinMap_UART_RTS);
    USART_TypeDef *uart_cts = pinmap_peripheral(obj->pin_cts, PinMap_UART_CTS);
    /* Check if pins are swapped */
#if defined(UART_ADVFEATURE_SWAP_INIT) || defined(USE_HALV2_DRIVER)
    USART_TypeDef *uart_tx_swap = pinmap_peripheral(obj->pin_tx, PinMap_UART_RX);
    USART_TypeDef *uart_rx_swap = pinmap_peripheral(obj->pin_rx, PinMap_UART_TX);
#else
    /* Pin swap not supported */
    USART_TypeDef *uart_tx_swap = NP;
    USART_TypeDef *uart_rx_swap = NP;
#endif

    /* Pin Tx must not be NP */
    if ((uart_tx == NP) && (uart_tx_swap == NP)) {
      if (obj != &serial_debug) {
        core_debug("ERROR: [U(S)ART] Tx pin has no peripheral!\n");
      }
      status = false;
    }
    /* Pin Rx must not be NP if not half-duplex */
    if (status && (obj->pin_rx != NC) && (uart_rx == NP) && (uart_rx_swap == NP)) {
      if (obj != &serial_debug) {
        core_debug("ERROR: [U(S)ART] Rx pin has no peripheral!\n");
      }
      status = false;
    }
    /* Pin RTS must not be NP if flow control is enabled */
    if (status && (obj->pin_rts != NC) && (uart_rts == NP)) {
      if (obj != &serial_debug) {
        core_debug("ERROR: [U(S)ART] RTS pin has no peripheral!\n");
      }
      status = false;
    }
    /* Pin CTS must not be NP if flow control is enabled */
    if (status && (obj->pin_cts != NC) && (uart_cts == NP)) {
      if (obj != &serial_debug) {
        core_debug("ERROR: [U(S)ART] CTS pin has no peripheral!\n");
      }
      status = false;
    }
    if (status) {
      /*
      * Get the peripheral name (USART1, USART2, ...) from the pin
      * and assign it to the object
      */
      obj->uart = pinmap_merge_peripheral(uart_tx, uart_rx);
      if (obj->uart == NP) {
        /* Regular pins not matched, check if they can be swapped */
        obj->uart = pinmap_merge_peripheral(uart_tx_swap, uart_rx_swap);
      }
      /* We also merge RTS/CTS and assert all pins belong to the same instance */
      obj->uart = pinmap_merge_peripheral(obj->uart, uart_rts);
      obj->uart = pinmap_merge_peripheral(obj->uart, uart_cts);

      if (obj->uart == NP) {
        if (obj != &serial_debug) {
          core_debug("ERROR: [U(S)ART] Rx/Tx/RTS/CTS pins peripherals mismatch!\n");
        }
        status = false;
      } else {
        /* Configure UART GPIO pins */
#if defined(UART_ADVFEATURE_SWAP_INIT)
        uint32_t pin_swap = UART_ADVFEATURE_SWAP_DISABLE;
#elif defined(USE_HALV2_DRIVER)
        hal_uart_tx_rx_swap_status_t pin_swap = HAL_UART_TX_RX_SWAP_DISABLED;
#endif
        if (uart_tx != NP) {
          /* Regular GPIO */
          pinmap_pinout(obj->pin_tx, PinMap_UART_TX);
          if (uart_rx != NP) {
            pinmap_pinout(obj->pin_rx, PinMap_UART_RX);
          }
        }
#if defined(UART_ADVFEATURE_SWAP_INIT) || defined(USE_HALV2_DRIVER)
        else if (uart_tx_swap != NP) {
          /* Swapped GPIO */
          pinmap_pinout(obj->pin_tx, PinMap_UART_RX);
          if (uart_rx_swap != NP) {
            pinmap_pinout(obj->pin_rx, PinMap_UART_TX);
          }
#if defined(UART_ADVFEATURE_SWAP_INIT)
          pin_swap = UART_ADVFEATURE_SWAP_ENABLE;
#elif defined(USE_HALV2_DRIVER)
          pin_swap = HAL_UART_TX_RX_SWAP_ENABLED;
#endif
        }
#endif
        /* Enable clock for this peripheral */
        status = uart_enable_clock(obj);
#if defined (USE_HALV2_DRIVER)
        hal_uart_handle_t *huart = &(obj->handle);
        hal_uart_config_t uart_config;
        hal_uart_hw_control_t flow_control = HAL_UART_HW_CONTROL_NONE;
        if (uart_rts != NP) {
          flow_control |= HAL_UART_HW_CONTROL_RTS;
        }
        if (uart_cts != NP) {
          flow_control |= HAL_UART_HW_CONTROL_CTS;
        }

        if (HAL_UART_Init(huart, (hal_uart_t)obj->uart) != HAL_OK) {
          status = false;
        } else {
          uart_handlers[obj->index] = huart;
          uart_config.baud_rate = baudrate;
          uart_config.word_length = databits;
          uart_config.stop_bits = stopbits;
          uart_config.parity = parity;
          uart_config.direction = HAL_UART_DIRECTION_TX_RX;
          uart_config.hw_flow_ctl = flow_control;
          uart_config.oversampling = HAL_UART_OVERSAMPLING_16;
          uart_config.one_bit_sampling = HAL_UART_ONE_BIT_SAMPLE_DISABLE;
          uart_config.clock_prescaler = uart_compute_prescaler(huart, &uart_config);
#if defined(LPUART1_BASE)
          uart_init_lpuart(huart, baudrate);
#endif
          /* Set the NVIC priority for future interrupts */
          HAL_CORTEX_NVIC_SetPriority(obj->irq, UART_IRQ_PRIO, UART_IRQ_SUBPRIO);

          if (HAL_UART_SetConfig(huart, &uart_config) != HAL_OK) {
            status = false;
          } else {
            /* Tx and Rx pins swapping configuration */
            if (pin_swap == HAL_UART_TX_RX_SWAP_ENABLED) {
              if (HAL_UART_EnableTxRxSwap(huart) != HAL_OK) {
                status = false;
              }
            }
            if (status && rx_invert) {
              /* Rx pin level inversion configuration */
              if (HAL_UART_EnableRxPinLevelInvert(huart) != HAL_OK) {
                status = false;
              }
            }
            if (status && tx_invert) {
              /* Tx pin level inversion configuration */
              if (HAL_UART_EnableTxPinLevelInvert(huart) != HAL_OK) {
                status = false;
              }
            }
            if (status && data_invert) {
              /* Data inversion configuration */
              if (HAL_UART_EnableDataInvert(huart) != HAL_OK) {
                status = false;
              }
            }
            if ((uart_rx == NP) && (uart_rx_swap == NP)) {
              if (HAL_UART_EnableHalfDuplexMode(huart) != HAL_OK) {
                status = false;
              }
            }
          }
        }
#else
        UART_HandleTypeDef *huart = &(obj->handle);

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

        /* Configure UART Clock Prescaler */
#if defined(UART_PRESCALER_DIV1)
        huart->Init.ClockPrescaler = uart_compute_prescaler(huart);
#endif
#if defined(UART_ADVFEATURE_NO_INIT)
        // Default value
        huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#if defined(UART_ADVFEATURE_SWAP_INIT)
        huart->AdvancedInit.AdvFeatureInit |= UART_ADVFEATURE_SWAP_INIT;
        huart->AdvancedInit.Swap = pin_swap;
#endif
#if defined(UART_ADVFEATURE_RXINVERT_INIT)
        if (rx_invert) {
          huart->AdvancedInit.AdvFeatureInit |= UART_ADVFEATURE_RXINVERT_INIT;
          huart->AdvancedInit.RxPinLevelInvert = UART_ADVFEATURE_RXINV_ENABLE;
        }
#endif
#if defined(UART_ADVFEATURE_TXINVERT_INIT)
        if (tx_invert) {
          huart->AdvancedInit.AdvFeatureInit |= UART_ADVFEATURE_TXINVERT_INIT;
          huart->AdvancedInit.TxPinLevelInvert = UART_ADVFEATURE_TXINV_ENABLE;
        }
#endif
#if defined(UART_ADVFEATURE_DATAINVERT_INIT)
        if (data_invert) {
          huart->AdvancedInit.AdvFeatureInit |= UART_ADVFEATURE_DATAINVERT_INIT;
          huart->AdvancedInit.DataInvert = UART_ADVFEATURE_DATAINV_ENABLE;
        }
#endif
#else /* UART_ADVFEATURE_NO_INIT */
        (void)rx_invert;
        (void)tx_invert;
        (void)data_invert;
#endif
#ifdef UART_ONE_BIT_SAMPLE_DISABLE
        huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
#endif

        /* Set the NVIC priority for future interrupts */
        HAL_NVIC_SetPriority(obj->irq, UART_IRQ_PRIO, UART_IRQ_SUBPRIO);

#if defined(LPUART1_BASE) || defined(LPUART2_BASE)
        if (IS_LPUART_INSTANCE(huart->Instance)) {
          uart_init_lpuart(huart);
        }
#endif
        if ((uart_rx == NP) && (uart_rx_swap == NP)) {
          if (HAL_HalfDuplex_Init(huart) != HAL_OK) {
            status = false;
          }
        } else if (HAL_UART_Init(huart) != HAL_OK) {
          status = false;
        }
#endif /* USE_HALV2_DRIVER */
      }
    }
  }
  return status;
}

void uart_deinit(serial_t *obj)
{
  /* Ensure uart is set to prevent deinitializing uart at index 0 */
  if (obj->uart) {
    /* Reset UART and disable clock */
    switch (obj->index) {
#if defined(USART1_BASE)
      case UART1_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_USART1_Reset();
        HAL_RCC_USART1_DisableClock();
#else
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        __HAL_RCC_USART1_CLK_DISABLE();
#endif
        break;
#endif
#if defined(USART2_BASE)
      case UART2_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_USART2_Reset();
        HAL_RCC_USART2_DisableClock();
#else
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
#endif
        break;
#endif
#if defined(USART3_BASE)
      case UART3_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_USART3_Reset();
        HAL_RCC_USART3_DisableClock();
#else
        __HAL_RCC_USART3_FORCE_RESET();
        __HAL_RCC_USART3_RELEASE_RESET();
        __HAL_RCC_USART3_CLK_DISABLE();
#endif
        break;
#endif
#if defined(UART4_BASE)
      case UART4_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_UART4_Reset();
        HAL_RCC_UART4_DisableClock();
#else
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();
        __HAL_RCC_UART4_CLK_DISABLE();
#endif
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
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_UART5_Reset();
        HAL_RCC_UART5_DisableClock();
#else
        __HAL_RCC_UART5_FORCE_RESET();
        __HAL_RCC_UART5_RELEASE_RESET();
        __HAL_RCC_UART5_CLK_DISABLE();
#endif
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
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_USART6_Reset();
        HAL_RCC_USART6_DisableClock();
#else
        __HAL_RCC_USART6_FORCE_RESET();
        __HAL_RCC_USART6_RELEASE_RESET();
        __HAL_RCC_USART6_CLK_DISABLE();
#endif
        break;
#endif
#if defined(LPUART1_BASE)
      case LPUART1_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_LPUART1_Reset();
        HAL_RCC_LPUART1_DisableClock();
#else
        __HAL_RCC_LPUART1_FORCE_RESET();
        __HAL_RCC_LPUART1_RELEASE_RESET();
        __HAL_RCC_LPUART1_CLK_DISABLE();
#endif
        break;
#endif
#if defined(LPUART2_BASE)
      case LPUART2_INDEX:
        __HAL_RCC_LPUART2_FORCE_RESET();
        __HAL_RCC_LPUART2_RELEASE_RESET();
        __HAL_RCC_LPUART2_CLK_DISABLE();
        break;
#endif
#if defined(LPUART3_BASE)
      case LPUART3_INDEX:
        __HAL_RCC_LPUART3_FORCE_RESET();
        __HAL_RCC_LPUART3_RELEASE_RESET();
        __HAL_RCC_LPUART3_CLK_DISABLE();
        break;
#endif
#if defined(UART7_BASE)
      case UART7_INDEX:
#if defined(USE_HALV2_DRIVER)
        HAL_RCC_UART7_Reset();
        HAL_RCC_UART7_DisableClock();
#else
        __HAL_RCC_UART7_FORCE_RESET();
        __HAL_RCC_UART7_RELEASE_RESET();
        __HAL_RCC_UART7_CLK_DISABLE();
#endif
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
#if defined(USART11_BASE)
      case UART11_INDEX:
        __HAL_RCC_USART11_FORCE_RESET();
        __HAL_RCC_USART11_RELEASE_RESET();
        __HAL_RCC_USART11_CLK_DISABLE();
        break;
#endif
#if defined(UART12_BASE)
      case UART12_INDEX:
        __HAL_RCC_UART12_FORCE_RESET();
        __HAL_RCC_UART12_RELEASE_RESET();
        __HAL_RCC_UART12_CLK_DISABLE();
        break;
#endif
    }

    HAL_UART_DeInit(uart_handlers[obj->index]);

    /* Release uart debug to ensure init */
    if (serial_debug.index == obj->index) {
      serial_debug.index = UART_NUM;
    }
  }
}

#if defined(LPUART1_BASE) || defined(LPUART2_BASE)
/*
* Note that LPUART clock source must be in the range
* [3 x baud rate, 4096 x baud rate]
* check Reference Manual
*/
#if defined(USE_HALV2_DRIVER)
void uart_init_lpuart(hal_uart_handle_t *huart, uint32_t baudrate)
{
  if (baudrate <= 9600) {
    HAL_UART_EnableStopMode(huart);
  } else {
    HAL_UART_DisableStopMode(huart);
  }
}
#else
void uart_init_lpuart(UART_HandleTypeDef *huart)
{
  if (huart->Init.BaudRate <= 9600) {
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
}
#endif /* USE_HALV2_DRIVER */
#endif /* LPUART1_BASE || LPUART2_BASE */


#if defined(HAL_PWR_MODULE_ENABLED) && (defined(UART_IT_WUF) || defined(LPUART1_BASE))
void uart_config_lowpower(serial_t *obj)
{
  if (obj == NULL) {
    return;
  }
  /* Ensure clock is enable */
#if defined(STM32WB0x)
  enableClock(LSE_CLOCK);
#else
  enableClock(HSI_CLOCK);
#endif

  hsem_lock(CFG_HW_RCC_CRRCR_CCIPR_SEMID, HSEM_LOCK_DEFAULT_RETRY);
  /* Configure HSI as source clock for low power wakeup clock */
  switch (obj->index) {
#if defined(USART1_BASE)
    case UART1_INDEX:
      /* STM32WB0x direct clock CLK_16M */
#if defined(__HAL_RCC_GET_USART1_SOURCE)
      if (__HAL_RCC_GET_USART1_SOURCE() != RCC_USART1CLKSOURCE_HSI) {
        __HAL_RCC_USART1_CONFIG(RCC_USART1CLKSOURCE_HSI);
      }
#endif
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
#if defined(LPUART1_BASE) && (defined(__HAL_RCC_LPUART1_CONFIG) || defined(__HAL_RCC_LPUART1_CLK_CONFIG))
    /* LPUART1 is used for low power wakeup */
    case LPUART1_INDEX:
#if defined(__HAL_RCC_LPUART1_CONFIG)
#ifdef __HAL_RCC_LPUART1_CLKAM_ENABLE
      __HAL_RCC_LPUART1_CLKAM_ENABLE();
#endif
      if (__HAL_RCC_GET_LPUART1_SOURCE() != RCC_LPUART1CLKSOURCE_HSI) {
        __HAL_RCC_LPUART1_CONFIG(RCC_LPUART1CLKSOURCE_HSI);
      }
#elif defined(__HAL_RCC_LPUART1_CLK_CONFIG)
      if (__HAL_RCC_GET_LPUART1_CLK_CONFIG() != RCC_LPUART1_CLKSOURCE_LSE) {
        __HAL_RCC_LPUART1_CLK_CONFIG(RCC_LPUART1_CLKSOURCE_LSE);
      }
#endif
      break;
#endif
#if defined(LPUART2_BASE) && defined(__HAL_RCC_LPUART2_CONFIG)
    case LPUART2_INDEX:
      if (__HAL_RCC_GET_LPUART2_SOURCE() != RCC_LPUART2CLKSOURCE_HSI) {
        __HAL_RCC_LPUART2_CONFIG(RCC_LPUART2CLKSOURCE_HSI);
      }
      break;
#endif
#if defined(LPUART3_BASE) && defined(__HAL_RCC_LPUART3_CONFIG)
    case LPUART3_INDEX:
      if (__HAL_RCC_GET_LPUART3_SOURCE() != RCC_LPUART3CLKSOURCE_HSI) {
        __HAL_RCC_LPUART3_CONFIG(RCC_LPUART3CLKSOURCE_HSI);
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
  * @brief Function called to initialize the debug uart interface
  * @note   Call only if debug U(S)ART peripheral is not already initialized
  *         by a Serial instance
  *         Default config: 8N1
  * @return true on success, false otherwise
  */
bool uart_debug_init(void)
{
  bool status = false;
  if (DEBUG_UART != NP) {
#if defined(DEBUG_PINNAME_TX)
    serial_debug.pin_tx = DEBUG_PINNAME_TX;
#else
    serial_debug.pin_tx = pinmap_pin(DEBUG_UART, PinMap_UART_TX);
#endif
    /* serial_debug.pin_rx set by default to NC to configure in half duplex mode */
#if defined(USE_HALV2_DRIVER)
    status = uart_init(&serial_debug, DEBUG_UART_BAUDRATE, HAL_UART_WORD_LENGTH_8_BIT, HAL_UART_PARITY_ODD, HAL_UART_STOP_BIT_1, false, false, false);
#else
    status = uart_init(&serial_debug, DEBUG_UART_BAUDRATE, UART_WORDLENGTH_8B, UART_PARITY_NONE, UART_STOPBITS_1, false, false, false);
#endif
  }
  return status;
}

size_t uart_debug_write(uint8_t *data, uint32_t size)
{
  uint32_t tickstart = HAL_GetTick();
  serial_t *obj = NULL;

  if (serial_debug.index >= UART_NUM) {
    if (DEBUG_UART == NP) {
      return 0;
    }

    /* Search if DEBUG_UART already initialized */
    for (serial_debug.index = 0; serial_debug.index < UART_NUM; serial_debug.index++) {
      if (uart_handlers[serial_debug.index] != NULL) {
#if defined(USE_HALV2_DRIVER)
        if (DEBUG_UART == (uint32_t *)uart_handlers[serial_debug.index]->instance)
#else
        if (DEBUG_UART == uart_handlers[serial_debug.index]->Instance)
#endif
        {
          break;
        }
      }
    }

    if (serial_debug.index >= UART_NUM) {
      /* DEBUG_UART not initialized */
      if (!uart_debug_init()) {
        return 0;
      }
    }
  }
  obj = get_serial_obj(uart_handlers[serial_debug.index]);
  if (!obj) {
    return 0;
  }

  while (serial_tx_active(obj)) {
    if ((HAL_GetTick() - tickstart) >= TX_TIMEOUT) {
      return 0;
    }
  }

  if (HAL_UART_Transmit(&(obj->handle), data, size, TX_TIMEOUT) != HAL_OK) {
    size = 0;
  }

  return size;
}

uint8_t serial_rx_active(serial_t *obj)
{
#if defined(USE_HALV2_DRIVER)
  return ((HAL_UART_GetRxState(uart_handlers[obj->index]) & HAL_UART_RX_STATE_ACTIVE) == HAL_UART_RX_STATE_ACTIVE);
#else
  return ((HAL_UART_GetState(uart_handlers[obj->index]) & HAL_UART_STATE_BUSY_RX) == HAL_UART_STATE_BUSY_RX);
#endif
}

uint8_t serial_tx_active(serial_t *obj)
{
#if defined(USE_HALV2_DRIVER)
  return ((HAL_UART_GetTxState(uart_handlers[obj->index]) & HAL_UART_TX_STATE_ACTIVE) == HAL_UART_TX_STATE_ACTIVE);
#else
  return ((HAL_UART_GetState(uart_handlers[obj->index]) & HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX);
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
  * @brief Return index of the serial handler
  * @param huart Pointer on the uart reference
  * @return Index of the serial handler
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
  * @brief Rx Transfer completed callback
  * @param huart Pointer on the uart reference
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
  * @brief Tx Transfer completed callback
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
  * @brief Error callback from UART
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
  HAL_UART_IRQHandler(uart_handlers[UART1_INDEX]);
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
  if (uart_handlers[UART2_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART2_INDEX]);
  }
#if (defined(STM32G0xx) || defined(STM32U0xx)) && defined(LPUART2_BASE)
  if (uart_handlers[LPUART2_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[LPUART2_INDEX]);
  }
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
#if defined(STM32F0xx) || defined(STM32G0xx) || defined(STM32U0xx)
  /* USART3_4_IRQn */
  if (uart_handlers[UART4_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
  }
#if defined(STM32F030xC) || defined(STM32G0xx) && (defined(LPUART2_BASE) || defined(USART5_BASE))
  if (uart_handlers[UART5_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
  }
  if (uart_handlers[UART6_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART6_INDEX]);
  }
#endif /* STM32F030xC */
#if (defined(STM32G0xx) || STM32U0xx) && defined(LPUART1_BASE)
  if (uart_handlers[LPUART1_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[LPUART1_INDEX]);
  }
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
  HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
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
  * @brief USART 4 IRQ handler
  */
#if defined(STM32U0xx)
#if defined(USART4_BASE)
void USART4_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART4_IRQn);
  if (uart_handlers[UART4_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[UART4_INDEX]);
  }
#if defined(LPUART3_BASE)
  if (uart_handlers[LPUART3_INDEX] != NULL) {
    HAL_UART_IRQHandler(uart_handlers[LPUART3_INDEX]);
  }
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
  HAL_UART_IRQHandler(uart_handlers[UART5_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART6_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[LPUART1_INDEX]);
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
  HAL_UART_IRQHandler(uart_handlers[UART7_INDEX]);
}
#endif

/**
  * @brief UART 8 IRQ handler
  */
#if defined(UART8_BASE)
void UART8_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART8_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART8_INDEX]);
}
#endif

/**
  * @brief UART 9 IRQ handler
  */
#if defined(UART9_BASE)
void UART9_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART9_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART9_INDEX]);
}
#endif

/**
  * @brief UART 10 IRQ handler
  */
#if defined(UART10_BASE)
void UART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART10_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART10_INDEX]);
}
#endif

/**
  * @brief USART 10 IRQ handler
  */
#if defined(USART10_BASE)
void USART10_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART10_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART10_INDEX]);
}
#endif

/**
  * @brief USART 11 IRQ handler
  */
#if defined(USART11_BASE)
void USART11_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(USART11_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART11_INDEX]);
}
#endif

/**
  * @brief UART 12 IRQ handler
  */
#if defined(UART12_BASE)
void UART12_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(UART12_IRQn);
  HAL_UART_IRQHandler(uart_handlers[UART12_INDEX]);
}
#endif

/**
  * @brief HAL UART wakeup callback
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

#if defined(USE_HALV2_DRIVER)
hal_uart_prescaler_t uart_compute_prescaler(hal_uart_handle_t *huart, hal_uart_config_t *config)
{
  hal_uart_prescaler_t prescaler = HAL_UART_PRESCALER_DIV1;
  static const uint16_t presc_div[12] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256};
  uint32_t freq = HAL_RCC_UART_GetKernelClkFreq((USART_TypeDef *)huart->instance);
  uint32_t usartdiv = 0;
  if (huart->instance == HAL_LPUART1) {
    for (uint32_t idx = 0; idx < 12; idx++) {
      usartdiv = (freq / presc_div[idx]);
      if ((usartdiv > (3U * config->baud_rate)) && (usartdiv < (4096U * config->baud_rate))) {
        prescaler = HAL_UART_PRESCALER_DIV1 + idx;
        break;
      }
    }
  } else {
    for (uint32_t idx = 0; idx < 12; idx++) {
      if (config->oversampling == HAL_UART_OVERSAMPLING_8) {
        usartdiv = LL_USART_DIV_SAMPLING8(freq, presc_div[idx], config->baud_rate);
      } else {
        usartdiv = (uint32_t)(LL_USART_DIV_SAMPLING16(freq, presc_div[idx], config->baud_rate));
      }
      if ((usartdiv >= 0x10U) && (usartdiv <= 0xFFFFU)) {
        prescaler = HAL_UART_PRESCALER_DIV1 + idx;
        break;
      }
    }
  }
  return prescaler;
}
#endif

#if defined(UART_PRESCALER_DIV1)
uint32_t uart_compute_prescaler(UART_HandleTypeDef *huart)
{
  uint32_t prescaler = UART_PRESCALER_DIV1;
  static const uint16_t presc_div[12] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256};
  uint32_t freq = uart_get_clock_source_freq(huart);
  uint32_t usartdiv = 0;

#if defined(UART_INSTANCE_LOWPOWER)
  if (UART_INSTANCE_LOWPOWER(huart)) {
    for (uint32_t idx = 0; idx < 12; idx++) {
      /* Check computed UsartDiv value is in allocated range
        (it is forbidden to write values lower than 0x300 in the LPUART_BRR register) */
      usartdiv = (uint32_t)(UART_DIV_LPUART(freq, huart->Init.BaudRate, presc_div[idx]));
      if ((usartdiv >= 0x00000300U) && (usartdiv <= 0x000FFFFFU)) {
        prescaler = UART_PRESCALER_DIV1 + idx;
        break;
      }
    }
  } else
#endif /* UART_INSTANCE_LOWPOWER */
  {
    for (uint32_t idx = 0; idx < 12; idx++) {
      if (huart->Init.OverSampling == UART_OVERSAMPLING_8) {
        usartdiv = (uint32_t)(UART_DIV_SAMPLING8(freq, huart->Init.BaudRate, presc_div[idx]));
      } else {
        usartdiv = (uint32_t)(UART_DIV_SAMPLING16(freq, huart->Init.BaudRate, presc_div[idx]));
      }
      if ((usartdiv >= 0x10U) && (usartdiv <= 0x0000FFFFU)) {
        prescaler = UART_PRESCALER_DIV1 + idx;
        break;
      }
    }
  }
  return prescaler;
}

uint32_t uart_get_clock_source_freq(UART_HandleTypeDef *huart)
{
  uint32_t freq = 0;
#if defined(STM32WB0x) || defined(STM32WL3x)
  freq = UART_PERIPHCLK;
  if (UART_INSTANCE_LOWPOWER(huart)) {
#if defined(RCC_CFGR_LPUCLKSEL)
    freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_LPUART1);
#endif /* RCC_CFGR_LPUCLKSEL */
  }
#else /* STM32WB0x || STM32WL3x */
  uint32_t clocksource;
  UART_GETCLOCKSOURCE(huart, clocksource);
#if defined(STM32H5) || defined(STM32MP1) || defined(STM32U0) ||\
    defined(STM32U3) || defined(STM32U5)
  freq = HAL_RCCEx_GetPeriphCLKFreq(clocksource);
#else
  switch (clocksource) {
#if defined(UART_CLOCKSOURCE_D2PCLK1) || defined(UART_CLOCKSOURCE_PCLK1)
#if defined(UART_CLOCKSOURCE_D2PCLK1)
    case UART_CLOCKSOURCE_D2PCLK1:
#endif /* UART_CLOCKSOURCE_D2PCLK1*/
#if defined(UART_CLOCKSOURCE_PCLK1)
    case UART_CLOCKSOURCE_PCLK1:
#endif /* UART_CLOCKSOURCE_PCLK1 */
      freq = HAL_RCC_GetPCLK1Freq();
      break;
#endif /* UART_CLOCKSOURCE_D2PCLK1 || UART_CLOCKSOURCE_PCLK1*/
#if defined(UART_CLOCKSOURCE_D2PCLK2) || defined(UART_CLOCKSOURCE_PCLK2)
#if defined(UART_CLOCKSOURCE_D2PCLK2)
    case UART_CLOCKSOURCE_D2PCLK2:
#endif /* UART_CLOCKSOURCE_D2PCLK2*/
#if defined(UART_CLOCKSOURCE_PCLK2)
    case UART_CLOCKSOURCE_PCLK2:
#endif /* UART_CLOCKSOURCE_PCLK2 */
      freq = HAL_RCC_GetPCLK2Freq();
      break;
#endif /* UART_CLOCKSOURCE_D2PCLK2 || UART_CLOCKSOURCE_PCLK2*/
#if defined(UART_CLOCKSOURCE_PCLK7)
    case UART_CLOCKSOURCE_PCLK7:
      freq = HAL_RCC_GetPCLK7Freq();
      break;
#endif /* UART_CLOCKSOURCE_PCLK7 */
#if defined(UART_CLOCKSOURCE_PLL2)
    case UART_CLOCKSOURCE_PLL2:
      HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
      freq = pll2_clocks.PLL2_Q_Frequency;
      break;
    case UART_CLOCKSOURCE_PLL3:
      HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
      freq = pll3_clocks.PLL3_Q_Frequency;
      break;
#endif /* UART_CLOCKSOURCE_PLL2 */
    case UART_CLOCKSOURCE_HSI:
#if defined(__HAL_RCC_GET_HSIKER_DIVIDER)
      freq = (HSI_VALUE / ((__HAL_RCC_GET_HSIKER_DIVIDER() >> RCC_CR_HSIKERDIV_Pos) + 1U));
#else
#if defined(RCC_FLAG_HSIDIV)
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIDIV) != 0U) {
        freq = (uint32_t)(HSI_VALUE >> (__HAL_RCC_GET_HSI_DIVIDER() >> 3U));
      } else
#endif /* RCC_FLAG_HSIDIV */
      {
        freq = (uint32_t) HSI_VALUE;
      }
#endif
      break;
#if defined(UART_CLOCKSOURCE_CSI)
    case UART_CLOCKSOURCE_CSI:
      freq = (uint32_t) CSI_VALUE;
      break;
#endif /* UART_CLOCKSOURCE_CSI */
#if defined(UART_CLOCKSOURCE_SYSCLK)
    case UART_CLOCKSOURCE_SYSCLK:
      freq = HAL_RCC_GetSysClockFreq();
      break;
#endif /* UART_CLOCKSOURCE_SYSCLK */
    case UART_CLOCKSOURCE_LSE:
      freq = (uint32_t) LSE_VALUE;
      break;
    default:
      freq = 0U;
      break;
  }
#endif /* STM32H5 */
#endif /* STM32WB0x || STM32WL3x */
  return freq;
}
#endif /* UART_PRESCALER_DIV1 */

#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

#ifdef __cplusplus
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
