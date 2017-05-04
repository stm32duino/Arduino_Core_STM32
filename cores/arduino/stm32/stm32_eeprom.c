/**
  ******************************************************************************
  * @file    eeprom.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide emulated eeprom from flash
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
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "stm32_eeprom.h"
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */
// We use the last page of the flash to store data (to prevent code overwrite).
// Use the last 16 page of the second bank (sector 15)
#define FLASH_BASE_ADDRESS  ((uint32_t)(0x0810C000))
#define FLASH_DATA_SECTOR   15

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Variables
  * @{
  */
static uint8_t tmpEE[E2END] = {0};

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  * @{
  */
void get_data_from_flash(void);
void set_data_to_flash(void);

/**
  * @}
  */

/**
  * @brief  Function read a byte from eeprom
  * @param  __p : address to read
  * @retval byte : data read from eeprom
  */
uint8_t eeprom_read_byte(const uint16_t __p)
{
  uint8_t byte = 0;

  get_data_from_flash();
  byte = tmpEE[__p];

  return byte;
}

/**
  * @brief  Function write a byte to eeprom
  * @param  __p : address to write
  * @param  __value : value to write
  * @retval none
  */
void eeprom_write_byte(uint16_t __p, uint8_t __value)
{
  tmpEE[__p] = __value;
  set_data_to_flash();
}

/**
  * @brief  The function read into the flash.
  * @param  none
  * @retval none
  */
void get_data_from_flash(void)
{
  memcpy(tmpEE, (uint8_t*)(FLASH_BASE_ADDRESS), E2END);
}

/**
  * @brief  The function write into the flash.
  * @param  none
  * @retval none
  */
void set_data_to_flash(void)
{
  //copy in flash
  FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t SectorError = 0;
  uint32_t offset = 0;
  uint32_t address = FLASH_BASE_ADDRESS;
  uint32_t address_end = FLASH_BASE_ADDRESS + E2END;
  uint32_t data = 0;

  // ERASING page
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector = FLASH_DATA_SECTOR;
  EraseInitStruct.NbSectors = 1;

  HAL_FLASH_Unlock();

  if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) == HAL_OK)
  {
    while(address < address_end) {
      memcpy(&data, tmpEE + offset, sizeof(uint32_t));
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) == HAL_OK) {
        address += 4;
        offset += 4;
      } else {
        address = address_end+1;
      }
    }
  }
  HAL_FLASH_Lock();
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
