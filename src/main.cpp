#include "config.h"
#include "controller/engine.h"

int main(){
    Engine* engine = new Engine();
    engine->initOpenGL();
    
    engine->run();
    
    delete engine;
    return 0;
}
