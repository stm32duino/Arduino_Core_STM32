

# **Release Notes for STM32F3xx CMSIS**
Copyright &copy; 2016 STMicroelectronics\

[![ST logo](./_htmresc/st_logo.png)](https://www.st.com)



# __Update History__
<label for="collapse-section2_3_9" aria-hidden="true">__V2.3.9 / 19-September-2026__</label>
<div>

## Main Changes

- General update
   - Align GPIO OSPEEDR defines with naming used in reference manual.
   - Rename GPIO_OSPEEDER_OSPEEDRx to GPIO_OSPEEDR_OSPEEDRx.
   - Initialize VTOR in SystemInit() by default to keep SysTick working.
   - Allow redefinition of the macro VECT_TAB_OFFSET externally from the IDE, makefile, or command line.

</div>

<label for="collapse-section2_3_8" aria-hidden="true">__V2.3.8 / 29-March-2024__</label>
<div>

## Main Changes

- General update
  - Remove duplicated definition of ADC12_CSR_ADRDY_OVR_SLV bit and add definition of ADC34_CSR_ADRDY_OVR_SLV bit
  - Align the CEC_RXDR register bit definition with reference manual

</div>

<label for="collapse-section2_3_7" aria-hidden="true">__V2.3.7 / 27-January-2023__</label>
<div>

## Main Changes

- General update
  - General updates to fix known defects and implementation enhancements
  - All source files: update disclaimer to add reference to the new license agreement.
- GCC start-up files updates
  - Alignment with IAR/MDK-ARM startup files: Update to call SystemInit first in startup/Reset_Handler()
- STM32F301x8/STM32F302xC/STM32F303x8/STM32F318xx/STM32F328xx/STM32F358xx updates
  - TIM16_OR_TI1_RMP wrong defined value

</div>

<label for="collapse-section2_3_6" aria-hidden="true">__V2.3.6 / 23-July-2021__</label>
<div>

## Main Changes

- General update
  - Added new atomic register access macros in stm32f3xx.h file.
  - Add LSI maximum startup time datasheet value: LSI_STARTUP_TIME.
- STM32F334x8 updates
  - HRTIM: Add missing defines to reset all Slave Timer X
- STM32F373xC/ STM32F378xx updates
  - Start-up files update to call COMP_IRQHandler instead of COMP1_2_IRQHandler

</div>

<label for="collapse-section2_3_5" aria-hidden="true">__V2.3.5 / 10-November-2020__</label>
<div>

## Main Changes

- General update
  - system_stm32f3xx.c
    - Protect Vector table modification following SRAM or FLASH preprocessor directive by a generic preprocessor directive : USER_VECT_TAB_ADDRESS
  - Add License.md and Readme.md files required for GitHub publication
  - Improve GCC startup files robustness.

</div>

<label for="collapse-section2_3_4" aria-hidden="true">__V2.3.4 / 12-September-2019__</label>
<div>

## Main Changes

- General update
    - Use 'UL' unsigned long postfix for _Msk definitions and memory/peripheral base addresses for MISRA C 2012 Compliance
    - SystemInit(): update to don't reset RCC registers to its reset values.
- STM32F334x8 update
    - HRTIM updates:
        - Fix too many defines for HRTIM Delayed Protection Flag Clear.
        - Fix wrong definition of HRTIM1_TIMx constants
        - Align HRTIM bits definition with reference manual
- Update OB_TypeDef structure to be aligned with reference manuals.
- Rename macro definition IS_**USB**_ALL_INSTANCE to IS_**PCD**_ALL_INSTANCE.
- Align ADC_DIFSEL_DIFSEL_Pos definition with reference manual.

</div>

<label for="collapse-section2.3.3" aria-hidden="true">__V2.3.3 / 11-June-2018__</label>
<div>

## Main Changes
- General update
    - Align ErrorStatus typedef to common error handling ( stm32f3xx.h )
- TIM updates
    - Add IS_TIM_SYNCHRO_INSTANCE macro for STM32F37xxx devices
    - Add IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE macro definition
</div>

<label for="collapse-section2.3.2" aria-hidden="true">__V2.3.2 / 23-June-2017__</label>
<div>

## Main Changes
- Remove support of Atollic TrueSTUDIO STM32 (TrueSTUDIO) toolchain.
- FLASH updates
    - Clean-up OB_WRP2_nWRP2 && OB_WRP2_nWRP3 (Option Byte) definitions according to family diversity.
- RTC updates
    - Renamed RTC_CR_BCK to RTC_CR_BKP in RTC_CR register in order to be aligned with STM32F3xx Reference Manual.
- SYSCFG updates
    - Removed SYSCFG_CFGR3_DAC1_TRG3, SYSCFG_CFGR3_DAC1_TRG5, SYSCFG_CFGR3_TRIGGER definitions for STM32F328xx devices.
- SPI updates
    - Removed SPI_SR_CHSIDE, SPI_SR_UDR definitions for STM32F303x8, STM32F328xx, STM32F334x8 devices.
- EXTI updates
    - Add EXTI_EMR2_EM definition.
- COMP updates
    - Clean-up COMPx_CSR definitions according to family diversity.
</div>

<label for="collapse-section2.3.1" aria-hidden="true">__V2.3.1 / 16-December-2016__</label>
<div>

## Main Changes
- COMP updates
    - Corrected COMP inputs definition for STM32F3xxxx devices
- ADC updates
    - Corrected SDADC_CONF1R_COMMON1_1 bit definition for STM32F373xC and STM32F378xx devices
- TIM updates
    - Added macro IS_TIM_ADVANCED_INSTANCE() to identify advanced timer instances
    - Remove TIM_CR2_OIS2N, TIM_CR2_OIS3, TIM_CR2_OIS3N and TIM_CR2_OIS4 definitions for STM32F373xC and STM32F378xx devices (alignment with STM32F3xx Reference Manual)
- RCC updates
    - Renamed RCC_CFGR register fields defines for STM32F378xx and STM32F373xC devices to be aligned with STM32F3xx Reference Manual : SDADCPRE ==> SDPRE
- PWR updates
    - Renamed PWR_CR register fields defines for STM32F378xx and STM32F373xC devices to be aligned with STM32F3xx Reference Manual : SDADCxEN ==> ENSDx
- USB updates
    - compliance with MISRA C 2004 rules:
        - MISRA C 2004 rule 10.6 ('U' suffix applied to all constants of 'unsigned' type).
        - MISRA C 2004 rule 12.7 (bitwise operations not performed on signed integer types).
- EXTI updates
    - Depends on devices, removed EXTI_IMR_MRxx, EXTI_EMR_MRxx, EXTI_RTSR_TRxx,  EXTI_FTSR_TRxx, EXTI_SWIER_SWIERxx, EXTI_PR_PRxx, EXTI_IMR2_MRxx,  EXTI__EMR2_MRxx, EXTI_RTSR2_TRxx, EXTI_FTSR2_TRxx, EXTI_SWIER2_SWIERxx, EXTI_PR2_PRxx definitions to be aligned with STM32F3xx
</div>

<label for="collapse-section2.3.0" aria-hidden="true">__V2.3.0 / 29-April-2016__</label>
<div>

## Main Changes
- General updates
    - Updated CMSIS Device compliance with MISRA C 2004 rules:
        - MISRA C 2004 rule 5.1 (bitwise operators ~ and <<).
        - MISRA C 2004 rule 10.6 ('U' suffix applied to all constants of 'unsigned' type).
    - Added FLASHSIZE_BASE and UID_BASE defines.
    - Added HardFault_IRQn definition (Cortex-M4 Hard Fault Interrupt)
    - Updated “Liberty” License with the new license “Ultimate Liberty”.
    - Updated system_stm32f3xx.h/.c files:
        - Added AHBPrescTable definition as external.
        - Added APBPrescTable definition as external.
- ADC updates
    - Updated/added ADCxy_COMMON definitions for alignment between all STM32 series.
    - Aligned bit definitions and descriptions for ADC registers between all STM32 series.
- COMP updates
    - Updated/added COMPxy_COMMON definitions for alignment between all STM32 series.
    - Created literal COMP_CSR_COMPxSW1 (equivalent of COMP1_CSR_COMP1SW1 and COMP2_CSR_COMP2SW1).
    - Removed COMPxxx_CSR_COMPyyyNONINSEL bit definitions for devices not supporting COMP3 or COMP5 instances
    - and added COMP2_CSR_COMP2NONINSEL bit definition for STM32F303xE, STM32F398xx devices.
    - Added COMP6_CSR_COMP6NONINSEL bit definition for for STM32F303xE and STM32F398xx devices.
- DAC updates
    - Aligned DAC_CR_BOFFx bit definition in DAC_CR register to be declared on the 2 DAC channels.
- EXTI updates
    - Aligned EXTI bits definition with others STM32 series.
- FMC updates
    - Aligned FMC_BWTRx register bit definitions.
- I2C updates
    - Added IS_I2S_EXT_ALL_INSTANCE definition for I2S Full-Duplex feature.
    - Added IS_I2C_WAKEUP_FROMSTOP_INSTANCE definition for I2C instances supporting Wakeup from Stop mode.
- RCC updates
    - Used RCC_CFGR_MCOSEL as reference in all STM32 series.
    - Renamed RCC_CFGR_MCOSEL_PLL to RCC_CFGR_MCOSEL_PLL_DIV2 for alignment between all STM32 series.
    - Renamed RCC_CFGR3_TIMxSW_HCLK to RCC_CFGR3_TIMxSW_PCLK2 in RCC_CFGR3 register.
    - Renamed RCC_CFGR3_HRTIM1SW_HCLK to RCC_CFGR3_HRTIM1SW_PCLK2 in RCC_CFGR3 register.
    - Removed RCC_CFGR_PLLNODIV bit definition from STM32F358xx, STM32F303xC and STM32F302xC devices.
    - Removed RCC_CSR_VREGRSTF bit definition in RCC_CSR register for STM32F303xC and STM32F303xE devices.
    - Removed USART2 and USART3 clock switch in RCC_CFGR3 register not supported by STM32F303x8, STM32F334x8
    - and STM32F328xx devices and for STM32F301x8, STM32F302x8 and STM32F318xx devices.
    - Removed RCC_CSR_V18PWRRSTF bit definition in RCC_CSR register not supported by STM32F318xx, STM32F328xx, STM32F358xx, STM32F378xx and STM32F398xx devices.
- RTC updates
    - Added missing bits definition for RTC_TAFCR register.
    - Removed RTC_ISR_TAMP3F, RTC_TAFCR_TAMP3TRG, RTC_TAFCR_TAMP3E bit definitions in RTC_ISR and RTC_TAFCR registers for STM32F303x8, STM32F334x8, STM32F328xx, STM32F301x8, STM32F302x8 and STM32F318xx devices.
- TIM updates
    - Removed TIM_SMCR_OCCS bit definition not supported by STM32F373xC.h and STM32F378xC.
- WWDG updates
    - Aligned WWDG registers bits naming between all STM32 series.
</div>

<label for="collapse-section2.2.0" aria-hidden="true">__V2.2.0 / 13-November-2015__</label>
<div>

## Main Changes
- General updates
    - Aligned all peripheral registers structures to uint32_t.
    - Added preprocessor compilation switch STM32F3 definition (stm32f3xx.h).
    - Added missing STM32F302xD and STM32F303xD mcus in the description list (stm32f3xx.h).
    - Removed define for CCM(core coupled memory) data RAM base address in Bit-Band region.
    - Removed __IO or __I from constant table declaration (system_stm32f3xx.c).
    - Corrected _estack value in project template files.
- RCC updates
    - Renamed RCC_CFGR3_USART1SW_PCLK to RCC_CFGR3_USART1SW_PCLKx according to devices.
    - Added missing flag for RCC_CSR_VREGRSTF bit.
    - Moved RCC_CFGR_MCO flag in correct devices.
    - Fixed minor typod in the comments (RCC bit definition).
- RTC updates
    - Updated list of RTC backup registers according to devices.
- HRTIM updates
    - Corrected Bit definition for HRTIM_MCMP2R/HRTIM_MCMP3R/HRTIM_MCMP4R registers (STM32F334x8 device).
- GPIO updates
    - Removed duplicated definition of IS_GPIO_ALL_INSTANCE macro.
    - Used IS_GPIO_AF_INSTANCE and IS_GPIO_LOCK_INSTANCE macro definitions.
    - Cleaned GPIO bank. Updated GPIO MLOCK capability.
    - Added only one define BSRR for BSRRH/BSRRL GPIO port bit set/reset register.
    - Added macro to check AF capability of GPIO instance.
- I2C updates
    - Renamed I2C_CR1_DFN to I2C_CR1_DNF.
    - Added define for OwnAdress 2 mask bit field values (I2C_OAR2_OA2MASK).
- UART updates
    - Added IS_UART_DMA_INSTANCE macro to sort UART instances supporting DMA communication.
- FLASH updates
    - Renamed FLASH_OBR_WDG_SW to FLASH_OBR_IWDG_SW.
    - Added defines for DATA0 & DATA1 available in OBR register.
- USB updates
    - Renamed two bitfields: USB_XXX_PMAOVRM to USB_XXX_PMAOVR and USB_CNTR_LP_MODE to USB_CNTR_LPMODE.
- TIM updates
    - Corrected Repetition Counter bits definition (TIM_RCR_REP).
- DAC updates
    - Corrected/added DAC channel output switch enable bits definition in DAC_CR register.
- FMC updates
    - Updated Bits definitions for FMC registers.
- EXTI updates
    - Updated Bit definitions for External Interrupt/Event Controller (EXTI).
</div>

<label for="collapse-section2.1.0" aria-hidden="true">__V2.1.0 / 12-Sept-2014__</label>
<div>

## Main Changes
- Add the support of the **STM32F302xE** and the **STM32F398xx** devices.
- STM32F303xE update
    - Renamed SYSCFG_CFGR3 in SYSCFG_CFGR4
- STM32F302xC update
    - Removed DHR12R2, DHR12L2, DHR8R2 and DOR2 from DAC registers definition
    - Removed all DAC channel 2 related constant definitions
    - Removed TIM8 related constant definitions
    - Removed DAC_CHANNEL_2 from IS_DAC_CHANNEL_INSTANCE() macro
</div>

<label for="collapse-section2.1.0.RC2" aria-hidden="true">__V2.1.0.RC2 / 25-Aug-2014__</label>
<div>

## Main Changes
- Add CMSIS files for STM32F303xE products
</div>

<label for="collapse-section2.0.1" aria-hidden="true">__V2.0.1 / 18-June-2014__</label>
<div>

## Main Changes
- General
    - Add new macro IS_COMP_DAC1SWITCH_INSTANCE to check COMP instance with switch of DAC1 channel1 output to non inverting input
- STM32F301x8 update
    - Add new define SYSCFG_CFGR2_LOCKUP_LOCK
- STM32F302x8 update
    - Add USB interrupt remapping
        - Add new defines USB_HP_IRQn, USB_LP_IRQn and USBWakeUp_RMP_IRQn for USB interrupt remapping
        - Add new define SYSCFG_CFGR1_USB_IT_RMP
    - Add new define SYSCFG_CFGR2_LOCKUP_LOCK
- STM32F303xC update
    - Add new define SYSCFG_CFGR2_LOCKUP_LOCK
    - Remove SYSCFG CFGR3 register description
- STM32F373xC update
    - Add new define COMP1_2_3_IRQn alias definition on COMP_IRQn
- STM32F318xx update
    - Rename COMP4_5_6_IRQn to COMP4_6_IRQn
- STM32F328xx update
    - Remove HRTIM1 (cleanup  stm32f328xx.h and startup files)
- STM32F358xx update
    - Remove USB
        - Rename USB_HP_CAN_TX_IRQn and  USB_LP_CAN_RX0_IRQn to CAN_TX_IRQn and  CAN_RX0_IRQn
        - Remove USBWakeUp_IRQn, USB_HP_IRQn, USB_LP_IRQn and USBWakeUp_RMP_IRQn
        - Remove define SYSCFG_CFGR1_USB_IT_RMP
    - Remove SYSCFG CFGR3 register description
- STM32F378xx update
    - Remove USBWakeUp_IRQn, USB_HP_IRQn and USB_LP_IRQn
    - Add new define COMP1_2_3_IRQn alias definition on COMP_IRQn
</div>

<label for="collapse-section2.0.0" aria-hidden="true">__V2.0.0 / 28-May-2014__</label>
<div>

## Main Changes
- Major update based on STM32Cube specification: new CMSIS device files release dedicated to **STM32F301x6/x8, STM32F302x6/x8, STM32F302xB/xC, STM32F303x6/x8, STM32F373xB/xC, STM32F334x4/x6/x8, STM32F318xx, STM32F328xx, STM32F358xx and STM32F378xx devices .**
- **This version has to be used for STM32CubeF3 based development although files can be used independently too.**
</div>

<label for="collapse-section1.1.1" aria-hidden="true">__V1.1.1 / 28-March-2014__</label>
<div>

## Main Changes
- Add new startup files for the STM32F302x8 and STM32F334x8 devices for TrueSTUDIO toolchain.
- Update startup files for EWARM toolchain to cope with compiler enhancement of the V7.10 version.
</div>

<label for="collapse-section1.1.0" aria-hidden="true">__V1.1.0 / 27-February-2014__</label>
<div>

## Main Changes
- Add the support of the **STM32F302x8** and the **STM32F334x8** devices.
- Update devices names definition to be in line with the new new STM32F30x family devices names.
    - **STM32F30X** replaced by **STM32F303xC.**
- stm32f30x.h
    - Upddate to support the new STM32F30x family devices names.
        - **STM32F30X** replaced by **STM32F303xC**
    - Update IRQn enum to support the STM32F302x8 and STM32F334x8 devices.
    - Update HSE_STARTUP_TIMEOUT value.
    - Update HSI_STARTUP_TIMEOUT value.
    - Add HRTIM peripheral registers and bits definitions.
    - Add CFGR3 registers in the SYSCFG_TypeDef structure.
    - Update peripheral base addresses to support the added peripherals: DAC2, I2C3, HRTIM.
    - Update ADC_SQR4 register bit definition.
    - Remove ADC34_CCR_TSEN and ADC34_CCR_VBATEN bits definitions.
- Add new startup files for the STM32F302x8 and STM32F334x8 devices for the supported compilers
    - Replace startup_stm32f30x.s by startup_stm32f303xc.s file.
    - startup_stm32f30x.s file is maintained for legacy purpose.
</div>

<label for="collapse-section1.0.0" aria-hidden="true">__V1.0.0 / 04-September-2012__</label>
<div>

## Main Changes
- First official release for **STM32F30x devices** (Standard Library)
</div>


For complete documentation on STM32 Microcontrollers </mark> ,
visit: http://www.st.com/stm32
*This release note uses up to date web standards and, for this reason, should not be opened with Internet
Explorer but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft
Edge.*