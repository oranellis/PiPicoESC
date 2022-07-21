cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
set(PICO_SDK_PATH ~/Dev/pico-sdk)

include(pico_sdk_import.cmake)

project(PiPicoESC)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(controller
    src/controller.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(controller pico_stdlib hardware_gpio hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(controller)
