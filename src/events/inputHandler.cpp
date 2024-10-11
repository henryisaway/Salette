#include "../../include/events/inputHandler.h"

KeyboardHandler::KeyboardHandler(GLFWwindow* window){
	glfwSetKeyCallback(window, KeyCallback);
}
void KeyboardHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}