add_library(
        AssemblerSource
        scanner.c
        token.c
        byte.c)

add_library(
        VMSource 
        compiler.c
        byte.c
        vm.c
        )

add_executable(Assembler assembler.c)
add_executable(VirtualMachine main.c)

target_link_libraries(Assembler AssemblerSource)
target_link_libraries(VirtualMachine VMSource)
