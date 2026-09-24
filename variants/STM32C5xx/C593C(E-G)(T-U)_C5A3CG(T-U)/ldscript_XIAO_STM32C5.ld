/*
 * Copyright (c) 2026, Seeed Technology Co., Ltd.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * The application starts after the 32 KiB TinyUF2 bootloader. Memory sizes are
 * supplied by boards.txt through LD_MAX_SIZE and LD_MAX_DATA_SIZE.
 */
ENTRY(Reset_Handler)

HEAP_SIZE = 0x2000;
STACK_SIZE = 0x2000;

MEMORY
{
  ROM (rx)  : org = 0x08000000 + LD_FLASH_OFFSET, len = LD_MAX_SIZE - LD_FLASH_OFFSET
  /* TinyUF2 uses the final SRAM word for the 1200-bps reset handoff. */
  RAM (xrw) : org = 0x20000000, len = LD_MAX_DATA_SIZE - 4
}

SECTIONS
{
  .vectors :
  {
    . = ALIGN(8);
    KEEP(*(.vectors));
    . = ALIGN(8);
  } > ROM

  .text :
  {
    . = ALIGN(8);
    *(.text);
    *(.text*);
    *(.glue_7);
    *(.glue_7t);
    *(.eh_frame);
    KEEP(*(.init));
    KEEP(*(.fini));
    . = ALIGN(8);
    _etext = .;
  } > ROM

  .rodata :
  {
    . = ALIGN(8);
    *(.rodata);
    *(.rodata*);
    . = ALIGN(8);
  } > ROM

  .ARM.extab (READONLY) :
  {
    . = ALIGN(8);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(8);
  } > ROM

  .ARM (READONLY) :
  {
    . = ALIGN(8);
    __exidx_start = .;
    *(.ARM.exidx*);
    __exidx_end = .;
    . = ALIGN(8);
  } > ROM

  .preinit_array (READONLY) :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array*));
    PROVIDE_HIDDEN(__preinit_array_end = .);
    . = ALIGN(8);
  } > ROM

  .init_array (READONLY) :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)));
    KEEP(*(.init_array*));
    PROVIDE_HIDDEN(__init_array_end = .);
    . = ALIGN(8);
  } > ROM

  .fini_array (READONLY) :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)));
    KEEP(*(.fini_array*));
    PROVIDE_HIDDEN(__fini_array_end = .);
    . = ALIGN(8);
  } > ROM

  .copy.table (READONLY) :
  {
    . = ALIGN(8);
    __copy_table_start__ = .;
    LONG(LOADADDR(.data));
    LONG(ADDR(.data));
    LONG(SIZEOF(.data) / 4);
    __copy_table_end__ = .;
  } > ROM

  .zero.table (READONLY) :
  {
    . = ALIGN(8);
    __zero_table_start__ = .;
    LONG(ADDR(.bss));
    LONG(SIZEOF(.bss) / 4);
    __zero_table_end__ = .;
  } > ROM

  .data :
  {
    . = ALIGN(8);
    _sidata = LOADADDR(.data);
    __data_start__ = .;
    _sdata = .;
    *(.data);
    *(.data*);
    . = ALIGN(8);
    _edata = .;
  } > RAM AT> ROM

  .bss :
  {
    . = ALIGN(8);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss);
    *(.bss*);
    *(COMMON);
    . = ALIGN(8);
    _ebss = .;
    __bss_end__ = _ebss;
  } > RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    _heap_start = .;
    . += HEAP_SIZE;
    . = ALIGN(8);
    _heap_end = .;
    __HeapLimit = .;
  } > RAM

  .stack (NOLOAD) :
  {
    . = ALIGN(8);
    __StackLimit = .;
    . += STACK_SIZE;
    . = ALIGN(8);
    __StackTop = .;
    _estack = .;
    __stack = .;
  } > RAM

  /DISCARD/ :
  {
    libc.a(*);
    libm.a(*);
    libgcc.a(*);
  }

  .ARM.attributes 0 :
  {
    *(.ARM.attributes)
  }
}
