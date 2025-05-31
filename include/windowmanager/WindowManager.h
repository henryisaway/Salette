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
	std::vector<WindowHandle*>& getWindows();
	void pollEvents();
	void closeWindow(WindowHandle* window);
	bool isRunning();

private:
	std::vector<WindowHandle*> m_Windows; // List of all running windows
};