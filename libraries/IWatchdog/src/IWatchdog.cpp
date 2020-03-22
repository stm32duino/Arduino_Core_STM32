/*
  Copyright (c) 2018 Frederic Pillon <frederic.pillon@st.com> for
  STMicroelectronics. All right reserved.
  Copyright (c) 2018 Venelin Efremov <ghent360@iqury.us>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "IWatchdog.h"
#include "stm32yyxx_ll_iwdg.h"
#include "stm32yyxx_ll_rcc.h"

// Initialize static variable
bool IWatchdogClass::_enabled = false;

/**
  * @brief  Enable IWDG, must be called once
  * @param  timeout: value in microseconds
  * @param  window: optional value in microseconds
  *         Default: IWDG_TIMEOUT_MAX
  * @retval None
  */
void IWatchdogClass::begin(uint32_t timeout, uint32_t window)
{
  if (!IS_IWDG_TIMEOUT(timeout)) {
    return;
  }

  // Enable the peripheral clock IWDG
#ifdef STM32WBxx
  LL_RCC_LSI1_Enable();
  while (LL_RCC_LSI1_IsReady() != 1) {
  }
#else
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1) {
  }
#endif
  // Enable the IWDG by writing 0x0000 CCCC in the IWDG_KR register
  LL_IWDG_Enable(IWDG);
  _enabled = true;

  set(timeout, window);
}

/**
  * @brief  Set the timeout and window values
  * @param  timeout: value in microseconds
  * @param  window: optional value in microseconds
  *         Default: IWDG_TIMEOUT_MAX
  * @retval None
  */
void IWatchdogClass::set(uint32_t timeout, uint32_t window)
{
  if ((isEnabled()) && (!IS_IWDG_TIMEOUT(timeout))) {
    return;
  }

  // Compute the prescaler value
  uint16_t div = 0;
  uint8_t prescaler = 0;
  uint32_t reload = 0;

  // Convert timeout to seconds
  float t_sec = (float)timeout / 1000000 * LSI_VALUE;

  do {
    div = 4 << prescaler;
    prescaler++;
  } while ((t_sec / div) > IWDG_RLR_RL);

  // 'prescaler' value is one of the LL_IWDG_PRESCALER_XX define
  if (--prescaler > LL_IWDG_PRESCALER_256) {
    return;
  }
  reload = (uint32_t)(t_sec / div) - 1;

  // Enable register access by writing 0x0000 5555 in the IWDG_KR register
  LL_IWDG_EnableWriteAccess(IWDG);
  // Write the IWDG prescaler by programming IWDG_PR from 0 to 7
  // LL_IWDG_PRESCALER_4 (0) is lowest divider
  LL_IWDG_SetPrescaler(IWDG, (uint32_t)prescaler);
  // Write the reload register (IWDG_RLR)
  LL_IWDG_SetReloadCounter(IWDG, reload);

#ifdef IWDG_WINR_WIN
  if ((window != IWDG_TIMEOUT_MAX) &&
      (LL_IWDG_GetWindow(IWDG) != IWDG_WINR_WIN)) {
    if (window >= timeout) {
      // Reset window value
      reload = IWDG_WINR_WIN;
    } else {
      reload = (uint32_t)(((float)window / 1000000 * LSI_VALUE) / div) - 1;
    }
    LL_IWDG_SetWindow(IWDG, reload);
  }
#else
  UNUSED(window);
#endif

  // Wait for the registers to be updated (IWDG_SR = 0x0000 0000)
  while (LL_IWDG_IsReady(IWDG) != 1) {
  }

  // Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA)
  LL_IWDG_ReloadCounter(IWDG);
}

/**
  * @brief  Get the current timeout and window values
  * @param  timeout: pointer to the get the value in microseconds
  * @param  window: optional pointer to the get the value in microseconds
  * @retval None
  */
void IWatchdogClass::get(uint32_t *timeout, uint32_t *window)
{
  if (timeout != NULL) {
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    float base = (1000000.0 / LSI_VALUE);

    while (LL_IWDG_IsActiveFlag_RVU(IWDG));
    reload = LL_IWDG_GetReloadCounter(IWDG);

    while (LL_IWDG_IsActiveFlag_PVU(IWDG));
    prescaler = LL_IWDG_GetPrescaler(IWDG);

    // Timeout given in microseconds
    *timeout = (uint32_t)((4 << prescaler) * (reload + 1) * base);
#ifdef IWDG_WINR_WIN
    if (window != NULL) {
      while (LL_IWDG_IsActiveFlag_WVU(IWDG));
      uint32_t win = LL_IWDG_GetWindow(IWDG);
      *window = (uint32_t)((4 << prescaler) * (win + 1) * base);
    }
#else
    UNUSED(window);
#endif
  }
}

/**
  * @brief  Reload the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA)
  * @retval None
  */
void IWatchdogClass::reload(void)
{
  if (isEnabled()) {
    LL_IWDG_ReloadCounter(IWDG);
  }
}

/**
  * @brief  Check if the system has resumed from IWDG reset
  * @param  clear: if true clear IWDG reset flag. Default false
  * @retval return reset flag status
  */
bool IWatchdogClass::isReset(bool clear)
{
#ifdef IWDG1
  bool status = LL_RCC_IsActiveFlag_IWDG1RST();
#else
  bool status = LL_RCC_IsActiveFlag_IWDGRST();
#endif
  if (status && clear) {
    clearReset();
  }
  return status;
}

/**
  * @brief  Clear IWDG reset flag
  * @retval None
  */
void IWatchdogClass::clearReset(void)
{
  LL_RCC_ClearResetFlags();
}

// Preinstantiate Object
IWatchdogClass IWatchdog = IWatchdogClass();
