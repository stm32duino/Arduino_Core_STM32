
set(CI_FOLDER ${CMAKE_CURRENT_LIST_DIR}/../CI)

function(external_library LIBPATH)
  if(NOT EXISTS ${LIBPATH}/CMakeLists.txt)
    execute_process(
      COMMAND ${PYTHON3} ${CI_FOLDER}/update/cmake_libs.py ${LIBPATH}
    )
  endif()
  get_filename_component(LIBNAME ${LIBPATH} NAME)
  add_subdirectory(
    ${LIBPATH}
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}
  )
endfunction()
