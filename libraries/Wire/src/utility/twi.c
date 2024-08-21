/**
  ******************************************************************************
  * @file    twi.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide the TWI interface
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  *
  ******************************************************************************
  */
#include "core_debug.h"
#include "utility/twi.h"
#include "PinAF_STM32F1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Private Defines */
/// @brief I2C timeout in tick unit
#ifndef I2C_TIMEOUT_TICK
#define I2C_TIMEOUT_TICK        100
#endif

#define SLAVE_MODE_TRANSMIT     0
#define SLAVE_MODE_RECEIVE      1
#define SLAVE_MODE_LISTEN       2

/* Generic definition for series requiring I2C timing calculation */
#if !defined (STM32F1xx) && !defined (STM32F2xx) && !defined (STM32F4xx) &&\
    !defined (STM32L1xx)
#define I2C_TIMING
#if !defined(I2C_TIMING_SM) || !defined(I2C_TIMING_FM) || !defined(I2C_TIMING_FMP)
#define I2C_TIMING_COMPUTE
#endif /* !(I2C_TIMING_SM) || !(I2C_TIMING_FM) || !(I2C_TIMING_FMP)*/

#endif

#ifdef I2C_TIMING_COMPUTE
#ifndef I2C_VALID_TIMING_NBR
#define I2C_VALID_TIMING_NBR          8U
#endif
#define I2C_ANALOG_FILTER_DELAY_MIN  50U /* ns */
#ifndef I2C_ANALOG_FILTER_DELAY_MAX
#define I2C_ANALOG_FILTER_DELAY_MAX 260U /* ns */
#endif
#ifndef I2C_USE_ANALOG_FILTER
#define I2C_USE_ANALOG_FILTER         1U
#endif
#ifndef I2C_DIGITAL_FILTER_COEF
#define I2C_DIGITAL_FILTER_COEF       0U
#endif
#define I2C_PRESC_MAX                16U
#define I2C_SCLDEL_MAX               16U
#define I2C_SDADEL_MAX               16U
#define I2C_SCLH_MAX                256U
#define I2C_SCLL_MAX                256U
#define SEC2NSEC            1000000000UL

typedef enum {
  I2C_SPEED_FREQ_STANDARD,  /* 100 kHz */
  I2C_SPEED_FREQ_FAST,      /* 400 kHz */
  I2C_SPEED_FREQ_FAST_PLUS, /* 1 MHz */
  I2C_SPEED_FREQ_NUMBER     /* Must be the last entry */
} I2C_speed_freq_t;

typedef struct {
  uint32_t input_clock;      /* I2C Input clock */
  uint32_t timing;           /* I2C timing corresponding to Input clock */
} I2C_timing_t;

static I2C_timing_t I2C_ClockTiming[I2C_SPEED_FREQ_NUMBER] = {0};

typedef struct {
  uint32_t freq;      /* Frequency in Hz */
  uint32_t freq_min;  /* Minimum frequency in Hz */
  uint32_t freq_max;  /* Maximum frequency in Hz */
  uint16_t hddat_min; /* Minimum data hold time in ns */
  uint16_t vddat_max; /* Maximum data valid time in ns */
  uint16_t sudat_min; /* Minimum data setup time in ns */
  uint16_t lscl_min;  /* Minimum low period of the SCL clock in ns */
  uint16_t hscl_min;  /* Minimum high period of SCL clock in ns */
  uint16_t trise;     /* Rise time in ns */
  uint16_t tfall;     /* Fall time in ns */
  uint8_t dnf;       /* Digital noise filter coefficient */
} I2C_Charac_t;

static const I2C_Charac_t I2C_Charac[] = {
  [I2C_SPEED_FREQ_STANDARD] =
  {
    .freq = 100000,
    .freq_min = 80000,
    .freq_max = 120000,
    .hddat_min = 0,
    .vddat_max = 3450,
    .sudat_min = 250,
    .lscl_min = 4700,
    .hscl_min = 4000,
    .trise = 640,
    .tfall = 20,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST] =
  {
    .freq = 400000,
    .freq_min = 320000,
    .freq_max = 480000,
    .hddat_min = 0,
    .vddat_max = 900,
    .sudat_min = 100,
    .lscl_min = 1300,
    .hscl_min = 600,
    .trise = 250,
    .tfall = 100,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST_PLUS] =
  {
    .freq = 1000000,
    .freq_min = 800000,
    .freq_max = 1200000,
    .hddat_min = 0,
    .vddat_max = 450,
    .sudat_min = 50,
    .lscl_min = 500,
    .hscl_min = 260,
    .trise = 60,
    .tfall = 100,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  }
};
#endif /* I2C_TIMING_COMPUTE */

/*  Family specific description for I2C */
typedef enum {
#if defined(I2C1_BASE)
  I2C1_INDEX,
#endif
#if defined(I2C2_BASE)
  I2C2_INDEX,
#endif
#if defined(I2C3_BASE)
  I2C3_INDEX,
#endif
#if defined(I2C4_BASE)
  I2C4_INDEX,
#endif
#if defined(I2C5_BASE)
  I2C5_INDEX,
#endif
#if defined(I2C6_BASE)
  I2C6_INDEX,
#endif
  I2C_NUM
} i2c_index_t;

/* Private Variables */
static I2C_HandleTypeDef *i2c_handles[I2C_NUM];

#ifdef I2C_TIMING_COMPUTE
/**
  * @brief  This function return the I2C clock source frequency.
  * @param  i2c: I2C instance
  * @retval frequency in Hz
  */
static uint32_t i2c_getClkFreq(I2C_TypeDef *i2c)
{
  uint32_t clkSrcFreq = 0;
#ifdef STM32H7xx
  PLL3_ClocksTypeDef PLL3_Clocks;
#endif
#if defined(I2C1_BASE)
  if (i2c == I2C1) {
#if defined(RCC_PERIPHCLK_I2C1) || defined(RCC_PERIPHCLK_I2C12)
#ifdef RCC_PERIPHCLK_I2C1
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C1);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C12);
#endif
    if (clkSrcFreq == 0)
#endif
    {
#ifdef __HAL_RCC_GET_I2C1_SOURCE
      switch (__HAL_RCC_GET_I2C1_SOURCE()) {
#ifdef RCC_I2C1CLKSOURCE_HSI
        case RCC_I2C1CLKSOURCE_HSI:
          clkSrcFreq = HSI_VALUE;
          break;
#endif
#ifdef RCC_I2C1CLKSOURCE_HSIKER
        case RCC_I2C1CLKSOURCE_HSIKER:
          clkSrcFreq = __LL_RCC_CALC_HSIKER_FREQ(LL_RCC_HSIKER_GetDivider());
          break;
#endif
#ifdef RCC_I2C1CLKSOURCE_SYSCLK
        case RCC_I2C1CLKSOURCE_SYSCLK:
          clkSrcFreq = SystemCoreClock;
          break;
#endif
#if defined(RCC_I2C1CLKSOURCE_PCLK1) || defined(RCC_I2C1CLKSOURCE_D2PCLK1)
#ifdef RCC_I2C1CLKSOURCE_PCLK1
        case RCC_I2C1CLKSOURCE_PCLK1:
#endif
#ifdef RCC_I2C1CLKSOURCE_D2PCLK1
        case RCC_I2C1CLKSOURCE_D2PCLK1:
#endif
          clkSrcFreq = HAL_RCC_GetPCLK1Freq();
          break;
#endif
#ifdef RCC_I2C1CLKSOURCE_CSI
        case RCC_I2C1CLKSOURCE_CSI:
          clkSrcFreq = CSI_VALUE;
          break;
#endif
#ifdef RCC_I2C1CLKSOURCE_PLL3
        case RCC_I2C1CLKSOURCE_PLL3:
          HAL_RCCEx_GetPLL3ClockFreq(&PLL3_Clocks);
          clkSrcFreq = PLL3_Clocks.PLL3_R_Frequency;
          break;
#endif
        default:
          Error_Handler();
      }
#else
      Error_Handler();
#endif
    }
  }
#endif // I2C1_BASE
#if defined(I2C2_BASE)
  if (i2c == I2C2) {
#if defined(RCC_PERIPHCLK_I2C2) || defined(RCC_PERIPHCLK_I2C12)
#ifdef RCC_PERIPHCLK_I2C2
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C2);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C12);
#endif
    if (clkSrcFreq == 0)
#endif
    {
#ifdef __HAL_RCC_GET_I2C2_SOURCE
      switch (__HAL_RCC_GET_I2C2_SOURCE()) {
        case RCC_I2C2CLKSOURCE_HSI:
          clkSrcFreq = HSI_VALUE;
          break;
#ifdef RCC_I2C2CLKSOURCE_SYSCLK
        case RCC_I2C2CLKSOURCE_SYSCLK:
          clkSrcFreq = SystemCoreClock;
          break;
#endif
#if defined(RCC_I2C2CLKSOURCE_PCLK1) || defined(RCC_I2C2CLKSOURCE_D2PCLK1)
#ifdef RCC_I2C2CLKSOURCE_PCLK1
        case RCC_I2C2CLKSOURCE_PCLK1:
#endif
#ifdef RCC_I2C2CLKSOURCE_D2PCLK1
        case RCC_I2C2CLKSOURCE_D2PCLK1:
#endif
          clkSrcFreq = HAL_RCC_GetPCLK1Freq();
          break;
#endif
#ifdef RCC_I2C2CLKSOURCE_CSI
        case RCC_I2C2CLKSOURCE_CSI:
          clkSrcFreq = CSI_VALUE;
          break;
#endif
#ifdef RCC_I2C2CLKSOURCE_PLL3
        case RCC_I2C2CLKSOURCE_PLL3:
          HAL_RCCEx_GetPLL3ClockFreq(&PLL3_Clocks);
          clkSrcFreq = PLL3_Clocks.PLL3_R_Frequency;
          break;
#endif
        default:
          Error_Handler();
      }
#else
      /* STM32 L0/G0 I2C2 has no independent clock */
      clkSrcFreq = HAL_RCC_GetPCLK1Freq();
#endif
    }
  }
#endif // I2C2_BASE
#if defined(I2C3_BASE)
  if (i2c == I2C3) {
#if defined(RCC_PERIPHCLK_I2C3) || defined(RCC_PERIPHCLK_I2C35)
#ifdef RCC_PERIPHCLK_I2C3
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C3);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C35);
#endif
    if (clkSrcFreq == 0)
#endif
    {
#if defined(__HAL_RCC_GET_I2C3_SOURCE)
      switch (__HAL_RCC_GET_I2C3_SOURCE()) {
        case RCC_I2C3CLKSOURCE_HSI:
          clkSrcFreq = HSI_VALUE;
          break;
#ifdef RCC_I2C3CLKSOURCE_SYSCLK
        case RCC_I2C3CLKSOURCE_SYSCLK:
          clkSrcFreq = SystemCoreClock;
          break;
#endif
#if defined(RCC_I2C3CLKSOURCE_PCLK1) || defined(RCC_I2C3CLKSOURCE_D2PCLK1)
#ifdef RCC_I2C3CLKSOURCE_PCLK1
        case RCC_I2C3CLKSOURCE_PCLK1:
#endif
#ifdef RCC_I2C3CLKSOURCE_D2PCLK1
        case RCC_I2C3CLKSOURCE_D2PCLK1:
#endif
          clkSrcFreq = HAL_RCC_GetPCLK1Freq();
          break;
#endif
#ifdef RCC_I2C3CLKSOURCE_CSI
        case RCC_I2C3CLKSOURCE_CSI:
          clkSrcFreq = CSI_VALUE;
          break;
#endif
#ifdef RCC_I2C3CLKSOURCE_PLL3
        case RCC_I2C3CLKSOURCE_PLL3:
          HAL_RCCEx_GetPLL3ClockFreq(&PLL3_Clocks);
          clkSrcFreq = PLL3_Clocks.PLL3_R_Frequency;
          break;
#endif
        default:
          Error_Handler();
      }
#else
      /* STM32 G0 I2C3 has no independent clock */
      clkSrcFreq = HAL_RCC_GetPCLK1Freq();
#endif
    }
  }
#endif // I2C3_BASE
#if defined(I2C4_BASE)
  if (i2c == I2C4) {
#if defined(RCC_PERIPHCLK_I2C4) || defined(RCC_PERIPHCLK_I2C46)
#ifdef RCC_PERIPHCLK_I2C4
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C4);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C46);
#endif
    if (clkSrcFreq == 0)
#endif
    {
#if defined(__HAL_RCC_GET_I2C4_SOURCE)
      switch (__HAL_RCC_GET_I2C4_SOURCE()) {
#ifdef RCC_I2C4CLKSOURCE_HSI
        case RCC_I2C4CLKSOURCE_HSI:
          clkSrcFreq = HSI_VALUE;
          break;
#endif
#ifdef RCC_I2C4CLKSOURCE_SYSCLK
        case RCC_I2C4CLKSOURCE_SYSCLK:
          clkSrcFreq = SystemCoreClock;
          break;
#endif
#ifdef RCC_I2C4CLKSOURCE_PCLK1
        case RCC_I2C4CLKSOURCE_PCLK1:
          clkSrcFreq = HAL_RCC_GetPCLK1Freq();
          break;
#endif
#ifdef RCC_I2C4CLKSOURCE_D3PCLK1
        case RCC_I2C4CLKSOURCE_D3PCLK1:
          clkSrcFreq = HAL_RCCEx_GetD3PCLK1Freq();
          break;
#endif
#ifdef RCC_I2C4CLKSOURCE_CSI
        case RCC_I2C4CLKSOURCE_CSI:
          clkSrcFreq = CSI_VALUE;
          break;
#endif
#ifdef RCC_I2C4CLKSOURCE_PLL3
        case RCC_I2C4CLKSOURCE_PLL3:
          HAL_RCCEx_GetPLL3ClockFreq(&PLL3_Clocks);
          clkSrcFreq = PLL3_Clocks.PLL3_R_Frequency;
          break;
#endif
        default:
          Error_Handler();
      }
#else
      Error_Handler();
#endif
    }
  }
#endif // I2C4_BASE
#if defined(I2C5_BASE)
  if (i2c == I2C5) {
#if defined(RCC_PERIPHCLK_I2C5) || defined(RCC_PERIPHCLK_I2C35)
#ifdef RCC_PERIPHCLK_I2C5
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C5);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C35);
#endif
#endif
  }
#endif // I2C5_BASE
#if defined(I2C6_BASE)
  if (i2c == I2C6) {
#if defined(RCC_PERIPHCLK_I2C6) || defined(RCC_PERIPHCLK_I2C46)
#ifdef RCC_PERIPHCLK_I2C6
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C6);
#else
    clkSrcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C46);
#endif
#endif
  }
#endif // I2C6_BASE
  return clkSrcFreq;
}

/**
* @brief Calculate PRESC, SCLDEL, SDADEL, SCLL and SCLH and find best configuration.
* @param clkSrcFreq I2C source clock in HZ.
* @param i2c_speed I2C frequency (index).
* @retval config index (0 to I2C_VALID_TIMING_NBR], 0xFFFFFFFF for no
valid config.
*/
static uint32_t i2c_computeTiming(uint32_t clkSrcFreq, uint32_t i2c_speed)
{
  uint32_t ret = 0xFFFFFFFFU;
  uint32_t valid_timing_nbr = 0;
  uint32_t ti2cclk;
  uint32_t ti2cspeed;
  uint32_t prev_error;
  uint32_t dnf_delay;
  uint32_t clk_min, clk_max;
  uint16_t scll, sclh;
  uint8_t prev_presc = I2C_PRESC_MAX;

  int32_t tsdadel_min, tsdadel_max;
  int32_t tscldel_min;
  uint8_t presc, scldel, sdadel;
  uint32_t tafdel_min, tafdel_max;

  if (i2c_speed < I2C_SPEED_FREQ_NUMBER) {

    /* Don't compute timing if already available value for the requested speed with the same I2C input frequency */
    if ((I2C_ClockTiming[i2c_speed].input_clock == clkSrcFreq) && (I2C_ClockTiming[i2c_speed].timing != 0U)) {
      ret = I2C_ClockTiming[i2c_speed].timing;
    } else {
      /* Save the I2C input clock for which the timing will be saved */
      I2C_ClockTiming[i2c_speed].input_clock = clkSrcFreq;

      ti2cclk = (SEC2NSEC + (clkSrcFreq / 2U)) / clkSrcFreq;
      ti2cspeed = (SEC2NSEC + (I2C_Charac[i2c_speed].freq / 2U)) / I2C_Charac[i2c_speed].freq;

      tafdel_min = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOG_FILTER_DELAY_MIN : 0U;
      tafdel_max = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOG_FILTER_DELAY_MAX : 0U;
      /*
       * tDNF = DNF x tI2CCLK
       * tPRESC = (PRESC+1) x tI2CCLK
       * SDADEL >= {tf +tHD;DAT(min) - tAF(min) - tDNF - [3 x tI2CCLK]} / {tPRESC}
       * SDADEL <= {tVD;DAT(max) - tr - tAF(max) - tDNF- [4 x tI2CCLK]} / {tPRESC}
       */
      tsdadel_min = (int32_t)I2C_Charac[i2c_speed].tfall +
                    (int32_t)I2C_Charac[i2c_speed].hddat_min -
                    (int32_t)tafdel_min - (int32_t)(((int32_t)I2C_Charac[i2c_speed].dnf +
                                                     3) * (int32_t)ti2cclk);
      tsdadel_max = (int32_t)I2C_Charac[i2c_speed].vddat_max -
                    (int32_t)I2C_Charac[i2c_speed].trise -
                    (int32_t)tafdel_max - (int32_t)(((int32_t)I2C_Charac[i2c_speed].dnf +
                                                     4) * (int32_t)ti2cclk);
      /* {[tr+ tSU;DAT(min)] / [tPRESC]} - 1 <= SCLDEL */
      tscldel_min = (int32_t)I2C_Charac[i2c_speed].trise +
                    (int32_t)I2C_Charac[i2c_speed].sudat_min;
      if (tsdadel_min <= 0) {
        tsdadel_min = 0;
      }
      if (tsdadel_max <= 0) {
        tsdadel_max = 0;
      }

      /* tDNF = DNF x tI2CCLK */
      dnf_delay = I2C_Charac[i2c_speed].dnf * ti2cclk;

      clk_max = SEC2NSEC / I2C_Charac[i2c_speed].freq_min;
      clk_min = SEC2NSEC / I2C_Charac[i2c_speed].freq_max;

      prev_error = ti2cspeed;

      for (presc = 0; presc < I2C_PRESC_MAX; presc++) {
        for (scldel = 0; scldel < I2C_SCLDEL_MAX; scldel++) {
          /* TSCLDEL = (SCLDEL+1) * (PRESC+1) * TI2CCLK */
          uint32_t tscldel = (scldel + 1U) * (presc + 1U) * ti2cclk;
          if (tscldel >= (uint32_t)tscldel_min) {

            for (sdadel = 0; sdadel < I2C_SDADEL_MAX; sdadel++) {
              /* TSDADEL = SDADEL * (PRESC+1) * TI2CCLK */
              uint32_t tsdadel = (sdadel * (presc + 1U)) * ti2cclk;
              if ((tsdadel >= (uint32_t)tsdadel_min) && (tsdadel <=
                                                         (uint32_t)tsdadel_max)) {
                if (presc != prev_presc) {
                  valid_timing_nbr ++;
                  if (valid_timing_nbr >= I2C_VALID_TIMING_NBR) {
                    return ret;
                  }
                  /* tPRESC = (PRESC+1) x tI2CCLK*/
                  uint32_t tpresc = (presc + 1U) * ti2cclk;
                  for (scll = 0; scll < I2C_SCLL_MAX; scll++) {
                    /* tLOW(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLL+1) x tPRESC ] */
                    uint32_t tscl_l = tafdel_min + dnf_delay + (2U * ti2cclk) + ((scll + 1U) * tpresc);
                    /* The I2CCLK period tI2CCLK must respect the following conditions:
                    tI2CCLK < (tLOW - tfilters) / 4 and tI2CCLK < tHIGH */
                    if ((tscl_l > I2C_Charac[i2c_speed].lscl_min) &&
                        (ti2cclk < ((tscl_l - tafdel_min - dnf_delay) / 4U))) {
                      for (sclh = 0; sclh < I2C_SCLH_MAX; sclh++) {
                        /* tHIGH(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLH+1) x tPRESC] */
                        uint32_t tscl_h = tafdel_min + dnf_delay + (2U * ti2cclk) + ((sclh + 1U) * tpresc);
                        /* tSCL = tf + tLOW + tr + tHIGH */
                        uint32_t tscl = tscl_l + tscl_h + I2C_Charac[i2c_speed].trise +
                                        I2C_Charac[i2c_speed].tfall;
                        if ((tscl >= clk_min) && (tscl <= clk_max) &&
                            (tscl_h >= I2C_Charac[i2c_speed].hscl_min) && (ti2cclk < tscl_h)) {
                          int32_t error = (int32_t)tscl - (int32_t)ti2cspeed;
                          if (error < 0) {
                            error = -error;
                          }
                          /* look for the timings with the lowest clock error */
                          if ((uint32_t)error < prev_error) {
                            prev_error = (uint32_t)error;
                            ret = ((presc & 0x0FU) << 28) | \
                                  ((scldel & 0x0FU) << 20) | \
                                  ((sdadel & 0x0FU) << 16) | \
                                  ((sclh & 0xFFU) << 8) | \
                                  ((scll & 0xFFU) << 0);
                            prev_presc = presc;
                            /* Save I2C Timing found for further reuse (and avoid to compute again) */
                            I2C_ClockTiming[i2c_speed].timing = ret;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return ret;
}
#endif /* I2C_TIMING_COMPUTE */

/**
* @brief Compute I2C timing according current I2C clock source and
required I2C clock.
* @param  obj : pointer to i2c_t structure
* @param frequency
 Required I2C clock in Hz.
* @retval I2C timing or 0 in case of error.
*/
static uint32_t i2c_getTiming(i2c_t *obj, uint32_t frequency)
{
  uint32_t ret = 0;
  uint32_t i2c_speed = 0;
  if (frequency <= 100000) {
    i2c_speed = 100000;
  } else if (frequency <= 400000) {
    i2c_speed = 400000;
  } else if (frequency <= 1000000) {
    i2c_speed = 1000000;
  }
#ifdef I2C_TIMING
#ifndef I2C_TIMING_COMPUTE
  UNUSED(obj);
#endif
  if (i2c_speed != 0U) {
    switch (i2c_speed) {
      default:
      case 100000:
#ifdef I2C_TIMING_SM
        ret = I2C_TIMING_SM;
#else
        ret = i2c_computeTiming(i2c_getClkFreq(obj->i2c), I2C_SPEED_FREQ_STANDARD);
#endif
        break;
      case 400000:
#ifdef I2C_TIMING_FM
        ret = I2C_TIMING_FM;
#else
        ret = i2c_computeTiming(i2c_getClkFreq(obj->i2c), I2C_SPEED_FREQ_FAST);
#endif
        break;
      case 1000000:
#ifdef I2C_TIMING_FMP
        ret = I2C_TIMING_FMP;
#else
        ret = i2c_computeTiming(i2c_getClkFreq(obj->i2c), I2C_SPEED_FREQ_FAST_PLUS);
#endif
        break;
    }
  }
  /* Kept for future if more speed are proposed */
  /* uint32_t speed;
   * for (speed = 0; speed <= (uint32_t)I2C_SPEED_FREQ_FAST_PLUS; speed++) {
   *   if ((i2c_speed >= I2C_Charac[speed].freq_min) &&
   *       (i2c_speed <= I2C_Charac[speed].freq_max)) {
   *     i2c_computeTiming(i2c_getClkFreq(obj->i2c), speed);
   *     break;
   *   }
   * }
   */
#else
  UNUSED(obj);
  ret = i2c_speed;
#endif /* I2C_TIMING */
  return ret;
}

/**
  * @brief  Initialize and setup GPIO and I2C peripheral
  * @param  obj : pointer to i2c_t structure
  * @param  timing : one of the i2c_timing_e
  * @param  ownAddress : device address
  * @retval none
  */
void i2c_init(i2c_t *obj, uint32_t timing, uint32_t ownAddress)
{
  if (obj != NULL) {


    I2C_HandleTypeDef *handle = &(obj->handle);

    // Determine the I2C to use
    I2C_TypeDef *i2c_sda = pinmap_peripheral(obj->sda, PinMap_I2C_SDA);
    I2C_TypeDef *i2c_scl = pinmap_peripheral(obj->scl, PinMap_I2C_SCL);

    //Pins SDA/SCL must not be NP
    if (i2c_sda == NP || i2c_scl == NP) {
      core_debug("ERROR: at least one I2C pin has no peripheral\n");
    } else {

      obj->i2c = pinmap_merge_peripheral(i2c_sda, i2c_scl);

      if (obj->i2c == NP) {
        core_debug("ERROR: I2C pins mismatch\n");

      } else {

#if defined I2C1_BASE
        // Enable I2C1 clock if not done
        if (obj->i2c == I2C1) {
          __HAL_RCC_I2C1_CLK_ENABLE();
          __HAL_RCC_I2C1_FORCE_RESET();
          __HAL_RCC_I2C1_RELEASE_RESET();

          obj->irq = I2C1_EV_IRQn;
#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
          obj->irqER = I2C1_ER_IRQn;
#endif /* !STM32C0xx && !STM32F0xx && !STM32G0xx && !STM32L0xx */
          i2c_handles[I2C1_INDEX] = handle;
        }
#endif // I2C1_BASE
#if defined I2C2_BASE
        // Enable I2C2 clock if not done
        if (obj->i2c == I2C2) {
          __HAL_RCC_I2C2_CLK_ENABLE();
          __HAL_RCC_I2C2_FORCE_RESET();
          __HAL_RCC_I2C2_RELEASE_RESET();
          obj->irq = I2C2_EV_IRQn;
#if !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
          obj->irqER = I2C2_ER_IRQn;
#endif /* !STM32F0xx && !STM32G0xx && !STM32L0xx */
          i2c_handles[I2C2_INDEX] = handle;
        }
#endif // I2C2_BASE
#if defined I2C3_BASE
        // Enable I2C3 clock if not done
        if (obj->i2c == I2C3) {
          __HAL_RCC_I2C3_CLK_ENABLE();
          __HAL_RCC_I2C3_FORCE_RESET();
          __HAL_RCC_I2C3_RELEASE_RESET();
          obj->irq = I2C3_EV_IRQn;
#if !defined(STM32G0xx) && !defined(STM32L0xx)
          obj->irqER = I2C3_ER_IRQn;
#endif /* !STM32G0xx && !STM32L0xx */
          i2c_handles[I2C3_INDEX] = handle;
        }
#endif // I2C3_BASE
#if defined I2C4_BASE
        // Enable I2C4 clock if not done
        if (obj->i2c == I2C4) {
          __HAL_RCC_I2C4_CLK_ENABLE();
          __HAL_RCC_I2C4_FORCE_RESET();
          __HAL_RCC_I2C4_RELEASE_RESET();
          obj->irq = I2C4_EV_IRQn;
          obj->irqER = I2C4_ER_IRQn;
          i2c_handles[I2C4_INDEX] = handle;
        }
#endif // I2C4_BASE
#if defined I2C5_BASE
        // Enable I2C5 clock if not done
        if (obj->i2c == I2C5) {
          __HAL_RCC_I2C5_CLK_ENABLE();
          __HAL_RCC_I2C5_FORCE_RESET();
          __HAL_RCC_I2C5_RELEASE_RESET();
          obj->irq = I2C5_EV_IRQn;
          obj->irqER = I2C5_ER_IRQn;
          i2c_handles[I2C5_INDEX] = handle;
        }
#endif // I2C5_BASE
#if defined I2C6_BASE
        // Enable I2C6 clock if not done
        if (obj->i2c == I2C6) {
          __HAL_RCC_I2C6_CLK_ENABLE();
          __HAL_RCC_I2C6_FORCE_RESET();
          __HAL_RCC_I2C6_RELEASE_RESET();
          obj->irq = I2C6_EV_IRQn;
          obj->irqER = I2C6_ER_IRQn;
          i2c_handles[I2C6_INDEX] = handle;
        }
#endif // I2C6_BASE

        /* Configure I2C GPIO pins */
        pinmap_pinout(obj->scl, PinMap_I2C_SCL);
        pinmap_pinout(obj->sda, PinMap_I2C_SDA);

        handle->Instance             = obj->i2c;
#ifdef I2C_TIMING
        handle->Init.Timing          = i2c_getTiming(obj, timing);
#else
        handle->Init.ClockSpeed      = i2c_getTiming(obj, timing);
        /* Standard mode (sm) is up to 100kHz, then it's Fast mode (fm)     */
        /* In fast mode duty cyble bit must be set in CCR register          */
        if (timing > 100000) {
          handle->Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
        } else {
          handle->Init.DutyCycle       = I2C_DUTYCYCLE_2;
        }
#endif
        handle->Init.OwnAddress1     = ownAddress;
        handle->Init.OwnAddress2     = 0;
        handle->Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
        handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        handle->Init.GeneralCallMode = (obj->generalCall == 0) ? I2C_GENERALCALL_DISABLE : I2C_GENERALCALL_ENABLE;
        handle->Init.NoStretchMode   = (obj->NoStretchMode == 0) ? I2C_NOSTRETCH_DISABLE : I2C_NOSTRETCH_ENABLE;

        handle->State = HAL_I2C_STATE_RESET;

        HAL_NVIC_SetPriority(obj->irq, I2C_IRQ_PRIO, I2C_IRQ_SUBPRIO);
        HAL_NVIC_EnableIRQ(obj->irq);
#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
        HAL_NVIC_SetPriority(obj->irqER, I2C_IRQ_PRIO, I2C_IRQ_SUBPRIO);
        HAL_NVIC_EnableIRQ(obj->irqER);
#endif /* !STM32C0xx && !STM32F0xx && !STM32G0xx && !STM32L0xx */

        /* Init the I2C */
        if (HAL_I2C_Init(handle) != HAL_OK) {
          /* Initialization Error */
          Error_Handler();
        }

        /* Initialize default values */
        obj->slaveRxNbData = 0;
        obj->slaveMode = SLAVE_MODE_LISTEN;
      }
    }
  }
}

/**
  * @brief  Initialize and setup GPIO and I2C peripheral
  * @param  obj : pointer to i2c_t structure
  * @retval none
  */
void i2c_deinit(i2c_t *obj)
{
  HAL_NVIC_DisableIRQ(obj->irq);
#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
  HAL_NVIC_DisableIRQ(obj->irqER);
#endif /* !STM32C0xx && !STM32F0xx && !STM32G0xx && !STM32L0xx */
  HAL_I2C_DeInit(&(obj->handle));
  /* Reset I2C GPIO pins as INPUT_ANALOG */
  pin_function(obj->scl, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0));
  pin_function(obj->sda, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0));
  // Reset I2Cx and disable clock
#if defined I2C1_BASE
  if (obj->i2c == I2C1) {
    __HAL_RCC_I2C1_FORCE_RESET();
    __HAL_RCC_I2C1_RELEASE_RESET();
    __HAL_RCC_I2C1_CLK_DISABLE();
  }
#endif // I2C1_BASE
#if defined I2C2_BASE
  if (obj->i2c == I2C2) {
    __HAL_RCC_I2C2_FORCE_RESET();
    __HAL_RCC_I2C2_RELEASE_RESET();
    __HAL_RCC_I2C2_CLK_DISABLE();
  }
#endif // I2C2_BASE
#if defined I2C3_BASE
  if (obj->i2c == I2C3) {
    __HAL_RCC_I2C3_FORCE_RESET();
    __HAL_RCC_I2C3_RELEASE_RESET();
    __HAL_RCC_I2C3_CLK_DISABLE();
  }
#endif // I2C3_BASE
#if defined I2C4_BASE
  if (obj->i2c == I2C4) {
    __HAL_RCC_I2C4_FORCE_RESET();
    __HAL_RCC_I2C4_RELEASE_RESET();
    __HAL_RCC_I2C4_CLK_DISABLE();
  }
#endif // I2C4_BASE
#if defined I2C5_BASE
  if (obj->i2c == I2C5) {
    __HAL_RCC_I2C5_FORCE_RESET();
    __HAL_RCC_I2C5_RELEASE_RESET();
    __HAL_RCC_I2C5_CLK_DISABLE();
  }
#endif // I2C5_BASE
#if defined I2C6_BASE
  if (obj->i2c == I2C6) {
    __HAL_RCC_I2C6_FORCE_RESET();
    __HAL_RCC_I2C6_RELEASE_RESET();
    __HAL_RCC_I2C6_CLK_DISABLE();
  }
#endif // I2C6_BASE
}

/**
  * @brief  Setup transmission speed. I2C must be configured before.
  * @param  obj : pointer to i2c_t structure
  * @param  frequency : i2c transmission speed
  * @retval none
  */
void i2c_setTiming(i2c_t *obj, uint32_t frequency)
{
  uint32_t f = i2c_getTiming(obj, frequency);
  __HAL_I2C_DISABLE(&(obj->handle));

#ifdef I2C_TIMING
  obj->handle.Init.Timing = f;
#else
  obj->handle.Init.ClockSpeed = f;
  /* Standard mode (sm) is up to 100kHz, then it's Fast mode (fm)     */
  /* In fast mode duty cyble bit must be set in CCR register          */
  if (frequency > 100000) {
    obj->handle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  } else {
    obj->handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  }
#endif
  HAL_I2C_Init(&(obj->handle));
  __HAL_I2C_ENABLE(&(obj->handle));
}

/**
  * @brief  Write bytes at a given address
  * @param  obj : pointer to i2c_t structure
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval read status
  */
i2c_status_e i2c_master_write(i2c_t *obj, uint8_t dev_address,
                              uint8_t *data, uint16_t size)

{
  i2c_status_e ret = I2C_OK;
  uint32_t tickstart = HAL_GetTick();
  uint32_t delta = 0;
  uint32_t err = 0;
  HAL_StatusTypeDef status = HAL_OK;

  /* When size is 0, this is usually an I2C scan / ping to check if device is there and ready */
  if (size == 0) {
    ret = i2c_IsDeviceReady(obj, dev_address, 1);
  } else {
#if defined(I2C_OTHER_FRAME)
    uint32_t XferOptions = obj->handle.XferOptions; // save XferOptions value, because handle can be modified by HAL, which cause issue in case of NACK from slave
#endif
    do {
#if defined(I2C_OTHER_FRAME)
      status = HAL_I2C_Master_Seq_Transmit_IT(&(obj->handle), dev_address, data, size, XferOptions);
#else
      status = HAL_I2C_Master_Transmit_IT(&(obj->handle), dev_address, data, size);
#endif
      // Ensure i2c ready
      if (status == HAL_BUSY) {
        delta = (HAL_GetTick() - tickstart);
        if (delta > I2C_TIMEOUT_TICK) {
          ret = I2C_BUSY;
          break;
        }
      } else {
        ret = (status == HAL_OK) ? I2C_OK : I2C_ERROR;
      }
    } while (status == HAL_BUSY);

    if (ret == I2C_OK) {
      tickstart = HAL_GetTick();
      // wait for transfer completion
      while ((HAL_I2C_GetState(&(obj->handle)) != HAL_I2C_STATE_READY) && (delta < I2C_TIMEOUT_TICK)) {
        delta = (HAL_GetTick() - tickstart);
        if (HAL_I2C_GetError(&(obj->handle)) != HAL_I2C_ERROR_NONE) {
          break;
        }
      }

      err = HAL_I2C_GetError(&(obj->handle));
      if ((delta >= I2C_TIMEOUT_TICK)
          || ((err & HAL_I2C_ERROR_TIMEOUT) == HAL_I2C_ERROR_TIMEOUT)) {
        ret = I2C_TIMEOUT;
      } else {
        if ((err & HAL_I2C_ERROR_AF) == HAL_I2C_ERROR_AF) {
          ret = I2C_NACK_DATA;
        } else if (err != HAL_I2C_ERROR_NONE) {
          ret = I2C_ERROR;
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  Write bytes to master
  * @param  obj : pointer to i2c_t structure
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval status
  */
i2c_status_e i2c_slave_write_IT(i2c_t *obj, uint8_t *data, uint16_t size)
{
  uint8_t i = 0;
  i2c_status_e ret = I2C_OK;

  // Protection to not override the TxBuffer
  if (size > I2C_TXRX_BUFFER_SIZE) {
    ret = I2C_DATA_TOO_LONG;
  } else {
    // Check the communication status
    for (i = 0; i < size; i++) {
      obj->i2cTxRxBuffer[obj->i2cTxRxBufferSize + i] = *(data + i);
    }

    obj->i2cTxRxBufferSize += size;
  }
  return ret;
}

/**
  * @brief  read bytes in master mode at a given address
  * @param  obj : pointer to i2c_t structure
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be read
  * @param  size: number of bytes to be read.
  * @retval read status
  */
i2c_status_e i2c_master_read(i2c_t *obj, uint8_t dev_address, uint8_t *data, uint16_t size)
{
  i2c_status_e ret = I2C_OK;
  uint32_t tickstart = HAL_GetTick();
  uint32_t delta = 0;
  uint32_t err = 0;
  HAL_StatusTypeDef status = HAL_OK;

#if defined(I2C_OTHER_FRAME)
  uint32_t XferOptions = obj->handle.XferOptions; // save XferOptions value, because handle can be modified by HAL, which cause issue in case of NACK from slave
#endif
  do {
#if defined(I2C_OTHER_FRAME)
    status = HAL_I2C_Master_Seq_Receive_IT(&(obj->handle), dev_address, data, size, XferOptions);
#else
    status = HAL_I2C_Master_Receive_IT(&(obj->handle), dev_address, data, size);
#endif
    // Ensure i2c ready
    if (status == HAL_BUSY) {
      delta = (HAL_GetTick() - tickstart);
      if (delta > I2C_TIMEOUT_TICK) {
        ret = I2C_BUSY;
        break;
      }
    } else {
      ret = (status == HAL_OK) ? I2C_OK : I2C_ERROR;
    }
  } while (status == HAL_BUSY);

  if (ret == I2C_OK) {
    tickstart = HAL_GetTick();
    // wait for transfer completion
    while ((HAL_I2C_GetState(&(obj->handle)) != HAL_I2C_STATE_READY) && (delta < I2C_TIMEOUT_TICK)) {
      delta = (HAL_GetTick() - tickstart);
      if (HAL_I2C_GetError(&(obj->handle)) != HAL_I2C_ERROR_NONE) {
        break;
      }
    }

    err = HAL_I2C_GetError(&(obj->handle));
    if ((delta >= I2C_TIMEOUT_TICK)
        || ((err & HAL_I2C_ERROR_TIMEOUT) == HAL_I2C_ERROR_TIMEOUT)) {
      ret = I2C_TIMEOUT;
    } else {
      if ((err & HAL_I2C_ERROR_AF) == HAL_I2C_ERROR_AF) {
        ret = I2C_NACK_DATA;
      } else if (err != HAL_I2C_ERROR_NONE) {
        ret = I2C_ERROR;
      }
    }
  }
  return ret;
}

/**
  * @brief  Checks if target device is ready for communication
  * @param  obj : pointer to i2c_t structure
  * @param  devAddr: specifies the address of the device.
  * @param  trials : Number of trials.
  * @retval status
  */
i2c_status_e i2c_IsDeviceReady(i2c_t *obj, uint8_t devAddr, uint32_t trials)
{
  i2c_status_e ret = I2C_OK;

  switch (HAL_I2C_IsDeviceReady(&(obj->handle), devAddr, trials, I2C_TIMEOUT_TICK)) {
    case HAL_OK:
      ret = I2C_OK;
      break;
    case HAL_TIMEOUT:
      ret = (obj->handle.State != HAL_I2C_STATE_READY) ? I2C_TIMEOUT : I2C_NACK_ADDR;
      break;
    case HAL_BUSY:
      ret = (obj->handle.State != HAL_I2C_STATE_READY) ? I2C_BUSY : I2C_NACK_ADDR;
      break;
    default:
      ret = (obj->handle.State != HAL_I2C_STATE_READY) ? I2C_ERROR : I2C_NACK_ADDR;
      break;
  }
  return ret;
}

/* Aim of the function is to get i2c_s pointer using hi2c pointer */
/* Highly inspired from magical linux kernel's "container_of" */
/* (which was not directly used since not compatible with IAR toolchain) */
i2c_t *get_i2c_obj(I2C_HandleTypeDef *hi2c)
{
  struct i2c_s *obj_s;
  i2c_t *obj;

  obj_s = (struct i2c_s *)((char *)hi2c - offsetof(struct i2c_s, handle));
  obj = (i2c_t *)((char *)obj_s - offsetof(i2c_t, i2c));

  return (obj);
}

/** @brief  sets function called before a slave read operation
  * @param  obj : pointer to i2c_t structure
  * @param  function: callback function to use
  * @retval None
  */
void i2c_attachSlaveRxEvent(i2c_t *obj, void (*function)(i2c_t *))
{
  if ((obj != NULL) && (function != NULL)) {
    obj->i2c_onSlaveReceive = function;
    HAL_I2C_EnableListen_IT(&(obj->handle));
  }
}

/** @brief  sets function called before a slave write operation
  * @param  obj : pointer to i2c_t structure
  * @param  function: callback function to use
  * @retval None
  */
void i2c_attachSlaveTxEvent(i2c_t *obj, void (*function)(i2c_t *))
{
  if ((obj != NULL) && (function != NULL)) {
    obj->i2c_onSlaveTransmit = function;
    HAL_I2C_EnableListen_IT(&(obj->handle));
  }
}

/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
  */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  UNUSED(AddrMatchCode);
  i2c_t *obj = get_i2c_obj(hi2c);
  if ((obj->slaveMode == SLAVE_MODE_RECEIVE) && (obj->slaveRxNbData != 0)) {
    obj->i2c_onSlaveReceive(obj);
    obj->slaveMode = SLAVE_MODE_LISTEN;
    obj->slaveRxNbData = 0;
  }

  if (TransferDirection == I2C_DIRECTION_RECEIVE) {
    obj->slaveMode = SLAVE_MODE_TRANSMIT;

    if (obj->i2c_onSlaveTransmit != NULL) {
      obj->i2cTxRxBufferSize = 0;
      obj->i2c_onSlaveTransmit(obj);
    }
    HAL_I2C_Slave_Seq_Transmit_IT(hi2c, (uint8_t *) obj->i2cTxRxBuffer,
                                  obj->i2cTxRxBufferSize, I2C_LAST_FRAME);
  } else {
    obj->slaveRxNbData = 0;
    obj->slaveMode = SLAVE_MODE_RECEIVE;
    /*  We don't know in advance how many bytes will be sent by master so
     *  we'll fetch one by one until master ends the sequence */
    HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *) & (obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                 1, I2C_NEXT_FRAME);
  }
}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);

  /*  Previous master transaction now ended, so inform upper layer if needed
   *  then prepare for listening to next request */
  if ((obj->slaveMode == SLAVE_MODE_RECEIVE) && (obj->slaveRxNbData != 0)) {
    obj->i2c_onSlaveReceive(obj);
  }
  obj->slaveMode = SLAVE_MODE_LISTEN;
  obj->slaveRxNbData = 0;
  HAL_I2C_EnableListen_IT(hi2c);
}

/**
  * @brief Slave RX complete callback
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);
  /* One more byte was received, store it then prepare next */
  if (obj->slaveRxNbData < I2C_TXRX_BUFFER_SIZE) {
    obj->slaveRxNbData++;
  } else {
    core_debug("ERROR: I2C Slave RX overflow\n");
  }
  /* Restart interrupt mode for next Byte */
  if (obj->slaveMode == SLAVE_MODE_RECEIVE) {
    HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *) & (obj->i2cTxRxBuffer[obj->slaveRxNbData]),
                                 1, I2C_NEXT_FRAME);
  }
}

/**
  * @brief Slave TX complete callback
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);
  /* Reset transmit buffer size */
  obj->i2cTxRxBufferSize = 0;
}

/**
  * @brief  I2C error callback.
  * @note   In master mode, the callback is not used because the error is reported
  *         to the Arduino API from i2c_master_write() and i2c_master_read().
  *         In slave mode, there is no mechanism in Arduino API to report an error
  *         so the error callback forces the slave to listen again.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  i2c_t *obj = get_i2c_obj(hi2c);

  if (obj->isMaster == 0) {
    HAL_I2C_EnableListen_IT(hi2c);
  }
}

#if defined(I2C1_BASE)
/**
* @brief  This function handles I2C1 interrupt.
* @param  None
* @retval None
*/
void I2C1_EV_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C1_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32C0xx) || defined(STM32F0xx) || defined(STM32G0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif /* STM32C0xx || STM32F0xx || STM32G0xx || STM32L0xx */
}

#if !defined(STM32C0xx) && !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C1 interrupt.
* @param  None
* @retval None
*/
void I2C1_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C1_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif /* !STM32C0xx && !STM32F0xx && !STM32G0xx && !STM32L0xx */
#endif // I2C1_BASE

#if defined(I2C2_BASE)
/**
* @brief  This function handles I2C2 interrupt.
* @param  None
* @retval None
*/
void I2C2_EV_IRQHandler(void)
{
#if defined(I2C3_BASE) && defined(STM32G0xx)
  /* I2C2_3_IRQHandler */
  I2C_HandleTypeDef *handle2 = i2c_handles[I2C2_INDEX];
  I2C_HandleTypeDef *handle3 = i2c_handles[I2C3_INDEX];
  if (handle2) {
    HAL_I2C_EV_IRQHandler(handle2);
    HAL_I2C_ER_IRQHandler(handle2);
  }
  if (handle3) {
    HAL_I2C_EV_IRQHandler(handle3);
    HAL_I2C_ER_IRQHandler(handle3);
  }
#else
  I2C_HandleTypeDef *handle = i2c_handles[I2C2_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32F0xx) || defined(STM32G0xx) || defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif /* STM32F0xx || STM32G0xx || STM32L0xx */
#endif
}

#if !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
/**
* @brief  This function handles I2C2 interrupt.
* @param  None
* @retval None
*/
void I2C2_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C2_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif /* !STM32F0xx && !STM32G0xx && !STM32L0xx */
#endif // I2C2_BASE

#if defined(I2C3_BASE) && !defined(STM32G0xx)
/**
* @brief  This function handles I2C3 interrupt.
* @param  None
* @retval None
*/
void I2C3_EV_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C3_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
#if defined(STM32L0xx)
  HAL_I2C_ER_IRQHandler(handle);
#endif /* STM32L0xx */
}

#if !defined(STM32L0xx)
/**
* @brief  This function handles I2C3 interrupt.
* @param  None
* @retval None
*/
void I2C3_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C3_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif /* !STM32L0xx */
#endif /* I2C3_BASE && ! STM32G0xx */

#if defined(I2C4_BASE)
/**
* @brief  This function handles I2C4 interrupt.
* @param  None
* @retval None
*/
void I2C4_EV_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C4_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
  HAL_I2C_ER_IRQHandler(handle);
}

/**
* @brief  This function handles I2C4 interrupt.
* @param  None
* @retval None
*/
void I2C4_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C4_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // I2C4_BASE

#if defined(I2C5_BASE)
/**
* @brief  This function handles I2C5 interrupt.
* @param  None
* @retval None
*/
void I2C5_EV_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C5_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
}

/**
* @brief  This function handles I2C5 interrupt.
* @param  None
* @retval None
*/
void I2C5_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C5_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // I2C5_BASE

#if defined(I2C6_BASE)
/**
* @brief  This function handles I2C6 interrupt.
* @param  None
* @retval None
*/
void I2C6_EV_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C6_INDEX];
  HAL_I2C_EV_IRQHandler(handle);
}

/**
* @brief  This function handles I2C6 interrupt.
* @param  None
* @retval None
*/
void I2C6_ER_IRQHandler(void)
{
  I2C_HandleTypeDef *handle = i2c_handles[I2C6_INDEX];
  HAL_I2C_ER_IRQHandler(handle);
}
#endif // I2C6_BASE

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
