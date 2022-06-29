
include(FetchContent)

function(ensure_binutils XPACK_PATH AUTODL_XPACK)
  # not "required" _yet_, if we don't find them we'll try to download them
  find_program(CMAKE_ASM_COMPILER arm-none-eabi-gcc PATHS ${XPACK_PATH}/bin) # not arm-none-eabi-as, because we want preprocessing
  find_program(CMAKE_C_COMPILER arm-none-eabi-gcc PATHS ${XPACK_PATH}/bin)
  find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ PATHS ${XPACK_PATH}/bin)
  find_program(CMAKE_AR arm-none-eabi-ar PATHS ${XPACK_PATH}/bin)
  find_program(CMAKE_LD arm-none-eabi-ld PATHS ${XPACK_PATH}/bin)
  find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy PATHS ${XPACK_PATH}/bin)
  find_program(CMAKE_SIZE arm-none-eabi-size PATHS ${XPACK_PATH}/bin)

  if (NOT EXISTS ${CMAKE_ASM_COMPILER} OR NOT EXISTS ${CMAKE_C_COMPILER} OR NOT EXISTS ${CMAKE_CXX_COMPILER} OR NOT EXISTS ${CMAKE_AR} OR NOT EXISTS ${CMAKE_LD} OR NOT EXISTS ${CMAKE_OBJCOPY})

    cmake_host_system_information(
      RESULT HOSTINFO
      QUERY OS_NAME OS_PLATFORM
    )
    list(GET HOSTINFO 0 HOST_OS)
    list(GET HOSTINFO 1 HOST_ARCH)

    unset(OSCODE)
    unset(ARCHIVE_EXT)
    if (${HOST_OS} STREQUAL "Linux")
      set(OSCODE "linux")
      set(ARCHIVE_EXT ".tar.gz")
    elseif (${HOST_OS} STREQUAL "Windows")
      set(OSCODE "win32")
      set(ARCHIVE_EXT ".zip")
    elseif (${HOST_OS} STREQUAL "Darwin")
      set(OSCODE "darwin")
      set(ARCHIVE_EXT ".tar.gz")
    endif()

    unset(CPUCODE)
    string(TOUPPER ${HOST_ARCH} HOST_ARCH)
    if (${HOST_ARCH} MATCHES "^(AMD64|X86_64|x64)$")
      set(CPUCODE "x64")
    elseif (${HOST_ARCH} MATCHES "^(ARM64)$")
      set(CPUCODE "arm64")
    elseif (${HOST_ARCH} MATCHES "^(ARM)$")
      set(CPUCODE "arm")
    elseif (${HOST_ARCH} MATCHES "^(I386|IA32|x86|i686)$")
      set(CPUCODE "ia32")
    endif()

    if (DEFINED OSCODE AND DEFINED CPUCODE AND DEFINED ARCHIVE_EXT)
      if (${AUTODL_XPACK})
        FetchContent_Declare(
          xpack
          SOURCE_DIR ${XPACK_PATH}
          URL "https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v10.3.1-2.3/xpack-arm-none-eabi-gcc-10.3.1-2.3-${OSCODE}-${CPUCODE}${ARCHIVE_EXT}"
        )
        if (NOT EXISTS ${XPACK_PATH})
          message(STATUS "Downloading xpack...")
          FetchContent_MakeAvailable(xpack)
        endif()
      else() # supported platform, no autodl
        message(FATAL_ERROR
          "
          Could not find arm-none-eabi-gcc/g++/ar/ld/objcopy. These are required to build for stm32.
          Please install them and make them available in your $PATH, or let me make my private install using the AUTODL_XPACK option.
          "
        )
      endif()
    else() # unsupported platform
      message(FATAL_ERROR
        "
        Could not find arm-none-eabi-gcc/g++/ar/ld/objcopy. These are required to build for stm32.
        Please install them and make them available in your $PATH.
        "
      )
    endif()


  endif()

  find_program(CMAKE_ASM_COMPILER arm-none-eabi-gcc PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_C_COMPILER arm-none-eabi-gcc PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_AR arm-none-eabi-ar PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_LD arm-none-eabi-ld PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy PATHS ${XPACK_PATH}/bin REQUIRED)
  find_program(CMAKE_SIZE arm-none-eabi-size PATHS ${XPACK_PATH}/bin REQUIRED)

endfunction()
