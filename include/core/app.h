#pragma once
#include "config.h"
#include "../events/inputHandler.h"
#include "../shader/shaderLinker.h"
#include "../factory/factory.h"

class App{
public:
	App();
	~App();
	void run();

private:
	const size_t m_width = 800;
	const size_t m_height = 600;

	unsigned int m_shader;

	void loadGLFW();
	void loadGLAD();
	void createWindow();
	void GLFWSettings();
	void setupOpenGL();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void onFramebufferSizeChange(int width, int height);
	void makeSystems(GLFWwindow* window);

	GLFWwindow* m_window;

	// Systems
	std::unique_ptr<KeyboardHandler> keyboardHandler;
	std::unique_ptr<PrimitiveModels> primitiveModels;
};