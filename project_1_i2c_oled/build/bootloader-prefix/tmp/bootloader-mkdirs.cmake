# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/senggee/esp/esp-idf/components/bootloader/subproject"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/tmp"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/src"
  "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/senggee/esp/ESP32C6_Projects/project_1_i2c_oled/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
