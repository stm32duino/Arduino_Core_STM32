#ifndef _STM32YYXX_LL_PKA_H_
#define _STM32YYXX_LL_PKA_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

#ifdef STM32L4xx
  #include "stm32l4xx_ll_pka.h"
#elif STM32L5xx
  #include "stm32l5xx_ll_pka.h"
#elif STM32U5xx
  #include "stm32u5xx_ll_pka.h"
#elif STM32WBxx
  #include "stm32wbxx_ll_pka.h"
#elif STM32WLxx
  #include "stm32wlxx_ll_pka.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_PKA_H_ */
