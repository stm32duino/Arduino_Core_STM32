# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(SPI INTERFACE)
add_library(SPI_usage INTERFACE)

target_include_directories(SPI_usage INTERFACE
  src
)


target_link_libraries(SPI_usage INTERFACE
  base_config
)

target_link_libraries(SPI INTERFACE SPI_usage)



add_library(SPI_bin OBJECT EXCLUDE_FROM_ALL
  src/SPI.cpp
  src/utility/spi_com.c
)
target_link_libraries(SPI_bin PUBLIC SPI_usage)

target_link_libraries(SPI INTERFACE
  SPI_bin
  $<TARGET_OBJECTS:SPI_bin>
)

