#include "system.hpp"
#include <glm/gtc/matrix_transform.hpp>

static std::vector<float> createCircleVertices()
{
    std::vector<float> vertices;
    vertices.reserve((SEGMENTS + 2) * 3);   // 1 center vertex, (SEGMENTS + 1) surrounding vertices, 3 coordinates per vertex

    // Center
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    constexpr float TWO_PI = 2.0f * 3.14159265358979323846f;
    for (size_t i = 0; i <= SEGMENTS; i++)
    {
        float theta = TWO_PI * static_cast<float>(i) / static_cast<float>(SEGMENTS);
        vertices.push_back(std::cos(theta));
        vertices.push_back(std::sin(theta));
        vertices.push_back(0.0f);
    }

    return vertices;
}

SolarSystem::SolarSystem()
    : m_mesh(createCircleVertices())
{
    m_celestialBodies.reserve(2);

    // Construct orbitting planet
    glm::vec3 planetPos(0.0f, 1.0f, 0.0f);
    float planetRadius = 0.1f;
    m_celestialBodies.try_emplace("planet", m_mesh, planetPos, planetRadius);

    // Construct sun
    glm::vec3 sunPos(0.0f, 0.0f, 0.0f);
    float sunRadius= 0.3f;
    m_celestialBodies.try_emplace("sun", m_mesh, sunPos, sunRadius);
}

void SolarSystem::update(float time)
{
    glm::vec3 planetPos(std::sin(time), std::cos(time), 0.0f);
    m_celestialBodies.at("planet").updatePosition(planetPos);
}

void SolarSystem::draw(Window* window, Shader* shader) const
{
    // Set projection matrix
    float aspect = window->getAspectRatio();
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    shader->setMat4("u_Projection", projection);
    
    for (const auto& [name, body]: m_celestialBodies)
    {
        body.draw(shader);
    }
}