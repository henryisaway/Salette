#pragma once
#include "../core/config.h"
#include "../windowmanager/WindowHandle.h"

class IRenderer {
public:
	// --- Initialization ---
	virtual void initialise() = 0; // Set up graphics API-specific resources.
	virtual void shutdown() = 0;  // Clean up resources.

	// --- Frame Lifecycle ---
	virtual void beginFrame() = 0; // Clear buffers, set up for a new frame.
	virtual void endFrame() = 0;   // Swap buffers.

	// --- Drawing ---
	//virtual void drawMesh(const Mesh& mesh, const Shader& shader) = 0; 
	//virtual void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) = 0; // Helper for 2D.
	//virtual void drawText(const std::string& text, const Font& font, const glm::vec2& position) = 0;

	// --- Resource Management ---
	//virtual std::shared_ptr<Texture> createTexture(const std::string& filepath) = 0;
	//virtual std::shared_ptr<Shader> createShader(const std::string& vertexSrc, const std::string& fragmentSrc) = 0;

	// --- State Management ---
	virtual void setViewport(int width, int height) = 0; // For window resizing.
	virtual void setClearColour(const glm::vec4& colour) = 0;

	// --- Debugging ---
	//virtual void enableWireframe(bool enabled) = 0;

	// --- Multi-Window Support ---
	virtual void bindTarget(WindowHandle* window) = 0;
};
