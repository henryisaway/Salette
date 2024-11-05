#pragma once
#include "config.h"
#include "../events/inputHandler.h"
#include "../factory/factory.h"
#include "../renderer/OpenGLRenderContext.h"

class App{
public:
	App();
	~App();
	void run();

private:
	void makeSystems();

	GLFWwindow* m_window;

	// Systems
	std::unique_ptr<OpenGL> renderer;
	std::unique_ptr<KeyboardHandler> keyboardHandler;
	std::unique_ptr<PrimitiveModels> primitiveModels;
};