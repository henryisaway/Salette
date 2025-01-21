#include "WindowManagerTest.h"

void WindowManagerTest::SetUp(){
}

void WindowManagerTest::TearDown(){
}

TEST_F(WindowManagerTest, CreateWindowReturnsNonNull){
	WindowManager windowmanager;
	std::shared_ptr<WindowHandle> newWindow = windowmanager.createWindow(800, 600, "Test Window");
	EXPECT_NE(newWindow, nullptr) << "Window handle should not be null.";
}