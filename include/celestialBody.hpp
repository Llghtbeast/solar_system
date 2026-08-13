#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include "tinyformat.h"

class CelestialBody {
public:
    CelestialBody(std::string& name, Mesh& mesh, glm::vec3& color, const glm::vec3& pos, const glm::vec3& velocity, float mass, float radius);

    void addForce(const glm::vec3& force);

    /// @brief Update position and velocity vectors and reset acceleration
    /// @param dt Time step
    void update(float dt);

    const glm::vec3& getColor() const { return m_color; }
    const glm::vec3& getPosition() const { return m_position; }
    const glm::vec3& getVelocity() const { return m_velocity; }
    float getMass() const { return m_mass; }

    glm::mat4 getModelMatrix() const;
    void draw(Shader* shader) const;

    const std::string toString() const;

private:
    std::string m_name;
    Mesh* m_mesh = nullptr;
    glm::vec3 m_color;
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;
    float m_mass;
    float m_radius;
};