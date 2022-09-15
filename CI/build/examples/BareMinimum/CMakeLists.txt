include(handle_sketch)

handle_sketch(BareMinimum ${CMAKE_CURRENT_BINARY_DIR}/BareMinimum.map ./BareMinimum.ino)

elf2bin(bin BareMinimum)
elf2hex(hex BareMinimum)

option(GRAPHING OFF "")
if (${GRAPHING})
  incgv(incntr.gv inctr.gv BareMinimum)
  gv2svg(inc_nontr incntr.gv)
  gv2svg(inc_tr inctr.gv)

  symgv(symfull.gv symsummary.gv ${CMAKE_CURRENT_BINARY_DIR}/BareMinimum.map)
  gv2svg(symfull symfull.gv)
  gv2svg(symsummary symsummary.gv)
endif()
