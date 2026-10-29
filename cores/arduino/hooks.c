/*
  Copyright (c) 2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdint.h>

/**
 * Empty yield() hook.
 *
 * This function is intended to be used by library writers to build
 * libraries or sketches that supports cooperative threads.
 *
 * Its defined as a weak symbol and it can be redefined to implement a
 * real cooperative scheduler.
 */
static void __empty()
{
  // Empty
}
void yield(void) __attribute__((weak, alias("__empty")));

#ifdef DTR_TOGGLING_SEQ
/**
 * Empty dtr_toggling() hook.
 *
 * This function is intended to be used by library writers to build
 * libraries or sketches that require DTR toggling feature.
 *
 * Its defined as a weak symbol and it can be redefined to implement
 * task to achieve in this case.
 */
static void __empty_dtr_toggling(uint8_t *buf, uint32_t *len)
{
  (void)buf;
  (void)len;
}
void dtr_togglingHook(uint8_t *buf, uint32_t *len) __attribute__((weak, alias("__empty_dtr_toggling")));
#endif

#if defined(USBCON) && defined(USBD_USE_CDC)
/**
 * Empty cdc_1200bps_touch() hook.
 *
 * Called when the host closes the CDC port while the line coding is set to
 * 1200 bps, which is the Arduino convention for asking the board to reboot
 * into its bootloader.
 *
 * Its defined as a weak symbol and it can be redefined to implement the
 * bootloader entry a given board needs.
 *
 * It is called from the USB control transfer callback, so it runs in handler
 * mode. Branching to a bootloader from here leaves the core inside an
 * exception that never returns; schedule the work and perform it from thread
 * mode or after a reset instead.
 */
static void __empty_1200bps_touch(void)
{
}
void cdc_1200bps_touchHook(void) __attribute__((weak, alias("__empty_1200bps_touch")));
#endif /* USBCON && USBD_USE_CDC */
