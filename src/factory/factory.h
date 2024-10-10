#pragma once
#include "../config.h"

class PrimitiveModels{
public:
	unsigned int makeTriangle();		// Creates triangle mesh on the middle of the screen;
	void draw(unsigned int shader);
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
};