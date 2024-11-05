#include "../core/config.h"
#include "../shader/shaderLinker.h"

class OpenGL{
public:
	OpenGL();
	void createWindow();
	GLFWwindow* getWindow();
	unsigned int getShader();
	void setupOpenGL();
private:

	unsigned int m_shader;

	void loadGLFW();
	void loadGLAD();
	void GLFWSettings();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void onFramebufferSizeChange(int width, int height);

	const size_t m_width = 800;
	const size_t m_height = 600;

	GLFWwindow* m_window;
};