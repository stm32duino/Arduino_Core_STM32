#define USE_HAL_DRIVER

{% for system in system_list %}
  {% if loop.first %}
#ifdef {{system.serie}}
  {% else %}
#elif {{system.serie}}
  {% endif %}
  #include "{{system.fn}}"
{% endfor %}
#endif

