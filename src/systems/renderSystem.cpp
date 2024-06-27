#include "renderSystem.h"

RenderSystem::RenderSystem(GLFWwindow* window){
    this->window = window;
}

void RenderSystem::update(std::unordered_map<unsigned int, RenderComponent> &renderComponents){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (std::pair<unsigned int, RenderComponent> entity : renderComponents){
        glBindVertexArray(entity.second.mesh);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
    glfwSwapBuffers(window);
}
