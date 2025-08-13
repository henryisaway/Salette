#include "../../include/windowmanager/OpenGLWindowHandle.h"

namespace Salette {

OpenGLWindowHandle::OpenGLWindowHandle(int width, int height, const std::string& title, unsigned int id) : m_Width(width), m_Height(height), m_Title(title), m_id(id) {
	// This creates the window proper;
	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	// Checks whether window creation was successful
	if(!m_Window){
		CLIO_FATAL("Failed to create window. Shutting down.");
		exit(1);
	}

	// Sets this instance as the user pointer for the window, needed for the window size callback.
	glfwSetWindowUserPointer(m_Window, this);

	// Sets a size callback to keep the dimensions updated
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int newWidth, int newHeight) {
		OpenGLWindowHandle* handle = static_cast<OpenGLWindowHandle*>(glfwGetWindowUserPointer(window));
		if (handle) {
			handle->m_Width = newWidth;
			handle->m_Height = newHeight;

			CLIO_TRACE("Window resizing was triggered. New size is ", handle->m_Width, "x", handle->m_Height);
		}
	});

	CLIO_INFO("Window (", m_id,") has been initialised with size ", m_Width, "x", m_Height);
}

OpenGLWindowHandle::OpenGLWindowHandle(GLFWwindow* window) : m_Window(window) {
    if (!m_Window) {
        CLIO_FATAL("Attempted to create OpenGLWindowHandle with a null GLFWwindow*.");
        exit(1);
    }

    glfwMakeContextCurrent(m_Window);

    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);
    m_Width = width;
    m_Height = height;

    const char* title = glfwGetWindowTitle(m_Window);
    if (title) {
        m_Title = title;
    } else {
        m_Title = ""; // Default empty title
    }
    // Assign a dummy ID for test purposes, or query if GLFW provides one
    m_id = 0; // Or some other unique identifier if available

    glfwSetWindowUserPointer(m_Window, this);

    CLIO_INFO("Window (", m_id, ") has been initialised from existing GLFWwindow* with size ", m_Width, "x", m_Height);
}

OpenGLWindowHandle::~OpenGLWindowHandle() {
	glfwDestroyWindow(m_Window);
	CLIO_INFO("Window (", m_id, ") has been destroyed.");
}

void* OpenGLWindowHandle::getNativeHandle() const {
	auto nativeHandle = reinterpret_cast<void*>(m_Window);
	CLIO_TRACE("Window (", m_id, ") called getNativeHandle() with return ", nativeHandle);
	return nativeHandle; // Returns raw pointer to the window
}

const std::string& OpenGLWindowHandle::getTitle() const {
	CLIO_DEBUG("Window (", m_id, ") called getTitle() with return ",  m_Title);
	return m_Title;
}

const unsigned int OpenGLWindowHandle::getID() const {
	CLIO_DEBUG("Window (", m_id, ") called getID().");
	return m_id;
}

int OpenGLWindowHandle::getWidth() const {
	CLIO_DEBUG("Window (", m_id, ") called getWidth() with return ", m_Width);
	return m_Width;
}

int OpenGLWindowHandle::getHeight() const {
	CLIO_DEBUG("Window (", m_id, ") called getHeight() with return ", m_Height);
	return m_Height;
}

bool OpenGLWindowHandle::shouldClose() const {
	return glfwWindowShouldClose(m_Window);
}

void OpenGLWindowHandle::setClearColour(const glm::vec4& colour) {
	CLIO_DEBUG("Window (", m_id, ") clear colour set to (", colour.r, "f, ", colour.g, "f, ", colour.b, "f, ", colour.a, "f)");
	glClearColor(colour.r, colour.g, colour.b, colour.a);
}

} // namespace Vista
