cmake_minimum_required(VERSION 3.23)
project(FindPackageTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_find test_main.cpp)

# Include FetchContent module
include(FetchContent)

# Fetch the library
FetchContent_Declare(
    ActiveObject
    GIT_REPOSITORY https://github.com/maxw1990/ActiveObject.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(ActiveObject)

target_link_libraries(test_find PRIVATE ActiveObject::ActiveObject)