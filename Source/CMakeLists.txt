add_library(AssemblerSource
        scanner.c
        vm.c
        compiler.c
        token.c
        byte.c
)

add_library(VMSource vm.c)

add_executable(Assembler assembler.c)
add_executable(VirtualMachine main.c)

target_link_libraries(Assembler AssemblerSource)
target_link_libraries(VirtualMachine VMSource)
