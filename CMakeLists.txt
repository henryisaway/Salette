cmake_minimum_required(VERSION 3.10)
project(Mira)
cmake_policy(SET CMP0072 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_Package(OpenGL REQUIRED)

# Include GLFW
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glfw")
include_directories(${GLFW_ROOT}/include)

# Link GLFW
link_directories(${GLFW_ROOT}/lib)

#include GLAD
set(GLAD_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glad")
include_directories(${GLAD_ROOT}/include)

#include GLM
set(GLM_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glm")
include_directories(${GLM_ROOT}/include)

# Add executable
add_executable(Mira
            src/config.h
            src/config.cpp
            src/main.cpp
            src/glad.c
            )

# Link libraries
target_link_libraries(Mira glfw OpenGL::GL)
