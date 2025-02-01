#pragma once
#include "../core/config.h"
#include "WindowHandle.h"
#include "OpenGLWindowHandle.h"

class WindowManager {
public:
	WindowManager();
	~WindowManager();

	// --- Basic Windowing functionality ---
	WindowHandle* createWindow(int width, int height, const std::string& title);
	void pollEvents();
	void closeWindow(WindowHandle* window);

private:
	std::vector<WindowHandle*> windows;
};