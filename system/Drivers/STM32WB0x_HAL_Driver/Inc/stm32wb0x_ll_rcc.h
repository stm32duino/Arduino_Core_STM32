/**
  ******************************************************************************
  * @file    stm32wb0x_ll_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB0x_LL_RCC_H
#define STM32WB0x_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Variables RCC Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Exported_Types RCC Exported Types
  * @{
  */

/** @defgroup LL_ES_CLOCK_FREQ Clocks Frequency Structure
  * @{
 */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t SYSCLK_Frequency;         /*!< SYSCLK clock frequency */
} LL_RCC_ClocksTypeDef;

/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_OSC_VALUES Oscillator Values adaptation
  * @brief    Defines used to adapt values of different oscillators
  * @note     These values could be modified in the user environment according to
  *           HW set-up.
  * @{
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    32000000U  /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    64000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (RC64MPLL_VALUE)
#define RC64MPLL_VALUE    64000000U  /*!< Value of the RC 64 MHz PLL clock in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_CLEAR_FLAG Ready Interrupt Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg LL_RCC_WriteReg function
  * @{
  */
#define LL_RCC_CIFR_LSIRDYF               RCC_CIFR_LSIRDYF     /*!< LSI Ready Interrupt Flag/Clear */
#define LL_RCC_CIFR_LSERDYF               RCC_CIFR_LSERDYF     /*!< LSE Ready Interrupt Flag/Clear */
#define LL_RCC_CIFR_HSIRDYF               RCC_CIFR_HSIRDYF     /*!< HSI Ready Interrupt Flag/Clear */
#define LL_RCC_CIFR_HSERDYF               RCC_CIFR_HSERDYF     /*!< HSE Ready Interrupt Flag/Clear */
#define LL_RCC_CIFR_PLLRDYF               RCC_CIFR_HSIPLLRDYF  /*!< PLL Ready Interrupt Flag/Clear */
#define LL_RCC_CIFR_PLLUNLOCKDETF         RCC_CIFR_HSIPLLUNLOCKDETF  /*!< PLL Unlock Interrupt Flag/Clear        */
#define LL_RCC_CIFR_RTCRSTRELF            RCC_CIFR_RTCRSTF  /*!< RTC Reset Release Interrupt Flag/Clear */
#define LL_RCC_CIFR_WDGRSTRELF            RCC_CIFR_WDGRSTF  /*!< WDG Reset Release Interrupt Flag/Clear */
#if defined(RCC_CIFR_LPURSTF)
#define LL_RCC_CIFR_LPURSTRELF            RCC_CIFR_LPURSTF  /*!< LPUART Reset Release Interrupt Flag/Clear */
#endif

/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Reset Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_RCC_CSR_LOCKUPRSTF              RCC_CSR_LOCKUPRSTF   /*!< CPU lockup reset flag */
#define LL_RCC_CSR_WDGRSTF                 RCC_CSR_WDGRSTF      /*!< Watchdog reset flag */
#define LL_RCC_CSR_SFTRSTF                 RCC_CSR_SFTRSTF      /*!< Software reset flag */
#define LL_RCC_CSR_PORRSTF                 RCC_CSR_PORRSTF      /*!< Power-On or BOR reset flag */
#define LL_RCC_CSR_PADRSTF                 RCC_CSR_PADRSTF      /*!< NRSTn pad reset flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Enable Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_PLLRDYIE               RCC_CIER_HSIPLLRDYIE   /*!< PLL ready interrupt enable */
#define LL_RCC_CIER_HSERDYIE               RCC_CIER_HSERDYIE      /*!< HSE ready interrupt enable */
#define LL_RCC_CIER_HSIRDYIE               RCC_CIER_HSIRDYIE      /*!< HSI ready interrupt enable */
#define LL_RCC_CIER_LSERDYIE               RCC_CIER_LSERDYIE      /*!< LSE ready interrupt enable */
#define LL_RCC_CIER_LSIRDYIE               RCC_CIER_LSIRDYIE      /*!< LSI ready interrupt enable */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0x00000000U             /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_CSSWCR_LSEDRV_0     /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_CSSWCR_LSEDRV_1     /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_CSSWCR_LSEDRV       /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSE_CURRENT_CONTROL  HSE current control max limits
  * @{
  */
#define LL_RCC_HSE_CURRENTMAX_0            0x000000000U                                  /*!< HSE current control max limit = 0.18 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_1            RCC_RFSWHSECR_GMC_0                           /*!< HSE current control max limit = 0.57 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_2            RCC_RFSWHSECR_GMC_1                           /*!< HSE current control max limit = 0.78 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_3            (RCC_RFSWHSECR_GMC_1| RCC_RFSWHSECR_GMC_0)    /*!< HSE current control max limit = 1.13 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_4            RCC_RFSWHSECR_GMC_2                           /*!< HSE current control max limit = 0.61 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_5            (RCC_RFSWHSECR_GMC_2|RCC_RFSWHSECR_GMC_0)     /*!< HSE current control max limit = 1.65 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_6            (RCC_RFSWHSECR_GMC_2|RCC_RFSWHSECR_GMC_1)     /*!< HSE current control max limit = 2.12 mA/V*/
#define LL_RCC_HSE_CURRENTMAX_7            RCC_RFSWHSECR_GMC                             /*!< HSE current control max limit = 2.84 mA/V*/
/**
  * @}
  */

#if defined(RCC_RFSWHSECR_SATRG)
/** @defgroup RCC_LL_EC_HSE_SENSE_AMPLIFIER  HSE sense amplifier threshold
  * @{
  */
#define LL_RCC_HSEAMPTHRESHOLD_1_2         (0x000000000U)                          /*!< HSE sense amplifier bias current factor = 1/2*/
#define LL_RCC_HSEAMPTHRESHOLD_3_4         RCC_RFSWHSECR_SATRG                     /*!< HSE sense amplifier bias current factor = 3/4*/
/**
  * @}
  */
#endif

/** @defgroup RCC_LL_EC_LOCKDET_NSTOP  LOCKDET_NSTOP time selection
  * @{
  */
#define LL_RCC_LOCKDET_NSTOP_0  0x00000000U
#define LL_RCC_LOCKDET_NSTOP_1  RCC_LOCKDET_NSTOP_0
#define LL_RCC_LOCKDET_NSTOP_2  RCC_LOCKDET_NSTOP_1
#define LL_RCC_LOCKDET_NSTOP_3  RCC_LOCKDET_NSTOP_1 | RCC_LOCKDET_NSTOP_0
#define LL_RCC_LOCKDET_NSTOP_4  RCC_LOCKDET_NSTOP_2
#define LL_RCC_LOCKDET_NSTOP_5  RCC_LOCKDET_NSTOP_2 | RCC_LOCKDET_NSTOP_0
#define LL_RCC_LOCKDET_NSTOP_6  RCC_LOCKDET_NSTOP_2 | RCC_LOCKDET_NSTOP_1
#define LL_RCC_LOCKDET_NSTOP_7  RCC_LOCKDET_NSTOP_2 | RCC_LOCKDET_NSTOP_1 | RCC_LOCKDET_NSTOP_0
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Source Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSE             RCC_CFGR_CLKSLOWSEL_0  /*!< LSE selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSI             RCC_CFGR_CLKSLOWSEL_1  /*!< Enable the LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_HSI64M_DIV2048  RCC_CFGR_CLKSLOWSEL    /*!< HSI_64M divided by 2048 selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE_ENABLE  Enable LSCO Clock Source
  * @{
  */
#define LL_RCC_LSCO_LSI          RCC_CR_LSION       /*!< Enable LSI selection for low speed clock  */
#define LL_RCC_LSCO_LSE          RCC_CR_LSEON       /*!< Enable LSE selection for low speed clock  */
#define LL_RCC_LSCO_LSEBYP       RCC_CR_LSEBYP      /*!< Enable LSE clock bypass selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_HSEPLLBUFON Enable the External high speed clock buffer for PLL
  * @{
  */
#define LL_RCC_HSEPLLBUF_OFF     0x00000000U         /*!< Disable the External high speed clock buffer for PLL */
#define LL_RCC_HSEPLLBUF_ON      RCC_CR_HSEPLLBUFON  /*!< Enable the External high speed clock buffer for PLL. Always enabled when the radio is used  */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  Enable HS clock Source
  * @{
  */
#define LL_RCC_SYS_HSI           0x00000000U      /*!< Enable HSI system clock */
#define LL_RCC_SYS_HSE           RCC_CR_HSEON     /*!< Enable HSE system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RF_CLKSOURCE  RF system clock
  * @{
  */
#if defined(RCC_APB2ENR_CLKBLEDIV_0)
#define LL_RCC_RF_CLK_32M       RCC_APB2ENR_CLKBLEDIV_0   /*!< Radio system clock 32 MHz*/
#else
#define LL_RCC_RF_CLK_32M       0x00000000U               /*!< Radio system clock 32 MHz*/
#endif
#if defined(RCC_APB2ENR_CLKBLEDIV_1)
#define LL_RCC_RF_CLK_16M       RCC_APB2ENR_CLKBLEDIV_1   /*!< Radio system clock 16 MHz*/
#else
#define LL_RCC_RF_CLK_16M       RCC_APB2ENR_CLKBLEDIV     /*!< Radio system clock 16 MHz*/
#endif
/**
  * @}
  */

/** @defgroup RCC_DIRECT_HSE_Clock_Divider DIRECT HSE Clock Divider
  * @{
  */
#define LL_RCC_DIRECT_HSE_DIV_1             RCC_CFGR_CLKSYSDIV_0                             /*!< DIRECT HSE division factor = 1   */
#define LL_RCC_DIRECT_HSE_DIV_2             RCC_CFGR_CLKSYSDIV_1                             /*!< DIRECT HSE division factor = 2   */
#define LL_RCC_DIRECT_HSE_DIV_4             (RCC_CFGR_CLKSYSDIV_1 | RCC_CFGR_CLKSYSDIV_0)    /*!< DIRECT HSE division factor = 4   */
#define LL_RCC_DIRECT_HSE_DIV_8             RCC_CFGR_CLKSYSDIV_2                             /*!< DIRECT HSE division factor = 8   */
#define LL_RCC_DIRECT_HSE_DIV_16            (RCC_CFGR_CLKSYSDIV_2 | RCC_CFGR_CLKSYSDIV_0)    /*!< DIRECT HSE division factor = 16  */
#define LL_RCC_DIRECT_HSE_DIV_32            (RCC_CFGR_CLKSYSDIV_2 | RCC_CFGR_CLKSYSDIV_1)    /*!< DIRECT HSE division factor = 32  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  RC64MPLL divider factor to have the System clock
  * @{
  */
#define LL_RCC_RC64MPLL_DIV_1                0x00000000U                                     /*!< RC64MPLL not divided as SYSCLK   */
#define LL_RCC_RC64MPLL_DIV_2                RCC_CFGR_CLKSYSDIV_0                            /*!< RC64MPLL divided by 2 as SYSCLK  */
#define LL_RCC_RC64MPLL_DIV_4                RCC_CFGR_CLKSYSDIV_1                            /*!< RC64MPLL divided by 4 as SYSCLK  */
#define LL_RCC_RC64MPLL_DIV_8                (RCC_CFGR_CLKSYSDIV_1 | RCC_CFGR_CLKSYSDIV_0)   /*!< RC64MPLL divided by 8 as SYSCLK  */
#define LL_RCC_RC64MPLL_DIV_16               RCC_CFGR_CLKSYSDIV_2                            /*!< RC64MPLL divided by 16 as SYSCLK */
#define LL_RCC_RC64MPLL_DIV_32               (RCC_CFGR_CLKSYSDIV_2 | RCC_CFGR_CLKSYSDIV_0)   /*!< RC64MPLL divided by 32 as SYSCLK */
#define LL_RCC_RC64MPLL_DIV_64               (RCC_CFGR_CLKSYSDIV_2 | RCC_CFGR_CLKSYSDIV_1)   /*!< RC64MPLL divided by 64 as SYSCLK */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_SWITCH_DIV  RC64MPLL divider factor to switch the System clock with MR_BLE enabled
  * @{
  */
#define LL_RCC_RC64MPLL_SWITCH_DIV_1                0x00000000U                              /*!< RC64MPLL not divided as SYSCLK   */
#define LL_RCC_RC64MPLL_SWITCH_DIV_2                RCC_CSCMDR_CLKSYSDIV_REQ_0               /*!< RC64MPLL divided by 2 as SYSCLK  */
#define LL_RCC_RC64MPLL_SWITCH_DIV_4                RCC_CSCMDR_CLKSYSDIV_REQ_1               /*!< RC64MPLL divided by 4 as SYSCLK  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_SWITCH_STATUS  Status of the RC64MPLL clock switch  with MR_BLE enabled
  * @{
  */
#define LL_RCC_RC64MPLL_SWITCH_STATUS_IDLE          0x00000000U                              /*!< RC64MPLL Clock Switch Status IDLE    */
#define LL_RCC_RC64MPLL_SWITCH_STATUS_ONGOING       RCC_CSCMDR_STATUS_0                      /*!< RC64MPLL Clock Switch Status ONGOING */
#define LL_RCC_RC64MPLL_SWITCH_STATUS_DONE          RCC_CSCMDR_STATUS_1                      /*!< RC64MPLL Clock Switch Status DONE    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCOSOURCE  MCO SOURCE selection
  * @{
  */
#define LL_RCC_MCOSOURCE_NOCLOCK          0x00000000U                                   /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCOSOURCE_SYSCLK           RCC_CFGR_MCOSEL_0                             /*!< SYSCLK selection as MCO source */
#define LL_RCC_MCOSOURCE_HSI              (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_1)         /*!< HSI selection as MCO source */
#define LL_RCC_MCOSOURCE_RC64MPLL         (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_1)         /*!< RC64MPLL selection as MCO source */
#define LL_RCC_MCOSOURCE_HSE              RCC_CFGR_MCOSEL_2                             /*!< HSE after stabilization selection as MCO source */
#define LL_RCC_MCOSOURCE_HSI64M_DIV2048   (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_2)         /*!< HSI_64M divided by 2048 seelction as MCO source */
#define LL_RCC_MCOSOURCE_SMPS             (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2)         /*!< SMPS selection as MCO source */
#define LL_RCC_MCOSOURCE_ADC              RCC_CFGR_MCOSEL                               /*!< ADC selection as MCO source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO_DIV  MCO prescaler
  * @{
  */
#define LL_RCC_MCO_DIV_1                  0x00000000U                                   /*!< MCO not divided */
#define LL_RCC_MCO_DIV_2                  RCC_CFGR_CCOPRE_0                             /*!< MCO divided by 2 */
#define LL_RCC_MCO_DIV_4                  RCC_CFGR_CCOPRE_1                             /*!< MCO divided by 4 */
#define LL_RCC_MCO_DIV_8                  (RCC_CFGR_CCOPRE_1 | RCC_CFGR_CCOPRE_0)       /*!< MCO divided by 8 */
#define LL_RCC_MCO_DIV_16                 RCC_CFGR_CCOPRE_2                             /*!< MCO divided by 16 */
#define LL_RCC_MCO_DIV_32                 (RCC_CFGR_CCOPRE_2 | RCC_CFGR_CCOPRE_0)       /*!< MCO divided by 32 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCOSOURCE  LCO SOURCE selection
  * @{
  */
#define LL_RCC_LSCOSOURCE_NOCLOCK          0x00000000U                                   /*!< LSCO output disabled, no clock on LSCO          */
#define LL_RCC_LSCOSOURCE_LSI              RCC_CFGR_LCOSEL_1                             /*!< LSI selection as LSCO source                   */
#define LL_RCC_LSCOSOURCE_LSE              (RCC_CFGR_LCOSEL_0|RCC_CFGR_LCOSEL_1)         /*!< LSE selection as LSCO source                   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SMPS_DIV  SMPS prescaler
  * @{
  */
#define LL_RCC_SMPS_DIV_2                  (0x00000000U)                                 /*!< SMPS clock division 2 (SMPS clock is 8 MHz)*/
#define LL_RCC_SMPS_DIV_4                  RCC_CFGR_SMPSDIV                              /*!< SMPS clock division 4 (SMPS clock is 4 MHz)*/
/**
  * @}
  */

#if defined(RCC_CFGR_LPUCLKSEL)
/** @defgroup RCC_LL_CFGR_LPU_CLK  LPUART clock selection
  * @{
  */
#define LL_RCC_LPUCLKSEL_CLK16M            (0x00000000U)                                 /*!< LPUART Clock Selection 16 MHz     */
#define LL_RCC_LPUCLKSEL_CLKLSE            RCC_CFGR_LPUCLKSEL                            /*!< LPUART Clock Selection LSE source */
/**
  * @}
  */
#endif /* RCC_CFGR_LPUCLKSEL */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO         0x00000000U                 /*!< No clock enabled for the peripheral            */
#define LL_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU                 /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

#if defined(SPI2)
/** @defgroup RCC_LL_EC_SPI2_I2S SPI2_I2S
  * @{
  */
#define LL_RCC_SPI2_I2S_CLK16M              0x00000000U              /*!< SPI2 I2S 16 MHz clock source selection bits */
#define LL_RCC_SPI2_I2S_CLK32M              RCC_CFGR_SPI2I2SCLKSEL   /*!< SPI2 I2S 32 MHz clock source selection bits */
/**
  * @}
  */
#endif

/** @defgroup RCC_LL_EC_SPI3_I2S SPI3_I2S
  * @{
  */
#define LL_RCC_SPI3_I2S_CLK16M              0x00000000U              /*!< SPI3 I2S 16 MHz clock source selection bits */
#if !defined(RCC_CFGR_SPI3I2SCLKSEL_0)
#define LL_RCC_SPI3_I2S_CLK32M              RCC_CFGR_SPI3I2SCLKSEL   /*!< SPI3 I2S 32 MHz clock source selection bits */
#endif
#if defined(RCC_CFGR_SPI3I2SCLKSEL_0)
#define LL_RCC_SPI3_I2S_CLK32M              RCC_CFGR_SPI3I2SCLKSEL_0   /*!< SPI3 I2S 32 MHz clock source selection bits */
#define LL_RCC_SPI3_I2S_CLK64M              RCC_CFGR_SPI3I2SCLKSEL_1   /*!< SPI3 I2S 64 MHz clock source selection bits */
#endif
/**
  * @}
  */

#if defined(RCC_CFGR_LPUCLKSEL)
/** @defgroup RCC_LL_EC_LPUART1 LPUART1
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE           0x00000000U               /*!< LPUART1 clock source */
/**
  * @}
  */
#endif /* RCC_CFGR_LPUCLKSEL */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG(RCC->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE crystal oscillator is enabled.
  * @rmtoll CR         HSEON        LL_RCC_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEON) == (RCC_CR_HSEON)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE oscillator Ready
  * @rmtoll CR           HSERDY        LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY)) ? 1UL : 0UL);
}

/**
  * @brief  Set HSE capacitor tuning
  * @rmtoll RFSWHSECR        SWXOTUNE       LL_RCC_HSE_SetCapacitorTuning
  * @param  Value Between Min_Data = 0 and Max_Data = 63
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_SetCapacitorTuning(uint32_t Value)
{
  MODIFY_REG(RCC->RFSWHSECR, RCC_RFSWHSECR_SWXOTUNE, Value << RCC_RFSWHSECR_SWXOTUNE_Pos);
  SET_BIT(RCC->RFSWHSECR, RCC_RFSWHSECR_SWXOTUNEEN);
}

/**
  * @brief  Get HSE capacitor tuning
  * @rmtoll RFSWHSECR        SWXOTUNE      LL_RCC_HSE_GetCapacitorTuning
  * @retval Between Min_Data = 0 and Max_Data = 63
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetCapacitorTuning(void)
{
  return (uint32_t)(READ_BIT(RCC->RFSWHSECR, RCC_RFSWHSECR_SWXOTUNE) >> RCC_RFSWHSECR_SWXOTUNE_Pos);
}

/**
  * @brief  Set HSE current control
  * @rmtoll RFSWHSECR        GMC       LL_RCC_HSE_SetCurrentControl
  * @param  CurrentMax This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_0
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_1
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_2
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_3
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_4
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_5
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_6
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_7
  */
__STATIC_INLINE void LL_RCC_HSE_SetCurrentControl(uint32_t CurrentMax)
{
  MODIFY_REG(RCC->RFSWHSECR, RCC_RFSWHSECR_GMC, CurrentMax);
}

/**
  * @brief  Get HSE current control
  * @rmtoll RFSWHSECR       GMC       LL_RCC_HSE_GetCurrentControl
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_0
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_1
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_2
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_3
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_4
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_5
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_6
  *         @arg @ref LL_RCC_HSE_CURRENTMAX_7
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetCurrentControl(void)
{
  return (uint32_t)(READ_BIT(RCC->RFSWHSECR, RCC_RFSWHSECR_GMC));
}

#if defined(RCC_RFSWHSECR_SATRG)
/**
  * @brief  Set HSE sense amplifier threshold
  * @rmtoll RFSWHSECR        SATRG       LL_RCC_HSE_SetSenseAmplifier
  * @param  SenseAmplifier This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSEAMPTHRESHOLD_1_2
  *         @arg @ref LL_RCC_HSEAMPTHRESHOLD_3_4
  */
__STATIC_INLINE void LL_RCC_HSE_SetSenseAmplifier(uint32_t SenseAmplifier)
{
  MODIFY_REG(RCC->RFSWHSECR, RCC_RFSWHSECR_SATRG, SenseAmplifier);
}

/**
  * @brief  Get HSE current control
  * @rmtoll RFSWHSECR        SATRG       LL_RCC_HSE_GetSenseAmplifier
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSEAMPTHRESHOLD_1_2
  *         @arg @ref LL_RCC_HSEAMPTHRESHOLD_3_4
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetSenseAmplifier(void)
{
  return (uint32_t)(READ_BIT(RCC->RFSWHSECR, RCC_RFSWHSECR_SATRG));
}
#endif

#if defined(RCC_RFSWHSECR_ISTARTUP)
/**
  * @brief  Set HSE startup current
  * @rmtoll RFSWHSECR        ISTARTUP      LL_RCC_HSE_SetStartupCurrent
  * @param  StartupCurrent HSE startup current
  */
__STATIC_INLINE void LL_RCC_HSE_SetStartupCurrent(uint32_t StartupCurrent)
{
  MODIFY_REG_FIELD(RCC->RFSWHSECR, RCC_RFSWHSECR_ISTARTUP, StartupCurrent);
}

/**
  * @brief  Get HSE startup current
  * @rmtoll RFSWHSECR        ISTARTUP       LL_RCC_HSE_GetStartupCurrent
  * @retval Startup Current value
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetStartupCurrent(void)
{
  return (uint32_t)(READ_REG_FIELD(RCC->RFSWHSECR, RCC_RFSWHSECR_ISTARTUP));
}
#endif
#if defined(RCC_RFSWHSECR_AMPLTHRESH)
/**
  * @brief  Set HSE Amplitude Control threshold
  * @rmtoll RFSWHSECR        AMPLTHRESH      LL_RCC_HSE_SetAmplitudeThreshold
  * @param  AmplThr HSE Amplitude Control threshold
  */
__STATIC_INLINE void LL_RCC_HSE_SetAmplitudeThreshold(uint32_t AmplThr)
{
  MODIFY_REG_FIELD(RCC->RFSWHSECR, RCC_RFSWHSECR_AMPLTHRESH, AmplThr);
}

/**
  * @brief  Get HSE Amplitude Control threshold
  * @rmtoll RFSWHSECR        AMPLTHRESH       LL_RCC_HSE_GetAmplitudeThreshold
  * @retval HSE Amplitude Control threshold
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetAmplitudeThreshold(void)
{
  return (uint32_t)(READ_REG_FIELD(RCC->RFSWHSECR, RCC_RFSWHSECR_AMPLTHRESH));
}
#endif
/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI
  * @rmtoll CFGR           STOPHSI        LL_RCC_HSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_STOPHSI);
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_HSESEL);
}

/**
  * @brief  Disable HSI
  * @rmtoll CFGR           STOPHSI        LL_RCC_HSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  SET_BIT(RCC->CFGR, RCC_CFGR_HSESEL);
  SET_BIT(RCC->CFGR, RCC_CFGR_STOPHSI);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll CR           HSIRDY        LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value
  * @note Default value is loaded by HW at reset as soon as the flash controller achieves the reading of the
  *       information in Flash memory (reg. ICSCR).
  * @rmtoll CSSWCR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 127
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_HSITRIMSW, Value << RCC_CSSWCR_HSITRIMSW_Pos);
  SET_BIT(RCC->CSSWCR, RCC_CSSWCR_HSISWTRIMEN);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll ICSCR/CSSWCR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  if ((uint32_t)(READ_BIT(RCC->CSSWCR, RCC_CSSWCR_HSISWTRIMEN)))
  {
    return (uint32_t)(READ_BIT(RCC->CSSWCR, RCC_CSSWCR_HSITRIMSW) >> RCC_CSSWCR_HSITRIMSW_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSITRIM) >> RCC_ICSCR_HSITRIM_Pos);
  }
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_DIRECT_HSE DIRECT_HSE
  * @{
  */
/**
  * @brief  Enable DIRECT_HSE mode
  * @rmtoll CFGR       HSESEL/STOPHSI         LL_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DIRECT_HSE_Enable(void)
{
  while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0);
  SET_BIT(RCC->CFGR, RCC_CFGR_HSESEL);
  for (volatile int i = 0; i < 6; i++)
  {
    __asm("NOP");
  }
  SET_BIT(RCC->CFGR, RCC_CFGR_STOPHSI);
}

/**
  * @brief  Disable DIRECT_HSE
  * @rmtoll CFGR       HSESEL/STOPHSI         LL_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DIRECT_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_STOPHSI);
  while (LL_RCC_HSI_IsReady() == 0);
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_HSESEL);
}

/**
  * @brief  Check if DIRECT_HSE mode is ready
  * @rmtoll CFGR           HSESEL/STOPHSI  LL_RCC_DIRECT_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_DIRECT_HSE_IsEnabled(void)
{
#if defined(RCC_CFGR_HSESEL_STATUS)
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_HSESEL_STATUS) == (RCC_CFGR_HSESEL_STATUS)) ? 1UL : 0UL);
#else
  return (((READ_BIT(RCC->CFGR, RCC_CFGR_HSESEL) == (RCC_CFGR_HSESEL)) && (READ_BIT(RCC->CFGR, RCC_CFGR_STOPHSI) == (RCC_CFGR_STOPHSI))) ? 1UL : 0UL);
#endif
}

#if defined(RCC_CFGR_HSESEL_STATUS)
/**
  * @brief  Get the DIRECT HSE Selection Status
  * @rmtoll CFGR         HSESEL_STATUS     LL_RCC_Get_DIRECT_HSESEL_Status
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_Get_DIRECT_HSESEL_Status(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_HSESEL_STATUS) == (RCC_CFGR_HSESEL_STATUS)) ? 1UL : 0UL);
}
#endif

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LOCKDET_NSTOP LOCKDET_NSTOP
  * @{
  */

/**
  * @brief  Set LOCKDET_NSTOP time
  * @rmtoll CR       LOCKDET_NSTOP          LL_RCC_LOCKDET_NSTOP_SetTime
  * @param  time This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_0
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_1
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_2
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_3
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_4
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_5
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_6
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LOCKDET_NSTOP_SetTime(uint32_t time)
{
  MODIFY_REG(RCC->CR, RCC_CR_LOCKDET_NSTOP, time);
}

/**
  * @brief  Get LOCKDET_NSTOP time
  * @rmtoll CR         LOCKDET_NSTOP     LL_RCC_LOCKDET_NSTOP_GetTime
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_0
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_1
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_2
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_3
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_4
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_5
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_6
  *         @arg @ref LL_RCC_LOCKDET_NSTOP_7
  */
__STATIC_INLINE uint32_t LL_RCC_LOCKDET_NSTOP_GetTime(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_LOCKDET_NSTOP));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll CFGR         CLKSLOWSEL       LL_RCC_LSCO_SetSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_HSI64M_DIV2048
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_CLKSLOWSEL, Source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll CFGR         CLKSLOWSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_HSI64M_DIV2048
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_CLKSLOWSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll CR         LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll CR         LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_LSEON);
}

/**
  * @brief  Check if Low Speed External (LSE) crystal has been enabled or not
  * @rmtoll CR         LSEON         LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_LSEON) == (RCC_CR_LSEON)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll CR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_LSERDY) == (RCC_CR_LSERDY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll CR         LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->CR, RCC_CR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll CR         LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_LSEBYP);
}

/**
  * @brief  Check if LSE bypass configuration is enabled.
  * @rmtoll CR         LSEBYP        LL_RCC_LSE_IsBypassEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsBypassEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_LSEBYP) == (RCC_CR_LSEBYP)) ? 1UL : 0UL);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll CSSWCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll CSSWCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->CSSWCR, RCC_CSSWCR_LSEDRV));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll CR          LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll CR          LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_LSION);
}

/**
  * @brief  Check if LSI crystal oscillator is enabled.
  * @rmtoll CR         LSION        LL_RCC_LSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_LSION) == (RCC_CR_LSION)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll CR          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_LSIRDY) == (RCC_CR_LSIRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSI trimming procedure
  * @rmtoll ICSCR          LSITRIMEN         LL_RCC_LSI_EnableTrimming
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_EnableTrimming(void)
{
  SET_BIT(RCC->ICSCR, RCC_ICSCR_LSITRIMEN);
}

/**
  * @brief  Disable LSI trimming procedure
  * @rmtoll ICSCR          LSITRIMEN         LL_RCC_LSI_DisableTrimming
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_DisableTrimming(void)
{
  CLEAR_BIT(RCC->ICSCR, RCC_ICSCR_LSITRIMEN);
}

/**
  * @brief  Check if LSI trimming procedure is enabled
  * @rmtoll ICSCR          LSITRIMEN        LL_RCC_LSI_IsTrimmingEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsTrimmingEnabled(void)
{
  return ((READ_BIT(RCC->ICSCR, RCC_ICSCR_LSITRIMEN) == (RCC_ICSCR_LSITRIMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set LSI trimming value
  * @note After enabling the LSI oscillator and the LSI trimming procedure
  *       the LSI trimming value is decreased from 15 to 0, till LSITRIMOK raised
  * @rmtoll CSSWCR        LSISWBW       LL_RCC_LSI_SetTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 15
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_SetTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->CSSWCR, RCC_CSSWCR_LSISWBW, Value << RCC_CSSWCR_LSISWBW_Pos);
  SET_BIT(RCC->CSSWCR, RCC_CSSWCR_LSISWTRIMEN);
}

/**
  * @brief  Get LSI trimming value
  * @rmtoll CSSWCR/ICSCR        LSITRIM       LL_RCC_LSI_GetTrimming
  * @retval Between Min_Data = 0 and Max_Data = 15
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_GetTrimming(void)
{
  if (READ_BIT(RCC->CSSWCR, RCC_CSSWCR_LSISWTRIMEN))
  {
    return (uint32_t)(READ_BIT(RCC->CSSWCR, RCC_CSSWCR_LSISWBW) >> RCC_CSSWCR_LSISWBW_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_LSIBW) >> RCC_ICSCR_LSIBW_Pos);
  }
}

#if defined(RCC_ICSCR_LSITRIMOK)
/**
  * @brief  Check if LSI oscillator trimming is OK
  * @rmtoll ICSCR         LSITRIMOK        LL_RCC_LSI_IsTrimmed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsTrimmed(void)
{
  return ((READ_BIT(RCC->ICSCR, RCC_ICSCR_LSITRIMOK) == (RCC_ICSCR_LSITRIMOK)) ? 1UL : 0UL);
}
#endif

/**
  * @}
  */


/** @defgroup RCC_LL_EF_System System Clock
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll CR         HSEON            LL_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_HSI
  *         @arg @ref LL_RCC_SYS_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t Source)
{
  if (Source == LL_RCC_SYS_HSI)
  {
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
  }
  if (Source == LL_RCC_SYS_HSE)
  {
    SET_BIT(RCC->CR, RCC_CR_HSEON);
  }
}

/**
  * @brief  Get the system clock source
  * @rmtoll CR       HSEON      LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_HSI
  *         @arg @ref LL_RCC_SYS_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  if (READ_BIT(RCC->CR, RCC_CR_HSEON))
  {
    return LL_RCC_SYS_HSE;
  }

  return LL_RCC_SYS_HSI;
}

#if defined(RCC_APB2ENR_CLKBLEDIV)
/**
  * @brief  Set the RF clock frequency
  * @rmtoll APB2ENR         CLKBLEDIV          LL_RCC_SetRFClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RF_CLK_16M
  *         @arg @ref LL_RCC_RF_CLK_32M
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRFClock(uint32_t Source)
{
  MODIFY_REG(RCC->APB2ENR, RCC_APB2ENR_CLKBLEDIV, Source);
}

/**
  * @brief  Get the RF clock frequency
  * @rmtoll APB2ENR         CLKBLEDIV          LL_RCC_GetRFClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RF_CLK_16M
  *         @arg @ref LL_RCC_RF_CLK_32M
  */
__STATIC_INLINE uint32_t LL_RCC_GetRFClock(void)
{
  return (uint32_t)(READ_BIT(RCC->APB2ENR, RCC_APB2ENR_CLKBLEDIV));
}
#endif

#if defined(RCC_APB2RSTR_MRBLERST)
/**
    * @brief  Check if Radio System is reset.
    * @rmtoll APB2RSTR    MRBLERST    LL_RCC_IsRFUnderReset
    * @retval State of bit (1 or 0).
    */
__STATIC_INLINE uint32_t LL_RCC_IsRFUnderReset(void)
{
  return ((READ_BIT(RCC->APB2RSTR, RCC_APB2RSTR_MRBLERST) == (RCC_APB2RSTR_MRBLERST)) ? 1UL : 0UL);
}
#endif
/**
  * @}
  */

/** @defgroup RCC_LL_EF_SMPS SMPS
  * @{
  */

/**
  * @brief  Set SMPS prescaler
  * @rmtoll CFGR         SMPSDIV          LL_RCC_SetSMPSPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SMPS_DIV_2
  *         @arg @ref LL_RCC_SMPS_DIV_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSMPSPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SMPSDIV, Prescaler);
}

/**
  * @brief  Get SMPS prescaler
  * @rmtoll CFGR         SMPSDIV          LL_RCC_GetSMPSPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SMPS_DIV_2
  *         @arg @ref LL_RCC_SMPS_DIV_4
  */
__STATIC_INLINE uint32_t LL_RCC_GetSMPSPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SMPSDIV));
}

/**
  * @}
  */

#if defined(RCC_CFGR_LPUCLKSEL)
/** @defgroup RCC_LL_CFGR_LPUCLK_SEL LPUART Clock Selection
  * @{
  */

/**
  * @brief  Set LPUART Clock source
  * @rmtoll CFGR         LPUCLKSEL          LL_RCC_SetLPUARTClockSource
  * @param  Source this parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUCLKSEL_CLK16M
  *         @arg @ref LL_RCC_LPUCLKSEL_CLKLSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_LPUCLKSEL, Source);
}

/**
  * @brief  Get LPUART Clock source
  * @rmtoll CFGR         LPUCLKSEL          LL_RCC_GetLPUARTClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUCLKSEL_CLK16M
  *         @arg @ref LL_RCC_LPUCLKSEL_CLKLSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_LPUCLKSEL));
}

/**
  * @}
  */
#endif /* RCC_CFGR_LPUCLKSEL */

/** @defgroup RCC_LL_EF_MCO_LSCO MCO/LSCO configuration
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR         MCOSEL        LL_RCC_ConfigMCO\n
  *         CFGR         CCOPRE        LL_RCC_ConfigMCO
  * @param  MCOSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCOSOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCOSOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCOSOURCE_HSI
  *         @arg @ref LL_RCC_MCOSOURCE_RC64MPLL
  *         @arg @ref LL_RCC_MCOSOURCE_HSE
  *         @arg @ref LL_RCC_MCOSOURCE_HSI64M_DIV2048
  *         @arg @ref LL_RCC_MCOSOURCE_SMPS
  *         @arg @ref LL_RCC_MCOSOURCE_ADC
  * @param  MCOPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO_DIV_1
  *         @arg @ref LL_RCC_MCO_DIV_2
  *         @arg @ref LL_RCC_MCO_DIV_4
  *         @arg @ref LL_RCC_MCO_DIV_8
  *         @arg @ref LL_RCC_MCO_DIV_16
  *         @arg @ref LL_RCC_MCO_DIV_32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOSource, uint32_t MCOPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCOSEL | RCC_CFGR_CCOPRE, MCOSource | MCOPrescaler);
}

/**
  * @brief  Configure LSCOx
  * @rmtoll CFGR         LCOSEL        LL_RCC_ConfigLSCO
  * @param  LSCOSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCOSOURCE_NOCLOCK
  *         @arg @ref LL_RCC_LSCOSOURCE_LSI
  *         @arg @ref LL_RCC_LSCOSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigLSCO(uint32_t LSCOSource)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_LCOSEL, LSCOSource);
}

#if defined(RCC_CFGR_LCOEN)
/**
  * @brief  LCO enabled on GPIA_Pin_10 also in deepstop
  * @rmtoll CFGR         LCOEN        LL_RCC_LSCOinDeepStop_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCOinDeepStop_Enable(void)
{
  SET_BIT(RCC->CFGR, RCC_CFGR_LCOEN);
}

/**
  * @brief  LCO disabled on GPIA_Pin_10 also in deepstop
  * @rmtoll CFGR         LCOEN        LL_RCC_LSCOinDeepStop_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCOinDeepStop_Disable(void)
{
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_LCOEN);
}

/**
  * @brief  Check if the LCO is enabled on PA10 in deepstop
  * @rmtoll CFGR         LCOEN        LL_RCC_LSCOinDeepStop_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSCOinDeepStop_IsEnabled(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_LCOEN) == (RCC_CFGR_LCOEN)) ? 1UL : 0UL);
}
#endif
/**
  * @}
  */


#if defined( RCC_CFGR_IOBOOSTEN)
/** @defgroup RCC_LL_EF_IOBOOST IOBOOSTER configuration
  * @{
  */
/**
  * @brief  IO BOOSTER enable
  * @rmtoll CFGR         IOBOOSTEN        LL_RCC_IOBOOST_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IOBOOST_Enable(void)
{
  SET_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTEN);
}

/**
  * @brief  IO BOOSTER disable
  * @rmtoll CFGR         IOBOOSTEN        LL_RCC_IOBOOST_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IOBOOST_Disable(void)
{
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTEN);
}

/**
  * @brief  Check if the IO BOOSTER is enabled
  * @rmtoll CFGR         IOBOOSTEN        LL_RCC_IOBOOST_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IOBOOST_IsEnabled(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTEN) == (RCC_CFGR_IOBOOSTEN)) ? 1UL : 0UL);
}

/**
  * @}
  */
#endif

#if defined( RCC_CFGR_IOBOOSTCLKEN)
/** @defgroup RCC_LL_EF_IOBOOSTCLK IOBOOSTER Clock configuration
  * @{
  */

/**
  * @brief  IO BOOSTER clock enable
  * @rmtoll CFGR         IOBOOSTCLKEN        LL_RCC_IOBOOSTCLK_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IOBOOSTCLK_Enable(void)
{
  SET_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTCLKEN);
}

/**
  * @brief  IO BOOSTER clock disable
  * @rmtoll CFGR         IOBOOSTCLKEN        LL_RCC_IOBOOSTCLK_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IOBOOSTCLK_Disable(void)
{
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTCLKEN);
}

/**
  * @brief  Check if the IO BOOSTER clock is enabled
  * @rmtoll CFGR         IOBOOSTCLKEN        LL_RCC_IOBOOSTCLK_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IOBOOSTCLK_IsEnabled(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_IOBOOSTCLKEN) == (RCC_CFGR_IOBOOSTCLKEN)) ? 1UL : 0UL);
}

/**
  * @}
  */
#endif

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

#if defined(SPI2)
/**
  * @brief  Configure SPI2I2S  clock source
  * @rmtoll CFGR        SPI2I2SCLKSEL      LL_RCC_SetSPI2I2SClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI2_I2S_CLK16M
  *         @arg @ref LL_RCC_SPI2_I2S_CLK32M
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2I2SClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SPI2I2SCLKSEL, Source);
}
#endif

/**
  * @brief  Configure SPI3I2S  clock source
  * @rmtoll CFGR        SPI3I2SCLKSEL      LL_RCC_SetSPI3I2SClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI3_I2S_CLK16M
  *         @arg @ref LL_RCC_SPI3_I2S_CLK32M
  *         @arg @ref LL_RCC_SPI3_I2S_CLK64M
  * @retval None
  * @note The LL_RCC_SPI3_I2S_CLK64M is valid for STM32WB05 and STM32WB09 family
  */
__STATIC_INLINE void LL_RCC_SetSPI3I2SClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SPI3I2SCLKSEL, Source);
}

#if defined(SPI2)
/**
  * @brief  Get SPI2I2S clock source
  * @rmtoll CFGR        SPI2I2SCLKSEL    LL_RCC_GetSPI2I2SClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI2_I2S_CLK16M
  *         @arg @ref LL_RCC_SPI2_I2S_CLK32M
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2I2SClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SPI2I2SCLKSEL));
}
#endif

/**
  * @brief  Get SPI3I2S clock source
  * @rmtoll CFGR        SPI3I2SCLKSEL    LL_RCC_GetSPI3I2SClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI3_I2S_CLK16M
  *         @arg @ref LL_RCC_SPI3_I2S_CLK32M
  *         @arg @ref LL_RCC_SPI3_I2S_CLK64M
  * @note The LL_RCC_SPI3_I2S_CLK64M is valid for STM32WB05 and STM32WB09 family
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI3I2SClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SPI3I2SCLKSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Enable RTC
  * @rmtoll APB0ENR         RTCEN         LL_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->APB0ENR, RCC_APB0ENR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll APB0ENR         RTCEN         LL_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->APB0ENR, RCC_APB0ENR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll APB0ENR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->APB0ENR, RCC_APB0ENR_RTCEN) == (RCC_APB0ENR_RTCEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Enable RC64MPLL
  * @rmtoll CR           HSIPLLON         LL_RCC_RC64MPLL_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RC64MPLL_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIPLLON);
}

/**
  * @brief  Disable RC64MPLL
  * @note Cannot be disabled if the RC64MPLL clock is used as the system clock
  * @rmtoll CR           HSIPLLON         LL_RCC_RC64MPLL_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RC64MPLL_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIPLLON);
}

/**
  * @brief  Check if RC64MPLL is Ready
  * @rmtoll CR           HSIPLLRDY        LL_RCC_RC64MPLL_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_RC64MPLL_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIPLLRDY) == (RCC_CR_HSIPLLRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Set RC64MPLL prescaler
  * @rmtoll CFGR       CLKSYSDIV          LL_RCC_SetRC64MPLLPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RC64MPLL_DIV_1
  *         @arg @ref LL_RCC_RC64MPLL_DIV_2
  *         @arg @ref LL_RCC_RC64MPLL_DIV_4
  *         @arg @ref LL_RCC_RC64MPLL_DIV_8
  *         @arg @ref LL_RCC_RC64MPLL_DIV_16
  *         @arg @ref LL_RCC_RC64MPLL_DIV_32
  *         @arg @ref LL_RCC_RC64MPLL_DIV_64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRC64MPLLPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_CLKSYSDIV, Prescaler);
}

/**
  * @brief  Get RC64MPLL prescaler
  * @rmtoll CFGR         CLKSYSDIV     LL_RCC_GetRC64MPLLPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RC64MPLL_DIV_1
  *         @arg @ref LL_RCC_RC64MPLL_DIV_2
  *         @arg @ref LL_RCC_RC64MPLL_DIV_4
  *         @arg @ref LL_RCC_RC64MPLL_DIV_8
  *         @arg @ref LL_RCC_RC64MPLL_DIV_16
  *         @arg @ref LL_RCC_RC64MPLL_DIV_32
  *         @arg @ref LL_RCC_RC64MPLL_DIV_64
  */
__STATIC_INLINE uint32_t LL_RCC_GetRC64MPLLPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_CLKSYSDIV));
}

#if defined(RCC_CFGR_CLKSYSDIV_STATUS)
/**
  * @brief  Get System Clock Prescaler Status
  * @rmtoll CFGR         CLKSYSDIV_STATUS     LL_RCC_GetCLKSYSPrescalerStatus
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RC64MPLL_DIV_1
  *         @arg @ref LL_RCC_RC64MPLL_DIV_2
  *         @arg @ref LL_RCC_RC64MPLL_DIV_4
  *         @arg @ref LL_RCC_RC64MPLL_DIV_8
  *         @arg @ref LL_RCC_RC64MPLL_DIV_16
  *         @arg @ref LL_RCC_RC64MPLL_DIV_32
  *         @arg @ref LL_RCC_RC64MPLL_DIV_64
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_1
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_2
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_4
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_8
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_16
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_32
  */
__STATIC_INLINE uint32_t LL_RCC_GetCLKSYSPrescalerStatus(void)
{
  return (uint32_t)((READ_BIT(RCC->CFGR, RCC_CFGR_CLKSYSDIV_STATUS) >> RCC_CFGR_CLKSYSDIV_STATUS_Pos) << RCC_CFGR_CLKSYSDIV_Pos);
}
#endif

/**
  * @brief  Set DIRECT_HSE prescaler
  * @rmtoll CFGR       CLKSYSDIV          LL_RCC_SetDirectHSEPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_1
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_2
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_4
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_8
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_16
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDirectHSEPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_CLKSYSDIV, Prescaler);
}

/**
  * @brief  Get DIRECT_HSE prescaler
  * @rmtoll CFGR         CLKSYSDIV     LL_RCC_GetDirectHSEPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_1
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_2
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_4
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_8
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_16
  *         @arg @ref LL_RCC_DIRECT_HSE_DIV_32
  */
__STATIC_INLINE uint32_t LL_RCC_GetDirectHSEPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_CLKSYSDIV));
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll CIFR         LSIRDYF       LL_RCC_ClearFlag_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_LSIRDYF);
}

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll CIFR         LSERDYF       LL_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_LSERDYF);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll CIFR         HSIRDYF       LL_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_HSIRDYF);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll CIFR         HSERDYF       LL_RCC_ClearFlag_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_HSERDYF);
}

/**
  * @brief  Clear RC64MPLL ready interrupt flag
  * @rmtoll CIFR         HSIPLLRDYF       LL_RCC_ClearFlag_RC64MPLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_RC64MPLLRDY(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_HSIPLLRDYF);
}

/**
  * @brief  Clear RC64MPLL Unlock Detection interrupt flag
  * @rmtoll CIFR         HSIPLLUNLOCKDETF       LL_RCC_ClearFlag_RC64MPLLUNLOCKDET
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_RC64MPLLUNLOCKDET(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_HSIPLLUNLOCKDETF);
}

/**
  * @brief  Clear RTC Reset Release interrupt flag
  * @rmtoll CIFR         RTCRSTF       LL_RCC_ClearFlag_RTCRRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_RTCRSTREL(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_RTCRSTF);
}

/**
  * @brief  Clear Watchdog Reset Release interrupt flag
  * @rmtoll CIFR         WDGRSTF       LL_RCC_ClearFlag_WDGRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_WDGRSTREL(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_WDGRSTF);
}

#if defined(RCC_CIFR_LPURSTF)
/**
  * @brief  Clear LPUART Reset Release interrupt flag
  * @rmtoll CIFR         LPURSTF       LL_RCC_ClearFlag_LPURSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LPURSTREL(void)
{
  WRITE_REG(RCC->CIFR, RCC_CIFR_LPURSTF);
}
#endif

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == (RCC_CIFR_LSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == (RCC_CIFR_LSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == (RCC_CIFR_HSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == (RCC_CIFR_HSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RC64MPLL ready interrupt occurred or not
  * @rmtoll CIFR         HSIPLLRDYF       LL_RCC_IsActiveFlag_RC64MPLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_RC64MPLLRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIPLLRDYF) == (RCC_CIFR_HSIPLLRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RC64MPLL Unlock Detection flag interrupt occurred or not
  * @rmtoll CIFR         HSIPLLUNLOCKDETF       LL_RCC_IsActiveFlag_RC64MPLLUNLOCKDET
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_RC64MPLLUNLOCKDET(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIPLLUNLOCKDETF) == (RCC_CIFR_HSIPLLUNLOCKDETF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RTC Reset Release flag interrupt occurred or not
  * @rmtoll CIFR         RTCRSTF       LL_RCC_IsActiveFlag_RTCRSTREL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_RTCRSTREL(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_RTCRSTF) == (RCC_CIFR_RTCRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if WDG Reset Release flag interrupt occurred or not
  * @rmtoll CIFR         WDGRSTF       LL_RCC_IsActiveFlag_WDGRSTREL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WDGRSTREL(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_WDGRSTF) == (RCC_CIFR_WDGRSTF)) ? 1UL : 0UL);
}

#if defined(RCC_CIFR_LPURSTF)
/**
  * @brief  Check if LPUART Reset Release flag interrupt occurred or not
  * @rmtoll CIFR         LPURSTF       LL_RCC_IsActiveFlag_LPURSTREL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPURSTREL(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LPURSTF) == (RCC_CIFR_LPURSTF)) ? 1UL : 0UL);
}
#endif


/**
  * @brief  Check if RCC flag CPU lockup reset is set or not.
  * @rmtoll CSR          LOCKUPRSTF      LL_RCC_IsActiveFlag_LOCKUPRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LOCKUPRST(void)
{
  return (((RAM_VR.ResetReason & LL_RCC_CSR_LOCKUPRSTF) == LL_RCC_CSR_LOCKUPRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Watchdog reset is set or not.
  * @rmtoll CSR          WDGRSTF      LL_RCC_IsActiveFlag_WDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WDGRST(void)
{
  return (((RAM_VR.ResetReason & LL_RCC_CSR_WDGRSTF) == LL_RCC_CSR_WDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR          SFTRSTF      LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return (((RAM_VR.ResetReason & LL_RCC_CSR_SFTRSTF) == LL_RCC_CSR_SFTRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Power-On reset is set or not.
  * @rmtoll CSR          PORRSTF      LL_RCC_IsActiveFlag_PORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PORRST(void)
{
  return (((RAM_VR.ResetReason & LL_RCC_CSR_PORRSTF) == LL_RCC_CSR_PORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag NRSTn pad reset is set or not.
  * @rmtoll CSR          PADRSTF      LL_RCC_IsActiveFlag_PADRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PADRST(void)
{
  return (((RAM_VR.ResetReason & LL_RCC_CSR_PADRSTF) == LL_RCC_CSR_PADRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Clear all reset flags.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  RAM_VR.ResetReason = 0;
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_CLK_SWITCH_Management Clock Switch Management
  * @{
  */

/**
  * @brief  Set RC64MPLL prescaler to switch the clock when the MR_BLE is enabled
  * @rmtoll CSCMDR       CLKSYSDIV_REQ          LL_RCC_SwitchRC64MPLLPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_DIV_1
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_DIV_2
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_DIV_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SwitchRC64MPLLPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CSCMDR, RCC_CSCMDR_CLKSYSDIV_REQ, Prescaler);
}

/**
  * @brief  Request the RC64MPLL prescaler to switch the clock when the MR_BLE is enabled
  * @rmtoll CSCMDR       REQUEST          LL_RCC_RequestSwitchRC64MPLLClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RequestSwitchRC64MPLLClock(void)
{
  SET_BIT(RCC->CSCMDR, RCC_CSCMDR_REQUEST);
}

/**
  * @brief  Get RC64MPLL clock switch status
  * @rmtoll CSCMDR        STATUS      LL_RCC_HSE_GetCapacitorTuning
  * @retval The Clock switch status. Possible values are:
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_STATUS_IDLE
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_STATUS_ONGOING
  *         @arg @ref LL_RCC_RC64MPLL_SWITCH_STATUS_DONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetRC64MPLLSwitchStatus(void)
{
  return (uint32_t)(READ_BIT(RCC->CSCMDR, RCC_CSCMDR_STATUS));
}

/**
  * @brief  Enable End of Switch Sequence interrupt
  * @rmtoll CSCMDR         EOFSEQ_IE      LL_RCC_EnableIT_EOFSEQ
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_EOFSEQ(void)
{
  SET_BIT(RCC->CSCMDR, RCC_CSCMDR_EOFSEQ_IE);
}

/**
  * @brief  Disable End of Switch Sequence interrupt
  * @rmtoll CSCMDR         EOFSEQ_IE      LL_RCC_DisableIT_EOFSEQ
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_EOFSEQ(void)
{
  CLEAR_BIT(RCC->CSCMDR, RCC_CSCMDR_EOFSEQ_IE);
}

/**
  * @brief  Checks if End of Switch Sequence interrupt source is enabled or disabled.
  * @rmtoll CSCMDR         EOFSEQ_IE      LL_RCC_IsEnabledIT_EOFSEQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_EOFSEQ(void)
{
  return ((READ_BIT(RCC->CSCMDR, RCC_CSCMDR_EOFSEQ_IE) == (RCC_CSCMDR_EOFSEQ_IE)) ? 1UL : 0UL);
}

/**
  * @brief  Clear End of Sequence interrupt flag
  * @rmtoll CSCMDR         EOFSEQ_IRQ       LL_RCC_ClearFlag_EOFSEQ
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_EOFSEQ(void)
{
  WRITE_REG(RCC->CSCMDR, RCC_CSCMDR_EOFSEQ_IRQ);
}

/**
  * @brief  Check if End of Sequence interrupt occurred or not
  * @rmtoll CSCMDR         EOFSEQ_IRQ       LL_RCC_IsActiveFlag_EOFSEQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_EOFSEQ(void)
{
  return ((READ_BIT(RCC->CSCMDR, RCC_CSCMDR_EOFSEQ_IRQ) == (RCC_CSCMDR_EOFSEQ_IRQ)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_EnableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_EnableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_EnableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Enable RC64MPLL ready interrupt
  * @rmtoll CIER         HSIPLLRDYIE      LL_RCC_EnableIT_RC64MPLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_RC64MPLLRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIPLLRDYIE);
}

/**
  * @brief  Enable RC64MPLL Unlock Detection interrupt
  * @rmtoll CIER         RCC_CIER_HSIPLLUNLOCKDETIE      LL_RCC_EnableIT_RC64MPLLUNLOCKDET
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_RC64MPLLUNLOCKDET(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIPLLUNLOCKDETIE);
}

/**
  * @brief  Enable RTC Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_RTCRSTIE      LL_RCC_EnableIT_RTCRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_RTCRSTREL(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_RTCRSTIE);
}

/**
  * @brief  Enable Watchdog Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_WDGRSTIE      LL_RCC_EnableIT_WDGRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_WDGRSTREL(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_WDGRSTIE);
}

#if defined(RCC_CIER_LPURSTIE)
/**
  * @brief  Enable LPUART Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_LPURSTIE      LL_RCC_EnableIT_LPURSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LPURSTREL(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LPURSTIE);
}
#endif

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_DisableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Disable RC64MPLL ready interrupt
  * @rmtoll CIER         HSIPLLRDYIE      LL_RCC_DisableIT_RC64MPLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_RC64MPLLRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIPLLRDYIE);
}

/**
  * @brief  Disable RC64MPLL Unlock Detection interrupt
  * @rmtoll CIER         RCC_CIER_HSIPLLUNLOCKDETIE      LL_RCC_DisableIT_RC64MPLLUNLOCKDET
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_RC64MPLLUNLOCKDET(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIPLLUNLOCKDETIE);
}

/**
  * @brief  Disable RTC Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_RTCRSTIE      LL_RCC_DisableIT_RTCRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_RTCRSTREL(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_RTCRSTIE);
}

/**
  * @brief  Disable Watchdog Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_WDGRSTIE      LL_RCC_DisableIT_WDGRSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_WDGRSTREL(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_WDGRSTIE);
}

#if defined(RCC_CIER_LPURSTIE)
/**
  * @brief  Disable LPUART Reset Release interrupt
  * @rmtoll CIER         RCC_CIER_LPURSTIE      LL_RCC_DisableIT_LPURSTREL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LPURSTREL(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LPURSTIE);
}
#endif

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == (RCC_CIER_LSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == (RCC_CIER_LSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == (RCC_CIER_HSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == (RCC_CIER_HSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if RC64MPLL ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIPLLRDYIE      LL_RCC_IsEnabledIT_RC64MPLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_RC64MPLLRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIPLLRDYIE) == (RCC_CIER_HSIPLLRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if RC64MPLL Unlock Detection interrupt source is enabled or disabled.
  * @rmtoll CIER         RCC_CIER_HSIPLLUNLOCKDETIE      LL_RCC_IsEnabledIT_RC64MPLLUNLOCKDET
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_RC64MPLLUNLOCKDET(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIPLLUNLOCKDETIE) == (RCC_CIER_HSIPLLUNLOCKDETIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if RTC Reset Release interrupt source is enabled or disabled.
  * @rmtoll CIER         RCC_CIER_RTCRSTIE      LL_RCC_IsEnabledIT_RTCRSTREL
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_RTCRSTREL(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_RTCRSTIE) == (RCC_CIER_RTCRSTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if Watchdog Reset Release interrupt source is enabled or disabled.
  * @rmtoll CIER         RCC_CIER_WDGRSTIE      LL_RCC_IsEnabledIT_WDGRSTREL
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_WDGRSTREL(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_WDGRSTIE) == (RCC_CIER_WDGRSTIE)) ? 1UL : 0UL);
}

#if defined(RCC_CIER_LPURSTIE)
/**
  * @brief  Checks if LPUART Reset Release interrupt source is enabled or disabled.
  * @rmtoll CIER         RCC_CIER_LPURSTIE      LL_RCC_IsEnabledIT_LPURSTREL
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LPURSTREL(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LPURSTIE) == (RCC_CIER_LPURSTIE)) ? 1UL : 0UL);
}
#endif


/**
  * @}
  */

/** @defgroup RCC_LL_HSEPLL_BUFFER_RF External high speed clock buffer for PLL RF2G4
  * @{
  */

/**
  * @brief  Enable high speed clock buffer for PLL RF2G4
  * @rmtoll CR           HSEPLLBUFON     LL_RCC_HSEPLLBUFON_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEPLLBUFON_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEPLLBUFON);
}

/**
  * @brief  Disable high speed clock buffer for PLL RF2G4
  * @rmtoll CR           HSEPLLBUFON         LL_RCC_HSEPLLBUFON_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEPLLBUFON_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEPLLBUFON);
}

/**
  * @brief  Check if the high speed clock buffer for PLL RF2G4 is enabled.
  * @rmtoll CR         HSEPLLBUFON        LL_RCC_HSEPLLBUFON_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSEPLLBUFON_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEPLLBUFON) == (RCC_CR_HSEPLLBUFON)) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks);
uint32_t    LL_RCC_GetSMPSClockFreq(void);
#if defined(RCC_CFGR_LPUCLKSEL)
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
#endif /* RCC_CFGR_LPUCLKSEL */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32WB0x_LL_RCC_H */
