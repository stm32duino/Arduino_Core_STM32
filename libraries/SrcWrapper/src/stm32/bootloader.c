#include "bootloader.h"

#include <stdbool.h>

#include "stm32_def.h"
#include "backup.h"

#ifdef BL_LEGACY_LEAF
void dtr_togglingHook(uint8_t *buf, uint32_t *len)
{
  /**
   * Four byte is the magic pack "1EAF" that puts the MCU into bootloader.
   * Check if the incoming contains the string "1EAF".
   * If yes, put the MCU into the bootloader mode.
   */
  if ((*len >= 4) && (buf[0] == '1') && (buf[1] == 'E') && (buf[2] == 'A') && (buf[3] == 'F')) {
    NVIC_SystemReset();
  }
}
#endif /* BL_LEGACY_LEAF */

#ifdef BL_HID
void dtr_togglingHook(uint8_t *buf, uint32_t *len)
{
  /**
   * Four byte is the magic pack "1EAF" that puts the MCU into bootloader.
   * Check if the incoming contains the string "1EAF".
   * If yes, put the MCU into the bootloader mode.
   */
  if ((*len >= 4) && (buf[0] == '1') && (buf[1] == 'E') && (buf[2] == 'A') && (buf[3] == 'F')) {
    enableBackupDomain();
    /* New HID Bootloader (ver 2.2+) */
    setBackupRegister(HID_MAGIC_NUMBER_BKP_INDEX, HID_MAGIC_NUMBER_BKP_VALUE);
#ifdef HID_OLD_MAGIC_NUMBER_BKP_INDEX
    /* Compatibility to the old HID Bootloader (ver <= 2.1) */
    setBackupRegister(HID_OLD_MAGIC_NUMBER_BKP_INDEX, HID_MAGIC_NUMBER_BKP_VALUE);
#endif
    NVIC_SystemReset();
  }
}
#endif /* BL_HID */

#if defined(BL_SYSTEM)
/* Request to enter the ST system memory bootloader. It lives in .noinit so it
 * survives the reset that carries it, and holds an arbitrary value after a
 * power cycle, which is why it is only trusted after a software reset. A
 * backup register would not do, some series have none. Low half counts
 * attempts. */
static uint32_t bootloaderRequest __attribute__((section(".noinit")));

#define BOOTLOADER_REQUEST_MAGIC 0x5A5A0000
#define BOOTLOADER_REQUEST_MASK  0xFFFF0000

/* The ROM clocks USB from the HSE but does not know which crystal is fitted,
 * so it measures one against the HSI and resets the part when that measurement
 * misses, see AN2606 "HSE detected" -> no -> "Generate System reset". On a
 * 12 MHz STM32F405 a single attempt reached DFU 5 times in 12, so the request
 * survives the reset and is tried again. */
#define BOOTLOADER_MAX_ATTEMPTS 16

/* Where the bootloader's vector table lives, a stack pointer to load followed
 * by an address to jump to. Remapping system memory to 0 keeps this free of
 * per-series addresses. WEAK so a board can point it elsewhere. */
WEAK uint32_t systemBootloaderAddress(void)
{
#ifdef __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH
  /* Remap system Flash memory at address 0x00000000 */
  __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
  return 0;
#else
#error "System memory address unknown for this series"
#endif
}

/* Called from premain(), before init() runs HAL_Init(), so the ROM gets the
 * part close to reset state. It cannot be done from cdc_1200bps_touchHook():
 * that runs in handler mode and the ROM would never leave the exception. */
WEAK void jumpToSystemBootloaderIfRequested(void)
{
  uint32_t request = bootloaderRequest;
  uint32_t attempts = request & ~BOOTLOADER_REQUEST_MASK;
  bool requested = __HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)
                   && ((request & BOOTLOADER_REQUEST_MASK) == BOOTLOADER_REQUEST_MAGIC);

  /* Clear it in every other case, so a power cycle always leaves the
   * bootloader and a completed session does not re-enter it. */
  bootloaderRequest = 0;

  if (!requested || (attempts >= BOOTLOADER_MAX_ATTEMPTS)) {
    return;
  }
  bootloaderRequest = BOOTLOADER_REQUEST_MAGIC | (attempts + 1);
  __HAL_RCC_CLEAR_RESET_FLAGS();

  uint32_t sys = systemBootloaderAddress();

  /* Assembly to prevent modifying the stack pointer after loading it, and to
   * ensure a jump rather than a call. */
  asm volatile(
    "ldr r0, [%[sys], #0]   \n\t"  // get address of stack pointer
    "msr msp, r0            \n\t"  // set stack pointer
    "ldr r0, [%[sys], #4]   \n\t"  // get address of reset handler
    "dsb                    \n\t"  // data sync barrier
    "isb                    \n\t"  // instruction sync barrier
    "bx r0                  \n\t"  // branch to bootloader
    : : [sys] "l"(sys) : "r0"
  );

  __builtin_unreachable();
}

/* Host closed the CDC port at 1200 bps. Record the request and reset; a reset
 * is safe from the control transfer callback where a branch is not. */
void cdc_1200bps_touchHook(void)
{
  bootloaderRequest = BOOTLOADER_REQUEST_MAGIC;
  NVIC_SystemReset();
}
#endif /* BL_SYSTEM */
