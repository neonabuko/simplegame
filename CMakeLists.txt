cmake_minimum_required(VERSION 3.26)
project(simplegame)

set(CMAKE_CXX_STANDARD 23)

# Look for any version of SFML
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(simplegame 
    src/main.cpp 
    src/entity/Entity.cpp
    src/entity/Laser.cpp
    src/collision/CollisionDetection.cpp
    src/entity/Enemy.cpp
    src/include/Enemy.h
    src/include/Entity.h
    src/include/Laser.h
    src/include/GameAssets.h
    src/include/PlayerAssets.h
    src/include/LaserAssets.h
    src/include/CollisionDetection.h
    src/include/EnemyAssets.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(VALGRIND "valgrind")

# Link with SFML libraries
target_link_libraries(simplegame sfml-graphics sfml-audio)
