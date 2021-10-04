

cmake_minimum_required(VERSION 3.20.4)

project(TestPathFinder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")
# set(GoogleTest_DIR /Users/robert/git/googletest/_build)
# set(GTEST_ROOT "/Users/robert/git/googletest/googletest" CACHE PATH "path to gtest"). 

find_package(GTest REQUIRED)
# if (NOT GTest_FOUND)
#     message(FATAL_ERROR "Cannot find Google Test Framework!")
# endif()
# message(STATUS "GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIRS}")
# message(STATUS "GTEST_INCLUDE_DIR=${GoogleTest_INCLUDE_DIRS}")


set(_INCLUDE_DIRS
    # GL
    # /usr/include
    # Qt5
    # ${Qt5Widgets_INCLUDES}
    # local
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${GTEST_INCLUDE_DIRS}
    # /Users/robert/git/googletest/googletest/include
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
# target_link_libraries(testPathFinder GTest::gtest GTest::gtest_main)

add_test(TestPathFinder testPathFinder)
