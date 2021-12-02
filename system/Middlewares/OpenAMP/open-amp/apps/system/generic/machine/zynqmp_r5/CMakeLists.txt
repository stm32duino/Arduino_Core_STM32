include(CheckSymbolExists)

collect (APP_COMMON_SOURCES helper.c)

set (_linker_script "${CMAKE_CURRENT_SOURCE_DIR}/linker_remote.ld")
set_property (GLOBAL PROPERTY APP_LINKER_OPT "-T\"${_linker_script}\"")
set (_linker_large_text_script "${CMAKE_CURRENT_SOURCE_DIR}/linker_large_text.ld")
set_property (GLOBAL PROPERTY APP_LINKER_LARGE_TEXT_OPT "-T\"${_linker_large_text_script}\"")

find_path(XIL_INCLUDE_DIR NAMES xparameters.h PATHS ${CMAKE_FIND_ROOT_PATH})
collect (PROJECT_INC_DIRS "${XIL_INCLUDE_DIR}")

find_library(LIBXIL_LIB NAMES xil PATHS ${CMAKE_FIND_ROOT_PATH})
get_filename_component(LIBXIL_LIB_DIR ${LIBXIL_LIB} DIRECTORY)
collect(PROJECT_LIB_DIRS ${LIBXIL_LIB_DIR})

# check PM API for certain headers and set client version based
CHECK_SYMBOL_EXISTS(XPAR_XILPM_ENABLED "xparameters.h" PM_FOUND)
if(PM_FOUND)
  find_library(HAS_PM_LIB NAMES xilpm PATHS ${CMAKE_FIND_ROOT_PATH})
  collect (PROJECT_LIB_DEPS xilpm)
  CHECK_SYMBOL_EXISTS(versal "xparameters.h" VERSION_2_PM_CLIENT)
  if (VERSION_2_PM_CLIENT)
    collect (APP_EXTRA_C_FLAGS "  -DVERSION_2_PM_CLIENT ")
  else()
    collect (APP_EXTRA_C_FLAGS "  -DVERSION_1_PM_CLIENT ")
  endif(VERSION_2_PM_CLIENT)
endif(PM_FOUND)

collect(PROJECT_LIB_DEPS xil)
collect(PROJECT_LIB_DEPS c)
collect(PROJECT_LIB_DEPS m)
find_library(XILMEM_LIB NAMES xilmem PATHS ${CMAKE_FIND_ROOT_PATH})
if(XILMEM_LIB)
  collect (PROJECT_LIB_DEPS xilmem)
endif(XILMEM_LIB)
