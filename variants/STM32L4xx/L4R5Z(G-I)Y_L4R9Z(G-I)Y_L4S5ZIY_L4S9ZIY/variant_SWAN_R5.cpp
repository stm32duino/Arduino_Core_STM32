/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#if defined(ARDUINO_SWAN_R5)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PD_9,   //  0 - D0
  PD_8,   //  1 - D1
  PF_15,  //  2 - D2
  PE_13,  //  3 - D3
  PE_3,   //  4 - D4
  PE_11,  //  5 - D5
  PE_9,   //  6 - D6
  PF_13,  //  7 - D7
  PF_12,  //  8 - D8
  PD_15,  //  9 - D9
  PA_4,   // 10 - A10/D10
  PA_7,   // 11 - A11/D11
  PA_6,   // 12 - A12/D12
  PA_5,   // 13 - A13/D13
  PB_9,   // 14 - D14
  PE_1,   // 15 - D15
  PD_0,   // 16 - CS
  PA_3,   // 17 - A0
  PA_1,   // 18 - A1
  PC_3,   // 19 - A2
  PC_1,   // 20 - A3
  PC_4,   // 21 - A4
  PC_5,   // 22 - A5
  PB_1,   // 23 - A6
  PD_1,   // 24 - CK
  PC_2,   // 25 - A7
  PB_15,  // 26 - MO
  PB_14,  // 27 - MI
  PA_10,  // 28 - RX
  PG_12,  // 29 - RTS
  PA_9,   // 30 - TX
  PB_4,   // 31 - CTS
  PH_3,   // 32 - B
  PD_5,   // 33 - QEN
  PD_6,   // 34 - RX2
  PA_2,   // 35 - A9/TX2
  PD_4,   // 36 - RTS2
  PD_3,   // 37 - CTS2
  PB_11,  // 38 - RX3
  PB_10,  // 39 - TX3
  PD_2,   // 40 - RTS3
  PB_13,  // 41 - CTS3
  PB_6,   // 42 - SCL
  PF_1,   // 43 - SCL2
  PB_7,   // 44 - SDA
  PF_0,   // 45 - SDA2
  PC_9,   // 46 - SDA3
  PC_0,   // 47 - A14/SCL3
  PC_11,  // 48 - QCS
  PE_10,  // 49 - QCLK
  PE_15,  // 50 - QIO3
  PE_14,  // 51 - QIO2
  PB_0,   // 52 - A15/QIO1
  PE_12,  // 53 - QIO0
  PE_2,   // 54 - LED_BUILTIN
  PC_13,  // 55 - USER_BTN
  PA_13,  // 56 - SWDIO
  PA_14,  // 57 - SWCLK
  PB_3,   // 58 - JTDO
  PA_15,  // 59 - JTDI
  PG_7,   // 60 - LPUART1_VCP_TX (TX0)
  PG_8,   // 61 - LPUART1_VCP_RX (RX0)
  PE_4,   // 62 - ENABLE_3V3
  PE_6,   // 63 - DISCHARGE_3V3
  PA_0,   // 64 - A8/BATTERY_VOLTAGE (STAT)
  PC_6,   // 65 - USB_DETECT
  PA_11,  // 66 - USB_DM
  PA_12,  // 67 - USB_DP
  PC_14,  // 68 - OSC32 IN (LSE)
  PC_15,  // 69 - OSC32 OUT (LSE)
  PG_0,   // 70 - VERSION BIT 0
  PG_1,   // 71 - VERSION BIT 1
  PG_2,   // 72 - VERSION BIT 2
  PG_3,   // 73 - VERSION BIT 3
  PB_2    // 74 - BOOT1 (Do not connect to VDD)
};

// Analog (Ax) pin number array
const pin_size_t analogInputPin[] = {
  17, // PA3, A0
  18, // PA1, A1
  19, // PC3, A2
  20, // PC1, A3
  21, // PC4, A4
  22, // PC5, A5
  23, // PB1, A6
  25, // PC2, A7
  64, // PA0, A8/BATTERY_VOLTAGE (STAT)
  35, // PA2, A9/TX2
  10, // PA4, A10/D10
  11, // PA7, A11/D11
  12, // PA6, A12/D12
  13, // PA5, A13/D13
  47, // PC0, A14/SCL3
  52  // PB0, A15/QIO1
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void initVariant(void)
{
  /* All pins set to high-Z (floating) initially */
  /* DS12023 Rev 5, Section 3.10.5 - Reset mode: */
  /* In order to improve the consumption under reset, the I/Os state under
   * and after reset is "analog state" (the I/O schmitt trigger is disabled).
   * In addition, the internal reset pull-up is deactivated when the reset
   * source is internal.
   */

  /* Configure the 3V3 regulator */
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitTypeDef  GPIO_InitStruct = {};
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

    /* PE4 is ENABLE_3V3 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* PE6 is DISCHARGE_3V3 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* Enable 3V3 regulator and disable discharging */
    HAL_GPIO_WritePin(GPIOE, (GPIO_PIN_4 | GPIO_PIN_6), GPIO_PIN_SET);
  }
}

/**
 * @brief  System Clock Configuration - High-performance STM32L4R5xx with PLL from MSI
 *
 * Key features:
 *   - SYSCLK = 120 MHz from PLL (MSI Range 11 /6 x 30 /2 via PLLR)
 *   - USB FS uses MSI Range 11 as CLK48 source (48 MHz, RM0432 s.6.2.3)
 *   - OSPI clocked from SYSCLK (120 MHz)
 *   - ADC clocked from SYSCLK (120 MHz)
 *   - LSE enabled for RTC timing and MSI auto-calibration (MSIPLLEN)
 *   - Voltage Scale 1 Boost required for 120 MHz (RM0432 s.5.1.8)
 *   - MSI PLL-mode (MSIPLLEN) enabled after peripheral clocks to avoid premature MSIRDY deassertion during PeriphCLKConfig
 *
 * References:
 *   - RM0432 Rev 9 - STM32L4+ Series advanced Arm-based 32-bit MCUs
 *     (www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
 *   - RM0432 s.5.1.8 - Dynamic voltage scaling management: Range 1 boost mode up to 120 MHz
 *   - RM0432 s.6.2.3 - MSI clock: MSI as CLK48 source for USB FS in Range 11; MSI PLL-mode (MSIPLLEN)
 *   - RM0432 s.6.2.5 - PLL: source input range 4-16 MHz
 *   - RM0432 s.6.4.4 - PLL configuration register (RCC_PLLCFGR): PLLM/PLLN/PLLR fields;
 *                      VCO input 2.66-8 MHz; VCO output 64-344 MHz; PLLR drives SYSCLK
 *   - RM0432 Table 12 - Flash latency: 5 wait states at 120 MHz in Range 1 Boost
 *   - RM0432 s.6.4.29 - RCC_BDCR: LSEDRV[1:0] = 01 for medium low drive capability
 *   - AN2867 Rev 23 (Jan 2025) - Guidelines for oscillator design on STM32 MCUs/MPUs
 *     (www.st.com/resource/en/application_note/an2867-guidelines-for-oscillator-design-on-stm8afals-and-stm32-mcusmpus-stmicroelectronics.pdf)
 */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  /** Enable PWR peripheral clock
  *
  * RM0432 s.6.4.19: PWREN (RCC_APB1ENR1 bit 28) resets to 0, so this call
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

  /* Voltage scaling - Scale 1 Boost required for SYSCLK = 120 MHz
   * RM0432 s.5.1.8: "In Range 1 boost mode (R1MODE = 0), the maximum system
   * clock frequency is 120 MHz"
   */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK) {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  *
  * Use MEDIUMLOW (not LOW): RCC_LSEDRIVE_LOW risks marginal LSE startup on units
  * near the crystal ESR tolerance limit and degrades MSI PLL mode (MSIPLLEN) lock
  * quality. ST recommends MEDIUMLOW as the minimum when MSIPLLEN is in use.
  * (RM0432 s.6.4.29; AN2867 Rev 23)
  *
  * Backup domain access must be enabled before configuring LSE, as RCC->BDCR
  * is write-protected after reset and silently ignores writes until the lock
  * is cleared.
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMLOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  *
  * Oscillator configuration summary:
  *   - MSI: MSIRANGE_11 (48 MHz) -- PLL source and USB CLK48 (RM0432 s.6.2.3)
  *   - LSE: ON -- for RTC and MSI auto-calibration (MSIPLLEN)
  *   - PLL: ON (MSI 48 MHz / PLLM=6 x PLLN=30 / PLLR=2 = 120 MHz)
  *     - PLL source: 48 MHz (4-16 MHz range, RM0432 s.6.2.5)
  *     - PLL input (after PLLM): 48/6 = 8 MHz (2.66-8 MHz range, RM0432 s.6.4.4)
  *     - VCO: 8x30 = 240 MHz (64-344 MHz range, RM0432 s.6.4.4)
  *     - SYSCLK from PLLR/2 = 120 MHz (RM0432 s.6.4.4)
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE
                                     | RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  *
  * SYSCLK = PLLCLK (120 MHz). No AHB/APB dividers.
  */
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK    | RCC_CLOCKTYPE_PCLK1
                                     | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  /* FLASH_LATENCY_5: required for 120 MHz at Range 1 Boost (RM0432 Table 12) */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the Peripheral clocks
  *
  * USB clock: MSI Range 11 (48 MHz). RM0432 s.6.2.3: "The MSI clock can be
  * selected as clock source for the USB FS device, SDMMC1 and RNG when the
  * MSI is in Range 11 (48 MHz)."
  * OSPI and ADC clocked from SYSCLK (120 MHz).
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC
                                       | RCC_PERIPHCLK_OSPI
                                       | RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  /** Enable MSI Auto calibration (MSIPLLEN, RCC_CR[2])
  *
  * RM0432 s.6.2.3: setting MSIPLLEN causes the MSI hardware to automatically
  * trim itself against LSE as a phase reference. LSE must already be stable
  * (LSERDY=1) before the bit is set -- guaranteed here because
  * HAL_RCC_OscConfig() waited for LSERDY before returning.
  *
  * This call must come AFTER HAL_RCCEx_PeriphCLKConfig() -- setting MSIPLLEN
  * causes MSIRDY to deassert transiently while MSI re-synchronises to LSE.
  * Because SYSCLK is PLLCLK (120 MHz), SysTick is decoupled from MSI and
  * HAL_GetTick() remains reliable; the concern is HAL routines that check
  * MSIRDY as a readiness flag, all of which must complete before this call.
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

#ifdef __cplusplus
}
#endif
#endif /* ARDUINO_SWAN_R5* */
