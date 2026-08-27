/*
 * Copyright (c) 2026, Seeed Technology Co., Ltd.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if defined(ARDUINO_XIAO_STM32C5)

#include "pins_arduino.h"

const PinName digitalPin[] = {
  PA_0,  // D0 / A0
  PA_1,  // D1 / A1
  PA_2,  // D2 / A2
  PA_3,  // D3 / A3
  PB_7,  // D4 / I2C1_SDA
  PB_6,  // D5 / I2C1_SCL
  PA_9,  // D6 / USART1_TX
  PA_10, // D7 / USART1_RX
  PE_2,  // D8 / SPI3_SCK
  PB_0,  // D9 / SPI3_MISO
  PB_15, // D10 / SPI3_MOSI
  PB_8,  // D11 / FDCAN1_RX
  PB_9,  // D12 / FDCAN1_TX
  PB_5,  // D13 / FDCAN2_RX
  PB_13, // D14 / FDCAN2_TX
  PB_14, // D15 / CAN_STB
  PB_12, // Board LED, active low
  PB_3,  // Onboard IMU / I2C2_SCL
  PB_4,  // Onboard IMU / I2C2_SDA
  PC_13, // Onboard IMU / INT1
  PA_8,  // Onboard IMU heater / TIM1_CH1
  PH_2   // BOOT0 / user button (active low)
};

const pin_size_t analogInputPin[] = {
  D0,
  D1,
  D2,
  D3
};

/* TinyUF2 C5 (d52adcf) reserves the last SRAM word for the double-tap
 * handoff. The matching application linker script excludes this word from
 * the stack/heap RAM region. */
static constexpr uintptr_t TINYUF2_HANDOFF_ADDRESS = 0x2003FFFCUL;
static constexpr uint32_t TINYUF2_ENTER_DFU_MAGIC = 0xF01669EFUL;

extern "C" void CDC_LineCodingChanged(uint32_t bitrate)
{
  if (bitrate == 1200U) {
    *reinterpret_cast<volatile uint32_t *>(TINYUF2_HANDOFF_ADDRESS) = TINYUF2_ENTER_DFU_MAGIC;
    __DSB();
    __ISB();
    NVIC_SystemReset();
    while (true) {
    }
  }
}

extern "C" void SystemClock_Config(void)
{
  if (HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON) != HAL_OK) {
    Error_Handler();
  }

  hal_rcc_psi_config_t psi_config;
  psi_config.psi_source = HAL_RCC_PSI_SRC_HSE;
  psi_config.psi_ref = HAL_RCC_PSI_REF_48MHZ;
  psi_config.psi_out = HAL_RCC_PSI_OUT_144MHZ;
  if (HAL_RCC_PSI_SetConfig(&psi_config) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_RCC_PSIS_Enable() != HAL_OK) {
    Error_Handler();
  }

  hal_rcc_bus_clk_config_t bus_config;
  bus_config.hclk_prescaler = HAL_RCC_HCLK_PRESCALER1;
  bus_config.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER2;
  bus_config.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER2;
  bus_config.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER2;
  if (HAL_RCC_SetBusClockConfig(&bus_config) != HAL_OK) {
    Error_Handler();
  }

  HAL_FLASH_ITF_SetLatency(HAL_FLASH, HAL_FLASH_ITF_LATENCY_4);
  if (HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_PSIS) != HAL_OK) {
    Error_Handler();
  }
  HAL_FLASH_ITF_SetProgrammingDelay(HAL_FLASH, HAL_FLASH_ITF_PROGRAM_DELAY_2);
  if (HAL_RCC_CK48_SetKernelClkSource(HAL_RCC_CK48_CLK_SRC_HSE) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_UpdateCoreClock() != HAL_OK) {
    Error_Handler();
  }
}

void initVariant(void)
{
  /* CAN_STB is active high. Keep the onboard transceiver out of standby. */
  pinMode(D15, OUTPUT);
  digitalWrite(D15, LOW);
}

#endif /* ARDUINO_XIAO_STM32C5 */
