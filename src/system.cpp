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

    for (size_t i = 0; i <= SEGMENTS; i++)
    {
        float theta = 2 * M_PI * static_cast<float>(i) / static_cast<float>(SEGMENTS);
        vertices.push_back(std::cos(theta));
        vertices.push_back(std::sin(theta));
        vertices.push_back(0.0f);
    }

    return vertices;
}

static float findOrbitingVelocity(const glm::vec3& dir, float mass)
{
    // Find orthogonal vector to position
    // glm::vec3 helper = (std::abs(dir.x) > std::abs(dir.z))
    //                     ? glm::vec3(0.0f, 0.0f, 1.0f)
    //                     : glm::vec3(1.0f, 0.0f, 0.0f);
    
    // glm::vec3 normalizedVel = glm::normalize(glm::cross(dir, helper));

    // Find magnitude of velocity
    float dist = std::sqrt(glm::dot(dir, dir) + EPSILON);
    float magnitudeVel = std::sqrt(GRAVITATIONAL_CONSTANT * mass / dist);

    return magnitudeVel;
}

SolarSystem::SolarSystem()
    : m_mesh(createCircleVertices())
{
    m_celestialBodies.reserve(2);

    // Construct sun
    std::string sunName = "Sun";
    glm::vec3 sunColor(hexToColor(COLOR_SUN));
    glm::vec3 sunPos(0.0f, 0.0f, 0.0f);
    glm::vec3 sunVel(0.0f, 0.0f, 0.0f);
    float sunMass = 1.0f;
    float sunRadius= 0.1f;

    CelestialBody sun(sunName, m_mesh, sunColor, sunPos, sunVel, sunMass, sunRadius);
    m_celestialBodies.push_back(sun);

    // Construct orbitting planet
    std::string planetName = "Planet";
    glm::vec3 planetColor(hexToColor(COLOR_EARTH));
    glm::vec3 planetPos(0.0f, 0.8f, 0.0f);
    float planetMass = 0.0025f;
    glm::vec3 planetVel = glm::vec3(1.0f, 0.0f, 0.0f);
    float planetRadius = 0.02f;

    CelestialBody planet(planetName, m_mesh, planetColor, planetPos, planetVel, planetMass, planetRadius);
    m_celestialBodies.push_back(planet);
}

void SolarSystem::update(float dt)
{
    for (auto it1 = m_celestialBodies.begin(); it1 != m_celestialBodies.end(); ++it1)
    {
        for (auto it2 = std::next(it1); it2 != m_celestialBodies.end(); ++it2)
        {
            glm::vec3 dir = it2->getPosition() - it1->getPosition();
            float distSq = glm::dot(dir, dir) + EPSILON;
            float dist = std::sqrt(distSq);

            glm::vec3 force = GRAVITATIONAL_CONSTANT * (it1->getMass() * it2->getMass()) * dir / (dist * distSq);

            it1->addForce(force);
            it2->addForce(-force);
        }
    }

    // Update all the positions and velocities now that the forces have been added up
    for (auto& body: m_celestialBodies)
    {
        body.update(dt);
    }
}

void SolarSystem::draw(Window* window, Shader* shader) const
{
    // Set projection matrix
    float aspect = window->getAspectRatio();
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    shader->setMat4("u_Projection", projection);
    
    for (const auto& body : m_celestialBodies)
    {
        shader->setVec3("u_Color", body.getColor());
        body.draw(shader);
    }
}