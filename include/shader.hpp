#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setVec3(const std::string& name, const glm::vec3& vec) const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint m_programID = 0;
    void checkCompileErrors(GLuint shader, const std::string& type);
};