cmake_minimum_required(VERSION 2.8)

project('Tetris')

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(SOURCE_FILES main.cpp)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

find_package(OpenGL REQUIRED)

find_package(SFML REQUIRED system window graphics audio network)

include_directories( ${OPENGL_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})

add_executable(pro ${SOURCE_FILES})

target_link_libraries(pro ${OPENGL_LIBRARIES} ${SFML_LIBRARIES})


