#ifndef __STM32H7RSxx_HAL_CONF_H
#define __STM32H7RSxx_HAL_CONF_H

#include "variant.h"

/* STM32H7RSxx specific HAL configuration options. */
#if __has_include("hal_conf_custom.h")
#include "hal_conf_custom.h"
#else
#if __has_include("hal_conf_extra.h")
#include "hal_conf_extra.h"
#endif
#include "stm32h7rsxx_hal_conf_default.h"
#endif

#endif /* __STM32H7RSxx_HAL_CONF_H */