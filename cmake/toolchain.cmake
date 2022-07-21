cmake_minimum_required(VERSION 3.21)

find_package(
        Python3 3.9 REQUIRED
        COMPONENTS Interpreter
)

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import graphviz"
    RESULT_VARIABLE EXIT_CODE
    OUTPUT_QUIET
)
if(${EXIT_CODE})
  message(WARNING "Python's `graphviz` module not found. Some features will be disabled.")
  set(PYTHON_HAS_GRAPHVIZ OFF)
else()
  set(PYTHON_HAS_GRAPHVIZ ON)
endif()

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import jinja2"
    RESULT_VARIABLE EXIT_CODE
    OUTPUT_QUIET
)
if(${EXIT_CODE})
  message(WARNING "Python's `jinja2` module not found. Some features will be disabled.")
  set(PYTHON_HAS_JINJA OFF)
else()
  set(PYTHON_HAS_JINJA ON)
endif()



find_program(SFDP "sfdp") # graphviz layout engine -- you may change the engine, use dot or whatever

include("${CMAKE_CURRENT_LIST_DIR}/ensure_core_deps.cmake")
ensure_core_deps()

# Setting Linux is forcing th extension to be .o instead of .obj when building on WIndows.
# It is important because armlink is failing when files have .obj extensions (error with
# scatter file section not found)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY) # don't try to link when testing the compiler, it won't work anyway
set(BUILD_SHARED_LIBS false CACHE STRING "")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
