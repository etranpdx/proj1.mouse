cmake_minimum_required(VERSION 3.13)


# 1) Loads the Pico SDK that was vendored as a submodule in ./pico-sdk
include(pico-sdk/pico_sdk_init.cmake)

# 2) Start project named mouse_fw that uses C CXX by default + turns on Pico toolbox
project(mouse_fw)
pico_sdk_init()

# 3) Define the executable target + add source files to this target
add_executable(mouse_fw)

target_sources(mouse_fw PUBLIC
    src/main.c
)

# 4) Lets code in 'include/' be visible, so TinyUSB can find tusb_config.h
target_include_directories(mouse_fw PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# 5) Links core Pico libraries to use SDK functions
target_link_libraries(mouse_fw 
    pico_stdlib

)

# 7) Enable helful warnings for this target
target_compile_options(mouse_fw PUBLIC -Wall -Wextra)

# ) Turn on USB-serial + off the UART pins for printf/scanf
pico_enable_stdio_usb(mouse_fw 1)
pico_enable_stdio_uart(mouse_fw 0)


# 8) Uses RP2040 USB enumeration fix
target_compile_definitions(mouse_fw PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)


# 9) Tell the build to also make a .uf2 file for flashing
pico_add_extra_outputs(mouse_fw)