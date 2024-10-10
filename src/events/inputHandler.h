#include "../config.h"

class KeyboardHandler{
public:
	KeyboardHandler(GLFWwindow* window);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};