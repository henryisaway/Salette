#include "keyboard.h"

KeyboardManager::KeyboardManager(GLFWwindow* window){
	glfwSetKeyCallback(window, KeyCallback);
}
void KeyboardManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}