#include "test.h"

Test::~Test(){
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteBuffers(VBOs.size(), VBOs.data());
}

unsigned int Test::makeTriMesh(){
    std::vector<float> vertices = {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);
        
    return VAO;
}

unsigned int Test::makeCube(float s){
    std::vector<float> vertices = {
         s,  s, -s, 1.0f, 1.0f,
         s, -s, -s, 1.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s,  s, -s, 0.0f, 1.0f,
         s,  s, -s, 1.0f, 1.0f,

        -s, -s,  s, 0.0f, 0.0f,
         s, -s,  s, 1.0f, 0.0f,
         s,  s,  s, 1.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f,
        -s,  s,  s, 0.0f, 1.0f,
        -s, -s,  s, 0.0f, 0.0f,

        -s,  s,  s, 1.0f, 1.0f,
        -s,  s, -s, 1.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s,  s, 0.0f, 1.0f,
        -s,  s,  s, 1.0f, 1.0f,

         s, -s, -s, 0.0f, 0.0f,
         s,  s, -s, 1.0f, 0.0f,
         s,  s,  s, 1.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f,
         s, -s,  s, 0.0f, 1.0f,
         s, -s, -s, 0.0f, 0.0f,

        -s, -s, -s, 0.0f, 0.0f,
         s, -s, -s, 1.0f, 0.0f,
         s, -s,  s, 1.0f, 1.0f,  
         s, -s,  s, 1.0f, 1.0f,
        -s, -s,  s, 0.0f, 1.0f,
        -s, -s, -s, 0.0f, 0.0f,

         s,  s,  s, 1.0f, 1.0f,
         s,  s, -s, 1.0f, 0.0f,
        -s,  s, -s, 0.0f, 0.0f, 
        -s,  s, -s, 0.0f, 0.0f,
        -s,  s,  s, 0.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    
    return VAO;
}
