#ifndef __STM32YYxx_HAL_CONF_H
#define __STM32YYxx_HAL_CONF_H

#if defined(USE_HALV2_DRIVER)
  /*
  * Mandatory HALv2 modules
  */
  #define USE_HAL_CORTEX_MODULE                   1U
  #define USE_HAL_EXTI_MODULE                     1U
  #define USE_HAL_FLASH_MODULE                    1U
  #define USE_HAL_GPIO_MODULE                     1U
  #define USE_HAL_RCC_MODULE                      1U
  #define USE_HAL_PWR_MODULE                      1U

  /* Legacy compatibility macros */
  /*
  * Optional HAL modules, can be enabled/disabled using
  * variant.h, build_opt.h or hal_conf_extra.h
  */
  #if defined(HAL_ADC_MODULE_DISABLED)
    #if defined(USE_HAL_ADC_MODULE)
      #undef USE_HAL_ADC_MODULE
    #endif
    #define USE_HAL_ADC_MODULE                    0U
  #else
    #define USE_HAL_ADC_MODULE                    1U
  #endif

  #if defined(HAL_CRC_MODULE_DISABLED)
    #if defined(USE_HAL_CRC_MODULE)
      #undef USE_HAL_CRC_MODULE
    #endif
    #define USE_HAL_CRC_MODULE                    0U
  #else
    #define USE_HAL_CRC_MODULE                    1U
  #endif

  #if defined(HAL_I2C_MODULE_DISABLED)
    #if defined(USE_HAL_I2C_MODULE)
      #undef USE_HAL_I2C_MODULE
    #endif
    #define USE_HAL_I2C_MODULE                    0U
  #else
    #define USE_HAL_I2C_MODULE                    1U
    #define USE_HAL_I2C_GET_LAST_ERRORS           1U
  #endif

  #if defined(HAL_I2S_MODULE_DISABLED)
    #if defined(USE_HAL_I2S_MODULE)
      #undef USE_HAL_I2S_MODULE
    #endif
    #define USE_HAL_I2S_MODULE                    0U
  #else
    #define USE_HAL_I2S_MODULE                    1U
  #endif

  #if defined(HAL_I3C_MODULE_DISABLED)
    #if defined(USE_HAL_I3C_MODULE)
      #undef USE_HAL_I3C_MODULE
    #endif
    #define USE_HAL_I3C_MODULE                    0U
  #else
    #define USE_HAL_I3C_MODULE                    1U
    #define USE_HAL_I3C_GET_LAST_ERRORS           0U
  #endif

  #if defined(HAL_RTC_MODULE_DISABLED)
    #if defined(USE_HAL_RTC_MODULE)
      #undef USE_HAL_RTC_MODULE
    #endif
    #define USE_HAL_RTC_MODULE                    0U
  #else
    #define USE_HAL_RTC_MODULE                    1U
  #endif

  #if defined(HAL_SAI_MODULE_DISABLED)
    #if defined(USE_HAL_SAI_MODULE)
      #undef USE_HAL_SAI_MODULE
    #endif
    #define USE_HAL_SAI_MODULE                    0U
  #else
    #define USE_HAL_SAI_MODULE                    1U
  #endif

  #if defined(HAL_SPI_MODULE_DISABLED)
    #if defined(USE_HAL_SPI_MODULE)
      #undef USE_HAL_SPI_MODULE
    #endif
    #define USE_HAL_SPI_MODULE                    0U
  #else
    #define USE_HAL_SPI_MODULE                    1U
  #endif

  #if defined(HAL_TIM_MODULE_DISABLED)
    #if defined(USE_HAL_TIM_MODULE)
      #undef USE_HAL_TIM_MODULE
    #endif
    #define USE_HAL_TIM_MODULE                    0U
  #else
    #define USE_HAL_TIM_MODULE                    1U
  #endif

  #if defined(HAL_ICACHE_MODULE_DISABLED)
    #if defined(USE_HAL_ICACHE_MODULE)
      #undef USE_HAL_ICACHE_MODULE
    #endif
    #define USE_HAL_ICACHE_MODULE                 0U
  #else
    #define USE_HAL_ICACHE_MODULE                 1U
  #endif

  /*
  * Not defined by default
  */
  #if defined(HAL_DAC_MODULE_DISABLED)
    #if defined(USE_HAL_DAC_MODULE)
      #undef USE_HAL_DAC_MODULE
    #endif
    #define USE_HAL_DAC_MODULE                    0U
  #endif

  #if defined(HAL_EXTI_MODULE_DISABLED)
    #if defined(USE_HAL_EXTI_MODULE)
      #undef USE_HAL_EXTI_MODULE
    #endif
    #define USE_HAL_EXTI_MODULE                   0U
  #endif

  #if defined(HAL_ETH_MODULE_DISABLED)
    #if defined(USE_HAL_ETH_MODULE)
      #undef USE_HAL_ETH_MODULE
    #endif
    #define USE_HAL_ETH_MODULE                    0U
  #endif

  /*
  * Disabled HAL modules, handled thanks Arduino menu
  */
  #if defined(HAL_UART_MODULE_ENABLED)
    #if defined(USE_HAL_UART_MODULE)
      #undef USE_HAL_UART_MODULE
    #endif
    #define USE_HAL_UART_MODULE                   1U
  #endif

  #if defined(HAL_PCD_MODULE_ENABLED)
    #if defined(USE_HAL_PCD_MODULE)
      #undef USE_HAL_PCD_MODULE
    #endif
    #define USE_HAL_PCD_MODULE                    1U
    #if defined(USBD_CDC_USE_SINGLE_BUFFER)
      #define USE_HAL_PCD_USB_DOUBLE_BUFFER         0U
    #else
      #define USE_HAL_PCD_USB_DOUBLE_BUFFER         1U
    #endif
  #endif

#else /* HALv1 */
  /*
  * Mandatory HALv1 modules
  */
  #define HAL_MODULE_ENABLED
  #define HAL_CORTEX_MODULE_ENABLED
  #define HAL_DMA_MODULE_ENABLED /* Required by other modules */
  #define HAL_FLASH_MODULE_ENABLED
  #define HAL_GPIO_MODULE_ENABLED
  #define HAL_HSEM_MODULE_ENABLED
  #define HAL_IPCC_MODULE_ENABLED
  #define HAL_MDMA_MODULE_ENABLED /* Required by HAL QSPI module */
  #define HAL_PWR_MODULE_ENABLED
  #define HAL_RCC_MODULE_ENABLED

  /*
  * Optional HAL modules, can be enabled/disabled using
  * variant.h, build_opt.h or hal_conf_extra.h
  */
  /*
  * Defined by default
  */
  #if !defined(HAL_ADC_MODULE_DISABLED)
    #define HAL_ADC_MODULE_ENABLED
  #else
    #undef HAL_ADC_MODULE_ENABLED
  #endif

  #if !defined(HAL_CRC_MODULE_DISABLED)
    #define HAL_CRC_MODULE_ENABLED
  #else
    #undef HAL_CRC_MODULE_ENABLED
  #endif

  #if !defined(HAL_I2C_MODULE_DISABLED)
    #define HAL_I2C_MODULE_ENABLED
  #else
    #undef HAL_I2C_MODULE_ENABLED
  #endif

  #if !defined(HAL_I2S_MODULE_DISABLED)
    #define HAL_I2S_MODULE_ENABLED
  #else
    #undef HAL_I2S_MODULE_ENABLED
  #endif

  #if !defined(HAL_RTC_MODULE_DISABLED)
    #define HAL_RTC_MODULE_ENABLED
  #else
    #undef HAL_RTC_MODULE_ENABLED
  #endif

  #if !defined(HAL_SAI_MODULE_DISABLED)
    #define HAL_SAI_MODULE_ENABLED
  #else
    #undef HAL_SAI_MODULE_ENABLED
  #endif

  #if !defined(HAL_SPI_MODULE_DISABLED)
    #define HAL_SPI_MODULE_ENABLED
  #else
    #undef HAL_SPI_MODULE_ENABLED
  #endif

  #if !defined(HAL_TIM_MODULE_DISABLED)
    #define HAL_TIM_MODULE_ENABLED
  #else
    #undef HAL_TIM_MODULE_ENABLED
  #endif

  #if !defined(HAL_ICACHE_MODULE_DISABLED)
    #define HAL_ICACHE_MODULE_ENABLED
  #else
    #undef HAL_ICACHE_MODULE_ENABLED
  #endif

  #if !defined(HAL_SUBGHZ_MODULE_DISABLED)
    #define HAL_SUBGHZ_MODULE_ENABLED
  #else
    #undef HAL_SUBGHZ_MODULE_ENABLED
  #endif

  #if !defined(HAL_RADIO_MODULE_DISABLED)
    #define HAL_RADIO_MODULE_ENABLED
  #else
    #undef HAL_RADIO_MODULE_ENABLED
  #endif

  #if !defined(HAL_RADIO_TIMER_MODULE_DISABLED)
    #define HAL_RADIO_TIMER_MODULE_ENABLED
  #else
    #undef HAL_RADIO_TIMER_MODULE_ENABLED
  #endif

  /*
  * Not defined by default
  */
  #if !defined(HAL_DAC_MODULE_DISABLED)
    /*#define HAL_DAC_MODULE_ENABLED*/
  #else
    #undef HAL_DAC_MODULE_ENABLED
  #endif

  /* Note: interrupt API does not used HAL EXTI module */
  /* anyway API is cleaned with HAL_EXTI_MODULE_DISABLED */
  #if !defined(HAL_EXTI_MODULE_DISABLED)
    /*#define HAL_EXTI_MODULE_ENABLED*/
  #else
    #undef HAL_EXTI_MODULE_ENABLED
  #endif

  #if !defined(HAL_ETH_MODULE_DISABLED)
    /*#define HAL_ETH_MODULE_ENABLED*/
  #else
    #undef HAL_ETH_MODULE_ENABLED
  #endif

  #if !defined(HAL_I3C_MODULE_DISABLED)
    /*#define HAL_I3C_MODULE_ENABLED*/
  #else
    #undef HAL_I3C_MODULE_ENABLED
  #endif

  #if !defined(HAL_OSPI_MODULE_DISABLED)
    /*#define HAL_OSPI_MODULE_ENABLED*/
  #else
    #undef HAL_OSPI_MODULE_ENABLED
  #endif

  #if !defined(HAL_QSPI_MODULE_DISABLED)
    /*#define HAL_QSPI_MODULE_ENABLED*/
  #else
    #undef HAL_QSPI_MODULE_ENABLED
  #endif

  #if !defined(HAL_SD_MODULE_DISABLED)
    /*#define HAL_SD_MODULE_ENABLED*/
  #else
    #undef HAL_SD_MODULE_ENABLED
  #endif

  /*
  * Disabled HAL modules, handled thanks Arduino menu
  */
  /*#define HAL_UART_MODULE_ENABLED*/
  /*#define HAL_PCD_MODULE_ENABLED*/

  /*
  * Unused HAL modules
  */
  #if 0
    HAL_CAN_LEGACY_MODULE_ENABLED
    HAL_CAN_LEGACY_MODULE_ENABLED
    HAL_CEC_MODULE_ENABLED
    HAL_COMP_MODULE_ENABLED
    HAL_CORDIC_MODULE_ENABLED
    HAL_CRYP_MODULE_ENABLED
    HAL_DCMI_MODULE_ENABLED
    HAL_DFSDM_MODULE_ENABLED
    HAL_DMA2D_MODULE_ENABLED
    HAL_DSI_MODULE_ENABLED
    HAL_EXTI_MODULE_ENABLED // interrupt API does not use the module
    HAL_FDCAN_MODULE_ENABLED
    HAL_FIREWALL_MODULE_ENABLED
    HAL_FMAC_MODULE_ENABLED
    HAL_FMPI2C_MODULE_ENABLED
    HAL_GFXMMU_MODULE_ENABLED
    HAL_GTZC_MODULE_ENABLED
    HAL_HASH_MODULE_ENABLED
    HAL_HCD_MODULE_ENABLED
    HAL_HRTIM_MODULE_ENABLED
    HAL_IRDA_MODULE_ENABLED
    HAL_IWDG_MODULE_ENABLED // IWD built-in library uses LL
    HAL_JPEG_MODULE_ENABLED
    HAL_LCD_MODULE_ENABLED
    HAL_LPTIM_MODULE_ENABLED
    HAL_LTDC_MODULE_ENABLED
    HAL_MDIOS_MODULE_ENABLED
    HAL_MDMA_MODULE_ENABLED
    HAL_MMC_MODULE_ENABLED
    HAL_NAND_MODULE_ENABLED
    HAL_NOR_MODULE_ENABLED
    HAL_OPAMP_MODULE_ENABLED
    HAL_OTFDEC_MODULE_ENABLED
    HAL_PCCARD_MODULE_ENABLED
    HAL_PKA_MODULE_ENABLED
    HAL_RAMECC_MODULE_ENABLED
    HAL_RNG_MODULE_ENABLED
    HAL_SDADC_MODULE_ENABLED
    HAL_SDRAM_MODULE_ENABLED
    HAL_SMARTCARD_MODULE_ENABLED
    HAL_SMBUS_MODULE_ENABLED
    HAL_SPDIFRX_MODULE_ENABLED
    HAL_SRAM_MODULE_ENABLED
    HAL_SUBGHZ_MODULE_ENABLED
    HAL_SWPMI_MODULE_ENABLED
    HAL_TSC_MODULE_ENABLED
    HAL_USART_MODULE_ENABLED
    HAL_WWDG_MODULE_ENABLED
  #endif /* 0 */
#endif /* HALv1 */
#endif /* __STM32YYxx_HAL_CONF_H */
