#include "config.h"

class TriangleMesh {
public:
TriangleMesh();
void draw();
~TriangleMesh();

private:
std::vector<unsigned int> VBOs;
unsigned int EBO, VAO, vertex_count;
};
