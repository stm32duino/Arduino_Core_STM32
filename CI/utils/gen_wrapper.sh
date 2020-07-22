#!/bin/bash -
set -o nounset # Treat unset variables as an error

# Base path
Core_path=../..
SrcWrapper_path=$Core_path/libraries/SrcWrapper
HALDrivers_path=$Core_path/system/Drivers
CMSIS_Device_ST_path=$Core_path/system/Drivers/CMSIS/Device/ST
CMSIS_DSP_path=$Core_path/libraries/CMSIS_DSP
# CMSIS outside of the core. To be updated to match environment
CMSIS_path=$Core_path/../ArduinoModule-CMSIS/CMSIS_5
CMSIS_DSPSrc_path=$CMSIS_path/CMSIS/DSP/Source

# Out sources files
HALoutSrc_path=$SrcWrapper_path/src/HAL
LLoutSrc_path=$SrcWrapper_path/src/LL
CMSIS_DSP_outSrc_path=$CMSIS_DSP_path/src

# Out include files
LLoutInc_path=$Core_path/cores/arduino/stm32/LL

# Out startup files
CMSIS_Startupfile=$Core_path/cores/arduino/stm32/stm32_def_build.h

# Variables
series=($(find $HALDrivers_path -maxdepth 1 -type d -name "STM32*" | sed -e "s#$HALDrivers_path/STM32##g" -e "s#xx_HAL_Driver##g" | sort))

all_LL_file=stm32yyxx_ll.h

# Create the file
print_C_header() {
  # if [[ $1 = *"template"* ]]; then
  #   echo "#if 0" > "$1"
  # else
  #   touch "$1"
  # fi
  touch "$1"
}

# Add some pragma to ll header files to avoid several warnings
# which will be corrected along Cube update
print_LL_header() {
  upper=$(echo "$1" | awk '{print toupper($1)}' | sed -e "s/\./_/g")
  echo "#ifndef _${upper}_
#define _${upper}_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored \"-Wunused-parameter\"
#pragma GCC diagnostic ignored \"-Wstrict-aliasing\"
" > $LLoutInc_path/"$1"
}

print_CMSIS_Startup_header() {
  echo "#ifndef _STM32_DEF_BUILD_
#define _STM32_DEF_BUILD_

#if !defined(CMSIS_STARTUP_FILE) && !defined(CUSTOM_STARTUP_FILE)" > $CMSIS_Startupfile
}

print_CMSIS_Startup_footer() {
  echo "  #else
    #error UNKNOWN CHIP
  #endif
#else
  #warning \"No CMSIS startup file defined, custom one should be used\"
#endif /* !CMSIS_STARTUP_FILE && !CUSTOM_STARTUP_FILE */
#endif /* _STM32_DEF_BUILD_ */" >> $CMSIS_Startupfile
}

print_CMSIS_Startup_list() {
  # Handle first elements
  # File name
  local f
  local upper
  f=$(echo "${list[0]}" | awk -F/ '{print $NF}')
  upper=$(echo "$f" | awk -F'[_.]' '{print toupper($2)}' | tr X x)
  echo "  #if defined($upper)
    #define CMSIS_STARTUP_FILE \"$f\"" >> $CMSIS_Startupfile

  if [ ${#list[@]} -gt 1 ]; then
    for fp in "${list[@]:1}"; do
      # File name
      f=$(echo "$fp" | awk -F/ '{print $NF}')
      upper=$(echo "$f" | awk -F'[_.]' '{print toupper($2)}' | tr X x)
      upper="${upper//MP15xx/MP1xx}"
      echo "  #elif defined($upper)
    #define CMSIS_STARTUP_FILE \"$f\"" >> $CMSIS_Startupfile
    done
  fi
}

# main
# Check if this is the right place
if [ ! -d $HALDrivers_path ]; then
  echo "Could not find $HALDrivers_path!"
  echo "Launch $0 from scripts folder!"
  exit 1
fi

# Remove old file
rm -f $HALoutSrc_path/* $LLoutSrc_path/* $LLoutInc_path/* $CMSIS_Startupfile

# Search all files for each series
for serie in "${series[@]}"; do
  if [ -d $HALDrivers_path/STM32"${serie}"xx_HAL_Driver/Src ]; then
    lower=$(echo "$serie" | awk '{print tolower($0)}')
    echo -n "Generating for $serie..."

    # Generate stm32yyxx_[hal|ll]*.c file
    filelist=($(find $HALDrivers_path/STM32"${serie}"xx_HAL_Driver/Src -maxdepth 1 -name "stm32${lower}xx_*.c"))
    for fp in "${filelist[@]}"; do
      # No need for template
      if [[ $fp = *"template"* ]]; then
        continue
      fi
      outp=$HALoutSrc_path
      # File name
      f=$(echo "$fp" | awk -F/ '{print $NF}')
      # Compute generic file name
      g="${f//$lower/yy}"
      if [[ $f = *"_ll_"* ]]; then
        outp=$LLoutSrc_path
      fi
      if [ ! -f $outp/"$g" ]; then
        print_C_header $outp/"$g"
      fi
      # Amend file name under serie switch
      {
        echo "#ifdef STM32${serie}xx"
        echo "  #include \"$f\""
        echo "#endif"
      } >> $outp/"$g"
    done

    # Generate stm32yyxx_ll_*.h file
    filelist=($(find $HALDrivers_path/STM32"${serie}"xx_HAL_Driver/Inc -maxdepth 2 -name "stm32${lower}xx_ll_*.h"))
    for fp in "${filelist[@]}"; do
      # File name
      f=$(echo "$fp" | awk -F/ '{print $NF}')
      # Compute generic file name
      g="${f//$lower/yy}"

      if [ ! -f $LLoutInc_path/"$g" ]; then
        print_LL_header "$g"
      fi
      # Amend full LL header file
      echo "#include \"$g\"" >> $LLoutInc_path/${all_LL_file}.tmp
      # Amend file name under serie switch
      {
        echo "#ifdef STM32${serie}xx"
        echo "  #include \"$f\""
        echo "#endif"
      } >> $LLoutInc_path/"$g"
    done
    echo "done"
  fi
done

# Filter full LL header file
if [ ! -f $LLoutInc_path/$all_LL_file ]; then
  print_LL_header $all_LL_file
fi
echo "/* Include Low Layers drivers */" >> $LLoutInc_path/${all_LL_file}
sort -u $LLoutInc_path/${all_LL_file}.tmp >> $LLoutInc_path/${all_LL_file}
rm -f $LLoutInc_path/${all_LL_file}.tmp

# Search all template file to end "#if 0"
# filelist=($(find $HALoutSrc_path -maxdepth 1 -name "stm32*_template.c"))
# for fp in "${filelist[@]}"; do
#   echo "#endif /* 0 */" >> "$fp"
# done

# Search all LL header files to end guard
filelist=($(find $LLoutInc_path -maxdepth 1 -name "stm32yyxx_ll*.h"))
for fp in "${filelist[@]}"; do
  upper=$(basename "$fp" | awk '{print toupper($1)}' | sed -e "s/\./_/g")
  echo "#pragma GCC diagnostic pop" >> "$fp"
  echo "#endif /* _${upper}_ */" >> "$fp"
done

# CMSIS startup files
list=($(find $CMSIS_Device_ST_path -name "startup_*.s" | grep gcc | sort -du))
if [ ${#list[@]} -ne 0 ]; then
  echo "Number of startup files: ${#list[@]}"
  print_CMSIS_Startup_header
  print_CMSIS_Startup_list
  print_CMSIS_Startup_footer
else
  echo "No startup files found!"
fi

# CMSIS DSP C source files
if [ ! -d $CMSIS_DSPSrc_path ]; then
  echo "Could not find $CMSIS_DSPSrc_path!"
  echo "Update 'CMSIS_path' in $0 to point on ArduinoModule-CMSIS folder."
  echo "Skip CMSIS DSP generation."
else
  # Remove old file
  rm -fr "${CMSIS_DSP_outSrc_path:?}"/*/

  filelist=($(find $CMSIS_DSPSrc_path -name "*.c" | sed -e "s#$CMSIS_DSPSrc_path/##g" | sort -u))
  for fp in "${filelist[@]}"; do
    # Directory name
    d=$(echo "$fp" | awk -F/ '{print $(NF-1)}')
    if [ ! -d $CMSIS_DSP_outSrc_path/"$d" ]; then
      mkdir $CMSIS_DSP_outSrc_path/"$d"
      echo "#include \"../Source/$d/$d.c\"" > $CMSIS_DSP_outSrc_path/"$d"/"$d".c
    fi
  done
fi
