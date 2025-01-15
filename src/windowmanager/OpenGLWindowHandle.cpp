#include "../../include/windowmanager/OpenGLWindowHandle.h"

OpenGLWindowHandle::OpenGLWindowHandle(GLFWwindow* window, const std::string& title) : m_Window(window), m_Title(title){
	if(!m_Window){
		throw std::runtime_error("Invalid GLFW window handle.");
	}
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);
}

OpenGLWindowHandle::~OpenGLWindowHandle(){
	if(m_Window) glfwDestroyWindow(m_Window);
}

void* OpenGLWindowHandle::getNativeHandle() const {
	return reinterpret_cast<void*>(m_Window); // Returns raw pointer to the window
}

const std::string& OpenGLWindowHandle::getTitle() const {
	return m_Title;
}

int OpenGLWindowHandle::getWidth() const {
	return m_Width;
}

int OpenGLWindowHandle::getHeight() const {
	return m_Height;
}

bool OpenGLWindowHandle::shouldClose() const {
	return glfwWindowShouldClose(m_Window);
}