add_library(
        Source
        scanner.c
        token.c
        byte.c)

add_executable(Assembler assembler.c)

target_link_libraries(Assembler Source)
