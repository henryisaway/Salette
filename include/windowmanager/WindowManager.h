#pragma once
#include "../core/config.h"
#include "WindowHandle.h"
#include "OpenGLWindowHandle.h"

class WindowManager {
public:
	WindowManager();
	~WindowManager();

	// --- Basic Windowing functionality ---
	std::shared_ptr<WindowHandle> createWindow(int width, int height, const std::string& title);
	void pollEvents();
	void closeWindow(std::shared_ptr<WindowHandle> window);

private:
	std::vector<std::shared_ptr<WindowHandle>> windows;
};