cmake_minimum_required(VERSION 3.21)
set(CORE_PATH ${CMAKE_CURRENT_LIST_DIR}/..)
set(SCRIPTS_FOLDER ${CORE_PATH}/scripts)

function(updatedb)
  set(BOARDS_TXT ${CORE_PATH}/boards.txt)
  set(PLATFORM_TXT ${CORE_PATH}/platform.txt)
  set(TEMPLATE ${CORE_PATH}/CI/update/templates/boards_db.cmake)
  set(DB ${CORE_PATH}/cmake/boards_db.cmake)

  set_directory_properties(PROPERTIES
    CMAKE_CONFIGURE_DEPENDS "${BOARDS_TXT};${PLATFORM_TXT};${TEMPLATE}"
  )

  if(${BOARDS_TXT} IS_NEWER_THAN ${DB} OR ${TEMPLATE} IS_NEWER_THAN ${DB})
    execute_process(
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/parse_boards.py
      -b ${BOARDS_TXT} -p ${PLATFORM_TXT} -t ${TEMPLATE} -o ${DB}
      # COMMAND_ERROR_IS_FATAL ANY # requires VERSION 3.19
    )
  endif()
endfunction()
