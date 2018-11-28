cmake_minimum_required(VERSION 3.10)
project(graph_lib)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(graph_lib "")

target_sources(graph_lib
    PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/graph.h
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/vertex.h 
    ${CMAKE_SOURCE_DIR}/src/graph.cpp
    ${CMAKE_SOURCE_DIR}/src/vertex.cpp)

target_include_directories(graph_lib
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

