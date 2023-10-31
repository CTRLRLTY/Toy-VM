add_library(AssemblerSource
        scanner.c
        compiler.c
        token.c
        byte.c
)

add_library(VMSource 
        vm.c
        context.c
)

add_subdirectory(Context)

add_executable(Assembler assembler.c)
add_executable(VirtualMachine main.c)

target_link_libraries(Assembler 
        VMSource 
        AssemblerSource
        ContextLib
)

target_link_libraries(VirtualMachine 
        VMSource
        ContextLib
)
