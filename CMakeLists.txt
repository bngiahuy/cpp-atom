cmake_minimum_required(VERSION 4.0)

project( cpp-atom )

find_package(OpenGL REQUIRED)


add_subdirectory( glfw-3.4 )

add_executable(${PROJECT_NAME} main.cpp glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include # Points to your_project/include/
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
