
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
