#pragma once
#include "../config.h"
#include "../components/cameraComponent.h"
#include "../components/transformComponent.h"

class CameraSystem {
public:
    CameraSystem(GLFWwindow* window, unsigned int shader);
    
    void update(std::unordered_map<unsigned int, TransformComponent> &transformComponent, unsigned int cameraID, CameraComponent& cameraComponent);
    
private:
    unsigned int viewLocation;
    glm::vec3 globalUp = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
};
