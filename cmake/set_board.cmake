
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

function(set_board BOARD_ID)
  include(boards_db)

  if (NOT TARGET ${BOARD_ID})
    message(SEND_ERROR "Board ${BOARD_ID} not found. Maybe the board database is not up-to-date?")
    return()
  endif()
  add_library(board ALIAS ${BOARD_ID})
  set(BUILD_VARIANT_PATH ${${BOARD_ID}_VARIANT_PATH} CACHE STRING "" FORCE)
  set(BOARD_MAXSIZE ${${BOARD_ID}_MAXSIZE} CACHE STRING "" FORCE)
  set(BOARD_MAXDATASIZE ${${BOARD_ID}_MAXDATASIZE} CACHE STRING "" FORCE)
  set(MCU ${${BOARD_ID}_MCU} CACHE STRING "" FORCE)
endfunction()
