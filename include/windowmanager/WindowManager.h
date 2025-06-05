#pragma once
#include "../core/config.h"
#include "WindowHandle.h"
#include "OpenGLWindowHandle.h"

class WindowManager {
public:
	// --- Basic Windowing functionality ---
	WindowHandle* createWindow(int width, int height, const std::string& title);
	std::vector<WindowHandle*>& getWindows();
	void pollEvents();
	void closeWindow(WindowHandle* window);
	bool isRunning();

	static WindowManager& getInstance();



private:
	WindowManager();
	WindowManager(const WindowManager&) = delete;				// Deleting copying operation
	WindowManager operator=(const WindowManager&) = delete;		// Deleting assignment operation

	std::vector<WindowHandle*> m_Windows; // List of all running windows

	unsigned int windowID = 0;
};