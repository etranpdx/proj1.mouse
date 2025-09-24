# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "G:/etran/dev/pico/mouse-fw/firmware/build/_deps/picotool-src"
  "G:/etran/dev/pico/mouse-fw/firmware/build/_deps/picotool-build"
  "G:/etran/dev/pico/mouse-fw/firmware/build/_deps"
  "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/tmp"
  "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/src/picotoolBuild-stamp"
  "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/src"
  "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "G:/etran/dev/pico/mouse-fw/firmware/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
