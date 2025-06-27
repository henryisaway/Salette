#include "../../include/core/app.h"

App::App(){
	CLIO_INFO("App instance has been created");
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

		for (auto it = windows.begin(); it != windows.end();) {
			WindowHandle* window = *it;
			glfwMakeContextCurrent((GLFWwindow*)window->getNativeHandle()); // Focus on the current window

			// Check if it should close
			if (window->shouldClose()) {
				it = windows.erase(it);
				WindowManager::getInstance().closeWindow(window);
			} else {
				//Run any rendering calls directed at this window over here
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers((GLFWwindow*)window->getNativeHandle());
				++it;
			}
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
		CLIO_FATAL("Failed to initialize GLFW. Shutting down.");
		exit(1);
	}

	// Requires OpenGL 3.3 or higher
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CLIO_INFO("GLFW is ready");

	// Creating main window;
	auto window_ptr = WindowManager::getInstance().createWindow(800, 550, windowTitle);
	glfwMakeContextCurrent((GLFWwindow*)window_ptr->getNativeHandle());

	// Setting up GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		CLIO_FATAL("Failed to initialise GLAD. Shutting down.");
		glfwTerminate();
		exit(1);
	}

	CLIO_INFO("GLAD is ready");
}

void App::shutdown(){
	glfwTerminate();
	CLIO_INFO("Program Finished.");
}