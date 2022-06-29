## core feature

set(SCRIPTS_FOLDER ${CMAKE_CURRENT_LIST_DIR}/../scripts)

# MAPFILE should be absolute!!
# only a rule is generated for the mapfile, not a target
function(handle_sketch TGTNAME MAPFILE SRCLIST)
  # TODO: have the sketch folder in the include path of base_config

  add_executable(${TGTNAME} EXCLUDE_FROM_ALL ${SRCLIST})
  target_link_libraries(${TGTNAME} stm32_runtime)
  target_link_options(${TGTNAME} PRIVATE
    LINKER:-Map,${MAPFILE}
  )

  add_custom_command(OUTPUT ${MAPFILE}
    # COMMAND ${CMAKE_COMMAND} -E true
    DEPENDS ${TGTNAME}
  ) # generated automatically with ELFTGT; this is here only make CMake aware of it.

  if(EXISTS ${PYTHON3})
    add_custom_command(TARGET ${TGTNAME} POST_BUILD
      COMMAND ${PYTHON3} ${SCRIPTS_FOLDER}/sizereport.py -x ${CMAKE_SIZE} -f ${TGTNAME} --progmem ${BOARD_MAXSIZE} --datamem ${BOARD_MAXDATASIZE}
    )
  else() #  STREQUAL "PYTHON3-NOTFOUND"
    message(WARNING "python3 not found; the final size report will not be displayed")
  endif()
endfunction()


## internal

macro(find_dependencies TGT DEPTGTS)
  get_target_property(TGT_TYPE ${TGT} TYPE)
  unset(_DEP_PRIV)
  unset(_DEP_PUB)

  get_target_property(_DEP_PUB ${TGT} INTERFACE_LINK_LIBRARIES)

  if (NOT ${TGT_TYPE} STREQUAL INTERFACE_LIBRARY)
    get_target_property(_DEP_PRIV ${TGT} LINK_LIBRARIES)
    list(APPEND ${DEPTGTS} ${TGT})
  endif()

  foreach(_LIB IN LISTS _DEP_PRIV _DEP_PUB)
    if (TARGET ${_LIB} AND NOT ${_LIB} IN_LIST ${DEPTGTS})
      find_dependencies(${_LIB} ${DEPTGTS})
    endif()
  endforeach()
endmacro()


## file generation rules
# (doesn't create a target, only generates rules)
# make a custom_target depend on the files to get a hook on them from userspace

# calling this function has side-effects on all the targets ELFTGT depends on,
#   since it alters their compiling process. The resulting binaries are identical
#   but the compilation will become slower (uses a python wrapper around the compiler...)
# __Best practise would be to call this function conditionnally based on a user switch__
function(incgv NONTRGV TRGV ELFTGT)
  set(LOGDIR "${CMAKE_CURRENT_BINARY_DIR}/cc_logs")
  file(MAKE_DIRECTORY ${LOGDIR})

  find_dependencies(${ELFTGT} ALLTARGETS)
  set(ALL_LOGS "")
  foreach(TGT IN LISTS ALLTARGETS)
    set(TGT_LOGS "")
    get_target_property(TGTSOURCES ${TGT} SOURCES)
    foreach(S IN LISTS TGTSOURCES)
      get_filename_component(FN ${S} NAME)
      set(S_LOG "${LOGDIR}/${FN}.log")
      # # doesn't work properly on some source files
      # set_source_files_properties(${S} PROPERTIES
      #   OBJECT_OUTPUTS ${S_LOG}
      # )
      add_custom_command(
        # the log depends on the whole target, no just on the object file
        # the latter would be more efficient, but is harder to implement properly
        OUTPUT ${S_LOG}
        DEPENDS ${TGT}
      )
      list(APPEND ALL_LOGS ${S_LOG})
      list(APPEND TGT_LOGS ${S_LOG})

      target_compile_options(${TGT} PRIVATE
        -H # display #include'd paths on stderr
      )
      set_target_properties(${TGT} PROPERTIES
        RULE_LAUNCH_COMPILE "${PYTHON3} ${SCRIPTS_FOLDER}/ccwrapper.py -d ${LOGDIR} -i <SOURCE> --"
        ADDITIONAL_CLEAN_FILES "${TGT_LOGS}"
      )
    endforeach()
  endforeach()

  add_custom_command(OUTPUT ${NONTRGV} ${TRGV}
    COMMAND ${PYTHON3} ${SCRIPTS_FOLDER}/includes.py -o ${NONTRGV} -t ${TRGV} ${ALL_LOGS}
    DEPENDS ${ALL_LOGS}
  )
endfunction()

# on the other hand, this one is quite harmless
# you should wrap it too, though
function(symgv FULLGV SUMMARYGV MAPFILE)
  add_custom_command(OUTPUT ${FULLGV} ${SUMMARYGV}
    COMMAND ${PYTHON3} ${SCRIPTS_FOLDER}/syms.py -m ${MAPFILE} -f ${FULLGV} -s ${SUMMARYGV}
    DEPENDS ${MAPFILE}
  )
endfunction()


## file conversion

function(elf2bin TGTNAME ELFTGT)
  # set(BINFILE $<TARGET_FILE_BASE_NAME:${ELFTGT}>.bin)
  set(BINFILE ${ELFTGT}.bin)
  add_custom_command(OUTPUT ${BINFILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary ${ELFTGT} ${BINFILE}
    DEPENDS ${ELFTGT}
  )
  add_custom_target(${TGTNAME} ALL DEPENDS ${BINFILE})
endfunction()
function(elf2hex TGTNAME ELFTGT)
  # set(HEXFILE $<TARGET_FILE_BASE_NAME:${ELFTGT}>.hex)
  set(HEXFILE ${ELFTGT}.hex)
  add_custom_command(OUTPUT ${HEXFILE}
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${ELFTGT} ${HEXFILE}
    DEPENDS ${ELFTGT}
  )
  add_custom_target(${TGTNAME} ALL DEPENDS ${HEXFILE})
endfunction()
function(gv2svg TGTNAME GVFILE)
  set(SVGFILE ${GVFILE}.svg)
  add_custom_command(OUTPUT ${SVGFILE}
    COMMAND ${SFDP} -Tsvg -o ${SVGFILE} ${GVFILE}
    DEPENDS ${GVFILE}
  )
  add_custom_target(${TGTNAME} DEPENDS ${SVGFILE})
endfunction()
