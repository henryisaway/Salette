#pragma once
#include "../core/config.h"
#include "WindowHandle.h"

class WindowManager {
public:
	WindowManager();
	~WindowManager();

	// --- Basic Windowing functionality ---
	std::shared_ptr<WindowHandle> createWindow(int width, int height, const std::string& title);
	void pollEvents();
	void closeWindow();

	// --- Utilities ---
	std::vector<std::shared_ptr<WindowHandle>> getWindows() const;
	std::shared_ptr<WindowHandle> getWindowByTitle(std::string& title) const;

private:
	std::vector<std::shared_ptr<WindowHandle>> windows;

	// --- Backend-specific methods ---
    std::shared_ptr<WindowHandle> backendCreateWindow(int width, int height, const std::string& title);
    void backendPollEvents();z
};