#include "motionSystem.h"

void MotionSystem::update(std::unordered_map<unsigned int, TransformComponent> &transformComponents, std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents, float deltaTime){

    // For each entity in the physics components list
    for(std::pair<unsigned int, PhysicsComponent> entity : physicsComponent){

        transformComponents[entity.first].position += entity.second.velocity * deltaTime;
        transformComponents[entity.first].eulers += entity.second.eulers * deltaTime;
        
        if (transformComponents[entity.first].eulers.x > 360){
            transformComponents[entity.first].eulers.x -= 360;
        }
        
        if (transformComponents[entity.first].eulers.y > 360){
            transformComponents[entity.first].eulers.y -= 360;
        }
        
        if (transformComponents[entity.first].eulers.z > 360){
            transformComponents[entity.first].eulers.z -= 360;
        }
    }
}
