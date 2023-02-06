#ifndef _STM32YYXX_LL_HRTIM_H_
#define _STM32YYXX_LL_HRTIM_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

#ifdef STM32F3xx
  #include "stm32f3xx_ll_hrtim.h"
#elif STM32G4xx
  #include "stm32g4xx_ll_hrtim.h"
#elif STM32H7xx
  #include "stm32h7xx_ll_hrtim.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_HRTIM_H_ */
