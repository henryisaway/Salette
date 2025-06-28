#pragma once
#include <includes.h>

class WindowHandle{
public:
	virtual ~WindowHandle() = default;

	// --- Window getters ---
	virtual void* getNativeHandle() const = 0; // Returns the handle of the windowing API (GLFW, Vulkan, DirectX) as a void pointer
	virtual const std::string& getTitle() const = 0;
	virtual const unsigned int getID() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual bool shouldClose() const = 0;

	// --- Window setters ---
	virtual void setClearColour(const glm::vec4& colour) = 0;
};