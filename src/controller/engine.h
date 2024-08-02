#pragma once
#include "../config.h"

#include "../components/renderComponent.h"
#include "../components/cameraComponent.h"
#include "../components/physicsComponent.h"
#include "../components/transformComponent.h"

#include "../systems/motionSystem.h"
#include "../systems/cameraSystem.h"
#include "../systems/renderSystem.h"
#include "../shaderapps/shaderapps.h"

class Engine{
public:
    Engine();
    ~Engine();
    
    unsigned int createEntity();
    unsigned int makeCube(float s);
    unsigned int makeTexture(const char* filename);
    void run();
    void setupOpenGL();
    void makeSystems();
    
    // Compoments
    std::unordered_map<unsigned int, TransformComponent> transformComponents;
    std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    std::unordered_map<unsigned int, RenderComponent> renderComponents;
    
private:
    void setupGLFW();
    
    GLFWwindow* window;
    unsigned int entityID = 0;
    
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> textures;
    
    unsigned int shader;
    
    MotionSystem* motionSystem;
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;
};
