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

static glm::vec3 findOrbitingVelocity(const glm::vec3& pos, const CelestialBody* orbitCenter)
{
    glm::vec3 dir = pos - orbitCenter->getPosition();

    glm::vec3 normal(0.0f, 0.0f, 1.0f);
    glm::vec3 velDir = glm::normalize(glm::cross(dir, normal));

    //Find magnitude of velocity
    float dist = std::sqrt(glm::dot(dir, dir) + EPSILON);
    float velMagn = std::sqrt(GRAVITATIONAL_CONSTANT * orbitCenter->getMass() / dist);

    return velMagn * velDir + orbitCenter->getVelocity();
}

SolarSystem::SolarSystem(): m_mesh(createCircleVertices()) {}

SolarSystem::SolarSystem(const std::string& filepath)
    : m_mesh(createCircleVertices())
{
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_file(filepath.c_str());

    if (!res)
        throw std::runtime_error("Failed to load solar system XML file: " + std::string(res.description()));

    pugi::xml_node systemNode = doc.child("system");
    if (!systemNode)
        throw std::runtime_error("Invalid XML file structure: missing <system> root tag.");
    
    // Loop through all the <body> tags
    for (pugi::xml_node bodyNode = systemNode.child("body"); bodyNode; bodyNode = bodyNode.next_sibling("body"))
    {
        std::string name = bodyNode.attribute("name").as_string("Unnamed");
        float mass       = bodyNode.attribute("mass").as_float(0.0f);
        float radius     = bodyNode.attribute("radius").as_float(0.1f);

        // Parse auto orbitting
        bool autoOrbit = bodyNode.attribute("auto_orbit").as_bool(false);
        std::string orbitCenterName = bodyNode.attribute("orbit_center").as_string("None");

        // Parse color attribute
        std::string hexStr = bodyNode.attribute("color").as_string("0xFFFFFF");
        glm::vec3 color    = hexToColor(std::stoul(hexStr, nullptr, 16));

        // Parse position
        pugi::xml_node posNode = bodyNode.child("position");
        if (!posNode)
            throw std::runtime_error("Invalid XML file structure: missing <position> tag.");
        glm::vec3 pos(
            posNode.attribute("x").as_float(0.0f),
            posNode.attribute("y").as_float(0.0f),
            posNode.attribute("z").as_float(0.0f)
        );

        // Parse velocity
        glm::vec3 vel(0.0f);
        if (autoOrbit) {
            auto it = m_celestialBodies.find(orbitCenterName);
            if (it != m_celestialBodies.end())
            {
                const CelestialBody& orbitCenter = it->second;
                vel = findOrbitingVelocity(pos, &orbitCenter);
            }
            else throw std::runtime_error("Orbit center \"" + orbitCenterName + "\" not found.");

        } else {
            pugi::xml_node velNode = bodyNode.child("velocity");
            if (!velNode)
                throw std::runtime_error("Invalid XML file structure: missing <velocity> tag when autoOrbit is false.");
            if (velNode) {
                vel = glm::vec3(
                    velNode.attribute("x").as_float(0.0f),
                    velNode.attribute("y").as_float(0.0f),
                    velNode.attribute("z").as_float(0.0f)
                );
            }
        }

        // Add body to list
        m_celestialBodies.try_emplace(name, name, m_mesh, color, pos, vel, mass, radius);
    }
}

void SolarSystem::update(float dt)
{
    for (auto it1 = m_celestialBodies.begin(); it1 != m_celestialBodies.end(); ++it1)
    {
        for (auto it2 = std::next(it1); it2 != m_celestialBodies.end(); ++it2)
        {
            glm::vec3 dir = it2->second.getPosition() - it1->second.getPosition();
            float distSq = glm::dot(dir, dir) + EPSILON;
            float dist = std::sqrt(distSq);

            glm::vec3 force = GRAVITATIONAL_CONSTANT * (it1->second.getMass() * it2->second.getMass()) * dir / (dist * distSq);

            it1->second.addForce(force);
            it2->second.addForce(-force);
        }
    }

    // Update all the positions and velocities now that the forces have been added up
    for (auto& [_, body]: m_celestialBodies)
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
    
    for (const auto& [_, body] : m_celestialBodies)
    {
        shader->setVec3("u_Color", body.getColor());
        body.draw(shader);
    }
}

const std::string SolarSystem::toString() const
{
    std::string bodiesStr;

    for (auto it = m_celestialBodies.begin(); it != m_celestialBodies.end(); ++it)
    {
        bodiesStr += tfm::format("        %s", it->second.toString());
        if (std::next(it) != m_celestialBodies.end())
            bodiesStr += ",\n";
    }

    return tfm::format(
        "solar system {\n"
        "    celestial bodies [\n"
        "%s\n"
        "    ]\n"
        "}",
        bodiesStr.c_str()
    );
}
