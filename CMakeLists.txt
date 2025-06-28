cmake_minimum_required(VERSION 3.10)
project(Vista)
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
add_executable(Vista
            include/core/config.h
            src/core/config.cpp
            main.cpp
            dependencies/glad/src/glad.c
            src/events/inputHandler.cpp
            src/shader/shaderLinker.cpp
            src/windowmanager/OpenGLWindowHandle.cpp
            src/windowmanager/WindowManager.cpp
            src/factory/PrimitiveModelFactory.cpp
            src/renderer/PrimitiveModel.cpp
            src/renderer/OpenGLRenderer.cpp
            src/core/app.cpp
            )

# Link libraries
target_link_libraries(Vista glfw OpenGL::GL)

# --- Google Tests ---
enable_testing()

add_executable(Tests 
            include/core/config.h
            src/core/config.cpp
            gtests/gtestmain.cpp
            dependencies/glad/src/glad.c
            src/windowmanager/OpenGLWindowHandle.cpp
            src/windowmanager/WindowManager.cpp
            gtests/windowmanager/WindowManagerTest.cpp
            gtests/windowmanager/OpenGLWindowHandleTest.cpp
            )
target_link_libraries(Tests gtest gtest_main pthread glfw OpenGL::GL)
add_test(NAME Tests COMMAND Tests)