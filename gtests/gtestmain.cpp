#include <gtest/gtest.h>
#include "windowmanager/OpenGLWindowHandleTest.h"
#include "windowmanager/WindowManagerTest.h"

// Main function for Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}