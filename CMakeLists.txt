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

cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH $ENV{SDK_PATH}/pico-sdk)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(pico_sdk_import.cmake)

project(PiPicoESC)

pico_sdk_init()

add_executable(controller
    src/main.cpp
    src/states.cpp
)

target_link_libraries(controller pico_stdlib hardware_gpio hardware_pwm)

pico_add_extra_outputs(controller)
pico_enable_stdio_usb(controller 1)
pico_enable_stdio_uart(controller 0)

add_custom_target(flash ALL ${CMAKE_SOURCE_DIR}/pi_flash.sh
    DEPENDS controller)
