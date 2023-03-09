cmake_minimum_required(VERSION 3.21)
include(FetchContent)

function(get_core_version OUTVAR)
  file(READ ${PLATFORMTXT_PATH} PLATFORMTXT)
  string(REGEX MATCH "version=.+\n" LINE "${PLATFORMTXT}")
  string(SUBSTRING "${LINE}" 8 -1 INVAR)
  set(${OUTVAR} ${INVAR} PARENT_SCOPE)
endfunction()

function(get_host OUTVAR)
  cmake_host_system_information(
    RESULT HOSTINFO
    QUERY OS_NAME OS_PLATFORM
  )
  list(GET HOSTINFO 0 HOST_OS)
  list(GET HOSTINFO 1 HOST_ARCH)
  string(TOUPPER ${HOST_ARCH} HOST_ARCH)

  set(${OUTVAR} "all" PARENT_SCOPE) # fallback value
  if (${HOST_OS} STREQUAL "Linux")
    if (${HOST_ARCH} MATCHES "^(AMD64|X86_64|x64)$")
      set(${OUTVAR} "x86_64-pc-linux-gnu" PARENT_SCOPE)
    elseif (${HOST_ARCH} MATCHES "^(ARM64)$")
      set(${OUTVAR} "aarch64-linux-gnu" PARENT_SCOPE)
    elseif (${HOST_ARCH} MATCHES "^(ARM)$")
      # TODO: check for FPU with cmake_host_system_information(HAS_FPU)
      set(${OUTVAR} "arm-linux-gnueabihf" PARENT_SCOPE)
    elseif (${HOST_ARCH} MATCHES "^(I386|IA32|x86|i686)$")
      set(${OUTVAR} "i686-pc-linux-gnu" PARENT_SCOPE)
    endif()
  elseif (${HOST_OS} STREQUAL "Windows")
    if (${HOST_ARCH} MATCHES "^(AMD64|X86_64|x64|I386|IA32|x86|I686)$")
      set(${OUTVAR} "i686-mingw32" PARENT_SCOPE)
    endif()
  elseif (${HOST_OS} STREQUAL "Darwin")
    if (${HOST_ARCH} MATCHES "^(AMD64|X86_64|x64)$")
      set(${OUTVAR} "x86_64-apple-darwin" PARENT_SCOPE)
    endif()
  endif()
endfunction()

function(get_target_url JSONARR OUT_URL OUT_SHA)
  get_host(HOSTID)
  string(JSON LEN LENGTH "${JSONARR}")
  math(EXPR LEN "${LEN}-1") # iterate from 0 to len-1
  foreach(I RANGE ${LEN})
    string(JSON IHOST GET "${JSONARR}" ${I} "host")
    if(${IHOST} STREQUAL "all" OR ${IHOST} STREQUAL ${HOSTID})
      string(JSON IURL GET "${JSONARR}" ${I} "url")
      string(JSON ISUM GET "${JSONARR}" ${I} "checksum")
      set(${OUT_URL} ${IURL} PARENT_SCOPE)
      string(SUBSTRING "${ISUM}" 8 -1 ISUM) # assume "SHA-256:", remove that prefix
      set(${OUT_SHA} ${ISUM} PARENT_SCOPE)
      return()
    endif()
  endforeach()
endfunction()

function(declare_deps CORE_VERSION)

  # Prevent warnings in CMake>=3.24 regarding ExternalProject_Add()
  # cf. https://cmake.org/cmake/help/latest/policy/CMP0135.html
  cmake_policy(SET CMP0135 OLD)

  file(REAL_PATH "${DL_DIR}/package_stmicroelectronics_index.json" JSONFILE)
  if (NOT EXISTS ${JSONFILE})
    file(DOWNLOAD "${JSONCONFIG_URL}" ${JSONFILE})
  endif()
  file(READ ${JSONFILE} JSONCONFIG)
  string(JSON PLATFORMS GET "${JSONCONFIG}" "packages" 0 "platforms")
  string(JSON TOOLS GET "${JSONCONFIG}" "packages" 0 "tools")
  string(JSON LEN_PLATFORM LENGTH "${PLATFORMS}")
  math(EXPR LEN_PLATFORM "${LEN_PLATFORM}-1") # iterate from 0 to len-1
  string(JSON LEN_TOOLS LENGTH "${TOOLS}")
  math(EXPR LEN_TOOLS "${LEN_TOOLS}-1")

  # 1. extract the dependencies of the core at the specified version
  # (or the latest version older than the target version)
  set(VERS "0.0.0")
  set(DEPS "")
  foreach(I_PKG RANGE ${LEN_PLATFORM})
    string(JSON I_ARCH GET "${PLATFORMS}" ${I_PKG} "architecture")
    if (NOT ${I_ARCH} STREQUAL "stm32")
      continue()
    endif()

    string(JSON I_VER GET "${PLATFORMS}" ${I_PKG} "version")
    if(${I_VER} VERSION_LESS_EQUAL ${CORE_VERSION} AND ${I_VER} VERSION_GREATER ${VERS})
      set(VERS ${I_VER})
      string(JSON DEPS GET "${PLATFORMS}" ${I_PKG} "toolsDependencies")
    endif()
  endforeach()

  # 2. find the versions of the dependencies for that core
  set(XPACK_VERSION "0.0.0")
  set(CMSIS_VERSION "0.0.0")
  # Note: we're ignoring the STM32Tools dep, because unlike Arduino IDE we don't need it (upload + misc scripts)
  string(JSON LEN_DEPS LENGTH "${DEPS}")
  math(EXPR LEN_DEPS "${LEN_DEPS}-1")
  foreach(I_DEP RANGE ${LEN_DEPS})
    string(JSON DEP_NAME GET "${DEPS}" ${I_DEP} "name")
    if(${DEP_NAME} STREQUAL "xpack-arm-none-eabi-gcc")
      string(JSON XPACK_VERSION GET "${DEPS}" ${I_DEP} "version")
    elseif(${DEP_NAME} STREQUAL "CMSIS")
      string(JSON CMSIS_VERSION GET "${DEPS}" ${I_DEP} "version")
    endif()
  endforeach()

  # 3. grab the correct download URL + SHAsum for each dep
  set(XPACK_URL "")
  set(XPACK_SHA "")
  set(CMSIS_URL "")
  set(CMSIS_SHA "")
  foreach(I_TOOL RANGE ${LEN_TOOLS})
    string(JSON TOOL_NAME GET "${TOOLS}" ${I_TOOL} "name")
    string(JSON TOOL_VERSION GET "${TOOLS}" ${I_TOOL} "version")
    string(JSON TOOL_SUPPORT GET "${TOOLS}" ${I_TOOL} "systems")
    if(${TOOL_NAME} STREQUAL "xpack-arm-none-eabi-gcc" AND ${TOOL_VERSION} VERSION_EQUAL ${XPACK_VERSION})
      get_target_url("${TOOL_SUPPORT}" XPACK_URL XPACK_SHA)
    elseif(${TOOL_NAME} STREQUAL "CMSIS" AND ${TOOL_VERSION} VERSION_EQUAL ${CMSIS_VERSION})
      get_target_url("${TOOL_SUPPORT}" CMSIS_URL CMSIS_SHA)
    endif()
  endforeach()

  # 4. declare the download (not executed yet, that will be up to the caller)
  FetchContent_Declare(
    xpack
    SOURCE_DIR ${DL_DIR}/dist/xpack
    PREFIX ${DL_DIR}
    URL "${XPACK_URL}"
    URL_HASH SHA256=${XPACK_SHA}
    UPDATE_DISCONNECTED
  )

  FetchContent_Declare(
    CMSIS5
    SOURCE_DIR ${DL_DIR}/dist/CMSIS5
    PREFIX ${DL_DIR}
    URL "${CMSIS_URL}"
    URL_HASH SHA256=${CMSIS_SHA}
    UPDATE_DISCONNECTED
  )
endfunction()

# defines a CMSIS5_PATH in the caller's scope
function(ensure_core_deps)
  if(NOT EXISTS ${DL_DIR}/dist/CMSIS5 OR NOT EXISTS ${DL_DIR}/dist/xpack)
    get_core_version(COREVER)
    declare_deps(${COREVER})
    message(STATUS "Downloading the CMSIS...")
    FetchContent_MakeAvailable(CMSIS5)
    message(STATUS "Downloading the CMSIS... Done.")
    message(STATUS "Downloading the compiler toolchain...")
    FetchContent_MakeAvailable(xpack)
    message(STATUS "Downloading the compiler toolchain... Done.")
  endif()

  set(CMSIS5_PATH ${DL_DIR}/dist/CMSIS5 PARENT_SCOPE)

  find_program(CMAKE_ASM_COMPILER arm-none-eabi-gcc PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_C_COMPILER arm-none-eabi-gcc PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_AR arm-none-eabi-ar PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_LD arm-none-eabi-ld PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
  find_program(CMAKE_SIZE arm-none-eabi-size PATHS ${DL_DIR}/dist/xpack/bin REQUIRED)
endfunction()
