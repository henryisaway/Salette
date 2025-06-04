#include "../../include/windowmanager/OpenGLWindowHandle.h"

OpenGLWindowHandle::OpenGLWindowHandle(int width, int height, const std::string& title) : m_Width(width), m_Height(height), m_Title(title){
	// This creates the window proper;
	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	// Checks whether window creation was successful
	if(!m_Window){
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	// Sets this instance as the user pointer for the window, needed for the window size callback.
	glfwSetWindowUserPointer(m_Window, this);

	// Sets a size callback to keep the dimensions updated
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int newWidth, int newHeight) {
		OpenGLWindowHandle* handle = static_cast<OpenGLWindowHandle*>(glfwGetWindowUserPointer(window));
		if (handle) {
			handle->m_Width = newWidth;
			handle->m_Height = newHeight;
		}
	});
}

OpenGLWindowHandle::~OpenGLWindowHandle(){
	glfwDestroyWindow(m_Window);
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

void OpenGLWindowHandle::setClearColour(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}