#pragma once
#include "../core/config.h"

class WindowHandle{
public:
	virtual ~WindowHandle() = default;

	// --- Window Information ---
	virtual void* getNativeHandle() const = 0; // Returns the handle of the windowing API (GLFW, Vulkan, DirectX) as a void pointer
	virtual const std::string& getTitle() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual bool shouldClose() const = 0;
	virtual void setClearColour(float r, float g, float b, float a) = 0;
};