#include "celestialBody.hpp"
#include <glm/gtc/matrix_transform.hpp>

CelestialBody::CelestialBody(std::string &name, Mesh &mesh, glm::vec3 &color, const glm::vec3 &pos, const glm::vec3 &velocity, float mass, float radius)
    : m_name(name), m_mesh(&mesh), m_color(color), m_position(pos), m_velocity(velocity), m_acceleration(0.0f), m_mass(mass), m_radius(radius)
{}

void CelestialBody::addForce(const glm::vec3 &force)
{
    if (m_mass > 0.0f)
        m_acceleration += force/m_mass;
}

void CelestialBody::update(float dt)
{
    // Symplectic Euler method
    m_velocity += m_acceleration * dt;
    m_position += m_velocity * dt;

    // Reset acceleration for next loop
    m_acceleration = glm::vec3(0.0f);
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

const std::string CelestialBody::toString() const
{
    return tfm::format(
        "CelestialBody{name: %s, mass: %f, position: [%f, %f, %f], velocity: [%f, %f, %f]}",
        m_name.c_str(), m_mass, 
        m_position.x, m_position.y, m_position.z,
        m_velocity.x, m_velocity.y, m_velocity.z
    );
}
