#include <gtest/gtest.h>
#include "../../include/core/config.h"
#include "../../include/windowmanager/OpenGLWindowHandle.h"

class OpenGLWindowHandleTest : public ::testing::Test {
protected:
	void SetUp() override;
	void TearDown() override;

	GLFWwindow* m_Window;
    std::unique_ptr<OpenGLWindowHandle> m_Handle;
};