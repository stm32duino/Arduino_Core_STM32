#ifndef _STM32YYXX_LL_RNG_H_
#define _STM32YYXX_LL_RNG_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

#ifdef STM32F2xx
  #include "stm32f2xx_ll_rng.h"
#elif STM32F4xx
  #include "stm32f4xx_ll_rng.h"
#elif STM32F7xx
  #include "stm32f7xx_ll_rng.h"
#elif STM32G0xx
  #include "stm32g0xx_ll_rng.h"
#elif STM32G4xx
  #include "stm32g4xx_ll_rng.h"
#elif STM32H7xx
  #include "stm32h7xx_ll_rng.h"
#elif STM32L0xx
  #include "stm32l0xx_ll_rng.h"
#elif STM32L4xx
  #include "stm32l4xx_ll_rng.h"
#elif STM32L5xx
  #include "stm32l5xx_ll_rng.h"
#elif STM32U5xx
  #include "stm32u5xx_ll_rng.h"
#elif STM32WBxx
  #include "stm32wbxx_ll_rng.h"
#elif STM32WLxx
  #include "stm32wlxx_ll_rng.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_RNG_H_ */
