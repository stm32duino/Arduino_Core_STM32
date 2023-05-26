/**
  ******************************************************************************
  * @file    stm32_eeprom.c
  * @brief   Provides emulated eeprom from flash
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

#include "stm32_eeprom.h"
#include "stm32yyxx_ll_utils.h"
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Be able to change FLASH_BANK_NUMBER to use if relevant */
#if !defined(FLASH_BANK_NUMBER) && defined(FLASH_BANK_1)
#if defined(FLASH_BANK_2)
#define FLASH_BANK_NUMBER   FLASH_BANK_2
#else /* FLASH_BANK_1 */
#define FLASH_BANK_NUMBER   FLASH_BANK_1
#endif /* FLASH_BANK_2 */
#ifndef FLASH_BANK_NUMBER
#error "FLASH_BANK_NUMBER could not be defined"
#endif
#endif /* !FLASH_BANK_NUMBER */

/* Be able to change FLASH_DATA_SECTOR to use if relevant */
#if defined(FLASH_SECTOR_TOTAL) || defined(FLASH_SECTOR_NB)
#if !defined(FLASH_DATA_SECTOR)
#if defined(FLASH_SECTOR_TOTAL)
#define FLASH_DATA_SECTOR   ((uint32_t)(FLASH_SECTOR_TOTAL - 1))
#elif defined(FLASH_SECTOR_NB)
#define FLASH_DATA_SECTOR   ((uint32_t)(FLASH_SECTOR_NB - 1))
#endif
#else
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS have to be defined when FLASH_DATA_SECTOR is defined"
#endif
#endif /* !FLASH_DATA_SECTOR */
#endif /* FLASH_SECTOR_TOTAL || FLASH_SECTOR_NB */

/* Be able to change FLASH_PAGE_NUMBER to use if relevant */
#if !defined(FLASH_PAGE_NUMBER) && defined(FLASH_PAGE_SIZE)
#define FLASH_PAGE_NUMBER   ((uint32_t)(((LL_GetFlashSize() * 1024) / FLASH_PAGE_SIZE) - 1))
#endif /* !FLASH_PAGE_NUMBER */

/* Be able to change FLASH_END to use */
#if !defined(FLASH_END)
#if defined(EEPROM_RETRAM_MODE)
#define FLASH_END  ((uint32_t)(EEPROM_RETRAM_START_ADDRESS + EEPROM_RETRAM_MODE_SIZE -1))
#elif defined(DATA_EEPROM_END)
#define FLASH_END DATA_EEPROM_END
#elif defined (FLASH_BANK2_END) && (FLASH_BANK_NUMBER == FLASH_BANK_2)
#define FLASH_END  FLASH_BANK2_END
#elif defined (FLASH_BANK1_END) && (FLASH_BANK_NUMBER == FLASH_BANK_1)
#define FLASH_END  FLASH_BANK1_END
#elif defined(FLASH_DATA_SECTOR)
#if defined(FLASH_BANK_2) && (FLASH_BANK_NUMBER == FLASH_BANK_2)
#define FLASH_END  ((uint32_t)(FLASH_BASE + FLASH_BANK_SIZE + (FLASH_DATA_SECTOR * FLASH_SECTOR_SIZE) + FLASH_SECTOR_SIZE - 1))
#else
#define FLASH_END  ((uint32_t)(FLASH_BASE + (FLASH_DATA_SECTOR * FLASH_SECTOR_SIZE) + FLASH_SECTOR_SIZE - 1))
#endif /* FLASH_BANK_2 */
#elif defined(FLASH_BASE) && defined(FLASH_PAGE_NUMBER) && defined (FLASH_PAGE_SIZE)
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
 * in order to prevent overwriting
 * program data
 */
#if defined(EEPROM_RETRAM_MODE)
#define FLASH_BASE_ADDRESS  EEPROM_RETRAM_START_ADDRESS
#else
#define FLASH_BASE_ADDRESS  ((uint32_t)((FLASH_END + 1) - FLASH_PAGE_SIZE))
#endif
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS could not be defined"
#endif
#endif /* FLASH_BASE_ADDRESS */

#if !defined(DATA_EEPROM_BASE)
static uint8_t eeprom_buffer[E2END + 1] __attribute__((aligned(8))) = {0};
#endif

/**
  * @brief  Function reads a byte from emulated eeprom (flash)
  * @param  pos : address to read
  * @retval byte : data read from eeprom
  */
uint8_t eeprom_read_byte(const uint32_t pos)
{
#if defined(DATA_EEPROM_BASE)
  __IO uint8_t data = 0;
  if (pos <= (DATA_EEPROM_END - DATA_EEPROM_BASE)) {
    /* with actual EEPROM, pos is a relative address */
    data = *(__IO uint8_t *)(DATA_EEPROM_BASE + pos);
  }
  return (uint8_t)data;
#else
  eeprom_buffer_fill();
  return eeprom_buffered_read_byte(pos);
#endif /* _EEPROM_BASE */
}

/**
  * @brief  Function writes a byte to emulated eeprom (flash)
  * @param  pos : address to write
  * @param  value : value to write
  * @retval none
  */
void eeprom_write_byte(uint32_t pos, uint8_t value)
{
#if defined(DATA_EEPROM_BASE)
  /* with actual EEPROM, pos is a relative address */
  if (pos <= (DATA_EEPROM_END - DATA_EEPROM_BASE)) {
    if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
      HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, (pos + DATA_EEPROM_BASE), (uint32_t)value);
      HAL_FLASHEx_DATAEEPROM_Lock();
    }
  }
#else
  eeprom_buffered_write_byte(pos, value);
  eeprom_buffer_flush();
#endif /* _EEPROM_BASE */
}

#if !defined(DATA_EEPROM_BASE)

/**
  * @brief  Function reads a byte from the eeprom buffer
  * @param  pos : address to read
  * @retval byte : data read from eeprom
  */
uint8_t eeprom_buffered_read_byte(const uint32_t pos)
{
  return eeprom_buffer[pos];
}

/**
  * @brief  Function writes a byte to the eeprom buffer
  * @param  pos : address to write
  * @param  value : value to write
  * @retval none
  */
void eeprom_buffered_write_byte(uint32_t pos, uint8_t value)
{
  eeprom_buffer[pos] = value;
}

/**
  * @brief  This function copies the data from flash into the buffer
  * @param  none
  * @retval none
  */
void eeprom_buffer_fill(void)
{
#if defined(ICACHE) && defined (HAL_ICACHE_MODULE_ENABLED) && !defined(HAL_ICACHE_MODULE_DISABLED)
  bool icache_enabled = false;
  if (HAL_ICACHE_IsEnabled() == 1) {
    icache_enabled = true;
    /* Disable instruction cache prior to internal cacheable memory update */
    if (HAL_ICACHE_Disable() != HAL_OK) {
      Error_Handler();
    }
  }
#endif /* ICACHE && HAL_ICACHE_MODULE_ENABLED && !HAL_ICACHE_MODULE_DISABLED */
  memcpy(eeprom_buffer, (uint8_t *)(FLASH_BASE_ADDRESS), E2END + 1);
#if defined(ICACHE) && defined (HAL_ICACHE_MODULE_ENABLED) && !defined(HAL_ICACHE_MODULE_DISABLED)
  if (icache_enabled) {
    /* Re-enable instruction cache */
    if (HAL_ICACHE_Enable() != HAL_OK) {
      Error_Handler();
    }
  }
#endif /* ICACHE && HAL_ICACHE_MODULE_ENABLED && !HAL_ICACHE_MODULE_DISABLED */
}

#if defined(EEPROM_RETRAM_MODE)

/**
  * @brief  This function writes the buffer content into the flash
  * @param  none
  * @retval none
  */
void eeprom_buffer_flush(void)
{
  memcpy((uint8_t *)(FLASH_BASE_ADDRESS), eeprom_buffer, E2END + 1);
}

#else /* defined(EEPROM_RETRAM_MODE) */

/**
  * @brief  This function writes the buffer content into the flash
  * @param  none
  * @retval none
  */
void eeprom_buffer_flush(void)
{
#if defined(ICACHE) && defined (HAL_ICACHE_MODULE_ENABLED) && !defined(HAL_ICACHE_MODULE_DISABLED)
  bool icache_enabled = false;
  if (HAL_ICACHE_IsEnabled() == 1) {
    icache_enabled = true;
    /* Disable instruction cache prior to internal cacheable memory update */
    if (HAL_ICACHE_Disable() != HAL_OK) {
      Error_Handler();
    }
  }
#endif /* ICACHE && HAL_ICACHE_MODULE_ENABLED && !HAL_ICACHE_MODULE_DISABLED */
  FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t offset = 0;
  uint32_t address = FLASH_BASE_ADDRESS;
  uint32_t address_end = FLASH_BASE_ADDRESS + E2END;
#if defined(FLASH_TYPEERASE_PAGES)
  uint32_t pageError = 0;
#if defined(FLASH_TYPEPROGRAM_QUADWORD)
  uint64_t data[2] = {0x0000};
#else
  uint64_t data = 0;
#endif

  /* ERASING page */
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
#if defined(FLASH_BANK_NUMBER)
  EraseInitStruct.Banks = FLASH_BANK_NUMBER;
#endif /* FLASH_BANK_NUMBER */
#if defined (FLASH_PAGE_NUMBER) && defined(FLASH_SIZE)
  EraseInitStruct.Page = FLASH_PAGE_NUMBER;
#else
  EraseInitStruct.PageAddress = FLASH_BASE_ADDRESS;
#endif
  EraseInitStruct.NbPages = 1;

  if (HAL_FLASH_Unlock() == HAL_OK) {
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &pageError) == HAL_OK) {
      while (address <= address_end) {
#if defined(FLASH_TYPEPROGRAM_QUADWORD)
        /* 128 bits */
        memcpy(&data, eeprom_buffer + offset, 4 * sizeof(uint32_t));
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, address, (uint32_t)data) == HAL_OK) {
          address += 16;
          offset += 16;
#else
        data = *((uint64_t *)((uint8_t *)eeprom_buffer + offset));

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data) == HAL_OK) {
          address += 8;
          offset += 8;
#endif
        } else {
          address = address_end + 1;
        }
      }
    }
    HAL_FLASH_Lock();
  }
#else /* FLASH_TYPEERASE_SECTORS */
  uint32_t SectorError = 0;
#if defined(FLASH_TYPEPROGRAM_FLASHWORD)
  uint64_t data[4] = {0x0000};
#elif defined(FLASH_TYPEPROGRAM_QUADWORD)
  uint32_t data[4] = {0x0000};
#else
  uint32_t data = 0;
#endif

  /* ERASING page */
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
#if defined(FLASH_BANK_NUMBER)
  EraseInitStruct.Banks = FLASH_BANK_NUMBER;
#endif
#if defined(FLASH_VOLTAGE_RANGE_3)
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
  EraseInitStruct.Sector = FLASH_DATA_SECTOR;
  EraseInitStruct.NbSectors = 1;

  HAL_FLASH_Unlock();

  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) == HAL_OK) {
    while (address <= address_end) {
#if defined(FLASH_TYPEPROGRAM_FLASHWORD)
      /* 256 bits */
      memcpy(&data, eeprom_buffer + offset, 8 * sizeof(uint32_t));
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, address, (uint32_t)data) == HAL_OK) {
        address += 32;
        offset += 32;
#elif defined(FLASH_TYPEPROGRAM_QUADWORD)
      /* 128 bits */
      memcpy(&data, eeprom_buffer + offset, 4 * sizeof(uint32_t));
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, address, (uint32_t)data) == HAL_OK) {
        address += 16;
        offset += 16;
#elif defined(FLASH_TYPEPROGRAM_WORD)
      memcpy(&data, eeprom_buffer + offset, sizeof(uint32_t));
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) == HAL_OK) {
        address += 4;
        offset += 4;
#else
#error "Unknown FLASH Program Type."
      if (0) {}
#endif
      } else {
        address = address_end + 1;
      }
    }
  }
  HAL_FLASH_Lock();
#endif
#if defined(ICACHE) && defined (HAL_ICACHE_MODULE_ENABLED) && !defined(HAL_ICACHE_MODULE_DISABLED)
  if (icache_enabled)
  {
    /* Re-enable instruction cache */
    if (HAL_ICACHE_Enable() != HAL_OK) {
      Error_Handler();
    }
  }
#endif /* ICACHE && HAL_ICACHE_MODULE_ENABLED && !HAL_ICACHE_MODULE_DISABLED */
}

#endif /* defined(EEPROM_RETRAM_MODE) */

#endif /* ! DATA_EEPROM_BASE */

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
