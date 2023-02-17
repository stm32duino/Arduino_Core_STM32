#ifndef _STM32YYXX_LL_HSEM_H_
#define _STM32YYXX_LL_HSEM_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

#ifdef STM32H7xx
  #include "stm32h7xx_ll_hsem.h"
#elif STM32MP1xx
  #include "stm32mp1xx_ll_hsem.h"
#elif STM32WBxx
  #include "stm32wbxx_ll_hsem.h"
#elif STM32WLxx
  #include "stm32wlxx_ll_hsem.h"
#endif
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_HSEM_H_ */
