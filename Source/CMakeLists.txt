add_library(
        Source
        scanner.c
        token.c
        byte.c)

add_executable(Main assembler.c)

target_link_libraries(Main Source)
