#ifndef __STM32U0xx_HAL_CONF_H
#define __STM32U0xx_HAL_CONF_H

#include "variant.h"

/* STM32U0xx specific HAL configuration options. */
#if __has_include("hal_conf_custom.h")
#include "hal_conf_custom.h"
#else
#if __has_include("hal_conf_extra.h")
#include "hal_conf_extra.h"
#endif
#include "stm32u0xx_hal_conf_default.h"
#endif

#endif /* __STM32U0xx_HAL_CONF_H */