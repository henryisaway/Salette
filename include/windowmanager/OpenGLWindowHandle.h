#pragma once
#include "../core/config.h"
#include "WindowHandle.h"

class OpenGLWindowHandle : public WindowHandle{
public:

	OpenGLWindowHandle(GLFWwindow* window, const std::string& title);
	~OpenGLWindowHandle();

	// --- Window Information ---
	void* getNativeHandle() const override; // Returns the GLFW window pointer
	const std::string& getTitle() const override;
	int getWidth() const override;
	int getHeight() const override;
	bool shouldClose() const override;

private:

	GLFWwindow* m_Window;
	std::string m_Title;
	int m_Width;
	int m_Height;
};