#include "../../include/core/app.h"

App::App(){
	if (!glfwInit()) {
		std::runtime_error("Failed to initialize GLFW.");
	}

	makeSystems();
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	//renderer->setupOpenGL();

	auto window_ptr = windowManager->createWindow(800, 600, "Jynx - Now with WindowManager!");
	
	glfwMakeContextCurrent((GLFWwindow*)window_ptr->getNativeHandle());

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	window_ptr->setClearColour(0.4f, 0.4f, 0.4f, 1.0f);

	while(!window_ptr->shouldClose()){
		glClear(GL_COLOR_BUFFER_BIT);
		//primitiveModels->draw(renderer->getShader());
		glfwSwapBuffers((GLFWwindow*)window_ptr->getNativeHandle());
		windowManager->pollEvents();
	}

	if(DEBUG_MODE) std::cout << "Program finished." << std::endl;
}

void App::makeSystems(){
	//renderer = std::make_unique<OpenGL>();
	//keyboardHandler = std::make_unique<KeyboardHandler>(m_window);
	//primitiveModels = std::make_unique<PrimitiveModels>();
	windowManager = std::make_unique<WindowManager>();
}