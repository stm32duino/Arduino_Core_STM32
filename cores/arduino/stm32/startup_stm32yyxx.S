#include "stm32_def_build.h"

#if defined(CMSIS_STARTUP_FILE)
#include CMSIS_STARTUP_FILE
#endif

# Expose Reset_Handler under a different name, to allow overriding it
# with a strong symbol and then calling the original.
.global Original_Reset_Handler
.thumb_set Original_Reset_Handler,Reset_Handler
