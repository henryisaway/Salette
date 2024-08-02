#pragma once
#include "../config.h"
#include "../components/transformComponent.h"
#include "../components/physicsComponent.h"

class MotionSystem {
public:
    void update(std::unordered_map<unsigned int, TransformComponent> &transformComponents, std::unordered_map<unsigned int, PhysicsComponent> &physicsComponents, float deltaTime);
};
