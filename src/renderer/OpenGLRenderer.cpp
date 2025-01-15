#include "../../include/renderer/OpenGLRenderer.h"

// --- Basic Management ---

void OpenGLRenderer::Initialise(){
	loadGLFW();
	loadGLAD();
	loadGLFWSettings();
}

// --- OpenGL Setup ---

void OpenGLRenderer::loadGLFW(){
	if(DEBUG_MODE) std::cout << "Setting up GLFW...\n";
	if(!glfwInit()){
		std::cerr << "Failed to initialise GLFW." << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OpenGL::loadGLAD(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

void OpenGL::GLFWSettings(){
	// Sets the OpenGL instance as the window user pointer
	glfwSetWindowUserPointer(m_window, this); // Needed for the framebuffer size callback to work
	glViewport(0, 0, m_width, m_height);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	
	if(DEBUG_MODE) std::cout << "GLFW is ready!\n";
}

// --- Framebuffer callback ---

/* This is needed because OpenGL doesn't support instance methods (they implicitly take a *this* pointer,
which the compiler doesn't like). These functions work around it by making the window a static cast.

Possible bugs:
- Might not work with multiple windows, since each renderer is tied to a window and static methods don't retain
instance-specific data. glfwSetWindowUserPointer() might fix this issue.
*/

void OpenGL::framebufferSizeCallback(GLFWwindow* window, int width, int height){
	OpenGL* renderer = static_cast<OpenGL*>(glfwGetWindowUserPointer(window));
	if(renderer){
		renderer->onFramebufferSizeChange(width, height);
	}
}

void OpenGL::onFramebufferSizeChange(int width, int height){
	glViewport(0, 0, width, height);
}