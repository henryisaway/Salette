#pragma once
#include "../core/config.h"
#include "WindowHandle.h"

class OpenGLWindowHandle : public WindowHandle{
public:

	OpenGLWindowHandle(int width, int height, const std::string& title);

	// --- Window Information ---
	void* getNativeHandle() const override; // Returns the GLFW window pointer
	const std::string& getTitle() const override;
	int getWidth() const override;
	int getHeight() const override;
	bool shouldClose() const override;

private:

	std::shared_ptr<GLFWwindow> m_Window;
	std::string m_Title;
	int m_Width;
	int m_Height;
};