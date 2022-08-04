cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH $ENV{SDK_PATH}/pico-sdk)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(pico_sdk_import.cmake)

project(PiPicoESC)

pico_sdk_init()

add_executable(controller
    src/controller.c
)

target_link_libraries(controller pico_stdlib hardware_gpio hardware_pwm)

pico_add_extra_outputs(controller)
pico_enable_stdio_usb(controller 1)
pico_enable_stdio_uart(controller 0)

add_custom_target(flash ALL ${CMAKE_SOURCE_DIR}/pi_flash.sh
    DEPENDS controller)
