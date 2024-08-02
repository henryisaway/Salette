#include "renderSystem.h"

RenderSystem::RenderSystem(GLFWwindow* window, unsigned int shader){

    modelLocation = glGetUniformLocation(shader, "model");
    this->window = window;
}

void RenderSystem::update(std::unordered_map<unsigned int, RenderComponent> &renderComponents, std::unordered_map<unsigned int, TransformComponent> &transformComponents){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (std::pair<unsigned int, RenderComponent> entity : renderComponents){
        TransformComponent& transform = transformComponents[entity.first];

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::rotate(model, glm::radians(transform.eulers.z), {0.0f, 0.0f, 1.0f});
        
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        
        glBindTexture(GL_TEXTURE_2D, entity.second.material);
        glBindVertexArray(entity.second.mesh); // Handle for the VBO
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    glfwSwapBuffers(window);
}
