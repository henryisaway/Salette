#include "../../include/core/app.h"
#include "../../include/renderer/OpenGLRenderer.h" // For make_unique

App::App() {
	CLIO_INFO("App instance has been created");
	makeSystems();
	startup("Vista");
}

App& App::getInstance() {
	static App instance;
	return instance;
}

void App::run(){
    // --- One-time setup for all windows ---
    for(WindowHandle* window : WindowManager::getInstance().getWindows()){
        m_renderer->bindTarget(window);
        m_renderer->setClearColour({0.4f, 0.4f, 0.4f, 1.0f});
    }
    m_renderer->bindTarget(nullptr); // Unbind after setup

	while(WindowManager::getInstance().isRunning()) {
		// Use a copy of the window list to avoid iterator invalidation issues
        auto windows = WindowManager::getInstance().getWindows();

		for (WindowHandle* window : windows) {

			if (window->shouldClose()) {
                // Unbind the context before closing the window
                m_renderer->bindTarget(nullptr);
                // Let the WindowManager handle the entire closing process
				WindowManager::getInstance().closeWindow(window);
			} else {
                // Tell the renderer which window to draw to
                m_renderer->bindTarget(window);

                // Render the frame
				m_renderer->beginFrame();
				// --- All drawing commands for this window will go here ---
				m_renderer->endFrame();
			}
		}

		WindowManager::getInstance().pollEvents();
	}

	shutdown();
}

void App::makeSystems() {
	m_renderer = std::make_unique<OpenGLRenderer>();
}


void App::startup(const std::string& windowTitle) {
    m_renderer->initialise();
	WindowManager::getInstance().createWindow(800, 550, windowTitle);
}

void App::shutdown() {
    m_renderer->shutdown();
	CLIO_INFO("Program Finished.");
}