#include "OpenGLWindowHandleTest.h"

void OpenGLWindowHandleTest::SetUp(){
    if (!glfwInit()) {
            FAIL() << "Failed to initialize GLFW";
        }

        // Create a dummy GLFW window
        m_Window = glfwCreateWindow(800, 600, "Test Window", nullptr, nullptr);
        if (!m_Window) {
            FAIL() << "Failed to create GLFW window";
        }

        // Create an OpenGLWindowHandle
        m_Handle = std::make_unique<OpenGLWindowHandle>(m_Window, "Test Window");
}

void OpenGLWindowHandleTest::TearDown(){
        m_Handle.reset();  // Ensure the handle is destroyed first
        glfwTerminate();
    }

// Test: GetNativeHandle
TEST_F(OpenGLWindowHandleTest, GetNativeHandle) {
    ASSERT_EQ(static_cast<GLFWwindow*>(m_Handle->getNativeHandle()), m_Window)
        << "Native handle should match the GLFW window pointer";
}

// Test: GetTitle
TEST_F(OpenGLWindowHandleTest, GetTitle) {
    ASSERT_EQ(m_Handle->getTitle(), "Test Window")
        << "Window title should match the provided string";
}

// Test: GetWidth and GetHeight
TEST_F(OpenGLWindowHandleTest, GetDimensions) {
    ASSERT_EQ(m_Handle->getWidth(), 800) << "Window width should be 800";
    ASSERT_EQ(m_Handle->getHeight(), 600) << "Window height should be 600";
}

// Test: ShouldClose (Default State)
TEST_F(OpenGLWindowHandleTest, ShouldCloseDefault) {
    ASSERT_FALSE(m_Handle->shouldClose())
        << "ShouldClose should be false for a newly created window";
}

// Test: ShouldClose (After Trigger)
TEST_F(OpenGLWindowHandleTest, ShouldCloseTriggered) {
    // Simulate closing the window
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    ASSERT_TRUE(m_Handle->shouldClose())
        << "ShouldClose should return true after triggering close";
}
