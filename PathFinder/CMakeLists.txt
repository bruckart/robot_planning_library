


cmake_minimum_required(VERSION 3.20.4)

project(PathFinder VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${_INCLUDE_DIRS}
)

set(_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/PathFinder.h
)

set(_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/PathFinder.cpp
)

add_library(PathFinder SHARED
    ${_SOURCES}
)

if (CMAKE_TESTING_ENABLED)
    add_subdirectory(test)
endif()
