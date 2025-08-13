#include "../../include/renderer/OpenGLRenderer.h"


namespace Salette {
// --- Basic Management ---

void OpenGLRenderer::initialise() {
	// Only initialize GLFW here. GLAD will be initialized on the first context creation.
	loadGLFW();
}

void OpenGLRenderer::shutdown() {
	glfwTerminate();
}

void OpenGLRenderer::beginFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::endFrame() {
    if (m_bound_target) {
	    glfwSwapBuffers(static_cast<GLFWwindow*>(m_bound_target->getNativeHandle()));
    }
}


// --- OpenGL Setup ---
void OpenGLRenderer::loadGLFW() {
	CLIO_INFO("Setting up GLFW...");
	if(!glfwInit()){
		CLIO_FATAL("Failed to initialise GLFW.");
		exit(-1);
	}

    glfwDefaultWindowHints();
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// --- Multi-Window Support ---
void OpenGLRenderer::bindTarget(WindowHandle* window) {
    m_bound_target = window;
    if (m_bound_target) {
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_bound_target->getNativeHandle()));

        // Load GLAD the first time we get a valid context.
        static bool glad_loaded = false;
        if (!glad_loaded) {
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                CLIO_FATAL("Failed to initialise GLAD.");
                glfwTerminate();
                exit(-1);
            }

            CLIO_INFO("GLAD is ready!");
            glad_loaded = true;
        }

    } else {
        glfwMakeContextCurrent(nullptr);
    }
}

// --- State Management ---

void OpenGLRenderer::setViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::setClearColour(const glm::vec4& colour) {
    if (m_bound_target) {
        m_bound_target->setClearColour(colour);
    }
}

// --- Framebuffer callback ---

void OpenGLRenderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	OpenGLRenderer* renderer = static_cast<OpenGLRenderer*>(glfwGetWindowUserPointer(window));
	if(renderer){
		renderer->onFramebufferSizeChange(width, height);
	}
}

void OpenGLRenderer::onFramebufferSizeChange(int width, int height) {
	glViewport(0, 0, width, height);
}

}