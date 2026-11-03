

# **Release Notes for STM32F0xx CMSIS**
Copyright &copy; 2016 STMicroelectronics\

[![ST logo](./_htmresc/st_logo.png)](https://www.st.com)




# __Update History__


<label for="collapse-section2_3_8" aria-hidden="true">__V2.3.8/  19-September-2026__</label>
<div>

## Main Changes

- General updates
  - Remove Unique device ID (UID) register definition from STM32F030x4/x6/x8/xC and STM32F070x6/xB advanced Arm®-based 32-bit MCUs.
  - Add support for HSI48 in SystemCoreClockUpdate.

</div>

<label for="collapse-section2_3_7" aria-hidden="true">__V2.3.7/ 27-January-2023__</label>
<div>

## Main Changes

- General updates
  - All source files: update disclaimer to add reference to the new license agreement.
  - Update GCC startup files to call SystemInit() API in beginning of Reset_Handler() API to be aligned with IAR/MDK-ARM implementation.
  - Fix inconsistent IRQn_Type enumeration for supervisor call exception with alias for compatibility
  - Add support for HSI48 in SystemCoreClockUpdate.
  - stm32f030xc.h header file update:
    - Revert change done in V2.3.5 on RCC_CFGR bits definition.
    - RCC_CFGR bits description will be updated in documentation: RM0360.

</div>

<label for="collapse-section2_3_6" aria-hidden="true">__V2.3.6 / 23-July-2021__</label>
<div>

## Main Changes

- General updates
  - CAN updates
    - Remove extra CAN filters: bit fields 14..27
  - Added new atomic register access macros in stm32f0xx.h file.
  - Add new defined value for LSI maximum startup time: LSI_STARTUP_TIME.

</div>

<label for="collapse-section2_3_5" aria-hidden="true">__V2.3.5 / 06-November-2020__</label>
<div>

## Main Changes

- General updates
  - Update stm32f030xc.h header file to be aligned with RCC_CFGR bit definition.
  - Rename the defined STM32 sub-family "STM32F048x6" to "STM32F048xx"
  - Add License.md and Readme.md files required for GitHub publication.

</div>

<label for="collapse-section2_3_4" aria-hidden="true">__V2.3.4 / 12-September-2019__</label>
<div>

## Main Changes

- General updates
  - Align ErrorStatus typedef to common error handling (stm32f0xx.h)
  - SystemInit(): update to don't reset RCC registers to its reset values.
  - USE UL postfix for _Msk definitions and memory/peripheral base addresses for MISRA C 2012 Compliance
- Rename macro definition IS_USB_ALL_INSTANCE to IS_PCD_ALL_INSTANCE.
- Add macro definition IS_GPIO_AF_INSTANCE for stm32f030xc devices

</div>

<label for="collapse-section2_3_3" aria-hidden="true">__V2.3.3 / 25-August-2017__</label>
<div>

## Main Changes

- Remove support of Atollic TrueSTUDIO STM32 (TrueSTUDIO) toolchain.
- Performance improvement of the startup code for GCC.

</div>

<label for="collapse-section2_3_2" aria-hidden="true">__V2.3.2 / 07-April-2017__</label>
<div>

## Main Changes

- Rename GPIO_AFRH and GPIO_AFRL bitfields for alignment with all STM32 series.
- Add macro definition : IS_TIM_ADVANCED.
- Rename RTC_CR register bit definition to be aligned with STM32F0xx Reference Manual : RTC_CR_BCK ==> RTC_CR_BKP

</div>

<label for="collapse-section2_3_1" aria-hidden="true">__V2.3.1 / 04-November-2016__</label>
<div>

## Main Changes

- Add TIM6_IRQHandler in vectors table for STM32F030x8 devices

</div>

<label for="collapse-section2_3_0" aria-hidden="true">__V2.3.0 / 27-May-2016__</label>
<div>

## Main Changes
- General updates
  - Updated CMSIS Device compliance with MISRA C 2004 rules:
    - MISRA C 2004 rule 10.5 (bitwise operators ~ and <<).
    - MISRA C 2004 rule 10.6 ('U' suffix applied to all constants of 'unsigned' type).
  - Updated system_stm32f3xx.h/.c files:
    - Added AHBPrescTable definition as external.
    - Added APBPrescTable definition as external.
- EXTI updates
  - Added definitions of bit 31 in EXTI registers for STM32F04x, STM32F078xx and STM32F098xx devices.
- I2C updates
    - Added IS_I2C_WAKEUP_FROMSTOP_INSTANCE definition for I2C instances supporting Wakeup from Stop mode.
- I2S updates
    - Removed SPI_I2S prescaler register not supported by STM32F030x6 and STM32F030x8 devices.
- RCC updates
    - Added missing RCC_CFGR_PLLNODIV definition for STM32F030x4/6 devices.
- RTC updates
    - Removed cast from RTC_BKP_NUMBER definition.
- SYSCFG updates
    - Renamed SYSCFG_CFGR1_IRDA_ENV_SEL bit definitions to SYSCFG_CFGR1_IR_MOD for SYSCFG_CFGR1 register.
- TIM updates
    - Added IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE definition.
    - Added IS_TIM_ETR_INSTANCE definition.
- UART updates
    - Renamed IS_UART_WAKEUP_INSTANCE to IS_UART_WAKEUP_FROMSTOP_INSTANCE.
- USART updates
    - Defined USART_ISR_RWU bit for all STM32F0xx devices.

</div>

<label for="collapse-section2_2_3" aria-hidden="true">__V2.2.3 / 29-January-2016__</label>
<div>

## Main Changes

- Added mention to STM32F091xB mcus missing in the list of mcus of stm32f0xx.h.
- Updated CMSIS Device compliance with MISRA C 2004 rule 10.6.
- Updated CMSIS Device compliance with MISRA C 2004 rule 5.1.
- Added HSI48_VALUE definition in system_stm32f0xx.c file.
- Put variable AHBPrescTable as external in system_stm32f0xx.h.
- Added channel selection bit definitions for for DMA1_CSELR register.
- Used RCC_CFGR_MCOSEL as reference in all the families.
- Renamed RCC_CFGR_MCOSEL_PLL to RCC_CFGR_MCOSEL_PLL_DIV2 for alignment between all families.
- Updated EWUPx pins definitions for STM32F042x6 and STM32F048xx devices.
- Added FLASHSIZE_BASE and UID_BASE defines.
- Added missing bits definition for RTC_TAFCR register.
- Added missing bits definition for I2C_OAR2 register (I2C_OAR2 mask values).
- Renamed I2C_CR1_DFN to I2C_CR1_DNF bit definition for I2C_CR1 register.
- Removed __IO or __I on constant table declaration.
- Used default DAC instance naming DAC1 in macro IS_DAC_ALL_INSTANCE().
- Aligned EXTI registers Bits naming between all families.
- Aligned WWDG registers Bits naming between all families.
- Aligned COMP common instance definition.
- Corrected CRC defines: Replaced POL field by RESERVED3 for STM32F030x6, STM32F030x8, STM32F031x6, STM32F038xx, STM32F042x6, STM32F048xx devices.
- Corrected CRC defines: Removed Bit definitions related to Polynomial in CRC_CR and CRC_POL registers for STM32F030xC.
- Updated for ADC: removed conditions on CCR_TS definition.
- Corrected SYSCFG_RTC_WAKEUP and SYSCFG_RTC_ALRA Bits definition for SYSCFG_xxx ISR Wrapper register.
- Added ADC_CHSELR_CHSEL Bit definition for ADC_CHSELR register.
- Removed RCC_CSR_V18PWRRSTF Bit definition for STM32F0x8xx devices.
- Corrected USART defines for STM32F030xx, STM32F070xx devices.
- Removed IS_UART_AUTOBAUDRATE_DETECTION_INSTANCE macro definition.
- Adapted IS_USART_AUTOBAUDRATE_DETECTION_INSTANCE to device feature support.
- Removed IS_UART_DRIVER_ENABLE_INSTANCE definition for  STM32F030x8, STM32F030xC and STM32F070xB devices.
- Corrected FLASH_OBR_nBOOT0 value.
- Removed Synchronous mode support on USART5/6 for STM32F030xC.
- Removed HW Flow Control support on USART5/6/7/8 for STM32F091xC.

</div>

<label for="collapse-section2_2_2" aria-hidden="true">__V2.2.2 / 26-June-2015__</label>
<div>

## Main Changes

- Add missing WUT bits in EXTI_IMR/EMR/RTSR/FTSR/PR/SWIER for different IT lines.
- Add preprocessor compilation switch #define STM32F0 in stm32f0xx.h.
- Correct FLASH_KEY name difference between STM32F0 and STM32F3.
- Remove RCC_CFGR3_USART2SW from CMSIS, present only for STM32F07x and STM32F09x.
- Modify EXTI/COMP defines from uint16 to uint32.
- Add missing definitions of EXTI_IMR_MR31 used by PWREx in stm32f042x6 and stm32f048xx files.
- Add FLASH_BANK1_END defines.
- Remove WRP defines for few defines under devices swicthes.
- Add FLASH_OBR_RAM_PARITY_CHECK and FLASH_OBR_BOOT_SEL CMSIS files.

</div>

<label for="collapse-section2_2_1" aria-hidden="true">__V2.2.1 / 09-January-2015__</label>
<div>

## Main Changes

- system_stm32f0xx.c: replace wrong compilation switch STM32F078xB by STM32F078xx.
- stm32F070xb.h: correct wrong DMA remap mask value for STM32f070xB.
- stm32F070xb.h, stm32F070x6.h, stm32F030xc.h: add missing macro IS_UART_DRIVER_ENABLE_INSTANCE()
- stm32F070xb.h, stm32F030xc.h: add missing RTC periodic Wakeup register & bits description

</div>

<label for="collapse-section2_2_0" aria-hidden="true">__V2.2.0 / 05-December-2014__</label>
<div>

## Main Changes

- Add CMSIS files for new STM32F0 value line devices: STM32F030xC and STM32F070x6/xB.
- Add macro to check AF capability of gpio instance
- uint32_t alignment done on all Peripheral registers structures & bits definition
- stm32f091xc.h: DMA channel remap register renamed for compatibility with other STM32 devices
- startup_stm32f042x6.s & startup_stm32f070x6.s: fix boot issue

</div>

<label for="collapse-section2_1_0" aria-hidden="true">__V2.1.0 / 03-October-2014__</label>
<div>

## Main Changes

- Add new CMSIS files for STM32F091xc and STM32F098xx products
- VDDIO2 IRQ missing in F07xx/F09xx/F04xx product
- IS_DAC_CHANNEL_INSTANCE macro removed as unused
- uint32_t partial alignment done on peripheral Bit definition & register structure
- Bit definition name error for DMA_RMPCR1 register of STM32F091xC
- Remove PDV feature on REGoff part
- Remove POSITION_VAL macro as it uses RBIT, CLZ instructions, that are not supported by Cortex-M0
- GPIOS BSRR register should not be split in BSRRH/BSRRL

</div>

<label for="collapse-section2_0_1" aria-hidden="true">__V2.0.1 / 18-June-2014__</label>
<div>

## Main Changes

- General
  - Add new macros
    - IS_GPIO_LOCK_INSTANCE to check GPIO port with lock capability
    - IS_UART_HALFDUPLEX_INSTANCE, IS_UART_LIN_INSTANCE and IS_UART_WAKEUP_INSTANCE to  check  the UART instance supported features.
- STM32F042x8 and STM32F048xx update
  - Rename DMA1_Channel4_5_6_7_IRQn to DMA1_Channel4_5_IRQn
  - Rename ADC1_COMP_IRQn to ADC1_IRQn
  - Remove SPI2 instance
- STM32F051x8, STM32F058xx, STM32F071xB, STM32F072xB and STM32F078xx update
  - Fix COMP2 instance base address
  - Add new macro IS_COMP_DAC1SWITCH_INSTANCE to check COMP instance with switch of DAC1 channel1 output to non inverting input
- STM32F051x8 and STM32F058xx update
  - Rename DMA1_Channel4_5_6_7_IRQn to DMA1_Channel4_5_IRQn
- STM32F078xx update
  - Remove CAN peripheral description

</div>

<label for="collapse-section2_0_0" aria-hidden="true">__V2.0.0 / 28-May-2014__</label>
<div>

## Main Changes

- Major update based on STM32Cube specification: new CMSIS device files release dedicated to **STM32F030x4/x6, STM32F030x8, STM32F031x4/x6, STM32F051x4/x6/x8, STM32F071x8/xB, STM32F042x4/x6, STM32F072x8/xB, STM32F038xx, STM32F048xx, STM32F058xx and STM32F078xx devices**.
- **This version has to be used for STM32CubeF0 based development although files can be used independently too**.

</div>

<label for="collapse-section1_2_1" aria-hidden="true">__V1.2.1 / 22-November-2013__</label>
<div>

## Main Changes

- stm32f0xx.h
  - Update STM32F030 devices definition:
    - Remove the STM32F030X8 and STM32FO30X6 defines and replace them with the STM32F030 define
  - Update IRQn enum for STM32F030 devices
- system_stm32f0xx.c
  - SystemInit(): update to support STM32F030 devices
- Remove the startup files startup_stm32f030x8.s and startup_stm32f030x6.s and replace them by startup_stm32f030.s, for EWARM, MDK-ARM and Truestudio supported compilers

</div>

<label for="collapse-section1_2_0" aria-hidden="true">__V1.2.0 / 01-August-2013__</label>
<div>

## Main Changes

- Add support of STM32F030  devices (STM32F030x8 and STM32F030x6 microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)
- stm32f0xx.h
  - Update STM32F0xx devices definition:
    - Add new definition STM32F030X8 and STM32FO30X6 for STM32F030 devices
  - Update IRQn enum for STM32F030 devices
system_stm32f0xx.c
SystemInit(): update to support STM32F030 devices
Add new startup files, startup_stm32f030x8.s and startup_stm32f030x6.s, for EWARM, MDK-ARM and Truestudio supported compilers

</div>

<label for="collapse-section1_1_1" aria-hidden="true">__V1.1.1 / 31-July-2013__</label>
<div>

## Main Changes

- stm32f0xx.h
  - Extend HSE_STARTUP_TIMEOUT and HSI_STARTUP_TIMEOUT values to 0x5000

</div>

<label for="collapse-section1_1_0" aria-hidden="true">__V1.1.0 / 10-May-2013__</label>
<div>

## Main Changes

- Add support of STM32F0xx Low-density devices (STM32F050xx and STM32F060xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)
- stm32f0xx.h
  - Update STM32F0xx devices definition:
    - Define for STM32F0xx Medium-density devices changed from STM32F0XX to STM32F0XX_MD
    - Add new definition STM32F0XX_LD for STM32F0xx Low-density devices
  - Update IRQn enum for STM32F0XX_LD devices
  - Add new bits definition
    - RCC_CFGR register: MCOPRE[0:2] and PLLNODIV
    - SYSCFG_CFGR1 register: FMP_I2C1, FMP_PA9 and FMP_PA10
- system_stm32f0xx.c
  - SystemInit(): update to reset new bits added in RCC_CFGR register
- Add new startup files, startup_stm32f0xx_ld.s, for the supported compilers

</div>

<label for="collapse-section1_0_2" aria-hidden="true">__V1.0.2 / 13-July-2012__</label>
<div>

## Main Changes
- stm32f0xx.h
  - Fix issue with gcc_ride7 startup file

</div>

<label for="collapse-section1_0_1" aria-hidden="true">__V1.0.1 / 20-April-2012__</label>
<div>

## Main Changes

- stm32f0xx.h
  - Add reference to STM32F050xx (Flash memory up to 32 Kbytes) and STM32F051xx (Flash memory up to 64 Kbytes) devices
  - RTC register bits definition: remove reference to Tamper3

</div>

<label for="collapse-section1_0_0" aria-hidden="true">__V1.0.0 / 04-September-2012__</label>
<div>

## Main Changes

- First official release for **STM32F30x** devices (Standard Library)

</div>


For complete documentation on STM32 Microcontrollers </mark> ,
visit: http://www.st.com/stm32
*This release note uses up to date web standards and, for this reason, should not be opened with Internet
Explorer but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft
Edge.*