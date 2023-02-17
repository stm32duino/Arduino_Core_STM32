# OpenAMP MicroBlaze example

The microblaze_generic directories in OpenAMP repository provide an
implementation of rpmsg for Xilinx MicroBlaze design
example. The design instantiates Xilinx MicroBlaze soft processor in
ZynqMP's programmable logic (PL) and uses the processing system (PS)
DDR memory for its text and data. The HP0_DDR_LOW is mapped from 0 to
0x7FFFFFFF. The Local Memory Bus (LMB) is not connected and the LMB
memory is not present. The MicroBlaze Vector Base Address is set to
0x70000000 and its reset_mode (01) will force it to enter sleep mode
without performing any bus access. The design is available in the Xilinx
Shell Archive (XSA) format at https://xilinx-wiki.atlassian.net

## How to build OpenAMP echo server for the MicroBlaze design example.
For simplicity the example is not using Inter-Processor Interrupt (IPI)
hardware at this time and the MicroBlaze OpenAMP echo server is built
with RPMSG_NO_IPI flag.

* build the libmetal library on your host as follows:
  * Create your own cmake toolchain file to compile libmetal for your generic
    (baremetal) platform. Here is an example toolchain file:

    ```
        set (BSP  "/path/to/your_MicroBlaze_design_BSP/dir" CACHE STRING "")
        set (CMAKE_SYSTEM_PROCESSOR           "microblaze"  CACHE STRING "")
        set (MACHINE           "microblaze_generic"         CACHE STRING "")
        set (CROSS_PREFIX          "microblaze-xilinx-elf-" CACHE STRING "")
        set (CMAKE_C_FLAGS "-g -mlittle-endian -mxl-soft-mul -Wall -Werror \
                       "-Wextra -flto -Os -I${BSP}/include" CACHE STRING "")
        link_directories( ${BSP}/lib )
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
        SET(CMAKE_AR  "gcc-ar" CACHE STRING "")
        SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
        SET(CMAKE_C_ARCHIVE_FINISH   true)
        include (cross-generic-gcc)
    ```

  * Compile the libmetal library:

    ```
        $ mkdir -p build-libmetal
        $ cd build-libmetal
        $ BSP="/path/to/your_MicroBlaze_design_BSP/dir"
        $ cmake <libmetal_source> -DCMAKE_TOOLCHAIN_FILE=<toolchain_file> \
                -DCMAKE_LIBRARY_PATH=$BSP/lib
        $ make VERBOSE=1 DESTDIR=<libmetal_install> install
    ```

* build the OpenAMP library on your host as follows:
  * Create your own cmake toolchain file to compile openamp for your generic
    (baremetal) platform. Here is an example toolchain file:
    ```
        set (BSP  "/path/to/your_MicroBlaze_design_BSP/dir" CACHE STRING "")
        set (CMAKE_SYSTEM_PROCESSOR           "microblaze"  CACHE STRING "")
        set (MACHINE           "microblaze_generic"         CACHE STRING "")
        set (CROSS_PREFIX          "microblaze-xilinx-elf-" CACHE STRING "")
        set (CMAKE_C_FLAGS "-g -mlittle-endian -Wall -Wextra -flto -Os \
                -DUNDEFINE_FILE_OPS -DRPMSG_NO_IPI -I${LIBMETAL}/include \
                -I${BSP}/include" CACHE STRING "")

        set (PLATFORM_LIB_DEPS     "-lxil -lc -lm -lmetal " CACHE STRING "")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
        SET(CMAKE_AR  "gcc-ar" CACHE STRING "")
        SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
        SET(CMAKE_C_ARCHIVE_FINISH   true)
        link_directories(${LIBMETAL}/include/ ${LIBMETAL}/lib/)
        set (CMAKE_FIND_ROOT_PATH ${LIBMETAL}/lib  ${BSP}/lib )
        include (cross-generic-gcc)
    ```

  * We use cmake `find_path` and `find_library` to check if libmetal headers
    and library are in the includes and library search paths. However,
    for non-linux system, it doesn't work with `CMAKE_INCLUDE_PATH` and
    `CMAKE_LIBRARY_PATH` variables, and thus, we need to specify those paths
    in the toolchain file with `CMAKE_C_FLAGS` and `CMAKE_FIND_ROOT_PATH`.

* Compile the OpenAMP library:

    ```
    $ mkdir -p build-openamp
    $ cd build-openamp
    $ BSP="/path/to/your_MicroBlaze_design_BSP/dir"

    $ cmake <openamp_source> -DCMAKE_TOOLCHAIN_FILE=<toolchain_file> \
        -DCMAKE_INCLUDE_PATH="$LIBMETAL/include;$BSP/include" \
        -DCMAKE_LIBRARY_PATH="$LIBMETAL/lib/;BSP/lib"  -DWITH_APPS=on
    $ make VERBOSE=1 DESTDIR=$(pwd) install
    ```

The OpenAMP library will be built in `build/usr/local/lib` directory,
headers will be built in `build/usr/local/include` directory, and the
application executable will be built in `build/usr/local/bin` directory.

## How to build OpenAMP Linux Userspace echo Client for ZynqMP MPSoC

To test the MicroBlaze echo server we use an rpmsg-echo-ping client from
Linux running on the Application Processing Unit (APU) in PS. To run both
the echo server on the MicroBlaze in PL from PS DDR and a Linux echo
client on APU in PS the kernel device tree needs reserved-memory nodes
for the MicroBlaze text and data including vrings. A Yocto overlay
device tree example: openamp-linux-u-MicroBlaze.dtsi

Build the OpenAMP Linux userspace library and application via Yocto.
The open-amp and libmetal recipes are in this Yocto layer:
    https://github.com/OpenAMP/meta-openamp

* Add the `meta-openamp` layer to your layers in your Yocto build project's
  `bblayers.conf` file.
* Add `libmetal` and `open-amp` to your packages list. E.g. add `libmetal`
  and `open-amp` to the `IMAGE_INSTALL_append` in the `local.conf` file.
* You can also add OpenAMP demos Linux applications packages to your Yocto
  packages list. OpenAMP demo examples recipes are also in `meta-openamp`:
  https://github.com/OpenAMP/meta-openamp/tree/master/recipes-openamp/openamp-examples

## Sample Microblaze DTSI


	/ {
		reserved-memory {
			#address-cells = <2>;
			#size-cells = <2>;
			ranges;
			rproc_0_reserved: rproc@3ed000000 {
				no-map;
				reg = <0x0 0x3ed00000 0x0 0x1000000>;
			};
			microblaze_text_data: microblaze:@70000000 {
				no-map;
				reg = <0x0 0x70000000 0x0 0x80000>;
			};
		};

		amba {
			vring: vring@0 {
				compatible = "vring_uio";
				reg = <0x0 0x3ed40000 0x0 0x40000>;
			};
			shm0: shm@0 {
				compatible = "shm_uio";
				reg = <0x0 0x3ed20000 0x0 0x0100000>;
			};
			shm1: shm@1 {
				compatible = "shm_uio";
				reg = <0x0 0x3ee40000 0x0 0x0100000>;
			};
			ipi0: ipi@0 {
				compatible = "ipi_uio";
				reg = <0x0 0xff340000 0x0 0x1000>;
				interrupt-parent = <&gic>;
				interrupts = <0 29 4>;
			};
		};
	};
