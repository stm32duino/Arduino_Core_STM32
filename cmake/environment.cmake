cmake_minimum_required(VERSION 3.21)

string(MD5 PATH_HASH "${CMAKE_CURRENT_LIST_FILE}")

file(REAL_PATH "${CMAKE_CURRENT_LIST_DIR}/.." CORE_PATH)
file(REAL_PATH "${CORE_PATH}/cores/arduino" BUILD_CORE_PATH)
file(REAL_PATH "${CORE_PATH}/system" BUILD_SYSTEM_PATH)
file(REAL_PATH "${CORE_PATH}/libraries" BUILD_LIB_PATH)
file(REAL_PATH "~/.Arduino_Core_STM32_dl/${PATH_HASH}" DL_DIR EXPAND_TILDE)
file(REAL_PATH "${CORE_PATH}/platform.txt" PLATFORMTXT_PATH)
file(REAL_PATH "${CORE_PATH}/boards.txt" BOARDSTXT_PATH)
file(REAL_PATH "${CORE_PATH}/cmake/scripts" SCRIPTS_FOLDER)
file(REAL_PATH "${CORE_PATH}/cmake/templates/boards_db.cmake" CMAKE_BOARDS_DB_TEMPLATE_PATH)
file(REAL_PATH "${CORE_PATH}/cmake/boards_db.cmake" CMAKE_BOARDS_DB_PATH)

set(JSONCONFIG_URL "https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/dev/package_stmicroelectronics_index.json")

if(NOT "${CMAKE_CURRENT_LIST_DIR}" IN_LIST CMAKE_MODULE_PATH)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
endif()
