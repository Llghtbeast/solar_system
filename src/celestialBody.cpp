#include "celestialBody.hpp"
#include <glm/gtc/matrix_transform.hpp>

CelestialBody::CelestialBody(Mesh& mesh, const glm::vec3& pos, float r)
    : m_mesh(&mesh), m_position(pos), m_radius(r)
{}

void CelestialBody::updatePosition(const glm::vec3 position)
{
    m_position = position;
}

glm::mat4 CelestialBody::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::scale(model, glm::vec3(m_radius, m_radius, 1.0f));
    return model;
}

void CelestialBody::draw(Shader* shader) const
{
    shader->setMat4("u_Model", getModelMatrix());
    if (m_mesh)
    {
        m_mesh->draw(GL_TRIANGLE_FAN);
    }
}
