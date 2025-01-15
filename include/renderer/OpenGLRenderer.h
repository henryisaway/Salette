#pragma once
#include "../core/config.h"
#include "InterfaceRenderer.h"

// Refer to InterfaceRenderer.h for an explanation of each method.

class OpenGLRenderer : public IRenderer {
public:

	// --- Initialization ---
	void initialize() override;
	void shutdown() override;

	// --- Frame Lifecycle ---
	void beginFrame() override;
	void endFrame() override;

	// --- Drawing ---
	void drawMesh(const Mesh& mesh, const Shader& shader) override;
	void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) override;
	void drawText(const std::string& text, const Font& font, const glm::vec2& position) override;

	// --- Resource Management ---
	std::shared_ptr<Texture> createTexture(const std::string& filepath) override;
	std::shared_ptr<Shader> createShader(const std::string& vertexSrc, const std::string& fragmentSrc) override;

	// --- State Management ---
	void setViewport(int width, int height) override;
	void setClearColour(const glm::vec4& color) override;

	// --- Debugging ---
	void enableWireframe(bool enabled) override;

	// --- Multi-Window Support ---
	void bindTarget(WindowHandle window) override;

	// --- Miscellaneous ---
	void flush() override;

private:

	unsigned int m_shader; // Shader ID

	// --- Internal Initialisation ---
	void loadGLFW();
	void loadGLAD();
	void loadGLFWSettings();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void onFramebufferSizeChange(int width, int height);

	GLFWwindow* m_window;
};
