#include "../../include/core/app.h"

App::App(){
	makeSystems();
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	renderer->setupOpenGL();

	primitiveModels->makeTriangle();

	while(!glfwWindowShouldClose(m_window)){
		glClear(GL_COLOR_BUFFER_BIT);
		primitiveModels->draw(renderer->getShader());
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	if(DEBUG_MODE) std::cout << "Program finished." << std::endl;
}

void App::makeSystems(){
	renderer = std::make_unique<OpenGL>();
	m_window = renderer->getWindow();
	keyboardHandler = std::make_unique<KeyboardHandler>(m_window);
	primitiveModels = std::make_unique<PrimitiveModels>();
}