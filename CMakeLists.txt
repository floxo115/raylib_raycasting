cmake_minimum_required(VERSION 3.30)
project(myraylib C)

set(CMAKE_C_STANDARD 17)
add_subdirectory(extern/raylib)

add_executable(myraylib main.c
        bernoulli.c
        bernoulli.h)
target_link_libraries(myraylib PRIVATE raylib)
target_compile_options(myraylib PRIVATE ${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -pedantic-errors -Wshadow -Wcast-align -Wcast-qual -Wconversion -Wsign-conversion -Wformat=2 -Wundef -Wimplicit-fallthrough -Wlogical-op -Wnull-dereference -Wredundant-decls -fstack-protector-strong -D_FORTIFY_SOURCE=2)
