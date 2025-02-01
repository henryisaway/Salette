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
	windowManager->createWindow(800, 600, "Jynx 1");
	windowManager->createWindow(800, 600, "Jynx 2");
	windowManager->createWindow(800, 600, "Jynx 3");
	windowManager->createWindow(800, 600, "Jynx 4");
	
	glfwMakeContextCurrent((GLFWwindow*)window_ptr->getNativeHandle());

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	auto windows = windowManager->getWindows();

	for(auto window : windows){
		glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle());
		window->setClearColour(0.4f, 0.4f, 0.4f, 1.0f);
	}

	while(windowManager->isRunning()){
		for(auto window : windows){
			// These two tasks should be delegated to a renderer]
			glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle());
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers((GLFWwindow*)window->getNativeHandle());
		}

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