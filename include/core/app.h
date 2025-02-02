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
	void startup(const std::string& windowTitle);
	// Systems
	//std::unique_ptr<KeyboardHandler> keyboardHandler;
	std::unique_ptr<WindowManager> windowManager;
};