#pragma once

#include "../config.h"

#include "../components/renderComponent.h"

class RenderSystem{
public:

    RenderSystem(GLFWwindow* window);
    
    void update(std::unordered_map<unsigned int, RenderComponent> &renderComponents);
    
private:
    GLFWwindow* window;
};
