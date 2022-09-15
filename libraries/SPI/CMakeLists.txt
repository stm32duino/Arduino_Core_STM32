
add_library(SPI OBJECT EXCLUDE_FROM_ALL
  src/SPI.cpp
  src/utility/spi_com.c
)

target_include_directories(SPI PUBLIC
  src
)
