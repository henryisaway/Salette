cmake_minimum_required(VERSION 3.15)
project(Salette)
cmake_policy(SET CMP0072 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include OpenGL
find_package(OpenGL REQUIRED)

# GLFW
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glfw")
add_subdirectory(${GLFW_ROOT})

# GLAD
set(GLAD_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glad")
include_directories(${GLAD_ROOT}/include)

# GLM
set(GLM_ROOT "${CMAKE_SOURCE_DIR}/dependencies/glm")
include_directories(${GLM_ROOT}/include)

# Clio
set(CLIO_ROOT "${CMAKE_SOURCE_DIR}/dependencies/clio")
include_directories(${CLIO_ROOT})

# Includes
set(INCLUDES_ROOT "${CMAKE_SOURCE_DIR}/include/core")
include_directories(${INCLUDES_ROOT})

# Platform-specific dependencies (mainly for static GLFW)
if(UNIX AND NOT APPLE)
    set(PLATFORM_LIBS dl pthread X11)
elseif(WIN32)
    set(PLATFORM_LIBS)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    set(PLATFORM_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

# Add executable
add_executable(Salette
    src/core/includes.cpp
    main.cpp
    ${GLAD_ROOT}/src/glad.c
    src/events/inputHandler.cpp
    src/shader/OpenGLShader.cpp
    src/shader/OpenGLShaderLinker.cpp
    src/windowmanager/OpenGLWindowHandle.cpp
    src/windowmanager/WindowManager.cpp
    src/factory/PrimitiveModelFactory.cpp
    src/renderer/PrimitiveModel.cpp
    src/renderer/OpenGLRenderer.cpp
    src/core/app.cpp
)

target_link_libraries(Salette
    PRIVATE glfw OpenGL::GL ${PLATFORM_LIBS}
)

# --- Google Tests ---
enable_testing()

add_executable(Tests 
    src/core/includes.cpp
    gtests/gtestmain.cpp
    ${GLAD_ROOT}/src/glad.c
    src/windowmanager/OpenGLWindowHandle.cpp
    src/windowmanager/WindowManager.cpp
    gtests/windowmanager/WindowManagerTest.cpp
    gtests/windowmanager/OpenGLWindowHandleTest.cpp
)

target_link_libraries(Tests
    PRIVATE gtest gtest_main pthread glfw OpenGL::GL ${PLATFORM_LIBS}
)

add_test(NAME Tests COMMAND Tests)
