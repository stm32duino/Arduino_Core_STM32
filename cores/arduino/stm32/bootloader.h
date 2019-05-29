#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

/* Ensure DTR_TOGGLING_SEQ enabled */
#ifdef BL_LEGACY_LEAF
#ifndef DTR_TOGGLING_SEQ
#define DTR_TOGGLING_SEQ
#endif /* DTR_TOGGLING_SEQ */
#endif /* BL_LEGACY_LEAF */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _BOOTLOADER_H_ */
