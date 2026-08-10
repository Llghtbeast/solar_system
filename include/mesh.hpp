#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    ~Mesh();

    void draw(GLenum drawMode = GL_TRIANGLE_FAN) const;

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLsizei m_vertexCount = 0;
};