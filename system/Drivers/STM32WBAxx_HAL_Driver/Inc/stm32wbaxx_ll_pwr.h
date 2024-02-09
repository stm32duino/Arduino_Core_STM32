/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_LL_PWR_H
#define STM32WBAxx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_SR_CSSF         PWR_SR_CSSF     /*!< Clear Stop and Standby flags */
#define LL_PWR_WUSCR_CWUF1     PWR_WUSCR_CWUF1 /*!< Clear Wakeup flag 1          */
#define LL_PWR_WUSCR_CWUF2     PWR_WUSCR_CWUF2 /*!< Clear Wakeup flag 2          */
#define LL_PWR_WUSCR_CWUF3     PWR_WUSCR_CWUF3 /*!< Clear Wakeup flag 3          */
#define LL_PWR_WUSCR_CWUF4     PWR_WUSCR_CWUF4 /*!< Clear Wakeup flag 4          */
#define LL_PWR_WUSCR_CWUF5     PWR_WUSCR_CWUF5 /*!< Clear Wakeup flag 5          */
#define LL_PWR_WUSCR_CWUF6     PWR_WUSCR_CWUF6 /*!< Clear Wakeup flag 6          */
#define LL_PWR_WUSCR_CWUF7     PWR_WUSCR_CWUF7 /*!< Clear Wakeup flag 7          */
#define LL_PWR_WUSCR_CWUF8     PWR_WUSCR_CWUF8 /*!< Clear Wakeup flag 8          */
#define LL_PWR_WUSCR_CWUF_ALL  PWR_WUSCR_CWUF  /*!< Clear all Wakeup flags       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_VOSRDY    PWR_VOSR_VOSRDY     /*!< Voltage scaling ready flag                               */
#define LL_PWR_FLAG_STOPF     PWR_SR_STOPF        /*!< Stop flag                                                */
#define LL_PWR_FLAG_SBF       PWR_SR_SBF          /*!< Standby flag                                             */
#define LL_PWR_FLAG_ACTVOSRDY PWR_SVMSR_ACTVOSRDY /*!< Currently applied VOS ready flag                         */
#define LL_PWR_FLAG_PVDO      PWR_SVMSR_PVDO      /*!< VDD voltage detector output flag                         */
#define LL_PWR_FLAG_REGS      PWR_SVMSR_REGS      /*!< Regulator selection flag                                 */

#define LL_PWR_WAKEUP_FLAG1   PWR_WUSR_WUF1       /*!< Wakeup flag 1 */
#define LL_PWR_WAKEUP_FLAG2   PWR_WUSR_WUF2       /*!< Wakeup flag 2 */
#define LL_PWR_WAKEUP_FLAG3   PWR_WUSR_WUF3       /*!< Wakeup flag 3 */
#define LL_PWR_WAKEUP_FLAG4   PWR_WUSR_WUF4       /*!< Wakeup flag 4 */
#define LL_PWR_WAKEUP_FLAG5   PWR_WUSR_WUF5       /*!< Wakeup flag 5 */
#define LL_PWR_WAKEUP_FLAG6   PWR_WUSR_WUF6       /*!< Wakeup flag 6 */
#define LL_PWR_WAKEUP_FLAG7   PWR_WUSR_WUF7       /*!< Wakeup flag 7 */
#define LL_PWR_WAKEUP_FLAG8   PWR_WUSR_WUF8       /*!< Wakeup flag 8 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION  Low Power Mode Selection
  * @{
  */
#define LL_PWR_MODE_STOP0    0U                                /*!< Stop 0 mode   */
#define LL_PWR_MODE_STOP1    PWR_CR1_LPMS_0                    /*!< Stop 1 mode   */
#define LL_PWR_MODE_STANDBY  PWR_CR1_LPMS_2                    /*!< Standby mode  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM1_SB_RETENTION PWR SRAM1 Retention in Standby Mode
  * @{
  */
#define LL_PWR_SRAM1_SB_NO_RETENTION          0U               /*!< SRAM1 no retention in Standby mode             */
#define LL_PWR_SRAM1_SB_FULL_RETENTION        PWR_CR1_R1RSB1   /*!< SRAM1 all pages retention in Standby mode      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_SB_RETENTION PWR SRAM2 Retention in Standby Mode
  * @{
  */
#define LL_PWR_SRAM2_SB_NO_RETENTION    0U              /*!< SRAM2 no retention in Standby mode             */
#define LL_PWR_SRAM2_SB_FULL_RETENTION  PWR_CR1_R2RSB1  /*!< SRAM2 all pages retention in Standby mode      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_SB_RETENTION PWR RADIO SRAMs and Sleep Clock Retention in Standby Mode
  * @{
  */
#define LL_PWR_RADIO_SB_NO_RETENTION    0U                /*!< 2.4 GHz RADIO SRAMs and sleep timer content not retained in Standby mode */
#define LL_PWR_RADIO_SB_FULL_RETENTION  PWR_CR1_RADIORSB  /*!< 2.4 GHz RADIO SRAMs and sleep timer content retained in Standby mode     */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM1_STOP_RETENTION PWR SRAM1 Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM1_STOP_NO_RETENTION       0U                   /*!< SRAM1 no retention in Stop mode        */
#define LL_PWR_SRAM1_STOP_FULL_RETENTION  PWR_CR2_SRAM1PDS1   /*!< SRAM1 all pages retention in Stop mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_STOP_RETENTION PWR SRAM2 Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM2_STOP_NO_RETENTION    0U                  /*!< SRAM2 no retention in Stop mode        */
#define LL_PWR_SRAM2_STOP_FULL_RETENTION  PWR_CR2_SRAM2PDS1   /*!< SRAM2 all pages retention in Stop mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ICACHERAM_STOP_RETENTION PWR ICACHE SRAM Retention in Stop Mode
  * @{
  */
#define LL_PWR_ICACHERAM_STOP_NO_RETENTION    0U                  /*!< ICACHE SRAM no retention in Stop mode    */
#define LL_PWR_ICACHERAM_STOP_FULL_RETENTION  PWR_CR2_ICRAMPDS    /*!< ICACHE SRAM full retention in Stop mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_PWM_MODE PWR SMPS PWM mode
  * @{
  */
#define LL_PWR_SMPS_NO_PWM_MODE   0U           /*!< SMPS PWM mode disabled (high-efficiency mode) */
#define LL_PWR_SMPS_PWM_MODE      PWR_CR2_FPWM /*!< SMPS PWM mode enabled (harmonic reduction)    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGULATOR_SUPPLY_SELECTION PWR Regulator Supply Selection
  * @{
  */
#define LL_PWR_LDO_SUPPLY   0U             /*!< LDO regulator supply  */
#define LL_PWR_SMPS_SUPPLY  PWR_CR3_REGSEL /*!< SMPS regulator supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGULATOR_VDDHPA_SUPPLY_SELECTION PWR Regulator REG_VDDHPA input supply selection
  * @{
  */
#define LL_PWR_REG_VDDHPA_VDDRFPA_PIN   0U                    /*!< VDDRFPA pin selected as regulator REG_VDDHPA input supply */
#define LL_PWR_REG_VDDHPA_VDDRFPA_VDD11 PWR_RADIOSCR_REGPASEL /*!< Regulator REG_VDDHPA input supply selection between VDDRFPA and VDD11 dependent on requested regulated output voltage */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_PHY_MODE PWR 2.4 GHz RADIO PHY operating mode
  * @{
  */
#define LL_PWR_RADIO_PHY_SLEEP_MODE   0U                   /*!< 2.4 GHz RADIO Sleep mode   */
#define LL_PWR_RADIO_PHY_STANDBY_MODE PWR_RADIOSCR_PHYMODE /*!< 2.4 GHz RADIO Standby mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_OPERATING_MODE PWR 2.4 GHz RADIO operating mode
  * @{
  */
#define LL_PWR_RADIO_DEEP_SLEEP_MODE   0U                   /*!< 2.4 GHz RADIO Deep Sleep mode */
#define LL_PWR_RADIO_SLEEP_MODE        PWR_RADIOSCR_MODE_0  /*!< 2.4 GHz RADIO Sleep mode      */
#define LL_PWR_RADIO_ACTIVE_MODE       PWR_RADIOSCR_MODE_1  /*!< 2.4 GHz RADIO Active mode     */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE1 PWR_VOSR_VOS   /*!< Voltage scaling range 1 (highest frequency) */
#define LL_PWR_REGU_VOLTAGE_SCALE2 0U             /*!< Voltage scaling range 2 (lowest power)      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVD_LEVEL_SELECTION PWR Power Voltage Detector Level Selection
  * @{
  */
#define LL_PWR_PVDLEVEL_0 0U                                      /*!< Voltage threshold detected by PVD 2.0 V  */
#define LL_PWR_PVDLEVEL_1 PWR_SVMCR_PVDLS_0                       /*!< Voltage threshold detected by PVD 2.2 V  */
#define LL_PWR_PVDLEVEL_2 PWR_SVMCR_PVDLS_1                       /*!< Voltage threshold detected by PVD 2.4 V  */
#define LL_PWR_PVDLEVEL_3 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_1) /*!< Voltage threshold detected by PVD 2.5 V  */
#define LL_PWR_PVDLEVEL_4 PWR_SVMCR_PVDLS_2                       /*!< Voltage threshold detected by PVD 2.6 V  */
#define LL_PWR_PVDLEVEL_5 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.8 V  */
#define LL_PWR_PVDLEVEL_6 (PWR_SVMCR_PVDLS_1 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.9 V  */
#define LL_PWR_PVDLEVEL_7 PWR_SVMCR_PVDLS                         /*!< External input analog voltage on PVD_IN
                                                                       pin, compared to internal VREFINT level  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN PWR Wake Up Pin
  * @{
  */
#define LL_PWR_WAKEUP_PIN1 PWR_WUCR1_WUPEN1 /*!< Wakeup pin 1 enable */
#define LL_PWR_WAKEUP_PIN2 PWR_WUCR1_WUPEN2 /*!< Wakeup pin 2 enable */
#define LL_PWR_WAKEUP_PIN3 PWR_WUCR1_WUPEN3 /*!< Wakeup pin 3 enable */
#define LL_PWR_WAKEUP_PIN4 PWR_WUCR1_WUPEN4 /*!< Wakeup pin 4 enable */
#define LL_PWR_WAKEUP_PIN5 PWR_WUCR1_WUPEN5 /*!< Wakeup pin 5 enable */
#define LL_PWR_WAKEUP_PIN6 PWR_WUCR1_WUPEN6 /*!< Wakeup pin 6 enable */
#define LL_PWR_WAKEUP_PIN7 PWR_WUCR1_WUPEN7 /*!< Wakeup pin 7 enable */
#define LL_PWR_WAKEUP_PIN8 PWR_WUCR1_WUPEN8 /*!< Wakeup pin 8 enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_SELECTION PWR Wakeup Pin Selection
  * @{
  */
#define LL_PWR_WAKEUP_PIN_SELECTION_0 0UL                /*!< Wakeup pin selection 0 */
#define LL_PWR_WAKEUP_PIN_SELECTION_1 PWR_WUCR3_WUSEL1_0 /*!< Wakeup pin selection 1 */
#define LL_PWR_WAKEUP_PIN_SELECTION_2 PWR_WUCR3_WUSEL1_1 /*!< Wakeup pin selection 2 */
#define LL_PWR_WAKEUP_PIN_SELECTION_3 PWR_WUCR3_WUSEL1   /*!< Wakeup pin selection 3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_STATE_RETENTION_ENABLE_SELECTION PWR GPIO State Retention Enable Port Selection
  * @{
  */
#define LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTA  (uint32_t)(&(PWR->IORETENRA)) /*!< GPIO port A */
#define LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTB  (uint32_t)(&(PWR->IORETENRB)) /*!< GPIO port B */
#define LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTC  (uint32_t)(&(PWR->IORETENRC)) /*!< GPIO port C */
#define LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTH  (uint32_t)(&(PWR->IORETENRH)) /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_STATE_RETENTION_STATUS_SELECTION PWR GPIO State Retention Status Port Selection
  * @{
  */
#define LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTA  (uint32_t)(&(PWR->IORETRA)) /*!< GPIO port A */
#define LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTB  (uint32_t)(&(PWR->IORETRB)) /*!< GPIO port B */
#define LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTC  (uint32_t)(&(PWR->IORETRC)) /*!< GPIO port C */
#define LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTH  (uint32_t)(&(PWR->IORETRH)) /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PIN_MASK PWR GPIO Pin Mask
  * @{
  */
#define LL_PWR_GPIO_PIN_0  (0x0001U) /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_PIN_1  (0x0002U) /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_PIN_2  (0x0004U) /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_PIN_3  (0x0008U) /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_PIN_4  (0x0010U) /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_PIN_5  (0x0020U) /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_PIN_6  (0x0040U) /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_PIN_7  (0x0080U) /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_PIN_8  (0x0100U) /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_PIN_9  (0x0200U) /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_PIN_10 (0x0400U) /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_PIN_11 (0x0800U) /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_PIN_12 (0x1000U) /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_PIN_13 (0x2000U) /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_PIN_14 (0x4000U) /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_PIN_15 (0x8000U) /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ITEMS_SECURE_ATTRIBUTE PWR Items Secure Attribute
  * @{
  */
#define LL_PWR_WAKEUP_PIN1_NSEC 0U                  /*!< Wake up pin 1 nsecure mode            */
#define LL_PWR_WAKEUP_PIN1_SEC  PWR_SECCFGR_WUP1SEC /*!< Wake up pin 1 secure mode             */
#define LL_PWR_WAKEUP_PIN2_NSEC 0U                  /*!< Wake up pin 2 nsecure mode            */
#define LL_PWR_WAKEUP_PIN2_SEC  PWR_SECCFGR_WUP2SEC /*!< Wake up pin 2 secure mode             */
#define LL_PWR_WAKEUP_PIN3_NSEC 0U                  /*!< Wake up pin 3 nsecure mode            */
#define LL_PWR_WAKEUP_PIN3_SEC  PWR_SECCFGR_WUP3SEC /*!< Wake up pin 3 secure mode             */
#define LL_PWR_WAKEUP_PIN4_NSEC 0U                  /*!< Wake up pin 4 nsecure mode            */
#define LL_PWR_WAKEUP_PIN4_SEC  PWR_SECCFGR_WUP4SEC /*!< Wake up pin 4 secure mode             */
#define LL_PWR_WAKEUP_PIN5_NSEC 0U                  /*!< Wake up pin 5 nsecure mode            */
#define LL_PWR_WAKEUP_PIN5_SEC  PWR_SECCFGR_WUP5SEC /*!< Wake up pin 5 secure mode             */
#define LL_PWR_WAKEUP_PIN6_NSEC 0U                  /*!< Wake up pin 6 nsecure mode            */
#define LL_PWR_WAKEUP_PIN6_SEC  PWR_SECCFGR_WUP6SEC /*!< Wake up pin 6 secure mode             */
#define LL_PWR_WAKEUP_PIN7_NSEC 0U                  /*!< Wake up pin 7 nsecure mode            */
#define LL_PWR_WAKEUP_PIN7_SEC  PWR_SECCFGR_WUP7SEC /*!< Wake up pin 7 secure mode             */
#define LL_PWR_WAKEUP_PIN8_NSEC 0U                  /*!< Wake up pin 8 nsecure mode            */
#define LL_PWR_WAKEUP_PIN8_SEC  PWR_SECCFGR_WUP8SEC /*!< Wake up pin 8 secure mode             */

#define LL_PWR_LPM_NSEC         0U                  /*!< Low-power modes nsecure mode                  */
#define LL_PWR_LPM_SEC          PWR_SECCFGR_LPMSEC  /*!< Low-power modes secure mode                   */
#define LL_PWR_VDM_NSEC         0U                  /*!< Voltage detection and monitoring nsecure mode */
#define LL_PWR_VDM_SEC          PWR_SECCFGR_VDMSEC  /*!< Voltage detection and monitoring secure mode  */
#define LL_PWR_VB_NSEC          0U                  /*!< Backup domain nsecure mode                    */
#define LL_PWR_VB_SEC           PWR_SECCFGR_VBSEC   /*!< Backup domain secure mode                     */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and Read Registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register.
  * @param  __REG__      Register to be written.
  * @param  __VALUE__    Value to be written in the register.
  * @retval None.
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register.
  * @param  __REG__      Register to be read.
  * @retval Register value.
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_CONFIGURATION PWR Configuration
  * @{
  */

/**
  * @brief  Set system power mode.
  * @rmtoll CR1           LPMS            LL_PWR_SetPowerMode
  * @param  Mode  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t Mode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, Mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll CR1           LPMS            LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @brief  Set the SRAM2 page(s) retention in Standby mode.
  * @rmtoll CR1           R2RSB1          LL_PWR_SetSRAM2SBRetention
  * @param  SRAM2PageRetention  This parameter can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM2SBRetention(uint32_t SRAM2PageRetention)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_R2RSB1, SRAM2PageRetention);
}

/**
  * @brief  Get the SRAM2 page(s) retention in Standby mode.
  * @rmtoll CR1           R2RSB1          LL_PWR_GetSRAM2SBRetention
  * @retval Returned value can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2SBRetention(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_R2RSB1));
}

/**
  * @brief  Set the SRAM1 page(s) retention in Standby mode.
  * @rmtoll CR1           R1RSB1          LL_PWR_SetSRAM1SBRetention
  * @param  SRAM1PageRetention  This parameter can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM1_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM1_SB_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM1SBRetention(uint32_t SRAM1PageRetention)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_R1RSB1, SRAM1PageRetention);
}

/**
  * @brief  Get the SRAM1 page(s) retention in Standby mode.
  * @rmtoll CR1           R1RSB1          LL_PWR_GetSRAM1SBRetention
  * @retval Returned value can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM1_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM1_SB_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1SBRetention(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_R1RSB1));
}

/**
  * @brief  Set the Radio retention in Standby mode.
  * @rmtoll CR1           RADIORSB        LL_PWR_SetRadioSBRetention
  * @param  RadioRetention  This parameter can be one of the following values:
  *                              @arg @ref LL_PWR_RADIO_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_RADIO_SB_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRadioSBRetention(uint32_t RadioRetention)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_RADIORSB, RadioRetention);
}

/**
  * @brief  Get the Radio retention in Standby mode.
  * @rmtoll CR1           RADIORSB        LL_PWR_GetRadioSBRetention
  * @retval Returned value can be one of the following values:
  *                              @arg @ref LL_PWR_RADIO_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_RADIO_SB_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioSBRetention(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_RADIORSB));
}

/**
  * @brief  Enable BOR ultra low power mode.
  * @rmtoll CR1           UPLMEN          LL_PWR_EnableUltraLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Disable BOR ultra low-power mode.
  * @rmtoll CR1           UPLMEN          LL_PWR_DisableUltraLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Check if BOR ultra low power mode is enabled.
  * @rmtoll CR1           UPLMEN          LL_PWR_IsEnabledUltraLowPowerMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUltraLowPowerMode(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_ULPMEN) == (PWR_CR1_ULPMEN)) ? 1UL : 0UL);
}


/**
  * @brief  Set the SRAM1 page(s) retention in Stop mode.
  * @rmtoll CR2           SRAM1PDS1       LL_PWR_SetSRAM1StopRetention
  * @param  SRAM1PageRetention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM1StopRetention(uint32_t SRAM1PageRetention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_SRAM1PDS1, ((~SRAM1PageRetention) & PWR_CR2_SRAM1PDS1));
}

/**
  * @brief  Get the SRAM1 page(s) retention in Stop mode.
  * @rmtoll CR2           SRAM1PDS1       LL_PWR_GetSRAM1StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_SRAM1PDS1))) & PWR_CR2_SRAM1PDS1);
}

/**
  * @brief  Set the SRAM2 page(s) retention in Stop mode.
  * @rmtoll CR2           SRAM2PDS1       LL_PWR_SetSRAM2StopRetention
  * @param  SRAM2PageRetention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM2StopRetention(uint32_t SRAM2PageRetention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_SRAM2PDS1, ((~SRAM2PageRetention) & PWR_CR2_SRAM2PDS1));
}

/**
  * @brief  Get the SRAM2 page(s) retention in Stop mode.
  * @rmtoll CR2           SRAM2PDS1       LL_PWR_GetSRAM2StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_SRAM2PDS1))) & PWR_CR2_SRAM2PDS1);
}

/**
  * @brief  Set the ICACHE SRAM page(s) retention in Stop mode.
  * @rmtoll CR2           ICRAMPDS        LL_PWR_SetICacheRAMStopRetention
#if defined(STM32WBAXX_SI_CUT1_0)
  * @note   On Silicon Cut 1.0, it is mandatory to disable the ICACHE before going into
  *         stop modes otherwise an hard fault may occur when waking up from stop modes.
#endif
  * @param  ICRAMPageRetention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetICacheRAMStopRetention(uint32_t ICRAMPageRetention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_ICRAMPDS,
             ((~ICRAMPageRetention) & PWR_CR2_ICRAMPDS));
}

/**
  * @brief  Get the ICACHE SRAM page(s) retention in Stop mode.
  * @rmtoll CR2           ICRAMPDS        LL_PWR_GetICacheRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetICacheRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_ICRAMPDS))) & PWR_CR2_ICRAMPDS);
}

/**
  * @brief  Enable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2           FLASHFWU        LL_PWR_EnableFlashFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFlashFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Disable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2           FLASHFWU        LL_PWR_DisableFlashFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFlashFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Check if the flash memory fast wakeup from Stop mode (Stop 0, 1) is enabled.
  * @rmtoll CR2           FLASHFWU        LL_PWR_IsEnabledFlashFastWakeUp
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashFastWakeUp(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_FLASHFWU) == (PWR_CR2_FLASHFWU)) ? 1UL : 0UL);
}

#if defined(PWR_CR3_REGSEL)
/**
  * @brief  Set the VCore regulator supply.
  * @rmtoll CR3           REGSEL          LL_PWR_SetRegulatorSupply
  * @param  RegulatorSupply This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_SMPS_SUPPLY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulatorSupply(uint32_t RegulatorSupply)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_REGSEL, RegulatorSupply);
}

/**
  * @brief  Get the VCore regulator supply.
  * @rmtoll CR3           REGSEL          LL_PWR_GetRegulatorSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_SMPS_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorSupply(void)
{
  return (READ_BIT(PWR->CR3, PWR_CR3_REGSEL));
}
#endif /* PWR_CR3_REGSEL */

#if defined(PWR_CR2_FPWM)
/**
  * @brief  Enable the SMPS PWM mode.
  * @rmtoll CR2           FPWM            LL_PWR_EnableSMPSPWMMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSMPSPWMMode(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FPWM);
}

/**
  * @brief  Disable the SMPS PWM mode.
  * @rmtoll CR2           FPWM            LL_PWR_DisableSMPSPWMMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSMPSPWMMode(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FPWM);
}

/**
  * @brief  Check if the SMPS PWM mode is enabled.
  * @rmtoll CR2           FPWM            LL_PWR_IsEnabledSMPSPWMMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSPWMMode(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_FPWM) == (PWR_CR2_FPWM)) ? 1UL : 0UL);
}
#endif /* PWR_CR2_FPWM */

/**
  * @brief  Enable the fast soft start for selected regulator.
  * @rmtoll CR3           FSTEN           LL_PWR_EnableFastSoftStart
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFastSoftStart(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Disable the fast soft start for selected regulator.
  * @rmtoll CR3           FSTEN           LL_PWR_DisableFastSoftStart
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFastSoftStart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Check if the fast soft start for selected regulator is enabled.
  * @rmtoll CR3           FSTEN           LL_PWR_IsEnabledFastSoftStart
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFastSoftStart(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_FSTEN) == (PWR_CR3_FSTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the regulator supply output voltage.
  * @rmtoll VOSR          VOS             LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->VOSR, PWR_VOSR_VOS, VoltageScaling);
}

/**
  * @brief  Get the regulator supply output voltage.
  * @rmtoll VOSR          VOS             LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->VOSR, PWR_VOSR_VOS));
}

/**
  * @brief  Set the Power voltage detector level.
  * @rmtoll SVMCR         PVDLS           LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->SVMCR, PWR_SVMCR_PVDLS, PVDLevel);
}

/**
  * @brief  Get the Power voltage detector level.
  * @rmtoll SVMCR         PVDLS           LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (READ_BIT(PWR->SVMCR, PWR_SVMCR_PVDLS));
}

/**
  * @brief  Enable the power voltage detector.
  * @rmtoll SVMCR         PVDE            LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Disable the power voltage detector.
  * @rmtoll SVMCR         PVDE            LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Check if the power voltage detector is enabled.
  * @rmtoll SVMCR         PVDE            LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_PVDE) == (PWR_SVMCR_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the wake up pin_x.
  * @rmtoll WUCR1         WUPENx          LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WUCR1, WakeUpPin);
}

/**
  * @brief  Disable the wake up pin_x.
  * @rmtoll WUCR1         WUPENx          LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WUCR1, WakeUpPin);
}

/**
  * @brief  Check if the wake up pin_x is enabled.
  * @rmtoll WUCR1         WUPENx          LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WUCR1, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll WUCR2         WUPPx           LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WUCR2, WakeUpPin);
}

/**
  * @brief  Set the wake up pin polarity high for the event detection.
  * @rmtoll WUCR2         WUPPx           LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WUCR2, WakeUpPin);
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll WUCR2         WUPPx           LL_PWR_GetWakeUpPinPolarity
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval State of bit (1 : polarity or 0 : polarity high).
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WUCR2, WakeUpPin) == WakeUpPin) ? 1UL : 0UL);
}

/**
  * @brief  Set the wakeup pin_x selection 0.
  * @rmtoll WUCR3         WUSELx          LL_PWR_SetWakeUpPinSignal0Selection
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal0Selection(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpPin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_0 << (POSITION_VAL(WakeUpPin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 1.
  * @rmtoll WUCR3         WUSELx          LL_PWR_SetWakeUpPinSignal1Selection
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal1Selection(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpPin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_1 << (POSITION_VAL(WakeUpPin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 2.
  * @rmtoll WUCR3         WUSELx          LL_PWR_SetWakeUpPinSignal2Selection
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal2Selection(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpPin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_2 << (POSITION_VAL(WakeUpPin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 3.
  * @rmtoll WUCR3         WUSELx          LL_PWR_SetWakeUpPinSignal3Selection
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal3Selection(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpPin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_3 << (POSITION_VAL(WakeUpPin) * 2U)));
}

/**
  * @brief  Get the wakeup pin_x selection.
  * @rmtoll WUCR3         WUSELx          LL_PWR_GetWakeUpPinSignalSelection
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinSignalSelection(uint32_t WakeUpPin)
{
  return (READ_BIT(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpPin) * 2U))));
}

/**
  * @brief  Enable access to the backup domain.
  * @rmtoll DBPR          DBP             LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable access to the backup domain.
  * @rmtoll DBPR          DBP             LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Check if the access to backup domain is enabled.
  * @rmtoll DBPR          DBP             LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->DBPR, PWR_DBPR_DBP) == (PWR_DBPR_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO retention in Standby mode
  * @rmtoll IORETENRx     ENx             LL_PWR_EnableGPIOStandbyRetention
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTA
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTB
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTC
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTH
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOStandbyRetention(uint32_t GPIOPort, uint32_t GPIOPin)
{
  SET_BIT(*((__IO uint32_t *)GPIOPort), GPIOPin);
}

/**
  * @brief  Disable GPIO retention in Standby mode
  * @rmtoll IORETENRx     ENx             LL_PWR_DisableGPIOStandbyRetention
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTA
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTB
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTC
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTH
  * @param  GPIOPin This parameter can be a combinat+ion of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOStandbyRetention(uint32_t GPIOPort, uint32_t GPIOPin)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIOPort), GPIOPin);
}

/**
  * @brief  Check if GPIO retention is enabled in Standby mode
  * @rmtoll IORETENRx     ENx             LL_PWR_IsEnabledGPIOStandbyRetention
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTA
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTB
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTC
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_ENABLE_PORTH
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOStandbyRetention(uint32_t GPIOPort, uint32_t GPIOPin)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIOPort)), GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Check if GPIO state was retained after Standby mode entry
  * @rmtoll IORETRx       RETx            LL_PWR_IsGPIOStandbyStateRetained
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTA
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTB
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTC
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTH
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsGPIOStandbyStateRetained(uint32_t GPIOPort, uint32_t GPIOPin)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIOPort)), GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Clear GPIO state retention status after Standby mode entry
  * @rmtoll IORETRx       RETx            LL_PWR_ClearGPIOStandbyRetentionStatus
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTA
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTB
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTC
  *         @arg @ref LL_PWR_GPIO_STATE_RETENTION_STATUS_PORTH
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_ClearGPIOStandbyRetentionStatus(uint32_t GPIOPort, uint32_t GPIOPin)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIOPort), GPIOPin);
}

/**
  * @brief  Get currently voltage scaling applied to VCORE.
  * @rmtoll SVMSR         ACTVOS          LL_PWR_GetRegulCurrentVOS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulCurrentVOS(void)
{
  return (READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOS));
}
/**
  * @}
  */


/** @defgroup PWR_LL_EF_RADIO_MANAGEMENT PWR RADIO Management
  * @{
  */

#if defined(PWR_RADIOSCR_REGPABYPEN)
/**
  * @brief  Enable regulator REG_VDDHPA bypass.
  * @rmtoll RADIOSCR      REGPABYPEN      LL_PWR_EnableREGVDDHPABypass
  * @note  This bit shall only be written when the VDDHPA regulator is not used (When REGPASEL = 0)
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableREGVDDHPABypass(void)
{
  SET_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPABYPEN);
}

/**
  * @brief  Disable regulator REG_VDDHPA bypass.
  * @rmtoll RADIOSCR      REGPABYPEN      LL_PWR_DisableREGVDDHPABypass
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableREGVDDHPABypass(void)
{
  CLEAR_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPABYPEN);
}

/**
  * @brief  Check if regulator REG_VDDHPA bypass is enabled.
  * @rmtoll RADIOSCR      REGPABYPEN      LL_PWR_IsEnabledREGVDDHPABypass
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledREGVDDHPABypass(void)
{
  return ((READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPABYPEN) == (PWR_RADIOSCR_REGPABYPEN)) ? 1UL : 0UL);
}
#endif /* PWR_RADIOSCR_REGPABYPEN */

#if defined(PWR_RADIOSCR_REGPASEL)
/**
  * @brief  Set regulator REG_VDDHPA input supply.
  * @rmtoll RADIOSCR      REGPASEL        LL_PWR_SetREGVDDHPAInputSupply
  * @note  This bit shall only be written when the VDDHPA regulator is not used (When REGPASEL = 0)
  *         @arg @ref LL_PWR_REG_VDDHPA_VDDRFPA_PIN
  *         @arg @ref LL_PWR_REG_VDDHPA_VDDRFPA_VDD11
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetREGVDDHPAInputSupply(uint32_t InputSupply)
{
  MODIFY_REG(PWR->RADIOSCR, PWR_RADIOSCR_REGPASEL, InputSupply);
}

/**
  * @brief  Get regulator REG_VDDHPA input supply.
  * @rmtoll RADIOSCR      REGPASEL        LL_PWR_GetREGVDDHPAInputSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REG_VDDHPA_VDDRFPA_PIN
  *         @arg @ref LL_PWR_REG_VDDHPA_VDDRFPA_VDD11
  */
__STATIC_INLINE uint32_t LL_PWR_GetREGVDDHPAInputSupply(void)
{
  return (READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPASEL));
}
#endif /* PWR_RADIOSCR_REGPASEL */

/**
  * @brief  Indicate whether the VDDHPA voltage output is ready when selecting VDDRFPA input.
  * @rmtoll RADIOSCR      REGPARDYVDDRFPA LL_PWR_IsActiveFlag_REGPARDYVDDRFPA
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGPARDYVDDRFPA(void)
{
  return ((READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYVDDRFPA) == (PWR_RADIOSCR_REGPARDYVDDRFPA)) ? 1UL : 0UL);
}

#if defined(PWR_RADIOSCR_REGPARDYV11)
/**
  * @brief  Indicate whether the VDDHPA voltage output is ready when selecting VDD11 input.
  * @rmtoll RADIOSCR      REGPARDYV11     LL_PWR_IsActiveFlag_REGPARDYV11
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGPARDYV11(void)
{
  return ((READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_REGPARDYV11) == (PWR_RADIOSCR_REGPARDYV11)) ? 1UL : 0UL);
}
#endif /* PWR_RADIOSCR_REGPARDYV11 */

/**
  * @brief  Get 2.4 GHz RADIO VDDHPA control word.
  * @rmtoll RADIOSCR      RFVDDHPA        LL_PWR_GetRadioVDDHPAControlWord
  * @retval 4-bit control word.
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioVDDHPAControlWord(void)
{
  return (READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_RFVDDHPA));
}

/**
  * @brief  Indicate whether the 2.4 GHz RADIO encryption function is enabled
  * @rmtoll RADIOSCR      ENCMODE         LL_PWR_IsEnabledRadioEncryption
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledRadioEncryption(void)
{
  return ((READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_ENCMODE) == (PWR_RADIOSCR_ENCMODE)) ? 1UL : 0UL);
}

/**
  * @brief  Get 2.4 GHz RADIO PHY operating mode.
  * @rmtoll RADIOSCR      PHYMODE         LL_PWR_GetRadioPhyMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_PHY_SLEEP_MODE
  *         @arg @ref LL_PWR_RADIO_PHY_STANDBY_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioPhyMode(void)
{
  return (READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_PHYMODE));
}

/**
  * @brief  Get 2.4 GHz RADIO operating mode.
  * @rmtoll RADIOSCR      MODE            LL_PWR_GetRadioMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_DEEP_SLEEP_MODE
  *         @arg @ref LL_PWR_RADIO_SLEEP_MODE
  *         @arg @ref LL_PWR_RADIO_ACTIVE_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioMode(void)
{
  if (READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_MODE_1) != 0UL)
  {
    return LL_PWR_RADIO_ACTIVE_MODE;
  }
  else
  {
    return (READ_BIT(PWR->RADIOSCR, PWR_RADIOSCR_MODE_0));
  }
}
/**
  * @}
  */


/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether the regulator voltage output is above voltage
  *         scaling range or not.
  * @rmtoll VOSR          VOSRDY          LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_VOSRDY) == (PWR_VOSR_VOSRDY)) ? 1UL : 0UL);
}


/**
  * @brief  Indicate whether the system was in standby mode or not.
  * @rmtoll SR            SBF             LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_SBF) == (PWR_SR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in stop mode or not.
  * @rmtoll SR            STOPF           LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_STOPF) == (PWR_SR_STOPF)) ? 1UL : 0UL);
}


#if defined(PWR_SVMSR_REGS)
/**
  * @brief  Indicate whether the regulator supply is LDO or SMPS.
  * @rmtoll SVMSR         REGS            LL_PWR_IsActiveFlag_REGULATOR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGULATOR(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS) == (PWR_SVMSR_REGS)) ? 1UL : 0UL);
}
#endif /* PWR_SVMSR_REGS */

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll SVMSR         PVDO            LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO) == (PWR_SVMSR_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator voltage output is equal to current
  *         used voltage scaling range or not.
  * @rmtoll SVMSR         ACTVOSRDY       LL_PWR_IsActiveFlag_ACTVOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY) == (PWR_SVMSR_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll WUSR          WUF1            LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) == (PWR_WUSR_WUF1)) ? 1UL : 0UL);
}

#if defined(PWR_WUSR_WUF2)
/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll WUSR          WUF2            LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) == (PWR_WUSR_WUF2)) ? 1UL : 0UL);
}
#endif /* PWR_WUSR_WUF2 */

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 3.
  * @rmtoll WUSR          WUF3            LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF3) == (PWR_WUSR_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll WUSR          WUF4            LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) == (PWR_WUSR_WUF4)) ? 1UL : 0UL);
}

#if defined(PWR_WUSR_WUF5)
/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll WUSR          WUF5            LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) == (PWR_WUSR_WUF5)) ? 1UL : 0UL);
}
#endif /* PWR_WUSR_WUF5 */

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll WUSR          WUF6            LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) == (PWR_WUSR_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll WUSR          WUF7            LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) == (PWR_WUSR_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 8.
  * @rmtoll WUSR          WUF8            LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF8) == (PWR_WUSR_WUF8)) ? 1UL : 0UL);
}


/**
  * @brief  Clear stop flag.
  * @rmtoll SR            CSSF            LL_PWR_ClearFlag_STOP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}


/**
  * @brief  Clear standby flag.
  * @rmtoll SR            CSSF            LL_PWR_ClearFlag_SB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}

/**
  * @brief  Clear wake up flag 1.
  * @rmtoll WUSCR         CWUF1           LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1);
}

#if defined(PWR_WUSCR_CWUF2)
/**
  * @brief  Clear wake up flag 2.
  * @rmtoll WUSCR         CWUF2           LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2);
}
#endif /* PWR_WUSCR_CWUF2 */

/**
  * @brief  Clear wake up flag 3.
  * @rmtoll WUSCR         CWUF3           LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF3);
}

/**
  * @brief  Clear wake up flag 4.
  * @rmtoll WUSCR         CWUF4           LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4);
}

#if defined(PWR_WUSCR_CWUF5)
/**
  * @brief  Clear wake up flag 5.
  * @rmtoll WUSCR         CWUF5           LL_PWR_ClearFlag_WU5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5);
}
#endif /* PWR_WUSCR_CWUF5 */

/**
  * @brief  Clear wake up flag 6.
  * @rmtoll WUSCR         CWUF6           LL_PWR_ClearFlag_WU6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6);
}

/**
  * @brief  Clear wake up flag 7.
  * @rmtoll WUSCR         CWUF7           LL_PWR_ClearFlag_WU7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7);
}

/**
  * @brief  Clear wake up flag 8.
  * @rmtoll WUSCR         CWUF8           LL_PWR_ClearFlag_WU8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF8);
}

/**
  * @brief  Clear all wake up flags.
  * @rmtoll WUSCR         CWUF            LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_ATTRIBUTE_MANAGEMENT PWR Attribute Management
  * @{
  */

#if defined(PWR_PRIVCFGR_NSPRIV)
/**
  * @brief  Enable privileged mode for nsecure items.
  * @rmtoll PRIVCFGR      NSPRIV          LL_PWR_EnableNSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableNSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable privileged mode for nsecure items.
  * @rmtoll PRIVCFGR      NSPRIV          LL_PWR_DisableNSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableNSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if privileged mode for nsecure items is enabled.
  * @rmtoll PRIVCFGR      NSPRIV          LL_PWR_IsEnabledNSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledNSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV) == PWR_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
}
#endif /* PWR_PRIVCFGR_NSPRIV */

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable privileged mode for secure items.
  * @rmtoll PRIVCFGR      SPRIV           LL_PWR_EnableSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable privileged mode for secure items.
  * @rmtoll PRIVCFGR      SPRIV           LL_PWR_DisableSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}
#endif /* defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U) */

#if defined(PWR_PRIVCFGR_NSPRIV)
/**
  * @brief  Check if privileged mode for secure items is enabled.
  * @rmtoll PRIVCFGR      SPRIV           LL_PWR_IsEnabledSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV) == PWR_PRIVCFGR_SPRIV) ? 1UL : 0UL);
}
#endif /* PWR_PRIVCFGR_NSPRIV */

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure secure attribute mode.
  * @note   This API can be executed only by CPU in secure mode.
  * @rmtoll SECCFGR       WUP1SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP2SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP3SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP4SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP5SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP6SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP7SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       WUP8SEC         LL_PWR_ConfigSecure\n
  *         SECCFGR       LPMSEC          LL_PWR_ConfigSecure\n
  *         SECCFGR       VDMSEC          LL_PWR_ConfigSecure\n
  *         SECCFGR       VBSEC           LL_PWR_ConfigSecure
  * @param  SecureConfig This parameter can be the full combination
  *         of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1_NSEC or LL_PWR_WAKEUP_PIN1_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN2_NSEC or LL_PWR_WAKEUP_PIN2_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN3_NSEC or LL_PWR_WAKEUP_PIN3_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN4_NSEC or LL_PWR_WAKEUP_PIN4_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN5_NSEC or LL_PWR_WAKEUP_PIN5_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN6_NSEC or LL_PWR_WAKEUP_PIN6_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN7_NSEC or LL_PWR_WAKEUP_PIN7_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN8_NSEC or LL_PWR_WAKEUP_PIN8_SEC
  *         @arg @ref LL_PWR_LPM_NSEC         or LL_PWR_LPM_SEC
  *         @arg @ref LL_PWR_VDM_NSEC         or LL_PWR_VDM_SEC
  *         @arg @ref LL_PWR_VB_NSEC          or LL_PWR_VB_SEC
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_ConfigSecure(uint32_t SecureConfig)
{
  WRITE_REG(PWR->SECCFGR, SecureConfig);
}

/**
  * @brief  Get secure attribute configuration.
  * @note   This API can be executed only by CPU in secure mode.
  * @rmtoll SECCFGR       WUP1SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP2SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP3SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP4SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP5SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP6SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP7SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       WUP8SEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR       LPMSEC          LL_PWR_GetConfigSecure\n
  *         SECCFGR       VDMSEC          LL_PWR_GetConfigSecure\n
  *         SECCFGR       VBSEC           LL_PWR_GetConfigSecure
  * @retval Returned value is the combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1_NSEC or LL_PWR_WAKEUP_PIN1_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN2_NSEC or LL_PWR_WAKEUP_PIN2_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN3_NSEC or LL_PWR_WAKEUP_PIN3_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN4_NSEC or LL_PWR_WAKEUP_PIN4_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN5_NSEC or LL_PWR_WAKEUP_PIN5_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN6_NSEC or LL_PWR_WAKEUP_PIN6_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN7_NSEC or LL_PWR_WAKEUP_PIN7_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN8_NSEC or LL_PWR_WAKEUP_PIN8_SEC
  *         @arg @ref LL_PWR_LPM_NSEC         or LL_PWR_LPM_SEC
  *         @arg @ref LL_PWR_VDM_NSEC         or LL_PWR_VDM_SEC
  *         @arg @ref LL_PWR_VB_NSEC          or LL_PWR_VB_SEC
  */
__STATIC_INLINE uint32_t LL_PWR_GetConfigSecure(void)
{
  return (READ_REG(PWR->SECCFGR));
}
#endif /* defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

#if defined (USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* defined (USE_FULL_LL_DRIVER) */


/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32WBAxx_LL_PWR_H */
