cmake_minimum_required(VERSION 3.15.0)
project(GameEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory("ext")
add_subdirectory("engine")
add_subdirectory("examples")
add_subdirectory("sandboxes")

