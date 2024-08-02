#pragma once

#include "../config.h"

#include "../components/renderComponent.h"
#include "../components/transformComponent.h"

class RenderSystem{
public:

    RenderSystem(GLFWwindow* window, unsigned int shader);
    
    void update(std::unordered_map<unsigned int, RenderComponent> &renderComponents, std::unordered_map<unsigned int, TransformComponent> &transformComponent);
    
private:
    GLFWwindow* window;
    unsigned int modelLocation;
};
