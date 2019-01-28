/**
  ******************************************************************************
  * @file    stm32_eeprom.c
  * @brief   Provides emulated eeprom from flash
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

#include "stm32_eeprom.h"
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Be able to change FLASH_BANK_NUMBER to use if relevant */
#if !defined(FLASH_BANK_NUMBER) &&\
	  (defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32H7xx) ||\
	   defined(STM32L1xx) || defined(STM32L4xx))
/* Fo STM32F0xx, FLASH_BANK_1 is not defined only FLASH_BANK1_END is defined */
#if defined(STM32F0xx)
#define FLASH_BANK_1 1U
#endif
#if defined(FLASH_BANK_2)
#define FLASH_BANK_NUMBER   FLASH_BANK_2
#else
#define FLASH_BANK_NUMBER   FLASH_BANK_1
#endif /* FLASH_BANK_2 */
#ifndef FLASH_BANK_NUMBER
#error "FLASH_BANK_NUMBER could not be defined"
#endif
#endif /* !FLASH_BANK_NUMBER */

/* Be able to change FLASH_DATA_SECTOR to use if relevant */
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)  ||\
    defined(STM32H7xx)
#if !defined(FLASH_DATA_SECTOR)
#define FLASH_DATA_SECTOR   ((uint32_t)(FLASH_SECTOR_TOTAL - 1))
#else
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS have to be defined when FLASH_DATA_SECTOR is defined"
#endif
#endif /* !FLASH_DATA_SECTOR */
#endif /* STM32F2xx || STM32F4xx || STM32F7xx */

/* Be able to change FLASH_PAGE_NUMBER to use if relevant */
#if !defined(FLASH_PAGE_NUMBER) && defined (STM32L4xx)
#define FLASH_PAGE_NUMBER   ((uint32_t)((FLASH_SIZE / FLASH_PAGE_SIZE) - 1))
#endif /* !FLASH_PAGE_NUMBER */

/* Be able to change FLASH_END to use */
#if !defined(FLASH_END) && !defined(STM32L0xx)
#if defined (STM32F0xx) || defined (STM32F1xx) || defined(STM32L1xx)
#if defined (FLASH_BANK2_END) && (FLASH_BANK_NUMBER == FLASH_BANK_2)
#define FLASH_END  FLASH_BANK2_END
#elif defined (FLASH_BANK1_END) && (FLASH_BANK_NUMBER == FLASH_BANK_1)
#define FLASH_END  FLASH_BANK1_END
#endif
#elif defined (STM32F3xx)
static inline uint32_t get_flash_end(void) {
  uint32_t size;
  switch((*((uint16_t *)FLASH_SIZE_DATA_REGISTER))) {
    case 0x200U:
      size = 0x0807FFFFU;
    break;
    case 0x100U:
      size = 0x0803FFFFU;
    break;
    case 0x80U:
      size = 0x0801FFFFU;
    break;
    case 0x40U:
      size = 0x0800FFFFU;
    break;
    case 0x20U:
      size = 0x08007FFFU;
    break;
    default:
      size = 0x08003FFFU;
    break;
  }
  return size;
}
#define FLASH_END  get_flash_end()
#elif defined (STM32L4xx)
/* If FLASH_PAGE_NUMBER is defined by user, this is not really end of the flash */
#define FLASH_END  ((uint32_t)(FLASH_BASE + (((FLASH_PAGE_NUMBER +1) * FLASH_PAGE_SIZE))-1))
#endif
#ifndef FLASH_END
#error "FLASH_END could not be defined"
#endif
#endif /* FLASH_END */

/* Be able to change FLASH_BASE_ADDRESS to use */
#ifndef FLASH_BASE_ADDRESS
/*
 * By default, Use the last page of the flash to store data
 * in order to prevent overwritting
 * program data
 */
#if defined(STM32L0xx)
#define FLASH_BASE_ADDRESS  ((uint32_t)(DATA_EEPROM_BASE))
#else
#define FLASH_BASE_ADDRESS  ((uint32_t)((FLASH_END + 1) - FLASH_PAGE_SIZE))
#endif
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS could not be defined"
#endif
#endif /* FLASH_BASE_ADDRESS */

static uint8_t eeprom_buffer[E2END + 1] = {0};

/**
  * @brief  Function reads a byte from emulated eeprom (flash)
  * @param  pos : address to read
  * @retval byte : data read from eeprom
  */
uint8_t eeprom_read_byte(const uint32_t pos) {
  eeprom_buffer_fill();
  return eeprom_buffered_read_byte(pos);
}

/**
  * @brief  Function writes a byte to emulated eeprom (flash)
  * @param  pos : address to write
  * @param  value : value to write
  * @retval none
  */
void eeprom_write_byte(uint32_t pos, uint8_t value) {
  eeprom_buffered_write_byte(pos, value);
  eeprom_buffer_flush();
}

/**
  * @brief  Function reads a byte from the eeprom buffer
  * @param  pos : address to read
  * @retval byte : data read from eeprom
  */
uint8_t eeprom_buffered_read_byte(const uint32_t pos) {
  return eeprom_buffer[pos];
}

/**
  * @brief  Function writes a byte to the eeprom buffer
  * @param  pos : address to write
  * @param  value : value to write
  * @retval none
  */
void eeprom_buffered_write_byte(uint32_t pos, uint8_t value) {
  eeprom_buffer[pos] = value;
}

/**
  * @brief  This function copies the data from flash into the buffer
  * @param  none
  * @retval none
  */
void eeprom_buffer_fill(void) {
  memcpy(eeprom_buffer, (uint8_t*)(FLASH_BASE_ADDRESS), E2END + 1);
}

/**
  * @brief  This function writes the buffer content into the flash
  * @param  none
  * @retval none
  */
void eeprom_buffer_flush(void) {
  FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t offset = 0;
  uint32_t address = FLASH_BASE_ADDRESS;
  uint32_t address_end = FLASH_BASE_ADDRESS + E2END;
#if defined (STM32F0xx) || defined (STM32F1xx) || defined (STM32F3xx) || \
    defined (STM32L0xx) || defined (STM32L1xx) || defined(STM32L4xx)
  uint32_t pageError = 0;
  uint64_t data = 0;

  /* ERASING page */
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
#if defined(STM32L4xx) || defined(STM32F1xx)
  EraseInitStruct.Banks = FLASH_BANK_NUMBER;
#endif
#ifdef STM32L4xx
  EraseInitStruct.Page = FLASH_PAGE_NUMBER;
#else
  EraseInitStruct.PageAddress = FLASH_BASE_ADDRESS;
#endif
  EraseInitStruct.NbPages = 1;

  if(HAL_FLASH_Unlock() == HAL_OK) {
#if defined(STM32L0xx)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR|FLASH_FLAG_PGAERR|\
                           FLASH_FLAG_SIZERR|FLASH_FLAG_OPTVERR|FLASH_FLAG_RDERR|\
                           FLASH_FLAG_FWWERR|FLASH_FLAG_NOTZEROERR);
#elif defined(STM32L1xx)
#if defined(FLASH_SR_RDERR)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR|FLASH_FLAG_PGAERR|\
                           FLASH_FLAG_SIZERR|FLASH_FLAG_OPTVERR|FLASH_FLAG_RDERR);
#else
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR|FLASH_FLAG_PGAERR|\
                           FLASH_FLAG_SIZERR|FLASH_FLAG_OPTVERR);
#endif
#elif defined (STM32L4xx)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);
#else
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR|FLASH_FLAG_PGERR);
#endif
    if(HAL_FLASHEx_Erase(&EraseInitStruct, &pageError) == HAL_OK) {
      while(address <= address_end) {
#if defined(STM32L0xx) || defined(STM32L1xx)
        memcpy(&data, eeprom_buffer + offset, sizeof(uint32_t));
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) == HAL_OK) {
          address += 4;
          offset += 4;
#else
        data = *((uint64_t*)((uint8_t*)eeprom_buffer + offset));

        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data) == HAL_OK) {
          address += 8;
          offset += 8;
#endif
        } else {
          address = address_end+1;
        }
      }
    }
    HAL_FLASH_Lock();
  }
#else
  uint32_t SectorError = 0;
#if defined(STM32H7xx)
  uint64_t data[4] = {0x0000};
#else
  uint32_t data = 0;
#endif

  /* ERASING page */
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
#if defined(STM32H7xx)
  EraseInitStruct.Banks = FLASH_BANK_NUMBER;
#endif
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector = FLASH_DATA_SECTOR;
  EraseInitStruct.NbSectors = 1;

  HAL_FLASH_Unlock();

  if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) == HAL_OK) {
    while(address <= address_end) {
#if defined(STM32H7xx)
      /* 256 bits */
      memcpy(&data, eeprom_buffer + offset, 8 *sizeof(uint32_t));
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, address, (uint32_t)data) == HAL_OK) {
        address += 32;
        offset += 32;
#else
      memcpy(&data, eeprom_buffer + offset, sizeof(uint32_t));
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) == HAL_OK) {
        address += 4;
        offset += 4;
#endif
      } else {
        address = address_end+1;
      }
    }
  }
  HAL_FLASH_Lock();
#endif
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
