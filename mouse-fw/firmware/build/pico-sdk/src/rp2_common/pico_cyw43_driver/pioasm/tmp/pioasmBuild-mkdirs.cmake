# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "G:/etran/dev/pico/mouse-fw/firmware/pico-sdk/tools/pioasm"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pioasm"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pioasm-install"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "G:/etran/dev/pico/mouse-fw/firmware/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
