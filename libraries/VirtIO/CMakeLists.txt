# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(VirtIO INTERFACE)
add_library(VirtIO_usage INTERFACE)

target_include_directories(VirtIO_usage INTERFACE
  src
)


target_link_libraries(VirtIO_usage INTERFACE
  base_config
)

target_link_libraries(VirtIO INTERFACE VirtIO_usage)



add_library(VirtIO_bin OBJECT EXCLUDE_FROM_ALL
  src/libmetal/device.c
  src/libmetal/generic/condition.c
  src/libmetal/generic/cortexm/sys.c
  src/libmetal/generic/generic_device.c
  src/libmetal/generic/generic_init.c
  src/libmetal/generic/generic_io.c
  src/libmetal/generic/generic_shmem.c
  src/libmetal/generic/time.c
  src/libmetal/init.c
  src/libmetal/io.c
  src/libmetal/log.c
  src/libmetal/shmem.c
  src/mbox_ipcc.c
  src/open-amp/remoteproc/remoteproc_virtio.c
  src/open-amp/rpmsg/rpmsg.c
  src/open-amp/rpmsg/rpmsg_virtio.c
  src/openamp.c
  src/rsc_table.c
  src/virt_uart.c
  src/virtio/virtio.c
  src/virtio/virtqueue.c
  src/virtio_buffer.c
  src/virtio_log.c
  src/VirtIOSerial.cpp
)
target_link_libraries(VirtIO_bin PUBLIC VirtIO_usage)

target_link_libraries(VirtIO INTERFACE
  VirtIO_bin
  $<TARGET_OBJECTS:VirtIO_bin>
)

