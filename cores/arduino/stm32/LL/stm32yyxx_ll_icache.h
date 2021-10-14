#ifndef _STM32YYXX_LL_ICACHE_H_
#define _STM32YYXX_LL_ICACHE_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

#ifdef STM32L5xx
  #include "stm32l5xx_ll_icache.h"
#elif STM32U5xx
  #include "stm32u5xx_ll_icache.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_ICACHE_H_ */
