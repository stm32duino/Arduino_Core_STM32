cmake_minimum_required(VERSION 3.13)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_program(CMAKE_SIZE "arm-none-eabi-size")
find_program(PYTHON3 "python3")
find_program(SFDP "sfdp") # graphviz layout engine -- you may change the engine, use dot or whatever

project("Arduino_Core_STM32" CXX C ASM)

set(BOARD_SERIE "STM32L4xx" CACHE STRING "")
set(BOARD_PRODUCTLINE "STM32L433xx" CACHE STRING "")
set(BOARD_VARIANT "L433RCTxP" CACHE STRING "")
set(BOARD_ID "NUCLEO_L433RC_P" CACHE STRING "")
set(BOARD_MAXSIZE 262144 CACHE STRING "Program space size")
set(BOARD_MAXDATASIZE 65536 CACHE STRING "Dynamic memory size")
set(FLASH_OFFSET 0 CACHE STRING "ld flash offset")

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

set(USB_PID 0 CACHE STRING "")
set(USB_VID 0 CACHE STRING "")

set(USB_PID 0)
set(USB_VID 0)


set(BUILD_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sketch" CACHE STRING "")
set(BUILD_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cores/arduino")
set(BUILD_SYSTEM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/system")
set(BUILD_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(BUILD_CMSIS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMSIS_5/CMSIS") # https://github.com/ARM-software/CMSIS_5.git
set(BUILD_VARIANT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/variants/${BOARD_SERIE}/${BOARD_VARIANT}")


add_library(core_config INTERFACE)

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
		DMETAL_INTERNAL
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
		DMETAL_INTERNAL
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

if (${BUILD_OPT} MATCHES "[0-3gs]")
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
target_compile_definitions(core_config INTERFACE
	"${BOARD_SERIE}"
	"ARDUINO_${BOARD_ID}"
	"BOARD_NAME=\"${BOARD_ID}\""
	"BOARD_ID=${BOARD_ID}"
	"VARIANT_H=\"variant_${BOARD_ID}.h\""
	"${BOARD_PRODUCTLINE}"
)
target_compile_options(core_config INTERFACE
 -mcpu=cortex-m4
 -mfpu=fpv4-sp-d16
 -mfloat-abi=hard
)

target_link_options(core_config INTERFACE
  -mcpu=cortex-m4
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  LINKER:--defsym=LD_FLASH_OFFSET=${FLASH_OFFSET}
	LINKER:--defsym=LD_MAX_SIZE=${BOARD_MAXSIZE}
	LINKER:--defsym=LD_MAX_DATA_SIZE=${BOARD_MAXDATASIZE}
	LINKER:--default-script=${BUILD_VARIANT_PATH}/ldscript.ld
	LINKER:--script=${BUILD_SYSTEM_PATH}/ldscript.ld
)
target_link_directories(core_config INTERFACE
	"${BUILD_CMSIS_PATH}/CMSIS/DSP/Lib/GCC"
)
target_include_directories(core_config INTERFACE
	"${BUILD_SOURCE_PATH}"
	"${BUILD_CORE_PATH}"
	"${BUILD_CORE_PATH}/avr"
	"${BUILD_CORE_PATH}/stm32"
	"${BUILD_CORE_PATH}/stm32/LL"
	"${BUILD_CORE_PATH}/stm32/usb"
	"${BUILD_CORE_PATH}/stm32/OpenAMP"
	"${BUILD_CORE_PATH}/stm32/usb/hid"
	"${BUILD_CORE_PATH}/stm32/usb/cdc"
	"${BUILD_SYSTEM_PATH}/${BOARD_SERIE}"
	"${BUILD_SYSTEM_PATH}/Drivers/${BOARD_SERIE}_HAL_Driver/Inc"
	"${BUILD_SYSTEM_PATH}/Drivers/${BOARD_SERIE}_HAL_Driver/Src"
	"${BUILD_SYSTEM_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc"
	"${BUILD_SYSTEM_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Src"
	"${BUILD_SYSTEM_PATH}/Drivers/CMSIS/Device/ST/${BOARD_SERIE}/Include/"
	"${BUILD_SYSTEM_PATH}/Drivers/CMSIS/Device/ST/${BOARD_SERIE}/Source/Templates/gcc/"
	"${BUILD_CMSIS_PATH}/DSP/Include"
	"${BUILD_CMSIS_PATH}/DSP/PrivateInclude"
	"${BUILD_CMSIS_PATH}/Core/Include/"
	"${BUILD_VARIANT_PATH}"

  "${BUILD_LIB_PATH}/SrcWrapper/src"
)

# propagate config to all the parts of the core
link_libraries(core_config)

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
  SrcWrapper
  $<TARGET_OBJECTS:SrcWrapper>
  core
  variant

  arm_cortexM4lf_math
  m
  stdc++
  c
  gcc
)


include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/handle_sketch.cmake)
