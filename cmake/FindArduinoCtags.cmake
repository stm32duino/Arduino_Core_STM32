cmake_minimum_required(VERSION 3.21)
include(FetchContent)
include(FindPackageHandleStandardArgs)

function(get_ctags)
  cmake_host_system_information(
    RESULT HOSTINFO
    QUERY OS_NAME OS_PLATFORM
  )
  list(GET HOSTINFO 0 HOST_OS)
  list(GET HOSTINFO 1 HOST_ARCH)

  unset(CPUCODE)
  string(TOUPPER ${HOST_ARCH} HOST_ARCH)
  if (${HOST_ARCH} MATCHES "^(AMD64|X86_64|x64)$")
    set(CPUCODE "x86_64")
  elseif (${HOST_ARCH} MATCHES "^(ARM|ARM64)$")
    # not sure there, am I specific enough?
    set(CPUCODE "armv6")
  elseif (${HOST_ARCH} MATCHES "^(I386|IA32|x86|i686)$")
    set(CPUCODE "i686")
  endif()

  unset(OSCODE)
  unset(ARCHIVE_EXT)
  if (${HOST_OS} STREQUAL "Linux")
    if(${CPUCODE} STREQUAL "armv6")
      set(OSCODE "linux-gnueabihf")
      # ... I guess? Is there any further check to perform?
    else()
      set(OSCODE "pc-linux-gnu")
    endif()
    set(ARCHIVE_EXT ".tar.bz2")
  elseif (${HOST_OS} STREQUAL "Windows")
    if(${CPUCODE} MATCHES "i686|x86_64")
      # ctags supports only 32-bit for Windows
      set(CPUCODE "i686")
      set(OSCODE "mingw32")
      set(ARCHIVE_EXT ".zip")
    endif()
  elseif (${HOST_OS} STREQUAL "Darwin")
    if(${CPUCODE} STREQUAL "x86_64")
      set(OSCODE "apple-darwin")
      set(ARCHIVE_EXT ".zip")
    endif()
  endif()

  # the SHA512 file is of the form "hash_in_hexa filename"
  if(NOT EXISTS ${DL_DIR}/ctags_sha512.txt)
    file(DOWNLOAD
      "https://github.com/arduino/ctags/releases/download/5.8-arduino11/ctags-5.8-arduino11-${CPUCODE}-${OSCODE}${ARCHIVE_EXT}.sha512"
      ${DL_DIR}/ctags_sha512.txt
    )
  endif()
  file(READ ${DL_DIR}/ctags_sha512.txt CHECKSUM_FULLTEXT)
  string(SUBSTRING "${CHECKSUM_FULLTEXT}" 0 128 CHECKSUM) # keep just the hash; 512 bits make 128 hex characters

  FetchContent_Declare(
    ctags
    SOURCE_DIR ${DL_DIR}/dist/ctags
    PREFIX ${DL_DIR}
    URL "https://github.com/arduino/ctags/releases/download/5.8-arduino11/ctags-5.8-arduino11-${CPUCODE}-${OSCODE}${ARCHIVE_EXT}"
    URL_HASH SHA512=${CHECKSUM}
    UPDATE_DISCONNECTED
  )
  message(STATUS "Downloading Arduino's ctags...")
  FetchContent_MakeAvailable(ctags)
  message(STATUS "Downloading Arduino's ctags... Done.")
endfunction()

# -------------------------------------------------------------------------------

if(NOT EXISTS ${DL_DIR}/dist/ctags)
  get_ctags()
endif()

find_program(ARDUINOCTAGS_EXECUTABLE ctags PATHS ${DL_DIR}/dist/ctags NO_DEFAULT_PATH)

find_package_handle_standard_args(ArduinoCtags DEFAULT_MSG
  ARDUINOCTAGS_EXECUTABLE
)
