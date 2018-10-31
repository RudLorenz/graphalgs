cmake_minimum_required(VERSION 3.12)
project(graphsalg)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wconversion \
 -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
  -D_FORTIFY_SOURCE=2")

add_executable(graphsalg main.cpp graph.h)
