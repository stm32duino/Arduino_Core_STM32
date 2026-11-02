/**
  ******************************************************************************
  * @file    stm32_eeprom.h
  * @brief   Header for eeprom module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016-2021, STMicroelectronics
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_EEPROM_H
#define __STM32_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#if !defined(USE_HALV2_DRIVER)
#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#if defined(STM32MP1xx)
/** @brief The EEPROM emulation uses RETRAM on STM32MP1xx.
 *
 * @note Those devices do not have non-volatile memory. The emulation is done
 * in RETRAM. Therefore data will be preserved *only* when VBAT is supplied
 * (e.g. A coin battery is connected to CN3 on STM32MP157A_DK1) and
 * the coprocessor is waken up from STANBY mode.
 * The data won't be preserved from cold boot, even if VBAT is connected.
 * See: https://community.st.com/s/question/0D50X0000B44pHUSQY/doesnt-the-mcu-coprocessor-have-nonvolatile-memory
 */
#define EEPROM_RETRAM_MODE
/**
 * @brief EEPROM size in RETRAM mode.
 *        4kB is the same size as EEPROM size of ATMega2560.
 */
#ifndef EEPROM_RETRAM_MODE_SIZE
#define EEPROM_RETRAM_MODE_SIZE ((uint32_t)(4*1024))
#endif
/** @brief EEPROM start address in RETRAM mode.
 *
 * RETRAM start address is 0x00000000 (retset entry) and end address is
 * 0x00020000 (64kB in total). The by default, ldscript.ld for STM32MP1xx
 * does not define address between 0x00000298 (end of ISR Vector) and 0x00020000.
 * So it is okay to use in this address range. Make sure ldscript.ld does not
 * overrap the following address range.
 */
#ifndef EEPROM_RETRAM_START_ADDRESS
#define EEPROM_RETRAM_START_ADDRESS (0x00000400UL)
#endif
/** @brief Last EEPROM address (EEPROM size - 1). */
#define E2END (EEPROM_RETRAM_MODE_SIZE - 1)
#else
/** @brief Mask of all the flash error flags to clear before programming. */
#ifndef FLASH_FLAG_ALL_ERRORS
#if defined(FLASH_FLAG_PGERR)
#if defined(FLASH_FLAG_OPTVERR)
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR | FLASH_FLAG_OPTVERR)
#else
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR)
#endif /* FLASH_FLAG_OPTVERR */
#else
#if defined(FLASH_PCROP_SUPPORT)
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_OPERR   | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                   FLASH_FLAG_PGAERR  | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR | \
                                   FLASH_FLAG_MISERR  | FLASH_FLAG_FASTERR | FLASH_FLAG_RDERR  | \
                                   FLASH_FLAG_OPTVERR | FLASH_FLAG_ECCC    | FLASH_FLAG_ECCD)
#else
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_OPERR   | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                   FLASH_FLAG_PGAERR  | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR | \
                                   FLASH_FLAG_MISERR  | FLASH_FLAG_FASTERR | \
                                   FLASH_FLAG_OPTVERR | FLASH_FLAG_ECCC    | FLASH_FLAG_ECCD)
#endif /* FLASH_PCROP_SUPPORT */
#endif /* FLASH_FLAG_PGERR */
#endif /* FLASH_FLAG_ALL_ERRORS */

#ifndef FLASH_PAGE_SIZE
/**
 * @brief Size of the flash area used for the EEPROM emulation.
 *
 * FLASH_PAGE_SIZE is not defined for STM32F2xx, STM32F4xx and STM32F7xx
 * Could be redefined in variant.h or using build_opt.h
 * @warning This is not the sector size, only the size used for EEPROM
 * emulation. Anyway, all the sector size will be erased.
 * So pay attention to not use this sector for other stuff.
 */
#define FLASH_PAGE_SIZE     ((uint32_t)(8*1024)) /* 8kB page */
#endif

#if defined(DATA_EEPROM_BASE) || defined(FLASH_EEPROM_BASE)

#if defined (DATA_EEPROM_END)
/** @brief Last EEPROM address (EEPROM size - 1). */
#define E2END (DATA_EEPROM_END - DATA_EEPROM_BASE)
#elif defined (DATA_EEPROM_BANK2_END)
/* assuming two contiguous banks */
#define DATA_EEPROM_END DATA_EEPROM_BANK2_END
/** @brief Last EEPROM address (EEPROM size - 1). */
#define E2END (DATA_EEPROM_BANK2_END - DATA_EEPROM_BASE)
#elif defined (FLASH_EEPROM_END)
#define DATA_EEPROM_BASE FLASH_EEPROM_BASE
#define DATA_EEPROM_END FLASH_EEPROM_END
/** @brief Last EEPROM address (EEPROM size - 1). */
#define E2END (DATA_EEPROM_END - DATA_EEPROM_BASE)
#endif /* __EEPROM_END */

#else /* _EEPROM_BASE */
/** @brief Last EEPROM address (EEPROM size - 1). */
#define E2END (FLASH_PAGE_SIZE - 1)
#endif /* _EEPROM_BASE */

#endif /* STM32MP1xx */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief Read a byte from the emulated EEPROM (flash).
 *
 * With a real data EEPROM, pos is a relative address and 0 is returned if it
 * is out of range.
 * Otherwise the flash content is first copied into the EEPROM buffer.
 * @param pos Address to read.
 * @return Data read from EEPROM.
 */
uint8_t eeprom_read_byte(const uint32_t pos);
/**
 * @brief Write a byte to the emulated EEPROM (flash).
 *
 * With a real data EEPROM, pos is a relative address and the write is ignored
 * if it is out of range.
 * Otherwise the byte is written to the EEPROM buffer, then the whole buffer is
 * written into flash.
 * @param pos Address to write.
 * @param value Value to write.
 */
void eeprom_write_byte(uint32_t pos, uint8_t value);

#if !defined(DATA_EEPROM_BASE)
/**
 * @brief Copy the data from flash into the EEPROM buffer.
 * @note Any pending change in the buffer which was not flushed is overwritten.
 */
void eeprom_buffer_fill();
/**
 * @brief Write the EEPROM buffer content into flash.
 * @note Use it after eeprom_buffered_write_byte() to make the changes persistent.
 */
void eeprom_buffer_flush();
/**
 * @brief Read a byte from the EEPROM buffer, flash is not read.
 * @param pos Address to read.
 * @return Data read from the EEPROM buffer.
 */
uint8_t eeprom_buffered_read_byte(const uint32_t pos);
/**
 * @brief Write a byte to the EEPROM buffer, flash is not updated.
 * @param pos Address to write.
 * @param value Value to write.
 */
void eeprom_buffered_write_byte(uint32_t pos, uint8_t value);
#endif /* ! DATA_EEPROM_BASE */

#ifdef __cplusplus
}
#endif
#endif /* !USE_HALV2_DRIVER */
#endif /* __STM32_EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
