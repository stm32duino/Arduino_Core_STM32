cmake_minimum_required(VERSION 3.21)
include(convert_file)

# internal
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

function(insights)
  set(KEYWORDS "DIRECT_INCLUDES" "TRANSITIVE_INCLUDES" "SYMBOLS" "ARCHIVES" "LOGIC_STRUCTURE")
  cmake_parse_arguments(PARSE_ARGV 0 INSIGHTS "${KEYWORDS}" "TARGET" "")

  if(DEFINED INSIGHTS_UNPARSED_ARGUMENTS OR DEFINED INSIGHTS_KEYWORDS_MISSING_VALUES)
    message(SEND_ERROR "Invalid call to insights(); some arguments went unparsed")
  endif()

  if(NOT DEFINED INSIGHTS_TARGET)
    message(SEND_ERROR "Invalid call to insights(); please specify a TARGET")
    return()
  endif()

  get_target_property(OUTDIR ${INSIGHTS_TARGET} BINARY_DIR)

  if (${INSIGHTS_DIRECT_INCLUDES} OR ${INSIGHTS_TRANSITIVE_INCLUDES})
    set(LOGDIR "${OUTDIR}/cc_logs")
    file(MAKE_DIRECTORY ${LOGDIR})

    find_dependencies(${INSIGHTS_TARGET} ALLTARGETS)
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
          RULE_LAUNCH_COMPILE "${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/ccwrapper.py -d ${LOGDIR} -i <SOURCE> --"
        )
        set_property(TARGET ${TGT} APPEND PROPERTY
          ADDITIONAL_CLEAN_FILES "${TGT_LOGS}"
        )
      endforeach()
    endforeach()
  endif()

  if (${INSIGHTS_SYMBOLS} OR ${INSIGHTS_ARCHIVES})
    set(MAPFILE ${OUTDIR}/${INSIGHTS_TARGET}.map)
  endif()

  if (${INSIGHTS_DIRECT_INCLUDES})
    set(INSIGHTS_DIRECT_INCLUDES_GVFNAME ${OUTDIR}/direct_includes.gv)
    add_custom_command(OUTPUT ${INSIGHTS_DIRECT_INCLUDES_GVFNAME}
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/includes.py -o ${INSIGHTS_DIRECT_INCLUDES_GVFNAME} ${ALL_LOGS}
      DEPENDS ${ALL_LOGS}
    )
    gv2svg(${INSIGHTS_DIRECT_INCLUDES_GVFNAME} ${SFDP})
  endif()

  if (${INSIGHTS_TRANSITIVE_INCLUDES})
    set(INSIGHTS_TRANSITIVE_INCLUDES_GVFNAME ${OUTDIR}/transitive_includes.gv)
    add_custom_command(OUTPUT ${INSIGHTS_TRANSITIVE_INCLUDES_GVFNAME}
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/includes.py -t ${INSIGHTS_TRANSITIVE_INCLUDES_GVFNAME} ${ALL_LOGS}
      DEPENDS ${ALL_LOGS}
    )
    gv2svg(${INSIGHTS_TRANSITIVE_INCLUDES_GVFNAME} ${SFDP})
  endif()

  if (${INSIGHTS_SYMBOLS})
    set(INSIGHTS_SYMBOLS_GVFNAME ${OUTDIR}/symbols.gv)
    add_custom_command(OUTPUT ${INSIGHTS_SYMBOLS_GVFNAME}
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/syms.py -m ${MAPFILE} -f ${INSIGHTS_SYMBOLS_GVFNAME}
      DEPENDS ${MAPFILE}
    )
    gv2svg(${INSIGHTS_SYMBOLS_GVFNAME} ${SFDP})
  endif()

  if (${INSIGHTS_ARCHIVES})
    set(INSIGHTS_ARCHIVES_GVFNAME ${OUTDIR}/archives.gv)
    add_custom_command(OUTPUT ${INSIGHTS_ARCHIVES_GVFNAME}
      COMMAND ${Python3_EXECUTABLE} ${SCRIPTS_FOLDER}/syms.py -m ${MAPFILE} -s ${INSIGHTS_ARCHIVES_GVFNAME}
      DEPENDS ${MAPFILE}
    )
    gv2svg(${INSIGHTS_ARCHIVES_GVFNAME} ${SFDP})
  endif()

  if(${INSIGHTS_LOGIC_STRUCTURE})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gv)
    add_custom_command(OUTPUT ${OUTDIR}/logicstructure.gv
      COMMAND ${CMAKE_COMMAND} --graphviz=${CMAKE_CURRENT_BINARY_DIR}/gv/project.gv ${CMAKE_BINARY_DIR}
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gv/project.gv.${INSIGHTS_TARGET} ${OUTDIR}/logicstructure.gv
      BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/gv/project.gv.${INSIGHTS_TARGET}
    )
    gv2svg(${OUTDIR}/logicstructure.gv ${DOT})
  endif()
endfunction()
