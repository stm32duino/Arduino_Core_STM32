/*
 * This script extends the default linker script to add a .noinit
 * section. This section is just mapped to RAM, but it is emitted
 * separately from the .data and .bss sections (both of which are
 * initialized by startup code), so any variables in this section are
 * untouched on startup (so they survive across resets).
 *
 * This script is intended to supplied to the linker's -T / --script
 * option as the primary linker script. When the linker sees an INSERT
 * command, this will cause it to *also* read the default linker script
 * (after reading this script) and then executing the INSERT commands
 * after both scripts have been read.
 *
 * Note that parsing of linker scripts is a bit peculiar, e.g. INSERT
 * does not textually inserts, it inserts any generated output sections.
 * Also, because this script is read *first*, we cannot refer to things
 * in the default script. In particular, it would make sense to add >
 * RAM to the output section below to ensure that the section is mapped
 * into RAM, but the RAM region is not defined yet (I think it would
 * work though, but produces warnings). Instead, we just rely on the
 * defaults used by the linker: If no region is defined for an output
 * section, it will just map to first address after the previous section
 * (.bss in this case, which is fine).
 */
SECTIONS
{
  /* Define a noinit output section and mark it as NOLOAD to prevent
   * putting its contents into the resulting .bin file (which is the
   * default). */
  .noinit (NOLOAD) :
  {
    /* Ensure output is aligned */
    . = ALIGN(4);
    /* Define a global _snoinit (and _enoinit below) symbol just in case
     * code wants to iterate over all noinit variables for some reason */
    _snoinit = .;
    /* Actually import the .noinit and .noinit* import sections */
    *(.noinit)
    *(.noinit*)
    . = ALIGN(4);
    _enoinit = .;
  }
}
INSERT AFTER .bss;
