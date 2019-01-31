/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
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

#ifndef _PINAF_STM32F1_H
#define _PINAF_STM32F1_H

#ifdef STM32F1xx

#ifdef __cplusplus
extern "C" {
#endif

enum {
    AFIO_NONE,
    AFIO_SPI1_ENABLE,
    AFIO_SPI1_DISABLE,
    AFIO_I2C1_ENABLE,
    AFIO_I2C1_DISABLE,
    AFIO_USART1_ENABLE,
    AFIO_USART1_DISABLE,
    AFIO_USART2_ENABLE,
    AFIO_USART2_DISABLE,
    AFIO_USART3_ENABLE,
    AFIO_USART3_PARTIAL,
    AFIO_USART3_DISABLE,
    AFIO_TIM1_ENABLE,
    AFIO_TIM1_PARTIAL,
    AFIO_TIM1_DISABLE,
    AFIO_TIM2_ENABLE,
    AFIO_TIM2_PARTIAL_2,
    AFIO_TIM2_PARTIAL_1,
    AFIO_TIM2_DISABLE,
    AFIO_TIM3_ENABLE,
    AFIO_TIM3_PARTIAL,
    AFIO_TIM3_DISABLE,
    AFIO_TIM4_ENABLE,
    AFIO_TIM4_DISABLE,
//#if defined(AFIO_MAPR_CAN_REMAP1)
    AFIO_CAN1_1,
    AFIO_CAN1_2,
    AFIO_CAN1_3,
//#endif
    AFIO_PD01_ENABLE,
    AFIO_PD01_DISABLE,
#if defined(AFIO_MAPR_TIM5CH4_IREMAP)
    AFIO_TIM5CH4_ENABLE,
    AFIO_TIM5CH4_DISABLE,
#endif
#if defined(AFIO_MAPR_ETH_REMAP)
    AFIO_ETH_ENABLE,
    AFIO_ETH_DISABLE,
#endif
#if defined(AFIO_MAPR_CAN2_REMAP)
    AFIO_CAN2_ENABLE,
    AFIO_CAN2_DISABLE,
#endif
#if defined(AFIO_MAPR_MII_RMII_SEL)
    AFIO_ETH_RMII,
    AFIO_ETH_MII,
#endif
    AFIO_ADC1_ETRGINJ_ENABLE,
    AFIO_ADC1_ETRGINJ_DISABLE,
    AFIO_ADC1_ETRGREG_ENABLE,
    AFIO_ADC1_ETRGREG_DISABLE,
#if defined(AFIO_MAPR_ADC2_ETRGINJ_REMAP)
    AFIO_ADC2_ETRGINJ_ENABLE,
    AFIO_ADC2_ETRGINJ_DISABLE,
#endif
#if defined(AFIO_MAPR_ADC2_ETRGREG_REMAP)
    AFIO_ADC2_ETRGREG_ENABLE,
    AFIO_ADC2_ETRGREG_DISABLE,
#endif
    AFIO_SWJ_ENABLE,
    AFIO_SWJ_NONJTRST,
    AFIO_SWJ_NOJTAG,
    AFIO_SWJ_DISABLE,
#if defined(AFIO_MAPR_SPI3_REMAP)
    AFIO_SPI3_ENABLE,
    AFIO_SPI3_DISABLE,
#endif
#if defined(AFIO_MAPR_TIM2ITR1_IREMAP)
    AFIO_TIM2ITR1_TO_USB,
    AFIO_TIM2ITR1_TO_ETH,
#endif
#if defined(AFIO_MAPR_PTP_PPS_REMAP)
    AFIO_ETH_PTP_PPS_ENABLE,
    AFIO_ETH_PTP_PPS_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM9_REMAP)
    AFIO_TIM9_ENABLE,
    AFIO_TIM9_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM10_REMAP)
    AFIO_TIM10_ENABLE,
    AFIO_TIM10_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM11_REMAP)
    AFIO_TIM11_ENABLE,
    AFIO_TIM11_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM13_REMAP)
    AFIO_TIM13_ENABLE,
    AFIO_TIM13_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM14_REMAP)
    AFIO_TIM14_ENABLE,
    AFIO_TIM14_DISABLE,
#endif
#if defined(AFIO_MAPR2_FSMC_NADV_REMAP)
    AFIO_FSMCNADV_DISCONNECTED,
    AFIO_FSMCNADV_CONNECTED,
#endif
#if defined(AFIO_MAPR2_TIM15_REMAP)
    AFIO_TIM15_ENABLE,
    AFIO_TIM15_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM16_REMAP)
    AFIO_TIM16_ENABLE,
    AFIO_TIM16_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM17_REMAP)
    AFIO_TIM17_ENABLE,
    AFIO_TIM17_DISABLE,
#endif
#if defined(AFIO_MAPR2_CEC_REMAP)
    AFIO_CEC_ENABLE,
    AFIO_CEC_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM1_DMA_REMAP)
    AFIO_TIM1DMA_ENABLE,
    AFIO_TIM1DMA_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM67_DAC_DMA_REMAP)
    AFIO_TIM67DACDMA_ENABLE,
    AFIO_TIM67DACDMA_DISABLE,
#endif
#if defined(AFIO_MAPR2_TIM12_REMAP)
    AFIO_TIM12_ENABLE,
    AFIO_TIM12_DISABLE,
#endif
#if defined(AFIO_MAPR2_MISC_REMAP)
    AFIO_MISC_ENABLE,
    AFIO_MISC_DISABLE,
#endif
};

static inline void pinF1_DisconnectDebug(PinName pin)
{
  /** Enable this flag gives the possibility to use debug pins without any risk
    * to lose traces
    */
#ifndef STM32F1_LOCK_DEBUG
    // Enable AFIO clock
    __HAL_RCC_AFIO_CLK_ENABLE();

    // Disconnect JTAG-DP + SW-DP signals.
    // Warning: Need to reconnect under reset
    if ((pin == PA_13) || (pin == PA_14)) {
        __HAL_AFIO_REMAP_SWJ_DISABLE(); // JTAG-DP Disabled and SW-DP Disabled
    }
    if ((pin == PA_15) || (pin == PB_3) || (pin == PB_4)) {
        __HAL_AFIO_REMAP_SWJ_NOJTAG(); // JTAG-DP Disabled and SW-DP enabled
    }
#else
    UNUSED(pin);
#endif /* STM32F1_FORCE_DEBUG */
}

static inline void pin_SetF1AFPin(uint32_t afnum)
{
   // Enable AFIO clock
   __HAL_RCC_AFIO_CLK_ENABLE();

   switch (afnum) {
   case AFIO_SPI1_ENABLE:
       __HAL_AFIO_REMAP_SPI1_ENABLE();
       break;
   case AFIO_SPI1_DISABLE:
       __HAL_AFIO_REMAP_SPI1_DISABLE();
       break;
   case AFIO_I2C1_ENABLE:
       __HAL_AFIO_REMAP_I2C1_ENABLE();
       break;
   case AFIO_I2C1_DISABLE:
       __HAL_AFIO_REMAP_I2C1_DISABLE();
       break;
   case AFIO_USART1_ENABLE:
       __HAL_AFIO_REMAP_USART1_ENABLE();
       break;
   case AFIO_USART1_DISABLE:
       __HAL_AFIO_REMAP_USART1_DISABLE();
       break;
   case AFIO_USART2_ENABLE:
       __HAL_AFIO_REMAP_USART2_ENABLE();
       break;
   case AFIO_USART2_DISABLE:
       __HAL_AFIO_REMAP_USART2_DISABLE();
       break;
#if defined(AFIO_MAPR_USART3_REMAP)
   case AFIO_USART3_ENABLE:
       __HAL_AFIO_REMAP_USART3_ENABLE();
       break;
   case AFIO_USART3_PARTIAL:
       __HAL_AFIO_REMAP_USART3_PARTIAL();
       break;
   case AFIO_USART3_DISABLE:
       __HAL_AFIO_REMAP_USART3_DISABLE();
       break;
#endif
   case AFIO_TIM1_ENABLE:
       __HAL_AFIO_REMAP_TIM1_ENABLE();
       break;
   case AFIO_TIM1_PARTIAL:
       __HAL_AFIO_REMAP_TIM1_PARTIAL();
       break;
   case AFIO_TIM1_DISABLE:
       __HAL_AFIO_REMAP_TIM1_DISABLE();
       break;
   case AFIO_TIM2_ENABLE:
       __HAL_AFIO_REMAP_TIM2_ENABLE();
       break;
   case AFIO_TIM2_PARTIAL_2:
       __HAL_AFIO_REMAP_TIM2_PARTIAL_2();
       break;
   case AFIO_TIM2_PARTIAL_1:
       __HAL_AFIO_REMAP_TIM2_PARTIAL_1();
       break;
   case AFIO_TIM2_DISABLE:
       __HAL_AFIO_REMAP_TIM2_DISABLE();
       break;
   case AFIO_TIM3_ENABLE:
       __HAL_AFIO_REMAP_TIM3_ENABLE();
       break;
   case AFIO_TIM3_PARTIAL:
       __HAL_AFIO_REMAP_TIM3_PARTIAL();
       break;
   case AFIO_TIM3_DISABLE:
       __HAL_AFIO_REMAP_TIM3_DISABLE();
       break;
#if defined(AFIO_MAPR_TIM4_REMAP)
   case AFIO_TIM4_ENABLE:
       __HAL_AFIO_REMAP_TIM4_ENABLE();
       break;
   case AFIO_TIM4_DISABLE:
       __HAL_AFIO_REMAP_TIM4_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_CAN_REMAP1)
   case AFIO_CAN1_1:
       __HAL_AFIO_REMAP_CAN1_1();
       break;
   case AFIO_CAN1_2:
       __HAL_AFIO_REMAP_CAN1_2();
       break;
   case AFIO_CAN1_3:
       __HAL_AFIO_REMAP_CAN1_3();
       break;
#endif
   case AFIO_PD01_ENABLE:
       __HAL_AFIO_REMAP_PD01_ENABLE();
       break;
   case AFIO_PD01_DISABLE:
       __HAL_AFIO_REMAP_PD01_DISABLE();
       break;
#if defined(AFIO_MAPR_TIM5CH4_IREMAP)
   case AFIO_TIM5CH4_ENABLE:
       __HAL_AFIO_REMAP_TIM5CH4_ENABLE();
       break;
   case AFIO_TIM5CH4_DISABLE:
       __HAL_AFIO_REMAP_TIM5CH4_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_ETH_REMAP)
   case AFIO_ETH_ENABLE:
       __HAL_AFIO_REMAP_ETH_ENABLE();
       break;
   case AFIO_ETH_DISABLE:
       __HAL_AFIO_REMAP_ETH_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_CAN2_REMAP)
   case AFIO_CAN2_ENABLE:
       __HAL_AFIO_REMAP_CAN2_ENABLE();
       break;
   case AFIO_CAN2_DISABLE:
       __HAL_AFIO_REMAP_CAN2_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_MII_RMII_SEL)
   case AFIO_ETH_RMII:
       __HAL_AFIO_ETH_RMII();
       break;
   case AFIO_ETH_MII:
       __HAL_AFIO_ETH_MII();
       break;
#endif
#if defined(AFIO_MAPR_ADC1_ETRGINJ_REMAP)
   case AFIO_ADC1_ETRGINJ_ENABLE:
       __HAL_AFIO_REMAP_ADC1_ETRGINJ_ENABLE();
       break;
   case AFIO_ADC1_ETRGINJ_DISABLE:
       __HAL_AFIO_REMAP_ADC1_ETRGINJ_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_ADC1_ETRGREG_REMAP)
   case AFIO_ADC1_ETRGREG_ENABLE:
       __HAL_AFIO_REMAP_ADC1_ETRGREG_ENABLE();
       break;
   case AFIO_ADC1_ETRGREG_DISABLE:
       __HAL_AFIO_REMAP_ADC1_ETRGREG_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_ADC2_ETRGINJ_REMAP)
   case AFIO_ADC2_ETRGINJ_ENABLE:
       __HAL_AFIO_REMAP_ADC2_ETRGINJ_ENABLE();
       break;
   case AFIO_ADC2_ETRGINJ_DISABLE:
       __HAL_AFIO_REMAP_ADC2_ETRGINJ_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_ADC2_ETRGREG_REMAP)
   case AFIO_ADC2_ETRGREG_ENABLE:
       __HAL_AFIO_REMAP_ADC2_ETRGREG_ENABLE();
       break;
   case AFIO_ADC2_ETRGREG_DISABLE:
       __HAL_AFIO_REMAP_ADC2_ETRGREG_DISABLE();
       break;
#endif
   case AFIO_SWJ_ENABLE:
       __HAL_AFIO_REMAP_SWJ_ENABLE();
       break;
   case AFIO_SWJ_NONJTRST:
       __HAL_AFIO_REMAP_SWJ_NONJTRST();
       break;
   case AFIO_SWJ_NOJTAG:
       __HAL_AFIO_REMAP_SWJ_NOJTAG();
       break;
   case AFIO_SWJ_DISABLE:
       __HAL_AFIO_REMAP_SWJ_DISABLE();
       break;
#if defined(AFIO_MAPR_SPI3_REMAP)
   case AFIO_SPI3_ENABLE:
       __HAL_AFIO_REMAP_SPI3_ENABLE();
       break;
   case AFIO_SPI3_DISABLE:
       __HAL_AFIO_REMAP_SPI3_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR_TIM2ITR1_IREMAP)
   case AFIO_TIM2ITR1_TO_USB:
       __HAL_AFIO_TIM2ITR1_TO_USB();
       break;
   case AFIO_TIM2ITR1_TO_ETH:
       __HAL_AFIO_TIM2ITR1_TO_ETH();
       break;
#endif
#if defined(AFIO_MAPR_PTP_PPS_REMAP)
   case AFIO_ETH_PTP_PPS_ENABLE:
       __HAL_AFIO_ETH_PTP_PPS_ENABLE();
       break;
   case AFIO_ETH_PTP_PPS_DISABLE:
       __HAL_AFIO_ETH_PTP_PPS_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM9_REMAP)
   case AFIO_TIM9_ENABLE:
       __HAL_AFIO_REMAP_TIM9_ENABLE();
       break;
   case AFIO_TIM9_DISABLE:
       __HAL_AFIO_REMAP_TIM9_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM10_REMAP)
   case AFIO_TIM10_ENABLE:
       __HAL_AFIO_REMAP_TIM10_ENABLE();
       break;
   case AFIO_TIM10_DISABLE:
       __HAL_AFIO_REMAP_TIM10_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM11_REMAP)
   case AFIO_TIM11_ENABLE:
       __HAL_AFIO_REMAP_TIM11_ENABLE();
       break;
   case AFIO_TIM11_DISABLE:
       __HAL_AFIO_REMAP_TIM11_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM13_REMAP)
   case AFIO_TIM13_ENABLE:
       __HAL_AFIO_REMAP_TIM13_ENABLE();
       break;
   case AFIO_TIM13_DISABLE:
       __HAL_AFIO_REMAP_TIM13_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM14_REMAP)
   case AFIO_TIM14_ENABLE:
       __HAL_AFIO_REMAP_TIM14_ENABLE();
       break;
   case AFIO_TIM14_DISABLE:
       __HAL_AFIO_REMAP_TIM14_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_FSMC_NADV_REMAP)
   case AFIO_FSMCNADV_DISCONNECTED:
       __HAL_AFIO_FSMCNADV_DISCONNECTED();
       break;
   case AFIO_FSMCNADV_CONNECTED:
       __HAL_AFIO_FSMCNADV_CONNECTED();
       break;
#endif
#if defined(AFIO_MAPR2_TIM15_REMAP)
   case AFIO_TIM15_ENABLE:
       __HAL_AFIO_REMAP_TIM15_ENABLE();
       break;
   case AFIO_TIM15_DISABLE:
       __HAL_AFIO_REMAP_TIM15_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM16_REMAP)
   case AFIO_TIM16_ENABLE:
       __HAL_AFIO_REMAP_TIM16_ENABLE();
       break;
   case AFIO_TIM16_DISABLE:
       __HAL_AFIO_REMAP_TIM16_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM17_REMAP)
   case AFIO_TIM17_ENABLE:
       __HAL_AFIO_REMAP_TIM17_ENABLE();
       break;
   case AFIO_TIM17_DISABLE:
       __HAL_AFIO_REMAP_TIM17_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_CEC_REMAP)
   case AFIO_CEC_ENABLE:
       __HAL_AFIO_REMAP_CEC_ENABLE();
       break;
   case AFIO_CEC_DISABLE:
       __HAL_AFIO_REMAP_CEC_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM1_DMA_REMAP)
   case AFIO_TIM1DMA_ENABLE:
       __HAL_AFIO_REMAP_TIM1DMA_ENABLE();
       break;
   case AFIO_TIM1DMA_DISABLE:
       __HAL_AFIO_REMAP_TIM1DMA_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM67_DAC_DMA_REMAP)
   case AFIO_TIM67DACDMA_ENABLE:
       __HAL_AFIO_REMAP_TIM67DACDMA_ENABLE();
       break;
   case AFIO_TIM67DACDMA_DISABLE:
       __HAL_AFIO_REMAP_TIM67DACDMA_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_TIM12_REMAP)
   case AFIO_TIM12_ENABLE:
       __HAL_AFIO_REMAP_TIM12_ENABLE();
       break;
   case AFIO_TIM12_DISABLE:
       __HAL_AFIO_REMAP_TIM12_DISABLE();
       break;
#endif
#if defined(AFIO_MAPR2_MISC_REMAP)
   case AFIO_MISC_ENABLE:
       __HAL_AFIO_REMAP_MISC_ENABLE();
       break;
   case AFIO_MISC_DISABLE:
       __HAL_AFIO_REMAP_MISC_DISABLE();
       break;
#endif
   default:
   case AFIO_NONE:
       break;
   }
}

#ifdef __cplusplus
}
#endif

#endif /* STM32F1xx */

#endif /* _PINAF_STM32F1_H */
