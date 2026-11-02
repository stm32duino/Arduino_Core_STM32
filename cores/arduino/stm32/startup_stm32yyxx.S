/**
 * @file startup_stm32yyxx.S
 * @brief Includes the CMSIS startup file (CMSIS_STARTUP_FILE) of the selected
 * device when using the HAL v1 driver.
 */
#if !defined(USE_HALV2_DRIVER)
#include "stm32_def_build.h"

#if defined(CMSIS_STARTUP_FILE)
#include CMSIS_STARTUP_FILE
#endif
#endif /* !USE_HALV2_DRIVER */
