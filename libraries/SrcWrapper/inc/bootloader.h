#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

#include <stdint.h>

/* Ensure DTR_TOGGLING_SEQ enabled */
#if defined(BL_LEGACY_LEAF) || defined(BL_HID)
  #ifndef DTR_TOGGLING_SEQ
    #define DTR_TOGGLING_SEQ
  #endif /* DTR_TOGGLING_SEQ || BL_HID */
#endif /* BL_LEGACY_LEAF */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(BL_SYSTEM)
uint32_t systemBootloaderAddress(void);
void jumpToSystemBootloaderIfRequested(void);
#endif /* BL_SYSTEM */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _BOOTLOADER_H_ */
