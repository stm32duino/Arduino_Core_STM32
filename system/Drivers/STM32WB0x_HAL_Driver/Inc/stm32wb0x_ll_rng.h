/**
  ******************************************************************************
  * @file    stm32wb0x_ll_rng.h
  * @author  MCD Application Team
  * @brief   Header file of RNG LL module.
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
#ifndef STM32WB0x_LL_RNG_H
#define STM32WB0x_LL_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"

/** @addtogroup STM32WB0x_LL_Driver
  * @{
  */

#if defined (RNG)
/** @defgroup RNG_LL RNG
  * @{
  */
#if defined (STM32WB09)

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_ES_Init_Struct RNG Exported Init structures
  * @{
  */

/**
  * @brief LL RNG Init Structure Definition
  */
typedef struct
{
  uint32_t         SamplingClockDivider; /*!< TRNG includes an internal clock enable divider that can be set by bits
                                              CLKDIV0 to CLKDIV15 of TRNG_CR register.
                                              It is used for decreasing internal random source sampling. Before
                                              changing the clock divider, it is recommended
                                              to disable the TRNG bit setting bit DISABLE to 1.
                                              This parameter can be one value being in the range of 0 to 65535.
                                              This parameter can be modified using unitary functions @ref
                                              LL_RNG_SetSamplingClockEnableDivider(). */
} LL_RNG_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RNG_LL_DISABLE Values
  * @{
 */
#define LL_RNG_CR_DISABLE_0                                (0U)
#define LL_RNG_CR_DISABLE_1                                (RNG_CR_DISABLE)
/**
  * @}
  */

/** @defgroup RNG_LL_CLR_REVCLK_FLAG Values
  * @{
 */
#define LL_RNG_CR_CLR_REVCLK_FLAG_0                        (0U)
#define LL_RNG_CR_CLR_REVCLK_FLAG_1                        (RNG_CR_CLR_REVCLK_FLAG)
/**
  * @}
  */

/** @defgroup RNG_LL_RST_HEALTH_FLAGS Values
  * @{
 */
#define LL_RNG_CR_RST_HEALTH_FLAGS_0                       (0U)
#define LL_RNG_CR_RST_HEALTH_FLAGS_1                       (RNG_CR_RST_HEALTH_FLAGS)
/**
  * @}
  */


/** @defgroup RNG_LL_BP_POSTP Values
  * @{
 */
#define LL_RNG_CR_BP_POSTP_0                               (0U)
#define LL_RNG_CR_BP_POSTP_1                               (RNG_CR_BP_POSTP)
/**
  * @}
  */

/** @defgroup RNG_LL_DISABLED Values
  * @{
 */
#define LL_RNG_SR_DISABLED_0                               (0U)
#define LL_RNG_SR_DISABLED_1                               (RNG_SR_DISABLED)
/**
  * @}
  */

/** @defgroup RNG_LL_ALL_OSCS_DOWN Values
  * @{
 */
#define LL_RNG_SR_ALL_OSCS_DOWN_0                          (0U)
#define LL_RNG_SR_ALL_OSCS_DOWN_1                          (RNG_SR_ALL_OSCS_DOWN)
/**
  * @}
  */

/** @defgroup RNG_LL_REVEAL_CLK_ERR Values
  * @{
 */
#define LL_RNG_SR_REVEAL_CLK_ERR_0                         (0U)
#define LL_RNG_SR_REVEAL_CLK_ERR_1                         (RNG_SR_REVEAL_CLK_ERR)
/**
  * @}
  */

/** @defgroup RNG_LL_ENTROPY_ERR Values
  * @{
 */
#define LL_RNG_SR_ENTROPY_ERR_0                            (0U)
#define LL_RNG_SR_ENTROPY_ERR_1                            (RNG_SR_ENTROPY_ERR)
/**
  * @}
  */

/** @defgroup RNG_LL_VAL_READY Values
  * @{
 */
#define LL_RNG_SR_VAL_READY_0                              (0U)
#define LL_RNG_SR_VAL_READY_1                              (RNG_SR_VAL_READY)
/**
  * @}
  */

/** @defgroup RNG_LL_FIFO_FULL Values
  * @{
 */
#define LL_RNG_SR_FIFO_FULL_0                              (0U)
#define LL_RNG_SR_FIFO_FULL_1                              (RNG_SR_FIFO_FULL)
/**
  * @}
  */

/** @defgroup RNG_LL_SRC_HEALTH_DONE Values
  * @{
 */
#define LL_RNG_SR_SRC_HEALTH_DONE_0                        (0U)
#define LL_RNG_SR_SRC_HEALTH_DONE_1                        ( RNG_SR_SRC_HEALTH_DONE)
/**
  * @}
  */

/** @defgroup RNG_LL_REPET_ERROR Values
  * @{
 */
#define LL_RNG_SR_REPET_ERROR_0                            (0U)
#define LL_RNG_SR_REPET_ERROR_1                            (RNG_SR_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_SR_ADAPT_ERROR_0                            (0U)
#define LL_RNG_SR_ADAPT_ERROR_1                            (RNG_SR_ADAPT_ERROR_0)
/**
  * @}
  */

/** @defgroup RNG_LL_OSCS_HEALTH_DONE Values
  * @{
 */
#define LL_RNG_SR_OSCS_HEALTH_DONE_0                       (0U)
#define LL_RNG_SR_OSCS_HEALTH_DONE_1                       (RNG_SR_OSCS_HEALTH_DONE)
/**
  * @}
  */

/** @defgroup RNG_LL_OSCS_REPET_ERROR Values
  * @{
 */
#define LL_RNG_SR_OSCS_REPET_ERROR_0                       (0U)
#define LL_RNG_SR_OSCS_REPET_ERROR_1                       (RNG_SR_OSCS_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_OSCS_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_SR_OSCS_ADAPT_ERROR_0                       (0U)
#define LL_RNG_SR_OSCS_ADAPT_ERROR_1                       ( RNG_SR_OSCS_ADAPT_ERROR)
/**
  * @}
  */


/** @defgroup RNG_LL_PWRD1 Values
  * @{
 */
#define LL_RNG_OSCS_CR_PWRD1_0                             (0U)
#define LL_RNG_OSCS_CR_PWRD1_1                             (RNG_OSCS_CR_PWRD1_0)
#define LL_RNG_OSCS_CR_PWRD1_2                             (RNG_OSCS_CR_PWRD1_1)
#define LL_RNG_OSCS_CR_PWRD1_3                             (RNG_OSCS_CR_PWRD1_1 | RNG_OSCS_CR_PWRD1_0)
#define LL_RNG_OSCS_CR_PWRD1_4                             (RNG_OSCS_CR_PWRD1_2)
#define LL_RNG_OSCS_CR_PWRD1_5                             (RNG_OSCS_CR_PWRD1_2 | RNG_OSCS_CR_PWRD1_0)
#define LL_RNG_OSCS_CR_PWRD1_6                             (RNG_OSCS_CR_PWRD1_2 | RNG_OSCS_CR_PWRD1_1)
#define LL_RNG_OSCS_CR_PWRD1_7                             (RNG_OSCS_CR_PWRD1_2 |\
                                                            RNG_OSCS_CR_PWRD1_1 | RNG_OSCS_CR_PWRD1_0)
/**
  * @}
  */

/** @defgroup RNG_LL_PWRD2 Values
  * @{
 */
#define LL_RNG_OSCS_CR_PWRD2_0                             (0U)
#define LL_RNG_OSCS_CR_PWRD2_1                             (RNG_OSCS_CR_PWRD2_0)
#define LL_RNG_OSCS_CR_PWRD2_2                             (RNG_OSCS_CR_PWRD2_1)
#define LL_RNG_OSCS_CR_PWRD2_3                             (RNG_OSCS_CR_PWRD2_1 | RNG_OSCS_CR_PWRD2_0)
#define LL_RNG_OSCS_CR_PWRD2_4                             ( RNG_OSCS_CR_PWRD2_2)
#define LL_RNG_OSCS_CR_PWRD2_5                             ( RNG_OSCS_CR_PWRD2_2 | RNG_OSCS_CR_PWRD2_0)
#define LL_RNG_OSCS_CR_PWRD2_6                             ( RNG_OSCS_CR_PWRD2_2 | RNG_OSCS_CR_PWRD2_1)
#define LL_RNG_OSCS_CR_PWRD2_7                             ( RNG_OSCS_CR_PWRD2_2 |\
                                                             RNG_OSCS_CR_PWRD2_1 | RNG_OSCS_CR_PWRD2_0  )
/**
  * @}
  */

/** @defgroup RNG_LL_PWRD3 Values
  * @{
 */
#define LL_RNG_OSCS_CR_PWRD3_0                             (0U)
#define LL_RNG_OSCS_CR_PWRD3_1                             (RNG_OSCS_CR_PWRD3_0)
#define LL_RNG_OSCS_CR_PWRD3_2                             (RNG_OSCS_CR_PWRD3_1)
#define LL_RNG_OSCS_CR_PWRD3_3                             (RNG_OSCS_CR_PWRD3_1 | RNG_OSCS_CR_PWRD3_0)
#define LL_RNG_OSCS_CR_PWRD3_4                             (RNG_OSCS_CR_PWRD3_2)
#define LL_RNG_OSCS_CR_PWRD3_5                             (RNG_OSCS_CR_PWRD3_2 | RNG_OSCS_CR_PWRD3_0)
#define LL_RNG_OSCS_CR_PWRD3_6                             (RNG_OSCS_CR_PWRD3_2 | RNG_OSCS_CR_PWRD3_1)
#define LL_RNG_OSCS_CR_PWRD3_7                             (RNG_OSCS_CR_PWRD3_2 |\
                                                            RNG_OSCS_CR_PWRD3_1 | RNG_OSCS_CR_PWRD3_0)
/**
  * @}
  */

/** @defgroup RNG_LL_SYNC_OSCS Values
  * @{
 */
#define LL_RNG_OSCS_CR_SYNC_OSCS_0                         (0U)
#define LL_RNG_OSCS_CR_SYNC_OSCS_1                         (RNG_OSCS_CR_SYNC_OSCS)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_RESET Values
  * @{
 */
#define LL_RNG_POSTP_CR_AES_RESET_0                        (0U)
#define LL_RNG_POSTP_CR_AES_RESET_1                        (RNG_POSTP_CR_AES_RESET)
/**
  * @}
  */

/** @defgroup RNG_LL_NB_LOOP_AES Values
  * @{
 */
#define LL_RNG_POSTP_CR_NB_LOOP_AES_0                      (0U)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_1                      (RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_2                      (RNG_POSTP_CR_NB_LOOP_AES_1)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_3                      (RNG_POSTP_CR_NB_LOOP_AES_1 | RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_4                      (RNG_POSTP_CR_NB_LOOP_AES_2)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_5                      (RNG_POSTP_CR_NB_LOOP_AES_2 | RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_6                      (RNG_POSTP_CR_NB_LOOP_AES_2 | RNG_POSTP_CR_NB_LOOP_AES_1)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_7                      (RNG_POSTP_CR_NB_LOOP_AES_2 | RNG_POSTP_CR_NB_LOOP_AES_1 |\
                                                            RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_8                      (RNG_POSTP_CR_NB_LOOP_AES_3)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_9                      (RNG_POSTP_CR_NB_LOOP_AES_3 | RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_10                     (RNG_POSTP_CR_NB_LOOP_AES_3 | RNG_POSTP_CR_NB_LOOP_AES_1)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_11                     (RNG_POSTP_CR_NB_LOOP_AES_3 |\
                                                            RNG_POSTP_CR_NB_LOOP_AES_1 | RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_12                     (RNG_POSTP_CR_NB_LOOP_AES_3 | RNG_POSTP_CR_NB_LOOP_AES_2)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_13                     (RNG_POSTP_CR_NB_LOOP_AES_3 |\
                                                            RNG_POSTP_CR_NB_LOOP_AES_2 | RNG_POSTP_CR_NB_LOOP_AES_0)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_14                     (RNG_POSTP_CR_NB_LOOP_AES_3 |\
                                                            RNG_POSTP_CR_NB_LOOP_AES_2 | RNG_POSTP_CR_NB_LOOP_AES_1)
#define LL_RNG_POSTP_CR_NB_LOOP_AES_15                     (RNG_POSTP_CR_NB_LOOP_AES_3 | RNG_POSTP_CR_NB_LOOP_AES_2 |\
                                                            RNG_POSTP_CR_NB_LOOP_AES_1 | RNG_POSTP_CR_NB_LOOP_AES_0)
/**
  * @}
  */


/** @defgroup RNG_LL_AES_INIT Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_INIT_0                         (0U)
#define LL_RNG_POSTP_SR_AES_INIT_1                         (RNG_POSTP_SR_AES_INIT)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_KEY_LD Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_KEY_LD_0                       (0U)
#define LL_RNG_POSTP_SR_AES_KEY_LD_1                       (RNG_POSTP_SR_AES_KEY_LD)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_BUSY Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_BUSY_0                         (0U)
#define LL_RNG_POSTP_SR_AES_BUSY_1                         (RNG_POSTP_SR_AES_BUSY)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_HEALTH_DONE Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_HEALTH_DONE_0                  (0U)
#define LL_RNG_POSTP_SR_AES_HEALTH_DONE_1                  (RNG_POSTP_SR_AES_HEALTH_DONE)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_K12_ERROR Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_K12_ERROR_0                    (0U)
#define LL_RNG_POSTP_SR_AES_K12_ERROR_1                    (RNG_POSTP_SR_AES_K12_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_AES_DOUT_ERROR Values
  * @{
 */
#define LL_RNG_POSTP_SR_AES_DOUT_ERROR_0                   (0U)
#define LL_RNG_POSTP_SR_AES_DOUT_ERROR_1                   (RNG_POSTP_SR_AES_DOUT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_ITER_ADAP Values
  * @{
 */
#define LL_RNG_HEALTH_CR_ITER_ADAP_0                       (0U)
#define LL_RNG_HEALTH_CR_ITER_ADAP_1                       (RNG_HEALTH_CR_ITER_ADAP_0)
#define LL_RNG_HEALTH_CR_ITER_ADAP_2                       (RNG_HEALTH_CR_ITER_ADAP_1)
#define LL_RNG_HEALTH_CR_ITER_ADAP_3                       (RNG_HEALTH_CR_ITER_ADAP_1 | RNG_HEALTH_CR_ITER_ADAP_0)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR_1            (RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR_0)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR_1            (RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR_1            (RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR_1            (RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR_1            (RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR_1            (RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR_1            (RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR_1            (RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR_1            (RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR_1            (RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR_1            (RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR_1            (RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR_1            (RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO1_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR_1            (RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR_1            (RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO2_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR_1            (RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_REPET_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR_1            (RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_TO3_ADAPT_ERROR Values
  * @{
 */
#define LL_RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR_0            (0U)
#define LL_RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR_1            (RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR)
/**
  * @}
  */

/** @defgroup RNG_LL_EN_FF_FULL_IRQ Values
  * @{
 */
#define LL_RNG_IRQ_CR_EN_FF_FULL_IRQ_0                     (0U)
#define LL_RNG_IRQ_CR_EN_FF_FULL_IRQ_1                     (RNG_IRQ_CR_EN_FF_FULL_IRQ)
/**
  * @}
  */

/** @defgroup RNG_LL_EN_ERROR_IRQ Values
  * @{
 */
#define LL_RNG_IRQ_CR_EN_ERROR_IRQ_0                       (0U)
#define LL_RNG_IRQ_CR_EN_ERROR_IRQ_1                       (RNG_IRQ_CR_EN_ERROR_IRQ)
/**
  * @}
  */

/** @defgroup RNG_LL_FF_FULL_IRQ Values
  * @{
 */
#define LL_RNG_IRQ_SR_FF_FULL_IRQ_0                        (0U)
#define LL_RNG_IRQ_SR_FF_FULL_IRQ_1                        (RNG_IRQ_SR_FF_FULL_IRQ)
/**
  * @}
  */

/** @defgroup RNG_LL_ERROR_IRQ Values
  * @{
 */
#define LL_RNG_IRQ_SR_ERROR_IRQ_0                          (0U)
#define LL_RNG_IRQ_SR_ERROR_IRQ_1                          (RNG_IRQ_SR_ERROR_IRQ)
/**
  * @}
  */


/**
  * @brief  Enable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Enable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Enable(RNG_TypeDef *RNGx)
{
  MODIFY_REG(RNGx->CR, RNG_CR_DISABLE, LL_RNG_CR_DISABLE_0);
}

/**
  * @brief  Disable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Disable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Disable(RNG_TypeDef *RNGx)
{
  MODIFY_REG(RNGx->CR, RNG_CR_DISABLE, LL_RNG_CR_DISABLE_1);
}

/**
  * @brief  When writing a 1, the value remains until it is seen by RNG core clock domain after
  resynchronization. Then it is automatically reset
  * @note   0x0 no reset
            0x1 reset revclk flag
  * @rmtoll CR          CLR_REVCLK_FLAG       LL_RNG_SetResetRevealClockErrorFlags
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_CR_CLR_REVCLK_FLAG_0
  *         @arg LL_RNG_CR_CLR_REVCLK_FLAG_1
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetResetRevealClockErrorFlags(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->CR, RNG_CR_CLR_REVCLK_FLAG, value);
}

/**
  * @brief  Get the Reset Reveal Clock Error Flag
  * @note   0x0 no reset
  *         0x1 reset revclk flag
  * @rmtoll CR          CLR_REVCLK_FLAG       LL_RNG_GetResetRevealClockErrorFlags
  * @retval can be one of the following values
  *         @arg LL_RNG_CR_CLR_REVCLK_FLAG_0
  *         @arg LL_RNG_CR_CLR_REVCLK_FLAG_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetResetRevealClockErrorFlags(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->CR, RNG_CR_CLR_REVCLK_FLAG));
}

/**
  * @brief  Set the Reset Health Error Flag
    @note   When writing a 1, the value remains until it is seen by RNG core clock domain after resynchronization.
        Then it is automatically reset
            0x0 no reset
            0x1 reset health flag
  * @rmtoll CR          RST_HEALTH_FLAGS       LL_RNG_SetResetHealthErrorFlags
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_CR_RST_HEALTH_FLAGS_0
  *         @arg LL_RNG_CR_RST_HEALTH_FLAGS_1
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetResetHealthErrorFlags(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->CR, RNG_CR_RST_HEALTH_FLAGS, value);
}

/**
  * @brief  Get the Reset Health Error Flag
    @note   When writing a 1, the value remains until it is seen by RNG core clock domain after resynchronization.
     Then it is automatically reset
            0x0 no reset
  * @rmtoll CR          RST_HEALTH_FLAGS       LL_RNG_GetResetHealthErrorFlags
  * @retval can be one of the following values
  *         @arg LL_RNG_CR_RST_HEALTH_FLAGS_0
  *         @arg LL_RNG_CR_RST_HEALTH_FLAGS_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetResetHealthErrorFlags(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->CR, RNG_CR_RST_HEALTH_FLAGS));
}

/**
  * @brief  Set the sampling clock enable divider
    @note   dividing by a factor equal to CLKDIV[15:0] + 1, values being in the range of 0 to 65535
  * @rmtoll CR          CLKDIV_15_0       LL_RNG_SetSamplingClockEnableDivider
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 65535 (form 0x0 to 0xffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetSamplingClockEnableDivider(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->CR, RNG_CR_CLKDIV_15_0, value << RNG_CR_CLKDIV_15_0_Pos);
}

/**
  * @brief  Get the sampling clock enable divider
    @note   dividing by a factor equal to CLKDIV[15:0] + 1, values being in the range of 0 to 65535
  * @rmtoll CR          CLKDIV_15_0       LL_RNG_GetSamplingClockEnableDivider
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetSamplingClockEnableDivider(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->CR, RNG_CR_CLKDIV_15_0) >> RNG_CR_CLKDIV_15_0_Pos);
}


/**
  * @brief  Indicate if DISABLED value Flag is set or not.
  * @note   RNG is disabled
  *         0x0 Normal operation.
  *         0x1 RNG is disabled
  * @rmtoll SR          DISABLED            LL_RNG_IsActiveFlag_DISABLED
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_DISABLED(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_DISABLED) == (RNG_SR_DISABLED)) ? 1U : 0U);
}

/**
  * @brief  Indicate if ALL_OSCS_DOWN value Flag is set or not.
  * @note   All oscillators of the random source noise have been powered down
  *         This can cause the rising of OEC3 flag
  *         0x0 At least one oscillator is ON0x1 All oscillators are down
  * @rmtoll SR          ALL_OSCS_DOWN            LL_RNG_IsActiveFlag_ALL_OSCS_DOWN
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_ALL_OSCS_DOWN(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_ALL_OSCS_DOWN) == (RNG_SR_ALL_OSCS_DOWN)) ? 1U : 0U);
}

/**
  * @brief  Indicate if REVEAL_CLK_ERR value Flag is set or not.
  * @note   The internal clock for the RNG core is not revealed
  *         0x0 Internal clock for RNG clock is present.
  *         0x1 Internal RNG clock is not present
  * @rmtoll SR          REVEAL_CLK_ERR            LL_RNG_IsActiveFlag_REVEAL_CLK_ERR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_REVEAL_CLK_ERR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_REVEAL_CLK_ERR) == (RNG_SR_REVEAL_CLK_ERR)) ? 1U : 0U);
}

/**
  * @brief  Indicate if ENTROPY_ERR value Flag is set or not.
  * @note   The error refers to a fault in the bit sequence detected by the Entropy Monitor. Failed test is
  given by REPET_ERROR, and ADAPT_ERROR, OSCS_REPET_ERROR and OSCS_ADAPT_ERROR status flags
  *         0x0 No fault detected
  *         0x1 Embedded heath monitor detects an error in bit stream quality
  * @rmtoll SR          ENTROPY_ERR            LL_RNG_IsActiveFlag_ENTROPY_ERR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_ENTROPY_ERR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_ENTROPY_ERR) == (RNG_SR_ENTROPY_ERR)) ? 1U : 0U);
}

/**
  * @brief  Indicate if VAL_READY value Flag is set or not.
  * @note   At least one 32-bit random value is available in the data FIFO
  *         Note that application must ensure that a random is available in internal FIFO before starting a
  read otherwise a bus error will be generated
  *         0x0 No value is ready in FIFO.
  *         0x1 A 32-bit value is available in the internal FIFO
  * @rmtoll SR          VAL_READY            LL_RNG_IsActiveFlag_VAL_READY
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_VAL_READY(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_VAL_READY) == (RNG_SR_VAL_READY)) ? 1U : 0U);
}


/**
  * @brief  Indicate if FIFO_FULL value Flag is set or not.
  * @note   Indicates whether random data FIFO is full
  *         0x0 FIFO is not full.
  *         0x1 The internal data FIFO is full and four 32-bit random values can be read
  * @rmtoll SR          FIFO_FULL            LL_RNG_IsActiveFlag_FIFO_FULL
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_FIFO_FULL(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_FIFO_FULL) == (RNG_SR_FIFO_FULL)) ? 1U : 0U);
}

/**
  * @brief  Indicate if SRC_HEALTH_DONE value Flag is set or not.
  * @note   First run of noise source health test is completed
  * @rmtoll SR          SRC_HEALTH_DONE            LL_RNG_IsActiveFlag_SRC_HEALTH_DONE
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_SRC_HEALTH_DONE(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_SRC_HEALTH_DONE) == (RNG_SR_SRC_HEALTH_DONE)) ? 1U : 0U);
}

/**
  * @brief  Indicate if REPET_ERROR value Flag is set or not.
  * @note   Noise source Repetition health test error
  * @rmtoll SR          REPET_ERROR            LL_RNG_IsActiveFlag_REPET_ERROR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_REPET_ERROR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_REPET_ERROR) == (RNG_SR_REPET_ERROR)) ? 1U : 0U);
}

/**
  * @brief  Indicate if ADAPT_ERROR value Flag is set or not.
  * @note   Noise source Adaptive 1024 health test error
  * @rmtoll SR          ADAPT_ERROR            LL_RNG_IsActiveFlag_ADAPT_ERROR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_ADAPT_ERROR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_ADAPT_ERROR) == (RNG_SR_ADAPT_ERROR)) ? 1U : 0U);
}

/**
  * @brief  Indicate if OSCS_HEALTH_DONE value Flag is set or not.
  * @note   First run of source health tests of individual oscillators composing the noise source are completed
  * @rmtoll SR          OSCS_HEALTH_DONE            LL_RNG_IsActiveFlag_OSCS_HEALTH_DONE
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_OSCS_HEALTH_DONE(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_OSCS_HEALTH_DONE) == (RNG_SR_OSCS_HEALTH_DONE)) ? 1U : 0U);
}

/**
  * @brief  Indicate if OSCS_REPET_ERROR value Flag is set or not.
  * @note   Logical OR of repetition health test errors of individual oscillators composing the noise source
  * @rmtoll SR          OSCS_REPET_ERROR            LL_RNG_IsActiveFlag_OSCS_REPET_ERROR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_OSCS_REPET_ERROR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_OSCS_REPET_ERROR) == (RNG_SR_OSCS_REPET_ERROR)) ? 1U : 0U);
}

/**
  * @brief  Indicate if OSCS_ADAPT_ERROR value Flag is set or not.
  * @note   Logical OR of adaptive health test errors of individual oscillators composing the noise source
  * @rmtoll SR          OSCS_ADAPT_ERROR            LL_RNG_IsActiveFlag_OSCS_ADAPT_ERROR
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_OSCS_ADAPT_ERROR(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_OSCS_ADAPT_ERROR) == (RNG_SR_OSCS_ADAPT_ERROR)) ? 1U : 0U);
}


/**
  * @brief  Get the RND_VAL is a 32-bit Random Value
  * @note   This is the output of the internal four-word FIFO. Note that application must ensure that a random is
  available in FIFO by ready VAL_READY flag before starting a read otherwise a null value will be returned
  * @rmtoll VAL          RND_VAL       LL_RNG_GetRndVal
  * @retval a 32-bit Random Value
  */
__STATIC_INLINE uint32_t LL_RNG_GetRndVal(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->VAL, RNG_VAL_RND_VAL) >> RNG_VAL_RND_VAL_Pos);
}

#define LL_RNG_READRANDDATA32 LL_RNG_GetRndVal

/**
  * @brief  Set the Power down of individual oscillators in triple-oscillator block number 1
  * @rmtoll OSCS_CR          PWRD1       LL_RNG_SetPowerDownBlock1
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_OSCS_CR_PWRD1_0
  *         @arg LL_RNG_OSCS_CR_PWRD1_1
  *         @arg LL_RNG_OSCS_CR_PWRD1_2
  *         @arg LL_RNG_OSCS_CR_PWRD1_3
  *         @arg LL_RNG_OSCS_CR_PWRD1_4
  *         @arg LL_RNG_OSCS_CR_PWRD1_5
  *         @arg LL_RNG_OSCS_CR_PWRD1_6
  *         @arg LL_RNG_OSCS_CR_PWRD1_7
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetPowerDownBlock1(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD1, value);
}

/**
  * @brief  Get the Power down of individual oscillators in triple-oscillator block number 1
  * @rmtoll OSCS_CR          PWRD1       LL_RNG_GetPowerDownBlock1
  * @retval can be one of the following values
  *         @arg LL_RNG_OSCS_CR_PWRD1_0
  *         @arg LL_RNG_OSCS_CR_PWRD1_1
  *         @arg LL_RNG_OSCS_CR_PWRD1_2
  *         @arg LL_RNG_OSCS_CR_PWRD1_3
  *         @arg LL_RNG_OSCS_CR_PWRD1_4
  *         @arg LL_RNG_OSCS_CR_PWRD1_5
  *         @arg LL_RNG_OSCS_CR_PWRD1_6
  *         @arg LL_RNG_OSCS_CR_PWRD1_7
  */
__STATIC_INLINE uint32_t LL_RNG_GetPowerDownBlock1(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD1));
}

/**
  * @brief  Set the Power down of individual oscillators in triple-oscillator block number 2
  * @rmtoll OSCS_CR          PWRD2       LL_RNG_SetPowerDownBlock2
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_OSCS_CR_PWRD2_0
  *         @arg LL_RNG_OSCS_CR_PWRD2_1
  *         @arg LL_RNG_OSCS_CR_PWRD2_2
  *         @arg LL_RNG_OSCS_CR_PWRD2_3
  *         @arg LL_RNG_OSCS_CR_PWRD2_4
  *         @arg LL_RNG_OSCS_CR_PWRD2_5
  *         @arg LL_RNG_OSCS_CR_PWRD2_6
  *         @arg LL_RNG_OSCS_CR_PWRD2_7
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetPowerDownBlock2(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD2, value);
}

/**
  * @brief  Get the Power down of individual oscillators in triple-oscillator block number 2
  * @rmtoll OSCS_CR          PWRD2       LL_RNG_GetPowerDownBlock2
  * @retval can be one of the following values
  *         @arg LL_RNG_OSCS_CR_PWRD2_0
  *         @arg LL_RNG_OSCS_CR_PWRD2_1
  *         @arg LL_RNG_OSCS_CR_PWRD2_2
  *         @arg LL_RNG_OSCS_CR_PWRD2_3
  *         @arg LL_RNG_OSCS_CR_PWRD2_4
  *         @arg LL_RNG_OSCS_CR_PWRD2_5
  *         @arg LL_RNG_OSCS_CR_PWRD2_6
  *         @arg LL_RNG_OSCS_CR_PWRD2_7
  */
__STATIC_INLINE uint32_t LL_RNG_GetPowerDownBlock2(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD2));
}

/**
  * @brief  Set the Power down of individual oscillators in triple-oscillator block number 3
  * @rmtoll OSCS_CR          PWRD3       LL_RNG_SetPowerDownBlock3
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_OSCS_CR_PWRD3_0
  *         @arg LL_RNG_OSCS_CR_PWRD3_1
  *         @arg LL_RNG_OSCS_CR_PWRD3_2
  *         @arg LL_RNG_OSCS_CR_PWRD3_3
  *         @arg LL_RNG_OSCS_CR_PWRD3_4
  *         @arg LL_RNG_OSCS_CR_PWRD3_5
  *         @arg LL_RNG_OSCS_CR_PWRD3_6
  *         @arg LL_RNG_OSCS_CR_PWRD3_7
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetPowerDownBlock3(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD3, value);
}

/**
  * @brief  Get the Power down of individual oscillators in triple-oscillator block number 3
  * @rmtoll OSCS_CR          PWRD3       LL_RNG_GetPowerDownBlock3
  * @retval can be one of the following values
  *         @arg LL_RNG_OSCS_CR_PWRD3_0
  *         @arg LL_RNG_OSCS_CR_PWRD3_1
  *         @arg LL_RNG_OSCS_CR_PWRD3_2
  *         @arg LL_RNG_OSCS_CR_PWRD3_3
  *         @arg LL_RNG_OSCS_CR_PWRD3_4
  *         @arg LL_RNG_OSCS_CR_PWRD3_5
  *         @arg LL_RNG_OSCS_CR_PWRD3_6
  *         @arg LL_RNG_OSCS_CR_PWRD3_7
  */
__STATIC_INLINE uint32_t LL_RNG_GetPowerDownBlock3(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->OSCS_CR, RNG_OSCS_CR_PWRD3));
}

/**
  * @brief  Set the When set, selection of resynchronized output of oscillators
  * @note   It is recommended to disable RNG before changing this value
  * @rmtoll OSCS_CR          SYNC_OSCS       LL_RNG_SetSyncOscs
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_OSCS_CR_SYNC_OSCS_0
  *         @arg LL_RNG_OSCS_CR_SYNC_OSCS_1
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetSyncOscs(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->OSCS_CR, RNG_OSCS_CR_SYNC_OSCS, value);
}

/**
  * @brief  Get the When set, selection of resynchronized output of oscillators
  * @note   It is recommended to disable RNG before changing this value
  * @rmtoll OSCS_CR          SYNC_OSCS       LL_RNG_GetSyncOscs
  * @retval can be one of the following values
  *         @arg LL_RNG_OSCS_CR_SYNC_OSCS_0
  *         @arg LL_RNG_OSCS_CR_SYNC_OSCS_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetSyncOscs(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->OSCS_CR, RNG_OSCS_CR_SYNC_OSCS));
}

/**
  * @brief  Set the Reset AES post processing
  * @note   When writing a 1, the AES post processing is reinitialized, resulting in a new key and new state
  generation before 128-bit random words generation. The 1 written is frozen until it is seen by RNG core clock domain
  after resynchronization. Then it is automatically reset. It also reruns analog source health tests0x0 No effect0x1
  Reset AES core
  * @rmtoll POSTP_CR          AES_RESET       LL_RNG_SetAesReset
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_POSTP_CR_AES_RESET_0
  *         @arg LL_RNG_POSTP_CR_AES_RESET_1
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetAesReset(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->POSTP_CR, RNG_POSTP_CR_AES_RESET, value);
}

/**
  * @brief  Get the Reset AES post processing
  * @note   When writing a 1, the AES post processing is reinitialized, resulting in a new key and new state
  generation before 128-bit random words generation. The 1 written is frozen until it is seen by RNG core clock
  domain after resynchronization. Then it is automatically reset. It also reruns analog source health tests0x0 No
  effect0x1 Reset AES core
  * @rmtoll POSTP_CR          AES_RESET       LL_RNG_GetAesReset
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_CR_AES_RESET_0
  *         @arg LL_RNG_POSTP_CR_AES_RESET_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesReset(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_CR, RNG_POSTP_CR_AES_RESET));
}

/**
  * @brief  Set the NB_LOOP_AES is the number of 128-bit words got from the noise source that have to be processed
  by AES for generating a single 128-bit random word
  * @note   By default, this value is set to 2 (128 bits generated before an AES processing).A new AES processing
 is started only when the previous one is completed.0: value means 16 loops
  * @rmtoll POSTP_CR          NB_LOOP_AES       LL_RNG_SetNbLoopAes
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_0
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_1
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_2
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_3
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_4
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_5
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_6
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_7
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_8
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_9
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_10
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_11
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_12
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_13
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_14
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_15
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetNbLoopAes(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->POSTP_CR, RNG_POSTP_CR_NB_LOOP_AES, value);
}

/**
  * @brief  Get the NB_LOOP_AES is the number of 128-bit words got from the noise source that have to be processed by
  AES for generating a single 128-bit random word
  * @note   By default, this value is set to 2 (128 bits generated before an AES processing).A new AES processing is
  started only when the previous one is completed.0: value means 16 loops
  * @rmtoll POSTP_CR          NB_LOOP_AES       LL_RNG_GetNbLoopAes
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_0
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_1
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_2
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_3
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_4
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_5
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_6
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_7
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_8
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_9
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_10
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_11
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_12
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_13
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_14
  *         @arg LL_RNG_POSTP_CR_NB_LOOP_AES_15
  */
__STATIC_INLINE uint32_t LL_RNG_GetNbLoopAes(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_CR, RNG_POSTP_CR_NB_LOOP_AES));
}

/**
  * @brief  Set the Number of 128-bit random words generated before AES automatically resets
  * @note   This number is in the range of 1 to 65535 words. Value 0x0000 means that AES is never reinitialized
  * @rmtoll POSTP_CR          NB_RND_REINIT       LL_RNG_SetNbRndReinit
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 65535 (form 0x0 to 0xffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetNbRndReinit(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->POSTP_CR, RNG_POSTP_CR_NB_RND_REINIT, value << RNG_POSTP_CR_NB_RND_REINIT_Pos);
}

/**
  * @brief  Get the Number of 128-bit random words generated before AES automatically resets
  * @note   This number is in the range of 1 to 65535 words. Value 0x0000 means that AES is never reinitialized
  * @rmtoll POSTP_CR          NB_RND_REINIT       LL_RNG_GetNbRndReinit
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetNbRndReinit(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_CR, RNG_POSTP_CR_NB_RND_REINIT) >> RNG_POSTP_CR_NB_RND_REINIT_Pos);
}

/**
  * @brief  Get the AES Post processing has been fully initialized (key and state) and is ready for generating 128-bit
  random words
  * @note   0x0 AES core is not initialized (no key or state set).0x1 AES core is fully initialized
  * @rmtoll POSTP_SR          AES_INIT       LL_RNG_GetAesInit
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_INIT_0
  *         @arg LL_RNG_POSTP_SR_AES_INIT_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesInit(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_INIT));
}

/**
  * @brief  Get the AES random key has been generated and loaded in AES key register
  * @note   0x0 AES core is waiting for 128 random bits from the entropy sources for generating its key0x1 AES key
  register has been loaded with a random key
  * @rmtoll POSTP_SR          AES_KEY_LD       LL_RNG_GetAesKeyLd
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_KEY_LD_0
  *         @arg LL_RNG_POSTP_SR_AES_KEY_LD_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesKeyLd(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_KEY_LD));
}

/**
  * @brief  Get the AES core is busy, generating a random value
  * @note   0x0 AES core is idle0x1 AES core is busy
  * @rmtoll POSTP_SR          AES_BUSY       LL_RNG_GetAesBusy
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_BUSY_0
  *         @arg LL_RNG_POSTP_SR_AES_BUSY_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesBusy(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_BUSY));
}

/**
  * @brief  Get the AES-CMAC health test is completed
  * @rmtoll POSTP_SR          AES_HEALTH_DONE       LL_RNG_GetAesHealthDone
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_HEALTH_DONE_0
  *         @arg LL_RNG_POSTP_SR_AES_HEALTH_DONE_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesHealthDone(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_HEALTH_DONE));
}

/**
  * @brief  Get the Health test error on AES-CMAC sub-keys generation
  * @rmtoll POSTP_SR          AES_K12_ERROR       LL_RNG_GetAesK12Error
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_K12_ERROR_0
  *         @arg LL_RNG_POSTP_SR_AES_K12_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesK12Error(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_K12_ERROR));
}

/**
  * @brief  Get the Health test error on AES-CMAC output generation
  * @rmtoll POSTP_SR          AES_DOUT_ERROR       LL_RNG_GetAesDoutError
  * @retval can be one of the following values
  *         @arg LL_RNG_POSTP_SR_AES_DOUT_ERROR_0
  *         @arg LL_RNG_POSTP_SR_AES_DOUT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetAesDoutError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->POSTP_SR, RNG_POSTP_SR_AES_DOUT_ERROR));
}

/**
  * @brief  Set the Bits 31 to 0 of AES 128-bit Default Key
  * @rmtoll DEFKEY0          RNG_DEFKEY0       LL_RNG_SetRngDefkey0
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 4294967295 (form 0x0 to 0xffffffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRngDefkey0(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->DEFKEY0, RNG_DEFKEY0_RNG_DEFKEY0, value << RNG_DEFKEY0_RNG_DEFKEY0_Pos);
}

/**
  * @brief  Get the Bits 31 to 0 of AES 128-bit Default Key
  * @rmtoll DEFKEY0          RNG_DEFKEY0       LL_RNG_GetRngDefkey0
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRngDefkey0(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->DEFKEY0, RNG_DEFKEY0_RNG_DEFKEY0) >> RNG_DEFKEY0_RNG_DEFKEY0_Pos);
}

/**
  * @brief  Set the Bits 63 to 31 of AES 128-bit Default Key
  * @rmtoll DEFKEY1          RNG_DEFKEY1       LL_RNG_SetRngDefkey1
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 4294967295 (form 0x0 to 0xffffffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRngDefkey1(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->DEFKEY1, RNG_DEFKEY1_RNG_DEFKEY1, value << RNG_DEFKEY1_RNG_DEFKEY1_Pos);
}

/**
  * @brief  Get the Bits 63 to 31 of AES 128-bit Default Key
  * @rmtoll DEFKEY1          RNG_DEFKEY1       LL_RNG_GetRngDefkey1
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRngDefkey1(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->DEFKEY1, RNG_DEFKEY1_RNG_DEFKEY1) >> RNG_DEFKEY1_RNG_DEFKEY1_Pos);
}

/**
  * @brief  Set the Bits 95 to 64 of AES 128-bit Default Key
  * @rmtoll DEFKEY2          RNG_DEFKEY2       LL_RNG_SetRngDefkey2
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 4294967295 (form 0x0 to 0xffffffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRngDefkey2(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->DEFKEY2, RNG_DEFKEY2_RNG_DEFKEY2, value << RNG_DEFKEY2_RNG_DEFKEY2_Pos);
}

/**
  * @brief  Get the Bits 95 to 64 of AES 128-bit Default Key
  * @rmtoll DEFKEY2          RNG_DEFKEY2       LL_RNG_GetRngDefkey2
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRngDefkey2(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->DEFKEY2, RNG_DEFKEY2_RNG_DEFKEY2) >> RNG_DEFKEY2_RNG_DEFKEY2_Pos);
}

/**
  * @brief  Set the Bits 127 to 96 of AES 128-bit Default Key
  * @rmtoll DEFKEY3          RNG_DEFKEY3       LL_RNG_SetRngDefkey3
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 4294967295 (form 0x0 to 0xffffffff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRngDefkey3(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->DEFKEY3, RNG_DEFKEY3_RNG_DEFKEY3, value << RNG_DEFKEY3_RNG_DEFKEY3_Pos);
}

/**
  * @brief  Get the Bits 127 to 96 of AES 128-bit Default Key
  * @rmtoll DEFKEY3          RNG_DEFKEY3       LL_RNG_GetRngDefkey3
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRngDefkey3(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->DEFKEY3, RNG_DEFKEY3_RNG_DEFKEY3) >> RNG_DEFKEY3_RNG_DEFKEY3_Pos);
}

/**
  * @brief  Set the Cutoff value of Repetition Test
  * @note   The default value is set to 51. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_CR          REPET_CUTOFF       LL_RNG_SetRepetCutoff
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRepetCutoff(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_CR, RNG_HEALTH_CR_REPET_CUTOFF, value << RNG_HEALTH_CR_REPET_CUTOFF_Pos);
}

/**
  * @brief  Get the Cutoff value of Repetition Test
  * @note   The default value is set to 51. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_CR          REPET_CUTOFF       LL_RNG_GetRepetCutoff
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRepetCutoff(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_CR, RNG_HEALTH_CR_REPET_CUTOFF) >> RNG_HEALTH_CR_REPET_CUTOFF_Pos);
}

/**
  * @brief  Set the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_CR          ADAP_CUTOFF       LL_RNG_SetAdapCutoff
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 1023 (form 0x0 to 0x3ff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetAdapCutoff(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_CR, RNG_HEALTH_CR_ADAP_CUTOFF, value << RNG_HEALTH_CR_ADAP_CUTOFF_Pos);
}

/**
  * @brief  Get the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_CR          ADAP_CUTOFF       LL_RNG_GetAdapCutoff
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetAdapCutoff(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_CR, RNG_HEALTH_CR_ADAP_CUTOFF) >> RNG_HEALTH_CR_ADAP_CUTOFF_Pos);
}

/**
  * @brief  Set the Number of iterations minus 1 of Adaptive test during initialization phase
  * @note   Default value is set to 0 i.e. 1 iteration
  * @rmtoll HEALTH_CR          ITER_ADAP       LL_RNG_SetIterAdap
  * @param  RNGx RNG Instance
  * @param  value can be one of the following values:
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_0
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_1
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_2
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_3
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetIterAdap(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_CR, RNG_HEALTH_CR_ITER_ADAP, value);
}

/**
  * @brief  Get the Number of iterations minus 1 of Adaptive test during initialization phase
  * @note   Default value is set to 0 i.e. 1 iteration
  * @rmtoll HEALTH_CR          ITER_ADAP       LL_RNG_GetIterAdap
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_0
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_1
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_2
  *         @arg LL_RNG_HEALTH_CR_ITER_ADAP_3
  */
__STATIC_INLINE uint32_t LL_RNG_GetIterAdap(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_CR, RNG_HEALTH_CR_ITER_ADAP));
}

/**
  * @brief  Set the Cutoff value of Repetition Test
  * @note   The default value is set to 51. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC1_CR          REPET_CUTOFF_OSC1       LL_RNG_SetRepetCutoffOsc1
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRepetCutoffOsc1(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC1_CR, RNG_HEALTH_OSC1_CR_REPET_CUTOFF_OSC1,
             value << RNG_HEALTH_OSC1_CR_REPET_CUTOFF_OSC1_Pos);
}

/**
  * @brief  Get the Cutoff value of Repetition Test
  * @note   The default value is set to 51. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC1_CR          REPET_CUTOFF_OSC1       LL_RNG_GetRepetCutoffOsc1
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRepetCutoffOsc1(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_CR,
                             RNG_HEALTH_OSC1_CR_REPET_CUTOFF_OSC1) >> RNG_HEALTH_OSC1_CR_REPET_CUTOFF_OSC1_Pos);
}

/**
  * @brief  Set the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC1_CR          ADAP_CUTOFF_OSC1       LL_RNG_SetAdapCutoffOsc1
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 1023 (form 0x0 to 0x3ff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetAdapCutoffOsc1(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC1_CR, RNG_HEALTH_OSC1_CR_ADAP_CUTOFF_OSC1,
             value << RNG_HEALTH_OSC1_CR_ADAP_CUTOFF_OSC1_Pos);
}

/**
  * @brief  Get the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior
  of RNG
  * @rmtoll HEALTH_OSC1_CR          ADAP_CUTOFF_OSC1       LL_RNG_GetAdapCutoffOsc1
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetAdapCutoffOsc1(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_CR,
                             RNG_HEALTH_OSC1_CR_ADAP_CUTOFF_OSC1) >> RNG_HEALTH_OSC1_CR_ADAP_CUTOFF_OSC1_Pos);
}

/**
  * @brief  Set the Cutoff value of Repetition Test
  * @note   The default value is set to 51.Caution: To be handled with care as any change can lead to misbehavior
  of RNG
  * @rmtoll HEALTH_OSC2_CR          REPET_CUTOFF_OSC2       LL_RNG_SetRepetCutoffOsc2
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRepetCutoffOsc2(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC2_CR, RNG_HEALTH_OSC2_CR_REPET_CUTOFF_OSC2,
             value << RNG_HEALTH_OSC2_CR_REPET_CUTOFF_OSC2_Pos);
}

/**
  * @brief  Get the Cutoff value of Repetition Test
  * @note   The default value is set to 51.Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC2_CR          REPET_CUTOFF_OSC2       LL_RNG_GetRepetCutoffOsc2
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRepetCutoffOsc2(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_CR,
                             RNG_HEALTH_OSC2_CR_REPET_CUTOFF_OSC2) >> RNG_HEALTH_OSC2_CR_REPET_CUTOFF_OSC2_Pos);
}

/**
  * @brief  Set the Cutoff value of Adaptive Test
  * @note   The default value is set to 699.Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC2_CR          ADAP_CUTOFF_OSC2       LL_RNG_SetAdapCutoffOsc2
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 1023 (form 0x0 to 0x3ff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetAdapCutoffOsc2(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC2_CR, RNG_HEALTH_OSC2_CR_ADAP_CUTOFF_OSC2,
             value << RNG_HEALTH_OSC2_CR_ADAP_CUTOFF_OSC2_Pos);
}

/**
  * @brief  Get the Cutoff value of Adaptive Test
  * @note   The default value is set to 699.Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC2_CR          ADAP_CUTOFF_OSC2       LL_RNG_GetAdapCutoffOsc2
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetAdapCutoffOsc2(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_CR,
                             RNG_HEALTH_OSC2_CR_ADAP_CUTOFF_OSC2) >> RNG_HEALTH_OSC2_CR_ADAP_CUTOFF_OSC2_Pos);
}

/**
  * @brief  Set the Cutoff value of Repetition Test
  * @note   The default value is set to 51.Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC3_CR          REPET_CUTOFF_OSC3       LL_RNG_SetRepetCutoffOsc3
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 255 (form 0x0 to 0xff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetRepetCutoffOsc3(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC3_CR, RNG_HEALTH_OSC3_CR_REPET_CUTOFF_OSC3,
             value << RNG_HEALTH_OSC3_CR_REPET_CUTOFF_OSC3_Pos);
}

/**
  * @brief  Get the Cutoff value of Repetition Test
  * @note   The default value is set to 51.Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC3_CR          REPET_CUTOFF_OSC3       LL_RNG_GetRepetCutoffOsc3
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetRepetCutoffOsc3(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_CR,
                             RNG_HEALTH_OSC3_CR_REPET_CUTOFF_OSC3) >> RNG_HEALTH_OSC3_CR_REPET_CUTOFF_OSC3_Pos);
}

/**
  * @brief  Set the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior of
  RNG
  * @rmtoll HEALTH_OSC3_CR          ADAP_CUTOFF_OSC3       LL_RNG_SetAdapCutoffOsc3
  * @param  RNGx RNG Instance
  * @param  value parameter must be a number between 0 and 1023 (form 0x0 to 0x3ff)
  * @retval None
  */
__STATIC_INLINE void LL_RNG_SetAdapCutoffOsc3(RNG_TypeDef *RNGx, uint32_t value)
{
  MODIFY_REG(RNGx->HEALTH_OSC3_CR, RNG_HEALTH_OSC3_CR_ADAP_CUTOFF_OSC3,
             value << RNG_HEALTH_OSC3_CR_ADAP_CUTOFF_OSC3_Pos);
}

/**
  * @brief  Get the Cutoff value of Adaptive Test
  * @note   The default value is set to 699. Caution: To be handled with care as any change can lead to misbehavior
  of RNG
  * @rmtoll HEALTH_OSC3_CR          ADAP_CUTOFF_OSC3       LL_RNG_GetAdapCutoffOsc3
  * @retval can be one of the following values
  */
__STATIC_INLINE uint32_t LL_RNG_GetAdapCutoffOsc3(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_CR,
                             RNG_HEALTH_OSC3_CR_ADAP_CUTOFF_OSC3) >> RNG_HEALTH_OSC3_CR_ADAP_CUTOFF_OSC3_Pos);
}

/**
  * @brief  Get the Repetition error flag of first oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO1_REPET_ERROR       LL_RNG_GetOSC1_To1RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC1_To1RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO1_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO1_ADAPT_ERROR       LL_RNG_GetOSC1_To1AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC1_To1AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO1_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO2_REPET_ERROR       LL_RNG_GetOSC_To2RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC_To2RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO2_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO2_ADAPT_ERROR       LL_RNG_GetOSC_To2AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC_To2AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO2_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO3_REPET_ERROR       LL_RNG_GetTo3RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetTo3RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO3_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC1_SR          TO3_ADAPT_ERROR       LL_RNG_GetTo3AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetTo3AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC1_SR, RNG_HEALTH_OSC1_SR_TO3_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag
  * @note   Repetition error flag of first oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO1_REPET_ERROR       LL_RNG_GetOSC2_To1RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC2_To1RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO1_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag
  * @note   Adaptive error flag of first oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO1_ADAPT_ERROR       LL_RNG_GetOSC2_To1AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC2_To1AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO1_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO2_REPET_ERROR       LL_RNG_GetOSC2_To2RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC2_To2RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO2_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO2_ADAPT_ERROR       LL_RNG_GetOSC2_To2AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC2_To2AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO2_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO3_REPET_ERROR       LL_RNG_GetOSC2_To3RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_OSC2_GetTo3RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO3_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC2_SR          TO3_ADAPT_ERROR       LL_RNG_GetOSC2_To3AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC2_To3AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC2_SR, RNG_HEALTH_OSC2_SR_TO3_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of third oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO1_REPET_ERROR       LL_RNG_GetOSC3_To1RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To1RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO1_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of first triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO1_ADAPT_ERROR       LL_RNG_GetOSC3_To1AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To1AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO1_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO2_REPET_ERROR       LL_RNG_GetOSC3_To2RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To2RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO2_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of second triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO2_ADAPT_ERROR       LL_RNG_GetOSC3_To2AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To2AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO2_ADAPT_ERROR));
}

/**
  * @brief  Get the Repetition error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO3_REPET_ERROR       LL_RNG_GetOSC3_To3RepetError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To3RepetError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO3_REPET_ERROR));
}

/**
  * @brief  Get the Adaptive error flag of first oscillator of third triple-oscillator cell
  * @rmtoll HEALTH_OSC3_SR          TO3_ADAPT_ERROR       LL_RNG_GetOSC3_To3AdaptError
  * @retval can be one of the following values
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR_0
  *         @arg LL_RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetOSC3_To3AdaptError(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->HEALTH_OSC3_SR, RNG_HEALTH_OSC3_SR_TO3_ADAPT_ERROR));
}

/**
  * @brief  RNG Enable Enable the interrupt when the output fifo is full of new random
  * @rmtoll IRQ_CR          EN_FF_FULL_IRQ            LL_RNG_EnableEnFfFullIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_EnableEnFfFullIrq(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_FF_FULL_IRQ);
}

/**
  * @brief  RNG Disable Enable the interrupt when the output fifo is full of new random
  * @rmtoll IRQ_CR          EN_FF_FULL_IRQ            LL_RNG_DisableEnFfFullIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_DisableEnFfFullIrq(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_FF_FULL_IRQ);
}

/**
  * @brief  Indicate if EN_FF_FULL_IRQ is enabled. Enable the interrupt when the output fifo is full of new random
  * @rmtoll IRQ_CR          EN_FF_FULL_IRQ            LL_RNG_IsEnabledEnFfFullIrq
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsEnabledEnFfFullIrq(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_FF_FULL_IRQ) == (RNG_IRQ_CR_EN_FF_FULL_IRQ)) ? 1U : 0U);
}

/**
  * @brief  RNG Enable Enable the interrupt when an error is reported by the health tests
  * @rmtoll IRQ_CR          EN_ERROR_IRQ            LL_RNG_EnableEnErrorIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_EnableEnErrorIrq(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_ERROR_IRQ);
}

/**
  * @brief  RNG Disable Enable the interrupt when an error is reported by the health tests
  * @rmtoll IRQ_CR          EN_ERROR_IRQ            LL_RNG_DisableEnErrorIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_DisableEnErrorIrq(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_ERROR_IRQ);
}

/**
  * @brief  Indicate if EN_ERROR_IRQ is enabled. Enable the interrupt when an error is reported by the health tests
  * @rmtoll IRQ_CR          EN_ERROR_IRQ            LL_RNG_IsEnabledEnErrorIrq
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsEnabledEnErrorIrq(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->IRQ_CR, RNG_IRQ_CR_EN_ERROR_IRQ) == (RNG_IRQ_CR_EN_ERROR_IRQ)) ? 1U : 0U);
}


/**
  * @brief  Get the Set to 1 when the output fifo is full of new random
  * @note   Flag is cleared by writing a 1
  * @rmtoll IRQ_SR          FF_FULL_IRQ       LL_RNG_GetFfFullIrq
  * @retval can be one of the following values
  *         @arg LL_RNG_IRQ_SR_FF_FULL_IRQ_0
  *         @arg LL_RNG_IRQ_SR_FF_FULL_IRQ_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetFfFullIrq(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->IRQ_SR, RNG_IRQ_SR_FF_FULL_IRQ));
}

/**
  * @brief  Get the Set to 1 when an error is reported by the health tests
  * @note   Flag is cleared by writing a 1
  * @rmtoll IRQ_SR          ERROR_IRQ       LL_RNG_GetErrorIrq
  * @retval can be one of the following values
  *         @arg LL_RNG_IRQ_SR_ERROR_IRQ_0
  *         @arg LL_RNG_IRQ_SR_ERROR_IRQ_1
  */
__STATIC_INLINE uint32_t LL_RNG_GetErrorIrq(RNG_TypeDef *RNGx)
{
  return (uint32_t)(READ_BIT(RNGx->IRQ_SR, RNG_IRQ_SR_ERROR_IRQ));
}

/**
  * @brief  Clear the FF_FULL_IRQ flag
  * @note   Flag is cleared by writing a 1
  * @rmtoll IRQ_SR          FF_FULL_IRQ       LL_RNG_ClearFfFullIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_ClearFfFullIrq(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->IRQ_SR, RNG_IRQ_SR_FF_FULL_IRQ);
}
/**
  * @brief  Clear the ERROR_IRQ flag
  * @note   Flag is cleared by writing a 1
  * @rmtoll IRQ_SR          ERROR_IRQ       LL_RNG_ClearErrorIrq
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_ClearErrorIrq(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->IRQ_SR, RNG_IRQ_SR_ERROR_IRQ);
}
/**
  * @brief  Check if Random Number Generator is enabled
  * @rmtoll CR           RNG_DIS         LL_RNG_IsEnabled
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsEnabled(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->CR, RNG_CR_DISABLE) != (RNG_CR_DISABLE)) ? 1UL : 0UL);
}

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, LL_RNG_InitTypeDef *RNG_InitStruct);
void LL_RNG_StructInit(LL_RNG_InitTypeDef *RNG_InitStruct);
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

#endif /* STM32WB09 */
#if defined (STM32WB07) || defined (STM32WB06) || defined(STM32WB05)
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_ES_Init_Struct RNG Exported Init structures
  * @{
  */

/**
  * @brief LL RNG Init Structure Definition
  */
typedef struct
{
  uint32_t         ClockDetection; /*!< RNG Clock detection.
                                      This parameter can be modified using unitary functions @ref
                    LL_RNG_EnableClkDetect(). */
} LL_RNG_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Constants RNG Exported Constants
  * @{
  */

/** @defgroup RNG_LL_CLK_DET Logic that detects the presence of the RNG Clock
  * @{
  */
#define LL_RNG_CLK_DET_DISABLE        0x00000000U              /*!< RNG Clock detection disabled  */
#define LL_RNG_CLK_DET_ENABLE         RNG_CR_TST_CLK           /*!< RNG Clock detection enabled   */
/**
  * @}
  */

/** @defgroup RNG_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RNG_ReadReg function
  * @{
  */
#define LL_RNG_SR_RNGRDY RNG_SR_RNGRDY    /*!< Register contains valid random data */
#define LL_RNG_SR_REVCLK RNG_SR_REVCLK    /*!< Clock Reveal bit                    */
#define LL_RNG_SR_FAULT  RNG_SR_FAULT     /*!< Fault Reveal bit                    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Macros RNG Exported Macros
  * @{
  */

/** @defgroup RNG_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RNG register
  * @param  __INSTANCE__ RNG Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RNG_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RNG register
  * @param  __INSTANCE__ RNG Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RNG_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup RNG_LL_Exported_Functions RNG Exported Functions
  * @{
  */
/** @defgroup RNG_LL_EF_Configuration RNG Configuration functions
  * @{
  */

/**
  * @brief  Enable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Enable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Enable(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->CR, RNG_CR_RNG_DIS);
}

/**
  * @brief  Disable Random Number Generation
  * @rmtoll CR           RNG_DIS         LL_RNG_Disable
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_Disable(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->CR, RNG_CR_RNG_DIS);
}

/**
  * @brief  Check if Random Number Generator is enabled
  * @rmtoll CR           RNG_DIS         LL_RNG_IsEnabled
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsEnabled(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->CR, RNG_CR_RNG_DIS) != (RNG_CR_RNG_DIS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable RNG Clock detection
  * @rmtoll CR           TST_CLK           LL_RNG_EnableClkDetect
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_EnableClkDetect(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->CR, RNG_CR_TST_CLK);
}

/**
  * @brief  Disable RNG Clock detection
  * @rmtoll CR           TST_CLK         LL_RNG_DisableClkDetect
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_DisableClkDetect(RNG_TypeDef *RNGx)
{
  CLEAR_BIT(RNGx->CR, RNG_CR_TST_CLK);
}

/**
  * @}
  */

/** @defgroup RNG_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Indicate if the RNG value ready Flag is set or not
  * @rmtoll SR           RNGRDY          LL_RNG_IsActiveFlag_RNGRDY
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_RNGRDY(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_RNGRDY) == (RNG_SR_RNGRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if the Clock Reveal Status Flag is set or not
  * @rmtoll SR           REVCLK          LL_RNG_IsActiveFlag_REVCLK
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_REVCLK(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_REVCLK) == (RNG_SR_REVCLK)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if the Fault Reveal Flag is set or not
  * @rmtoll SR           FAULT          LL_RNG_IsActiveFlag_FAULT
  * @param  RNGx RNG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RNG_IsActiveFlag_FAULT(RNG_TypeDef *RNGx)
{
  return ((READ_BIT(RNGx->SR, RNG_SR_FAULT) == (RNG_SR_FAULT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Fault Reveal Flag Flag
  * @rmtoll SR           FAULT          LL_RNG_ClearFlag_FAULT
  * @param  RNGx RNG Instance
  * @retval None
  */
__STATIC_INLINE void LL_RNG_ClearFlag_FAULT(RNG_TypeDef *RNGx)
{
  SET_BIT(RNGx->SR, RNG_SR_FAULT);
}

/**
  * @}
  */

/** @defgroup RNG_LL_EF_Data_Management Data Management
  * @{
  */

/**
  * @brief  Return16-bit Random Number value
  * @rmtoll DR           RNDATA        LL_RNG_ReadRandData16
  * @param  RNGx RNG Instance
  * @retval Generated 16-bit random value
  */
__STATIC_INLINE uint16_t LL_RNG_ReadRandData16(RNG_TypeDef *RNGx)
{
  return (uint16_t)(READ_REG(RNGx->VAL));
}

/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RNG_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_RNG_Init(RNG_TypeDef *RNGx, LL_RNG_InitTypeDef *RNG_InitStruct);
void LL_RNG_StructInit(LL_RNG_InitTypeDef *RNG_InitStruct);
ErrorStatus LL_RNG_DeInit(RNG_TypeDef *RNGx);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */
#endif /* STM32WB07 || STM32WB06 || STM32WB05*/
/**
  * @}
  */
#endif /* RNG */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WB0x_LL_RNG_H */
