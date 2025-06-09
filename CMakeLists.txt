cmake_minimum_required(VERSION 4.0)

project( cpp-atom )

find_package(OpenGL REQUIRED)


add_subdirectory( glfw-3.4 )

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/glad.c 
    src/Shader.cpp 
    src/Vector3.cpp 
    src/Particle.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
