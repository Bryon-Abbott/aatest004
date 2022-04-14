# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.18.0)


#find_package(Protobuf REQUIRED)
#ADD_SUBDIRECTORY(aaproto)

# include to point to machine/endian.h
INCLUDE_DIRECTORIES("/home/bryon/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/xtensa-esp32-elf/sys-include"
                    "/home/bryon/esp/v4/esp-idf/examples/common_components/protocol_examples_common/include"
                    "/home/bryon/AbbottCode/AAIoT/aaclient/aatest003/ext/aafsm/src"
                    "/home/bryon/AbbottCode/AAIoT/aaclient/aatest003/ext/aaled/src")

set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common ext)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

#add_subdirectory(ext/aafsm)
#add_subdirectory(ext/aaled)

project(test003) 
