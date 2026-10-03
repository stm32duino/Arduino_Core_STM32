#ifndef _STM32YYXX_UTILS_I3C_H_
#define _STM32YYXX_UTILS_I3C_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

#ifdef STM32C5xx
  #include "stm32_utils_i3c.h"
#elif STM32H5xx
  #include "stm32h5xx_util_i3c.h"
#elif STM32H7RSxx
  #include "stm32h7rsxx_util_i3c.h"
#elif STM32U3xx
  #include "stm32u3xx_util_i3c.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_UTILS_I3C_H_ */
