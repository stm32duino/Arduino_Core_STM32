/**
  ******************************************************************************
  * @file    uart.h
  * @author  WI6LABS, fpistm
  * @brief   Header for uart module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32_def.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HAL_UART_MODULE_ENABLED) || defined(HAL_UART_MODULE_ONLY)
#define serial_t void*
#else

#ifndef UART_IRQ_PRIO
/** @brief Default UART IRQ pre-emption priority */
#define UART_IRQ_PRIO       1
#endif
#ifndef UART_IRQ_SUBPRIO
/** @brief Default UART IRQ sub-priority */
#define UART_IRQ_SUBPRIO    0
#endif

/* Exported types ------------------------------------------------------------*/
typedef struct serial_s serial_t;

/**
 * @brief Serial (U(S)ART) object
 */
struct serial_s {
  /*  The 1st 2 members USART_TypeDef *uart
   *  and UART_HandleTypeDef handle should
   *  be kept as the first members of this struct
   *  to have get_serial_obj() function work as expected
   */
  /** U(S)ART peripheral instance */
  USART_TypeDef *uart;
#if defined(USE_HALV2_DRIVER)
  /** HAL UART handle */
  hal_uart_handle_t handle;
#else
  /** HAL UART handle */
  UART_HandleTypeDef handle;
#endif

  /** Called when a byte has been received */
  void (*rx_callback)(serial_t *);
  /** Called when a transmission is completed */
  int (*tx_callback)(serial_t *);
  /** TX pin */
  PinName pin_tx;
  /** RX pin, NC for half-duplex mode */
  PinName pin_rx;
  /** RTS pin, NC if not used */
  PinName pin_rts;
  /** CTS pin, NC if not used */
  PinName pin_cts;
  /** U(S)ART IRQ number */
  IRQn_Type irq;
  /** Index of the peripheral in the internal handlers table */
  uint8_t index;
  /** Last received byte */
  uint8_t recv;
  /** RX ring buffer */
  uint8_t *rx_buff;
  /** TX ring buffer */
  uint8_t *tx_buff;
  /** RX buffer tail index */
  uint16_t rx_tail;
  /** TX buffer head index */
  uint16_t tx_head;
  /** RX buffer head index */
  volatile uint16_t rx_head;
  /** TX buffer tail index */
  volatile uint16_t tx_tail;
  /** Number of bytes of the transfer in progress */
  size_t tx_size;
};

/* Exported constants --------------------------------------------------------*/
#ifndef TX_TIMEOUT
/** @brief Transmission timeout in ms */
#define TX_TIMEOUT  1000
#endif

#if !defined(RCC_USART1CLKSOURCE_HSI)
/* Some series like C0 have 2 derivated clock from HSI: HSIKER (for peripherals)
 * and HSISYS (for system clock). But each have a dedicated prescaler.
 * To avoid changing Arduino implementation,
 * remap RCC_USART1CLKSOURCE_HSI to RCC_USART1CLKSOURCE_HSIKER
 */
#define RCC_USART1CLKSOURCE_HSI RCC_USART1CLKSOURCE_HSIKER
#endif

#if defined(USART2_BASE) && !defined(USART2_IRQn)
#if defined(STM32G0xx) || defined(STM32U0xx)
#if defined(LPUART2_BASE)
#define USART2_IRQn USART2_LPUART2_IRQn
#define USART2_IRQHandler USART2_LPUART2_IRQHandler
#endif
#endif /* STM32G0xx */
#endif

#if defined(USART3_BASE) && !defined(USART3_IRQn)
#if defined(STM32F0xx)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART3_IRQn USART3_8_IRQn
#define USART3_IRQHandler USART3_8_IRQHandler
#elif defined(STM32F030xC)
#define USART3_IRQn USART3_6_IRQn
#define USART3_IRQHandler USART3_6_IRQHandler
#else
#define USART3_IRQn USART3_4_IRQn
#define USART3_IRQHandler USART3_4_IRQHandler
#endif /* STM32F091xC || STM32F098xx */
#elif defined(STM32G0xx) || defined(STM32C0xx)
#if defined(LPUART2_BASE)
#define USART3_IRQn USART3_4_5_6_LPUART1_IRQn
#define USART3_IRQHandler USART3_4_5_6_LPUART1_IRQHandler
#elif defined(LPUART1_BASE)
#define USART3_IRQn USART3_4_LPUART1_IRQn
#define USART3_IRQHandler USART3_4_LPUART1_IRQHandler
#elif defined(USART5_BASE)
#define USART3_IRQn USART3_4_5_6_IRQn
#define USART3_IRQHandler USART3_4_5_6_IRQHandler
#else
#define USART3_IRQn USART3_4_IRQn
#define USART3_IRQHandler USART3_4_IRQHandler
#endif
#elif defined(STM32U0xx)
#define USART3_IRQn USART3_LPUART1_IRQn
#define USART3_IRQHandler USART3_LPUART1_IRQHandler
#endif /* STM32F0xx */
#endif

#if defined(USART4_BASE) && !defined(USART4_IRQn)
#if defined(STM32F0xx)
/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART4_IRQn USART3_8_IRQn
#elif defined(STM32F030xC)
#define USART4_IRQn USART3_6_IRQn
#else
#define USART4_IRQn USART3_4_IRQn
#endif /* STM32F091xC || STM32F098xx */
#elif defined(STM32L0xx)
#define USART4_IRQn USART4_5_IRQn
#elif defined(STM32G0xx) || defined(STM32C0xx)
#if defined(LPUART2_BASE)
#define USART4_IRQn USART3_4_5_6_LPUART1_IRQn
#elif defined(LPUART1_BASE)
#define USART4_IRQn USART3_4_LPUART1_IRQn
#elif defined(USART5_BASE)
#define USART4_IRQn USART3_4_5_6_IRQn
#else
#define USART4_IRQn USART3_4_IRQn
#endif
#elif defined(STM32U0xx)
#if defined(LPUART3_BASE)
#define USART4_IRQn USART4_LPUART3_IRQn
#define USART4_IRQHandler USART4_LPUART3_IRQHandler
#endif /* LPUART3_BASE */
#endif /* STM32G0xx */
#endif

#if defined(USART5_BASE) && !defined(USART5_IRQn)
#if defined(STM32F0xx)
/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART5_IRQn USART3_8_IRQn
#elif defined(STM32F030xC)
#define USART5_IRQn USART3_6_IRQn
#endif /* STM32F091xC || STM32F098xx */
#elif defined(STM32G0xx)
#if defined(LPUART2_BASE)
#define USART5_IRQn USART3_4_5_6_LPUART1_IRQn
#elif defined(USART5_BASE)
#define USART5_IRQn USART3_4_5_6_IRQn
#endif
#elif defined(STM32L0xx)
#define USART5_IRQn USART4_5_IRQn
#endif /* STM32F0xx */
#endif

/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#if defined(USART6_BASE) && !defined(USART6_IRQn)
#if defined (STM32F0xx)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART6_IRQn USART3_8_IRQn
#elif defined(STM32F030xC)
#define USART6_IRQn USART3_6_IRQn
#endif /* STM32F091xC || STM32F098xx */
#elif defined(STM32G0xx)
#if defined(LPUART2_BASE)
#define USART6_IRQn USART3_4_5_6_LPUART1_IRQn
#elif defined(USART5_BASE)
#define USART6_IRQn USART3_4_5_6_IRQn
#endif
#endif /* STM32F0xx */
#endif

#if defined(USART7_BASE) && !defined(USART7_IRQn)
#if defined (STM32F0xx)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART7_IRQn USART3_8_IRQn
#endif /* STM32F091xC || STM32F098xx */
#endif /* STM32F0xx */
#endif

#if defined(USART8_BASE) && !defined(USART8_IRQn)
#if defined (STM32F0xx)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART8_IRQn USART3_8_IRQn
#endif /* STM32F091xC || STM32F098xx */
#endif /* STM32F0xx */
#endif

#if defined(LPUART1_BASE) && !defined(LPUART1_IRQn)
#if defined(STM32G0xx)
#if defined(LPUART2_BASE)
#define LPUART1_IRQn USART3_4_5_6_LPUART1_IRQn
#elif defined(USART3_BASE)
#define LPUART1_IRQn USART3_4_LPUART1_IRQn
#endif
#endif /* STM32G0xx */
#if defined(STM32U0xx)
#define LPUART1_IRQn USART3_LPUART1_IRQn
#endif /* STM32U0xx */
#endif

#if defined(LPUART2_BASE) && !defined(LPUART2_IRQn)
#if defined(STM32G0xx)
#if defined(LPUART2_BASE)
#define LPUART2_IRQn USART2_LPUART2_IRQn
#endif
#endif /* STM32G0xx */
#if defined(STM32U0xx)
#define LPUART2_IRQn USART2_LPUART2_IRQn
#endif /* STM32U0xx */
#endif

#if defined(LPUART3_BASE) && !defined(LPUART3_IRQn)
#if defined(STM32U0xx)
#define LPUART3_IRQn USART4_LPUART3_IRQn
#endif /* STM32U0xx */
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 * @brief Initialize the UART interface.
 *        The U(S)ART peripheral is deduced from the pins set in obj (pin_tx,
 *        pin_rx, pin_rts, pin_cts).
 *        Swapped TX/RX pins are supported when the series allows it.
 *        If pin_rx is NC, the UART is configured in half-duplex mode.
 * @param obj Pointer to serial_t structure.
 * @param baudrate Baud rate.
 * @param databits Word length.
 * @param parity Parity configuration.
 * @param stopbits Number of stop bits.
 * @param rx_invert Invert the RX line.
 * @param tx_invert Invert the TX line.
 * @param data_invert Invert the data bits.
 * @return true on success, false otherwise (obj is NULL, pins do not match the
 *         same U(S)ART peripheral or HAL initialization failed).
 */
#if defined(USE_HALV2_DRIVER)
bool uart_init(serial_t *obj, uint32_t baudrate, hal_uart_word_length_t databits, hal_uart_parity_t parity, hal_uart_stop_bits_t stopbits, bool rx_invert, bool tx_invert, bool data_invert);
#else
bool uart_init(serial_t *obj, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopbits, bool rx_invert, bool tx_invert, bool data_invert);
#endif
/**
 * @brief Deinitialize the UART interface: reset the peripheral and disable its clock.
 * @param obj Pointer to serial_t structure.
 */
void uart_deinit(serial_t *obj);
/**
 * @brief Configure the UART interface for low power operation:
 *        select HSI (LSE on STM32WB0x) as the source clock of the low power
 *        wakeup and enable the wakeup EXTI line when available.
 * @param obj Pointer to serial_t structure.
 */
#if defined(HAL_PWR_MODULE_ENABLED) && (defined(UART_IT_WUF) || defined(LPUART1_BASE))
void uart_config_lowpower(serial_t *obj);
#endif
/**
 * @brief Read the last received byte from the UART and restart the RX interrupt.
 * @param obj Pointer to serial_t structure.
 * @param c Pointer where the received character is stored.
 * @return 0 on success, -1 if obj is NULL or a reception is ongoing.
 */
int uart_getc(serial_t *obj, unsigned char *c);
/**
 * @brief Begin an asynchronous RX transfer (enable interrupt for data
 *        collecting).
 *        Does nothing if obj is NULL or a reception is already ongoing.
 * @param obj Pointer to serial_t structure.
 * @param callback Function called at the end of reception.
 */
void uart_attach_rx_callback(serial_t *obj, void (*callback)(serial_t *));
/**
 * @brief Begin an asynchronous TX transfer (enable interrupt for data sending).
 * @param obj Pointer to serial_t structure.
 * @param callback Function called at the end of transmission.
 * @param size Number of bytes to transmit, starting at the tx_tail index of
 *             the TX buffer.
 */
void uart_attach_tx_callback(serial_t *obj, int (*callback)(serial_t *), size_t size);

/**
 * @brief Determine if the serial peripheral is already in use for TX.
 * @param obj The serial object.
 * @return Non-zero if the TX transaction is ongoing, 0 otherwise.
 */
uint8_t serial_tx_active(serial_t *obj);
/**
 * @brief Determine if the serial peripheral is already in use for RX.
 * @param obj The serial object.
 * @return Non-zero if the RX transaction is ongoing, 0 otherwise.
 */
uint8_t serial_rx_active(serial_t *obj);

/**
 * @brief Enable the transmitter for half-duplex mode (when pin_rx is NC).
 *        No-op in full-duplex mode.
 * @param obj Pointer to serial_t structure.
 */
void uart_enable_tx(serial_t *obj);
/**
 * @brief Enable the receiver for half-duplex mode (when pin_rx is NC).
 *        No-op in full-duplex mode.
 * @param obj Pointer to serial_t structure.
 */
void uart_enable_rx(serial_t *obj);

/**
 * @brief Write data on the UART, used by printf for debug only (syscalls).
 *        The debug UART (DEBUG_UART) is initialized on first use if no Serial
 *        instance already uses it.
 * @param data Bytes to write.
 * @param size Number of bytes to write.
 * @return The number of bytes written, 0 on error or timeout (TX_TIMEOUT).
 */
size_t uart_debug_write(uint8_t *data, uint32_t size);

#if defined(LPUART1_BASE) || defined(LPUART2_BASE)
/**
 * @brief Configure the LPUART stop mode according to the baud rate:
 *        stop mode is enabled for baud rates up to 9600, disabled otherwise.
 *        LPUART clock source must be in the range
 *        [3 x baud rate, 4096 x baud rate].
 * @param huart uart handle structure.
 * @param baudrate Baud rate (HALv2 driver only, otherwise taken from the handle).
 */
#if defined(USE_HALV2_DRIVER)
void uart_init_lpuart(hal_uart_handle_t *huart, uint32_t baudrate);
#else
void uart_init_lpuart(UART_HandleTypeDef *huart);
#endif
#endif

/**
 * @brief Compute the UART clock prescaler: the first one giving a valid baud
 *        rate divider for the current kernel clock (LPUART instances have
 *        their own valid range).
 * @param huart uart handle structure.
 * @param config uart configuration structure (HALv2 driver only).
 * @return The clock prescaler.
 */
#if defined(USE_HALV2_DRIVER)
hal_uart_prescaler_t uart_compute_prescaler(hal_uart_handle_t *huart, hal_uart_config_t *config);
#endif
#if defined(UART_PRESCALER_DIV1)
/**
 * @brief Compute the UART clock prescaler: the first one giving a valid baud
 *        rate divider for the current clock source (LPUART instances have
 *        their own valid range).
 * @param huart uart handle structure.
 * @return The clock prescaler.
 */
uint32_t uart_compute_prescaler(UART_HandleTypeDef *huart);
/**
 * @brief Get the clock source frequency of the UART.
 * @param huart uart handle structure.
 * @return The clock source frequency in Hz.
 */
uint32_t uart_get_clock_source_freq(UART_HandleTypeDef *huart);
#endif
#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */
#ifdef __cplusplus
}
#endif

#endif /* __UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
