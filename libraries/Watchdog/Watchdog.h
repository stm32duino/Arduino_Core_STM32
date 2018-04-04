#ifndef __WATCHDOG_STM32_H__
#define __WATCHDOG_STM32_H__

#include "Arduino.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * To enable the IWDG HAL component used by this library you must add a
 * file named build_opt.h to your sketch with the following content:
 * 
 * -DHAL_IWDG_MODULE_ENABLED
 * 
 * Include the dash (-) in front of DHAL_IWDG_MODULE_ENABLED
 */

/*
 * The watchdog_init function would initialize the IWDG hardware block.
 * 
 * The timeout_ms parameter would set the timer reset timeout. When the
 * timer reaches zero the hardware block would generate a reset signal
 * for the CPU.
 * 
 * When specifying timeout value plan to refresh the timer at least twice
 * as often. The reset operation is not very expensive.
 * 
 * The downside of slecting a very large timeout value is that your system
 * may be left in a "stuck" state for too long, before the reset is
 * generated.
 * 
 * Valid timeout values are between 1ms and 32,768ms (~32.8 seconds). For
 * values above 4095 the timeout paramater starts to loose precision:
 * 
 * timeout value range | timeout value precision
 * 00001-04096         | 1ms
 * 04097-08192         | 2ms
 * 08193-16384         | 4ms
 * 16385-32768         | 8ms
 * 
 * Calling the watchdog_init method with value outside of the valid range
 * would return without initializing the watchdog timer.
 * 
 * WARNING: Once started the watchdog timer can not be stopped. If you are
 * planning to debug the live system, the watchdog timer may cause the
 * system to be reset while you are stopped in the debugger. Also consider
 * the watchdog timer implications if you are designing a system which puts
 * the CPU in sleep mode.
 * 
 */
void watchdog_init(uint16_t timeout_ms);

/*
 * The watchdog_reset() function would reset the watchdog timer. Once you
 * have initialized the watchdog you HAVE to call watchdog_reset()
 * periodically to prevent the CPU being reset.
 */
void watchdog_reset();

#ifdef __cplusplus
}
#endif

#endif // __WATCHDOG_STM32_H__
