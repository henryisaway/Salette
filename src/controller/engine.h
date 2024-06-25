#pragma once
#include "../config.h"

class Engine{
public:
    Engine();
    ~Engine();
    
    void run();
    
    void initOpenGL();
    
private:
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void glfwSetup();
    
    GLFWwindow* window;
};
