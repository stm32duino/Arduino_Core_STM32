/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 *******************************************************************************
 */

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SYSMEM_RESET_VECTOR            0x1FFFC804
#define RESET_TO_BOOTLOADER_MAGIC_CODE 0xDEADBEEF
#define BOOTLOADER_STACK_POINTER       0x20002250

uint32_t dfu_reset_to_bootloader_magic;

// Pin number
const PinName digitalPin[] = {
  //P2 connector Right side (top view)
  PB_9,  //D0
  PB_8,  //D1
  PB_7,  //D2
  PB_6,  //D3
  PB_5,  //D4
  PB_4,  //D5
  PB_3,  //D6
  PD_2,  //D7
  PC_12, //D8
  PC_11, //D9
  PC_10, //D10
  PA_15, //D11
  PA_14, //D12
  PA_13, //D13
#ifdef USB_REMOVED
  PA_12, //D14
  PA_11, //D15
#else
  NC,
  NC,
#endif
  PA_10, //D16
  PA_9,  //D17
  PA_8,  //D18
  PC_9,  //D19
  PC_8,  //D20
  PC_7,  //D21
  PC_6,  //D22
  PB_15, //D23
  PB_14, //D24
  PB_13, //D25
  //P1 connector Left side (top view)
  PC_13, //D26
  PC_14, //D27
  PC_15, //D28
  PF_0,  //D29
  PF_1,  //D30
  PC_0,  //D31
  PC_1,  //D32
  PC_2,  //D33
  PC_3,  //D34
  PA_0,  //D35
  PA_1,  //D36
#ifdef TSC_REMOVED
  PA_2,  //D37
  PA_3,  //D38
#else
  NC,
  NC,
#endif
  PA_4,  //D39
  PA_5,  //D40
#ifdef TSC_REMOVED
  PA_6,  //D41
  PA_7,  //D42
#else
  NC,
  NC,
#endif
  PC_4,  //D43
  PC_5,  //D44
#ifdef TSC_REMOVED
  PB_0,  //D45
  PB_1,  //D46
#else
  NC,
  NC,
#endif
  PB_2,  //D47
  PB_10, //D48
  PB_11, //D49
  PB_12, //D50
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void __initialize_hardware_early(void)
{
  if (dfu_reset_to_bootloader_magic == RESET_TO_BOOTLOADER_MAGIC_CODE) {
    void (*bootloader)(void) = (void (*)(void)) (*((uint32_t *) SYSMEM_RESET_VECTOR));
    dfu_reset_to_bootloader_magic = 0;
    __set_MSP(BOOTLOADER_STACK_POINTER);
    bootloader();
    while (42);
  }
}

void variant_soft_dfu_hook(uint8_t *Buf, uint32_t *Len)
{
  uint32_t i;
  static unsigned char passkey[] = "1EAF";
  static unsigned char passkey_index = 0;
  
  for (i = 0; i < *Len; i++) {
    /* reading buffer for a sequential bytes that form a pass key */
    if (*(Buf+i) == passkey[passkey_index])
      passkey_index++;
    else
      passkey_index = 0;
    /* jump to DFU mode when the pass key found */
    if (passkey_index == 4) {
      dfu_reset_to_bootloader_magic = RESET_TO_BOOTLOADER_MAGIC_CODE;
      NVIC_SystemReset();
    }
  }
}

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

#ifdef __cplusplus
}
#endif
