cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(ensure_CMSIS)
include(ensure_ctags)

project("Arduino_Core_STM32" CXX C ASM)


set(FEAT_NANOC ON CACHE BOOL "Use nano libc?")
set(FEAT_FPF OFF CACHE BOOL "nanolibc: enable %f in printf?")
set(FEAT_FSF OFF CACHE BOOL "nanolibc: enable %f in scanf?")
set(FEAT_TIMER ON CACHE BOOL "Timer support")

set(BUILD_OPT "s" CACHE STRING "Optimization level")
set(BUILD_DBG OFF CACHE BOOL "Enable debug symbols")
set(BUILD_LTO OFF CACHE BOOL "Enable Link-Time-Optimisations")
set(BUILD_RELPATH ON CACHE BOOL "make __FILE__ be relative instead of absolute")
set(BUILD_NDEBUG ON CACHE BOOL "define the NDEBUG macro?")


set(BUILD_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cores/arduino")
set(BUILD_SYSTEM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/system")
set(BUILD_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(CMSIS5_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_5" CACHE STRING "Path to CMSIS_5")
set(CTAGS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ctags" CACHE STRING "Folder to find/put ctags in")

option(AUTODL_CMSIS OFF)
option(AUTODL_CTAGS OFF)

ensure_CMSIS(${CMSIS5_PATH} ${AUTODL_CMSIS})
ensure_ctags(${CTAGS_PATH} ${AUTODL_CTAGS})

add_library(base_config INTERFACE)

if(${BUILD_RELPATH})
  # $<TARGET_PROPERTY:SOURCE_DIR> is evaluated by the final consumer, no base_config
  target_compile_options(base_config INTERFACE
    "-fmacro-prefix-map=$<TARGET_PROPERTY:SOURCE_DIR>=."
  )
endif()

if(${BUILD_NDEBUG})
  add_compile_definitions(base_config INTERFACE NDEBUG)
endif()


if (${FEAT_NANOC})
	target_link_options(base_config INTERFACE
		"--specs=nano.specs"
	)
	if (${FEAT_FPF})
		target_link_options(base_config INTERFACE
			"SHELL:-u _printf_float"
		)
	endif()
	if(${FEAT_FSF})
		target_link_options(base_config INTERFACE
			"SHELL:-u _scanf_float"
		)
	endif()
endif()

if (${FEAT_TIMER})
  target_compile_definitions(base_config INTERFACE
    HAL_TIM_MODULE_ENABLE
  )
else ()
  # triggers a user-directed warning
  target_compile_definitions(base_config INTERFACE
    HAL_TIM_MODULE_DISABLED
  )
endif()

if (${BUILD_OPT} MATCHES "^[0-3gs]$")
	target_compile_options(base_config INTERFACE
		-O${BUILD_OPT}
	)
else()
	message(SEND_ERROR "Bad value for BUILD_OPT: got `${BUILD_OPT}`, expected one of 0123gs.")
endif()

if (${BUILD_DBG})
	target_compile_options(base_config INTERFACE
		-g
	)
endif()

if (${BUILD_LTO})
	target_compile_options(base_config INTERFACE
    -flto
  )
	target_link_options(base_config INTERFACE
    -flto
  )
endif()

# generic compilation options
target_link_libraries(base_config INTERFACE board)
target_compile_definitions(base_config INTERFACE
	USE_FULL_LL_DRIVER
	ARDUINO_ARCH_STM32
)
target_compile_options(base_config INTERFACE
  -mthumb
	--param max-inline-insns-single=500
	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
	-ffunction-sections
	-fdata-sections
)

target_link_options(base_config INTERFACE
  -mthumb
  LINKER:--cref
  LINKER:--check-sections
  LINKER:--gc-sections
  LINKER:--entry=Reset_Handler
  LINKER:--unresolved-symbols=report-all
  LINKER:--warn-common
	LINKER:--script=${BUILD_SYSTEM_PATH}/ldscript.ld
)
target_link_directories(base_config INTERFACE
	"${CMSIS5_PATH}/CMSIS/DSP/Lib/GCC"
)
target_include_directories(base_config INTERFACE
	"${BUILD_CORE_PATH}"
	"${BUILD_CORE_PATH}/avr"
	"${BUILD_CORE_PATH}/stm32"
	"${BUILD_CORE_PATH}/stm32/LL"
	"${BUILD_CORE_PATH}/stm32/usb"
	"${BUILD_CORE_PATH}/stm32/OpenAMP"
	"${BUILD_CORE_PATH}/stm32/usb/hid"
	"${BUILD_CORE_PATH}/stm32/usb/cdc"
	"${BUILD_SYSTEM_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc"
	"${BUILD_SYSTEM_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Src"
	"${CMSIS5_PATH}/CMSIS/DSP/Include"
	"${CMSIS5_PATH}/CMSIS/DSP/PrivateInclude"
	"${CMSIS5_PATH}/CMSIS/Core/Include/"
	"${CMSIS5_PATH}/CMSIS"
  "${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP"
  "${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/open-amp/lib/include"
  "${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/libmetal/lib/include"
  "${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/virtual_driver"

  "${BUILD_LIB_PATH}/SrcWrapper/src"
)

add_subdirectory(${BUILD_CORE_PATH})
add_subdirectory(${BUILD_VARIANT_PATH})
add_subdirectory(${BUILD_LIB_PATH})


add_library(stm32_runtime INTERFACE)
target_link_libraries(stm32_runtime INTERFACE
  # note: there may be recursive dependencies between core and SrcWrapper (v. <= 2.2.0)
  # this would require some --Wl,--start-group / -Wl,--end-group
  # but SrcWrapper is an object library, not an archive, so it isn't necessary
  # (this means the linker takes all the object unconditionally, as opposed to an archive where it picks what it needs)
  # note: SrcWrapper in particular MUST be an object library, due to possible weak+strong symbols (cf. library.properties)
  base_config

  SrcWrapper
  core
  variant

  ${CMSIS_LIB}
  m
  stdc++
  c
  gcc
)
