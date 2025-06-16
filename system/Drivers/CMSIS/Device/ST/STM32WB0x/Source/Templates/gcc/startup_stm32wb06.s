/**
  ******************************************************************************
  * @file      : startup_stm32wb06.s
  * @author    : GPM MCD Application Team
  * @brief     : STM32WB06 Ultra Low Power Devices vector
  *              This module performs:
  *              - Set the initial SP
  *              - Set the initial PC == Reset_Handler,
  *              - Set the vector table entries with the exceptions ISR address
  *              - Branches to main in the C library (which eventually
  *                calls main()).
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

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global  __vector_table
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section of blue_ram defined in linker script */
.word  _sbssblue
/* end address for the .bss section of blue_ram defined in linker script */
.word  _ebssblue
/* start address for the .bss section defined in linker script */
.word  _sbss
/* end address for the .bss section defined in linker script */
.word  _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

	.section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
   ldr   r0, =_estack
   mov   sp, r0          /* set stack pointer */
/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =_sbss
  b  LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss
  ldr  r2, =_sbssblue
  b  LoopFillZeroBlueRam


FillZerobssram:
  movs  r3, #0
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZeroBlueRam:
  ldr  r3, = _ebssblue
  cmp  r2, r3
  bcc  FillZerobssram

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl  main

LoopForever:
    b LoopForever

.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .intvec,"a",%progbits
  .type  __vector_table, %object
  .size  __vector_table, .-__vector_table


__vector_table:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  .word  FLASH_IRQHandler             /* IRQ0:  FLASH Controller interrupt    */
  .word  RCC_IRQHandler               /* IRQ1:  RCC interrupt                 */
  .word  PVD_IRQHandler               /* IRQ2:  PVD interrupt                 */
  .word I2C1_IRQHandler               /* IRQ3:  I2C1 interrupt                */
  .word I2C2_IRQHandler               /* IRQ4:  I2C2 interrupt                */
  .word SPI1_IRQHandler               /* IRQ5:  SPI1 interrupt                */
  .word SPI2_IRQHandler               /* IRQ6:  SPI2 interrupt                */
  .word SPI3_IRQHandler               /* IRQ7:  SPI3 interrupt                */
  .word USART1_IRQHandler             /* IRQ8:  USART1 interrupt              */
  .word LPUART1_IRQHandler            /* IRQ9:  LPUART1 interrupt             */
  .word TIM1_IRQHandler               /* IRQ10: TIM1 interrupt                */
  .word RTC_IRQHandler                /* IRQ11: RTC interrupt                 */
  .word ADC_IRQHandler                /* IRQ12: ADC interrupt                 */
  .word PKA_IRQHandler                /* IRQ13: PKA interrupt                 */
  .word 0x00000000                    /* IRQ14: Reserved                      */
  .word GPIOA_IRQHandler              /* IRQ15: GPIOA interrupt               */
  .word GPIOB_IRQHandler              /* IRQ16: GPIOB interrupt               */
  .word DMA_IRQHandler                /* IRQ17: DMA interrupt                 */
  .word RADIO_TXRX_IRQHandler         /* IRQ18: RADIO Tx/Rx interrupt         */
  .word 0x00000000                    /* IRQ19: Reserved                      */
  .word RADIO_TIMER_ERROR_IRQHandler  /* IRQ20: RADIO TIMER Error interrupt   */
  .word 0x00000000                    /* IRQ21: Reserved                      */
  .word 0x00000000                    /* IRQ22: Reserved                      */
  .word RADIO_TIMER_CPU_WKUP_IRQHandler   /* IRQ23: RADIO TIMER CPU Wakeup interrupt    */
  .word RADIO_TIMER_TXRX_WKUP_IRQHandler  /* IRQ24: RADIO TIMER Wakeup interrupt        */
  .word RADIO_TXRX_SEQ_IRQHandler     /* IRQ25: RADIO Tx/Rx Sequence interrupt*/
  .word 0x00000000                    /* IRQ26: Reserved                      */
  .word 0x00000000                    /* IRQ27: Reserved                      */
  .word 0x00000000                    /* IRQ28: Reserved                      */
  .word 0x00000000                    /* IRQ29: Reserved                      */
  .word 0x00000000                    /* IRQ30: Reserved                      */
  .word 0x00000000                    /* IRQ31: Reserved                      */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RCC_IRQHandler
   .thumb_set RCC_IRQHandler,Default_Handler

   .weak      PVD_IRQHandler
   .thumb_set PVD_IRQHandler,Default_Handler

   .weak      I2C1_IRQHandler
   .thumb_set I2C1_IRQHandler,Default_Handler

   .weak      I2C2_IRQHandler
   .thumb_set I2C2_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler,Default_Handler

   .weak      SPI3_IRQHandler
   .thumb_set SPI3_IRQHandler,Default_Handler

   .weak      USART1_IRQHandler
   .thumb_set USART1_IRQHandler,Default_Handler

   .weak      LPUART1_IRQHandler
   .thumb_set LPUART1_IRQHandler,Default_Handler

   .weak      TIM1_IRQHandler
   .thumb_set TIM1_IRQHandler,Default_Handler

   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler,Default_Handler

   .weak      ADC_IRQHandler
   .thumb_set ADC_IRQHandler,Default_Handler

   .weak      PKA_IRQHandler
   .thumb_set PKA_IRQHandler,Default_Handler

   .weak      GPIOA_IRQHandler
   .thumb_set GPIOA_IRQHandler,Default_Handler

   .weak      GPIOB_IRQHandler
   .thumb_set GPIOB_IRQHandler,Default_Handler

   .weak      DMA_IRQHandler
   .thumb_set DMA_IRQHandler,Default_Handler

   .weak      RADIO_TXRX_IRQHandler
   .thumb_set RADIO_TXRX_IRQHandler,Default_Handler

   .weak      RADIO_TIMER_ERROR_IRQHandler
   .thumb_set RADIO_TIMER_ERROR_IRQHandler,Default_Handler

   .weak      RADIO_TIMER_CPU_WKUP_IRQHandler
   .thumb_set RADIO_TIMER_CPU_WKUP_IRQHandler,Default_Handler

   .weak      RADIO_TIMER_TXRX_WKUP_IRQHandler
   .thumb_set RADIO_TIMER_TXRX_WKUP_IRQHandler,Default_Handler

   .weak      RADIO_TXRX_SEQ_IRQHandler
   .thumb_set RADIO_TXRX_SEQ_IRQHandler,Default_Handler


	.weak	SystemInit

/************************ (C) COPYRIGHT STMicroelectonics *****END OF FILE****/
