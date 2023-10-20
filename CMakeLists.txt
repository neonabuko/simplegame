cmake_minimum_required(VERSION 3.26)
project(simplegame)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(simplegame main.cpp)

target_link_libraries(simplegame sfml-graphics)

