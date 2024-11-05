#include "../../include/renderer/OpenGLRenderContext.h"

OpenGL::OpenGL(){
	loadGLFW();
	createWindow();
	loadGLAD();
	GLFWSettings();
}

void OpenGL::loadGLFW(){
	if(DEBUG_MODE) std::cout << "Setting up GLFW...\n";
	if(!glfwInit()){
		std::cerr << "Failed to initialise GLFW." << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OpenGL::createWindow(){
	m_window = glfwCreateWindow(m_width, m_height, "Jynx", NULL, NULL);
	if(m_window == NULL){
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);
}

GLFWwindow* OpenGL::getWindow(){
	return m_window;
}

unsigned int OpenGL::getShader(){
	return m_shader;
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

void OpenGL::setupOpenGL(){
	if(DEBUG_MODE) std::cout << "Setting up OpenGL...\n";
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	if(DEBUG_MODE) std::cout << "OpenGL is ready!\n";

	m_shader = linkShader(
		"../shaders/vertex.glsl",
		"../shaders/fragment.glsl");

	glUseProgram(m_shader);
}

void OpenGL::framebufferSizeCallback(GLFWwindow* window, int width, int height){
	OpenGL* renderer = static_cast<OpenGL*>(glfwGetWindowUserPointer(window));
	if(renderer){
		renderer->onFramebufferSizeChange(width, height);
	}
}

void OpenGL::onFramebufferSizeChange(int width, int height){
	glViewport(0, 0, width, height);
}