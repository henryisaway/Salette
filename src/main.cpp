#include "config.h"

#include "components/renderComponents.h"

#include "controller/engine.h"
#include "controller/test.h"



int main(){
    Engine* engine = new Engine();
    
    unsigned int tri = engine->createEntity();
    std::cout << "triangleMeshID:" << tri << std::endl;
    RenderComponent render;
    render.mesh = engine->makeTriMesh();
    std::cout << render.mesh << std::endl;
    render.material = 0;
    engine->renderComponents[tri] = render;
    
    engine->setupOpenGL();
    engine->makeSystems();
    
    engine->run();
    
    delete engine;
    return 0;
}
