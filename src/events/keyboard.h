#include "../config.h"

class KeyboardManager{
public:
	KeyboardManager(GLFWwindow* window);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};