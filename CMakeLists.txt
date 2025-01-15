cmake_minimum_required(VERSION 3.10)
project(Jynx)
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
add_executable(Jynx
            include/core/config.h
            src/core/config.cpp
            main.cpp
            dependencies/glad/src/glad.c
            src/events/inputHandler.cpp
            src/shader/shaderLinker.cpp
            src/factory/factory.cpp
            src/renderer/OpenGLRenderContext.cpp
            src/core/app.cpp
            )

# Link libraries
target_link_libraries(Jynx glfw OpenGL::GL)

# --- Google Tests ---
enable_testing()

add_executable(Tests 
            tests/testmain.cpp
            tests/windowmanager/OpenGLWindowHandleTest.cpp
            src/windowmanager/OpenGLWindowHandle.cpp
            )
target_link_libraries(Tests gtest gtest_main pthread glfw)
add_test(NAME Tests COMMAND Tests)