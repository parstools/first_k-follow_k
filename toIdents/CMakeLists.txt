cmake_minimum_required(VERSION 3.21)
project(toIdents)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-Werror=return-type")

add_executable(toIdents main.cpp)

target_link_libraries(toIdents
        boost_system
        boost_filesystem)
