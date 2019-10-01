/**
  ******************************************************************************
  * @file    stm32_eeprom.h
  * @brief   Header for eeprom module
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
#ifndef __STM32_EEPROM_H
#define __STM32_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#if defined(STM32MP1xx)
/* Note for STM32MP1xx devices:
 * Those devices do not have non-volatile memory. The emulation is done
 * in RETRAM. Therefore data will be preserved *only* when VBAT is supplied
 * (e.g. A coin battery is connected to CN3 on STM32MP157A_DK1) and
 * the coprocessor is waken up from STANBY mode.
 * The data won't be preserved from cold boot, even if VBAT is connected.
 * See: https://community.st.com/s/question/0D50X0000B44pHUSQY/doesnt-the-mcu-coprocessor-have-nonvolatile-memory
 */
#define EEPROM_RETRAM_MODE
/* 4kB is the same size as EEPROM size of ATMega2560. */
#ifndef EEPROM_RETRAM_MODE_SIZE
#define EEPROM_RETRAM_MODE_SIZE ((uint32_t)(4*1024))
#endif
/* RETRAM start address is 0x00000000 (retset entry) and end address is
 * 0x00020000 (64kB in total). The by default, ldscript.ld for STM32MP1xx
 * does not define address between 0x00000298 (end of ISR Vector) and 0x00020000.
 * So it is okay to use in this address range. Make sure ldscript.ld does not
 * overrap the following address range.
 */
#ifndef EEPROM_RETRAM_START_ADDRESS
#define EEPROM_RETRAM_START_ADDRESS (0x00000400UL)
#endif
#define E2END (EEPROM_RETRAM_MODE_SIZE - 1)
#else
#ifndef FLASH_PAGE_SIZE
/*
 * FLASH_PAGE_SIZE is not defined for STM32F2xx, STM32F4xx and STM32F7xx
 * Could be redefined in variant.h or using build_opt.h
 * Warning: This is not the sector size, only the size used for EEPROM
 * emulation. Anyway, all the sector size will be erased.
 * So pay attention to not use this sector for other stuff.
 */
#define FLASH_PAGE_SIZE     ((uint32_t)(16*1024)) /* 16kB page */
#endif
#define E2END (FLASH_PAGE_SIZE - 1)
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint8_t eeprom_read_byte(const uint32_t pos);
void eeprom_write_byte(uint32_t pos, uint8_t value);

void eeprom_buffer_fill();
void eeprom_buffer_flush();
uint8_t eeprom_buffered_read_byte(const uint32_t pos);
void eeprom_buffered_write_byte(uint32_t pos, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
