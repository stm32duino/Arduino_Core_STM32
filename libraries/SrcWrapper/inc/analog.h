/**
  ******************************************************************************
  * @file    analog.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for analog module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ANALOG_H
#define __ANALOG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PeripheralPins.h"
#include "HardwareTimer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */
#if !defined(HAL_ADC_MODULE_ONLY)
#if defined(HAL_ADC_MODULE_ENABLED)
/**
 * @brief Return the ADC channel linked to a PinName.
 * @param pin PinName.
 * @param bank Pointer to get the ADC channel bank (A or B), if required by
 *             the series. Left untouched on series without channel banks.
 * @return The ADC channel.
 */
uint32_t get_adc_channel(PinName pin, uint32_t *bank);
/**
 * @brief Return the ADC internal channel linked to a PinName.
 * @param pin PinName, one of the ADC internal PinNames:
 *            PADC_TEMP, PADC_TEMP_ADC5, PADC_VREF, PADC_VBAT.
 * @note Not all of these values may be available for all series.
 * @return The ADC internal channel.
 */
uint32_t get_adc_internal_channel(PinName pin);
#endif
#if defined(USE_HAL_ADC_MODULE) && (USE_HAL_ADC_MODULE == 1)
/**
 * @brief Return the ADC HAL channel linked to a PinName (HAL v2 ADC driver).
 * @param pin PinName.
 * @return The ADC HAL channel.
 */
hal_adc_channel_t get_adc_channel(PinName pin);
/**
 * @brief Return the ADC HAL internal channel linked to a PinName
 *        (HAL v2 ADC driver).
 * @param pin PinName, one of the ADC internal PinNames: PADC_TEMP, PADC_VREF.
 * @note Not all of these values may be available for all series.
 * @return The ADC HAL internal channel.
 */
hal_adc_channel_t get_adc_internal_channel(PinName pin);
#endif
#if defined(HAL_ADC_MODULE_ENABLED) || (defined(USE_HAL_ADC_MODULE) && (USE_HAL_ADC_MODULE == 1))
/**
 * @brief Read the ADC value on a pin.
 * @param pin PinName to read.
 * @param resolution Resolution of the converted data: 6/8/10/12/14/16.
 * @return The converted ADC value, in the requested resolution.
 */
uint16_t adc_read_value(PinName pin, uint32_t resolution);
#endif
#endif /* !HAL_ADC_MODULE_ONLY */
#if !defined(HAL_DAC_MODULE_ONLY)
#if defined(HAL_DAC_MODULE_ENABLED)
/**
 * @brief Return the DAC channel linked to a PinName.
 * @param pin PinName.
 * @return The DAC channel.
 */
uint32_t get_dac_channel(PinName pin);
#endif
#if defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1)
/**
 * @brief Return the DAC HAL channel linked to a PinName (HAL v2 DAC driver).
 * @param pin PinName.
 * @return The DAC HAL channel.
 */
hal_dac_channel_t get_dac_channel(PinName pin);
#endif
#if defined(HAL_DAC_MODULE_ENABLED) || (defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1))
/**
 * @brief Set the DAC output to the required value.
 * @param pin PinName to use.
 * @param value Value to push on the DAC output.
 * @param do_init If true, the DAC (clock, GPIO and channel) is initialized
 *                before writing the value.
 */
void dac_write_value(PinName pin, uint32_t value, bool do_init);
/**
 * @brief Stop the DAC output on a pin.
 * @param pin PinName to use.
 */
void dac_stop(PinName pin);
#endif
#endif /* !HAL_DAC_MODULE_ONLY */
#if !defined(HAL_TIM_MODULE_ONLY) &&\
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)))
/**
 * @brief Start PWM output on a pin with the required value.
 * @param pin PinName to use.
 * @param PWM_freq PWM frequency in Hertz.
 * @param value Value to push on the PWM output, expressed according to resolution.
 * @param resolution Format of value (see TimerCompareFormat_t).
 */
void pwm_start(PinName pin, uint32_t PWM_freq, uint32_t value, TimerCompareFormat_t resolution);
/**
 * @brief Stop PWM output on a pin (disable the PWM and release its HardwareTimer instance).
 * @param pin PinName to use.
 */
void pwm_stop(PinName pin);
#endif
#ifdef __cplusplus
}
#endif

#endif /* __ANALOG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
