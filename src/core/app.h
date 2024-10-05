#pragma once
#include "../config.h"
#include "../events/keyboard.h"

class App{
public:
	App(const int width, const int height, const char* title);
	~App();
	void run();
	void setupGLFW(const int width, const int height, const char* title);
	void setupOpenGL();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void onFramebufferSizeChange(int width, int height);
private:
	GLFWwindow* window;
};