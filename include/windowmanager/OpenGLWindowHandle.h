#pragma once
#include "../core/config.h"
#include "WindowHandle.h"

class OpenGLWindowHandle : public WindowHandle{
public:

	OpenGLWindowHandle(int width, int height, const std::string& title, unsigned int id);
	~OpenGLWindowHandle();

	// --- Window Information ---
	void* getNativeHandle() const override; // Returns the GLFW window pointer
	const std::string& getTitle() const override;
	const unsigned int getID() const override;
	int getWidth() const override;
	int getHeight() const override;
	bool shouldClose() const override;
	void setClearColour(float r, float g, float b, float a) override;

private:

	unsigned int m_id;
	GLFWwindow* m_Window;
	std::string m_Title;
	int m_Width;
	int m_Height;
};