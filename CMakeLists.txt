cmake_minimum_required(VERSION 3.20)
project(opengl_starter)

set(CMAKE_CXX_STANDARD 23)

add_executable(opengl_starter main.cpp glad.c draw.cpp draw.h)
target_link_libraries(opengl_starter ${CMAKE_DL_LIBS})
target_link_libraries(opengl_starter GLEW glfw GL X11 pthread Xrandr Xi)