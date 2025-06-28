#pragma once
#include <includes.h>

class PrimitiveModel {
public:
    PrimitiveModel(unsigned int VAO, unsigned int VBO, unsigned int EBO, int indices_count);
    ~PrimitiveModel();

    void draw(unsigned int shader);

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
	unsigned int m_indices_count;
};
