cmake_minimum_required(VERSION 3.23)
project(FindPackageTest LANGUAGES CXX)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../install/ ${CMAKE_PREFIX_PATH})

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

find_package(ActiveObject 0.0.1 REQUIRED)

add_executable(test_find test_main.cpp)
target_link_libraries(test_find PRIVATE ActiveObject::ActiveObject)