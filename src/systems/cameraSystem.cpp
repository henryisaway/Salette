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
    //Keys
    glm::vec3 movementVec = {0.0f, 0.0f, 0.0f};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movementVec.x += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movementVec.y -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movementVec.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movementVec.y += 1.0f;
    }
    if (glm::length(movementVec) > 0.1f) {
        movementVec = glm::normalize(movementVec);
        pos += 0.1f * movementVec.x * forwards;
        pos += 0.1f * movementVec.y * right;
    }
    
    //Mouse
    glm::vec3 movementEulers = {0.0f, 0.0f, 0.0f};
    unsigned int sensitivity = 5;
    
    int w,h;
	glfwGetFramebufferSize(window, &w, &h);
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glfwSetCursorPos(window, w/2, h/2);
    glfwPollEvents();
	
    movementEulers.z = -0.01f * sensitivity * static_cast<float>(mouseX - w/2);
    movementEulers.y = -0.01f * sensitivity * static_cast<float>(mouseY - h/2);

    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + movementEulers.y));

    eulers.z += movementEulers.z;
    
    if (eulers.z > 360) {
        eulers.z -= 360;
    }
    else if (eulers.z < 0) {
        eulers.z += 360;
    }
}
