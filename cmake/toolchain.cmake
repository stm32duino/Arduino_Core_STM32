
find_program(PYTHON3 "python3")
find_program(SFDP "sfdp") # graphviz layout engine -- you may change the engine, use dot or whatever

include("${CMAKE_CURRENT_LIST_DIR}/ensure_binutils.cmake")

# Setting Linux is forcing th extension to be .o instead of .obj when building on WIndows.
# It is important because armlink is failing when files have .obj extensions (error with
# scatter file section not found)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

set(XPACK_PATH "${CMAKE_CURRENT_LIST_DIR}/../xpack-arm-none-eabi-gcc")
option(AUTODL_XPACK OFF)
ensure_binutils(${XPACK_PATH} ${AUTODL_XPACK})

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY) # don't try to link when testing the compiler, it won't work anyway
set(BUILD_SHARED_LIBS false CACHE STRING "")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

# global compilation options
add_compile_definitions(
	USE_FULL_LL_DRIVER
	ARDUINO=10607
	ARDUINO_ARCH_STM32
)

add_compile_options(
  -mthumb
	--param max-inline-insns-single=500
	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
	-ffunction-sections
	-fdata-sections
)

add_link_options(
  -mthumb
	LINKER:--cref
	LINKER:--check-sections
	LINKER:--gc-sections
	LINKER:--entry=Reset_Handler
	LINKER:--unresolved-symbols=report-all
	LINKER:--warn-common
)
