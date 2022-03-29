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
#if defined(ARDUINO_GENERIC_{{generic_list[0].board}}){% for name in generic_list[1:] %} || defined(ARDUINO_GENERIC_{{name.board}}){% endfor %}

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
{% for pinname in pinnames_list %}
{% if not loop.last %}
  {{"%-7s // %s"|format("{},".format(pinname.name), "D{}{}".format(loop.index-1, "" if pinname.ax == -1 else "/A{}".format(pinname.ax)))}}
{% else %}
  {{"%-7s // %s"|format(pinname.name, "D{}{}".format(loop.index-1, "" if pinname.ax == -1 else "/A{}".format(pinname.ax)))}}
{% endif %}
{% endfor %}
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
{% for analog_pin in analog_pins_list %}
{% if not loop.last %}
  {{"%-3s // %-4s %s"|format("{},".format(analog_pin.val), "{},".format(analog_pin.ax), analog_pin.pyn)}}
{% else %}
  {{"%-3s // %-4s %s"|format(analog_pin.val, "{},".format(analog_pin.ax), analog_pin.pyn)}}
{% endif %}
{% endfor %}
};

#endif /* ARDUINO_GENERIC_* */

