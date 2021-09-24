#ifndef _STM32YYXX_LL_CRS_H_
#define _STM32YYXX_LL_CRS_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

#ifdef STM32F0xx
  #include "stm32f0xx_ll_crs.h"
#elif STM32G0xx
  #include "stm32g0xx_ll_crs.h"
#elif STM32G4xx
  #include "stm32g4xx_ll_crs.h"
#elif STM32H7xx
  #include "stm32h7xx_ll_crs.h"
#elif STM32L0xx
  #include "stm32l0xx_ll_crs.h"
#elif STM32L4xx
  #include "stm32l4xx_ll_crs.h"
#elif STM32L5xx
  #include "stm32l5xx_ll_crs.h"
#elif STM32U5xx
  #include "stm32u5xx_ll_crs.h"
#elif STM32WBxx
  #include "stm32wbxx_ll_crs.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_CRS_H_ */
