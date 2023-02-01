target_sources(esc PRIVATE
    main.cpp
    uart_io/uart_io.cpp
    )

add_subdirectory(motor_drive)
