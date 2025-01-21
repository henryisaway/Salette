#include "../../include/windowmanager/OpenGLWindowHandle.h"

OpenGLWindowHandle::OpenGLWindowHandle(int width, int height, const std::string& title) : m_Width(width), m_Height(height), m_Title(title){
	
	if(!glfwInit()){
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwSetErrorCallback([](int error, const char* description) {
	    std::cerr << "GLFW error (" << error << "): " << description << std::endl;
	});

	// This creates the window proper; The second argument is a custom destructor for the GLFWwindow type
	m_Window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), 
		[](GLFWwindow* ptr) {
		if(ptr){
			glfwDestroyWindow(ptr);
		}
	});

	if(!m_Window){
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	// Set this instance as the user pointer for the window, needed for the window size callback.
	glfwSetWindowUserPointer(m_Window.get(), this);

	// Set a size callback to keep the dimensions updated
	glfwSetWindowSizeCallback(m_Window.get(), [](GLFWwindow* window, int newWidth, int newHeight) {
		auto* handle = static_cast<OpenGLWindowHandle*>(glfwGetWindowUserPointer(window));
		if (handle) {
			handle->m_Width = newWidth;
			handle->m_Height = newHeight;
		}
	});
}

void* OpenGLWindowHandle::getNativeHandle() const {
	return reinterpret_cast<void*>(m_Window.get()); // Returns raw pointer to the window
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
	return glfwWindowShouldClose(m_Window.get());
}