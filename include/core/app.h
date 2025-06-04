#pragma once
#include "config.h"
#include "../events/inputHandler.h"
#include "../factory/factory.h"
#include "../renderer/OpenGLRenderContext.h"
#include "../windowmanager/WindowManager.h"

class App{
public:
	void run();

	static App& getInstance();

private:

	App();
	App(const App&) = delete; 				// Deleting copying operation
	App operator=(const App&) = delete;		// Deleting assignment operation

	void makeSystems();
	void startup(const std::string& windowTitle);
	void shutdown();
};