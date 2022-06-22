cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(ensure_CMSIS)

project("Arduino_Core_STM32" CXX C ASM)


set(FEAT_XSERIAL "GENERIC" CACHE STRING "USART support")
set(FEAT_USB "NONE" CACHE STRING "USB support")
set(FEAT_XUSB "FS" CACHE STRING "USB speed")
set(FEAT_NANOC ON CACHE BOOL "Use nano libc?")
set(FEAT_FPF OFF CACHE BOOL "nanolibc: enable %f in printf?")
set(FEAT_FSF OFF CACHE BOOL "nanolibc: enable %f in scanf?")
set(FEAT_VIRTIO "DISABLED" CACHE STRING "Virtual serial support")
set(FEAT_TIMER ON CACHE BOOL "Timer support")

set(BUILD_OPT "s" CACHE STRING "Optimization level")
set(BUILD_DBG OFF CACHE BOOL "Enable debug symbols")
set(BUILD_LTO OFF CACHE BOOL "Enable Link-Time-Optimisations")
set(BUILD_RELPATH ON CACHE BOOL "make __FILE__ be relative instead of absolute")
set(BUILD_NDEBUG ON CACHE BOOL "define the NDEBUG macro?")

set(USB_PID 0)
set(USB_VID 0)


set(BUILD_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cores/arduino")
set(BUILD_SYSTEM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/system")
set(BUILD_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(CMSIS5_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_5" CACHE STRING "Path to CMSIS_5")

option(AUTODL_CMSIS OFF)
ensure_CMSIS(${CMSIS5_PATH} ${AUTODL_CMSIS})

add_library(core_config INTERFACE)

if(${BUILD_RELPATH})
  # $<TARGET_PROPERTY:SOURCE_DIR> is evaluated by the final consumer, no core_config
  target_compile_options(core_config INTERFACE
    "-fmacro-prefix-map=$<TARGET_PROPERTY:SOURCE_DIR>=."
  )
endif()

if(${BUILD_NDEBUG})
  add_compile_definitions(core_config INTERFACE NDEBUG)
endif()

# configuration specifics
if (${FEAT_XSERIAL} STREQUAL "GENERIC")
	target_compile_definitions(core_config INTERFACE
		HAL_UART_MODULE_ENABLED
	)
elseif (${FEAT_XSERIAL} STREQUAL "NONE")
	target_compile_definitions(core_config INTERFACE
		HAL_UART_MODULE_ENABLED
		HWSERIAL_NONE
	)
elseif (${FEAT_XSERIAL} STREQUAL "DISABLED")
	# nothing
else()
	message(SEND_ERROR "Bad value for FEAT_XSERIAL: got `${FEAT_XSERIAL}`, expected GENERIC, NONE or DISABLED.")
endif()

# define USB_SPEED
if (${FEAT_XUSB} STREQUAL "FS")
	set(USB_SPEED "")
elseif (${FEAT_XUSB} STREQUAL "HS")
	set(USB_SPEED "USE_USB_HS")
elseif (${FEAT_XUSB} STREQUAL "HSFS")
	set(USB_SPEED "USE_USB_HS;USE_USB_HS_IN_FS")
else()
	message(SEND_ERROR "Bad value for FEAT_XUSB: got `${FEAT_XUSB}`, expected FS, HS or HSFS.")
endif()

# consume USB_SPEED
if (${FEAT_USB} STREQUAL "NONE")
	#nothing
elseif (${FEAT_USB} STREQUAL "CDCGEN")
	target_compile_definitions(core_config INTERFACE
		USBCON
		${USB_SPEED}
		USBD_VID=${USB_VID}
		USBD_PID=${USB_PID}
		HAL_PCD_MODULE_ENABLED
		USBD_USE_CDC
	)
elseif (${FEAT_USB} STREQUAL "CDC")
	target_compile_definitions(core_config INTERFACE
		USBCON
		${USB_SPEED}
		USBD_VID=${USB_VID}
		USBD_PID=${USB_PID}
		HAL_PCD_MODULE_ENABLED
		USBD_USE_CDC
		DISABLE_GENERIC_SERIALUSB
	)
elseif (${FEAT_USB} STREQUAL "HID")
	target_compile_definitions(core_config INTERFACE
		USBCON
		${USB_SPEED}
		USBD_VID=${USB_VID}
		USBD_PID=${USB_PID}
		HAL_PCD_MODULE_ENABLED
		USBD_USE_HID_COMPOSITE
	)
else()
	message(SEND_ERROR "Bad value for FEAT_USB: got `${FEAT_USB}`, expected NONE, CDCGEN, CDC or HID.")
endif()

if (${FEAT_NANOC})
	target_link_options(core_config INTERFACE
		"--specs=nano.specs"
	)
	if (${FEAT_FPF})
		target_link_options(core_config INTERFACE
			"SHELL:-u _printf_float"
		)
	endif()
	if(${FEAT_FSF})
		target_link_options(core_config INTERFACE
			"SHELL:-u _scanf_float"
		)
	endif()
endif()

if (${FEAT_VIRTIO} STREQUAL "DISABLED")
	# nothing
elseif (${FEAT_VIRTIO} STREQUAL "GENERIC")
	target_compile_definitions(core_config INTERFACE
		VIRTIOCON
		NO_ATOMIC_64_SUPPORT
		METAL_INTERNAL
		METAL_MAX_DEVICE_REGIONS=2
		VIRTIO_SLAVE_ONLY
		VIRTIO_LOG
	)
	target_include_directories(core_config INTERFACE
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/open-amp/lib/include
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/libmetal/lib/include
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/virtual_driver
	)
elseif (${FEAT_VIRTIO} STREQUAL "ENABLED")
	target_compile_definitions(core_config INTERFACE
		VIRTIOCON
		NO_ATOMIC_64_SUPPORT
		METAL_INTERNAL
		METAL_MAX_DEVICE_REGIONS=2
		VIRTIO_SLAVE_ONLY
		VIRTIO_LOG
		DISABLE_GENERIC_SERIALVIRTIO
	)
	target_include_directories(core_config INTERFACE
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/open-amp/lib/include
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/libmetal/lib/include
		${BUILD_SYSTEM_PATH}/Middlewares/OpenAMP/virtual_driver
	)
else()
	message(SEND_ERROR "Bad value for FEAT_VIRTIO: got `${FEAT_VIRTIO}`, expected DISABLED, GENERIC or ENABLED.")
endif()

if (${FEAT_TIMER})
  target_compile_definitions(core_config INTERFACE
    HAL_TIM_MODULE_ENABLE
  )
else ()
  # triggers a user-directed warning
  target_compile_definitions(core_config INTERFACE
    HAL_TIM_MODULE_DISABLED
  )
endif()

if (${BUILD_OPT} MATCHES "^[0-3gs]$")
	target_compile_options(core_config INTERFACE
		-O${BUILD_OPT}
	)
else()
	message(SEND_ERROR "Bad value for BUILD_OPT: got `${BUILD_OPT}`, expected one of 0123gs.")
endif()

if (${BUILD_DBG})
	target_compile_options(core_config INTERFACE
		-g
	)
endif()

if (${BUILD_LTO})
	target_compile_options(core_config INTERFACE
    -flto
  )
	target_link_options(core_config INTERFACE
    -flto
  )
endif()

# generic compilation options
target_link_libraries(core_config INTERFACE board)
target_link_options(core_config INTERFACE
	LINKER:--script=${BUILD_SYSTEM_PATH}/ldscript.ld
)
target_link_directories(core_config INTERFACE
	"${CMSIS5_PATH}/CMSIS/DSP/Lib/GCC"
)
target_include_directories(core_config INTERFACE
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
  core_config

  SrcWrapper
  $<TARGET_OBJECTS:SrcWrapper>
  core
  variant

  ${CMSIS_LIB}
  m
  stdc++
  c
  gcc
)
