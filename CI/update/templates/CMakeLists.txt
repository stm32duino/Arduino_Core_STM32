{% if precompiled != "full" %}


add_library({{target}}{{" OBJECT" if objlib}} EXCLUDE_FROM_ALL
  {% for file in sources | sort %}
  {{file}}
  {% endfor %}
)

{% if includedirs %}
target_include_directories({{target}} PUBLIC
  {% for dir in  includedirs | sort %}
  {{dir}}
  {% endfor %}
)
{% endif %}

target_link_libraries({{target}} PUBLIC
  core_config
  {% for lib in extra_libs | sort %}
  {{lib}}
  {% endfor %}
)

{% if precompiled == "true" %}
if(EXISTS "{{"${CMAKE_CURRENT_SOURCE_DIR}"}}/src/{{"${"}}MCU{{"}"}}/lib{{target}}.a")
target_link_libraries({{target}} PUBLIC
  "{{"${CMAKE_CURRENT_SOURCE_DIR}"}}/src/{{"${"}}MCU{{"}"}}/lib{{target}}.a"
)
endif()
{% endif %}

{% if ldflags %}
taget_link_options({{target}} PUBLIC
  {{ldflags}}
)
{% endif %}

{% else %} {# precompiled == "full" #}

{#
When precompiled = full, we define 3 targets:
target, target_bin, target_usage
target is the externally usable library
target_bin contains the source files, to be used as fallback
target_usage contains the "transitive usage requirements", i.e., include directories, linker options...

target wraps target_usage and [target_bin or the precompiled library]
target_bin uses target_usage (it's a public interface, i.e. meant for me and my users)
#}

add_library({{target}} INTERFACE)
add_library({{target}}_usage INTERFACE)
add_library({{target}}_bin {{" OBJECT" if objlib}} EXCLUDE_FROM_ALL
{% for file in sources | sort %}
  {{file}}
{% endfor %}
)
target_link_libraries({{target}} INTERFACE {{target}}_usage)
target_link_libraries({{target}}_bin PUBLIC {{target}}_usage)

if(EXISTS "./src/{{"${"}}MCU{{"}"}}/lib{{target}}.a")
  target_link_libraries({{target}} INTERFACE
    "./src/{{"${"}}MCU{{"}"}}/lib{{target}}.a"
  )
else()
  target_link_libraries({{target}} INTERFACE
    {{target}}_bin
    $<TARGET_OBJECTS:{{target}}_bin>
  )
endif()


{% if includedirs %}
target_include_directories({{target}}_usage INTERFACE
  {% for dir in  includedirs | sort %}
  {{dir}}
  {% endfor %}
)
{% endif %}

target_link_libraries({{target}}_usage INTERFACE
  core_config
  {% for lib in extra_libs | sort %}
  {{lib}}
  {% endfor %}
)

{% if ldflags %}
taget_link_options({{target}}_usage INTERFACE
  {{ldflags}}
)
{% endif %}

{% endif %} {# precompiled ?= "full" #}
