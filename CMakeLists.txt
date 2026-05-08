cmake_minimum_required(VERSION 4.2)
project(doot C)
set(CMAKE_C_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(doot main.c
        renderer.h
        renderer.c
        glHelpers.h
        glHelpers.c
        vector.h
        matrix.h
        vector.c
        matrix.c
        tesseractTest.h)

target_link_libraries(doot PRIVATE OpenGL::GL GLEW::GLEW glfw m)

