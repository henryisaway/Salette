#pragma once
#include <includes.h>
#include "WindowHandle.h"
#include "OpenGLWindowHandle.h"

namespace Salette {

class WindowManager {
public:
	// --- Basic Windowing functionality ---
	WindowHandle* createWindow(int width, int height, const std::string& title);
	const std::vector<std::unique_ptr<WindowHandle>>& getWindows() const;
	void pollEvents();
	void closeWindow(WindowHandle* window);
	bool isRunning();

	static WindowManager& getInstance();



private:
	WindowManager();
	WindowManager(const WindowManager&) = delete;				// Deleting copying operation
	WindowManager operator=(const WindowManager&) = delete;		// Deleting assignment operation

	std::vector<std::unique_ptr<WindowHandle>> m_Windows; // List of all running windows

	unsigned int windowID = 0;
};

}