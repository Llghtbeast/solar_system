#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    ~Mesh();

    void draw() const;

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLsizei m_vertexCount = 0;
};