#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

private:
    GLuint m_programID = 0;
    void checkCompileErrors(GLuint shader, const std::string& type);
};