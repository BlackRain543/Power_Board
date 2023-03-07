# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/espidf/vscode-esp/esp-idf-v5.0/components/bootloader/subproject"
  "D:/Espidf/Projects/Power_Board/build/bootloader"
  "D:/Espidf/Projects/Power_Board/build/bootloader-prefix"
  "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/tmp"
  "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/src"
  "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Espidf/Projects/Power_Board/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
