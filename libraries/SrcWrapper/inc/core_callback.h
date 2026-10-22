/**
  ******************************************************************************
  * @file    core_callback.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    8-September-2017
  * @brief   Header for callback methods.
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
#ifndef __CALLBACK_H
#define __CALLBACK_H
#if defined(CORE_CALLBACK)
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifndef CALLBACK_LIST_SIZE
#define CALLBACK_LIST_SIZE  4
#endif

/* Exported functions ------------------------------------------------------- */
/**
 * @brief Adds a callback function to the list called from the main loop.
 * @param func Callback function pointer to add. Ignored if NULL.
 * @note Up to CALLBACK_LIST_SIZE callbacks can be registered. Extra
 *       registrations are silently dropped when the list is full.
 */
void registerCoreCallback(void (*func)(void));

/**
 * @brief Removes a callback function from the list.
 * @param func Callback function pointer to remove. Ignored if NULL.
 */
void unregisterCoreCallback(void (*func)(void));

/**
 * @brief Calls every registered callback, in the order they were added.
 * @note There is no priority: first added is first called. Must be called
 *       only from the main() loop.
 */
void CoreCallback(void);

#ifdef __cplusplus
}
#endif
#endif // CORE_CALLBACK
#endif /* __CALLBACK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
