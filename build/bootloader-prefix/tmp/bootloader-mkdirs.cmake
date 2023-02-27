# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/Espressif/esp-idf/components/bootloader/subproject"
  "D:/espidf/Power_Board/build/bootloader"
  "D:/espidf/Power_Board/build/bootloader-prefix"
  "D:/espidf/Power_Board/build/bootloader-prefix/tmp"
  "D:/espidf/Power_Board/build/bootloader-prefix/src/bootloader-stamp"
  "D:/espidf/Power_Board/build/bootloader-prefix/src"
  "D:/espidf/Power_Board/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/espidf/Power_Board/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/espidf/Power_Board/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
