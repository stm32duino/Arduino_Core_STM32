/**
  ******************************************************************************
  * @file    core_callback.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    8-September-2017
  * @brief   Provides methods to add callback to call inside the main loop.
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

/*
 * @NOTE
 * This file provides methods to add callback in the main() function loop.
 * If you need to call as often as possible a function to update your system and
 * you want to be sure this function to be called, you can add it to the callback
 * list. Otherwise, your function should be called inside the loop() function of
 * the sketch.
 */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_callback.h"

// List of callback to call
static void (*callbackList[CALLBACK_LIST_SIZE])(void);

/**
  * @brief  Adds a callback pointer
  * @param  func: callback pointer
  * @retval None
  */
void registerCoreCallback(void (*func)(void))
{
  if(func == NULL)
    return;

  for(uint8_t i = 0; i < CALLBACK_LIST_SIZE; i++) {
    if(callbackList[i] == NULL) {
      callbackList[i] = func;
      break;
    }
  }
}

/**
  * @brief  Removes a callback pointer
  * @param  func: callback pointer
  * @retval None
  */
void unregisterCoreCallback(void (*func)(void))
{
  if(func == NULL)
    return;

  for(uint8_t i = 0; i < CALLBACK_LIST_SIZE; i++) {
    if(callbackList[i] == func) {
      callbackList[i] = NULL;
      break;
    }
  }
}

/**
  * @brief  Calls callback of the list. There is no priority. First added first
  *         called. This function must be called only in main() function loop.
  * @param  None
  * @retval None
  */
void CoreCallback(void)
{
  for(uint8_t i = 0; i < CALLBACK_LIST_SIZE; i++) {
    if(callbackList[i] != NULL)
      callbackList[i]();
  }
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
