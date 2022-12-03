#  ____  _ ____  _           _____ ____   ____
# |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
# | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
# |  __/| |  __/| | (_| (_) | |___ ___) | |___
# |_|   |_|_|   |_|\___\___/|_____|____/ \____|
#
# ==== CMakeLists.txt ====
#
# Authors: Oran Ellis, Karl Hartmann
# Licence: GPLv3

# set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH $ENV{SDK_PATH}/pico-sdk)
include(pico_sdk_import.cmake)
pico_sdk_init()

project(PiPicoESC)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(esc
    main.cpp
    schemes/sin/states.cpp
)

target_include_directories(esc PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(esc pico_stdlib hardware_gpio hardware_pwm pico_multicore)

pico_add_extra_outputs(esc)
pico_enable_stdio_usb(esc 1)
pico_enable_stdio_uart(esc 0)

add_custom_target(flash ALL ${CMAKE_SOURCE_DIR}/pi_flash.sh
    DEPENDS esc)
