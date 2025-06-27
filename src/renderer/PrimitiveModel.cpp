#include "../../include/renderer/PrimitiveModel.h"

PrimitiveModel::PrimitiveModel(unsigned int VAO, unsigned int VBO, unsigned int EBO, int indices_count)
    : m_VAO(VAO), m_VBO(VBO), m_EBO(EBO), m_indices_count(indices_count) {}

PrimitiveModel::~PrimitiveModel() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void PrimitiveModel::draw(unsigned int shader) {
    glUseProgram(shader);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices_count, GL_UNSIGNED_INT, 0);
}
