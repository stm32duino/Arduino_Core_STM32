# open-amp
This repository is the home for the Open Asymmetric Multi Processing (OpenAMP)
framework project. The OpenAMP framework provides software components that
enable development of software applications for Asymmetric Multiprocessing
(AMP) systems. The framework provides the following key capabilities.

1. Provides Life Cycle Management, and Inter Processor Communication
   capabilities for management of remote compute resources and their associated
   software contexts.
2. Provides a stand alone library usable with RTOS and Baremetal software
   environments
3. Compatibility with upstream Linux remoteproc and rpmsg components
4. Following AMP configurations supported
	a. Linux master/Generic(Baremetal) remote
	b. Generic(Baremetal) master/Linux remote
5. Proxy infrastructure and supplied demos showcase ability of proxy on master
   to handle printf, scanf, open, close, read, write calls from Bare metal
   based remote contexts.

## OpenAMP Source Structure
```
|- lib/
|  |- virtio/     # virtio implementation
|  |- rpmsg/      # rpmsg implementation
|  |- remoteproc/ # remoteproc implementation
|  |- proxy/      # implement one processor access device on the
|  |              # other processor with file operations
|- apps/        # demonstration/testing applications
|  |- examples/ # Application samples using the OpenAMP framework.
|  |- machine/  # common files for machine can be shared by applications
|  |            # It is up to each app to decide whether to use these files.
|  |- system/   # common files for system can be shared by applications
|               # It is up to each app to decide whether to use these files.
|- cmake        # CMake files
|- script       # helper scripts (such as checkpatch) for contributors.
```

OpenAMP library libopen_amp is composed of the following directories in `lib/`:
*   `virtio/`
*   `rpmsg/`
*   `remoteproc/`
*   `proxy/`

OpenAMP system/machine support has been moved to libmetal, the system/machine
layer in the `apps/` directory is for system application initialization, and
resource table definition.

### libmetal APIs used in OpenAMP
Here are the libmetal APIs used by OpenAMP, if you want to port OpenAMP for your
system, you will need to implement the following libmetal APIs in the libmetal's
`lib/system/<SYS>` directory:
* alloc, for memory allocation and memory free
* cache, for flushing cache and invalidating cache
* io, for memory mapping. OpenAMP required memory mapping in order to access
  vrings and carved out memory.
* irq, for IRQ handler registration, IRQ disable/enable and global IRQ handling.
* mutex
* shmem (For RTOS, you can usually use the implementation from
  `lib/system/generic/`)
* sleep, at the moment, OpenAMP only requires microseconds sleep as when OpenAMP
  fails to get a buffer to send messages, it will call this function to sleep and
  then try again.
* time, for timestamp
* init, for libmetal initialization.
* atomic

Please refer to `lib/system/generic` when you port libmetal for your system.

If you a different compiler to GNU gcc, please refer to `lib/compiler/gcc/` to
port libmetal for your compiler. At the moment, OpenAMP needs the atomic
operations defined in `lib/compiler/gcc/atomic.h`.

## OpenAMP Compilation
OpenAMP uses CMake for library and demonstration application compilation.
OpenAMP requires libmetal library. For now, you will need to download and
compile libmetal library separately before you compiling OpenAMP library.
In future, we will try to make libmetal as a submodule to OpenAMP to make this
flow easier.

Some Cmake options are available to allow user to customize to the OpenAMP
library for it project:
* **WITH_PROXY** (default OFF): Include proxy support in the library.
* **WITH APPS** (default OFF): Build with sample applications.
* **WITH_PROXY_APPS** (default OFF):Build with proxy sample applications.
* **WITH_VIRTIO_MASTER** (default ON): Build with virtio master enabled.
  This option can be set to OFF if the only the remote mode is implemented.
* **WITH_VIRTIO_SLAVE** (default ON): Build with virtio slave enabled.
  This option can be set to OFF if the only the master mode is implemented.
* **WITH_STATIC_LIB** (default ON): Build with a static library.
* **WITH_SHARED_LIB** (default ON): Build with a shared library.
* **WITH_ZEPHYR** (default OFF): Build open-amp as a zephyr library. This option
  is mandatory in a Zephyr environment.
* **WITH_DCACHE_VRINGS** (default OFF): Build with data cache operations
  enabled on vrings.
* **WITH_DCACHE_BUFFERS** (default OFF): Build with data cache operations
  enabled on buffers.
* **RPMSG_BUFFER_SIZE** (default 512): adjust the size of the RPMsg buffers.
  The default value of the RPMsg size is compatible with the Linux Kernel hard
  coded value. If you AMP configuration is Linux kernel master/ OpenAMP remote,
  this option must not be used.

### Example to compile OpenAMP for Zephyr
The [Zephyr open-amp repo](https://github.com/zephyrproject-rtos/open-amp)
implements the open-amp library for the Zephyr project. It is mainly a fork of
this repository, with some add-ons for integration in the Zephyr project.
The standard way to compile OpenAMP for a Zephyr project is to use Zephyr build
environment. Please refer to [Zephyr OpenAMP samples](https://github.com/zephyrproject-rtos/zephyr/tree/master/samples/subsys/ipc) for examples.

Nevertheless you can compile the OpenAMP project for Zephyr.
As OpenAMP uses libmetal, please refer to libmetal README to build libmetal
for Zephyr before building OpenAMP library for Zephyr.
As Zephyr uses CMake, we build OpenAMP library as a target of Zephyr CMake
project. Here is how to build libmetal for Zephyr:
```
    $ export ZEPHRY_GCC_VARIANT=zephyr
    $ export ZEPHRY_SDK_INSTALL_DIR=<where Zephyr SDK is installed>
    $ source <git_clone_zephyr_project_source_root>/zephyr-env.sh

    $ cmake <OpenAMP_source_root> \
      -DWITH_ZEPHYR=on -DBOARD=qemu_cortex_m3 \
      -DCMAKE_INCLUDE_PATH="<libmetal_zephyr_build_dir>/lib/include" \
      -DCMAKE_LIBRARY_PATH="<libmetal_zephyr_build_dir>/lib" \
    $ make VERBOSE=1 all
```

### Example to compile OpenAMP for communication between Linux processes:
* Install libsysfs devel and libhugetlbfs devel packages on your Linux host.
* build libmetal library on your host as follows:

    ```
        $ mkdir -p build-libmetal
        $ cd build-libmetal
        $ cmake <libmetal_source>
        $ make VERBOSE=1 DESTDIR=<libmetal_install> install
    ```

* build OpenAMP library on your host as follows:

        $ mkdir -p build-openamp
        $ cd build-openamp
        $ cmake <openamp_source> -DCMAKE_INCLUDE_PATH=<libmetal_built_include_dir> \
              -DCMAKE_LIBRARY_PATH=<libmetal_built_lib_dir> [-DWITH_APPS=ON]
        $ make VERBOSE=1 DESTDIR=$(pwd) install

The OpenAMP library will be generated to `build/usr/local/lib` directory,
headers will be generated to `build/usr/local/include` directory, and the
applications executable will be generated to `build/usr/local/bin`
directory.

* cmake option `-DWITH_APPS=ON` is to build the demonstration applications.
* If you have used `-DWITH_APPS=ON` to build the demos, you can try them on
  your Linux host as follows:

  * rpmsg echo demo:
    ```
    # Start echo test server to wait for message to echo
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build/usr/local/bin/rpmsg-echo-shared
    # Run echo test to send message to echo test server
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build/usr/local/bin/rpmsg-echo-ping-shared 1
    ```

  * rpmsg echo demo with the nocopy API:
    ```
    # Start echo test server to wait for message to echo
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build/usr/local/bin/rpmsg-nocopy-echo-shared
    # Run echo test to send message to echo test server
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build/usr/local/bin/rpmsg-nocopy-ping-shared 1
    ```

###  Example to compile Zynq UltraScale+ MPSoC R5 generic(baremetal) remote:
* build libmetal library on your host as follows:
  * Create your on cmake toolchain file to compile libmetal for your generic
    (baremetal) platform. Here is the example of the toolchain file:

    ```
        set (CMAKE_SYSTEM_PROCESSOR "arm"              CACHE STRING "")
        set (MACHINE "zynqmp_r5" CACHE STRING "")

        set (CROSS_PREFIX           "armr5-none-eabi-" CACHE STRING "")
        set (CMAKE_C_FLAGS          "-mfloat-abi=soft -mcpu=cortex-r5 -Wall -Werror -Wextra \
           -flto -Os -I/ws/xsdk/r5_0_bsp/psu_cortexr5_0/include" CACHE STRING "")

        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
        SET(CMAKE_AR  "gcc-ar" CACHE STRING "")
        SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
        SET(CMAKE_C_ARCHIVE_FINISH   true)

        include (cross-generic-gcc)
    ```

  * Compile libmetal library:

    ```
        $ mkdir -p build-libmetal
        $ cd build-libmetal
        $ cmake <libmetal_source> -DCMAKE_TOOLCHAIN_FILE=<toolchain_file>
        $ make VERBOSE=1 DESTDIR=<libmetal_install> install
    ```

* build OpenAMP library on your host as follows:
  * Create your on cmake toolchain file to compile openamp for your generic
    (baremetal) platform. Here is the example of the toolchain file:
    ```
        set (CMAKE_SYSTEM_PROCESSOR "arm" CACHE STRING "")
        set (MACHINE                "zynqmp_r5" CACHE STRING "")
        set (CROSS_PREFIX           "armr5-none-eabi-" CACHE STRING "")
        set (CMAKE_C_FLAGS          "-mfloat-abi=soft -mcpu=cortex-r5 -Os -flto \
          -I/ws/libmetal-r5-generic/usr/local/include \
          -I/ws/xsdk/r5_0_bsp/psu_cortexr5_0/include" CACHE STRING "")
        set (CMAKE_ASM_FLAGS        "-mfloat-abi=soft -mcpu=cortex-r5" CACHE STRING "")
        set (PLATFORM_LIB_DEPS      "-lxil -lc -lm" CACHE STRING "")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
        SET(CMAKE_AR  "gcc-ar" CACHE STRING "")
        SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
        SET(CMAKE_C_ARCHIVE_FINISH   true)
        set (CMAKE_FIND_ROOT_PATH /ws/libmetal-r5-generic/usr/local/lib \
            /ws/xsdk/r5_bsp/psu_cortexr5_0/lib )

        include (cross_generic_gcc)
    ```

  * We use cmake `find_path` and `find_library` to check if libmetal includes
    and libmetal library is in the includes and library search paths. However,
    for non-linux system, it doesn't work with `CMAKE_INCLUDE_PATH` and
    `CMAKE_LIBRARY_PATH` variables, and thus, we need to specify those paths
    in the toolchain file with `CMAKE_C_FLAGS` and `CMAKE_FIND_ROOT_PATH`.
* Compile the OpenAMP library:

    ```
    $ mkdir -p build-openamp
    $ cd build-openamp
    $ cmake <openamp_source> -DCMAKE_TOOLCHAIN_FILE=<toolchain_file>
    $ make VERBOSE=1 DESTDIR=$(pwd) install
    ```

The OpenAMP library will be generated to `build/usr/local/lib` directory,
headers will be generated to `build/usr/local/include` directory, and the
applications executable will be generated to `build/usr/local/bin`
directory.


### Example to compile OpenAMP Linux Userspace for Zynq UltraScale+ MPSoC
We can use yocto to build the OpenAMP Linux userspace library and application.
open-amp and libmetal recipes are in this yocto layer:
https://github.com/OpenAMP/meta-openamp
* Add the `meta-openamp` layer to your layers in your yocto build project's `bblayers.conf` file.
* Add `libmetal` and `open-amp` to your packages list. E.g. add `libmetal` and `open-amp` to the
  `IMAGE_INSTALL_append` in the `local.conf` file.
* You can also add OpenAMP demos Linux applications packages to your yocto packages list. OpenAMP
  demo examples recipes are also in `meta-openamp`:
  https://github.com/OpenAMP/meta-openamp/tree/master/recipes-openamp/openamp-examples

In order to user OpenAMP(RPMsg) in Linux userspace, you will need to have put the IPI device,
  vring memory and shared buffer memory to your Linux kernel device tree. The device tree example
  can be found here:
  https://github.com/OpenAMP/open-amp/blob/master/apps/machine/zynqmp/openamp-linux-userspace.dtsi

## Version
The OpenAMP version follows the set of rule proposed in [Semantic Versioning specification](https://semver.org/).

## Supported System and Machines
For now, it supports:
* Zynq generic slave
* Zynq UltraScale+ MPSoC R5 generic slave
* Linux host OpenAMP between Linux userspace processes
* Linux userspace OpenAMP RPMsg master
* Linux userspace OpenAMP RPMsg slave
* Linux userspace OpenAMP RPMsg and MicroBlaze bare metal remote

## Known Limitations:
1. In case of OpenAMP on Linux userspace for inter processors communication,
   it only supports static vrings and shared buffers.
2. `sudo` is required to run the OpenAMP demos between Linux processes, as
   it doesn't work on some systems if you are normal users.

## How to contribute:
As an open-source project, we welcome and encourage the community to submit patches directly to the project. As a contributor you  should be familiar with common developer tools such as Git and CMake, and platforms such as GitHub.
Then following points should be rescpected to facilitate the review process.

### Licencing
Code is contributed to the Linux kernel under a number of licenses, but all code must be compatible with version the [BSD License](https://github.com/OpenAMP/open-amp/blob/master/LICENSE.md), which is the license covering the OpenAMP distribution as a whole. In practice, use the following tag instead of the full license text in the individual files:

    ```
    SPDX-License-Identifier:    BSD-3-Clause
    SPDX-License-Identifier:    BSD-2-Clause
    ```
### Signed-off-by
Commit message must contain Signed-off-by: line and your email must match the change authorship information. Make sure your .gitconfig is set up correctly:

    ```
    git config --global user.name "first-name Last-Namer"
    git config --global user.email "yourmail@company.com"
    ```
### gitlint
Before you submit a pull request to the project, verify your commit messages meet the requirements. The check can be  performed locally using the the gitlint command.

Run gitlint locally in your tree and branch where your patches have been committed:

      ```gitlint```
Note, gitlint only checks HEAD (the most recent commit), so you should run it after each commit, or use the --commits option to specify a commit range covering all the development patches to be submitted.

### Code style
In general, follow the Linux kernel coding style, with the following exceptions:

* Use /**  */ for doxygen comments that need to appear in the documentation.

The Linux kernel GPL-licensed tool checkpatch is used to check coding style conformity.Checkpatch is available in the scripts directory.

To check your \<n\> commits in your git branch:
   ```
   ./scripts/checkpatch.pl --strict  -g HEAD-<n>

   ```
### Send a pull request
We use standard github mechanism for pull request. Please refer to github documentation for help.

## Communication and Collaboration
[Subscribe](https://lists.openampproject.org/mailman/listinfo/openamp-rp) to the OpenAMP mailing list(openamp-rp@lists.openampproject.org).

For more details on the framework please refer to the the [OpenAMP wiki](https://github.com/OpenAMP/open-amp/wiki).
