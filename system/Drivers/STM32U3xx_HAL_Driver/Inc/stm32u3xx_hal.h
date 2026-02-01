/**
  ******************************************************************************
  * @file    stm32u3xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32U3xx_HAL_H
#define __STM32U3xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_conf.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_Exported_Types HAL Exported Types
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
extern __IO uint32_t            uwTick;
extern uint32_t                 uwTickPrio;
extern HAL_TickFreqTypeDef      uwTickFreq;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/**
  * @brief STM32U3xx HAL Driver version number
   */
#define __STM32U3xx_HAL_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32U3xx_HAL_VERSION_SUB1   (0x01U) /*!< [23:16] sub1 version */
#define __STM32U3xx_HAL_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32U3xx_HAL_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32U3xx_HAL_VERSION         ((__STM32U3xx_HAL_VERSION_MAIN << 24U)\
                                         |(__STM32U3xx_HAL_VERSION_SUB1 << 16U)\
                                         |(__STM32U3xx_HAL_VERSION_SUB2 << 8U )\
                                         |(__STM32U3xx_HAL_VERSION_RC))


/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_FPU_Interrupts FPU Interrupts
  * @{
  */
#define SYSCFG_IT_FPU_IOC              SYSCFG_FPUIMR_FPU_IOIE  /*!< Floating Point Unit Invalid operation Interrupt */
#define SYSCFG_IT_FPU_DZC              SYSCFG_FPUIMR_FPU_DZIE  /*!< Floating Point Unit Divide-by-zero Interrupt */
#define SYSCFG_IT_FPU_UFC              SYSCFG_FPUIMR_FPU_UFIE  /*!< Floating Point Unit Underflow Interrupt */
#define SYSCFG_IT_FPU_OFC              SYSCFG_FPUIMR_FPU_OFIE  /*!< Floating Point Unit Overflow Interrupt */
#define SYSCFG_IT_FPU_IDC              SYSCFG_FPUIMR_FPU_IDIE  /*!< Floating Point Unit Input denormal Interrupt */
#define SYSCFG_IT_FPU_IXC              SYSCFG_FPUIMR_FPU_IXIE  /*!< Floating Point Unit Inexact Interrupt */
#define SYSCFG_IT_FPU_ALL              (SYSCFG_IT_FPU_IOC| \
                                        SYSCFG_IT_FPU_DZC| \
                                        SYSCFG_IT_FPU_UFC| \
                                        SYSCFG_IT_FPU_OFC| \
                                        SYSCFG_IT_FPU_IDC| \
                                        SYSCFG_IT_FPU_IXC)  /*!< All */

/**
  * @}
  */

/** @defgroup SYSCFG_Compensation_Cell_Selection Compensation Cell Selection
  * @{
  */
#define SYSCFG_IO_VDD_CELL             SYSCFG_CCCSR_EN1        /*!< Compensation cell for the I/O supplied by VDD */
#define SYSCFG_IO_VDDIO2_CELL          SYSCFG_CCCSR_EN2        /*!< Compensation cell for the I/O supplied by VDDIO2 */
/**
  * @}
  */

/** @defgroup SYSCFG_IO_Compensation_Code_Config IO Compensation Code config
  * @{
  */
#define SYSCFG_IO_CELL_CODE          0U                      /*!< Code from the cell */
#define SYSCFG_IO_REGISTER_CODE      1U                      /*!< Code from the values in the cell code register */
/**
  * @}
  */

/** @defgroup SYSCFG_HAL_EC_IR_MOD SYSCFG IR Modulation
  * @{
  */
#define SYSCFG_IR_MOD_TIM16        0U                      /*!< TIM16 is selected as IR Modulation envelope source */
#define SYSCFG_IR_MOD_USART1       SYSCFG_CFGR1_IR_MOD_0   /*!< USART1 is selected as IR Modulation envelope source */
#define SYSCFG_IR_MOD_UART4        SYSCFG_CFGR1_IR_MOD_1   /*!< UART4 is selected as IR Modulation envelope source */
/**
  * @}
  */

/** @defgroup SYSCFG_HAL_EC_IR_OUTPOL SYSCFG IR Output Polarity
  * @{
  */
#define SYSCFG_IR_OUTPUTPOL_NONINVERTED   0U                     /*!< Output of IR (IROut) non-inverted */
#define SYSCFG_IR_OUTPUTPOL_INVERTED      SYSCFG_CFGR1_IR_POL    /*!< Output of IR (IROut) inverted */
/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE0  ((uint32_t)0x00000000)
                          /*!< Voltage reference scale 0 (VREF_OUT1) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE1  VREFBUF_CSR_VRS_0
                          /*!< Voltage reference scale 1 (VREF_OUT2) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE2  VREFBUF_CSR_VRS_1
                          /*!< Voltage reference scale 2 (VREF_OUT3) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE3  (VREFBUF_CSR_VRS_0 | VREFBUF_CSR_VRS_1)
                          /*!< Voltage reference scale 3 (VREF_OUT4) */

/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_HighImpedance VREFBUF High Impedance
  * @{
  */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE  ((uint32_t)0x00000000) /*!< VREF_plus pin is internally connected to
                                                                           Voltage reference buffer output */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE   VREFBUF_CSR_HIZ        /*!< VREF_plus pin is high impedance */

/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PB6        SYSCFG_CFGR1_PB6_FMP  /*!< Enable Fast-mode Plus on PB6 */
#define SYSCFG_FASTMODEPLUS_PB7        SYSCFG_CFGR1_PB7_FMP  /*!< Enable Fast-mode Plus on PB7 */
#define SYSCFG_FASTMODEPLUS_PB8        SYSCFG_CFGR1_PB8_FMP  /*!< Enable Fast-mode Plus on PB8 */
#define SYSCFG_FASTMODEPLUS_PB9        SYSCFG_CFGR1_PB9_FMP  /*!< Enable Fast-mode Plus on PB9 */
#define SYSCFG_FASTMODEPLUS_ALL        (SYSCFG_FASTMODEPLUS_PB6| \
                                        SYSCFG_FASTMODEPLUS_PB7| \
                                        SYSCFG_FASTMODEPLUS_PB8| \
                                        SYSCFG_FASTMODEPLUS_PB9)  /*!< All */

/**
  * @}
  */

/** @defgroup SYSCFG_Lock_items SYSCFG Lock items
  * @brief SYSCFG items to set lock on
  * @{
  */
#define SYSCFG_MPU_NSEC              SYSCFG_CNSLCKR_LOCKNSMPU
                                          /*!< Non-secure MPU lock (privileged secure or non-secure only) */
#define SYSCFG_VTOR_NSEC             SYSCFG_CNSLCKR_LOCKNSVTOR
                                          /*!< Non-secure VTOR lock (privileged secure or non-secure only) */
#if defined (CPU_IN_SECURE_STATE)
#define SYSCFG_SAU                   (SYSCFG_CSLCKR_LOCKSAU << 16U)
                                          /*!< SAU lock (privileged secure code only) */
#define SYSCFG_MPU_SEC               (SYSCFG_CSLCKR_LOCKSMPU << 16U)
                                          /*!< Secure MPU lock (privileged secure code only) */
#define SYSCFG_VTOR_AIRCR_SEC        (SYSCFG_CSLCKR_LOCKSVTAIRCR << 16U)
                                          /*!< VTOR_S and AIRCR lock (privileged secure code only) */
#define SYSCFG_LOCK_ALL              (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC|SYSCFG_SAU|SYSCFG_MPU_SEC|SYSCFG_VTOR_AIRCR_SEC)
                                          /*!< All */
#else
#define SYSCFG_LOCK_ALL              (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC)
                                          /*!< All (privileged secure or non-secure only) */
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup SYSCFG_Attributes_items SYSCFG Attributes items
  * @brief SYSCFG items to configure secure or non-secure attributes on
  * @{
  */
#define SYSCFG_CLK                     SYSCFG_SECCFGR_SYSCFGSEC   /*!< SYSCFG clock control */
#define SYSCFG_CLASSB                  SYSCFG_SECCFGR_CLASSBSEC   /*!< Class B */
#define SYSCFG_FPU                     SYSCFG_SECCFGR_FPUSEC      /*!< FPU */
#define SYSCFG_ALL                     (SYSCFG_CLK | SYSCFG_CLASSB | SYSCFG_FPU) /*!< All */
/**
  * @}
  */

/** @defgroup SYSCFG_attributes SYSCFG attributes
  * @brief SYSCFG secure or non-secure attributes
  * @{
  */
#define SYSCFG_SEC                     0x00000001U   /*!< Secure attribute      */
#define SYSCFG_NSEC                    0x00000000U   /*!< Non-secure attribute  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode
  */
#if defined(DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM2_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM3_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_FREEZE_TIM4()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM4()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM4_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_FREEZE_TIM6()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM6()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM6_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_FREEZE_TIM7()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM7()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM7_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_WWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_IWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C1_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_FREEZE_I2C2()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C2_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I3C1_STOP)
#define __HAL_DBGMCU_FREEZE_I3C1()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I3C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I3C1()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I3C1_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I3C1_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_RTC_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_RTC_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM2()            SET_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM2()          CLEAR_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#endif /* DBGMCU_APB1FZR2_DBG_LPTIM2_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()              SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()            CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM1_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM15_STOP)
#define __HAL_DBGMCU_FREEZE_TIM15()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM15_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM15()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM15_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM15_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM16_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM17_STOP */

#if defined(DBGMCU_APB2FZR_DBG_I3C2_STOP)
#define __HAL_DBGMCU_FREEZE_I3C2()              SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_I3C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I3C2()            CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_I3C2_STOP)
#endif /* DBGMCU_APB2FZR_DBG_I3C2_STOP */

#if defined(DBGMCU_APB3FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_FREEZE_I2C3()              SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3()            CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_I2C3_STOP)
#endif /* DBGMCU_APB3FZR_DBG_I2C3_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM1_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM3()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM3()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM3_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM4()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM4()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM4_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA0()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA0()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA0_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA1()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA1()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA2()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA2()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA2_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA3()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA3()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA3_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA4()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA4()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA4_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA5()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA5()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA5_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA6()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA6()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA6_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA7()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA7()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA7_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA8()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA8()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA8_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA9()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA9()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA9_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA10()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA10()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA10_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA11()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA11()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA11_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  Floating Point Unit interrupt enable/disable macros
  * @param __INTERRUPT__: This parameter can be a value of @ref SYSCFG_FPU_Interrupts
  */
#define __HAL_SYSCFG_FPU_INTERRUPT_ENABLE(__INTERRUPT__)    do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 SET_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

#define __HAL_SYSCFG_FPU_INTERRUPT_DISABLE(__INTERRUPT__)   do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 CLEAR_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

/** @brief  SYSCFG Break ECC lock.
  *         Enable and lock the connection of Flash ECC double error connection to TIM1/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_ECC_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_ECCL)

/** @brief  SYSCFG Break Cortex-M33 Lockup lock.
  *         Enable and lock the connection of Cortex-M33 LOCKUP (Hardfault) output to TIM1/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()     SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

/** @brief  SYSCFG Break PVD lock.
  *         Enable and lock the PVD connection to Timer1/15/16/17 Break input, as well as the PVDE and PVDLS[2:0] in
  *         the PWR_SVMCR register.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVDL)

/** @brief  SYSCFG Break SRAM2 parity lock.
  *         Enable and lock the SRAM2 parity error signal connection to TIM1/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked by system reset.
  */
#define __HAL_SYSCFG_BREAK_SRAM2PARITY_LOCK()  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPL)

/** @brief  Fast-mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__: This parameter can be a value of :
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB6 Fast-mode Plus driving capability activation on PB6
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB7 Fast-mode Plus driving capability activation on PB7
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB8 Fast-mode Plus driving capability activation on PB8
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB9 Fast-mode Plus driving capability activation on PB9
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    SET_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    CLEAR_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */
#define IS_SYSCFG_IR_MODULATION(__MODULATION__) (((__MODULATION__) == SYSCFG_IR_MOD_TIM16)  || \
                                                 ((__MODULATION__) == SYSCFG_IR_MOD_USART1) || \
                                                 ((__MODULATION__) == SYSCFG_IR_MOD_UART4))

#define IS_SYSCFG_IR_OUTPUTPOL(__OUTPUTPOL__) (((__OUTPUTPOL__) == SYSCFG_IR_OUTPUTPOL_NONINVERTED) || \
                                               ((__OUTPUTPOL__) == SYSCFG_IR_OUTPUTPOL_INVERTED))

#define IS_SYSCFG_IO_COMPENSATION_CODE(__VALUE__) (((__VALUE__) == SYSCFG_IO_CELL_CODE)      || \
                                                   ((__VALUE__) == SYSCFG_IO_REGISTER_CODE))

#define IS_SYSCFG_IO_COMPENSATION_CELL_PMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))
#define IS_SYSCFG_IO_COMPENSATION_CELL_NMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))

#define IS_SYSCFG_FPU_INTERRUPT(__INTERRUPT__) ((((__INTERRUPT__) & SYSCFG_IT_FPU_ALL) != 0x00U) && \
                                                (((__INTERRUPT__) & ~SYSCFG_IT_FPU_ALL) == 0x00U))

#define IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(__SCALE__)  (((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE0) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE1) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE2) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE3))

#define IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(__VALUE__)  (((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE) || \
                                                      ((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE))

#define IS_SYSCFG_VREFBUF_TRIMMING(__VALUE__)  (((__VALUE__) > 0U) && ((__VALUE__) <= VREFBUF_CCR_TRIM))

#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_ALL) != 0x00U) && \
                                         (((__PIN__) & ~SYSCFG_FASTMODEPLUS_ALL) == 0x00U))

#define IS_SYSCFG_COMPENSATION_CELL(__CELL__) (((__CELL__) == SYSCFG_IO_VDD_CELL)  || \
                                               ((__CELL__) == SYSCFG_IO_VDDIO2_CELL))

#if defined (CPU_IN_SECURE_STATE)

#define IS_SYSCFG_ATTRIBUTES(__ATTRIBUTES__) (((__ATTRIBUTES__) == SYSCFG_SEC)  ||\
                                              ((__ATTRIBUTES__) == SYSCFG_NSEC))

#define IS_SYSCFG_ITEMS_ATTRIBUTES(__ITEM__) ((((__ITEM__) & SYSCFG_ALL) != 0x00U) && \
                                              (((__ITEM__) & ~SYSCFG_ALL) == 0x00U))

#endif /* CPU_IN_SECURE_STATE */

#define IS_SYSCFG_SINGLE_ITEMS_ATTRIBUTES(__ITEM__) (((__ITEM__) == (SYSCFG_CLK))    || \
                                                     ((__ITEM__) == (SYSCFG_CLASSB)) || \
                                                     ((__ITEM__) == (SYSCFG_FPU)))

#define IS_SYSCFG_LOCK_ITEMS(__ITEM__) ((((__ITEM__) & SYSCFG_LOCK_ALL) != 0x00U) && \
                                        (((__ITEM__) & ~SYSCFG_LOCK_ALL) == 0x00U))


/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void              HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void              HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void              HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void);
void              HAL_SYSCFG_DisableVREFBUF(void);
void              HAL_SYSCFG_EnableIOAnalogBooster(void);
void              HAL_SYSCFG_DisableIOAnalogBooster(void);
void              HAL_SYSCFG_EnableIOAnalogSwitchVdd(void);
void              HAL_SYSCFG_DisableIOAnalogSwitchVdd(void);
void              HAL_SYSCFG_EnableCompensationCell(uint32_t Selection);
void              HAL_SYSCFG_DisableCompensationCell(uint32_t Selection);
uint32_t          HAL_SYSCFG_GetCompensationCellReadyStatus(uint32_t Selection);
void              HAL_SYSCFG_ConfigCompensationCell(uint32_t Selection,
                                                    uint32_t Code,
                                                    uint32_t NmosValue,
                                                    uint32_t PmosValue);
HAL_StatusTypeDef HAL_SYSCFG_GetCompensationCell(uint32_t Selection,
                                                 uint32_t *pCode,
                                                 uint32_t *pNmosValue,
                                                 uint32_t *pPmosValue);
void              HAL_SYSCFG_ConfigIR(uint32_t Modulation, uint32_t OutputPol);
HAL_StatusTypeDef HAL_SYSCFG_GetConfigIR(uint32_t *pModulation, uint32_t *pOutputPol);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group5
  * @{
  */

/* SYSCFG Lock functions ********************************************/
void              HAL_SYSCFG_Lock(uint32_t Item);
HAL_StatusTypeDef HAL_SYSCFG_GetLock(uint32_t *pItem);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group6
  * @{
  */

/* SYSCFG Attributes functions ********************************************/
#if defined (CPU_IN_SECURE_STATE)
void              HAL_SYSCFG_ConfigAttributes(uint32_t Item, uint32_t Attributes);
#endif /* CPU_IN_SECURE_STATE */
HAL_StatusTypeDef HAL_SYSCFG_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32U3xx_HAL_H */
