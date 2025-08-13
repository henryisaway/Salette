#include "../../include/core/app.h"
#include "../../include/renderer/OpenGLRenderer.h"

#include "../../include/shader/IShader.h"
#include "../../include/shader/IShaderLinker.h"
#include "../../include/shader/OpenGLShader.h"
#include "../../include/shader/OpenGLShaderLinker.h"

Salette::App::App() {
	CLIO_INFO("App instance has been created");
	makeSystems();
	startup("Salette");
}

Salette::App& Salette::App::getInstance() {
	static App instance;
	return instance;
}

void Salette::App::run(){
    // --- One-time setup for all windows ---
    for(const auto& window : WindowManager::getInstance().getWindows()){
        m_renderer->bindTarget(window.get());
        m_renderer->setClearColour({0.2f, 0.2f, 0.2f, 1.0f});
    }

    // --- TEST STUFF, DELETE AFTER USE ---

    std::unique_ptr<IShaderLinker> shaderLinker = std::make_unique<OpenGLShaderLinker>();

    auto vertexPath= "/home/henryisaway/Documents/MIA/Salette/shaders/vertex.glsl";
    auto vertexFragment= "/home/henryisaway/Documents/MIA/Salette/shaders/fragment.glsl";

    std::unique_ptr<IShader> shader = shaderLinker->createShader(vertexPath, vertexFragment);

    float vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.5f, -0.5f, 0.0f,
	     0.0f,  0.5f, 0.0f
	};  

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// --- TEST STUFF ABOVE ---

	while(WindowManager::getInstance().isRunning()) {

		for (const auto& window : WindowManager::getInstance().getWindows()) {

			if (window->shouldClose()) {
				CLIO_DEBUG("Window (", window->getID(), ") declared 'shouldClose' is true.");
                m_renderer->bindTarget(nullptr);
				WindowManager::getInstance().closeWindow(window.get());
			} else {
                m_renderer->bindTarget(window.get());

				m_renderer->beginFrame();
				shader->bind();

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				m_renderer->endFrame();
			}
		}

		WindowManager::getInstance().pollEvents();
	}

	shutdown();
}

void Salette::App::makeSystems() {
	m_renderer = std::make_unique<OpenGLRenderer>();
}

void Salette::App::startup(const std::string& windowTitle) {
    m_renderer->initialise();
	WindowManager::getInstance().createWindow(800, 550, windowTitle);
}

void Salette::App::shutdown() {
    m_renderer->shutdown();
	CLIO_INFO("Program Finished.");
}