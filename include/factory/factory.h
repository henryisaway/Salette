#pragma once
#include "../core/config.h"

class PrimitiveModels{
public:
	unsigned int makeTriangle();		// Creates triangle mesh on the middle of the screen;
	unsigned int makeQuad();
	void draw(unsigned int shader);
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
};