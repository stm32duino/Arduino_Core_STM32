{% if dualpad_pins_list %}
/* Dual pad pin name */
  {% for dp in dualpad_pins_list %}
{{"%s = %s | PDUAL,"|format(dp.name.ljust(waltpin), dp.base.ljust(waltpin-5))}}
  {% endfor %}

{% endif %}
{% if remap_pins_list %}
/* Remap pin name */
  {% for dp in remap_pins_list %}
{{"%s = %s | PREMAP,"|format(dp.name.ljust(waltpin), dp.base.ljust(waltpin-5))}}
  {% endfor %}

{% endif %}
{% if alt_pins_list %}
/* Alternate pin name */
  {% for alt in alt_pins_list %}
{{"%s = %s | %s,"|format(alt.name.ljust(waltpin), alt.base.ljust(waltpin-5), alt.num)}}
  {% endfor %}
{% else %}
/* No alternate */
{% endif %}

{% if syswkup_pins_list %}
/* SYS_WKUP */
  {% for syswkup_list in syswkup_pins_list %}
    {% set outer_loop = loop %}
    {% if syswkup_list %}
      {% for syswkup in syswkup_list %}
#ifdef PWR_WAKEUP_PIN{{outer_loop.index}}
  SYS_WKUP{{outer_loop.index}}{{"_{}".format(loop.index - 1) if loop.index > 1}} = {{syswkup[0]}},{{syswkup[1]}}
#endif
      {% endfor %}
    {% else %}
#ifdef PWR_WAKEUP_PIN{{loop.index}}
  SYS_WKUP{{loop.index}} = NC,
#endif
    {% endif %}
  {% endfor %}
{% else %}
/* No SYS_WKUP */
{% endif %}

{% if usb_pins_list %}
/* USB */
#ifdef USBCON
{% for usb in usb_pins_list %}
  {% if (loop.previtem and loop.previtem.name == usb.name) or (loop.nextitem and loop.nextitem.name == usb.name) %}
  #ifdef {{usb.name}}_{{usb.pn}}
    {{"%s = %s,"|format(usb.name.ljust(wusbpin), usb.pn)}}
  #endif
  {% else %}
  {{"%s = %s,"|format(usb.name.ljust(wusbpin), usb.pn)}}
  {% endif %}
{% endfor %}
#endif
{% else %}
/* No USB */
{% endif %}

