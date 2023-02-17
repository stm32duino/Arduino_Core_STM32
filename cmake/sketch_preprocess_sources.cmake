cmake_minimum_required(VERSION 3.21)

function(sketch_preprocess_sources)
  cmake_parse_arguments(PARSE_ARGV 0 SPC "" "OUTPUT_VARIABLE" "SOURCES")
  set(SRCLIST "")
  foreach(SRCFILE IN LISTS SPC_SOURCES)
    if (${SRCFILE} MATCHES "\.ino$")
      cmake_path(GET SRCFILE FILENAME SRC_BASE_NAME)

      configure_file(
        ${SRCFILE}
        ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.cpp
        COPYONLY
      )

      add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.h
        COMMAND ${ARDUINOCTAGS_EXECUTABLE} -u --language-force=c++ -f ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.ctags --c++-kinds=svpf --fields=KSTtzns --line-directives ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.cpp
        COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/generate_header.py -i ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.ctags -o ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.h

        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.cpp
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${SRC_BASE_NAME}.ctags
        VERBATIM
      )

      set_source_files_properties(${SRCFILE}.cpp
        PROPERTIES
        COMPILE_OPTIONS "-include;Arduino.h;-include;${SRCFILE}.h"
        OBJECT_DEPENDS "${SRCFILE}.h"
      )
      list(APPEND SRCLIST ${SRCFILE}.cpp)
    else()
      list(APPEND SRCLIST ${SRCFILE})
    endif()
  endforeach()
  set(${SPC_OUTPUT_VARIABLE} ${SRCLIST} PARENT_SCOPE)
endfunction()
