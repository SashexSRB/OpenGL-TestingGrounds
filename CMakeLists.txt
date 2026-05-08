cmake_minimum_required(VERSION 4.2)
project(doot C)

set(CMAKE_C_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(doot main.c)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(doot ${OPENGL_LIBRARIES} /usr/lib/x86_64-linux-gnu/libglut.so)
