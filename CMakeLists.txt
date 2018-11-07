cmake_minimum_required(VERSION 3.10)
project(graphsalg)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wconversion \
 -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
  -D_FORTIFY_SOURCE=2")

endif()

add_executable(graphsalg main.cpp src/graph.h src/vertex.h)
