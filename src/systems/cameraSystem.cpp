#include "cameraSystem.h"

CameraSystem::CameraSystem(GLFWwindow* window, unsigned int shader) {
    this->window = window;
    
    glUseProgram(shader);
    viewLocation = glGetUniformLocation(shader, "view");
}

void CameraSystem::update(std::unordered_map<unsigned int, TransformComponent> &transformComponents, unsigned int cameraID, CameraComponent& cameraComponent){
    glm::vec3& pos = transformComponents[cameraID].position;
    glm::vec3& eulers = transformComponents[cameraID].eulers;
    
    float theta = glm::radians(eulers.z); // LR rotation
    float phi = glm::radians(eulers.y); // Up & Down rotation
    
    glm::vec3& right = cameraComponent.right;
    glm::vec3& up = cameraComponent.up;
    glm::vec3& forwards = cameraComponent.forwards;
    
    // Didn't check the math but probably works
    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    right = glm::normalize(glm::cross(forwards, globalUp));
    up = glm::normalize(glm::cross(right, forwards));
    
    // View matrix is done here
    glm::mat4 view = glm::lookAt(pos, pos + forwards, up);
    
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    
    //TODO: Camera movement
    glfwPollEvents();
}
