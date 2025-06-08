cmake_minimum_required(VERSION 4.0)

project( cpp-atom )

find_package(OpenGL REQUIRED)


add_subdirectory( glfw-3.4 )

add_executable(cpp-atom main.cpp)

target_link_libraries(cpp-atom glfw OpenGL::GL)
