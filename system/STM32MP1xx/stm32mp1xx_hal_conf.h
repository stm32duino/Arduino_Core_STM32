#ifndef __STM32MP1xx_HAL_CONF_H
#define __STM32MP1xx_HAL_CONF_H

#include "variant.h"

/* STM32MP1xx specific HAL configuration options. */
#if __has_include("hal_conf_custom.h")
#include "hal_conf_custom.h"
#else
#if __has_include("hal_conf_extra.h")
#include "hal_conf_extra.h"
#endif
#include "stm32mp1xx_hal_conf_default.h"
#endif

#endif /* __STM32MP1xx_HAL_CONF_H */
