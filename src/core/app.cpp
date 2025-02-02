#include "../../include/core/app.h"

App::App(){
	startup("Jynx Project");
	makeSystems();
}

App::~App(){
	glfwTerminate();
}

void App::run(){
	//renderer->setupOpenGL();
	auto windows = windowManager->getWindows();

	for(auto window : windows){
		glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle());
		window->setClearColour(0.4f, 0.4f, 0.4f, 1.0f);
	}

	while(windowManager->isRunning()){
		windows = windowManager->getWindows(); // This is needed to keep the list updated on opened/closed windows

		for(auto window : windows){
			// These two tasks should be delegated to a renderer]
			glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle());

			if(window->shouldClose()){
				windowManager->closeWindow(window);
				continue;
			}

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


void App::startup(const std::string& windowTitle){
	// GLFW initialisation
	if (!glfwInit()) {
		std::runtime_error("Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(DEBUG_MODE) std::cout << "GLFW is ready!\n";

	// Creating main window;
	auto window_ptr = windowManager->createWindow(800, 600, windowTitle);
	glfwMakeContextCurrent((GLFWwindow*)window_ptr->getNativeHandle());

	// Setting up GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD." << std::endl;
		glfwTerminate();
		exit(-1);
	}
}