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

# Auto download the Pico SDK where required
set(PICO_SDK_FETCH_FROM_GIT on)

# Download and source the Pico SDK
include(pico_sdk_import.cmake)

project(PiPicoESC)

# Initialise the Pico SDK
pico_sdk_init()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(esc)
add_subdirectory(src)

target_include_directories(esc PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(esc pico_stdlib hardware_gpio hardware_pwm pico_multicore pico_stdio_uart)

# Expand outputs, enable serial over USB, disable serial over GPIO UART
pico_add_extra_outputs(esc)
pico_enable_stdio_usb(esc 1)
pico_enable_stdio_uart(esc 0)

# Custom linux Pi Pico flashing script
add_custom_target(flash ALL ${CMAKE_SOURCE_DIR}/pi_flash.sh
    DEPENDS esc)
