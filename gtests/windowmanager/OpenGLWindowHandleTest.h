#include <gtest/gtest.h>
#include "../../include/windowmanager/OpenGLWindowHandle.h"
#include <includes.h>

namespace Vista {

class OpenGLWindowHandleTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;
};

}