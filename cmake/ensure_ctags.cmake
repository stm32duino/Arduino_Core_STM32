include(FetchContent)

function(ensure_ctags CTAGS_PATH AUTODL_CTAGS)
  find_program(CTAGS ctags PATHS ${CTAGS_PATH})
  if(EXISTS ${CTAGS})
    return()
  endif()


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

  if (DEFINED OSCODE AND DEFINED CPUCODE AND DEFINED ARCHIVE_EXT)
    if (${AUTODL_CTAGS})
      # the SHA512 file is of the form "hash_in_hexa filename"
      file(DOWNLOAD
        "https://github.com/arduino/ctags/releases/download/5.8-arduino11/ctags-5.8-arduino11-${CPUCODE}-${OSCODE}${ARCHIVE_EXT}.sha512"
        ${CMAKE_CURRENT_BINARY_DIR}/ctags_sha512.txt
      )
      file(READ ${CMAKE_CURRENT_BINARY_DIR}/ctags_sha512.txt CHECKSUM_FULLTEXT)
      string(SUBSTRING "${CHECKSUM_FULLTEXT}" 0 128 CHECKSUM) # keep just the hash; 512 bits make 128 hex caracters

      FetchContent_Declare(
        ctags
        SOURCE_DIR ${CTAGS_PATH}
        URL "https://github.com/arduino/ctags/releases/download/5.8-arduino11/ctags-5.8-arduino11-${CPUCODE}-${OSCODE}${ARCHIVE_EXT}"
        URL_HASH SHA512=${CHECKSUM}
      )
      if (NOT EXISTS ${CTAGS_PATH})
        message(STATUS "Downloading ctags...")
        FetchContent_MakeAvailable(ctags)
      endif()
    else() # supported platform, no autodl
      message(WARNING
        "
        Could not find Arduino's ctags. This tool is used to convert sketches to proper C++.
        Please install it and make it available in your $PATH, or let me make my private install using the AUTODL_CTAGS option.
        (You can ignore this warning if you understand the implications regarding the structure of your sketch.)
        "
      )
    endif()
  else() # unsupported platform
    message(WARNING
      "
      Could not find Arduino's ctags. This tool is used to convert sketches to proper C++.
      Please install it and make it available in your $PATH: https://github.com/arduino/ctags/releases/latest
      (You can ignore this warning if you understand the implications regarding the structure of your sketch.)
      "
    )
  endif()

  find_program(CTAGS ctags PATHS ${CTAGS_PATH})
endfunction()
