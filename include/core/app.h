#pragma once
#include "config.h"
#include "../events/inputHandler.h"
#include "../factory/factory.h"
#include "../renderer/OpenGLRenderContext.h"
#include "../windowmanager/WindowManager.h"

class App{
public:
	App();
	~App();
	void run();

private:
	void makeSystems();

	// Remember to get rid of the window and renderer here.
	// Get App a window manager.

	// std::shared_ptr<WindowHandle> m_window;

	// Systems
	//std::unique_ptr<OpenGL> renderer;
	//std::unique_ptr<KeyboardHandler> keyboardHandler;
	//std::unique_ptr<PrimitiveModels> primitiveModels;
	std::unique_ptr<WindowManager> windowManager;
};