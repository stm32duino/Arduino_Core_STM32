/**
  ******************************************************************************
  * @file    stm32u3xx_ll_pwr.h
  * @author  GPM Application Team
  * @brief   Header file of PWR LL module.
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
#ifndef STM32U3xx_LL_PWR_H
#define STM32U3xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx.h"

/** @addtogroup STM32U3xx_LL_Driver
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
#define LL_PWR_SR_CSSF                 PWR_SR_CSSF                   /*!< Clear Stop and Standby flags */
#define LL_PWR_WUSCR_CWUF1             PWR_WUSCR_CWUF1               /*!< Clear Wakeup flag 1          */
#define LL_PWR_WUSCR_CWUF2             PWR_WUSCR_CWUF2               /*!< Clear Wakeup flag 2          */
#define LL_PWR_WUSCR_CWUF3             PWR_WUSCR_CWUF3               /*!< Clear Wakeup flag 3          */
#define LL_PWR_WUSCR_CWUF4             PWR_WUSCR_CWUF4               /*!< Clear Wakeup flag 4          */
#define LL_PWR_WUSCR_CWUF5             PWR_WUSCR_CWUF5               /*!< Clear Wakeup flag 5          */
#define LL_PWR_WUSCR_CWUF6             PWR_WUSCR_CWUF6               /*!< Clear Wakeup flag 6          */
#define LL_PWR_WUSCR_CWUF7             PWR_WUSCR_CWUF7               /*!< Clear Wakeup flag 7          */
#define LL_PWR_WUSCR_CWUF8             PWR_WUSCR_CWUF8               /*!< Clear Wakeup flag 8          */
#define LL_PWR_WUSCR_CWUF9             PWR_WUSCR_CWUF9               /*!< Clear Wakeup flag 9          */
#define LL_PWR_WUSCR_CWUF10            PWR_WUSCR_CWUF10              /*!< Clear Wakeup flag 10         */
#define LL_PWR_WUSCR_CWUF_ALL         (PWR_WUSCR_CWUF1 | PWR_WUSCR_CWUF2 | PWR_WUSCR_CWUF3 | PWR_WUSCR_CWUF4 |\
                                       PWR_WUSCR_CWUF5 | PWR_WUSCR_CWUF6 | PWR_WUSCR_CWUF7 | PWR_WUSCR_CWUF8 |\
                                       PWR_WUSCR_CWUF9 | PWR_WUSCR_CWUF10)
/*!< Clear all Wakeup flags       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_STOPF              PWR_SR_STOPF                  /*!< Stop flag                                   */
#define LL_PWR_FLAG_SBF                PWR_SR_SBF                    /*!< Standby flag                                */
#define LL_PWR_FLAG_R1RDY              PWR_VOSR_R1RDY                /*!< Voltage range 1 selection ready flag        */
#define LL_PWR_FLAG_R2RDY              PWR_VOSR_R2RDY                /*!< Voltage range 2 selection ready flag        */
#define LL_PWR_FLAG_BOOSTRDY           PWR_VOSR_BOOSTRDY             /*!< EPOD booster ready flag                     */
#define LL_PWR_FLAG_PVDO               PWR_SVMSR_PVDO                /*!< VDD voltage detector output flag            */
#define LL_PWR_FLAG_REGS               PWR_SVMSR_REGS                /*!< Regulator selection flag                    */
#define LL_PWR_FLAG_VDDA1RDY           PWR_SVMSR_VDDA1RDY            /*!< VDDA ready versus 1.6V voltage monitor flag */
#define LL_PWR_FLAG_VDDA2RDY           PWR_SVMSR_VDDA2RDY            /*!< VDDA ready versus 1.8V voltage monitor flag */
#if defined(PWR_SVMCR_IO2VMEN)
#define LL_PWR_FLAG_VDDIO2RDY          PWR_SVMSR_VDDIO2RDY           /*!< VDDIO2 ready voltage monitor flag           */
#endif /* PWR_SVMCR_IO2VMEN */
#define LL_PWR_FLAG_VDDUSBRDY          PWR_SVMSR_VDDUSBRDY           /*!< VDDUSB ready voltage monitor flag           */

#define LL_PWR_WAKEUP_FLAG1            PWR_WUSR_WUF1                 /*!< Wakeup flag 1  */
#define LL_PWR_WAKEUP_FLAG2            PWR_WUSR_WUF2                 /*!< Wakeup flag 2  */
#define LL_PWR_WAKEUP_FLAG3            PWR_WUSR_WUF3                 /*!< Wakeup flag 3  */
#define LL_PWR_WAKEUP_FLAG4            PWR_WUSR_WUF4                 /*!< Wakeup flag 4  */
#define LL_PWR_WAKEUP_FLAG5            PWR_WUSR_WUF5                 /*!< Wakeup flag 5  */
#define LL_PWR_WAKEUP_FLAG6            PWR_WUSR_WUF6                 /*!< Wakeup flag 6  */
#define LL_PWR_WAKEUP_FLAG7            PWR_WUSR_WUF7                 /*!< Wakeup flag 7  */
#define LL_PWR_WAKEUP_FLAG8            PWR_WUSR_WUF8                 /*!< Wakeup flag 8  */
#define LL_PWR_WAKEUP_FLAG9            PWR_WUSR_WUF9                 /*!< Wakeup flag 9  */
#define LL_PWR_WAKEUP_FLAG10           PWR_WUSR_WUF10                /*!< Wakeup flag 10 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_LINE PWR Wake Up Line
  * @{
  */
#define LL_PWR_WAKEUP_LINE1            PWR_WUCR1_WUPEN1                        /*!< Wakeup line 1 enable  */
#define LL_PWR_WAKEUP_LINE2            PWR_WUCR1_WUPEN2                        /*!< Wakeup line 2 enable  */
#define LL_PWR_WAKEUP_LINE3            PWR_WUCR1_WUPEN3                        /*!< Wakeup line 3 enable  */
#define LL_PWR_WAKEUP_LINE4            PWR_WUCR1_WUPEN4                        /*!< Wakeup line 4 enable  */
#define LL_PWR_WAKEUP_LINE5            PWR_WUCR1_WUPEN5                        /*!< Wakeup line 5 enable  */
#define LL_PWR_WAKEUP_LINE6            PWR_WUCR1_WUPEN6                        /*!< Wakeup line 6 enable  */
#define LL_PWR_WAKEUP_LINE7            PWR_WUCR1_WUPEN7                        /*!< Wakeup line 7 enable  */
#define LL_PWR_WAKEUP_LINE8            PWR_WUCR1_WUPEN8                        /*!< Wakeup line 8 enable  */
#define LL_PWR_WAKEUP_LINE9            PWR_WUCR1_WUPEN9                        /*!< Wakeup line 9 enable  */
#define LL_PWR_WAKEUP_LINE10           PWR_WUCR1_WUPEN10                       /*!< Wakeup line 10 enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_LINE_SELECTION PWR Wakeup line Selection
  * @{
  */
#define LL_PWR_WAKEUP_LINE_SELECTION_0  (0UL)                                  /*!< Wakeup line selection 0 */
#define LL_PWR_WAKEUP_LINE_SELECTION_1  PWR_WUCR3_WUSEL1_0                     /*!< Wakeup line selection 1 */
#define LL_PWR_WAKEUP_LINE_SELECTION_2  PWR_WUCR3_WUSEL1_1                     /*!< Wakeup line selection 2 */
#define LL_PWR_WAKEUP_LINE_SELECTION_3  PWR_WUCR3_WUSEL1                       /*!< Wakeup line selection 3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION Low Power Mode Selection
  * @{
  */
#define LL_PWR_MODE_STOP0              (0U)                                    /*!< Stop 0 mode   */
#define LL_PWR_MODE_STOP1              PWR_CR1_LPMS_0                          /*!< Stop 1 mode   */
#define LL_PWR_MODE_STOP2              PWR_CR1_LPMS_1                          /*!< Stop 2 mode   */
#define LL_PWR_MODE_STOP3              (PWR_CR1_LPMS_0 | PWR_CR1_LPMS_1)       /*!< Stop 3 mode   */
#define LL_PWR_MODE_STANDBY            PWR_CR1_LPMS_2                          /*!< Standby mode  */
#define LL_PWR_MODE_SHUTDOWN           (PWR_CR1_LPMS_2 | PWR_CR1_LPMS_1)       /*!< Shutdown mode */
/**
  * @}
  */

/** @defgroup PWR_LL_RAM_PowerDown PWR SRAM Power Down
  * @{
  */
#define LL_PWR_SRAM1_POWERDOWN         PWR_CR1_SRAM1PD                         /*!< SRAM1 power down */
#define LL_PWR_SRAM2_POWERDOWN         PWR_CR1_SRAM2PD                         /*!< SRAM2 power down */
#if defined(RAMCFG_SRAM3)
#define LL_PWR_SRAM3_POWERDOWN         PWR_CR1_SRAM3PD                         /*!< SRAM3 power down */
#define LL_PWR_SRAM4_POWERDOWN         PWR_CR1_SRAM4PD                         /*!< SRAM4 power down */
#endif /* RAMCFG_SRAM3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_SB_CONTENTS_RETENTION PWR SRAM2 Content Retention in Standby Mode
  * @{
  */
#define LL_PWR_SRAM2_SB_NO_RETENTION     (0U)          /*!< SRAM2 no retention in Standby mode     */
#define LL_PWR_SRAM2_SB_PAGE1_RETENTION  PWR_CR1_RRSB1 /*!< SRAM2 page 1 retention in Standby mode */
#define LL_PWR_SRAM2_SB_PAGE2_RETENTION  PWR_CR1_RRSB2 /*!< SRAM2 page 2 retention in Standby mode */
#define LL_PWR_SRAM2_SB_PAGE3_RETENTION  PWR_CR1_RRSB3 /*!< SRAM2 page 3 retention in Standby mode */
#define LL_PWR_SRAM2_SB_FULL_RETENTION   (PWR_CR1_RRSB1 | PWR_CR1_RRSB2 | PWR_CR1_RRSB3)
/*!< SRAM2 all pages retention in Standby mode      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM1_STOP_CONTENTS_RETENTION PWR SRAM1 Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM1_STOP_NO_RETENTION     (0U)              /*!< SRAM1 no retention in Stop modes (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM1_STOP_PAGE1_RETENTION  PWR_CR2_SRAM1PDS1 /*!< SRAM1 page 1 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE2_RETENTION  PWR_CR2_SRAM1PDS2 /*!< SRAM1 page 2 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE3_RETENTION  PWR_CR2_SRAM1PDS3 /*!< SRAM1 page 3 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE4_RETENTION  PWR_CR2_SRAM1PDS4 /*!< SRAM1 page 4 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE5_RETENTION  PWR_CR2_SRAM1PDS5 /*!< SRAM1 page 5 retention Stop modes (Stop 0, 1, 2, 3) */
#if defined(PWR_CR2_SRAM1PDS6)
#define LL_PWR_SRAM1_STOP_PAGE6_RETENTION  PWR_CR2_SRAM1PDS6 /*!< SRAM1 page 6 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE7_RETENTION  PWR_CR2_SRAM1PDS7 /*!< SRAM1 page 7 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_FULL_RETENTION   (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | PWR_CR2_SRAM1PDS3 |\
                                            PWR_CR2_SRAM1PDS4 | PWR_CR2_SRAM1PDS5 | PWR_CR2_SRAM1PDS6 |\
                                            PWR_CR2_SRAM1PDS7)
/*!< SRAM1 all pages retention in Stop modes (Stop 0, 1, 2, 3) */
#else
#define LL_PWR_SRAM1_STOP_FULL_RETENTION   (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | PWR_CR2_SRAM1PDS3 |\
                                            PWR_CR2_SRAM1PDS4 | PWR_CR2_SRAM1PDS5)
/*!< SRAM1 all pages retention in Stop modes (Stop 0, 1, 2, 3) */
#endif /* PWR_CR2_SRAM1PDS6 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_STOP_CONTENTS_RETENTION PWR SRAM2 Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM2_STOP_NO_RETENTION     (0U)              /*!< SRAM2 no retention in Stop modes (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM2_STOP_PAGE1_RETENTION  PWR_CR2_SRAM2PDS1 /*!< SRAM2 page 1 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM2_STOP_PAGE2_RETENTION  PWR_CR2_SRAM2PDS2 /*!< SRAM2 page 2 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM2_STOP_PAGE3_RETENTION  PWR_CR2_SRAM2PDS3 /*!< SRAM2 page 3 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM2_STOP_FULL_RETENTION   (PWR_CR2_SRAM2PDS1 | PWR_CR2_SRAM2PDS2 | PWR_CR2_SRAM2PDS3)
/*!< SRAM2 all pages retention in Stop modes (Stop 0, 1, 2, 3) */
/**
  * @}
  */

#if defined(RAMCFG_SRAM3)
/** @defgroup PWR_LL_EC_SRAM3_STOP_CONTENTS_RETENTION PWR SRAM3 Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM3_STOP_NO_RETENTION     (0U)              /*!< SRAM3 no retention in Stop modes (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM3_STOP_PAGE1_RETENTION  PWR_CR2_SRAM3PDS1 /*!< SRAM3 page 1 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM3_STOP_PAGE2_RETENTION  PWR_CR2_SRAM3PDS2 /*!< SRAM3 page 2 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM3_STOP_PAGE3_RETENTION  PWR_CR2_SRAM3PDS3 /*!< SRAM3 page 3 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM3_STOP_PAGE4_RETENTION  PWR_CR2_SRAM3PDS4 /*!< SRAM3 page 4 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM3_STOP_PAGE5_RETENTION  PWR_CR2_SRAM3PDS5 /*!< SRAM3 page 5 retention Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM3_STOP_FULL_RETENTION   (PWR_CR2_SRAM3PDS1 | PWR_CR2_SRAM3PDS2 | PWR_CR2_SRAM3PDS3 |\
                                            PWR_CR2_SRAM3PDS4 | PWR_CR2_SRAM3PDS5)
/*!< SRAM3 all pages retention in Stop modes (Stop 0, 1, 2, 3) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM4_STOP_CONTENTS_RETENTION PWR SRAM4 Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_SRAM4_STOP_NO_RETENTION     (0U)             /*!< SRAM4 no retention in Stop modes (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM4_STOP_FULL_RETENTION   PWR_CR2_SRAM4PDS /*!< SRAM4 full retention in Stop modes (Stop 0, 1, 2, 3) */
/**
  * @}
  */
#endif /* RAMCFG_SRAM3 */

/** @defgroup PWR_LL_EC_PKARAM_STOP_CONTENTS_RETENTION PWR PKA SRAM Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_PKARAM_STOP_NO_RETENTION  (0U)              /*!< PKA SRAM no retention in Stop modes (Stop 0, 1, 2, 3) */
#define LL_PWR_PKARAM_STOP_RETENTION     PWR_CR2_PKARAMPDS /*!< PKA SRAM content retained in Stop modes
                                                                (Stop 0, 1, 2, 3) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_FDCANUSBRAM_STOP_CONTENTS_RETENTION PWR FDCAN & USB SRAM Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_FDCANUSBRAM_STOP_NO_RETENTION  (0U)            /*!< FDCAN & USB SRAM no retention in Stop modes
                                                                    (Stop 0, 1, 2, 3) */
#define LL_PWR_FDCANUSBRAM_STOP_RETENTION     PWR_CR2_PRAMPDS /*!< FDCAN & USB SRAM content retained in Stop modes
                                                                    (Stop 0, 1, 2, 3) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ICACHERAM_STOP_CONTENTS_RETENTION PWR ICACHE SRAM Content Retention in Stop Mode
  * @{
  */
#define LL_PWR_ICACHERAM_STOP_NO_RETENTION  (0U)             /*!< ICACHE SRAM no retention in Stop modes
                                                                  (Stop 0, 1, 2, 3)      */
#define LL_PWR_ICACHERAM_STOP_RETENTION     PWR_CR2_ICRAMPDS /*!< ICACHE SRAM content retained in Stop modes
                                                                  (Stop 0, 1, 2, 3)  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGULATOR_SUPPLY_SELECTION PWR Regulator Supply Selection
  * @{
  */
#define LL_PWR_LDO_SUPPLY              (0U)           /*!< LDO regulator supply  */
#define LL_PWR_SMPS_SUPPLY             PWR_CR3_REGSEL /*!< SMPS regulator supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE1     PWR_VOSR_R1EN /*!< Voltage scaling range 1 (highest frequency) */
#define LL_PWR_REGU_VOLTAGE_SCALE2     PWR_VOSR_R2EN /*!< Voltage scaling range 2 (lowest power)      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVD_LEVEL_SELECTION PWR Power Voltage Detector Level Selection
  * @{
  */
#define LL_PWR_PVDLEVEL_0       (0U)                                    /*!< Voltage threshold detected by PVD 2.0 V  */
#define LL_PWR_PVDLEVEL_1       PWR_SVMCR_PVDLS_0                       /*!< Voltage threshold detected by PVD 2.2 V  */
#define LL_PWR_PVDLEVEL_2       PWR_SVMCR_PVDLS_1                       /*!< Voltage threshold detected by PVD 2.4 V  */
#define LL_PWR_PVDLEVEL_3       (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_1) /*!< Voltage threshold detected by PVD 2.5 V  */
#define LL_PWR_PVDLEVEL_4       PWR_SVMCR_PVDLS_2                       /*!< Voltage threshold detected by PVD 2.6 V  */
#define LL_PWR_PVDLEVEL_5       (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.8 V  */
#define LL_PWR_PVDLEVEL_6       (PWR_SVMCR_PVDLS_1 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.9 V  */
#define LL_PWR_PVDLEVEL_7       PWR_SVMCR_PVDLS
/*!< External input analog voltage on PVD_IN pin, compared to internal VREFINT level  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_CHARGING_RESISTOR_SELECTION PWR VBAT Charging Resistor Selection
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K    (0U)          /*!< Charge the battery through a 5 kO resistor   */
#define LL_PWR_BATT_CHARG_RESISTOR_1_5K  PWR_BDCR_VBRS /*!< Charge the battery through a 1.5 kO resistor */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PORT_SELECTION PWR GPIO Port Selection
  * @{
  */
#define LL_PWR_GPIO_PORTA              ((uint32_t)(&(PWR->PUCRA)))             /*!< GPIO port A */
#define LL_PWR_GPIO_PORTB              ((uint32_t)(&(PWR->PUCRB)))             /*!< GPIO port B */
#define LL_PWR_GPIO_PORTC              ((uint32_t)(&(PWR->PUCRC)))             /*!< GPIO port C */
#define LL_PWR_GPIO_PORTD              ((uint32_t)(&(PWR->PUCRD)))             /*!< GPIO port D */
#define LL_PWR_GPIO_PORTE              ((uint32_t)(&(PWR->PUCRE)))             /*!< GPIO port E */
#if defined(RAMCFG_SRAM3)
#define LL_PWR_GPIO_PORTF              ((uint32_t)(&(PWR->PUCRF)))             /*!< GPIO port F */
#endif /* RAMCFG_SRAM3 */
#define LL_PWR_GPIO_PORTG              ((uint32_t)(&(PWR->PUCRG)))             /*!< GPIO port G */
#define LL_PWR_GPIO_PORTH              ((uint32_t)(&(PWR->PUCRH)))             /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PIN_MASK PWR GPIO Pin Mask
  * @{
  */
#define LL_PWR_GPIO_PIN_0              (0x0001U)                               /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_PIN_1              (0x0002U)                               /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_PIN_2              (0x0004U)                               /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_PIN_3              (0x0008U)                               /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_PIN_4              (0x0010U)                               /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_PIN_5              (0x0020U)                               /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_PIN_6              (0x0040U)                               /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_PIN_7              (0x0080U)                               /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_PIN_8              (0x0100U)                               /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_PIN_9              (0x0200U)                               /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_PIN_10             (0x0400U)                               /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_PIN_11             (0x0800U)                               /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_PIN_12             (0x1000U)                               /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_PIN_13             (0x2000U)                               /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_PIN_14             (0x4000U)                               /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_PIN_15             (0x8000U)                               /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_I3C_PULLUP_CONFIG1 PWR I3C PULL-UP Configuration Port A-B
  * @{
  */
#define LL_PWR_I3CPUCR1_PA1            PWR_I3CPUCR1_PA1_I3CPU                  /*!< I3C pull-up on PA1  */
#define LL_PWR_I3CPUCR1_PA6            PWR_I3CPUCR1_PA6_I3CPU                  /*!< I3C pull-up on PA6  */
#define LL_PWR_I3CPUCR1_PA7            PWR_I3CPUCR1_PA7_I3CPU                  /*!< I3C pull-up on PA7  */
#define LL_PWR_I3CPUCR1_PB2            PWR_I3CPUCR1_PB2_I3CPU                  /*!< I3C pull-up on PB2  */
#define LL_PWR_I3CPUCR1_PB6            PWR_I3CPUCR1_PB6_I3CPU                  /*!< I3C pull-up on PB6  */
#if defined(RAMCFG_SRAM3)
#define LL_PWR_I3CPUCR1_PB7            PWR_I3CPUCR1_PB7_I3CPU                  /*!< I3C pull-up on PB7  */
#endif /* defined(RAMCFG_SRAM3) */
#if defined(PWR_I3CPUCR1_PB8_I3CPU)
#define LL_PWR_I3CPUCR1_PB8            PWR_I3CPUCR1_PB8_I3CPU                  /*!< I3C pull-up on PB8  */
#define LL_PWR_I3CPUCR1_PB9            PWR_I3CPUCR1_PB9_I3CPU                  /*!< I3C pull-up on PB9  */
#endif /* PWR_I3CPUCR1_PB8_I3CPU */
#define LL_PWR_I3CPUCR1_PB10           PWR_I3CPUCR1_PB10_I3CPU                 /*!< I3C pull-up on PB10 */
#define LL_PWR_I3CPUCR1_PB12           PWR_I3CPUCR1_PB12_I3CPU                 /*!< I3C pull-up on PB12 */
#define LL_PWR_I3CPUCR1_PB13           PWR_I3CPUCR1_PB13_I3CPU                 /*!< I3C pull-up on PB13 */
#if defined(PWR_I3CPUCR1_PB8_I3CPU)
#define LL_PWR_I3CPUCR1_PB14           PWR_I3CPUCR1_PB14_I3CPU                 /*!< I3C pull-up on PB14 */
#endif /* PWR_I3CPUCR1_PB8_I3CPU */
#if defined(LL_PWR_I3CPUCR1_PB7)
#define LL_PWR_I3CPUCR1_ALL            (LL_PWR_I3CPUCR1_PA1  | LL_PWR_I3CPUCR1_PA6  | LL_PWR_I3CPUCR1_PA7  |\
                                        LL_PWR_I3CPUCR1_PB2  | LL_PWR_I3CPUCR1_PB6  | LL_PWR_I3CPUCR1_PB7  |\
                                        LL_PWR_I3CPUCR1_PB8  | LL_PWR_I3CPUCR1_PB9  | LL_PWR_I3CPUCR1_PB10 |\
                                        LL_PWR_I3CPUCR1_PB12 | LL_PWR_I3CPUCR1_PB13 | LL_PWR_I3CPUCR1_PB14)
#elif defined(PWR_I3CPUCR1_PB8_I3CPU)
#define LL_PWR_I3CPUCR1_ALL            (LL_PWR_I3CPUCR1_PA1  | LL_PWR_I3CPUCR1_PA6  | LL_PWR_I3CPUCR1_PA7  |\
                                        LL_PWR_I3CPUCR1_PB2  | LL_PWR_I3CPUCR1_PB6  | LL_PWR_I3CPUCR1_PB8  |\
                                        LL_PWR_I3CPUCR1_PB9  | LL_PWR_I3CPUCR1_PB10 | LL_PWR_I3CPUCR1_PB12 |\
                                        LL_PWR_I3CPUCR1_PB13 | LL_PWR_I3CPUCR1_PB14)
#else
#define LL_PWR_I3CPUCR1_ALL            (LL_PWR_I3CPUCR1_PA1  | LL_PWR_I3CPUCR1_PA6  | LL_PWR_I3CPUCR1_PA7  |\
                                        LL_PWR_I3CPUCR1_PB2  | LL_PWR_I3CPUCR1_PB6  | LL_PWR_I3CPUCR1_PB10 |\
                                        LL_PWR_I3CPUCR1_PB12 | LL_PWR_I3CPUCR1_PB13)
#endif /* defined-LL_PWR_I3CPUCR1_PB7) */
/*!<  I3C pull-up all for port A-B */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_I3C_PULLUP_CONFIG2 PWR I3C PULL-UP Configuration Port C-D-G-H
  * @{
  */
#if defined(PWR_I3CPUCR2_PC0_I3CPU)
#define LL_PWR_I3CPUCR2_PC0            PWR_I3CPUCR2_PC0_I3CPU                  /*!< I3C pull-up on PC0  */
#endif /* defined(PWR_I3CPUCR2_PC0_I3CPU) */
#define LL_PWR_I3CPUCR2_PC1            PWR_I3CPUCR2_PC1_I3CPU                  /*!< I3C pull-up on PC1  */
#define LL_PWR_I3CPUCR2_PD12           PWR_I3CPUCR2_PD12_I3CPU                 /*!< I3C pull-up on PD12 */
#define LL_PWR_I3CPUCR2_PD13           PWR_I3CPUCR2_PD13_I3CPU                 /*!< I3C pull-up on PD13 */
#if defined(PWR_I3CPUCR2_PC0_I3CPU)
#define LL_PWR_I3CPUCR2_PG7            PWR_I3CPUCR2_PG7_I3CPU                  /*!< I3C pull-up on PG7  */
#define LL_PWR_I3CPUCR2_PG8            PWR_I3CPUCR2_PG8_I3CPU                  /*!< I3C pull-up on PG8  */
#define LL_PWR_I3CPUCR2_PG13           PWR_I3CPUCR2_PG13_I3CPU                 /*!< I3C pull-up on PG13 */
#define LL_PWR_I3CPUCR2_PG14           PWR_I3CPUCR2_PG14_I3CPU                 /*!< I3C pull-up on PG14 */
#endif /* defined(PWR_I3CPUCR2_PC0_I3CPU) */
#define LL_PWR_I3CPUCR2_PH3            PWR_I3CPUCR2_PH3_I3CPU                  /*!< I3C pull-up on PH3  */
#if defined(PWR_I3CPUCR2_PC0_I3CPU)
#define LL_PWR_I3CPUCR2_ALL            (LL_PWR_I3CPUCR2_PC0  | LL_PWR_I3CPUCR2_PC1  | LL_PWR_I3CPUCR2_PD12 |\
                                        LL_PWR_I3CPUCR2_PD13 | LL_PWR_I3CPUCR2_PG7  | LL_PWR_I3CPUCR2_PG8  |\
                                        LL_PWR_I3CPUCR2_PG13 | LL_PWR_I3CPUCR2_PG14 | LL_PWR_I3CPUCR2_PH3)
#else
#define LL_PWR_I3CPUCR2_ALL            (LL_PWR_I3CPUCR2_PC1  | LL_PWR_I3CPUCR2_PD12 | LL_PWR_I3CPUCR2_PH3)
#endif /* defined(PWR_I3CPUCR2_PC0_I3CPU) */
/*!<  I3C pull-up all for port C-D-G-H */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ITEMS_SECURE_ATTRIBUTE PWR Items Secure Attribute
  * @{
  */
#define LL_PWR_WAKEUP_LINE1_NSEC       (0U)                 /*!< Wake up line 1 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE1_SEC        PWR_SECCFGR_WUP1SEC  /*!< Wake up line 1 secure mode                    */
#define LL_PWR_WAKEUP_LINE2_NSEC       (0U)                 /*!< Wake up line 2 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE2_SEC        PWR_SECCFGR_WUP2SEC  /*!< Wake up line 2 secure mode                    */
#define LL_PWR_WAKEUP_LINE3_NSEC       (0U)                 /*!< Wake up line 3 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE3_SEC        PWR_SECCFGR_WUP3SEC  /*!< Wake up line 3 secure mode                    */
#define LL_PWR_WAKEUP_LINE4_NSEC       (0U)                 /*!< Wake up line 4 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE4_SEC        PWR_SECCFGR_WUP4SEC  /*!< Wake up line 4 secure mode                    */
#define LL_PWR_WAKEUP_LINE5_NSEC       (0U)                 /*!< Wake up line 5 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE5_SEC        PWR_SECCFGR_WUP5SEC  /*!< Wake up line 5 secure mode                    */
#define LL_PWR_WAKEUP_LINE6_NSEC       (0U)                 /*!< Wake up line 6 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE6_SEC        PWR_SECCFGR_WUP6SEC  /*!< Wake up line 6 secure mode                    */
#define LL_PWR_WAKEUP_LINE7_NSEC       (0U)                 /*!< Wake up line 7 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE7_SEC        PWR_SECCFGR_WUP7SEC  /*!< Wake up line 7 secure mode                    */
#define LL_PWR_WAKEUP_LINE8_NSEC       (0U)                 /*!< Wake up line 8 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE8_SEC        PWR_SECCFGR_WUP8SEC  /*!< Wake up line 8 secure mode                    */
#define LL_PWR_WAKEUP_LINE9_NSEC       (0U)                 /*!< Wake up line 9 nsecure mode                   */
#define LL_PWR_WAKEUP_LINE9_SEC        PWR_SECCFGR_WUP9SEC  /*!< Wake up line 9 secure mode                    */
#define LL_PWR_WAKEUP_LINE10_NSEC      (0U)                 /*!< Wake up line 10 nsecure mode                  */
#define LL_PWR_WAKEUP_LINE10_SEC       PWR_SECCFGR_WUP10SEC /*!< Wake up line 10 secure mode                   */
#define LL_PWR_LPM_NSEC                (0U)                 /*!< Low-power modes nsecure mode                  */
#define LL_PWR_LPM_SEC                 PWR_SECCFGR_LPMSEC   /*!< Low-power modes secure mode                   */
#define LL_PWR_VDM_NSEC                (0U)                 /*!< Voltage detection and monitoring nsecure mode */
#define LL_PWR_VDM_SEC                 PWR_SECCFGR_VDMSEC   /*!< Voltage detection and monitoring secure mode  */
#define LL_PWR_VB_NSEC                 (0U)                 /*!< Backup domain nsecure mode                    */
#define LL_PWR_VB_SEC                  PWR_SECCFGR_VBSEC    /*!< Backup domain secure mode                     */
#define LL_PWR_APC_NSEC                (0U)                 /*!< Pull-up/pull-down nsecure mode                */
#define LL_PWR_APC_SEC                 PWR_SECCFGR_APCSEC   /*!< Pull-up/pull-down secure mode                 */
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
  * @rmtoll CR1              LPMS          LL_PWR_SetPowerMode
  * @param  Mode  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STOP3
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t Mode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, Mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll CR1              LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STOP3
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @brief  Enable SRAM1 power down.
  * @rmtoll CR1          SRAM1PD        LL_PWR_EnableSRAM1PowerDown
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAM1PowerDown(void)
{
  /* SRAM1 powered off */
  SET_BIT(PWR->CR1, PWR_CR1_SRAM1PD);
}

/**
  * @brief  Disable SRAM1 power down.
  * @rmtoll CR1          SRAM1PD        LL_PWR_DisableSRAM1PowerDown
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAM1PowerDown(void)
{
  /* SRAM1 powered on */
  CLEAR_BIT(PWR->CR1, PWR_CR1_SRAM1PD);
}

/**
  * @brief  Check if SRAM1 power down is enabled.
  * @rmtoll CR1          SRAM1PD        LL_PWR_IsEnabledSRAM1PowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM1PowerDown(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_SRAM1PD) == (PWR_CR1_SRAM1PD)) ? 1UL : 0UL);
}

/**
  * @brief  Enable SRAM2 power down.
  * @rmtoll CR1          SRAM2PD        LL_PWR_EnableSRAM2PowerDown
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAM2PowerDown(void)
{
  /* SRAM2 powered off */
  SET_BIT(PWR->CR1, PWR_CR1_SRAM2PD);
}

/**
  * @brief  Disable SRAM2 power down.
  * @rmtoll CR1          SRAM2PD        LL_PWR_DisableSRAM2PowerDown
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAM2PowerDown(void)
{
  /* SRAM2 powered on */
  CLEAR_BIT(PWR->CR1, PWR_CR1_SRAM2PD);
}

/**
  * @brief  Check if SRAM2 power down is enabled.
  * @rmtoll CR1          SRAM2PD        LL_PWR_IsEnabledSRAM2PowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM2PowerDown(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_SRAM2PD) == (PWR_CR1_SRAM2PD)) ? 1UL : 0UL);
}

/**
  * @brief  Set the SRAM2 page(s) retention in Standby mode.
  * @rmtoll CR1              RRSB1         LL_PWR_SetSRAM2SBRetention
  * @rmtoll CR1              RRSB2         LL_PWR_SetSRAM2SBRetention
  * @rmtoll CR1              RRSB3         LL_PWR_SetSRAM2SBRetention
  * @param  SRAM2PageRetention  This parameter can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_PAGE3_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM2SBRetention(uint32_t SRAM2PageRetention)
{
  MODIFY_REG(PWR->CR1, (PWR_CR1_RRSB1 | PWR_CR1_RRSB2 | PWR_CR1_RRSB3), SRAM2PageRetention);
}

/**
  * @brief  Get the SRAM2 page(s) retention in Standby mode.
  * @rmtoll CR1              RRSB1         LL_PWR_GetSRAM2SBRetention
  * @rmtoll CR1              RRSB2         LL_PWR_GetSRAM2SBRetention
  * @rmtoll CR1              RRSB3         LL_PWR_GetSRAM2SBRetention
  * @retval Returned value can be one of the following values:
  *                              @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *                              @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2SBRetention(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_RRSB1 | PWR_CR1_RRSB2 | PWR_CR1_RRSB3));
}

#if defined(RAMCFG_SRAM3)
#if defined(PWR_CR1_SRAM3PD)
/**
  * @brief  Enable SRAM3 power down.
  * @rmtoll CR1          SRAM3PD        LL_PWR_EnableSRAM3PowerDown
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAM3PowerDown(void)
{
  /* SRAM3 powered off */
  SET_BIT(PWR->CR1, PWR_CR1_SRAM3PD);
}

/**
  * @brief  Disable SRAM3 power down.
  * @rmtoll CR1          SRAM3PD        LL_PWR_DisableSRAM3PowerDown
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAM3PowerDown(void)
{
  /* SRAM3 powered on */
  CLEAR_BIT(PWR->CR1, PWR_CR1_SRAM3PD);
}

/**
  * @brief  Check if SRAM3 power down is enabled.
  * @rmtoll CR1          SRAM3PD        LL_PWR_IsEnabledSRAM3PowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM3PowerDown(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_SRAM3PD) == (PWR_CR1_SRAM3PD)) ? 1UL : 0UL);
}
#endif /* defined(PWR_CR1_SRAM3PD) */

#if defined(PWR_CR1_SRAM4PD)
/**
  * @brief  Enable SRAM4 power down.
  * @rmtoll CR1          SRAM4PD        LL_PWR_EnableSRAM4PowerDown
  * @retval None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAM4PowerDown(void)
{
  /* SRAM4 powered off */
  SET_BIT(PWR->CR1, PWR_CR1_SRAM4PD);
}

/**
  * @brief  Disable SRAM4 power down.
  * @rmtoll CR1          SRAM4PD        LL_PWR_DisableSRAM4PowerDown
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAM4PowerDown(void)
{
  /* SRAM4 powered on */
  CLEAR_BIT(PWR->CR1, PWR_CR1_SRAM4PD);
}

/**
  * @brief  Check if SRAM4 power down is enabled.
  * @rmtoll CR1          SRAM4PD        LL_PWR_IsEnabledSRAM4PowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM4PowerDown(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_SRAM4PD) == (PWR_CR1_SRAM4PD)) ? 1UL : 0UL);
}
#endif /* defined(PWR_CR1_SRAM4PD) */
#endif /* RAMCFG_SRAM3 */

/**
  * @brief  Enable BOR ultra low power mode.
  * @rmtoll CR1          UPLMEN        LL_PWR_EnableUltraLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Disable BOR ultra low-power mode.
  * @rmtoll CR1          UPLMEN        LL_PWR_DisableUltraLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Check if BOR ultra low power mode is enabled.
  * @rmtoll CR1          UPLMEN        LL_PWR_IsEnabledUltraLowPowerMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUltraLowPowerMode(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_ULPMEN) == (PWR_CR1_ULPMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the SRAM1 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM1PDSi       LL_PWR_SetSRAM1StopRetention
  * @param  SRAM1PageRetention  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM1StopRetention(uint32_t SRAM1PageRetention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM1_STOP_FULL_RETENTION, ((~SRAM1PageRetention) & LL_PWR_SRAM1_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM1 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM1PDSi       LL_PWR_GetSRAM1StopRetention
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM1_STOP_FULL_RETENTION))) & LL_PWR_SRAM1_STOP_FULL_RETENTION);
}

/**
  * @brief  Set the SRAM2 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM2PDSi       LL_PWR_SetSRAM2StopRetention
  * @param  SRAM2PageRetention  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM2StopRetention(uint32_t SRAM2PageRetention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM2_STOP_FULL_RETENTION, ((~SRAM2PageRetention) & LL_PWR_SRAM2_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM2 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM2PDSi       LL_PWR_GetSRAM2StopRetention
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM2_STOP_FULL_RETENTION))) & LL_PWR_SRAM2_STOP_FULL_RETENTION);
}

#if defined(RAMCFG_SRAM3)
/**
  * @brief  Set the SRAM3 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM3PDS       LL_PWR_SetSRAM3StopRetention
  * @param  SRAM3PageRetention  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM3StopRetention(uint32_t SRAM3PageRetention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM3_STOP_FULL_RETENTION, ((~SRAM3PageRetention) & LL_PWR_SRAM3_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM3 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM3PDSi       LL_PWR_GetSRAM3StopRetention
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM3StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM3_STOP_FULL_RETENTION))) & LL_PWR_SRAM3_STOP_FULL_RETENTION);
}

/**
  * @brief  Set the SRAM4 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM4PDS       LL_PWR_SetSRAM4StopRetention
  * @param  SRAM4PageRetention  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM4_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSRAM4StopRetention(uint32_t SRAM4PageRetention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM4_STOP_FULL_RETENTION, ((~SRAM4PageRetention) & LL_PWR_SRAM4_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM4 page(s) retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    SRAM4PDSi       LL_PWR_GetSRAM4StopRetention
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM4_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM4StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM4_STOP_FULL_RETENTION))) & LL_PWR_SRAM4_STOP_FULL_RETENTION);
}
#endif /* RAMCFG_SRAM3 */

/**
  * @brief  Set the PKA SRAM retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    PKARAMPDS       LL_PWR_SetPKARAMStopRetention
  * @param  Retention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PKARAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PKARAM_STOP_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPKARAMStopRetention(uint32_t Retention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PKARAMPDS,
             ((~Retention) & PWR_CR2_PKARAMPDS));
}

/**
  * @brief  Get the PKA SRAM retention in Stop modes (Stop 0, 1, 2, 3).
  * @rmtoll CR2    PKARAMPDS       LL_PWR_GetPKARAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PKARAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PKARAM_STOP_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetPKARAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_PKARAMPDS))) & PWR_CR2_PKARAMPDS);
}

/**
  * @brief  Set the FDCAN and USB SRAM power-down in Stop modes (Stop 0,1,2,3).
  * @rmtoll CR2    PRAMPDS       LL_PWR_SetFDCANUSBRAMStopRetention
  * @param  Retention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_FDCANUSBRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_FDCANUSBRAM_STOP_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetFDCANUSBRAMStopRetention(uint32_t Retention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PRAMPDS,
             ((~Retention) & PWR_CR2_PRAMPDS));
}

/**
  * @brief  Get the PKA SRAM retention in Stop mode.
  * @rmtoll CR2    PRAMPDS       LL_PWR_GetFDCANUSBRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_FDCANUSBRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_FDCANUSBRAM_STOP_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetFDCANUSBRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_PRAMPDS))) & PWR_CR2_PRAMPDS);
}

/**
  * @brief  Set the ICACHE SRAM retention in Stop mode.
  * @rmtoll CR2    ICRAMPDS       LL_PWR_SetICacheRAMStopRetention
  * @param  Retention  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_RETENTION
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetICacheRAMStopRetention(uint32_t Retention)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_ICRAMPDS,
             ((~Retention) & PWR_CR2_ICRAMPDS));
}

/**
  * @brief  Get the ICACHE SRAM retention in Stop mode.
  * @rmtoll CR2    ICRAMPDS       LL_PWR_GetICacheRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetICacheRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, PWR_CR2_ICRAMPDS))) & PWR_CR2_ICRAMPDS);
}


/**
  * @brief  Enable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2    FLASHFWU       LL_PWR_EnableFlashFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFlashFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Disable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2    FLASHFWU       LL_PWR_DisableFlashFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFlashFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Check if the flash memory fast wakeup from Stop mode (Stop 0, 1)
  *         is enabled.
  * @rmtoll CR2    FLASHFWU       LL_PWR_IsEnabledFlashFastWakeUp
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashFastWakeUp(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_FLASHFWU) == (PWR_CR2_FLASHFWU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the SRAM memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2    SRAMFWU       LL_PWR_EnableSRAMFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAMFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_SRAMFWU);
}

/**
  * @brief  Disable the SRAM memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll CR2    SRAMFWU       LL_PWR_DisableSRAMFastWakeUp
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAMFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_SRAMFWU);
}

/**
  * @brief  Check if the SRAM memory fast wakeup from Stop mode (Stop 0, 1)
  *         is enabled.
  * @rmtoll CR2    SRAMFWU       LL_PWR_IsEnabledSRAMFastWakeUp
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAMFastWakeUp(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_SRAMFWU) == (PWR_CR2_SRAMFWU)) ? 1UL : 0UL);
}

#if defined(PWR_CR3_REGSEL)
/**
  * @brief  Set the VCore regulator supply.
  * @rmtoll CR3    REGSEL       LL_PWR_SetRegulatorSupply
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
  * @rmtoll CR3    REGSEL       LL_PWR_GetRegulatorSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_SMPS_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorSupply(void)
{
  return (READ_BIT(PWR->CR3, PWR_CR3_REGSEL));
}
#endif /* PWR_CR3_REGSEL */

/**
  * @brief  Enable the fast soft start for selected regulator.
  * @rmtoll CR3    FSTEN       LL_PWR_EnableFastSoftStart
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFastSoftStart(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Disable the fast soft start for selected regulator.
  * @rmtoll CR3    FSTEN       LL_PWR_DisableFastSoftStart
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFastSoftStart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Check if the fast soft start for selected regulator is enabled.
  * @rmtoll CR3    FSTEN       LL_PWR_IsEnabledFastSoftStart
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFastSoftStart(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_FSTEN) == (PWR_CR3_FSTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the regulator supply output voltage.
  * @note   R1EN and R2EN must be at opposite value.
  *         Any attempt to write R1EN and R2EN to same value is ignored.
  *         Modifying R1EN and R2EN is possible only when current range is
  *         ready (R1RDY=R1EN and R2RDY=R2EN).
  * @rmtoll VOSR          R1EN           LL_PWR_SetRegulVoltageScaling
  * @rmtoll VOSR          R2EN           LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->VOSR, PWR_VOSR_R1EN | PWR_VOSR_R2EN, VoltageScaling);
}

/**
  * @brief  Get the regulator supply output voltage.
  * @rmtoll VOSR          R1EN           LL_PWR_SetRegulVoltageScaling
  * @rmtoll VOSR          R2EN           LL_PWR_SetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->VOSR, PWR_VOSR_R1EN | PWR_VOSR_R2EN));
}

/**
  * @brief  Enable the EPOD (Embedded Power Distribution) booster.
  * @rmtoll VOSR    BOOSTEN       LL_PWR_EnableEPODBooster
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableEPODBooster(void)
{
  SET_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN);
}

/**
  * @brief  Disable the EPOD (Embedded Power Distribution) booster.
  * @rmtoll VOSR    BOOSTEN       LL_PWR_DisableEPODBooster
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableEPODBooster(void)
{
  CLEAR_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN);
}

/**
  * @brief  Check if  the EPOD (Embedded Power Distribution) booster is enabled.
  * @rmtoll VOSR    BOOSTEN       LL_PWR_IsEnabledEPODBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledEPODBooster(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN) == (PWR_VOSR_BOOSTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Get currently voltage scaling applied to VCORE.
  * @rmtoll VOSR             R1RDY      LL_PWR_GetRegulCurrentVOS
  * @rmtoll VOSR             R2RDY      LL_PWR_GetRegulCurrentVOS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulCurrentVOS(void)
{
  return (uint32_t)((READ_BIT(PWR->VOSR, PWR_VOSR_R1RDY | PWR_VOSR_R2RDY) >> PWR_VOSR_R1RDY_Pos));
}

/**
  * @brief  Set the Power voltage detector level.
  * @rmtoll SVMCR    PVDLS         LL_PWR_SetPVDLevel
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
  * @rmtoll SVMCR    PVDLS         LL_PWR_GetPVDLevel
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
  * @rmtoll SVMCR          PVDE          LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Disable the power voltage detector.
  * @rmtoll SVMCR          PVDE          LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Check if the power voltage detector is enabled.
  * @rmtoll SVMCR          PVDE          LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_PVDE) == (PWR_SVMCR_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent USB supply.
  * @rmtoll SVMCR    USV       LL_PWR_EnableVDDUSB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDUSB(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Disable the independent USB supply.
  * @rmtoll SVMCR    USV       LL_PWR_DisableVDDUSB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDUSB(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Check if the independent USB supply is enabled.
  * @rmtoll SVMCR    USV       LL_PWR_IsEnabledVDDUSB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDUSB(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_USV) == (PWR_SVMCR_USV)) ? 1UL : 0UL);
}

#if defined(PWR_SVMCR_IO2SV)
/**
  * @brief  Enable the independent I/Os supply.
  * @rmtoll SVMCR    IO2SV       LL_PWR_EnableVDDIO2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDIO2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Disable the independent I/Os supply.
  * @rmtoll SVMCR    IO2SV       LL_PWR_DisableVDDIO2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDIO2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Check if the independent I/Os supply is enabled.
  * @rmtoll SVMCR    IO2SV       LL_PWR_IsEnabledVDDIO2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDIO2(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV) == (PWR_SVMCR_IO2SV)) ? 1UL : 0UL);
}
#endif /* PWR_SVMCR_IO2SV */

/**
  * @brief  Enable the independent analog supply.
  * @rmtoll SVMCR    ASV       LL_PWR_EnableVDDA
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDA(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Disable the independent analog supply.
  * @rmtoll SVMCR    ASV       LL_PWR_DisableVDDA
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDA(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Check if the independent analog supply is enabled.
  * @rmtoll SVMCR    ASV       LL_PWR_IsEnabledVDDA
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDA(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_ASV) == (PWR_SVMCR_ASV)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent USB supply monitor.
  * @rmtoll SVMCR    UVMEN       LL_PWR_EnableVDDUSBMonitor
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDUSBMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Disable the independent USB supply monitor.
  * @rmtoll SVMCR    UVMEN       LL_PWR_DisableVDDUSBMonitor
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDUSBMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Check if the independent USB supply monitor is enabled.
  * @rmtoll SVMCR    UVMEN       LL_PWR_IsEnabledVDDUSBMonitor
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDUSBMonitor(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN) == (PWR_SVMCR_UVMEN)) ? 1UL : 0UL);
}

#if defined(PWR_SVMCR_IO2SV)
/**
  * @brief  Enable the independent I/Os supply monitor.
  * @rmtoll SVMCR    IO2VMEN       LL_PWR_EnableVDDIO2Monitor
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDIO2Monitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Disable the independent I/Os supply monitor.
  * @rmtoll SVMCR    IO2VMEN       LL_PWR_DisableVDDIO2Monitor
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDIO2Monitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Check if the independent I/Os supply monitor is enabled.
  * @rmtoll SVMCR    IO2VMEN       LL_PWR_IsEnabledVDDIO2Monitor
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDIO2Monitor(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN) == (PWR_SVMCR_IO2VMEN)) ? 1UL : 0UL);
}
#endif /* PWR_SVMCR_IO2SV */

/**
  * @brief  Enable the independent analog supply monitor 1.
  * @rmtoll SVMCR    AVM1EN       LL_PWR_EnableVDDAMonitor1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDAMonitor1(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Disable the independent analog supply monitor 1.
  * @rmtoll SVMCR    AVM1EN       LL_PWR_DisableVDDAMonitor1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDAMonitor1(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Check if the independent analog supply monitor 1 is enabled.
  * @rmtoll SVMCR    AVM1EN       LL_PWR_IsEnabledVDDAMonitor1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDAMonitor1(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN) == (PWR_SVMCR_AVM1EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent analog supply monitor 2.
  * @rmtoll SVMCR    AVM2EN       LL_PWR_EnableVDDAMonitor2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDAMonitor2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Disable the independent analog supply monitor 2.
  * @rmtoll SVMCR    AVM2EN       LL_PWR_DisableVDDAMonitor2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDAMonitor2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Check if the independent analog supply monitor 2 is enabled.
  * @rmtoll SVMCR    AVM2EN       LL_PWR_IsEnabledVDDAMonitor2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDAMonitor2(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN) == (PWR_SVMCR_AVM2EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the wake up line_x.
  * @rmtoll WUCR1    WUPENx       LL_PWR_EnableWakeUpLine
  * @param  WakeUpLine This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  *         @arg @ref LL_PWR_WAKEUP_LINE9
  *         @arg @ref LL_PWR_WAKEUP_LINE10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpLine(uint32_t WakeUpLine)
{
  SET_BIT(PWR->WUCR1, WakeUpLine);
}

/**
  * @brief  Disable the wake up line_x.
  * @rmtoll WUCR1    WUPENx       LL_PWR_DisableWakeUpLine
  * @param  WakeUpLine This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  *         @arg @ref LL_PWR_WAKEUP_LINE9
  *         @arg @ref LL_PWR_WAKEUP_LINE10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpLine(uint32_t WakeUpLine)
{
  CLEAR_BIT(PWR->WUCR1, WakeUpLine);
}

/**
  * @brief  Check if the wake up line_x is enabled.
  * @rmtoll WUCR1    WUPENx       LL_PWR_IsEnabledWakeUpLine
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  *         @arg @ref LL_PWR_WAKEUP_LINE9
  *         @arg @ref LL_PWR_WAKEUP_LINE10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpLine(uint32_t WakeUpLine)
{
  return ((READ_BIT(PWR->WUCR1, WakeUpLine) == (WakeUpLine)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up line polarity low for the event detection.
  * @rmtoll WUCR2          WUPPx       LL_PWR_SetWakeUpLinePolarityLow
  * @param  WakeUpLine This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLinePolarityLow(uint32_t WakeUpLine)
{
  SET_BIT(PWR->WUCR2, WakeUpLine);
}

/**
  * @brief  Set the wake up line polarity high for the event detection.
  * @rmtoll WUCR2          WUPPx       LL_PWR_SetWakeUpLinePolarityHigh
  * @param  WakeUpLine This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLinePolarityHigh(uint32_t WakeUpLine)
{
  CLEAR_BIT(PWR->WUCR2, WakeUpLine);
}

/**
  * @brief  Get the wake up line polarity for the event detection.
  * @rmtoll WUCR2          WUPPx       LL_PWR_GetWakeUpLinePolarity
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval State of bit (1 : polarity or 0 : polarity high).
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpLinePolarity(uint32_t WakeUpLine)
{
  return ((READ_BIT(PWR->WUCR2, WakeUpLine) == WakeUpLine) ? 1UL : 0UL);
}

/**
  * @brief  Set the wakeup line_x selection 0.
  * @rmtoll WUCR3          WUSELx          LL_PWR_SetWakeUpLineSignal0Selection
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLineSignal0Selection(uint32_t WakeUpLine)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U)),
             (LL_PWR_WAKEUP_LINE_SELECTION_0 << (POSITION_VAL(WakeUpLine) * 2U)));
}

/**
  * @brief  Set the wakeup line_x selection 1.
  * @rmtoll WUCR3          WUSELx          LL_PWR_SetWakeUpLineSignal1Selection
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLineSignal1Selection(uint32_t WakeUpLine)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U)),
             (LL_PWR_WAKEUP_LINE_SELECTION_1 << (POSITION_VAL(WakeUpLine) * 2U)));
}

/**
  * @brief  Set the wakeup line_x selection 2.
  * @rmtoll WUCR3          WUSELx          LL_PWR_SetWakeUpLineSignal2Selection
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLineSignal2Selection(uint32_t WakeUpLine)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U)),
             (LL_PWR_WAKEUP_LINE_SELECTION_2 << (POSITION_VAL(WakeUpLine) * 2U)));
}

/**
  * @brief  Set the wakeup line_x selection 3.
  * @rmtoll WUCR3          WUSELx          LL_PWR_SetWakeUpLineSignal3Selection
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpLineSignal3Selection(uint32_t WakeUpLine)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U)),
             (LL_PWR_WAKEUP_LINE_SELECTION_3 << (POSITION_VAL(WakeUpLine) * 2U)));
}

/**
  * @brief  Get the wakeup line_x selection.
  * @rmtoll WUCR3          WUSELx          LL_PWR_GetWakeUpLineSignalSelection
  * @param  WakeUpLine This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1
  *         @arg @ref LL_PWR_WAKEUP_LINE2
  *         @arg @ref LL_PWR_WAKEUP_LINE3
  *         @arg @ref LL_PWR_WAKEUP_LINE4
  *         @arg @ref LL_PWR_WAKEUP_LINE5
  *         @arg @ref LL_PWR_WAKEUP_LINE6
  *         @arg @ref LL_PWR_WAKEUP_LINE7
  *         @arg @ref LL_PWR_WAKEUP_LINE8
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpLineSignalSelection(uint32_t WakeUpLine)
{
  return (READ_BIT(PWR->WUCR3, (3UL << (POSITION_VAL(WakeUpLine) * 2U))));
}

/**
  * @brief  Enable battery charging.
  * @rmtoll BDCR          VBE           LL_PWR_EnableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->BDCR, PWR_BDCR_VBE);
}

/**
  * @brief  Disable battery charging.
  * @rmtoll BDCR          VBE           LL_PWR_DisableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->BDCR, PWR_BDCR_VBE);
}

/**
  * @brief  Check if battery charging is enabled.
  * @rmtoll BDCR          VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->BDCR, PWR_BDCR_VBE) == (PWR_BDCR_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Battery charge resistor impedance
  * @rmtoll BDCR          VBRS          LL_PWR_SetBattChargResistor
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t Resistor)
{
  MODIFY_REG(PWR->BDCR, PWR_BDCR_VBRS, Resistor);
}

/**
  * @brief  Get the Battery charge resistor impedance
  * @rmtoll BDCR          VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (uint32_t)(READ_BIT(PWR->BDCR, PWR_BDCR_VBRS));
}

/**
  * @brief  Enable access to the backup domain.
  * @rmtoll DBPR    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable access to the backup domain.
  * @rmtoll DBPR    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Check if the access to backup domain is enabled.
  * @rmtoll DBPR    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->DBPR, PWR_DBPR_DBP) == (PWR_DBPR_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the pull-up and pull-down configuration.
  * @rmtoll APCR          APC           LL_PWR_EnablePUPDConfig
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePUPDConfig(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable the pull-up and pull-down configuration.
  * @rmtoll APCR          APC           LL_PWR_DisablePUPDConfig
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePUPDConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Check if the pull-up and pull-down configuration is enabled.
  * @rmtoll APCR          APC           LL_PWR_IsEnabledPUPDConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDConfig(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_APC) == (PWR_APCR_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-up in Standby and Shutdown modes
  * @rmtoll PUCRx        PUx        LL_PWR_EnableGPIOPullUp
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
#if defined(RAMCFG_SRAM3)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
#endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE void LL_PWR_EnableGPIOPullUp(uint32_t GPIOPort, uint32_t GPIOPin)
{
  SET_BIT(*((uint32_t *)GPIOPort), GPIOPin);
}

/**
  * @brief  Disable GPIO pull-up in Standby and Shutdown modes
  * @rmtoll PUCRx        PUx        LL_PWR_DisableGPIOPullUp
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE void LL_PWR_DisableGPIOPullUp(uint32_t GPIOPort, uint32_t GPIOPin)
{
  CLEAR_BIT(*((uint32_t *)GPIOPort), GPIOPin);
}

/**
  * @brief  Check if GPIO pull-up in Standby and Shutdown modes is enabled
  * @rmtoll PUCRx        PUx        LL_PWR_IsEnabledGPIOPullUp
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullUp(uint32_t GPIOPort, uint32_t GPIOPin)
{
  return ((READ_BIT(*((uint32_t *)(GPIOPort)), GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-down in Standby and Shutdown modes.
  * @rmtoll PDCRx        PDx        LL_PWR_EnableGPIOPullDown
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE void LL_PWR_EnableGPIOPullDown(uint32_t GPIOPort, uint32_t GPIOPin)
{
  SET_BIT(*((__IO uint32_t *)(GPIOPort + 4U)), GPIOPin);
}

/**
  * @brief  Disable GPIO pull-down in Standby and Shutdown modes.
  * @rmtoll PDCRx        PDx        LL_PWR_DisableGPIOPullDown
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE void LL_PWR_DisableGPIOPullDown(uint32_t GPIOPort, uint32_t GPIOPin)
{
  CLEAR_BIT(*((__IO uint32_t *)(GPIOPort + 4U)), GPIOPin);
}

/**
  * @brief  Check if GPIO pull-down in Standby and Shutdown modes is enabled
  * @rmtoll PDCRx        PDx        LL_PWR_IsEnabledGPIOPullDown
  * @param  GPIOPort This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
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
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullDown(uint32_t GPIOPort, uint32_t GPIOPin)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIOPort + 4U)), GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set I3C pull-up configuration for GPIO on port A-B.
  * @rmtoll I3CPUCR1     PAx_I3CPU        LL_PWR_SetI3CPullUpConfig1
  * @rmtoll I3CPUCR1     PBx_I3CPU        LL_PWR_SetI3CPullUpConfig1
  * @param  Gpio  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_I3CPUCR1_PA1
  *         @arg @ref LL_PWR_I3CPUCR1_PA6
  *         @arg @ref LL_PWR_I3CPUCR1_PA7
  *         @arg @ref LL_PWR_I3CPUCR1_PB2
  *         @arg @ref LL_PWR_I3CPUCR1_PB6
  *         @arg @ref LL_PWR_I3CPUCR1_PB8
  *         @arg @ref LL_PWR_I3CPUCR1_PB9
  *         @arg @ref LL_PWR_I3CPUCR1_PB10
  *         @arg @ref LL_PWR_I3CPUCR1_PB12
  *         @arg @ref LL_PWR_I3CPUCR1_PB13
  *         @arg @ref LL_PWR_I3CPUCR1_PB14
  *         @arg @ref LL_PWR_I3CPUCR1_ALL
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetI3CPullUpConfig1(uint32_t Gpio)
{
  MODIFY_REG(PWR->I3CPUCR1, LL_PWR_I3CPUCR1_ALL, Gpio);
}

/**
  * @brief  Get I3C pull-up configuration for GPIO on port A-B.
#if defined(RAMCFG_SRAM3)
#endif
  * @rmtoll I3CPUCR1     PAx_I3CPU        LL_PWR_GetI3CPullUpConfig1
  * @rmtoll I3CPUCR1     PBx_I3CPU        LL_PWR_GetI3CPullUpConfig1
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_I3CPUCR1_PA1
  *         @arg @ref LL_PWR_I3CPUCR1_PA6
  *         @arg @ref LL_PWR_I3CPUCR1_PA7
  *         @arg @ref LL_PWR_I3CPUCR1_PB2
  *         @arg @ref LL_PWR_I3CPUCR1_PB6
  *         @arg @ref LL_PWR_I3CPUCR1_PB8
  *         @arg @ref LL_PWR_I3CPUCR1_PB9
  *         @arg @ref LL_PWR_I3CPUCR1_PB10
  *         @arg @ref LL_PWR_I3CPUCR1_PB12
  *         @arg @ref LL_PWR_I3CPUCR1_PB13
  *         @arg @ref LL_PWR_I3CPUCR1_PB14
  *         @arg @ref LL_PWR_I3CPUCR1_ALL
  */
__STATIC_INLINE uint32_t LL_PWR_GetI3CPullUpConfig1(void)
{
  return (READ_BIT(PWR->I3CPUCR1, LL_PWR_I3CPUCR1_ALL));
}

/**
  * @brief  Set I3C pull-up configuration for GPIO on port C-D-G-H.
  * @rmtoll I3CPUCR2     PCx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PDx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PGx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PHx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @param  Gpio  This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_I3CPUCR2_PC0
  *         @arg @ref LL_PWR_I3CPUCR2_PC1
  *         @arg @ref LL_PWR_I3CPUCR2_PD12
  *         @arg @ref LL_PWR_I3CPUCR2_PD13
  *         @arg @ref LL_PWR_I3CPUCR2_PG7
  *         @arg @ref LL_PWR_I3CPUCR2_PG8
  *         @arg @ref LL_PWR_I3CPUCR2_PG13
  *         @arg @ref LL_PWR_I3CPUCR2_PG14
  *         @arg @ref LL_PWR_I3CPUCR2_PH3
  *         @arg @ref LL_PWR_I3CPUCR2_ALL
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetI3CPullUpConfig2(uint32_t Gpio)
{
  MODIFY_REG(PWR->I3CPUCR2, LL_PWR_I3CPUCR2_ALL, Gpio);
}

/**
  * @brief  Get I3C pull-up configuration for GPIO on port C-D-G-H.
  * @rmtoll I3CPUCR2     PCx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PDx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PGx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @rmtoll I3CPUCR2     PHx_I3CPU        LL_PWR_GetI3CPullUpConfig2
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_PWR_I3CPUCR2_PC0
  *         @arg @ref LL_PWR_I3CPUCR2_PC1
  *         @arg @ref LL_PWR_I3CPUCR2_PD12
  *         @arg @ref LL_PWR_I3CPUCR2_PD13
  *         @arg @ref LL_PWR_I3CPUCR2_PG7
  *         @arg @ref LL_PWR_I3CPUCR2_PG8
  *         @arg @ref LL_PWR_I3CPUCR2_PG13
  *         @arg @ref LL_PWR_I3CPUCR2_PG14
  *         @arg @ref LL_PWR_I3CPUCR2_PH3
  *         @arg @ref LL_PWR_I3CPUCR2_ALL
  */
__STATIC_INLINE uint32_t LL_PWR_GetI3CPullUpConfig2(void)
{
  return (READ_BIT(PWR->I3CPUCR2, LL_PWR_I3CPUCR2_ALL));
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether the system was in standby mode or not.
  * @rmtoll SR          SBF          LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_SBF) == (PWR_SR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in stop mode or not.
  * @rmtoll SR          STOPF          LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_STOPF) == (PWR_SR_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the EPOD (Embedded Power Distribution) booster is
  *         ready OR not.
  * @rmtoll VOSR   BOOSTRDY       LL_PWR_IsActiveFlag_BOOST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BOOST(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) == (PWR_VOSR_BOOSTRDY)) ? 1UL : 0UL);
}

#if defined(PWR_SVMSR_REGS)
/**
  * @brief  Indicate whether the regulator supply is LDO or SMPS.
  * @rmtoll SVMSR          REGS          LL_PWR_IsActiveFlag_REGULATOR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGULATOR(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS) == (PWR_SVMSR_REGS)) ? 1UL : 0UL);
}
#endif /* PWR_SVMSR_REGS */

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll SVMSR          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO) == (PWR_SVMSR_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDUSB is below the threshold of monitor or not.
  * @rmtoll SVMSR          VDDUSBRDY          LL_PWR_IsActiveFlag_VDDUSB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDUSB(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDUSBRDY) == (PWR_SVMSR_VDDUSBRDY)) ? 1UL : 0UL);
}

#if defined(PWR_SVMSR_VDDIO2RDY)
/**
  * @brief  Indicate whether the VDDIO2 is below the threshold of monitor or not.
  * @rmtoll SVMSR          VDDIO2RDY          LL_PWR_IsActiveFlag_VDDIO2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDIO2(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDIO2RDY) == (PWR_SVMSR_VDDIO2RDY)) ? 1UL : 0UL);
}
#endif /* PWR_SVMSR_VDDIO2RDY */

/**
  * @brief  Indicate whether the VDDA1 is below the threshold of monitor 1 or
  *         not.
  * @rmtoll SVMSR          VDDA1RDY          LL_PWR_IsActiveFlag_VDDA1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDA1(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA1RDY) == (PWR_SVMSR_VDDA1RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDA2 is below the threshold of monitor 2 or
  *         not.
  * @rmtoll SVMSR          VDDA2RDY          LL_PWR_IsActiveFlag_VDDA2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDA2(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA2RDY) == (PWR_SVMSR_VDDA2RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 1.
  * @rmtoll WUSR          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) == (PWR_WUSR_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 2.
  * @rmtoll WUSR          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) == (PWR_WUSR_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 3.
  * @rmtoll WUSR          WUF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF3) == (PWR_WUSR_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 4.
  * @rmtoll WUSR          WUF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) == (PWR_WUSR_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 5.
  * @rmtoll WUSR          WUF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) == (PWR_WUSR_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 6.
  * @rmtoll WUSR          WUF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) == (PWR_WUSR_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 7.
  * @rmtoll WUSR          WUF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) == (PWR_WUSR_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 8.
  * @rmtoll WUSR          WUF8          LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF8) == (PWR_WUSR_WUF8)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 9.
  * @rmtoll WUSR          WUF9          LL_PWR_IsActiveFlag_WU9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU9(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF9) == (PWR_WUSR_WUF9)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up line 10.
  * @rmtoll WUSR          WUF10         LL_PWR_IsActiveFlag_WU10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU10(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF10) == (PWR_WUSR_WUF10)) ? 1UL : 0UL);
}

/**
  * @brief  Clear stop flag.
  * @rmtoll SR          CSSF          LL_PWR_ClearFlag_STOP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}

/**
  * @brief  Clear standby flag.
  * @rmtoll SR          CSSF          LL_PWR_ClearFlag_SB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}

/**
  * @brief  Clear wake up flag 1.
  * @rmtoll WUSCR          CWUF1         LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1);
}

/**
  * @brief  Clear wake up flag 2.
  * @rmtoll WUSCR          CWUF2         LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2);
}

/**
  * @brief  Clear wake up flag 3.
  * @rmtoll WUSCR          CWUF3         LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF3);
}

/**
  * @brief  Clear wake up flag 4.
  * @rmtoll WUSCR          CWUF4         LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4);
}

/**
  * @brief  Clear wake up flag 5.
  * @rmtoll WUSCR          CWUF5         LL_PWR_ClearFlag_WU5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5);
}

/**
  * @brief  Clear wake up flag 6.
  * @rmtoll WUSCR          CWUF6         LL_PWR_ClearFlag_WU6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6);
}

/**
  * @brief  Clear wake up flag 7.
  * @rmtoll WUSCR          CWUF7         LL_PWR_ClearFlag_WU7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7);
}

/**
  * @brief  Clear wake up flag 8.
  * @rmtoll WUSCR          CWUF8         LL_PWR_ClearFlag_WU8
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF8);
}

/**
  * @brief  Clear wake up flag 9.
  * @rmtoll WUSCR          CWUF9         LL_PWR_ClearFlag_WU9
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU9(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF9);
}

/**
  * @brief  Clear wake up flag 10.
  * @rmtoll WUSCR          CWUF10        LL_PWR_ClearFlag_WU10
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU10(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF10);
}

/**
  * @brief  Clear all wake up flags.
  * @rmtoll WUSCR          CWUF         LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  WRITE_REG(PWR->WUSCR, 0x3FFU);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_ATTRIBUTE_MANAGEMENT PWR Attribute Management
  * @{
  */

/**
  * @brief  Enable privileged mode for nsecure items.
  * @rmtoll PRIVCFGR     NSPRIV        LL_PWR_EnableNSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableNSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable privileged mode for nsecure items.
  * @rmtoll PRIVCFGR     NSPRIV          LL_PWR_DisableNSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableNSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if privileged mode for nsecure items is enabled.
  * @rmtoll PRIVCFGR     NSPRIV          LL_PWR_IsEnabledNSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledNSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV) == PWR_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Enable privileged mode for secure items.
  * @rmtoll PRIVCFGR     SPRIV        LL_PWR_EnableSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable privileged mode for secure items.
  * @rmtoll PRIVCFGR     SPRIV          LL_PWR_DisableSecurePrivilege
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Check if privileged mode for secure items is enabled.
  * @rmtoll PRIVCFGR     SPRIV          LL_PWR_IsEnabledSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV) == PWR_PRIVCFGR_SPRIV) ? 1UL : 0UL);
}

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Configure secure attribute mode.
  * @note   This API can be executed only by CPU in secure mode.
  * @rmtoll SECCFGR     WUP1SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP2SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP3SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP4SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP5SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP6SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP7SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP8SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP9SEC       LL_PWR_ConfigSecure\n
  *         SECCFGR     WUP10SEC      LL_PWR_ConfigSecure\n
  *         SECCFGR     LPMSEC        LL_PWR_ConfigSecure\n
  *         SECCFGR     VDMSEC        LL_PWR_ConfigSecure\n
  *         SECCFGR     VBSEC         LL_PWR_ConfigSecure\n
  *         SECCFGR     APCSEC        LL_PWR_ConfigSecure
  * @param  SecureConfig This parameter can be the full combination
  *         of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1_NSEC  or LL_PWR_WAKEUP_LINE1_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE2_NSEC  or LL_PWR_WAKEUP_LINE2_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE3_NSEC  or LL_PWR_WAKEUP_LINE3_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE4_NSEC  or LL_PWR_WAKEUP_LINE4_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE5_NSEC  or LL_PWR_WAKEUP_LINE5_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE6_NSEC  or LL_PWR_WAKEUP_LINE6_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE7_NSEC  or LL_PWR_WAKEUP_LINE7_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE8_NSEC  or LL_PWR_WAKEUP_LINE8_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE9_NSEC  or LL_PWR_WAKEUP_LINE9_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE10_NSEC or LL_PWR_WAKEUP_LINE10_SEC
  *         @arg @ref LL_PWR_LPM_NSEC           or LL_PWR_LPM_SEC
  *         @arg @ref LL_PWR_VDM_NSEC           or LL_PWR_VDM_SEC
  *         @arg @ref LL_PWR_VB_NSEC            or LL_PWR_VB_SEC
  *         @arg @ref LL_PWR_APC_NSEC           or LL_PWR_APC_SEC
  *
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_ConfigSecure(uint32_t SecureConfig)
{
  WRITE_REG(PWR->SECCFGR, SecureConfig);
}
#endif /* defined (CPU_IN_SECURE_STATE) */

/**
  * @brief  Get secure attribute configuration.
  * @note   This API can be executed only by CPU in secure mode.
  * @rmtoll SECCFGR     WUP1SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP2SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP3SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP4SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP5SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP6SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP7SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP8SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP9SEC       LL_PWR_GetConfigSecure\n
  *         SECCFGR     WUP10SEC      LL_PWR_GetConfigSecure\n
  *         SECCFGR     LPMSEC        LL_PWR_GetConfigSecure\n
  *         SECCFGR     VDMSEC        LL_PWR_GetConfigSecure\n
  *         SECCFGR     VBSEC         LL_PWR_GetConfigSecure\n
  *         SECCFGR     APCSEC        LL_PWR_GetConfigSecure
  * @retval Returned value is the combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_LINE1_NSEC  or LL_PWR_WAKEUP_LINE1_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE2_NSEC  or LL_PWR_WAKEUP_LINE2_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE3_NSEC  or LL_PWR_WAKEUP_LINE3_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE4_NSEC  or LL_PWR_WAKEUP_LINE4_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE5_NSEC  or LL_PWR_WAKEUP_LINE5_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE6_NSEC  or LL_PWR_WAKEUP_LINE6_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE7_NSEC  or LL_PWR_WAKEUP_LINE7_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE8_NSEC  or LL_PWR_WAKEUP_LINE8_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE9_NSEC  or LL_PWR_WAKEUP_LINE9_SEC
  *         @arg @ref LL_PWR_WAKEUP_LINE10_NSEC or LL_PWR_WAKEUP_LINE10_SEC
  *         @arg @ref LL_PWR_LPM_NSEC           or LL_PWR_LPM_SEC
  *         @arg @ref LL_PWR_VDM_NSEC           or LL_PWR_VDM_SEC
  *         @arg @ref LL_PWR_VB_NSEC            or LL_PWR_VB_SEC
  *         @arg @ref LL_PWR_APC_NSEC           or LL_PWR_APC_SEC
  */
__STATIC_INLINE uint32_t LL_PWR_GetConfigSecure(void)
{
  return (READ_REG(PWR->SECCFGR));
}
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

#endif /* STM32U3xx_LL_PWR_H */
