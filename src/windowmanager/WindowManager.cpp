#include "../../include/windowmanager/WindowManager.h"

WindowManager::WindowManager(){
    CLIO_INFO("Window Manager instance has been created.");
}

WindowManager& WindowManager::getInstance(){
    static WindowManager instance; 
    return instance;
}

WindowHandle* WindowManager::createWindow(int width, int height, const std::string& title){
	auto newWindow = std::make_unique<OpenGLWindowHandle>(width, height, title, windowID++);
    WindowHandle* newWindowPtr = newWindow.get();

	m_Windows.push_back(std::move(newWindow));

	return newWindowPtr;
}

const std::vector<std::unique_ptr<WindowHandle>>& WindowManager::getWindows() const {
    return m_Windows;
}

void WindowManager::pollEvents(){
	glfwPollEvents();
}

void WindowManager::closeWindow(WindowHandle* window) {
    auto it = std::find_if(m_Windows.begin(), m_Windows.end(),
        [&](const std::unique_ptr<WindowHandle>& p) { return p.get() == window; });

    if (it != m_Windows.end()) {
        m_Windows.erase(it);
    } else {
        CLIO_WARN("Attempted to close a window that does not exist.");
    }
}

bool WindowManager::isRunning(){
    // WindowManager is running as long as there's at least one window open
    if(m_Windows.size()){
        return 1;
    }
    return 0;
}