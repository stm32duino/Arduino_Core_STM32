
add_library({{ target }}{{" OBJECT" if objlib}} EXCLUDE_FROM_ALL
  {% for file in sources %}
  {{ file }}
  {% endfor %}
)

{% if includedir %}
target_include_directories({{ target }} PUBLIC
  {{ includedir }}
)
{% endif %}

target_link_libraries({{ target }} PUBLIC
  core_config
  {% for lib in extra_libs%}
  {{ lib }}
  {% endfor %}
)
