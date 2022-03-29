/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
/*
 * Automatically generated from {{mcu_file}}
 * CubeMX DB release {{db_release}}
 */
#if !defined(CUSTOM_PERIPHERAL_PINS)
#include "Arduino.h"
#include "PeripheralPins.h"

/* =====
 * Notes:
 * - The pins mentioned Px_y_ALTz are alternative possibilities which use other
 *   HW peripheral instances. You can use them the same way as any other "normal"
 *   pin (i.e. analogWrite(PA7_ALT1, 128);).
 *
 * - Commented lines are alternative possibilities which are not used per default.
 *   If you change them, you will have to know what you do
 * =====
 */
{% if peripherals_list %}
  {% for peripheral_list in peripherals_list %}
    {% for periph in peripheral_list %}
      {% if periph.list %}
        {% if loop.first %}

//*** {{periph.name}} ***
        {% endif %}

        {% if periph.hal is iterable and periph.hal is not string %}
#if defined(HAL_{{periph.hal[0]}}_MODULE_ENABLED){% for hal in periph.hal[1:] %} || defined(HAL_{{hal}}_MODULE_ENABLED){% endfor %}

        {% else %}
#ifdef HAL_{{periph.hal}}_MODULE_ENABLED
        {% endif %}
WEAK const PinMap PinMap_{{periph.aname}}[] = {
        {% for pm in periph.list %}
          {% if pm.hsinfs %}
            {%if pm.hsinfs == 1 %}
#ifdef USE_USB_HS_IN_FS
            {% elif pm.hsinfs == 2 %}
#else
            {% endif %}
          {% endif %}
          {% if periph.data %}
  {{"{"}}{{"%s %s"|format("{},".format(pm.pin).ljust(periph.wpin), "{},".format(pm.inst).ljust(periph.winst))}} STM_PIN_DATA_EXT({{pm.mode}}, {{pm.pull}}, {{pm.af}}, {{pm.chan}}, {{pm.inv}}){{"}"}},{{" // {}".format(pm.cmt) if pm.cmt}}
          {% else %}
  {{"{"}}{{"%s %s"|format("{},".format(pm.pin).ljust(periph.wpin), "{},".format(pm.inst).ljust(periph.winst))}} STM_PIN_DATA({{pm.mode}}, {{pm.pull}}, {{pm.af}}){{"}"}},{{" // {}".format(pm.cmt) if pm.cmt}}
          {% endif %}
          {% if loop.last %}
          {% if pm.hsinfs and pm.hsinfs == 3 %}
#endif /* USE_USB_HS_IN_FS */
          {% endif %}
  {{"{"}}{{"%s %s"|format("{},".format("NC").ljust(periph.wpin), "{},".format("NP").ljust(periph.winst))}} 0{{"}"}}
          {% endif %}
        {% endfor %}
};
#endif
      {% elif loop.first %}

//*** No {{periph.name}} ***
      {% endif %}
    {% endfor %}
  {% endfor %}
{% endif %}

#endif /* !CUSTOM_PERIPHERAL_PINS */

