#include "OpenGLWindowHandleTest.h"

void OpenGLWindowHandleTest::SetUp(){
	// Ensure GLFW is properly initialized before any test
	if (!glfwInit()) {
		FAIL() << "Failed to initialize GLFW in test setup.";
	}
}

void OpenGLWindowHandleTest::TearDown(){
	// Terminate GLFW after all tests
	glfwTerminate();
}

TEST_F(OpenGLWindowHandleTest, ConstructorCreatesWindow) {
	EXPECT_NO_THROW({
		OpenGLWindowHandle window(800, 600, "Test Window", 0);
	});
}

TEST_F(OpenGLWindowHandleTest, GetNativeHandleReturnsValidPointer) {
	OpenGLWindowHandle window(800, 600, "Test Window", 0);
	void* nativeHandle = window.getNativeHandle();

	EXPECT_NE(nativeHandle, nullptr) << "Native handle should not be null.";
}

TEST_F(OpenGLWindowHandleTest, GettersReturnCorrectValues) {
	int width = 800;
	int height = 600;
	std::string title = "Test Window";

	OpenGLWindowHandle window(width, height, title, 0);

	EXPECT_EQ(window.getWidth(), width) << "Width should match the constructor value.";
	EXPECT_EQ(window.getHeight(), height) << "Height should match the constructor value.";
	EXPECT_EQ(window.getTitle(), title) << "Title should match the constructor value.";
}

TEST_F(OpenGLWindowHandleTest, ShouldCloseReturnsFalseInitially) {
	OpenGLWindowHandle window(800, 600, "Test Window", 0);
	EXPECT_FALSE(window.shouldClose()) << "Window should not report close immediately after creation.";
}

TEST_F(OpenGLWindowHandleTest, UpdateWindowSizeReflectsResizedWindow) {
	OpenGLWindowHandle window(800, 600, "Test Window", 0);

	// Simulate a window resize
	glfwSetWindowSize(static_cast<GLFWwindow*>(window.getNativeHandle()), 1024, 700);

	while(window.getWidth() == 800 && window.getHeight() == 600){
		glfwPollEvents();
	}

	EXPECT_EQ(window.getWidth(), 1024) << "Width should update after resizing.";
	EXPECT_EQ(window.getHeight(), 700) << "Height should update after resizing.";
}

TEST_F(OpenGLWindowHandleTest, DestructorDestroysWindow) {
	GLFWwindow* rawWindow = nullptr;

	{
		OpenGLWindowHandle window(800, 600, "Test Window", 0);
		rawWindow = static_cast<GLFWwindow*>(window.getNativeHandle());
		EXPECT_NE(rawWindow, nullptr) << "Raw GLFW window pointer should not be null.";

		// Ensure window is valid inside scope
		EXPECT_FALSE(glfwWindowShouldClose(rawWindow));
	}

	// After the OpenGLWindowHandle goes out of scope, the window should be destroyed
	// EXPECT_TRUE(glfwWindowShouldClose(rawWindow)) << "Window should be marked for close after destruction.";
}
