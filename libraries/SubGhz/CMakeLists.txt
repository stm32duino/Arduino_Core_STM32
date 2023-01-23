# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(SubGhz INTERFACE)
add_library(SubGhz_usage INTERFACE)

target_include_directories(SubGhz_usage INTERFACE
  src
)


target_link_libraries(SubGhz_usage INTERFACE
  base_config
)

target_link_libraries(SubGhz INTERFACE SubGhz_usage)



add_library(SubGhz_bin OBJECT EXCLUDE_FROM_ALL
  src/SubGhz.cpp
)
target_link_libraries(SubGhz_bin PUBLIC SubGhz_usage)

target_link_libraries(SubGhz INTERFACE
  SubGhz_bin
  $<TARGET_OBJECTS:SubGhz_bin>
)

