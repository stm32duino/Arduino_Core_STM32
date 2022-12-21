cmake_minimum_required(VERSION 3.21)

include(sketch_preprocess_sources)
include(convert_file)

include(set_base_arduino_config)

function(build_sketch)
  add_subdirectory(${BUILD_VARIANT_PATH} ./variant)
  add_subdirectory(${BUILD_CORE_PATH} ./cores/arduino)
  add_subdirectory(${BUILD_LIB_PATH} ./libraries)


  cmake_parse_arguments(PARSE_ARGV 0 SKBD "" "TARGET" "SOURCES;DEPENDS")

  if(DEFINED SKBD_UNPARSED_ARGUMENTS OR DEFINED SKBD_KEYWORDS_MISSING_VALUES)
    message(SEND_ERROR "Invalid call to build_sketch(); some arguments went unparsed")
  endif()

  if(NOT DEFINED SKBD_TARGET)
    message(SEND_ERROR "Invalid call to build_sketch(); please specify a TARGET")
    return()
  elseif(NOT DEFINED SKBD_SOURCES)
    message(SEND_ERROR "Invalid call to build_sketch(); please specify some SOURCES")
    return()
  endif()

  add_executable(${SKBD_TARGET})
  target_include_directories(base_config BEFORE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

  foreach(SRCS IN LISTS SKBD_SOURCES)
    sketch_preprocess_sources(OUTPUT_VARIABLE SRCS SOURCES ${SRCS})
    target_sources(${SKBD_TARGET} PRIVATE ${SRCS})
  endforeach()

  target_link_libraries(${SKBD_TARGET} PRIVATE stm32_runtime)
  if(DEFINED SKBD_DEPENDS)
    target_link_libraries(${SKBD_TARGET} PRIVATE ${SKBD_DEPENDS})
  endif()

  get_target_property(OUTDIR ${SKBD_TARGET} BINARY_DIR)
  set(MAPFILE ${OUTDIR}/${SKBD_TARGET}.map)

  target_link_options(${SKBD_TARGET} PRIVATE
    LINKER:-Map,${MAPFILE}
  )

  # this is here to make CMake et al. aware that the map file
  # is generated along with the binary
  add_custom_command(TARGET ${SKBD_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E true # essentially a no-op
    BYPRODUCTS ${MAPFILE}
  )

  if(EXISTS ${Python3_EXECUTABLE})
    add_custom_command(TARGET ${SKBD_TARGET} POST_BUILD
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/sizereport.py -x ${CMAKE_SIZE} -f $<TARGET_FILE:${SKBD_TARGET}> --progmem ${BOARD_MAXSIZE} --datamem ${BOARD_MAXDATASIZE}
    )
  else() #  STREQUAL "PYTHON3-NOTFOUND"
    message(WARNING "python3 not found; the final size report will not be displayed")
  endif()

  elf2bin(${SKBD_TARGET})
  elf2hex(${SKBD_TARGET})
endfunction()
