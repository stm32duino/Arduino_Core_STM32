/**
  ******************************************************************************
  * @file    stm32u3xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U3xx_HAL_FLASH_H
#define STM32U3xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
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
  uint32_t TypeErase; /*!< Mass erase or page erase.
                           This parameter can be a value of @ref FLASH_Type_Erase */
  uint32_t Banks;     /*!< Select bank to erase.
                           This parameter must be a value of @ref FLASH_Banks
                           (FLASH_BANK_BOTH should be used only for mass erase) */
  uint32_t Page;      /*!< Initial Flash page to erase when page erase is enabled
                           This parameter must be a value between 0 and (max number of pages - 1) */
  uint32_t NbPages;   /*!< Number of pages to be erased.
                           This parameter must be a value between 1 and (max number of pages - value of initial page)*/
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;      /*!< Option byte to be configured.
                                 This parameter can be a combination of the values of @ref FLASH_OB_Type */
  uint32_t WRPArea;         /*!< Write protection area to be programmed (used for @ref OPTIONBYTE_WRP).
                                 Only one WRP area could be programmed at the same time.
                                 This parameter can be value of @ref FLASH_OB_WRP_Area */
  uint32_t WRPStartOffset;  /*!< Write protection start offset (used for @ref OPTIONBYTE_WRP).
                                 This parameter must be a value between 0 and (max number of pages - 1) */
  uint32_t WRPEndOffset;    /*!< Write protection end offset (used for @ref OPTIONBYTE_WRP).
                                 This parameter must be a value between WRPStartOffset and (max number of pages - 1) */
  FunctionalState WRPLock;  /*!< Write protection lock (used for @ref OPTIONBYTE_WRP).
                                 This parameter can be set to ENABLE or DISABLE */
  uint32_t RDPLevel;        /*!< Set the read protection level (used for @ref OPTIONBYTE_RDP).
                                 This parameter can be a value of @ref FLASH_OB_Read_Protection */
  uint32_t USERType;        /*!< User option byte(s) to be configured (used for @ref OPTIONBYTE_USER).
                                 This parameter can be a combination of @ref FLASH_OB_USER_Type */
  uint32_t USERConfig;      /*!< Value of the user option byte (used for @ref OPTIONBYTE_USER).
                                 This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
                                 @ref FLASH_OB_USER_NRST_STOP, @ref FLASH_OB_USER_NRST_STANDBY,
                                 @ref FLASH_OB_USER_NRST_SHUTDOWN, @ref FLASH_OB_USER_BDRST_POR,
                                 @ref FLASH_OB_USER_SRAM1_RST, @ref FLASH_OB_USER_IWDG_SW,
                                 @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
                                 @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_SWAP_BANK,
                                 @ref FLASH_OB_USER_DUALBANK, @ref FLASH_OB_USER_SRAM2_PE,
                                 @ref FLASH_OB_USER_SRAM2_RST, @ref FLASH_OB_USER_NSWBOOT0,
                                 @ref FLASH_OB_USER_NBOOT0, @ref FLASH_OB_USER_IO_VDD_HSLV,
                                 @ref FLASH_OB_USER_IO_VDDIO2_HSLV, @ref FLASH_OB_USER_TZEN */
#if defined (CPU_IN_SECURE_STATE)
  uint32_t WMSecConfig;      /*!< Configuration of the Watermark-based Secure Area (used for @ref OPTIONBYTE_WMSEC).
                                  This parameter must be a value of @ref FLASH_OB_WMSEC */
  uint32_t WMSecStartPage;   /*!< Start page of secure area (used for @ref OPTIONBYTE_WMSEC).
                                  This parameter must be a value between 0 and (max number of pages in the bank - 1) */
  uint32_t WMSecEndPage;     /*!< End page of secure area (used for @ref OPTIONBYTE_WMSEC).
                                  This parameter must be a value between WMSecStartPage and
                                  (max number of pages in the bank - 1) */
  uint32_t WMHDPEndPage;     /*!< End page of the secure hide protection (used for @ref OPTIONBYTE_WMSEC).
                                  This parameter must be a value between WMSecStartPage and WMSecEndPage */
  uint32_t BootLock;         /*!< Configuration of the boot lock (used for @ref OPTIONBYTE_BOOT_LOCK).
                                  This parameter must be a value of @ref FLASH_OB_BOOT_LOCK */
#endif /* CPU_IN_SECURE_STATE */
  uint32_t BootAddrConfig;   /*!< Configuration of the Boot address (used for @ref OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value of @ref FLASH_OB_BOOTADDR */
  uint32_t BootAddr;         /*!< Boot address (used for @ref OPTIONBYTE_BOOTADDR).
                                  This parameter must be a value between 0x0 and 0xFFFFFF00 */
  uint32_t RDPKeyType;       /*!< Configuration of the RDP OEM keys (used for @ref OPTIONBYTE_RDPKEY).
                                  This parameter can be a value of @ref FLASH_OB_RDP_Key_Type */
  uint32_t RDPKey1;          /*!< Value of the RDP OEM key - bits[0:31] (used for @ref OPTIONBYTE_RDPKEY) */
  uint32_t RDPKey2;          /*!< Value of the RDP OEM key - bits[32:63] (used for @ref OPTIONBYTE_RDPKEY) */
  uint32_t RDPKey3;          /*!< Value of the RDP OEM key - bits[64:95] (used for @ref OPTIONBYTE_RDPKEY) */
  uint32_t RDPKey4;          /*!< Value of the RDP OEM key - bits[96:127] (used for @ref OPTIONBYTE_RDPKEY) */
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  HAL_LockTypeDef     Lock;              /*!< FLASH locking object */
  uint32_t            ErrorCode;         /*!< FLASH error code */
  uint32_t            ProcedureOnGoing;  /*!< Internal variable to indicate which procedure is ongoing
                                              or not in IT context */
  uint32_t            Address;           /*!< Internal variable to save address selected for program in IT context */
  uint32_t            Bank;              /*!< Internal variable to save current bank selected during erase
                                              in IT context */
  uint32_t            Page;              /*!< Internal variable to define the current page which is erasing
                                              in IT context */
  uint32_t            NbPagesToErase;    /*!< Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#if defined (CPU_IN_SECURE_STATE)
#define FLASH_FLAG_EOP         FLASH_SSR_EOP                  /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR       FLASH_SSR_OPERR                /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR     FLASH_SSR_PROGERR              /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR      FLASH_SSR_WRPERR               /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR      FLASH_SSR_PGAERR               /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR      FLASH_SSR_SIZERR               /*!< FLASH Size error flag */
#define FLASH_FLAG_PGSERR      FLASH_SSR_PGSERR               /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR     FLASH_SR_OPTWERR               /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY         FLASH_SSR_BSY                  /*!< FLASH Busy flag */
#define FLASH_FLAG_WDW         FLASH_SSR_WDW                  /*!< FLASH Wait Data to Write flag */
#define FLASH_FLAG_ECCC        FLASH_ECCCR_ECCC               /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD        FLASH_ECCDR_ECCD               /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS   (FLASH_FLAG_OPERR  | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR)
#define FLASH_FLAG_ECCR_ERRORS (FLASH_FLAG_ECCC      | FLASH_FLAG_ECCD)
#define FLASH_FLAG_ALL_ERRORS  (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_OPTWERR | FLASH_FLAG_ECCR_ERRORS)
#else /* CPU_IN_SECURE_STATE */
#define FLASH_FLAG_EOP         FLASH_SR_EOP                   /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR       FLASH_SR_OPERR                 /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR     FLASH_SR_PROGERR               /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR      FLASH_SR_WRPERR                /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR      FLASH_SR_PGAERR                /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR      FLASH_SR_SIZERR                /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR      FLASH_SR_PGSERR                /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_OPTWERR     FLASH_SR_OPTWERR               /*!< FLASH Option modification error flag  */
#define FLASH_FLAG_BSY         FLASH_SR_BSY                   /*!< FLASH Busy flag */
#define FLASH_FLAG_WDW         FLASH_SR_WDW                   /*!< FLASH Wait Data to Write flag */
#define FLASH_FLAG_OEM1LOCK    FLASH_SR_OEM1LOCK              /*!< FLASH OEM1 key RDP lock flag */
#define FLASH_FLAG_OEM2LOCK    FLASH_SR_OEM2LOCK              /*!< FLASH OEM2 key RDP lock flag */
#define FLASH_FLAG_PD1         FLASH_SR_PD1                   /*!< FLASH Bank1 in power-down mode flag */
#define FLASH_FLAG_PD2         FLASH_SR_PD2                   /*!< FLASH Bank2 in power-down mode flag */
#define FLASH_FLAG_ECCC        FLASH_ECCCR_ECCC               /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD        FLASH_ECCDR_ECCD               /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS   (FLASH_FLAG_OPERR  | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR  | \
                                FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR  | \
                                FLASH_FLAG_OPTWERR)
#define FLASH_FLAG_ECCR_ERRORS (FLASH_FLAG_ECCC      | FLASH_FLAG_ECCD)
#define FLASH_FLAG_ALL_ERRORS  (FLASH_FLAG_SR_ERRORS | FLASH_FLAG_ECCR_ERRORS)
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#if defined (CPU_IN_SECURE_STATE)
#define FLASH_IT_EOP     FLASH_SCR_EOPIE                              /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_SCR_ERRIE                              /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCCR_ECCIE >> FLASH_ECCCR_ECCIE_Pos) /*!< ECC Correction Interrupt source */
#else /* CPU_IN_SECURE_STATE */
#define FLASH_IT_EOP     FLASH_CR_EOPIE                               /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR   FLASH_CR_ERRIE                               /*!< Error Interrupt source */
#define FLASH_IT_ECCC    (FLASH_ECCCR_ECCIE >> FLASH_ECCCR_ECCIE_Pos) /*!< ECC Correction Interrupt source */
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE   0x00000000U        /*!< Flash no error */
#define HAL_FLASH_ERROR_OP     FLASH_FLAG_OPERR   /*!< Flash operation error */
#define HAL_FLASH_ERROR_PROG   FLASH_FLAG_PROGERR /*!< Flash programming error */
#define HAL_FLASH_ERROR_WRP    FLASH_FLAG_WRPERR  /*!< Flash write protection error */
#define HAL_FLASH_ERROR_PGA    FLASH_FLAG_PGAERR  /*!< Flash programming alignment error */
#define HAL_FLASH_ERROR_SIZ    FLASH_FLAG_SIZERR  /*!< Flash size error */
#define HAL_FLASH_ERROR_PGS    FLASH_FLAG_PGSERR  /*!< Flash programming sequence error */
#define HAL_FLASH_ERROR_OPTW   FLASH_FLAG_OPTWERR /*!< Flash option modification error */
#define HAL_FLASH_ERROR_ECCC   FLASH_FLAG_ECCC    /*!< Flash ECC correction error */
#define HAL_FLASH_ERROR_ECCD   FLASH_FLAG_ECCD    /*!< Flash ECC detection error */
/**
  * @}
  */

/** @defgroup FLASH_Type_Erase FLASH Erase Type
  * @{
  */
#if defined (CPU_IN_SECURE_STATE)
#define FLASH_TYPEERASE_PAGES        FLASH_SCR_PER \
  /*!< Secure pages erase activation */
#define FLASH_TYPEERASE_PAGES_NS     (FLASH_CR_PER  | FLASH_NON_SECURE_MASK) \
  /*!< Non-secure pages erase activation */
#define FLASH_TYPEERASE_MASSERASE    (FLASH_SCR_MER1 | FLASH_SCR_MER2) \
  /*!< Secure flash mass erase activation */
#define FLASH_TYPEERASE_MASSERASE_NS (FLASH_CR_MER1 | FLASH_CR_MER2 | FLASH_NON_SECURE_MASK) \
  /*!< Non-secure flash mass erase activation */
#else /* CPU_IN_SECURE_STATE */
#define FLASH_TYPEERASE_PAGES        FLASH_CR_PER \
  /*!< Pages erase activation */
#define FLASH_TYPEERASE_MASSERASE    (FLASH_CR_MER1 | FLASH_CR_MER2) \
  /*!< Flash mass erase activation */
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup FLASH_Banks FLASH Banks
  * @{
  */
#define FLASH_BANK_1      FLASH_CR_MER1                 /*!< Bank 1 */
#define FLASH_BANK_2      FLASH_CR_MER2                 /*!< Bank 2 */
#define FLASH_BANK_BOTH   (FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank 1 and Bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Program Type
  * @{
  */
#if defined (CPU_IN_SECURE_STATE)
#define FLASH_TYPEPROGRAM_DOUBLEWORD    FLASH_SCR_PG \
  /*!< Program a double-word (64-bit) at a specified secure address */
#define FLASH_TYPEPROGRAM_DOUBLEWORD_NS (FLASH_CR_PG | FLASH_NON_SECURE_MASK) \
  /*!< Program a double-word (64-bit) at a specified non-secure address */
#define FLASH_TYPEPROGRAM_BURST         (FLASH_SCR_PG | FLASH_SCR_BWR) \
  /*!< Program a burst (16xdouble-word) at a specified secure address */
#define FLASH_TYPEPROGRAM_BURST_NS      (FLASH_CR_PG | FLASH_CR_BWR | FLASH_NON_SECURE_MASK) \
  /*!< Program a burst (16xdouble-word) at a specified non-secure address */
#else /* CPU_IN_SECURE_STATE */
#define FLASH_TYPEPROGRAM_DOUBLEWORD    FLASH_CR_PG \
  /*!<Program a double-word (64-bit) at a specified address */
#define FLASH_TYPEPROGRAM_BURST         (FLASH_CR_PG | FLASH_CR_BWR) \
  /*!<Program a burst (16xdouble-word) at a specified address */
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP        0x00000001U /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP        0x00000002U /*!< RDP option byte configuration */
#define OPTIONBYTE_USER       0x00000004U /*!< USER option byte configuration */
#define OPTIONBYTE_BOOTADDR   0x00000008U /*!< Boot address option byte configuration */
#if defined (CPU_IN_SECURE_STATE)
#define OPTIONBYTE_WMSEC      0x00000010U /*!< Watermark-based secure area option byte configuration */
#define OPTIONBYTE_BOOT_LOCK  0x00000020U /*!< Boot lock option byte configuration */
#endif /* CPU_IN_SECURE_STATE */
#define OPTIONBYTE_RDPKEY     0x00000040U /*!< RDP Key option byte configuration */
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_Area FLASH WRP Area
  * @{
  */
#define OB_WRPAREA_BANK1_AREAA   0x00000001U /*!< Flash Bank 1 Area A */
#define OB_WRPAREA_BANK1_AREAB   0x00000002U /*!< Flash Bank 1 Area B */
#define OB_WRPAREA_BANK2_AREAA   0x00000004U /*!< Flash Bank 2 Area A */
#define OB_WRPAREA_BANK2_AREAB   0x00000008U /*!< Flash Bank 2 Area B */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0   0xAAU /*!< RDP level 0 code */
#define OB_RDP_LEVEL_0_5 0x55U /*!< RDP level 0.5 code */
#define OB_RDP_LEVEL_1   0xBBU /*!< RDP level 1 code */
#define OB_RDP_LEVEL_2   0xCCU /*!< RDP level 2 code */
/**
  * @}
  */

/** @defgroup FLASH_OB_RDP_Key_Type FLASH Option Bytes Read Protection Key Type
  * @{
  */
#define OB_RDP_KEY_OEM1 0x01U  /*!< OEM1 key */
#define OB_RDP_KEY_OEM2 0x02U  /*!< OEM2 key */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_Type FLASH Option Bytes User Type
  * @{
  */
#define OB_USER_BOR_LEV        FLASH_OPTR_BOR_LEV        /*!< BOR reset Level */
#define OB_USER_BDRST_POR      FLASH_OPTR_BDRST_POR      /*!< Backup domain reset with power on reset */
#define OB_USER_NRST_STOP      FLASH_OPTR_nRST_STOP      /*!< Reset generated when entering the stop mode */
#define OB_USER_NRST_STDBY     FLASH_OPTR_nRST_STDBY     /*!< Reset generated when entering the standby mode */
#define OB_USER_NRST_SHDW      FLASH_OPTR_nRST_SHDW      /*!< Reset generated when entering the shutdown mode */
#define OB_USER_SRAM1_RST      FLASH_OPTR_SRAM1_RST      /*!< SRAM1 erase upon system reset */
#define OB_USER_IWDG_SW        FLASH_OPTR_IWDG_SW        /*!< Independent watchdog selection */
#define OB_USER_IWDG_STOP      FLASH_OPTR_IWDG_STOP      /*!< Independent watchdog counter freeze in stop mode */
#define OB_USER_IWDG_STDBY     FLASH_OPTR_IWDG_STDBY     /*!< Independent watchdog counter freeze in standby mode */
#define OB_USER_WWDG_SW        FLASH_OPTR_WWDG_SW        /*!< Window watchdog selection */
#define OB_USER_SWAP_BANK      FLASH_OPTR_SWAP_BANK      /*!< Swap banks */
#define OB_USER_DUALBANK       FLASH_OPTR_DUALBANK       /*!< Dual-Bank on 1MB/512kB Flash memory devices */
#define OB_USER_SRAM2_PE       FLASH_OPTR_SRAM2_PE       /*!< SRAM2 parity check enable */
#define OB_USER_SRAM2_RST      FLASH_OPTR_SRAM2_RST      /*!< SRAM2 erase when system reset */
#define OB_USER_NSWBOOT0       FLASH_OPTR_nSWBOOT0       /*!< Software BOOT0 */
#define OB_USER_NBOOT0         FLASH_OPTR_nBOOT0         /*!< nBOOT0 option bit */
#define OB_USER_IO_VDD_HSLV    FLASH_OPTR_IO_VDD_HSLV    /*!< High speed IO at low VDD voltage configuration bit */
#define OB_USER_IO_VDDIO2_HSLV FLASH_OPTR_IO_VDDIO2_HSLV /*!< High speed IO at low VDDIO2 voltage configuration bit */
#define OB_USER_TZEN           FLASH_OPTR_TZEN           /*!< Global TrustZone security enable */

#define OB_USER_ALL          (OB_USER_BOR_LEV    | OB_USER_BDRST_POR   | OB_USER_NRST_STOP      | \
                              OB_USER_NRST_STDBY | OB_USER_NRST_SHDW   | OB_USER_SRAM1_RST      | \
                              OB_USER_IWDG_SW    | OB_USER_IWDG_STOP   | OB_USER_IWDG_STDBY     | \
                              OB_USER_WWDG_SW    | OB_USER_SWAP_BANK   | OB_USER_DUALBANK       | \
                              OB_USER_SRAM2_PE   | OB_USER_SRAM2_RST   | OB_USER_NSWBOOT0       | \
                              OB_USER_NBOOT0     | OB_USER_IO_VDD_HSLV | OB_USER_IO_VDDIO2_HSLV | \
                              OB_USER_TZEN)     /*!< All User option bits */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes User BOR Level
  * @{
  */
#define OB_BOR_LEVEL_0   0x00000000U                                   /*!< Reset level threshold is around 1.7V */
#define OB_BOR_LEVEL_1   FLASH_OPTR_BOR_LEV_0                          /*!< Reset level threshold is around 2.0V */
#define OB_BOR_LEVEL_2   FLASH_OPTR_BOR_LEV_1                          /*!< Reset level threshold is around 2.2V */
#define OB_BOR_LEVEL_3   (FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_1) /*!< Reset level threshold is around 2.5V */
#define OB_BOR_LEVEL_4   FLASH_OPTR_BOR_LEV_2                          /*!< Reset level threshold is around 2.8V */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BDRST_POR FLASH Option Bytes User Backup domain Reset on Power On
  * @{
  */
#define OB_BDRST_RST     FLASH_OPTR_BDRST_POR /*!< Backup domain reset after a VDD domain brownout reset */
#define OB_BDRST_NORST   0x00000000U          /*!< Backup domain not reset after a VDD domain brownout reset */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NRST_STOP FLASH Option Bytes User Reset On Stop
  * @{
  */
#define OB_STOP_RST     0x00000000U          /*!< Reset generated when entering the stop mode */
#define OB_STOP_NORST   FLASH_OPTR_nRST_STOP /*!< No reset generated when entering the stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NRST_STANDBY FLASH Option Bytes User Reset On Standby
  * @{
  */
#define OB_STANDBY_RST     0x00000000U           /*!< Reset generated when entering the standby mode */
#define OB_STANDBY_NORST   FLASH_OPTR_nRST_STDBY /*!< No reset generated when entering the standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NRST_SHUTDOWN FLASH Option Bytes User Reset On Shutdown
  * @{
  */
#define OB_SHUTDOWN_RST     0x00000000U          /*!< Reset generated when entering the shutdown mode */
#define OB_SHUTDOWN_NORST   FLASH_OPTR_nRST_SHDW /*!< No reset generated when entering the shutdown mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM1_RST FLASH Option Bytes User SRAM1 Erase On Reset Type
  * @{
  */
#define OB_SRAM1_RST_ERASE       0x00000000U          /*!< SRAM1 erased when a system reset occurs */
#define OB_SRAM1_RST_NOT_ERASE   FLASH_OPTR_SRAM1_RST /*!< SRAM1 not erased when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes User IWDG Type
  * @{
  */
#define OB_IWDG_HW   0x00000000U        /*!< Hardware independent watchdog */
#define OB_IWDG_SW   FLASH_OPTR_IWDG_SW /*!< Software independent watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH Option Bytes User IWDG Mode On Stop
  * @{
  */
#define OB_IWDG_STOP_FREEZE   0x00000000U          /*!< Independent watchdog counter is frozen in Stop mode */
#define OB_IWDG_STOP_RUN      FLASH_OPTR_IWDG_STOP /*!< Independent watchdog counter is running in Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_STANDBY FLASH Option Bytes User IWDG Mode On Standby
  * @{
  */
#define OB_IWDG_STDBY_FREEZE   0x00000000U           /*!< Independent watchdog counter is frozen in Standby mode */
#define OB_IWDG_STDBY_RUN      FLASH_OPTR_IWDG_STDBY /*!< Independent watchdog counter is running in Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_WWDG_SW FLASH Option Bytes User WWDG Type
  * @{
  */
#define OB_WWDG_HW   0x00000000U        /*!< Hardware window watchdog */
#define OB_WWDG_SW   FLASH_OPTR_WWDG_SW /*!< Software window watchdog */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SWAP_BANK FLASH Option Bytes User Swap banks
  * @{
  */
#define OB_SWAP_BANK_DISABLE   0x00000000U          /*!< Bank 1 and Bank 2 addresses not swapped */
#define OB_SWAP_BANK_ENABLE    FLASH_OPTR_SWAP_BANK /*!< Bank 1 and Bank 2 addresses swapped */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_DUALBANK FLASH Option Bytes User Dual-bank Type
  * @{
  */
#define OB_DUALBANK_SINGLE   0x00000000U         /*!< Single-bank Flash with contiguous addresses in Bank 1 */
#define OB_DUALBANK_DUAL     FLASH_OPTR_DUALBANK /*!< Dual-bank Flash with contiguous addresses */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_PE FLASH Option Bytes User SRAM2 Parity Check Enable
  * @{
  */
#define OB_SRAM2_PE_ENABLE    0x00000000U         /*!< SRAM2 Parity check enable */
#define OB_SRAM2_PE_DISABLE   FLASH_OPTR_SRAM2_PE /*!< SRAM2 Parity check disable */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SRAM2_RST FLASH Option Bytes User SRAM2 Erase On Reset Type
  * @{
  */
#define OB_SRAM2_RST_ERASE       0x00000000U          /*!< SRAM2 erased when a system reset occurs */
#define OB_SRAM2_RST_NOT_ERASE   FLASH_OPTR_SRAM2_RST /*!< SRAM2 is not erased when a system reset occurs */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NSWBOOT0 FLASH Option Bytes User Software BOOT0
  * @{
  */
#define OB_BOOT0_FROM_OB    0x00000000U         /*!< BOOT0 taken from the option bit nBOOT0 */
#define OB_BOOT0_FROM_PIN   FLASH_OPTR_nSWBOOT0 /*!< BOOT0 taken from BOOT0 pin */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_NBOOT0 FLASH Option Bytes User nBOOT0 option bit
  * @{
  */
#define OB_NBOOT0_RESET   0x00000000U       /*!< nBOOT0 = 0 */
#define OB_NBOOT0_SET     FLASH_OPTR_nBOOT0 /*!< nBOOT0 = 1 */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IO_VDD_HSLV FLASH Option Bytes User High speed IO at low voltage configuration bit
  * @{
  */
#define OB_IO_VDD_HSLV_DISABLE   0x00000000U \
  /*!< High-speed IO at low VDD voltage feature disabled (VDD can exceed 2.5 V) */
#define OB_IO_VDD_HSLV_ENABLE    FLASH_OPTR_IO_VDD_HSLV \
  /*!< High-speed IO at low VDD voltage feature enabled (VDD remains below 2.5 V) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IO_VDDIO2_HSLV FLASH Option Bytes User High speed IO at low VDDIO2 voltage\
                                           configuration bit
  * @{
  */
#define OB_IO_VDDIO2_HSLV_DISABLE   0x00000000U \
  /*!< High-speed IO at low VDDIO2 voltage feature disabled (VDDIO2 can exceed 2.5 V) */
#define OB_IO_VDDIO2_HSLV_ENABLE    FLASH_OPTR_IO_VDDIO2_HSLV \
  /*!< High-speed IO at low VDDIO2 voltage feature enabled (VDDIO2 remains below 2.5 V) */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_TZEN FLASH Option Bytes User Global TrustZone
  * @{
  */
#define OB_TZEN_DISABLE   0x00000000U     /*!< Global TrustZone security disabled */
#define OB_TZEN_ENABLE    FLASH_OPTR_TZEN /*!< Global TrustZone security enabled */
/**
  * @}
  */

#if defined (CPU_IN_SECURE_STATE)
/** @defgroup FLASH_OB_BOOT_LOCK FLASH Option Bytes Boot Lock
  * @{
  */
#define OB_BOOT_LOCK_DISABLE   0x00000000U             /*!< Boot lock disable */
#define OB_BOOT_LOCK_ENABLE    FLASH_SBOOT0R_BOOT_LOCK /*!< Boot lock enable */
/**
  * @}
  */

/** @defgroup FLASH_OB_WMSEC FLASH Option Bytes Watermarked-based security configuration
  * @{
  */
#define OB_WMSEC_AREA1                 FLASH_BANK_1 /*!< Watermarked-based security area for bank 1 */
#define OB_WMSEC_AREA2                 FLASH_BANK_2 /*!< Watermarked-based security area for bank 2 */

#define OB_WMSEC_SECURE_AREA_CONFIG    0x00000010U  /*!< Configure Watermarked-based security area */
#define OB_WMSEC_HDP_AREA_CONFIG       0x00000020U  /*!< Configure Watermarked-based secure hide area */
#define OB_WMSEC_HDP_AREA_ENABLE       0x00000040U  /*!< Enable Watermarked-based secure hide area */
#define OB_WMSEC_HDP_AREA_DISABLE      0x00000080U  /*!< Disable Watermarked-based secure hide area */
/**
  * @}
  */
#endif /* CPU_IN_SECURE_STATE */

/** @defgroup FLASH_OB_BOOTADDR FLASH Option Bytes Boot address
  * @{
  */
#define OB_BOOTADDR_NS0      0x00000001U   /*!< Non-secure boot address 0 */
#define OB_BOOTADDR_NS1      0x00000002U   /*!< Non-secure boot address 1 */
#if defined (CPU_IN_SECURE_STATE)
#define OB_BOOTADDR_SEC0     0x00000004U   /*!< Secure boot address 0 */
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0    0x00000000U \
  /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1    FLASH_ACR_LATENCY_0 \
  /*!< FLASH One wait state */
#define FLASH_LATENCY_2    FLASH_ACR_LATENCY_1 \
  /*!< FLASH Two wait states */
#define FLASH_LATENCY_3    (FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Three wait states */
#define FLASH_LATENCY_4    FLASH_ACR_LATENCY_2 \
  /*!< FLASH Four wait states */
#define FLASH_LATENCY_5    (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Five wait states */
#define FLASH_LATENCY_6    (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1) \
  /*!< FLASH Six wait states */
#define FLASH_LATENCY_7    (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Seven wait states */
#define FLASH_LATENCY_8    FLASH_ACR_LATENCY_3 \
  /*!< FLASH Eight wait states */
#define FLASH_LATENCY_9    (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Nine wait states */
#define FLASH_LATENCY_10   (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1) \
  /*!< FLASH Ten wait states */
#define FLASH_LATENCY_11   (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Eleven wait states */
#define FLASH_LATENCY_12   (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2) \
  /*!< FLASH Twelve wait states */
#define FLASH_LATENCY_13   (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0) \
  /*!< FLASH Thirteen wait states */
#define FLASH_LATENCY_14   (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1) \
  /*!< FLASH Fourteen wait states */
#define FLASH_LATENCY_15   FLASH_ACR_LATENCY \
  /*!< FLASH Fifteen wait states */
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1   0x45670123U /*!< Flash key1 */
#define FLASH_KEY2   0xCDEF89ABU /*!< Flash key2: used with FLASH_KEY1 to unlock the FLASH registers access */

#define FLASH_PDKEY1_1   0x04152637U /*!< Flash bank 1 power down key1 */
#define FLASH_PDKEY1_2   0xFAFBFCFDU /*!< Flash bank 1 power down key2:
                                          used with FLASH_PDKEY1_1 to unlock the PDREQ1 bit in FLASH_ACR */

#define FLASH_PDKEY2_1   0x40516273U /*!< Flash Bank 2 power down key1 */
#define FLASH_PDKEY2_2   0xAFBFCFDFU /*!< Flash Bank 2 power down key2:
                                          used with FLASH_PDKEY2_1 to unlock the PDREQ2 bit in FLASH_ACR */

#define FLASH_OPTKEY1   0x08192A3BU /*!< Flash option byte key1 */
#define FLASH_OPTKEY2   0x4C5D6E7FU /*!< Flash option byte key2: used with FLASH_OPTKEY1
                                         to allow option bytes operations */

#define FLASH_LVEKEY1   0xF4F5F6F7U /*!< Flash LVE key1 */
#define FLASH_LVEKEY2   0x0A1B2C3DU /*!< Flash LVE key2: used with FLASH_LVEKEY1
                                         to unlock the ULVEN and LVEN bits in FLASH_ACR */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  *  @brief macros to control FLASH features
  *  @{
  */

/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency.
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  *     @arg @ref FLASH_LATENCY_3 FLASH Three wait states
  *     @arg @ref FLASH_LATENCY_4 FLASH Four wait states
  *     @arg @ref FLASH_LATENCY_5 FLASH Five wait states
  *     @arg @ref FLASH_LATENCY_6 FLASH Six wait states
  *     @arg @ref FLASH_LATENCY_7 FLASH Seven wait states
  *     @arg @ref FLASH_LATENCY_8 FLASH Eight wait states
  *     @arg @ref FLASH_LATENCY_9 FLASH Nine wait states
  *     @arg @ref FLASH_LATENCY_10 FLASH Ten wait states
  *     @arg @ref FLASH_LATENCY_11 FLASH Eleven wait states
  *     @arg @ref FLASH_LATENCY_12 FLASH Twelve wait states
  *     @arg @ref FLASH_LATENCY_13 FLASH Thirteen wait states
  *     @arg @ref FLASH_LATENCY_14 FLASH Fourteen wait states
  *     @arg @ref FLASH_LATENCY_15 FLASH Fifteen wait states
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)   (MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__)))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         Returned value can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *     @arg @ref FLASH_LATENCY_2 FLASH Two wait states
  *     @arg @ref FLASH_LATENCY_3 FLASH Three wait states
  *     @arg @ref FLASH_LATENCY_4 FLASH Four wait states
  *     @arg @ref FLASH_LATENCY_5 FLASH Five wait states
  *     @arg @ref FLASH_LATENCY_6 FLASH Six wait states
  *     @arg @ref FLASH_LATENCY_7 FLASH Seven wait states
  *     @arg @ref FLASH_LATENCY_8 FLASH Eight wait states
  *     @arg @ref FLASH_LATENCY_9 FLASH Nine wait states
  *     @arg @ref FLASH_LATENCY_10 FLASH Ten wait states
  *     @arg @ref FLASH_LATENCY_11 FLASH Eleven wait states
  *     @arg @ref FLASH_LATENCY_12 FLASH Twelve wait states
  *     @arg @ref FLASH_LATENCY_13 FLASH Thirteen wait states
  *     @arg @ref FLASH_LATENCY_14 FLASH Fourteen wait states
  *     @arg @ref FLASH_LATENCY_15 FLASH Fifteen wait states
  */
#define __HAL_FLASH_GET_LATENCY()   READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)

/**
  * @brief  Enable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()   SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN)

/**
  * @brief  Disable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN)

/**
  * @brief  Enable the FLASH power down during Low-Power sleep mode
  * @retval None
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_ENABLE()   SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Disable the FLASH power down during Low-Power sleep mode
  * @retval None
  */
#define __HAL_FLASH_SLEEP_POWERDOWN_DISABLE()   CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @}
  */

/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
  *  @brief macros to handle FLASH interrupts
  * @{
  */

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Enable secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->SCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
/**
  * @brief  Enable non-secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_ENABLE_IT_NS(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
#else /* CPU_IN_SECURE_STATE */
/**
  * @brief  Enable non-secure FLASH interrupts from the non-secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { SET_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { SET_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
#endif /* CPU_IN_SECURE_STATE */

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Disable secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->SCR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
/**
  * @brief  Disable non-secure FLASH interrupts from the secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT_NS(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
#else /* CPU_IN_SECURE_STATE */
/**
  * @brief  Disable non-secure FLASH interrupts from the non-secure world.
  * @param  __INTERRUPT__ FLASH interrupt.
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  *     @arg @ref FLASH_IT_ECCC ECC Correction Interrupt
  * @retval None
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)\
  do { if(((__INTERRUPT__) & FLASH_IT_ECCC) != 0U) { CLEAR_BIT(FLASH->ECCCR, FLASH_ECCCR_ECCIE); }\
      if(((__INTERRUPT__) & (~FLASH_IT_ECCC)) != 0U) { CLEAR_BIT(FLASH->CR, ((__INTERRUPT__) & (~FLASH_IT_ECCC))); }\
  } while(0)
#endif /* CPU_IN_SECURE_STATE */

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Check whether the specified secure FLASH flags from the secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_OPTWERR FLASH Option modification error flag
  *     @arg @ref FLASH_FLAG_BSY FLASH write/erase operations in progress flag
  *     @arg @ref FLASH_FLAG_WDW FLASH Wait Data to Write flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCC) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCCR, (__FLAG__)) == (__FLAG__)) : \
                                                 ((((__FLAG__) & (FLASH_FLAG_ECCD)) != 0U) ? \
                                                  (READ_BIT(FLASH->ECCDR, (__FLAG__)) == (__FLAG__)) : \
                                                  ((((__FLAG__) & (FLASH_FLAG_OPTWERR)) != 0U) ? \
                                                   (READ_BIT(FLASH->SR, (__FLAG__)) == (__FLAG__)) : \
                                                   (READ_BIT(FLASH->SSR, (__FLAG__)) == (__FLAG__)))))
/**
  * @brief  Check whether the specified non-secure FLASH flags from the secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_OPTWERR FLASH Option modification error flag
  *     @arg @ref FLASH_FLAG_BSY FLASH write/erase operations in progress flag
  *     @arg @ref FLASH_FLAG_WDW FLASH Wait Data to Write flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG_NS(__FLAG__)       ((((__FLAG__) & FLASH_FLAG_ECCC) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCCR, (__FLAG__)) == (__FLAG__)) : \
                                                 ((((__FLAG__) & (FLASH_FLAG_ECCD)) != 0U) ? \
                                                  (READ_BIT(FLASH->ECCDR, (__FLAG__)) == (__FLAG__)) : \
                                                  (READ_BIT(FLASH->SR, (__FLAG__)) == (__FLAG__))))
#else /* CPU_IN_SECURE_STATE */
/**
  * @brief  Check whether the specified non-secure FLASH flags from the non-secure world is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_OPTWERR FLASH Option modification error flag
  *     @arg @ref FLASH_FLAG_BSY FLASH write/erase operations in progress flag
  *     @arg @ref FLASH_FLAG_WDW FLASH Wait Data to Write flag
  *     @arg @ref FLASH_FLAG_OEM1LOCK FLASH OEM1 key RDP lock flag
  *     @arg @ref FLASH_FLAG_OEM2LOCK FLASH OEM2 key RDP lock flag
  *     @arg @ref FLASH_FLAG_PD1 FLASH bank 1 in power-down lock flag
  *     @arg @ref FLASH_FLAG_PD2 FLASH bank 2 in power-down lock flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCC) != 0U) ? \
                                                 (READ_BIT(FLASH->ECCCR, (__FLAG__)) == (__FLAG__)) : \
                                                 ((((__FLAG__) & (FLASH_FLAG_ECCD)) != 0U) ? \
                                                  (READ_BIT(FLASH->ECCDR, (__FLAG__)) == (__FLAG__)) : \
                                                  (READ_BIT(FLASH->SR, (__FLAG__)) == (__FLAG__))))
#endif /* CPU_IN_SECURE_STATE */

#if defined (CPU_IN_SECURE_STATE)
/**
  * @brief  Clear secure FLASH flags from the secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  *     @arg @ref FLASH_FLAG_ALL_ERRORS FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)\
  do { if(((__FLAG__) & FLASH_FLAG_ECCC) != 0U)\
    { SET_BIT(FLASH->ECCCR, ((__FLAG__) & FLASH_FLAG_ECCC)); }\
    if(((__FLAG__) & FLASH_FLAG_ECCD) != 0U)\
    { SET_BIT(FLASH->ECCDR, ((__FLAG__) & FLASH_FLAG_ECCD)); }\
    if(((__FLAG__) & FLASH_FLAG_OPTWERR) != 0U)\
    { SET_BIT(FLASH->SR, ((__FLAG__) & FLASH_FLAG_OPTWERR)); }\
    if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS | FLASH_FLAG_OPTWERR)) != 0U)\
    { WRITE_REG(FLASH->SSR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS | FLASH_FLAG_OPTWERR))); } \
  } while(0)
/**
  * @brief  Clear non-secure FLASH flags from the secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_OPTWERR FLASH Option modification error flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  *     @arg @ref FLASH_FLAG_ALL_ERRORS FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG_NS(__FLAG__)\
  do { if(((__FLAG__) & FLASH_FLAG_ECCC) != 0U)\
    { SET_BIT(FLASH->ECCCR, ((__FLAG__) & FLASH_FLAG_ECCC)); }\
    if(((__FLAG__) & FLASH_FLAG_ECCD) != 0U)\
    { SET_BIT(FLASH->ECCDR, ((__FLAG__) & FLASH_FLAG_ECCD)); }\
    if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U)\
    { WRITE_REG(FLASH->SR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
  } while(0)
#else /* CPU_IN_SECURE_STATE */
/**
  * @brief  Clear non-secure FLASH flags from the non-secure world.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_OPERR FLASH Operation error flag
  *     @arg @ref FLASH_FLAG_PROGERR FLASH Programming error flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_PGAERR FLASH Programming alignment error flag
  *     @arg @ref FLASH_FLAG_SIZERR FLASH Size error flag
  *     @arg @ref FLASH_FLAG_PGSERR FLASH Programming sequence error flag
  *     @arg @ref FLASH_FLAG_OPTWERR FLASH Option modification error flag
  *     @arg @ref FLASH_FLAG_ECCC FLASH one ECC error has been detected and corrected
  *     @arg @ref FLASH_FLAG_ECCD FLASH two ECC errors have been detected
  *     @arg @ref FLASH_FLAG_ALL_ERRORS FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)\
  do { if(((__FLAG__) & FLASH_FLAG_ECCC) != 0U)\
    { SET_BIT(FLASH->ECCCR, ((__FLAG__) & FLASH_FLAG_ECCC)); }\
    if(((__FLAG__) & FLASH_FLAG_ECCD) != 0U)\
    { SET_BIT(FLASH->ECCDR, ((__FLAG__) & FLASH_FLAG_ECCD)); }\
    if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U)\
    { WRITE_REG(FLASH->SR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
  } while(0)
#endif /* CPU_IN_SECURE_STATE */
/**
  * @}
  */

/* Include FLASH HAL Extended module */
#include "stm32u3xx_hal_flash_ex.h"


/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress);
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t DataAddress);
/* FLASH IRQ handler method */
void               HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void               HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void               HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef  HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Launch(void);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
uint32_t HAL_FLASH_GetError(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Private function ----------------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_BANK_SIZE          (FLASH_SIZE / 2U)
#define FLASH_PAGE_SIZE          0x1000U  /* 4 KB */

#define FLASH_PAGE_NB            (FLASH_BANK_SIZE / FLASH_PAGE_SIZE)

#define FLASH_TIMEOUT_VALUE      1000U   /* 1 s */

#define FLASH_NON_SECURE_MASK    0x80000000U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  *  @{
  */
#if defined (CPU_IN_SECURE_STATE)
#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_PAGES)     || \
                                            ((VALUE) == FLASH_TYPEERASE_PAGES_NS)  || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE) || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE_NS))
#else /* CPU_IN_SECURE_STATE */
#define IS_FLASH_TYPEERASE(VALUE)          (((VALUE) == FLASH_TYPEERASE_PAGES) || \
                                            ((VALUE) == FLASH_TYPEERASE_MASSERASE))
#endif /* CPU_IN_SECURE_STATE */

#define IS_FLASH_BANK(BANK)                (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2)  || \
                                            ((BANK) == FLASH_BANK_BOTH))

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2))


#if defined (CPU_IN_SECURE_STATE)
#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD)    || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD_NS) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST)       || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST_NS))
#else /* CPU_IN_SECURE_STATE */
#define IS_FLASH_TYPEPROGRAM(VALUE)        (((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD) || \
                                            ((VALUE) == FLASH_TYPEPROGRAM_BURST))
#endif /* CPU_IN_SECURE_STATE */

#if defined (CPU_IN_SECURE_STATE)
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) ((((ADDRESS) >= FLASH_BASE)    &&\
                                             ((ADDRESS) < (FLASH_BASE+FLASH_SIZE))) || \
                                            (((ADDRESS) >= FLASH_BASE_NS) &&\
                                             ((ADDRESS) < (FLASH_BASE_NS+FLASH_SIZE))))
#else /* CPU_IN_SECURE_STATE */
#define IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE)     && ((ADDRESS) < (FLASH_BASE+FLASH_SIZE)))
#endif /* CPU_IN_SECURE_STATE */

#define IS_FLASH_OTP_ADDRESS(ADDRESS)      (((ADDRESS) >= FLASH_OTP_BASE) &&\
                                            ((ADDRESS) < (FLASH_OTP_BASE + FLASH_OTP_SIZE)))

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  ((IS_FLASH_MAIN_MEM_ADDRESS(ADDRESS)) || (IS_FLASH_OTP_ADDRESS(ADDRESS)))

#define IS_FLASH_PAGE(PAGE)                ((PAGE) < FLASH_PAGE_NB)

#if defined (CPU_IN_SECURE_STATE)
#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP       | \
                                                         OPTIONBYTE_RDP       | \
                                                         OPTIONBYTE_USER      | \
                                                         OPTIONBYTE_WMSEC     | \
                                                         OPTIONBYTE_BOOT_LOCK | \
                                                         OPTIONBYTE_BOOTADDR  | \
                                                         OPTIONBYTE_RDPKEY)))
#else /* CPU_IN_SECURE_STATE */
#define IS_OPTIONBYTE(VALUE)               (((VALUE) <= (OPTIONBYTE_WRP   | OPTIONBYTE_RDP   | OPTIONBYTE_USER | \
                                                         OPTIONBYTE_BOOTADDR | OPTIONBYTE_RDPKEY)))
#endif /* CPU_IN_SECURE_STATE */

#define IS_OB_WRPAREA(VALUE)               (((VALUE) == OB_WRPAREA_BANK1_AREAA) || \
                                            ((VALUE) == OB_WRPAREA_BANK1_AREAB) || \
                                            ((VALUE) == OB_WRPAREA_BANK2_AREAA) || \
                                            ((VALUE) == OB_WRPAREA_BANK2_AREAB))

#define IS_OB_RDP_LEVEL(LEVEL)             (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_0_5) ||\
                                            ((LEVEL) == OB_RDP_LEVEL_1)   ||\
                                            ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_USER_TYPE(TYPE)              ((((TYPE) & OB_USER_ALL) != 0x00U) && (((TYPE) & ~OB_USER_ALL) == 0x00U))

#define IS_OB_USER_BOR_LEVEL(LEVEL)        (((LEVEL) == OB_BOR_LEVEL_0) || ((LEVEL) == OB_BOR_LEVEL_1) || \
                                            ((LEVEL) == OB_BOR_LEVEL_2) || ((LEVEL) == OB_BOR_LEVEL_3) || \
                                            ((LEVEL) == OB_BOR_LEVEL_4))

#define IS_OB_USER_BDRST(VALUE)            (((VALUE) == OB_BDRST_RST) || ((VALUE) == OB_BDRST_NORST))

#define IS_OB_USER_STOP(VALUE)             (((VALUE) == OB_STOP_RST) || ((VALUE) == OB_STOP_NORST))

#define IS_OB_USER_STANDBY(VALUE)          (((VALUE) == OB_STANDBY_RST) || ((VALUE) == OB_STANDBY_NORST))

#define IS_OB_USER_SHUTDOWN(VALUE)         (((VALUE) == OB_SHUTDOWN_RST) || ((VALUE) == OB_SHUTDOWN_NORST))

#define IS_OB_USER_SRAM1_RST(VALUE)        (((VALUE) == OB_SRAM1_RST_ERASE) || ((VALUE) == OB_SRAM1_RST_NOT_ERASE))

#define IS_OB_USER_IWDG(VALUE)             (((VALUE) == OB_IWDG_HW) || ((VALUE) == OB_IWDG_SW))

#define IS_OB_USER_IWDG_STOP(VALUE)        (((VALUE) == OB_IWDG_STOP_FREEZE) || ((VALUE) == OB_IWDG_STOP_RUN))

#define IS_OB_USER_IWDG_STDBY(VALUE)       (((VALUE) == OB_IWDG_STDBY_FREEZE) || ((VALUE) == OB_IWDG_STDBY_RUN))

#define IS_OB_USER_WWDG(VALUE)             (((VALUE) == OB_WWDG_HW) || ((VALUE) == OB_WWDG_SW))

#define IS_OB_USER_SWAP_BANK(VALUE)        (((VALUE) == OB_SWAP_BANK_DISABLE) || ((VALUE) == OB_SWAP_BANK_ENABLE))

#define IS_OB_USER_DUALBANK(VALUE)         (((VALUE) == OB_DUALBANK_SINGLE) || ((VALUE) == OB_DUALBANK_DUAL))

#define IS_OB_USER_SRAM2_PE(VALUE)         (((VALUE) == OB_SRAM2_PE_ENABLE) || ((VALUE) == OB_SRAM2_PE_DISABLE))

#define IS_OB_USER_SRAM2_RST(VALUE)        (((VALUE) == OB_SRAM2_RST_ERASE) || ((VALUE) == OB_SRAM2_RST_NOT_ERASE))

#define IS_OB_USER_SWBOOT0(VALUE)          (((VALUE) == OB_BOOT0_FROM_OB) || ((VALUE) == OB_BOOT0_FROM_PIN))

#define IS_OB_USER_BOOT0(VALUE)            (((VALUE) == OB_NBOOT0_RESET) || ((VALUE) == OB_NBOOT0_SET))

#define IS_OB_USER_IO_VDD_HSLV(VALUE)      (((VALUE) == OB_IO_VDD_HSLV_DISABLE) || ((VALUE) == OB_IO_VDD_HSLV_ENABLE))

#define IS_OB_USER_IO_VDDIO2_HSLV(VALUE)   (((VALUE) == OB_IO_VDDIO2_HSLV_DISABLE) ||\
                                            ((VALUE) == OB_IO_VDDIO2_HSLV_ENABLE))

#define IS_OB_USER_TZEN(VALUE)             (((VALUE) == OB_TZEN_DISABLE) || ((VALUE) == OB_TZEN_ENABLE))

#if defined (CPU_IN_SECURE_STATE)
#define IS_OB_BOOT_LOCK(VALUE)             (((VALUE) == OB_BOOT_LOCK_DISABLE) || ((VALUE) == OB_BOOT_LOCK_ENABLE))

#define IS_OB_WMSEC_CONFIG(CFG)            ((((CFG) & 0x80F4U) != 0U) && \
                                            (((CFG) & 0x8004U) != 0U) &&   \
                                            (((CFG) & 0xFFFF7F0BU) == 0U))

#define IS_OB_WMSEC_AREA_EXCLUSIVE(WMSEC)  (((((WMSEC) & OB_WMSEC_AREA1) != 0U) && \
                                             (((WMSEC) & OB_WMSEC_AREA2) == 0U)) || \
                                            ((((WMSEC) & OB_WMSEC_AREA2) != 0U) && \
                                             (((WMSEC) & OB_WMSEC_AREA1) == 0U)))
#endif /* CPU_IN_SECURE_STATE */

#if defined (CPU_IN_SECURE_STATE)
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || \
                                            ((CFG) == OB_BOOTADDR_NS1) || \
                                            ((CFG) == OB_BOOTADDR_SEC0))
#else /* CPU_IN_SECURE_STATE */
#define IS_OB_BOOTADDR_CONFIG(CFG)         (((CFG) == OB_BOOTADDR_NS0) || ((CFG) == OB_BOOTADDR_NS1))
#endif /* CPU_IN_SECURE_STATE */

#define IS_FLASH_LATENCY(LATENCY)          (((LATENCY) == FLASH_LATENCY_0)  || ((LATENCY) == FLASH_LATENCY_1) || \
                                            ((LATENCY) == FLASH_LATENCY_2)  || ((LATENCY) == FLASH_LATENCY_3) || \
                                            ((LATENCY) == FLASH_LATENCY_4)  || ((LATENCY) == FLASH_LATENCY_5) || \
                                            ((LATENCY) == FLASH_LATENCY_6)  || ((LATENCY) == FLASH_LATENCY_7) || \
                                            ((LATENCY) == FLASH_LATENCY_8)  || ((LATENCY) == FLASH_LATENCY_9) || \
                                            ((LATENCY) == FLASH_LATENCY_10) || ((LATENCY) == FLASH_LATENCY_11) || \
                                            ((LATENCY) == FLASH_LATENCY_12) || ((LATENCY) == FLASH_LATENCY_13) || \
                                            ((LATENCY) == FLASH_LATENCY_14) || ((LATENCY) == FLASH_LATENCY_15))

#define IS_OB_RDP_KEY_TYPE(TYPE)           (((TYPE) == OB_RDP_KEY_OEM1) || ((TYPE) == OB_RDP_KEY_OEM2))

#if defined (CPU_IN_SECURE_STATE)
#define IS_FLASH_SECURE_OPERATION()        ((pFlash.ProcedureOnGoing & FLASH_NON_SECURE_MASK) == 0U)
#else /* CPU_IN_SECURE_STATE */
#define IS_FLASH_SECURE_OPERATION()        (0U)
#endif /* CPU_IN_SECURE_STATE */
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

#endif /* STM32U3xx_HAL_FLASH_H */
