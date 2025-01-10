cmake_minimum_required(VERSION 3.10)
project(MCLSimulation)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED graphics window system)

add_executable(mcl_simulation src/main.cpp)

target_link_libraries(mcl_simulation sfml-graphics sfml-window sfml-system)
