# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(IWatchdog INTERFACE)
add_library(IWatchdog_usage INTERFACE)

target_include_directories(IWatchdog_usage INTERFACE
  src
)


target_link_libraries(IWatchdog_usage INTERFACE
  base_config
)

target_link_libraries(IWatchdog INTERFACE IWatchdog_usage)



add_library(IWatchdog_bin OBJECT EXCLUDE_FROM_ALL
  src/IWatchdog.cpp
)
target_link_libraries(IWatchdog_bin PUBLIC IWatchdog_usage)

target_link_libraries(IWatchdog INTERFACE
  IWatchdog_bin
  $<TARGET_OBJECTS:IWatchdog_bin>
)

