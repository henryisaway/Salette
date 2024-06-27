#pragma once
#include "../config.h"

#include "../components/renderComponents.h"

#include "../systems/renderSystem.h"
#include "../shaderapps/shaderapps.h"

class Engine{
public:
    Engine();
    ~Engine();
    
    unsigned int createEntity();
    unsigned int makeTriMesh();
    unsigned int makeCube(float s);
    void run();
    void setupOpenGL();
    void makeSystems();
    
    // Components
    std::unordered_map<unsigned int, RenderComponent> renderComponents;
    
private:
    void setupGLFW();
    
    GLFWwindow* window;
    unsigned int entityID = 0;
    
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    
    unsigned int shader;
    
    RenderSystem* renderSystem;
    
};
