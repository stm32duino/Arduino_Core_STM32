#ifndef _STM32YYXX_LL_UCPD_H_
#define _STM32YYXX_LL_UCPD_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

#ifdef STM32G0xx
  #include "stm32g0xx_ll_ucpd.h"
#elif STM32G4xx
  #include "stm32g4xx_ll_ucpd.h"
#elif STM32L5xx
  #include "stm32l5xx_ll_ucpd.h"
#elif STM32U5xx
  #include "stm32u5xx_ll_ucpd.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_UCPD_H_ */
