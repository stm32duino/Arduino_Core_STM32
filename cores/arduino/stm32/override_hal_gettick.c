/*

Module: override_hal_gettick.c

Function:
        Override Hal_GetTick() function for STM32 platform.

Copyright notice and license information:
        Copyright 2018-2019 MCCI Corporation. All rights reserved.

        This library is free software; you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public
        License as published by the Free Software Foundation; either
        version 2.1 of the License, or (at your option) any later version.

        This library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        See the GNU Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with this library; if not, write to the Free
        Software Foundation, Inc., 51 Franklin St, Fifth Floor,
        Boston, MA  02110-1301  USA

Author:
        ChaeHee Won, MCCI Corporation

*/

#include <Arduino.h>

uint32_t HAL_GetTick(void)
        {
        extern __IO uint32_t uwTick;

        /* Read PRIMASK register, check interrupt status before disable them */
        /* Returns 0 if they are enabled, or non-zero if disabled */
        if (__get_PRIMASK())
                {
                if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
                        {
                        SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
                        HAL_IncTick();
                        }
                }

        return uwTick;
        }
