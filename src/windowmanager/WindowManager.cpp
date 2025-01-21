#include "../../include/windowmanager/WindowManager.h"

WindowManager::WindowManager(){
	if (!glfwInit()) {
		std::runtime_error("Failed to initialize GLFW in test setup.");
	}
}

WindowManager::~WindowManager(){
	glfwTerminate();
}

std::shared_ptr<WindowHandle> WindowManager::createWindow(int width, int height, const std::string& title){
	std::shared_ptr<WindowHandle> newWindow = std::make_shared<OpenGLWindowHandle>(width, height, title);

	windows.insert(windows.begin(), newWindow);

	return newWindow;
}

void WindowManager::pollEvents(){
	glfwPollEvents();
}

void WindowManager::closeWindow(std::shared_ptr<WindowHandle> window) {
    // Checks if the window exists in the vector
    auto it = std::find(windows.begin(), windows.end(), window);
    if (it != windows.end()) {
        // Remove the window from the vector
        windows.erase(it);

        // Make the GLFWwindow shared_ptr go out of scope; custom deleter will handle cleanup
        window.reset();
    } else {
        std::cerr << "Attempted to close a window that does not exist in the manager.\n";
    }
}