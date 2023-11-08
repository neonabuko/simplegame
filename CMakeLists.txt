cmake_minimum_required(VERSION 3.26)
project(simplegame)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(simplegame 
src/main.cpp 
src/entity/Entity.cpp
src/entity/Laser.cpp
src/include/Entity.h
src/include/Laser.h
src/include/GameAssets.h
src/include/PlayerAssets.h
src/include/LaserAssets.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(VALGRIND "valgrind")

target_link_libraries(simplegame sfml-graphics)
target_link_libraries(simplegame sfml-audio)