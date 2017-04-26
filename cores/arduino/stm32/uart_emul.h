/**
  ******************************************************************************
  * @file    uart_emul.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    25-April-2017
  * @brief   Header for uart emulation module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_EMUL_H
#define __UART_EMUL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "timer.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  UART1_EMUL_E = 0,
  NB_UART_EMUL_MANAGED
} uart_emul_id_e;

typedef enum {
  NATIVE_UART_E   = 0,
  EMULATED_UART_E = 1,
  NB_UART_OPTION
} uart_option_e;

/* Exported constants --------------------------------------------------------*/
#define UART_RCV_SIZE 128

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void uart_emul_init(uart_emul_id_e uart_id, uint32_t baudRate);
void uart_emul_deinit(uart_emul_id_e uart_id);
int uart_emul_available(uart_emul_id_e uart_id);
int8_t uart_emul_read(uart_emul_id_e uart_id);
size_t uart_emul_write(uart_emul_id_e uart_id, uint8_t data);
int8_t uart_emul_peek(uart_emul_id_e uart_id);
void uart_emul_flush(uart_emul_id_e uart_id);
void uart_emul_attached_handler(stimer_t *obj, void (*irqHandle)(void));

#ifdef __cplusplus
}
#endif

#endif /* __UART_EMUL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
