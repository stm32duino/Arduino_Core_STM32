#ifndef _STM32YYXX_LL_{{periph.upper()}}_H_
#define _STM32YYXX_LL_{{periph.upper()}}_H_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wregister"
#endif

{% for serie, nx in serieslist %}
  {% if loop.first %}
#ifdef STM32{{serie.upper()}}{{nx}}
  {% else %}
#elif STM32{{serie.upper()}}{{nx}}
  {% endif %}
  #include "stm32{{serie}}{{nx}}_ll_{{periph}}.h"
  {% if loop.last %}
#endif
  {% endif %}
{% endfor %}
#pragma GCC diagnostic pop
#endif /* _STM32YYXX_LL_{{periph.upper()}}_H_ */

