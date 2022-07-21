# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library({{target}} INTERFACE)
add_library({{target}}_usage INTERFACE)

{% if includedirs %}
target_include_directories({{target}}_usage INTERFACE
  {% for dir in  includedirs | sort %}
  {{dir}}
  {% endfor %}
)
{% endif %}

{% if ldflags %}
target_link_options({{target}}_usage INTERFACE
  {{ldflags}}
)
{% endif %}

target_link_libraries({{target}}_usage INTERFACE
  base_config
  {% for lib in extra_libs | sort %}
  {{lib}}
  {% endfor %}
)

target_link_libraries({{target}} INTERFACE {{target}}_usage)


{% if precompiled in ("true", "full") %}
set({{target}}_PRECOMPILED false)
{% for config, libs in binaries | dictsort | reverse %}
{{"if" if loop.first else "elseif"}} ("${MCU}${FPCONF}" STREQUAL "{{config}}")
  target_link_libraries({{target}}_usage INTERFACE
    {% for lib in libs %}
    "{{"${CMAKE_CURRENT_SOURCE_DIR}/"}}{{lib}}"
    {% endfor %}
  )
  set({{target}}_PRECOMPILED true)
{{"endif()" if loop.last}}
{% endfor %}
{% endif %}

{% if sources %}
add_library({{target}}_bin {{"OBJECT" if objlib else "STATIC"}} EXCLUDE_FROM_ALL
  {% for file in sources | sort %}
  {{file}}
  {% endfor %}
)
target_link_libraries({{target}}_bin PUBLIC {{target}}_usage)

{% if precompiled == "full" %}
if(NOT {{"${"}}{{target}}_PRECOMPILED{{"}"}})
{% endif %}
target_link_libraries({{target}} INTERFACE
  {{target}}_bin
  {% if objlib %}
  $<TARGET_OBJECTS:{{target}}_bin>
  {% endif %}
)
{% if precompiled == "full" %}
endif()
{% endif %}

{% endif %}
