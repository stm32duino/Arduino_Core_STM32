/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Abstract    : Linker script for STM32MP1 series
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** Copyright (c) 2019 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
******************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x10040000;    /* end of RAM */

_Min_Heap_Size  = 0x200;  /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Memories definition */
MEMORY
{
  m_interrupts (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000298
  m_text       (RX)  : ORIGIN = 0x10000000, LENGTH = 0x00020000
  m_data       (RW)  : ORIGIN = 0x10020000, LENGTH = 0x00020000
  m_ipc_shm    (RW)  : ORIGIN = 0x10040000, LENGTH = 0x00008000
}

/* Symbols needed for OpenAMP to enable rpmsg */
__OPENAMP_region_start__  = ORIGIN(m_ipc_shm);
__OPENAMP_region_end__ = ORIGIN(m_ipc_shm)+LENGTH(m_ipc_shm);

/* Sections */
SECTIONS
{
  /* The startup code into ROM memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } > m_interrupts

  /* The program code and other data into ROM memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } > m_text

  /* Constant data into ROM memory*/
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } > m_text

  .ARM.extab   : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } > m_text

  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } > m_text

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } > m_text

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } > m_text

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } > m_text

  /* Used by the startup to initialize data */
  __DATA_ROM = .;
  _sidata = LOADADDR(.data);

  /* Initialized data sections */
  .data :  AT(__DATA_ROM)
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } > m_data

  __DATA_END = __DATA_ROM + (_edata - _sdata);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  .resource_table :
  {
    . = ALIGN(4);
    KEEP (*(.resource_table*))
    . = ALIGN(4);
  } > m_data
  _eirsc = LOADADDR(.resource_table) + SIZEOF(.resource_table);
  ASSERT(SIZEOF(.resource_table) == 0 || _eirsc <= text_end, "no room for resource_table load section in text")

  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss : AT (ADDR (.bss))
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } > m_data

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > m_data


  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }

}
