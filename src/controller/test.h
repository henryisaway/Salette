#pragma once
#include "../config.h"

class Test{
public:
    ~Test();
    unsigned int makeTriMesh();
    unsigned int makeCube(float size);

private:
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
};
