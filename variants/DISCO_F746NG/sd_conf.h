/**
  ******************************************************************************
  * @file    sd_conf.h
  * @author  fpiSTM
  * @date    2017
  * @brief   This file contains hw config for SD
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SD_CONF_H
#define __SD_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#define SD_DATATIMEOUT           ((uint32_t)100000000)

/*SD-detect signal */
#define SD_DETECT_PIN                        GPIO_PIN_13
#define SD_DETECT_GPIO_PORT                  GPIOC
#define SD_DETECT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                  EXTI15_10_IRQn

/* Definition for BSP SD */
#define SD_INSTANCE                          SDMMC1

#define SD_CLK_ENABLE                        __HAL_RCC_SDMMC1_CLK_ENABLE
#define SD_CLK_DISABLE                       __HAL_RCC_SDMMC1_CLK_DISABLE
#define SD_CLK_EDGE                          SDMMC_CLOCK_EDGE_RISING
#define SD_CLK_BYPASS                        SDMMC_CLOCK_BYPASS_DISABLE
#define SD_CLK_PWR_SAVE                      SDMMC_CLOCK_POWER_SAVE_DISABLE
#define SD_BUS_WIDE_1B                       SDMMC_BUS_WIDE_1B
#define SD_BUS_WIDE_4B                       SDMMC_BUS_WIDE_4B
#define SD_HW_FLOW_CTRL                      SDMMC_HARDWARE_FLOW_CONTROL_DISABLE
#define SD_CLK_DIV                           SDMMC_TRANSFER_CLK_DIV

/* Definition for MSP SD */
#define SD_AF                                GPIO_AF12_SDMMC1


#ifdef __cplusplus
}
#endif

#endif /* __SD_CONF_H */
