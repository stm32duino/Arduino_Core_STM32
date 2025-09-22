/**
  ******************************************************************************
  * @file    stm32u0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
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
#ifndef STM32U0xx_HAL_PWR_EX_H
#define STM32U0xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u0xx_hal_def.h"

/** @addtogroup STM32U0xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */

/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWREx_PVM_Type.
                           @arg @ref PWR_PVM_1 Peripheral Voltage Monitoring USB enable: VDDUSB versus 1.2 V
                           (applicable when USB feature is supported).
                           @arg @ref PWR_PVM_3 Peripheral Voltage Monitoring ADC enable: VDDA versus 1.62 V.
                           @arg @ref PWR_PVM_4 Peripheral Voltage Monitoring DAC enable: VDDA versus 2.2 V. */

  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWREx_PVM_Mode. */
} PWR_PVMTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_WUP_Polarity Shift to apply to retrieve polarity information from PWR_WAKEUP_PINy_xxx constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT       0x07U      /*!< Internal constant used to retrieve wakeup pin polarity */
/**
  * @}
  */

/** @defgroup PWREx_WakeUp_Pins  PWR wake-up pins
  * @{
  */
#define PWR_WAKEUP_PIN1              PWR_CR3_EWUP1                                                     /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2              PWR_CR3_EWUP2                                                     /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3              PWR_CR3_EWUP3                                                     /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN4              PWR_CR3_EWUP4                                                     /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN5              PWR_CR3_EWUP5                                                     /*!< Wakeup pin 5 (with high level polarity) */
#define PWR_WAKEUP_PIN7              PWR_CR3_EWUP7                                                     /*!< Wakeup pin 7 (with high level polarity) */
#define PWR_WAKEUP_PIN1_HIGH         PWR_CR3_EWUP1                                                     /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2_HIGH         PWR_CR3_EWUP2                                                     /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3_HIGH         PWR_CR3_EWUP3                                                     /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN4_HIGH         PWR_CR3_EWUP4                                                     /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN5_HIGH         PWR_CR3_EWUP5                                                     /*!< Wakeup pin 5 (with high level polarity) */
#define PWR_WAKEUP_PIN7_HIGH         PWR_CR3_EWUP7                                                     /*!< Wakeup pin 7 (with high level polarity) */
#define PWR_WAKEUP_PIN1_LOW          (uint32_t)((PWR_CR4_WP1<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP1) /*!< Wakeup pin 1 (with low level polarity)  */
#define PWR_WAKEUP_PIN2_LOW          (uint32_t)((PWR_CR4_WP2<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP2) /*!< Wakeup pin 2 (with low level polarity)  */
#define PWR_WAKEUP_PIN3_LOW          (uint32_t)((PWR_CR4_WP3<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP3) /*!< Wakeup pin 3 (with low level polarity)  */
#define PWR_WAKEUP_PIN4_LOW          (uint32_t)((PWR_CR4_WP4<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP4) /*!< Wakeup pin 4 (with low level polarity)  */
#define PWR_WAKEUP_PIN5_LOW          (uint32_t)((PWR_CR4_WP5<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP5) /*!< Wakeup pin 5 (with low level polarity)  */
#define PWR_WAKEUP_PIN7_LOW          (uint32_t)((PWR_CR4_WP7<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP7) /*!< Wakeup pin 7 (with low level polarity)  */
/**
  * @}
  */

/** @defgroup PWREx_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#if defined(USB_DRD_FS)
#define PWR_PVM_1                PWR_CR2_PVME1     /*!< Peripheral Voltage Monitoring 1 enable: VDDUSB versus 1.2 V (applicable when USB feature is supported) */
#endif /* USB_DRD_FS */
#define PWR_PVM_3                PWR_CR2_PVME3     /*!< Peripheral Voltage Monitoring 3 enable: VDDA versus 1.62 V */
#define PWR_PVM_4                PWR_CR2_PVME4     /*!< Peripheral Voltage Monitoring 4 enable: VDDA versus 2.2 V  */
/**
  * @}
  */

/** @defgroup PWREx_PVM_Mode  PWR PVM interrupt and event mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL                   0x00000000U       /*!< basic mode is used  */
#define PWR_PVM_MODE_IT_RISING                0x00010001U       /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_IT_FALLING               0x00010002U       /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_IT_RISING_FALLING        0x00010003U       /*!< External Interrupt Mode with Rising/Falling edge trigger detection   */
#define PWR_PVM_MODE_EVENT_RISING             0x00020001U       /*!< Event Mode with Rising edge trigger detection  */
#define PWR_PVM_MODE_EVENT_FALLING            0x00020002U       /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING_FALLING     0x00020003U       /*!< Event Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */

/** @defgroup PWREx_Flash_PowerDown  Flash Power Down modes
  * @{
  */
#define PWR_FLASHPD_LPRUN                 PWR_CR1_FPD_LPRUN     /*!< Enable Flash power down in low power run mode   */
#define PWR_FLASHPD_LPSLEEP               PWR_CR1_FPD_LPSLP     /*!< Enable Flash power down in low power sleep mode */
#define PWR_FLASHPD_STOP                  PWR_CR1_FPD_STOP      /*!< Enable Flash power down in stop mode            */
/**
  * @}
  */

/** @defgroup PWREx_Regulator_Voltage_Scale  PWR Regulator voltage scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1          PWR_CR1_VOS_0        /*!< Voltage scaling range 1 normal mode */
#define PWR_REGULATOR_VOLTAGE_SCALE2          PWR_CR1_VOS_1        /*!< Voltage scaling range 2             */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging_Selection PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5       0U                  /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5     PWR_CR4_VBRS        /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging PWR battery charging
  * @{
  */
#define PWR_BATTERY_CHARGING_DISABLE        0U                  /*!< VBAT charging disable  */
#define PWR_BATTERY_CHARGING_ENABLE         PWR_CR4_VBE         /*!< VBAT charging enable   */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number for I/O setting in standby/shutdown mode
  * @{
  */
#define PWR_GPIO_BIT_0                      PWR_PUCRA_PU0          /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1                      PWR_PUCRA_PU1          /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2                      PWR_PUCRA_PU2          /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3                      PWR_PUCRA_PU3          /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4                      PWR_PUCRA_PU4          /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5                      PWR_PUCRA_PU5          /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6                      PWR_PUCRA_PU6          /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7                      PWR_PUCRA_PU7          /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8                      PWR_PUCRA_PU8          /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9                      PWR_PUCRA_PU9          /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10                     PWR_PUCRA_PU10         /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11                     PWR_PUCRA_PU11         /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12                     PWR_PUCRA_PU12         /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13                     PWR_PUCRA_PU13         /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14                     PWR_PUCRA_PU14         /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15                     PWR_PUCRA_PU15         /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A                            0x00000000U        /*!< GPIO port A */
#define PWR_GPIO_B                            0x00000001U        /*!< GPIO port B */
#define PWR_GPIO_C                            0x00000002U        /*!< GPIO port C */
#define PWR_GPIO_D                            0x00000003U        /*!< GPIO port D */
#if defined (GPIOE)
#define PWR_GPIO_E                            0x00000004U        /*!< GPIO port E */
#endif /* GPIOE */
#define PWR_GPIO_F                            0x00000005U        /*!< GPIO port F */
/**
  * @}
  */

/** @defgroup PWREx_PVM_EXTI_LINE PWR PVM external interrupts lines
  * @{
  */
#if defined(USB_DRD_FS)
#define PWR_EXTI_LINE_PVM1       0x00100000U     /*!< External interrupt line 19 Connected to the PVM USB EXTI Line */
#endif /* USB_DRD_FS */
#define PWR_EXTI_LINE_PVM3       0x00200000U     /*!< External interrupt line 20 Connected to the PVM ADC EXTI Line  */
#define PWR_EXTI_LINE_PVM4       0x00400000U     /*!< External interrupt line 21 Connected to the PVM DAC EXTI Line  */
/**
  * @}
  */

/** @defgroup PWREx_PVM_EVENT_LINE PWR PVM event lines
  * @{
  */
#if defined(USB_DRD_FS)
#define PWR_EVENT_LINE_PVM1                  0x00100000U      /*!< Event line 19 Connected to the PVM USB EXTI Line */
#endif /* USB_DRD_FS */
#define PWR_EVENT_LINE_PVM3                  0x00200000U      /*!< Event line 20 Connected to the PVM ADC EXTI Line */
#define PWR_EVENT_LINE_PVM4                  0x00400000U      /*!< Event line 21 Connected to the PVM DAC EXTI Line */
/**
  * @}
  */

/** @defgroup PWREx_Flag  PWR Status Flags
  *        Elements values convention: 0000 00XX 000Y YYYYb
  *           - Y YYYY  : Flag position in the XX register (5 bits)
  *           - XX  : Status register (2 bits)
  *                 - 01: SR1 register
  *                 - 10: SR2 register
  *        The only exception is PWR_FLAG_WU, encompassing all
  *        wake-up flags and set to PWR_SR1_WUF.
  * @{
  */
#define PWR_FLAG_WUF1                        0x0100U             /*!< Wakeup event on wakeup pin 1              */
#define PWR_FLAG_WUF2                        0x0101U             /*!< Wakeup event on wakeup pin 2              */
#define PWR_FLAG_WUF3                        0x0102U             /*!< Wakeup event on wakeup pin 3              */
#define PWR_FLAG_WUF4                        0x0103U             /*!< Wakeup event on wakeup pin 4              */
#define PWR_FLAG_WUF5                        0x0104U             /*!< Wakeup event on wakeup pin 5              */
#define PWR_FLAG_WUF7                        0x0106U             /*!< Wakeup event on wakeup pin 7              */
#define PWR_FLAG_WU                          0x5FUL              /*!< Encompass wakeup event on all wakeup pins */
#define PWR_FLAG_SB                          0x0108U             /*!< Standby flag                              */
#define PWR_FLAG_STOP0                       0x010BU             /*!< Stop0 flag                                */
#define PWR_FLAG_STOP1                       0x0109U             /*!< Stop1 flag                                */
#define PWR_FLAG_STOP2                       0x010AU             /*!< Stop2 flag                                */
#define PWR_FLAG_WUFI                        0x010FU             /*!< Wakeup on internal wakeup line            */
#define PWR_FLAG_FLASHRDY                    0x0207U             /*!< flash ready flag                          */
#define PWR_FLAG_REGLPS                      0x0208U             /*!< Low-power regulator start flag            */
#define PWR_FLAG_REGLPF                      0x0209U             /*!< Low-power regulator flag                  */
#define PWR_FLAG_VOSF                        0x020AU             /*!< Voltage scaling flag                      */
#define PWR_FLAG_PVDO                        0x020BU             /*!< Power Voltage Detector output flag        */
#define PWR_FLAG_PVMO_USB                    0x020CU             /*!< Power Voltage Monitoring 1 output flag    */
#define PWR_FLAG_PVMO_ADC                    0x020EU             /*!< Power Voltage Monitoring 3 output flag    */
#define PWR_FLAG_PVMO_DAC                    0x020FU             /*!< Power Voltage Monitoring 4 output flag    */
#define PWR_SCR_CWUF                         0x005FU             /*!< Clear Wake-up Flags                       */
/**
  * @}
  */

/** @defgroup PWREx_SRAM_Retention PWR SRAM Retention in Standby mode
  * @{
  */
#define PWR_NO_SRAM_RETENTION       0U           /*!< SRAM is powered off in Standby mode (SRAM content is lost) */
#define PWR_FULL_SRAM_RETENTION     PWR_CR3_RRS  /*!< Full SRAM is powered by the low-power regulator in Standby mode */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWR Extended Exported Macros
  * @{
  */
#if defined(USB_DRD_FS)
/**
  * @brief Enable the PVM USB Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM USB Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM USB Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM1)

/**
  * @brief Disable the PVM USB Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM1)

/**
  * @brief Enable the PVM1 USB Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM USB Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM USB Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM USB Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM1)

/**
  * @brief  PVM USB EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_FALLING_EDGE()     \
  do {                                                       \
    __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE();                \
    __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE();               \
  } while(0)

/**
  * @brief Disable the PVM USB Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM1)

/**
  * @brief Check whether the specified PVM USB EXTI Rising interrupt flag is set or not.
  * @retval EXTI PVM_USB Line Status.
  */

#define __HAL_PWR_PVM1_EXTI_GET_RISING_FLAG() ((READ_BIT(EXTI->RPR1, PWR_EXTI_LINE_PVM1)\
                                                == PWR_EXTI_LINE_PVM1) ? 1UL : 0UL)

/**
  * @brief Check whether the specified PVM USB Falling EXTI interrupt flag is set or not.
  * @retval EXTI PVM USB Line Status.
  */
#define __HAL_PWR_PVM1_EXTI_GET_FALLING_FLAG() ((READ_BIT(EXTI->FPR1, PWR_EXTI_LINE_PVM1)\
                                                 == PWR_EXTI_LINE_PVM1) ? 1UL : 0UL)

/**
  * @brief Clear the PVM USB EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_CLEAR_FLAG()       \
  do                                           \
  {                                            \
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM1); \
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM1); \
  } while(0)
#endif /* USB_DRD_FS */

/**
  * @brief Enable the PVM ADC Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM ADC Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM ADC Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM3)

/**
  * @brief Disable the PVM ADC Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM3)

/**
  * @brief Enable the PVM ADC Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM ADC Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM ADC Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM ADC Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM3)

/**
  * @brief  PVM ADC EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM ADC Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM3)

/**
  * @brief Check whether the specified PVM ADC EXTI Rising interrupt flag is set or not.
  * @retval EXTI PVM ADC Line Status.
  */

#define __HAL_PWR_PVM3_EXTI_GET_RISING_FLAG() ((READ_BIT(EXTI->RPR1, PWR_EXTI_LINE_PVM3)\
                                                == PWR_EXTI_LINE_PVM3) ? 1UL : 0UL)

/**
  * @brief Check whether the specified PVM ADC EXTI Falling interrupt flag is set or not.
  * @retval EXTI PVM ADC Line Status.
  */

#define __HAL_PWR_PVM3_EXTI_GET_FALLING_FLAG() ((READ_BIT(EXTI->FPR1, PWR_EXTI_LINE_PVM3)\
                                                 == PWR_EXTI_LINE_PVM3) ? 1UL : 0UL)

/**
  * @brief Clear the PVM_ADC EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_CLEAR_FLAG()       \
  do                                           \
  {                                            \
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM3); \
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM3); \
  } while(0)

/**
  * @brief Enable the PVM DAC Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM DAC Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM DAC Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM4)

/**
  * @brief Disable the PVM DAC Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVM4)

/**
  * @brief Enable the PVM DAC Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM DAC Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM DAC Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM DAC Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVM4)

/**
  * @brief  PVM3 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM_DAC Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVM4)

/**
  * @brief Check whether the specified PVM DAC EXTI Rising interrupt flag is set or not.
  * @retval EXTI PVM DAC Line Status.
  */

#define __HAL_PWR_PVM4_EXTI_GET_RISING_FLAG() ((READ_BIT(EXTI->RPR1, PWR_EXTI_LINE_PVM4)\
                                                == PWR_EXTI_LINE_PVM4) ? 1UL : 0UL)

/**
  * @brief Check whether the specified PVM DAC EXTI Falling interrupt flag is set or not.
  * @retval EXTI PVM DAC Line Status.
  */

#define __HAL_PWR_PVM4_EXTI_GET_FALLING_FLAG() ((READ_BIT(EXTI->FPR1, PWR_EXTI_LINE_PVM4)\
                                                 == PWR_EXTI_LINE_PVM4) ? 1UL : 0UL)

/**
  * @brief  Clear the PVM DAC EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_CLEAR_FLAG()       \
  do                                           \
  {                                            \
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVM4); \
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVM4); \
  } while(0)

/**
  * @brief Configure the main internal regulator output voltage.
  * @param  __REGULATOR__ specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1  Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 80 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2  Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 26 MHz.
  * @note  This macro is similar to HAL_PWREx_ControlVoltageScaling() API but doesn't check
  *        whether or not VOSF flag is cleared when moving from range 2 to range 1. User
  *        may resort to __HAL_PWR_GET_FLAG() macro to check VOSF bit resetting.
  * @retval None
  */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg;                               \
                                                            MODIFY_REG(PWR->CR1, PWR_CR1_VOS, (__REGULATOR__)); \
                                                            /* Delay after an RCC peripheral clock enabling */  \
                                                            tmpreg = READ_BIT(PWR->CR1, PWR_CR1_VOS);           \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0)

/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1)      || \
                                ((PIN) == PWR_WAKEUP_PIN2)      || \
                                ((PIN) == PWR_WAKEUP_PIN3)      || \
                                ((PIN) == PWR_WAKEUP_PIN4)      || \
                                ((PIN) == PWR_WAKEUP_PIN5)      || \
                                ((PIN) == PWR_WAKEUP_PIN7)      || \
                                ((PIN) == PWR_WAKEUP_PIN1_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN5_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN7_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN1_LOW)  || \
                                ((PIN) == PWR_WAKEUP_PIN2_LOW)  || \
                                ((PIN) == PWR_WAKEUP_PIN3_LOW)  || \
                                ((PIN) == PWR_WAKEUP_PIN4_LOW)  || \
                                ((PIN) == PWR_WAKEUP_PIN5_LOW)  || \
                                ((PIN) == PWR_WAKEUP_PIN7_LOW))
#if defined(USB_DRD_FS)
#define IS_PWR_PVM_TYPE(TYPE) (((TYPE) == PWR_PVM_1) ||\
                               ((TYPE) == PWR_PVM_3) ||\
                               ((TYPE) == PWR_PVM_4))
#else
#define IS_PWR_PVM_TYPE(TYPE) (((TYPE) == PWR_PVM_3) ||\
                               ((TYPE) == PWR_PVM_4))
#endif /* USB_DRD_FS */
#define IS_PWR_PVM_MODE(MODE)  (((MODE) == PWR_PVM_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING)           ||\
                                ((MODE) == PWR_PVM_MODE_IT_FALLING)          ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING_FALLING)   ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING)        ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_FALLING)       ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING_FALLING))

#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE) (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))

#define IS_PWR_BATTERY_RESISTOR_SELECT(RESISTOR) (((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                  ((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

#define IS_PWR_BATTERY_CHARGING(CHARGING) (((CHARGING) == PWR_BATTERY_CHARGING_DISABLE) ||\
                                           ((CHARGING) == PWR_BATTERY_CHARGING_ENABLE))

#if defined (GPIOE)
#define IS_PWR_GPIO_PORT(GPIO_PORT)       (((GPIO_PORT) == PWR_GPIO_A) ||\
                                           ((GPIO_PORT) == PWR_GPIO_B) ||\
                                           ((GPIO_PORT) == PWR_GPIO_C) ||\
                                           ((GPIO_PORT) == PWR_GPIO_D) ||\
                                           ((GPIO_PORT) == PWR_GPIO_E) ||\
                                           ((GPIO_PORT) == PWR_GPIO_F))
#else
#define IS_PWR_GPIO_PORT(GPIO_PORT)       (((GPIO_PORT) == PWR_GPIO_A) ||\
                                           ((GPIO_PORT) == PWR_GPIO_B) ||\
                                           ((GPIO_PORT) == PWR_GPIO_C) ||\
                                           ((GPIO_PORT) == PWR_GPIO_D) ||\
                                           ((GPIO_PORT) == PWR_GPIO_F))
#endif /* GPIOE */

#define IS_PWR_GPIO_PIN_MASK(BIT_MASK)      ((((BIT_MASK) & GPIO_PIN_MASK) != 0U) && ((BIT_MASK) <= GPIO_PIN_MASK))

#define IS_PWR_FLASH_POWERDOWN(__MODE__)    ((((__MODE__) & (PWR_FLASHPD_LPRUN   |                              \
                                                             PWR_FLASHPD_LPSLEEP | PWR_FLASHPD_STOP)) != 0U) && \
                                             (((__MODE__) & ~(PWR_FLASHPD_LPRUN   |                             \
                                                              PWR_FLASHPD_LPSLEEP | PWR_FLASHPD_STOP)) == 0U))
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
uint32_t          HAL_PWREx_GetVoltageRange(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @{
  */
void              HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
void              HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry);
void              HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group3 Voltage Monitoring Functions
  * @{
  */
void              HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void              HAL_PWREx_DisableBatteryCharging(void);
#if defined(USB_DRD_FS)
void              HAL_PWREx_EnablePVM1(void);
void              HAL_PWREx_DisablePVM1(void);
#endif /* USB_DRD_FS */
void              HAL_PWREx_EnablePVM3(void);
void              HAL_PWREx_DisablePVM3(void);
void              HAL_PWREx_EnablePVM4(void);
void              HAL_PWREx_DisablePVM4(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(const PWR_PVMTypeDef *sConfigPVM);
#if defined(USB_DRD_FS)
void              HAL_PWREx_EnableVddUSB(void);
void              HAL_PWREx_DisableVddUSB(void);
#endif /* USB_DRD_FS */
void              HAL_PWREx_PVD_PVM_IRQHandler(void);
#if defined(USB_DRD_FS)
void              HAL_PWREx_PVM1_Callback(void);
#endif /* USB_DRD_FS */
void              HAL_PWREx_PVM3_Callback(void);
void              HAL_PWREx_PVM4_Callback(void);
void              HAL_PWREx_EnableInternalWakeUpLine(void);
void              HAL_PWREx_DisableInternalWakeUpLine(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group4 Memories Retention Functions
  * @{
  */
void              HAL_PWREx_EnableSRAMContentRetention(void);
void              HAL_PWREx_DisableSRAMContentRetention(void);
void              HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_EnableUltraLowPowerMode(void);
void              HAL_PWREx_DisableUltraLowPowerMode(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group5 I/O Pull-Up Pull-Down Configuration Functions
  * @{
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);
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

#endif /* STM32U0xx_HAL_PWR_EX_H */
