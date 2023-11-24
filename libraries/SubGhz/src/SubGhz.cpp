/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include <Arduino.h>
#include "SubGhz.h"

SubGhzClass SubGhz;

extern "C" void SUBGHZ_Radio_IRQHandler(void)
{
  SubGhz.handleIrq();
}

constexpr SPISettings SubGhzClass::spi_settings;

void SubGhzClass::handleIrq()
{
  if (callback) {
    callback();
  }
}

void SubGhzClass::attachInterrupt(callback_function_t callback)
{
  this->callback = callback;
  HAL_NVIC_ClearPendingIRQ(SUBGHZ_Radio_IRQn);
  enableInterrupt();
}

void SubGhzClass::detachInterrupt()
{
  disableInterrupt();
  this->callback = nullptr;
}

bool SubGhzClass::hasInterrupt()
{
  return (bool)this->callback;
}

void SubGhzClass::enableInterrupt()
{
  HAL_NVIC_EnableIRQ(SUBGHZ_Radio_IRQn);
}

void SubGhzClass::disableInterrupt()
{
  HAL_NVIC_DisableIRQ(SUBGHZ_Radio_IRQn);
}

void SubGhzClass::clearPendingInterrupt()
{
  HAL_NVIC_ClearPendingIRQ(SUBGHZ_Radio_IRQn);
}

bool SubGhzClass::isInterruptPending()
{
  return HAL_NVIC_GetPendingIRQ(SUBGHZ_Radio_IRQn);
}

void SubGhzClass::setNssActive(bool value)
{
  if (value) {
    LL_PWR_SelectSUBGHZSPI_NSS();
  } else {
    LL_PWR_UnselectSUBGHZSPI_NSS();
  }
}

bool SubGhzClass::isNssActive()
{
  return LL_PWR_IsSUBGHZSPI_NSS_Selected();
}

void SubGhzClass::setResetActive(bool value)
{
  if (value) {
    LL_RCC_RF_EnableReset();
  } else {
    LL_RCC_RF_DisableReset();
  }
}

bool SubGhzClass::isResetActive()
{
  return LL_RCC_RF_IsEnabledReset();
}

bool SubGhzClass::isBusy()
{
  return (LL_PWR_IsActiveFlag_RFBUSYS());
}
