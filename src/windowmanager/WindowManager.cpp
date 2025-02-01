#include "../../include/windowmanager/WindowManager.h"

WindowManager::WindowManager(){
}

WindowManager::~WindowManager(){
}

WindowHandle* WindowManager::createWindow(int width, int height, const std::string& title){
	WindowHandle* newWindow = new OpenGLWindowHandle(width, height, title);

	windows.insert(windows.begin(), newWindow);

	return newWindow;
}

void WindowManager::pollEvents(){
	glfwPollEvents();
}

void WindowManager::closeWindow(WindowHandle* window) {
    // Checks if the window exists in the vector
    auto it = std::find(windows.begin(), windows.end(), window);
    if (it != windows.end()) {
        // Remove the window from the vector
        windows.erase(it);

        // This needs to properly destroy the window and pointer.
    } else {
        std::cerr << "Attempted to close a window that does not exist in the manager.\n";
    }
}