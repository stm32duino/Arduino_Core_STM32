/*

Module: yield.c

Function:
        Override yield() function for STM32 platform.

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

/*

Name:	yield

Function:
        Yield CPU

Definition:
        void yield(void);

Description:
        This function override default week yield() function in the cores/
        arduino/hooks.c file. It requests wait for interrupt.

Returns:
        No explicit result.

Notes:
        We need to keep this function in this file because linker should link
        this yield function in this file. So do not make this yield function
        in separate file.

*/

void yield(void)
        {
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
        else
                {
                /* Request Wait For Interrupt */
                __WFI();
                }
        }
