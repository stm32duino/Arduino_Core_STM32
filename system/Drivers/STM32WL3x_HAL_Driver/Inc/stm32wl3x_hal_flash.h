/**
  ******************************************************************************
  * @file    stm32wl3x_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
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
#ifndef STM32WL3x_HAL_FLASH_H
#define STM32WL3x_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wl3x_hal_def.h"

/** @addtogroup STM32WL3x_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;   /*!< Mass erase or page erase.
                             This parameter can be a value of @ref FLASH_TYPE_ERASE */
  uint32_t Page;        /*!< Initial Flash page to erase when page erase is enabled
                             This parameter must be a value between 0 and (max number of pages - 1) */
  uint32_t NbPages;     /*!< Number of pages to be erased.
                             This parameter must be a value between 1
                             and (max number of pages - value of initial page) */
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef   Lock;              /*!< FLASH locking object */
  uint32_t          ErrorCode;         /*!< FLASH error code */
  uint32_t          ProcedureOnGoing;  /*!< Internal variable to indicate which procedure is ongoing or not in IT context */
  uint32_t          Address;           /*!< Internal variable to save address selected for program in IT context */
  uint32_t          Page;              /*!< Internal variable to define the current page which is erasing in IT context */
  uint32_t          NbPagesToErase;    /*!< Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

/**
  * @brief  Page Protection function configuration structure definition
  */
typedef struct
{
  uint32_t pageProt_0;    /*!< This is a bitfield built as follows:
                               - bit[7:0]   = SIZE: number of 2 kB pages to protect including the starting page
                                              @ref pageProt_0 param (provided in the offset bits)
                               - bit[15:8]  = OFFSET: page number to start the write protection
                                              (value between 0 and 0x7F)
                               - bit[23:16] = SIZE: same meaning of bit[7:0]
                               - bit[31:24] = OFFSET: same meaning of bit[15:8] */
  uint32_t pageProt_1;    /*!< Same meaning of @ref pageProt_0 parameter */
  FunctionalState state;  /*!< The new state of the group.
                               This parameter can be a value of FunctionalState */
} FLASH_PageProtectionTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_WAIT_STATES FLASH Wait States
  * @{
  */
#define FLASH_WAIT_STATES_0                 0x00000000UL                /*!< FLASH Zero wait state   */
#define FLASH_WAIT_STATES_1                 FLASH_CONFIG_WAIT_STATES_0  /*!< FLASH One wait state    */
/**
  * @}
  */

/** @defgroup FLASH_CONFIG_IRQ_VECT_TABLE FLASH Configuration Interrupt Vector Table
  * @{
  */
#define FLASH_CONFIG_IRQ_VECT_TABLE_FLASH   0x00000000UL         /*!< Vector Table located in FLASH */
#define FLASH_CONFIG_IRQ_VECT_TABLE_RAM     FLASH_CONFIG_REMAP   /*!< Vector Table located in RAM   */
/**
  * @}
  */

/** @defgroup FLASH_FLAGS FLASH Flags Definition
  * @{
  */
#define FLASH_FLAG_CMDDONE             FLASH_IRQRAW_CMDDONE_RIS     /*!< FLASH command done flag    */
#define FLASH_FLAG_CMDSTART            FLASH_IRQRAW_CMDSTART_RIS    /*!< FLASH command started flag */
#define FLASH_FLAG_CMDERR              FLASH_IRQRAW_CMDERR_RIS      /*!< FLASH command error flag   */
#define FLASH_FLAG_ILLCMD              FLASH_IRQRAW_ILLCMD_RIS      /*!< FLASH illegal command flag */
#define FLASH_FLAG_ALL_ERRORS          (FLASH_IRQRAW_CMDERR_RIS | FLASH_IRQRAW_ILLCMD_RIS) /*!< Flash error flag */
/**
  * @}
  */

/** @defgroup FLASH_INTERRUPT_DEFINITION FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_CMDDONE               FLASH_IRQMASK_CMDDONEM     /*!< FLASH command done Interrupt source */
#define FLASH_IT_CMDSTART              FLASH_IRQMASK_CMDSTARTM    /*!< FLASH command started Interrupt source */
#define FLASH_IT_CMDERR                FLASH_IRQMASK_CMDERRM      /*!< FLASH command error Interrupt source */
#define FLASH_IT_ILLCMD                FLASH_IRQMASK_ILLCMDM      /*!< FLASH illegal command Interrupt source */
/**
  * @}
  */

/** @defgroup FLASH_ERROR FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE            0x00000000U
#define HAL_FLASH_ERROR_OP              FLASH_FLAG_CMDERR
#define HAL_FLASH_ERROR_ILLCMD          FLASH_FLAG_ILLCMD

/**
  * @}
  */

/** @defgroup FLASH_COMMAND FLASH Command
  * @{
  */
#define FLASH_CMD_ERASE_PAGES           0x11  /*!< flash pages erase command */
#define FLASH_CMD_MASSERASE             0x22  /*!< Flash mass erase command  */
#define FLASH_CMD_WRITE                 0x33  /*!< Flash write command       */
#define FLASH_CMD_MASSREAD              0x55  /*!< Flash mass read command     */
#define FLASH_CMD_SLEEP                 0xAA  /*!< Flash in sleep mode command */
#define FLASH_CMD_WAKEUP                0xBB  /*!< Flash wakeup command        */
#define FLASH_CMD_BURSTWRITE            0xCC  /*!< Flash burst write command */
#define FLASH_CMD_OTPWRITE              0xEE  /*!< Flash OTP write command   */
/**
  * @}
  */

/** @defgroup FLASH_TYPE_ERASE FLASH Erase Type
  * @{
  */
#define FLASH_TYPEERASE_PAGES           0x00  /*!< Pages erase      */
#define FLASH_TYPEERASE_MASSERASE       0xFF  /*!< Flash mass erase */
/**
  * @}
  */

/** @defgroup FLASH_TYPE_PROGRAM FLASH Program Type
  * @{
  */
#define FLASH_TYPEPROGRAM_WORD          0x00000000U
#define FLASH_TYPEPROGRAM_BURST         0x00000001U
/**
  * @}
  */

/** @defgroup FLASH_PAGEPROT_GROUP FLASH write/page erase protection for group
  * @{
  */
#define FLASH_PAGEPROT_GROUP_31           (0x80000000UL)  /*!< write/page erase protection for group 31 containing Flash pages 248 to 255 */
#define FLASH_PAGEPROT_GROUP_30           (0x40000000UL)  /*!< write/page erase protection for group 30 containing Flash pages 240 to 247 */
#define FLASH_PAGEPROT_GROUP_29           (0x20000000UL)  /*!< write/page erase protection for group 29 containing Flash pages 232 to 239 */
#define FLASH_PAGEPROT_GROUP_28           (0x10000000UL)        /*!< write/page erase protection for group 28 containing Flash pages 224 to 231 */
#define FLASH_PAGEPROT_GROUP_27           (0x8000000UL)   /*!< write/page erase protection for group 27 containing Flash pages 216 to 223 */
#define FLASH_PAGEPROT_GROUP_26           (0x4000000UL)   /*!< write/page erase protection for group 26 containing Flash pages 208 to 215 */
#define FLASH_PAGEPROT_GROUP_25           (0x2000000UL)   /*!< write/page erase protection for group 25 containing Flash pages 200 to 207 */
#define FLASH_PAGEPROT_GROUP_24           (0x1000000UL)   /*!< write/page erase protection for group 24 containing Flash pages 192 to 199 */
#define FLASH_PAGEPROT_GROUP_23           (0x0800000UL)   /*!< write/page erase protection for group 23 containing Flash pages 184 to 191 */
#define FLASH_PAGEPROT_GROUP_22           (0x0400000UL)   /*!< write/page erase protection for group 22 containing Flash pages 176 to 183 */
#define FLASH_PAGEPROT_GROUP_21           (0x0200000UL)   /*!< write/page erase protection for group 21 containing Flash pages 168 to 175 */
#define FLASH_PAGEPROT_GROUP_20           (0x0100000UL)   /*!< write/page erase protection for group 20 containing Flash pages 160 to 167 */
#define FLASH_PAGEPROT_GROUP_19           (0x0080000UL)   /*!< write/page erase protection for group 19 containing Flash pages 152 to 159 */
#define FLASH_PAGEPROT_GROUP_18           (0x0040000UL)   /*!< write/page erase protection for group 18 containing Flash pages 144 to 151 */
#define FLASH_PAGEPROT_GROUP_17           (0x0020000UL)   /*!< write/page erase protection for group 17 containing Flash pages 136 to 143 */
#define FLASH_PAGEPROT_GROUP_16           (0x0010000UL)   /*!< write/page erase protection for group 16 containing Flash pages 128 to 135 */
#define FLASH_PAGEPROT_GROUP_15           (0x0008000UL)   /*!< write/page erase protection for group 15 containing Flash pages 120 to 127 */
#define FLASH_PAGEPROT_GROUP_14           (0x0004000UL)   /*!< write/page erase protection for group 14 containing Flash pages 112 to 119 */
#define FLASH_PAGEPROT_GROUP_13           (0x0002000UL)   /*!< write/page erase protection for group 13 containing Flash pages 104 to 111 */
#define FLASH_PAGEPROT_GROUP_12           (0x0001000UL)   /*!< write/page erase protection for group 12 containing Flash pages 96 to 103  */
#define FLASH_PAGEPROT_GROUP_11           (0x0000800UL)   /*!< write/page erase protection for group 11 containing Flash pages 88 to 95   */
#define FLASH_PAGEPROT_GROUP_10           (0x0000400UL)   /*!< write/page erase protection for group 10 containing Flash pages 80 to 87   */
#define FLASH_PAGEPROT_GROUP_9            (0x0000200UL)   /*!< write/page erase protection for group 9  containing Flash pages 72 to 79   */
#define FLASH_PAGEPROT_GROUP_8            (0x0000100UL)   /*!< write/page erase protection for group 8  containing Flash pages 64 to 71   */
#define FLASH_PAGEPROT_GROUP_7            (0x0000080UL)   /*!< write/page erase protection for group 7  containing Flash pages 56 to 63   */
#define FLASH_PAGEPROT_GROUP_6            (0x0000040UL)   /*!< write/page erase protection for group 6  containing Flash pages 48 to 55   */
#define FLASH_PAGEPROT_GROUP_5            (0x0000020UL)   /*!< write/page erase protection for group 5  containing Flash pages 40 to 47   */
#define FLASH_PAGEPROT_GROUP_4            (0x0000010UL)   /*!< write/page erase protection for group 4  containing Flash pages 32 to 39   */
#define FLASH_PAGEPROT_GROUP_3            (0x0000008UL)   /*!< write/page erase protection for group 3  containing Flash pages 24 to 31   */
#define FLASH_PAGEPROT_GROUP_2            (0x0000004UL)   /*!< write/page erase protection for group 2  containing Flash pages 16 to 23   */
#define FLASH_PAGEPROT_GROUP_1            (0x0000002UL)   /*!< write/page erase protection for group 1  containing Flash pages 8 to 15    */
#define FLASH_PAGEPROT_GROUP_0            (0x0000001UL)   /*!< write/page erase protection for group 0  containing Flash pages 0 to 7     */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  * @brief macros to control FLASH features
  * @{
  */

/**
  * @brief  Set the FLASH Wait States.
  * @param __WAIT_STATES__ FLASH WAIT States
  *        This parameter can be one of the following values :
  *        @arg @ref FLASH_WAIT_STATES_0 FLASH Zero wait state
  *        @arg @ref FLASH_WAIT_STATES_1 FLASH One wait state
  * @retval None
  */
#define __HAL_FLASH_SET_WAIT_STATES(__WAIT_STATES__)  MODIFY_REG(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES, (__WAIT_STATES__))

/**
  * @brief  Get the FLASH Wait States.
  * @retval FLASH Wait States
  *         Returned value can be one of the following values :
  *         @arg @ref FLASH_WAIT_STATES_0 FLASH Zero wait state
  *         @arg @ref FLASH_WAIT_STATES_1 FLASH One wait state
  */
#define __HAL_FLASH_GET_WAIT_STATES()  READ_BIT(FLASH->CONFIG, FLASH_CONFIG_WAIT_STATES)

/**
  * @brief  Enable the FLASH burst write operations.
  * @retval None
  */
#define __HAL_FLASH_BURSTWRITE_ENABLE()  CLEAR_BIT(FLASH->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE)

/**
  * @brief  Disable the FLASH burst write operations.
  * @retval None
  */
#define __HAL_FLASH_BURSTWRITE_DISABLE()  SET_BIT(FLASH->CONFIG, FLASH_CONFIG_DIS_GROUP_WRITE)

/**
  * @brief  Set the FLASH Interrupt Vector Table location.
  * @param __VECT_TABLE__ Vector Table Configuration
  *        This parameter can be one of the following values :
  *        @arg @ref FLASH_CONFIG_IRQ_VECT_TABLE_FLASH Vector Table located in FLASH
  *        @arg @ref FLASH_CONFIG_IRQ_VECT_TABLE_RAM   Vector Table located in RAM
  * @retval None
  */
#define __HAL_FLASH_SET_VECT_TABLE(__VECT_TABLE__)  MODIFY_REG(FLASH->CONFIG, FLASH_CONFIG_REMAP, (__VECT_TABLE__))

/**
  * @brief  Get the FLASH Interrupt Vector Table location.
  * @retval Vector Table Configuration
  *         Returned value can be one of the following values :
  *         @arg @ref FLASH_CONFIG_IRQ_VECT_TABLE_FLASH Vector Table located in FLASH
  *         @arg @ref FLASH_CONFIG_IRQ_VECT_TABLE_RAM   Vector Table located in RAM
  */
#define __HAL_FLASH_GET_VECT_TABLE()  READ_BIT(FLASH->CONFIG, FLASH_CONFIG_REMAP)

/**
  * @}
  */

/** @defgroup FLASH_Interrupt FLASH Interrupts and Flags Macros
  *  @brief macros to handle FLASH interrupts
  * @{
  */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param __INTERRUPT__ FLASH interrupt
  *        This parameter can be any combination of the following values:
  *        @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *        @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *        @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *        @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)  CLEAR_BIT(FLASH->IRQMASK, (__INTERRUPT__))

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param __INTERRUPT__ FLASH interrupt
  *        This parameter can be any combination of the following values:
  *        @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *        @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *        @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *        @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval none
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  SET_BIT(FLASH->IRQMASK, (__INTERRUPT__))

/**
  * @brief  Check whether the specified FLASH interrupt has occurred or not.
  * @param __INTERRUPT__ FLASH interrupt
  *        This parameter can be any combination of the following values:
  *        @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *        @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *        @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *        @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_FLASH_GET_IT(__INTERRUPT__)  ((READ_BIT(FLASH->IRQSTAT, (__INTERRUPT__)) != RESET) ? SET : RESET)

/**
  * @brief Clear the specified FLASH interrupt flag.
  * @param __INTERRUPT__ FLASH interrupt
  *        This parameter can be any combination of the following values:
  *        @arg @ref FLASH_IT_CMDDONE  Command Done Interrupt
  *        @arg @ref FLASH_IT_CMDSTART Command Started Interrupt
  *        @arg @ref FLASH_IT_CMDERR   Command Error Interrupt
  *        @arg @ref FLASH_IT_ILLCMD   Illegal Command Interrupt
  * @retval None
  */
#define __HAL_FLASH_CLEAR_IT(__INTERRUPT__)  WRITE_REG(FLASH->IRQSTAT, (__INTERRUPT__))

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param __FLAG__ specifies the FLASH flag to check.
  *       This parameter can be one of the following values:
  *       @arg @ref FLASH_FLAG_CMDDONE     FLASH command done flag
  *       @arg @ref FLASH_FLAG_CMDSTART    FLASH command started flag
  *       @arg @ref FLASH_FLAG_CMDERR      FLASH command error flag
  *       @arg @ref FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)  ((READ_BIT(FLASH->IRQRAW, (__FLAG__)) == (__FLAG__)) ? 1UL : 0UL)

/**
  * @brief  Clear the FLASH's pending flags.
  * @param __FLAG__ specifies the FLASH flags to clear.
  *       This parameter can be any combination of the following values:
  *       @arg @ref FLASH_FLAG_CMDDONE     FLASH command done flag
  *       @arg @ref FLASH_FLAG_CMDSTART    FLASH command started flag
  *       @arg @ref FLASH_FLAG_CMDERR      FLASH command error flag
  *       @arg @ref FLASH_FLAG_ILLCMD      FLASH illegal command flag
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__) (SET_BIT(FLASH->IRQRAW, (__FLAG__)))
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32wl3x_hal_flash_ex.h"

/* Exported variables --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Variables FLASH Exported Variables
  * @{
  */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data);
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t Data);
/* FLASH IRQ handler method */
void HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
uint32_t HAL_FLASH_GetError(void);

/**
  * @}
  */

/**
  * @}
  */

/* Private types --------------------------------------------------------*/
/** @defgroup FLASH_Private_types FLASH Private Types
  * @{
  */
HAL_StatusTypeDef  FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_SIZE_MASK                 FLASH_FLASH_SIZE_FLASH_SIZE
#define FLASH_SIZE                      (((*(uint32_t *)FLASHSIZE_BASE & FLASH_SIZE_MASK) + 1) << 2U)
#define FLASH_START_ADDR                FLASH_BASE
#define FLASH_END_ADDR                  (FLASH_START_ADDR + FLASH_SIZE - 1U)

#define FLASH_PAGE_SIZE                 0x00000800U  /*!< FLASH Page Size, 2KBytes */
#define FLASH_PAGE_NUMBER               (FLASH_SIZE/FLASH_PAGE_SIZE )
#define FLASH_TIMEOUT_VALUE             1000U        /*!< FLASH Execution Timeout, 1 s */

#define FLASH_WRP_GRANULARITY           0x00004000U  /*!< FLASH Write Protection Granularity, 16KBytes */
#define FLASH_PCROP_GRANULARITY         FLASH_SIZE   /*!< FLASH Code Readout Protection Granularity, all the MAIN FLASH */

#define FLASH_TYPENONE                  0x00000000U  /*!< No Programming Procedure On Going */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  *  @{
  */

#define IS_FLASH_MAIN_MEM_ADDRESS(__VALUE__)  (((__VALUE__) >= FLASH_START_ADDR) && ((__VALUE__) <= FLASH_END_ADDR))

#define IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__VALUE__)  (((__VALUE__) >= FLASH_START_ADDR) &&\
                                                       ((__VALUE__) <= (FLASH_START_ADDR + FLASH_SIZE - 4UL)) &&\
                                                       (((__VALUE__) % 4UL) == 0UL))

#define IS_FLASH_PROGRAM_OTP_ADDRESS(__VALUE__)  (((__VALUE__) >= OTP_AREA_BASE) &&\
                                                  ((__VALUE__) <= (OTP_AREA_END_ADDR + 1UL - 4UL)) &&\
                                                  (((__VALUE__) % 4UL) == 0UL))

#define IS_FLASH_PROGRAM_ADDRESS(__VALUE__)  ((IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__VALUE__)) ||\
                                              (IS_FLASH_PROGRAM_OTP_ADDRESS(__VALUE__)))

#define IS_FLASH_PAGE(__VALUE__)  ((__VALUE__) <= FLASH_PAGE_NUMBER)

#define IS_ADDR_ALIGNED_32BITS(__VALUE__)  (((__VALUE__) & ~0x3U) == (__VALUE__))

#define IS_FLASH_WAIT_STATES(__VALUE__)  (((__VALUE__) == FLASH_WAIT_STATES_0) || \
                                          ((__VALUE__) == FLASH_WAIT_STATES_1))

#define IS_FLASH_TYPE_ERASE(__VALUE__)  (((__VALUE__) == FLASH_TYPEERASE_PAGES) || \
                                         ((__VALUE__) == FLASH_TYPEERASE_MASSERASE))

#define IS_FLASH_TYPEPROGRAM(__VALUE__)             (((__VALUE__) == FLASH_TYPEPROGRAM_WORD) || \
                                                     ((__VALUE__) == FLASH_TYPEPROGRAM_BURST))
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

#endif /* STM32WL3x_HAL_FLASH_H */
