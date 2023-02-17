#ifndef _STM32YYXX_LL_H_
#define _STM32YYXX_LL_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

/* Include Low Layers drivers */
{% for ll_header_name in ll_header_list %}
#include "{{ll_header_name}}"
{% endfor %}
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_H_ */

