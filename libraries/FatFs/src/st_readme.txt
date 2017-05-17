
  @verbatim
  ******************************************************************************
  *  
  *           Portions COPYRIGHT 2017 STMicroelectronics                       
  *           Portions Copyright (C) 2015, ChaN, all right reserved            
  *
  * @file    st_readme.txt 
  * @author  MCD Application Team
  * @brief   This file lists the main modification done by STMicroelectronics on
  *          FatFs for integration with STM32Cube solution.
  *          For more details on FatFs implementation on STM32Cube, please refer
  *          to UM1721 "Developing Applications on STM32Cube with FatFs"  
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

### V1.4.1/14-February-2017 ###
===============================
  + sd_diskio.c, sdram_diskio.c and sram_diskio.c: fix bug in ioctl() function; when called with
    "GET_BLOCK_SIZE" as "cmd" parameter value, the “res” variable is not updated with “RES_OK” value
    thus the FatFs is getting always "RES_ERROR" as return value, which leads to ignore the actual block size.
  + sdram_diskio.c and sram_diskio.c: update initialize() function to check the return value of BSP Init function.


### V1.4.0/23-December-2016 ###
===============================
  + Update sd_diskio.c to align with latest changes on SD HAL & BSP APIs, these changes are integrated
    in STM32Cube F4 V1.15.0 and F7 V1.6.0 and break the compatibility with previous version.


### V1.3.0/23-December-2016 ###
============================
  + Upgrade to use FatFs R0.11.
  + Add new APIs FATFS_LinkDriverEx() and FATFS_UnLinkDriverEx() to manage USB Key Disk having 
     multi-lun capability. These APIs are equivalent to FATFS_LinkDriver() and FATFS_UnLinkDriver()
     with "lun" parameter set to 0.
  + ff_conf.h: add new define "_USE_BUFF_WO_ALIGNMENT".
     This option is available only for usbh diskio interface and allow to disable
     the management of the unaligned buffer.
     When STM32 USB OTG HS or FS IP is used with internal DMA enabled, this define
     must be set to 0 to align data into 32bits through an internal scratch buffer
     before being processed by the DMA . Otherwise (DMA not used), this define must
     be set to 1 to avoid Data alignment and improve the performance.
     Please note that if _USE_BUFF_WO_ALIGNMENT is set to 1 and an unaligned 32bits
     buffer is forwarded to the FatFs Write/Read functions, an error will be returned. 
     (0: default value or 1: unaligned buffer return an error).


  + Important note:
      For application code based on previous FatFs version; when moving to R0.11
      the changes that need to be done is to update ffconf.h file, taking 
      ffconf_template.h file as reference.


### V1.2.1/20-November-2014 ###
===============================
  + Disk I/O drivers; change count argument type from BYTE to UINT

  + Important note:
      For application code based on previous FatFs version; when moving to R0.10b
      the only change that need to be done is to update ffconf.h file, taking 
      ffconf_template.h file as reference.


### V1.2.0/04-November-2014 ###
===============================
  + Upgrade to use FatFs R0.10b.
  + diskio.c: update disk_read() and disk_write() argument's type.

  + Important note:
      For application code based on previous FatFs version; when moving to R0.10b
      the only change that need to be done is to update ffconf.h file, taking 
      ffconf_template.h file as reference.


### V1.1.1/12-September-2014 ###
================================
  + ff_gen_drv.c: Update the Disk_drvTypeDef disk variable initialization to avoid
    warnings detected with Atollic TrueSTUDIO Complier.


### V1.1.0/22-April-2014 ###
============================
  + Update sd_diskio to use SD BSP in polling mode instead of DMA mode (the scratch
    buffer needed for DMA alignment is removed as well).
  + diskio.c and ff_gen_drv.c/.h: update to prevent multiple initialization.


### V1.0.0/18-February-2014 ###
===============================
   + First R0.10 customized version for STM32Cube solution.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
