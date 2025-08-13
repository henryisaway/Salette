#pragma once
#include <includes.h>
#include "../events/inputHandler.h"
#include "../factory/PrimitiveModelFactory.h"
#include "../renderer/IRenderer.h"
#include "../shader/IShader.h"
#include "../windowmanager/WindowManager.h"

namespace Salette {

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

	// --- Systems ---
	std::unique_ptr<IRenderer> m_renderer;
};

}