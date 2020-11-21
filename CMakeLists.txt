cmake_minimum_required(VERSION 3.10)
project(graphsalg)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(include)

add_executable(graphsalg main.cpp)

target_link_libraries(graphsalg graph_lib)

target_compile_options(graphsalg PRIVATE
        $<$<CONFIG:Debug>:
            $<$<CXX_COMPILER_ID:Clang>: -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -g>
            $<$<CXX_COMPILER_ID:GNU>: -Wall -Wextra -pedantic -ggdb -Wformat=2 -Wconversion -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2>>
        $<$<CONFIG:Release>: -DNDEBUG -march=native>)

target_link_options(graphsalg PRIVATE $<$<CONFIG:Debug>: -fno-omit-frame-pointer>)
