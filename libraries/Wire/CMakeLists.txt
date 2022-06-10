
add_library(Wire OBJECT EXCLUDE_FROM_ALL
  src/Wire.cpp
  src/utility/twi.c
)

target_include_directories(Wire PUBLIC
  src
)

target_link_libraries(Wire PUBLIC
  core_config
)