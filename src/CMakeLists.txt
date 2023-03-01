target_sources(esc PRIVATE
    main.cpp
    )

add_subdirectory(control_logic)
add_subdirectory(motor_drive)
add_subdirectory(uart_io)
