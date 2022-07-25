cmake_minimum_required(VERSION 3.21)

function(overall_settings)
  if(TARGET user_settings)
    message(SEND_ERROR "overall_settings() was called twice. This is not allowed as it could result in conflicting settings.")
    return()
  endif()

  add_library(user_settings INTERFACE)

  set(KEYWORDS0 STANDARD_LIBC PRINTF_FLOAT SCANF_FLOAT DEBUG_SYMBOLS LTO NO_RELATIVE_MACRO UNDEF_NDEBUG CORE_CALLBACK)
  set(KEYWORDS1 OPTIMIZATION BUILD_OPT)
  set(KEYWORDSN DISABLE_HAL_MODULES)
  cmake_parse_arguments(PARSE_ARGV 0 WANT "${KEYWORDS0}" "${KEYWORDS1}" "${KEYWORDSN}")

  if(DEFINED WANT_UNPARSED_ARGUMENTS OR DEFINED WANT_KEYWORDS_MISSING_VALUES)
    message(SEND_ERROR "Invalid call to overall_settings(); some arguments went unparsed")
  endif()

  if(${WANT_CORE_CALLBACK})
    target_compile_options(user_settings INTERFACE
      CORE_CALLBACK
    )
  endif()

  if(NOT ${WANT_NO_RELATIVE_MACRO})
    # $<TARGET_PROPERTY:SOURCE_DIR> is evaluated by the final consumer, not user_settings
    target_compile_options(user_settings INTERFACE
      "-fmacro-prefix-map=$<TARGET_PROPERTY:SOURCE_DIR>=."
    )
  endif()

  if(NOT ${WANT_UNDEF_NDEBUG})
    target_compile_definitions(user_settings INTERFACE NDEBUG)
  endif()

  if(NOT ${WANT_STANDARD_LIBC})
  	target_link_options(user_settings INTERFACE
  		"--specs=nano.specs"
  	)
  	if(${WANT_PRINTF_FLOAT})
  		target_link_options(user_settings INTERFACE
  			"SHELL:-u _printf_float"
  		)
  	endif()
  	if(${WANT_SCANF_FLOAT})
  		target_link_options(user_settings INTERFACE
  			"SHELL:-u _scanf_float"
  		)
  	endif()
  endif()

  if(NOT DEFINED WANT_OPTIMIZATION)
    set(WANT_OPTIMIZATION "s")
  endif()
  if(${WANT_OPTIMIZATION} MATCHES "^[0-3gs]$")
  	target_compile_options(user_settings INTERFACE
  		-O${WANT_OPTIMIZATION}
  	)
  else()
  	message(SEND_ERROR "Bad value for OPTIMIZATION: got `${WANT_OPTIMIZATION}`, expected one of 0123gs.")
  endif()

  if(${WANT_DEBUG_SYMBOLS})
  	target_compile_options(user_settings INTERFACE
  		-g
  	)
  endif()

  if(${WANT_LTO})
    # the INTERPROCEDURAL_OPTIMIZATION property doesn't work here
    # (because it's an INTERFACE target I guess ?)
  	target_compile_options(user_settings INTERFACE
      -flto
    )
  	target_link_options(user_settings INTERFACE
      -flto
    )
  endif()

  if(DEFINED WANT_BUILD_OPT)
    cmake_path(ABSOLUTE_PATH WANT_BUILD_OPT)
    target_compile_options(user_settings INTERFACE
      "@${WANT_BUILD_OPT}"
    )
    target_link_options(user_settings INTERFACE
      "@${WANT_BUILD_OPT}"
    )
  endif()

  if(DEFINED WANT_DISABLE_HAL_MODULES)
    foreach(MOD IN LISTS WANT_DISABLE_HAL_MODULES)
      string(TOUPPER ${MOD} MOD)
      add_compile_definitions(user_settings INTERFACE
        HAL_${MOD}_MODULE_DISABLED
      )
    endforeach()
  endif()
endfunction()
