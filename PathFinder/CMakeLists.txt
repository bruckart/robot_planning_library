


cmake_minimum_required(VERSION 3.20.4)

project(PathFinder VERSION 1.0.0 LANGUAGES CXX)


# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

# find_package(Qt5Widgets REQUIRED)
# find_package(Qt5Core REQUIRED)
# find_package(Qt5OpenGL REQUIRED)

# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)

# Find includes in corresponding build directories.
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOUIC ON)

# Instruct Cmake to run automatically when needed.
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)


set(_INCLUDE_DIRS
    # GL
    # /usr/include
    # Qt5
    # ${Qt5Widgets_INCLUDES}
    # local
    ${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${_INCLUDE_DIRS}
                    # ${PROJECT_SOURCE_DIR}
                    # ${PROJECT_BINARY_DIR}
                    # ${OPENGL_INCLUDE_DIRS} 
                    # ${GLUT_INCLUDE_DIRS})
)

# set(_UI
#     ${CMAKE_CURRENT_LIST_DIR}/src/MainWindow.ui
#     ${CMAKE_CURRENT_LIST_DIR}/src/MyOpenGLWidget.ui
# )

set(_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/PathFinder.h
)

set(_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/PathFinder.cpp
)

# qt5_wrap_cpp(qtHelloWorld_header_moc ${_HEADERS})
# qt5_wrap_ui(qtHelloWorld_ui_moc ${_UI})


# add_executable(shield.ai
#     ${qtHelloWorld_header_moc}
#     ${qtHelloWorld_ui_moc}
#     ${_SOURCES}
#     ${CMAKE_CURRENT_LIST_DIR}/resources/shaders.qrc
#     ${CMAKE_CURRENT_LIST_DIR}/resources/textures.qrc)

# target_include_directories(shield.ai PUBLIC ${_INCLUDE_DIRS})
# target_link_libraries(shield.ai 
    # dl
    # nsl
    # m
    # rt
    # pthread
    # ssl
    # stdc++
    # glut
    # GLU
    # GL
    # Qt5::OpenGL
    # ${OPENGL_LIBRARY}
    # ${GLUT_LIBRARY}
    # ${Qt5Widgets_LIBRARIES}
    # Qt5::Core
    # Qt5::Gui
    # Qt5::Widgets)
# )

add_library(PathFinder SHARED
    ${_SOURCES}
    # ${qtHelloWorld_header_moc}
    # ${qtHelloWorld_ui_moc})
)
# target_link_libraries(qtHelloWorldLib Qt5::Widgets)

if (CMAKE_TESTING_ENABLED)
    add_subdirectory(test)
endif()







# enable_testing()
# find_package(Gtest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../googletest-master/googletest/mybuild)
# add_executable(test_qtHelloWorld ${CMAKE_CURRENT_LIST_DIR}/src/TestMidiFile.cpp)
# target_link_libraries(test_qtHelloWorld gtest gtest_main)
# target_link_libraries(test_qtHelloWorld qtHelloWorldLib)

# add_test(MidiFile test_qtHelloWorld)

# add_subdirectory(test)
