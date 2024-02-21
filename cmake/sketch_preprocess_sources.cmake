cmake_minimum_required(VERSION 3.21)

function(sketch_preprocess_sources)
  cmake_parse_arguments(PARSE_ARGV 0 SPC "" "OUTPUT_VARIABLE" "SOURCES")
  set(SRCLIST "")
  foreach(SRCFILE IN LISTS SPC_SOURCES)
    if (${SRCFILE} MATCHES "\.ino$")
      # Convert <file>.ino to ${CMAKE_CURRENT_BINARY_DIR}/<file>.ino.{cpp,h}
      cmake_path(GET SRCFILE FILENAME SRC_BASE_NAME)
      set(SRC_BINARY_BASE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME})

      configure_file(
        ${SRCFILE}
        ${SRC_BINARY_BASE_NAME}.cpp
        COPYONLY
      )

      add_custom_command(OUTPUT ${SRC_BINARY_BASE_NAME}.h
        COMMAND ${ARDUINOCTAGS_EXECUTABLE} -u --language-force=c++ -f ${SRC_BINARY_BASE_NAME}.ctags --c++-kinds=svpf --fields=KSTtzns --line-directives ${SRC_BINARY_BASE_NAME}.cpp
        COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/generate_header.py -i ${SRC_BINARY_BASE_NAME}.ctags -o ${SRC_BINARY_BASE_NAME}.h

        DEPENDS ${SRC_BINARY_BASE_NAME}.cpp
        BYPRODUCTS ${SRC_BINARY_BASE_NAME}.ctags
        VERBATIM
      )

      set_source_files_properties(${SRC_BINARY_BASE_NAME}.cpp
        PROPERTIES
        COMPILE_OPTIONS "-include;Arduino.h;-include;${SRC_BINARY_BASE_NAME}.h"
        OBJECT_DEPENDS ${SRC_BINARY_BASE_NAME}.h
      )
      list(APPEND SRCLIST ${SRC_BINARY_BASE_NAME}.cpp)
    else()
      list(APPEND SRCLIST ${SRCFILE})
    endif()
  endforeach()
  set(${SPC_OUTPUT_VARIABLE} ${SRCLIST} PARENT_SCOPE)
endfunction()
