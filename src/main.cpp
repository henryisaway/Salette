#include "config.h"
#include "controller/engine.h"

#include "components/renderComponent.h"
#include "components/cameraComponent.h"
#include "components/physicsComponent.h"
#include "components/transformComponent.h"

int main(){
    Engine* engine = new Engine();
    
    // Creating cube
    unsigned int cube = engine->createEntity();
    TransformComponent transform;
    transform.position = {0.0f, 0.0f, 0.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    engine->transformComponents[cube] = transform;
    
    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulers = {0.0f, 0.0f, -20.0f};
    engine->physicsComponents[cube] = physics;
    
    RenderComponent render;
    render.mesh = engine->makeCube(0.25f);
    render.material = engine->makeTexture("../img/test2.png");
    engine->renderComponents[cube] = render;
    
    unsigned int cameraEntity = engine->createEntity();
    transform.position = {-3.0f, 0.0f, 0.5f};
    transform.eulers = {0.0f, 0.0f, 15.0f};
    engine->transformComponents[cameraEntity] = transform;
    
    CameraComponent* camera = new CameraComponent();
    engine->cameraComponent = camera;
    engine->cameraID = cameraEntity;
    
    engine->setupOpenGL();
    engine->makeSystems();
    
    engine->run();
    
    delete engine;
    return 0;
}
