#include "app.h"

App::App(){
	setupGLFW();
	makeSystems(m_window);
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	setupOpenGL();

	if(DEBUG_MODE){
		std::cout << "DEBUG INFO ------------------------------\n";
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		std::cout << "Screen width: " << w << "\n";
		std::cout << "Screen height: " << h << "\n";
		std::cout << "Shader ID: " << m_shader << "\n";
	}

	primitiveModels->makeTriangle();

	while(!glfwWindowShouldClose(m_window)){
		glClear(GL_COLOR_BUFFER_BIT);
		primitiveModels->draw(m_shader);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	if(DEBUG_MODE) std::cout << "Program finished." << std::endl;
}

void App::setupGLFW(){
	if(DEBUG_MODE) std::cout << "Setting up GLFW...\n";
	if(!glfwInit()){
		std::cerr << "Failed to initialise GLFW." << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "Jynx", NULL, NULL);
	if(m_window == NULL){
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	// Sets the App instance as the window user pointer
	// Needed for the framebuffer size callback to work
	glfwSetWindowUserPointer(m_window, this); 
	glViewport(0, 0, m_width, m_height);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	if(DEBUG_MODE) std::cout << "GLFW is ready!\n";
}

void App::setupOpenGL(){
	if(DEBUG_MODE) std::cout << "Setting up OpenGL...\n";
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	if(DEBUG_MODE) std::cout << "OpenGL is ready!\n";

	m_shader = linkShader(
		"../src/shaders/vertex.glsl",
		"../src/shaders/fragment.glsl");

	glUseProgram(m_shader);
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

void App::makeSystems(GLFWwindow* window){
	keyboardHandler = std::make_unique<KeyboardHandler>(window);
	primitiveModels = std::make_unique<PrimitiveModels>();
}