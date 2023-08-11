add_library(
        Source
        scanner.c
        token.c
        byte.c)

add_executable(Main assembler.c)

set_property(TARGET Main PROPERTY C_STANDARD 23)

target_link_libraries(Main Source)
