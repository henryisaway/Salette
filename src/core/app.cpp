#include "app.h"

App::App(const int width, const int height, const char* title){
	setupGLFW(width, height, title);
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	setupOpenGL();
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void App::setupGLFW(const int width, const int height, const char* title){
	if(DEBUG_MODE) std::cout << "Setting up GLFW...\n";
	if(!glfwInit()){
		std::cerr << "Failed to initialise GLFW." << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL){
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	KeyboardManager keyboardManager(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	// Sets the App instance as the window user pointer
	// Needed for the framebuffer size callback to work
	glfwSetWindowUserPointer(window, this); 
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	if(DEBUG_MODE) std::cout << "GLFW is ready!\n";
}

void App::setupOpenGL(){
	if(DEBUG_MODE) std::cout << "Setting up OpenGL...\n";
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	if(DEBUG_MODE) std::cout << "OpenGL is ready!\n";
}

void App::framebufferSizeCallback(GLFWwindow* window, int width, int height){
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	if(app){
		app->onFramebufferSizeChange(width, height);
	}
}

void App::onFramebufferSizeChange(int width, int height){
	glViewport(0, 0, width, height);
}