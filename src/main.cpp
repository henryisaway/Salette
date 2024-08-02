#include "config.h"
#include "controller/engine.h"

#include "components/renderComponent.h"
#include "components/cameraComponent.h"
#include "components/physicsComponent.h"
#include "components/transformComponent.h"

int main(){
    Engine* engine = new Engine();
    
    unsigned int cube = engine->createEntity();
    TransformComponent transform;
    transform.position = {0.0f, 0.0f, 0.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    engine->transformComponents[cube] = transform;
    
    PhysicsComponent physics;
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.eulers = {0.0f, 0.0f, 10.0f};
    engine->physicsComponents[cube] = physics;
    
    unsigned int cameraEntity = engine->createEntity();
    transform.position = {-3.0f, 1.0f, 1.0f};
    transform.eulers = {0.0f, 0.0f, 0.0f};
    engine->transformComponents[cameraEntity] = transform;
    
    CameraComponent* camera = new CameraComponent();
    engine->cameraComponent = camera;
    engine->cameraID = cameraEntity;
    
    // TODO
    /*
     - Motion (Done), Rendering and Camera (mostly done) systems
     - Update Engine code to include makeTexture()
     - Then just follow amen's main idk
    */
    
    engine->setupOpenGL();
    engine->makeSystems();
    
    engine->run();
    
    delete engine;
    return 0;
}
