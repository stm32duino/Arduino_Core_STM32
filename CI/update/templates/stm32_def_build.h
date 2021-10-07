#ifndef _STM32_DEF_BUILD_
#define _STM32_DEF_BUILD_

#if !defined(CMSIS_STARTUP_FILE) && !defined(CUSTOM_STARTUP_FILE)
{% for cmsis in cmsis_list %}
  {% if loop.first %}
  #if defined({{ cmsis.vline }})
  {% else %}
  #elif defined({{ cmsis.vline }}){{ " && defined(USE_{}_STARTUP_FILE)".format(cmsis.cm) if cmsis.cm }}
  {% endif %}
    #define CMSIS_STARTUP_FILE "{{ cmsis.fn }}"
{% endfor %}
  #else
    #error UNKNOWN CHIP
  #endif
#else
  #warning "No CMSIS startup file defined, custom one should be used"
#endif /* !CMSIS_STARTUP_FILE && !CUSTOM_STARTUP_FILE */
#endif /* _STM32_DEF_BUILD_ */

