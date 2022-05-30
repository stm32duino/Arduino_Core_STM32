
include(FetchContent)

function(ensure_CMSIS CMSIS5_PATH AUTODL_CMSIS)
  FetchContent_Declare(
    CMSIS_5
    SOURCE_DIR ${CMSIS5_PATH} # put the CMSIS along the other sources of the core
    URL https://github.com/stm32duino/ArduinoModule-CMSIS/releases/download/5.7.0/CMSIS-5.7.0.tar.bz2
    # see also https://github.com/ARM-software/CMSIS_5/releases/tag/5.7.0
  )

  if (NOT EXISTS ${CMSIS5_PATH})
    if (${AUTODL_CMSIS})
      message(STATUS "Downloading CMSIS...")
      FetchContent_MakeAvailable(CMSIS_5)
    else()
      message(SEND_ERROR
        "
        CMSIS not found.
        Please pass the path to your CMSIS installation through CMSIS5_PATH
        or explicitly activate downloading with AUTODL_CMSIS.
        "
      )
    endif()
  endif()
endfunction()
