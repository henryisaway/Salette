#include "../../include/core/app.h"

App::App(){
	makeSystems();
}

App::~App(){

}

void App::run(){
	//renderer->setupOpenGL();
	windowManager->createWindow(800, 600, "Jynx - Now with WindowManager!");

	while(1){
		// glClear(GL_COLOR_BUFFER_BIT);
		//primitiveModels->draw(renderer->getShader());
		// glfwSwapBuffers(m_window);
		windowManager->pollEvents();
	}

	if(DEBUG_MODE) std::cout << "Program finished." << std::endl;
}

void App::makeSystems(){
	//renderer = std::make_unique<OpenGL>();
	//keyboardHandler = std::make_unique<KeyboardHandler>(m_window);
	//primitiveModels = std::make_unique<PrimitiveModels>();
	windowManager = std::make_unique<WindowManager>();
}