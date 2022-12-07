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

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(serial_tester
    main.cpp
)

target_include_directories(serial_tester PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(serial_tester)
