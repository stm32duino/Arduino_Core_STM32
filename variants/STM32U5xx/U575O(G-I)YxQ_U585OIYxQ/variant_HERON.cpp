/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_HERON)
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
  PB_0,   // 11 - A7/D11
  PB_15,  // 12 - D12
  PB_4,   // 13 - D13
  PA_7,   // 14 - A5
  PB_3,   // 15 - CK
  PB_5,   // 16 - MO
  PA_6,   // 17 - A6/MI
  PA_10,  // 18 - RX
  PA_9,   // 19 - TX
  PH_3,   // 20 - B
  PB_6,   // 21 - SCL
  PB_7,   // 22 - SDA
  PA_13,  // 23 - SWDIO
  PA_14,  // 24 - SWCLK
  PA_5,   // 25 - A9/USART3_VCP_RX
  PB_10,  // 26 - USART3_VCP_TX
  PH_0,   // 27 - ENABLE_3V3
  PH_1,   // 28 - DISCHARGE_3V3
  PA_15,  // 29 - CHARGE_DETECT
  PA_4,   // 30 - A8/BATTERY_VOLTAGE (STAT)
  PB_2,   // 31 - A10/USB_DETECT
  PA_11,  // 32 - USB_D_N
  PA_12,  // 33 - USB_D_P
  PC_14,  // 34 - OSC32_IN (LSE)
  PC_15,  // 35 - OSC32_OUT (LSE)
  // PC_0,   // 36 - A11/D30
  // PC_1,   // 37 - A12/D31
  // PC_2,   // 38 - A13/D32
  // PC_3,   // 39 - A14/D33
  // PC_5,   // 40 - A15/D34
  // PC_6,   // 41 - D35
  // PC_7,   // 42 - D36
  // PC_8,   // 43 - D37
  // PC_9,   // 44 - D38
  // PC_10,  // 45 - D39
  // PC_11,  // 46 - D40
  // PC_12,  // 47 - D41
  // PD_0,   // 48 - D45
  // PD_1,   // 49 - D46
  // PD_2,   // 50 - D47
  // PD_4,   // 51 - D48
  // PD_5,   // 52 - D49
  // PD_14,  // 53 - D50
  // PD_15,  // 54 - D51
  // PE_3,   // 55 - D52
  // PE_4,   // 56 - D53
  // PE_5,   // 57 - D54
  // PE_6,   // 58 - D55
  // PE_7,   // 59 - D56
  // PE_8,   // 60 - D57
  // PE_9,   // 61 - D58
  // PE_10,  // 62 - D59
  // PG_9,   // 63 - D60
  // PG_10,  // 64 - D61
  // PG_11,  // 65 - D62
  // PG_12,  // 66 - D63
  // PG_13,  // 67 - D64
  // PG_14   // 68 - D65
};

// Analog (Ax) to digital pin number array
const pin_size_t analogInputPin[] = {
  0,   // PA0, A0
  1,   // PA1, A1
  2,   // PA2, A2
  3,   // PA3, A3
  4,   // PB1, A4
  14,  // PA7, A5
  17,  // PA6, A6/MI
  11,  // PB0, A7/D11
  30   // PA4, A8/BATTERY_VOLTAGE (STAT)
  // 25,  // PA5, A9/USART3_VCP_RX
  // 31,  // PB2, A10/USB_DETECT
  // 36,  // PC0, A11
  // 37,  // PC1, A12
  // 38,  // PC2, A13
  // 39,  // PC3, A14
  // 40   // PC5, A15
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  /* All pins set to high-Z (floating) initially */
  /* DS13737 Rev 10, Section 3.9.4 - Reset Mode: */
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
 * @brief  System Clock Configuration - PLL-based STM32U575 with native USB FS
 *
 * Key features:
 *   - SYSCLK = 80 MHz from MSI (4 MHz, Range 4) via PLL1 (4MHz x 40 / R=2)
 *   - USB FS (48 MHz) sourced from HSI48 via the dedicated ICLK domain
 *   - LSE enabled with medium-low drive for RTC and MSI auto-calibration (MSIPLLEN)
 *   - Voltage Scale 1 required for 80 MHz operation
 *   - EPOD booster required for SYSCLK > 55 MHz at VOS1; enabled
 *     automatically inside HAL_PWREx_ControlVoltageScaling(SCALE1)
 *   - FLASH_LATENCY_2 required for 64 < HCLK <= 96 MHz at VOS1
 *   - CRS enabled; auto-trim HSI48 from USB SOF packets (+/-250 ppm)
 *   - Wake-up clock after STOP: MSI (PLL must be re-locked manually after wake)
 *
 * U5 vs L4 gotcha:
 *   The STM32U5 MSI range table is INVERSE of STM32L4. On U5,
 *   RCC_MSIRANGE_0 = 48 MHz (fastest) and RCC_MSIRANGE_15 = 100 kHz (slowest).
 *   RCC_MSIRANGE_4 = 4 MHz. See stm32u5xx_hal_rcc.h.
 *
 * References:
 *   - RM0456 Rev 7 (STM32U57x/U58x) - Ch. 11 (RCC), Ch. 12 (CRS), Ch. 72 (USB OTG_FS)
 *   - AN2867 Rev 11 - "Oscillator design guide for STM8AF/AL/S, STM32 MCUs and MPUs"
 */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef       RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef       RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit     = {};
  RCC_CRSInitTypeDef       CRS_InitStruct    = {};

  /** Enable PWR peripheral clock
  *
  * RM0456: PWREN (RCC_AHB3ENR bit 2) resets to 0, so this call is required
  * before accessing any PWR register (e.g., HAL_PWREx_ControlVoltageScaling
  * below).
  * CubeMX generates this unconditionally for all STM32U5 projects.
  */
  __HAL_RCC_PWR_CLK_ENABLE();

  /** Clear DBGMCU low-power-mode latch bits
   *
   * ST-Link and IDEs set DBG_STOP and DBG_STANDBY on debugger attach to keep
   * the SWD link alive across low-power mode entry. These bits survive NRST,
   * watchdog, and software reset, and only clear on a true VDD cycle. If
   * left set in the field, the debug subsystem stays clocked in STOP2 and
   * adds hundreds of uA.
   *
   * On STM32U5 only DBG_STOP and DBG_STANDBY exist in DBGMCU->CR; there is
   * no DBG_SLEEP bit on the Cortex-M33 debug architecture.
   */
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY);

  /** Select SMPS as the Vcore regulator
   *
   * The STM32U575OIY6QTR (Q-suffix) exposes the dedicated SMPS pinout, and
   * the Heron V3 board populates the required external components
   * (L3 = 2.2 uH on VLXSMPS, C39/C40 = 2.2 uF on VDD_CORE, VDDSMPS/VDD11
   * tied to VDD_CORE). Switching the Vcore supply from the default LDO to
   * the SMPS regulator reduces Run-mode current draw at 80 MHz; STOP2 floor
   * is unaffected (both regulators converge to the same low-power path).
   * Configure supply before voltage scaling so the VOS1 ramp and the
   * subsequent 80 MHz clock ramp both run on the SMPS.
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK) {
    Error_Handler();
  }

  /* Voltage scaling - Scale 1 required for SYSCLK = 48 MHz
   * RM0456: VOS2..VOS4 cap HCLK below 48 MHz
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
  *   - MSI: MSIRANGE_4 (4 MHz) -- used as PLL1 input
  *   - PLL1: ON  (MSI 4 MHz x PLLN=40 / PLLR=2 = 80 MHz)
  *   - HSI48: ON -- feeds the USB ICLK domain
  *   - LSE: ON -- RTC timing and MSI auto-calibration
  *   - FLASH_LATENCY: 2 (required for 64 < HCLK <= 96 MHz at VOS1)
  */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI48
                                          | RCC_OSCILLATORTYPE_LSE
                                          | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSI48State          = RCC_HSI48_ON;
  RCC_OscInitStruct.LSEState            = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_4;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST       = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM            = 1;
  RCC_OscInitStruct.PLL.PLLN            = 40;
  RCC_OscInitStruct.PLL.PLLP            = 2;
  RCC_OscInitStruct.PLL.PLLQ            = 2;
  RCC_OscInitStruct.PLL.PLLR            = 2;                        /* 4 MHz x 40 / 2 = 80 MHz */
  RCC_OscInitStruct.PLL.PLLRGE          = RCC_PLLVCIRANGE_0;        /* 4-8 MHz VCI range */
  RCC_OscInitStruct.PLL.PLLFRACN        = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  *
  * SYSCLK = PLLCLK (80 MHz), all bus prescalers = /1. FLASH_LATENCY_2 is
  * required for 64 < HCLK <= 96 MHz at VOS1.
  */
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK     | RCC_CLOCKTYPE_PCLK1
                                     | RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_PCLK3
                                     | RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the Peripheral clocks
  *
  * USB clock: HSI48 routed through the U5 ICLK domain
  * (RCC_PERIPHCLK_CLK48 + RCC_ICLK_CLKSOURCE_HSI48). HSI48 is trimmed
  * against USB SOF packets by the CRS block below; required for reliable
  * enumeration across temperature and cable-length variation.
  * ADC/DAC and LPUART1 kernel clocks follow SYSCLK for simplicity.
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC
                                       | RCC_PERIPHCLK_CLK48
                                       | RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.AdcDacClockSelection  = RCC_ADCDACCLKSOURCE_SYSCLK;
  PeriphClkInit.IclkClockSelection    = RCC_ICLK_CLKSOURCE_HSI48;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /** Enable MSI Auto calibration (MSIPLLEN, RCC_CR[2])
   *
   * RM0456 Ch. 11 (RCC): setting MSIPLLEN causes the MSI hardware to
   * automatically trim itself against LSE as a phase reference, reducing
   * MSI frequency error to < +/-0.25%. LSE must already be stable
   * (LSERDY=1) before the bit is set -- guaranteed here because
   * HAL_RCC_OscConfig() waited for LSERDY before returning.
   *
   * Setting MSIPLLEN causes MSIRDY to deassert transiently while MSI
   * re-synchronises to LSE. HAL_RCCEx_EnableMSIPLLMode() is a single
   * SET_BIT; it returns immediately and does not poll MSIRDY under a
   * HAL_GetTick() timeout, so the transient cannot stall any HAL routine
   * here.
   */
  HAL_RCCEx_EnableMSIPLLMode();

  /** Ensure that MSI is wake-up system clock
  *
  * After STOP mode, the PLL is not automatically re-enabled. MSI is used
  * as the initial wake-up clock; firmware must re-lock the PLL manually
  * if 80 MHz is required after wake. This is the same behaviour as the
  * Cygnet and Swan PLL-based designs on STM32L4.
  */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);

  /** Clock Recovery System -- auto-trim HSI48 from USB SOF packets
   *
   * Required for reliable USB enumeration across temperature and
   * cable-length variation. HSI48 alone is +/-1% untrimmed; CRS pulls
   * it to within +/-250 ppm, satisfying USB 2.0 FS.
   * RM0456 Ch. 12 (CRS).
   */
  __HAL_RCC_CRS_CLK_ENABLE();
  CRS_InitStruct.Prescaler             = RCC_CRS_SYNC_DIV1;
  CRS_InitStruct.Source                = RCC_CRS_SYNC_SOURCE_USB;
  CRS_InitStruct.ReloadValue           = RCC_CRS_RELOADVALUE_DEFAULT;
  CRS_InitStruct.ErrorLimitValue       = RCC_CRS_ERRORLIMIT_DEFAULT;
  CRS_InitStruct.HSI48CalibrationValue = RCC_CRS_HSI48CALIBRATION_DEFAULT;
  HAL_RCCEx_CRSConfig(&CRS_InitStruct);
}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_HERON */
