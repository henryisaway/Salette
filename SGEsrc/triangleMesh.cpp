#include "triangleMesh.h"

TriangleMesh::TriangleMesh() {
    
    std::vector<float> positionData = {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };
    std::vector<int> elementData = {0, 1, 2, 2, 1, 3};
    
    vertex_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(1); // Allocates memory for 1 vertex buffers

    glGenBuffers(1, VBOs.data());
    
    // Position
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positionData.size() * sizeof(float), positionData.data(), GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);
    
    // Element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementData.size() * sizeof(int), elementData.data(), GL_STATIC_DRAW); 
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, VBOs.data());
    glDeleteBuffers(1, &EBO);
}
