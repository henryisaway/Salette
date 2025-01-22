#include "../../include/core/app.h"

App::App(){
	if (!glfwInit()) {
		std::runtime_error("Failed to initialize GLFW.");
	}

	makeSystems();
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	//renderer->setupOpenGL();

	std::shared_ptr window_ptr = windowManager->createWindow(800, 600, "Jynx - Now with WindowManager!");

	//window_ptr->setClearColour(0.4f, 0.4f, 0.4f, 1.0f);
	while(!window_ptr->shouldClose()){
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