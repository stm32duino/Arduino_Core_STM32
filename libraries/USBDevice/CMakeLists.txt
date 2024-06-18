# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(USBDevice INTERFACE)
add_library(USBDevice_usage INTERFACE)

target_include_directories(USBDevice_usage INTERFACE
  src
)


target_link_libraries(USBDevice_usage INTERFACE
  base_config
)

target_link_libraries(USBDevice INTERFACE USBDevice_usage)



add_library(USBDevice_bin OBJECT EXCLUDE_FROM_ALL
  src/cdc/cdc_queue.c
  src/cdc/usbd_cdc.c
  src/cdc/usbd_cdc_if.c
  src/hid/usbd_hid_composite.c
  src/hid/usbd_hid_composite_if.c
  src/usb_device_core.c
  src/usb_device_ctlreq.c
  src/usb_device_ioreq.c
  src/usbd_conf.c
  src/usbd_desc.c
  src/usbd_ep_conf.c
  src/usbd_if.c
  src/USBSerial.cpp
)
target_link_libraries(USBDevice_bin PUBLIC USBDevice_usage)

target_link_libraries(USBDevice INTERFACE
  USBDevice_bin
  $<TARGET_OBJECTS:USBDevice_bin>
)

