cmake_minimum_required(VERSION 3.21)
function(elf2bin ELFTGT)
  add_custom_command(TARGET ${ELFTGT} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${ELFTGT}> $<TARGET_FILE:${ELFTGT}>.bin
  )
  set_property(TARGET ${ELFTGT} APPEND PROPERTY ADDITIONAL_CLEAN_FILES "$<TARGET_FILE:${ELFTGT}>.bin")
endfunction()

function(elf2hex ELFTGT)
  add_custom_command(TARGET ${ELFTGT} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${ELFTGT}> $<TARGET_FILE:${ELFTGT}>.hex
  )
  set_property(TARGET ${ELFTGT} APPEND PROPERTY ADDITIONAL_CLEAN_FILES "$<TARGET_FILE:${ELFTGT}>.hex")
endfunction()

function(gv2svg GVFILE ENGINE)
  get_filename_component(ABSGV ${GVFILE} ABSOLUTE BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
  get_filename_component(GVNAME ${GVFILE} NAME)

  # HACK: all this to get the final SVG file as a visible target with the same name as the file
  add_custom_target(${GVNAME}.svg DEPENDS ${ABSGV})
  add_custom_command(TARGET ${GVNAME}.svg POST_BUILD
    COMMAND ${ENGINE} -Tsvg -o ${ABSGV}.svg ${ABSGV}
  )
  set_property(TARGET ${GVNAME}.svg APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${ABSGV}.svg)

endfunction()
