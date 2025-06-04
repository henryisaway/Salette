#include "../../include/core/app.h"

App::App(){
	std::cout << "App instance has been created\n";
	makeSystems();
	startup("Vista");
}

App& App::getInstance(){
	static App instance;
	return instance;
}

void App::run(){
	std::vector<WindowHandle*>& windows = WindowManager::getInstance().getWindows();

	// Loop through each open window
	// Run any general renderer settings here
	for(WindowHandle* window : windows){
		glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle());
		window->setClearColour(0.4f, 0.4f, 0.4f, 1.0f); // In this case, this just sets the clear colour for every window
	}

	while(WindowManager::getInstance().isRunning()){
		windows = WindowManager::getInstance().getWindows(); // This is needed to keep the list updated on opened/closed windows

		for(WindowHandle* window : windows){
			glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle()); // Focus on the current window

			// Check if it should close
			if(window->shouldClose()){
				WindowManager::getInstance().closeWindow(window);
				continue;
			}

			//Run any rendering calls directed at this window over here
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers((GLFWwindow*)window->getNativeHandle());
		}

		WindowManager::getInstance().pollEvents();
	}

	shutdown();
}

void App::makeSystems(){
	//renderer = std::make_unique<OpenGL>();
	//keyboardHandler = std::make_unique<KeyboardHandler>(m_window);
	//windowManager = std::make_unique<WindowManager>();
}


void App::startup(const std::string& windowTitle){
	// GLFW initialisation
	if (!glfwInit()) {
		std::runtime_error("Failed to initialize GLFW");
	}

	// Requires OpenGL 3.3 or higher
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(DEBUG_MODE) std::cout << "GLFW is ready\n";

	// Creating main window;
	auto window_ptr = WindowManager::getInstance().createWindow(800, 550, windowTitle);
	glfwMakeContextCurrent((GLFWwindow*)window_ptr->getNativeHandle());

	// Setting up GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialise GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	if(DEBUG_MODE) std::cout << "GLAD is ready\n";
}

void App::shutdown(){
	glfwTerminate();
	if(DEBUG_MODE) std::cout << "Program finished" << std::endl;
}