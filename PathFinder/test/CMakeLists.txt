

cmake_minimum_required(VERSION 3.20.4)

project(TestPathFinder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${GTEST_INCLUDE_DIRS}
)

include_directories(${_INCLUDE_DIRS})


set(_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/TestPathFinder.cpp
)

add_executable(testPathFinder ${_SOURCES})
target_link_libraries(testPathFinder
    PathFinder
    GTest::gtest
)

add_test(TestPathFinder testPathFinder)
