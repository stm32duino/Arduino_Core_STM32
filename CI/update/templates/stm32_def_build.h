/**
 * @file stm32_def_build.h
 * @brief Selects the CMSIS startup file (CMSIS_STARTUP_FILE) matching the STM32 device.
 */
#ifndef _STM32_DEF_BUILD_
#define _STM32_DEF_BUILD_

#if !defined(USE_HALV2_DRIVER) && !defined(CMSIS_STARTUP_FILE) && !defined(CUSTOM_STARTUP_FILE)
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
#endif /* !USE_HALV2_DRIVER && !CMSIS_STARTUP_FILE && !CUSTOM_STARTUP_FILE */
#endif /* _STM32_DEF_BUILD_ */

