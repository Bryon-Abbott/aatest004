
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

#add_subdirectory(ext/aafsm)
#add_subdirectory(ext/aaled)

# include to point to machine/endian.h
INCLUDE_DIRECTORIES("/home/bryon/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/xtensa-esp32-elf/sys-include"
                    "/home/bryon/AbbottCode/AAIoT/aatest001/ext/aafsm/src"
                    "/home/bryon/AbbottCode/AAIoT/aatest001/ext/aaled/src")

set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/led_strip)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(test001) 

# add_executable(${PROJECT_NAME} test001.c)  
