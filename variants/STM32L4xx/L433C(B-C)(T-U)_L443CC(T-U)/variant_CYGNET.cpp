/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#if defined(ARDUINO_CYGNET)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PA_0,   //  0 - A0/D0
  PA_1,   //  1 - A1/D1
  PA_2,   //  2 - A2/D2
  PA_3,   //  3 - A3/D3
  PB_1,   //  4 - A4/D4
  PB_8,   //  5 - D5
  PB_9,   //  6 - D6
  PA_8,   //  7 - LED_BUILTIN
  PC_13,  //  8 - USER_BTN
  PB_14,  //  9 - D9
  PB_13,  // 10 - D10
  PB_0,   // 11 - D11
  PB_15,  // 12 - D12
  PB_4,   // 13 - D13
  PA_7,   // 14 - A5
  PA_5,   // 15 - CK
  PB_5,   // 16 - MO
  PA_6,   // 17 - MI
  PA_10,  // 18 - RX
  PA_9,   // 19 - TX
  PH_3,   // 20 - B
  PB_6,   // 21 - SCL
  PB_7,   // 22 - SDA
  PA_13,  // 23 - SWDIO
  PA_14,  // 24 - SWCLK
  PB_10,  // 25 - LPUART1_VCP_RX
  PB_11,  // 26 - LPUART1_VCP_TX
  PH_0,   // 27 - ENABLE_3V3
  PH_1,   // 28 - DISCHARGE_3V3
  PA_15,  // 29 - CHARGE_DETECT
  PA_4,   // 30 - A6/BATTERY_VOLTAGE (STAT)
  PB_3,   // 31 - USB_DETECT
  PA_11,  // 32 - USB_DM
  PA_12,  // 33 - USB_DP
  PC_14,  // 34 - OSC32_IN (LSE)
  PC_15   // 35 - OSC32_OUT (LSE)
};

// Analog (Ax) to digital pin number array
const pin_size_t analogInputPin[] = {
  0,   // PA0, A0
  1,   // PA1, A1
  2,   // PA2, A2
  3,   // PA3, A3
  4,   // PB1, A4
  14,  // PA7, A5
  30   // PA4, A6/BATTERY_VOLTAGE (STAT)
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  /* All pins set to high-Z (floating) initially */
  /* DS11449 Rev 8, Section 3.9.5 - Reset Mode: */
  /* In order to improve the consumption under reset, the I/Os state under
   * and after reset is "analog state" (the I/O schmitt trigger is disabled).
   * In addition, the internal reset pull-up is deactivated when the reset
   * source is internal.
   */

  /* Configure the USB charge detection; leaks ~80uA if not configured. */
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef  GPIO_InitStruct = {};
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    /* PA15 is CHARGE_DETECT */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }

  /* Configure D13 manually, to avoid stray current on D13 */
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef  GPIO_InitStruct = {};
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    /* PB4 is D13 */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }

  /* Configure the 3V3 regulator */
  {
    __HAL_RCC_GPIOH_CLK_ENABLE();
    GPIO_InitTypeDef  GPIO_InitStruct = {};
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

    /* PH0 is ENABLE_3V3 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* PH1 is DISCHARGE_3V3 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* Enable 3V3 regulator and disable discharging */
    HAL_GPIO_WritePin(GPIOH, (GPIO_PIN_0 | GPIO_PIN_1), GPIO_PIN_SET);
  }
}

/**
 * @brief  System Clock Configuration - PLL-based STM32L433 with native USB FS
 *
 * Key features:
 *   - SYSCLK = 80 MHz from MSI (4 MHz, Range 6) via PLL (4MHz x 40/2)
 *   - USB FS (48 MHz) sourced from PLLSAI1 (4MHz x 24/2)
 *   - LSE enabled with medium-low drive for RTC and MSI auto-calibration (MSIPLLEN)
 *   - Voltage Scale 1 required for 80 MHz operation
 *   - FLASH_LATENCY_4 required for HCLK > 64 MHz at VOS1 (RM0394 s.3.3.3)
 *   - MSI PLL-mode (MSIPLLEN) enabled after SYSCLK moves to PLL to avoid MSIRDY stall
 *   - Wake-up clock after STOP: MSI (PLL must be re-locked manually after wake)
 *
 * References:
 *   - RM0394 Rev 6 (STM32L43x/L44x) - s.6.2.3 "MSI clock" (includes MSI PLL-mode)
 *   - RM0394 s.3.3.3 "Read access latency"
 *   - AN2867 Rev 11 - "Oscillator design guide for STM8AF/AL/S, STM32 MCUs and MPUs"
 */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Enable PWR peripheral clock
  *
  * RM0394 s.6.4.18: PWREN (RCC_APB1ENR1 bit 28) resets to 0, so this call
  * is required before accessing any PWR register (e.g.,
  * HAL_PWREx_ControlVoltageScaling below).
  * CubeMX generates this unconditionally for all STM32L4 projects.
  */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* DBGMCU->CR debug bits (DBG_SLEEP, DBG_STOP, DBG_STANDBY) survive NRST
   * and are cleared only on VDD cycle. A prior SWD session can latch them,
   * leaving the debug subsystem clocked in STOP/STANDBY on every subsequent
   * warm reboot (hundreds of uA). Scrub them on every boot.
   */
  CLEAR_BIT(DBGMCU->CR,
            DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY);

  /* Voltage scaling - Scale 1 required for SYSCLK = 80 MHz
   * RM0394 s.5.1.7: VOS2 supports up to 26 MHz only
   */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  *
  * Use MEDIUMLOW (not LOW): RCC_LSEDRIVE_LOW risks marginal LSE startup
  * on units near the crystal ESR tolerance limit and degrades MSI PLL mode
  * (MSIPLLEN) lock quality. ST recommends MEDIUMLOW as the minimum when
  * MSIPLLEN is in use.
  *
  * Backup domain access must be enabled before configuring LSE or selecting
  * the RTC clock source, as those registers (RCC->BDCR) are write-protected
  * after reset and silently ignore writes until the lock is cleared.
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMLOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  *
  * Oscillator configuration summary:
  *   - MSI: MSIRANGE_6 (4 MHz) -- used as PLL input
  *   - PLL: ON  (MSI 4MHz x PLLN=40 / PLLR=2 = 80 MHz)
  *   - SYSCLK: PLLCLK (80 MHz)
  *   - USB clock: PLLSAI1 (48 MHz)
  *   - MSIRDY transient can not stall SysTick because SYSCLK = PLL, not MSI.
  *   - FLASH_LATENCY: 4 (required for 80 MHz / VOS1 per RM0394 s.3.3.3)
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;  /* 4MHz x 40 / 2 = 80 MHz */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  *
  * SYSCLK = PLLCLK (80 MHz). SysTick and HAL_GetTick() are now driven by
  * the PLL output, completely decoupled from MSI. Any subsequent MSIRDY
  * transient (from HAL_RCCEx_EnableMSIPLLMode below) cannot stall SysTick.
  */
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK    | RCC_CLOCKTYPE_PCLK1
                                     | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  /* FLASH_LATENCY_4: required for HCLK > 64 MHz at VOS1 (RM0394 s.3.3.3) */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the Peripheral clocks
  *
  * USB clock: PLLSAI1 (MSI 4 MHz x PLLSAI1N=24 / PLLSAI1Q=2 = 48 MHz).
  * This mirrors the Nucleo L432KC exactly. RCCEx_PLLSAI1_Config() waits
  * for PLLSAI1RDY using HAL_GetTick(). Because SYSCLK is now PLL-based,
  * HAL_GetTick() is immune to MSI transients -- the wait is reliable.
  * PLLSAI1 and the main PLL share the same source (MSI) and M divider (1),
  * which the HAL enforces; both are configured consistently here.
  *
  * HAL_RCCEx_PeriphCLKConfig writes CLK48SEL first (pointing at PLLSAI1
  * before it is running), then enables PLLSAI1 and waits for its RDY flag.
  * During that brief window the USB peripheral has no 48 MHz clock and
  * stays quiescent -- avoiding the race where a live MSI clock is handed
  * to USB before the peripheral is ready to handle the absence of VBUS.
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;  /* 4 x 24 / 2 = 48 MHz */
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /** Enable MSI Auto calibration (MSIPLLEN, RCC_CR[2])
   *
   * RM0394 s.6.2.3 (MSI clock): setting MSIPLLEN causes the MSI hardware
   * to automatically trim itself against LSE as a phase reference,
   * reducing MSI frequency error to < +/-0.25%. LSE must already be
   * stable (LSERDY=1) before the bit is set -- guaranteed here because
   * HAL_RCC_OscConfig() waited for LSERDY before returning.
   *
   * Setting MSIPLLEN causes MSIRDY to deassert transiently while MSI
   * re-synchronises to LSE. HAL_RCCEx_EnableMSIPLLMode() returns
   * immediately (it is a single SET_BIT); no MSIRDY wait is performed
   * inside it. Two conclusions follow:
   *
   *   (1) This call must come AFTER any HAL routine that polls MSIRDY
   *       under a HAL_GetTick() timeout -- if MSIRDY drops inside such
   *       a routine, the routine returns HAL_TIMEOUT and leaves the
   *       clock tree in an undefined state.
   *
   *   (2) If SYSCLK were MSI, a deadlock would be possible: MSIRDY
   *       drops -> SysTick stalls -> HAL_GetTick() freezes -> any
   *       subsequent timeout loop never exits. RM0394 s.6.2 confirms
   *       SysTick is driven by HCLK (= SYSCLK / AHBdiv). Because
   *       SYSCLK is now PLLCLK (80 MHz), SysTick is completely
   *       decoupled from MSI and the transient is harmless.
   *
   * Placement here -- after PeriphCLKConfig -- satisfies both constraints
   * and mirrors the ordering generated by CubeMX for the Nucleo L432KC.
   */
  HAL_RCCEx_EnableMSIPLLMode();

  /** Ensure that MSI is wake-up system clock
  *
  * After STOP mode, the PLL is not automatically re-enabled. MSI is used
  * as the initial wake-up clock; firmware must re-lock the PLL manually
  * if 80 MHz is required after wake. This is the same behaviour as any
  * PLL-based design on STM32L4.
  */
  HAL_RCCEx_WakeUpStopCLKConfig(RCC_STOP_WAKEUPCLOCK_MSI);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_CYGNET */
