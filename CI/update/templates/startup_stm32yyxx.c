/**
 * @file startup_stm32yyxx.c
 * @brief Includes the CMSIS startup file of the selected device when using the
 * HAL v2 driver.
 */
#ifndef _STARTUP_STM32YYXX_C_
#define _STARTUP_STM32YYXX_C_

#if defined(USE_HALV2_DRIVER)
{% for cmsis in cmsis_list %}
  {% if loop.first %}
  #if defined({{ cmsis.vline }})
  {% else %}
  #elif defined({{ cmsis.vline }}){{ " && defined(USE_{}_STARTUP_FILE)".format(cmsis.cm) if cmsis.cm }}
  {% endif %}
    #include "{{ cmsis.fn }}"
{% endfor %}
  #else
    #if !defined(CUSTOM_STARTUP_FILE)
      #error "No CMSIS startup file defined, custom one should be used"
    #else
      #include CUSTOM_STARTUP_FILE
    #endif
  #endif
#endif /* USE_HALV2_DRIVER */
#endif /* _STARTUP_STM32YYXX_C_ */
