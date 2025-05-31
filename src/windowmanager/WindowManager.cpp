#include "../../include/windowmanager/WindowManager.h"

WindowManager::WindowManager(){
}

WindowManager::~WindowManager(){
}

WindowHandle* WindowManager::createWindow(int width, int height, const std::string& title){
	WindowHandle* newWindow = new OpenGLWindowHandle(width, height, title);

	m_Windows.insert(m_Windows.end(), newWindow);

	return newWindow;
}

std::vector<WindowHandle*>& WindowManager::getWindows(){
    return m_Windows;
}

void WindowManager::pollEvents(){
	glfwPollEvents();
}

void WindowManager::closeWindow(WindowHandle* window) {
    // Checks if the window exists in the vector
    auto it = std::find(m_Windows.begin(), m_Windows.end(), window);
    if (it != m_Windows.end()) {
        // Remove the window from the vector
        m_Windows.erase(it);

        delete window; //WindowHandle destructor will destroy the window upon deletion.
    } else {
        std::cerr << "Attempted to close a window that does not exist.\n";
    }
}

bool WindowManager::isRunning(){
    // WindowManager is running as long as there's at least one window open
    if(m_Windows.size()){
        return 1;
    }
    return 0;
}