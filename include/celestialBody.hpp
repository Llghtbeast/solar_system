#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>

class CelestialBody {
public:
    CelestialBody(Mesh& mesh, const glm::vec3& pos, float r);

    void updatePosition(const glm::vec3 position);
    glm::mat4 getModelMatrix() const;
    void draw(Shader* shader) const;

private:
    Mesh* m_mesh = nullptr;
    glm::vec3 m_position;
    float m_radius;
};